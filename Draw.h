#pragma once
#include "Novice.h"
#include "Rectangle.h"
#include "Screen.h"

class Draw {
private:

	// 描くものの座標
	Vector2 screenPos_;
	Rectangle::Vertex screenVertex_;

	// リソース
	int backGround;
	int bullet;
	int player;
	int enemy;

	Screen* screen_;

public:
	Draw();
	~Draw();

	void DrawObj(const Vector2& pos, const Rectangle::Vertex& localVertex, const int image);
};