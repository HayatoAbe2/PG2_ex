#include "Rectangle.h"

void Rectangle::SetSide(const Vector2& center, const Vector2& size) {
	side_.left = center.x - size.x / 2.0f;
	side_.right = center.x + size.x / 2.0f;
	side_.top = center.y + size.y / 2.0f;
	side_.bottom = center.y - size.y / 2.0f;
}

void Rectangle::SetVertex(const Vector2& size) {
	localVertex_.leftTop = { -size.x / 2.0f,size.y / 2.0f };
	localVertex_.rightTop = { size.x / 2.0f,size.y / 2.0f };
	localVertex_.leftBottom = { -size.x / 2.0f,-size.y / 2.0f };
	localVertex_.rightBottom = { size.x / 2.0f,-size.y / 2.0f };
}

