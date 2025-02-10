#include "Enemy.h"
#include "Novice.h"
#include "time.h"
#include <math.h>


int Enemy::enemyCount_ = 0;

Enemy::Enemy() {
	srand(unsigned int(time(nullptr)));
	pos_ = { 0,0 };
	vel_ = { -2,0 };
	acc_ = { 0,0 };
	size_ = { 32,32 };
	speed_ = 2.0f;
	isAlive_ = false;
	screen_ = new Screen;
	respawnTimer_ = (rand() % 30 + 1) * 20;
	SetSide(pos_, size_);
	SetVertex(size_);
}

Enemy::~Enemy() {
	delete screen_;
}


void Enemy::Update(const float& escalation) {
	if (isAlive_) {
		vel_.x += acc_.x;
		vel_.y += acc_.y;

		// ベクトルの正規化
		float length = sqrtf(powf(vel_.x, 2.0f) + powf(vel_.y, 2.0f));
		if (length != 0) {
			vel_ /= length;
		}

		pos_.x += vel_.x * speed_;
		pos_.y += vel_.y * speed_;

		SetSide(pos_, size_);

		// 上下で反射
		if (side_.top > 720 || side_.bottom < 0) {
			vel_.y *= -1;
		}

		// 画面外で消滅
		if (side_.right < 0) {
			Despawn();
		}
	} else {
		respawnTimer_--;
		if (respawnTimer_ < 0) {
			Spawn(escalation);
		}
	}
}

void Enemy::Spawn(const float& escalation) {
	isAlive_ = true;
	respawnTimer_ = static_cast<int>(300 - escalation * 10);
	vel_.y = (rand() % 32 - 16) * 3.0f;

	pos_ = { 1280 + (rand() % 500) + size_.x,static_cast<float>(rand() % static_cast<int>(720.0f - size_.y)) };
	speed_ = 2.5f + escalation;
	enemyCount_++;
}

void Enemy::Hit() {
	respawnTimer_ *= 3; // 撃破ボーナス
	Despawn();
}

void Enemy::Despawn() {
	isAlive_ = false;
	enemyCount_--;
}

void Enemy::Draw() {
	if (isAlive_) {
		screenPos_ = screen_->ScreenTransform(pos_);
		theta_ += 0.05f;
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
	}
}