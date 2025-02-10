#include "Bullet.h"
#include "Novice.h"
#include "Draw.h"

int Bullet::maxBulletCount = 32;

Bullet::Bullet(){
	pos_ = { 0,0 };
	vel_ = { 5,0 };
	acc_ = { 0,0 };
	size_ = { 64,16 };
	isShot_ = false;
	color_ = WHITE;
	SetSide(pos_, size_);
	SetVertex(size_);

	screen_ = new Screen;
	image_ = Novice::LoadTexture("./NoviceResources/white1x1.png");
}

Bullet::~Bullet(){
	delete screen_;
}

void Bullet::Update() {
	if (isShot_) {
		vel_.x += acc_.x;
		vel_.y += acc_.y;

		pos_.x += vel_.x;
		pos_.y += vel_.y;

		SetSide(pos_, size_);

		// 画面外で消滅
		if (side_.right < 0 || side_.left > 1280 ||
			side_.top < 0 || side_.bottom > 720) {
			Erase();
		}
	}
}

void Bullet::Shoot(const Vector2 &playerPos){
	pos_ = { playerPos.x + size_.x / 2.0f,playerPos.y };
	vel_.x = 24;
	isShot_ = true;
	color_ = WHITE;
}

void Bullet::Erase(){
	isShot_ = false;
}

void Bullet::Draw() {
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
		0, 0, 1, 1, image_, color_);
}
