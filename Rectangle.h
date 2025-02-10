#pragma once
#include "Vector2.h"

class Rectangle {
public:

	struct Vertex { // (矩形の)頂点
		Vector2 leftTop;
		Vector2 rightTop;
		Vector2 leftBottom;
		Vector2 rightBottom;
	};

	struct Side {
		float left;
		float right;
		float top;
		float bottom;
	};

	// 辺の設定
	void SetSide(const Vector2& center, const Vector2& size);

	// 頂点の設定
	void SetVertex(const Vector2& size);

protected:

	Vertex localVertex_;
	Vertex screenVertex_;
	Side side_;
};