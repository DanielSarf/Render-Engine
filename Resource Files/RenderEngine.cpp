#include "../Header Files/RenderEngine.h"

RenderEngine::RenderEngine(Scene& inputScene) : pixels(inputScene.getWidth(), inputScene.getHeight(), inputScene.getBitDepth())
{
	height = inputScene.getHeight();
	width = inputScene.getWidth();

	aspectRatio = float(width) / height;

	x0 = -1;
	x1 = 1;
	xStep = (x1 - x0) / (width - 1);

	y0 = -1 / aspectRatio;
	y1 = 1 / aspectRatio;
	yStep = (y1 - y0) / (height - 1);

	camera = inputScene.getCamera();

	float x, y;

	for (int i = 0; i < height; i++)
	{
		y = y0 + i * yStep;

		for (int j = 0; j < width; j++)
		{
			x = x0 + j * xStep;

			Ray ray(*camera, (Vector3(x, y, 0) - *camera));

			pixels.setPixel(j, i, rayTrace(ray, inputScene));
		}
	}

	pixels.writeFile();
}

Color RenderEngine::rayTrace(Ray & inputRay, Scene & inputScene) const
{
	Color color;

	float hitDistance = NULL;
	Object* objectHit = NULL;

	findNearest(objectHit, hitDistance, inputRay, inputScene);

	if (objectHit == NULL)
	{
		return color;
	}

	Vector3 hitPosition = inputRay.getOrigin() + inputRay.getDirection() * hitDistance;

	Vector3 hitNormal = (*objectHit).normal(hitPosition);

	color = color + colorAt(objectHit, hitPosition, hitNormal, inputScene);

	return color;
}

void RenderEngine::findNearest(Object * &objectHit, float &hitDistance, Ray &inputRay, Scene &inputScene) const
{
	float minimumDistance = NULL;

	int numberOfObjects = (*inputScene.getObjects()).size();

	for (int i = 0; i < numberOfObjects; i++)
	{
		float distance = NULL;

		distance = (*inputScene.getObjects())[i].intersections(inputRay);

		if (distance != NULL && (objectHit == NULL || distance < minimumDistance))
		{
			minimumDistance = distance;

			objectHit = &(*inputScene.getObjects())[i];
		}
	}

	hitDistance = minimumDistance;
}

Color RenderEngine::colorAt(Object *&objectHit, Vector3 &hitPosition, Vector3 &hitNormal, Scene &inputScene) const
{
	Material objectMaterial = (*objectHit).getMaterial();

	Color objectColor = objectMaterial.colorAtMaterial();

	Vector3 toCam = *(inputScene.getCamera()) - hitPosition;

	float specularK = 50;

	Color color = Color("#000000") + objectMaterial.getAmbient();

	int numberOfLights = (*inputScene.getLights()).size();
	
	for (int i = 0; i < numberOfLights; i++)
	{
		Ray toLight(hitPosition, (*inputScene.getLights())[i].getLocation() - hitPosition);

		float hitNormalDotToLightDirection = hitNormal.dotProduct(toLight.getDirection());

		color = color + objectColor * objectMaterial.getDiffuse() * (hitNormalDotToLightDirection > 0 ? hitNormalDotToLightDirection : 0);

		Vector3 halfVector = (toLight.getDirection() + toCam).normalize();

		float hitNormalDotHalfVector = hitNormal.dotProduct(halfVector);

		color = color + (*inputScene.getLights())[i].getColor() * objectMaterial.getSpecular() * pow((hitNormalDotHalfVector > 0 ? hitNormalDotHalfVector : 0), specularK);
	}

	return color;
}