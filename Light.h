#pragma once

#include "Color.h"

class Light
{
private:
	Vector3 location;
	Color color;
	float power;
	//float radius;
	//int maxBounces;

public:
	//Constructor sets data members
	Light(Vector3 = Vector3(), Color = Color(1, 1, 1), float = 1);

	//Getter and setter functions:
	void setLocation(Vector3);

	void setLocation(Color inputColor);

	void setPower(float inputPower);

	Vector3 getLocation();

	Color getColor();

	float getPower();
};