#include "../Header Files/Vector3.h"

Vector3::Vector3(float inputX, float inputY, float inputZ) : x(inputX), y(inputY), z(inputZ) {}

Vector3 Vector3::operator+(Vector3 other) const
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(Vector3 other) const
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float other) const
{
	return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator/(float other) const
{
	return Vector3(x / other, y / other, z / other);
}

void Vector3::setAll(float inputX, float inputY, float inputZ)
{
	x = inputX;
	y = inputY;
	z = inputZ;
}

void Vector3::setX(float inputX)
{
	x = inputX;
}

void Vector3::setY(float inputY)
{
	y = inputY;
}

void Vector3::setZ(float inputZ)
{
	z = inputZ;
}

float Vector3::getX() const
{
	return x;
}

float Vector3::getY() const
{
	return y;
}

float Vector3::getZ() const
{
	return z;
}

float Vector3::dotProduct() const
{
	return (x * x + y * y + z * z);
}

float Vector3::dotProduct(Vector3 other) const
{
	return (x * other.x + y * other.y + z * other.z);
}

float Vector3::magnitude() const
{
	return sqrt(dotProduct());
}

Vector3 Vector3::normalize() const
{
	return (*this) / magnitude();
}

void Vector3::printVector() const
{
	std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}