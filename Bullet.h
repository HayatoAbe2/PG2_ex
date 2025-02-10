#pragma once
#include "Object.h"
class Bullet : Object {
public:
	// 弾最大数
	static int maxBulletCount;

	Bullet();
	~Bullet();

	bool GetIsShot() { return isShot_; };
	Side GetSide() { return side_; };

	void Update();
	void Draw() override;

	// 発射
	void Shoot(const Vector2& playerPos);
	void Erase();

private:

	bool isShot_;
	int image_;
	int color_;
};
