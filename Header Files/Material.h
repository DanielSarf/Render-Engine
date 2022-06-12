#pragma once

#include "Vector3.h"
#include "Color.h"

class Material
{
private:
	Color color;
	Color ambient;
	float diffuse;
	float specular;

public:
	//Constructor sets data members
	Material(Color = Color(), Color = Color(), float = 1, float = 1);

	//Getter and setter functions:
	void setColor(Color);

	void setAmbient(float);

	void setDiffuse(float);

	void setSpecular(float);

	Color getColor();

	Color getAmbient();

	float getDiffuse();

	float getSpecular();

	Color colorAtMaterial();
};