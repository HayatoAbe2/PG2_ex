#pragma once
#include "Rectangle.h"
#include "Screen.h"
#include "Draw.h"

class Object :public Rectangle {
public:

	virtual void Draw();

protected:

	Vector2 pos_;
	Vector2 vel_;
	Vector2 acc_;
	Vector2 size_;
	float speed_;
	Screen* screen_;
	Vector2 screenPos_;
	int image_;
};