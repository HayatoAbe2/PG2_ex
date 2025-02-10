#include "Vector2.h"
#include "Vector2.h"

void Vector2::operator+=(const Vector2& vec) {
	this->x += vec.x;
	this->y += vec.y;
}

void Vector2::operator-=(const Vector2& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
}

void Vector2::operator*=(const Vector2& vec) {
	this->x *= vec.x;
	this->y *= vec.y;
}

void Vector2::operator/=(const Vector2& vec) {
	this->x /= vec.x;
	this->y /= vec.y;
}

Vector2 Vector2::operator+(const Vector2& vec) {
	return {
		this->x + vec.x,
		this->y + vec.y
	};
}

Vector2 Vector2::operator-(const Vector2& vec) {
	return {
		this->x - vec.x,
		this->y - vec.y
	};
}

Vector2 Vector2::operator*(const Vector2& vec) {
	return {
		this->x * vec.x,
		this->y * vec.y
	};
}

Vector2 Vector2::operator/(const Vector2& vec) {
	return {
		this->x / vec.x,
		this->y / vec.y
	};
}

void Vector2::operator*=(const float& scalar){
	this->x *= scalar;
	this->y *= scalar;
}

void Vector2::operator/=(const float& scalar){
	this->x /= scalar;
	this->y /= scalar;
}
