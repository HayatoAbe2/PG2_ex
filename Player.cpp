#include "Player.h"
#include "Novice.h"
#include <math.h>

Player::Player() {
	pos_ = { 100,360 };
	vel_ = { 0,0 };
	size_ = { 32,32 };
	speed_ = 6.0f;
	isAlive_ = true;
	maxBulletCount_ = 2;
	shootInterval_ = 45;
	SetSide(pos_, size_);
	SetVertex(size_);

	screen_ = new Screen;
	image_ = Novice::LoadTexture("./NoviceResources/white1x1.png");

	for (int i = 0; i < maxBulletCount_; i++) {
		bullet_[i] = new Bullet;
	}

	theta_ = 0;
}

Player::~Player() {
	delete screen_;
	for (int i = 0; i < maxBulletCount_; i++) {
		delete bullet_[i];
	}
}

void Player::Update(char preKeys[256], char keys[256]) {
	if (isAlive_) {
		//-----------------
		// 移動
		//-----------------
		vel_ = { 0,0 };
		// キー入力
		if (keys[DIK_A]) {
			vel_.x--;
		}
		if (keys[DIK_D]) {
			vel_.x++;
		}
		if (keys[DIK_W]) {
			vel_.y++;
		}
		if (keys[DIK_S]) {
			vel_.y--;
		}

		// ベクトルの正規化
		float length = sqrtf(powf(vel_.x, 2.0f) + powf(vel_.y, 2.0f));
		if (length != 0) {
			vel_ /= length;
		}

		pos_.x += vel_.x * speed_;
		pos_.y += vel_.y * speed_;

		if (side_.left < 0) {
			pos_.x = size_.x / 2.0f;
		}
		if (side_.right > 1280) {
			pos_.x = 1280 - size_.x /2.0f;
		}
		if (side_.top > 720) {
			pos_.y = 720 - size_.y/2.0f;
		}
		if (side_.bottom < 0) {
			pos_.y = size_.y / 2.0f;
		}

		SetSide(pos_, size_);


		//-----------------
		// 射撃
		//-----------------

		if (!shootInterval_) {
			if (!preKeys[DIK_SPACE] && keys[DIK_SPACE]) {
				for (int i = 0; i < maxBulletCount_; i++) {
					// 撃たれていない弾があれば
					if (!bullet_[i]->GetIsShot()) {
						bullet_[i]->Shoot(pos_);
						shootInterval_ = 45;
						break;
					}
				}
			}
		}

		if (shootInterval_ > 0) {
			shootInterval_--;
		}
	} else {
		theta_ += 0.2f;
		pos_ += {-12.0f, 2.0f};
	}

	for (int i = 0; i < maxBulletCount_; i++) {
		bullet_[i]->Update();
	}

#ifdef _DEBUG
	Novice::ScreenPrintf(0, 0, "pos = {%3.0f , %3.0f}", pos_.x, pos_.y);
	Novice::ScreenPrintf(0, 20, "vel = {%2.1f , %2.1f}", vel_.x, vel_.y);
#endif // DEBUG
}

void Player::Draw(){
	screenPos_ = screen_->ScreenTransform(pos_);
	screenVertex_.leftTop = screen_->ScreenTransform(localVertex_.leftTop, { 1,1 }, theta_, pos_);
	screenVertex_.rightTop = screen_->ScreenTransform(localVertex_.rightTop, { 1,1 }, theta_, pos_);
	screenVertex_.leftBottom = screen_->ScreenTransform(localVertex_.leftBottom, { 1,1 }, theta_, pos_);
	screenVertex_.rightBottom = screen_->ScreenTransform(localVertex_.rightBottom, { 1,1 }, theta_, pos_);

	Novice::DrawQuad(
		static_cast<int>(screenVertex_.leftTop.x), static_cast<int>(screenVertex_.leftTop.y),
		static_cast<int>(screenVertex_.rightTop.x), static_cast<int>(screenVertex_.rightTop.y),
		static_cast<int>(screenVertex_.leftBottom.x), static_cast<int>(screenVertex_.leftBottom.y),
		static_cast<int>(screenVertex_.rightBottom.x), static_cast<int>(screenVertex_.rightBottom.y),
		0, 0, 1, 1, image_, WHITE);

	for (int i = 0; i < maxBulletCount_; i++) {
		bullet_[i]->Draw();
	}
}

void Player::Hit(){
	isAlive_ = false;
	// ゲーム終了

}
