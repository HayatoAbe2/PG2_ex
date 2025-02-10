#include "Object.h"

void Object::Draw() {
	screenPos_ = screen_->ScreenTransform(pos_);
	screenVertex_.leftTop = screen_->ScreenTransform(localVertex_.leftTop, { 1,1 }, 0, pos_);
	screenVertex_.rightTop = screen_->ScreenTransform(localVertex_.rightTop, { 1,1 }, 0, pos_);
	screenVertex_.leftBottom = screen_->ScreenTransform(localVertex_.leftBottom, { 1,1 }, 0, pos_);
	screenVertex_.rightBottom = screen_->ScreenTransform(localVertex_.rightBottom, { 1,1 }, 0, pos_);

	Novice::DrawQuad(
		static_cast<int>(screenVertex_.leftTop.x), static_cast<int>(screenVertex_.leftTop.y),
		static_cast<int>(screenVertex_.rightTop.x), static_cast<int>(screenVertex_.rightTop.y),
		static_cast<int>(screenVertex_.leftBottom.x), static_cast<int>(screenVertex_.leftBottom.y),
		static_cast<int>(screenVertex_.rightBottom.x), static_cast<int>(screenVertex_.rightBottom.y),
		0, 0, 1, 1, image_, WHITE);
}
