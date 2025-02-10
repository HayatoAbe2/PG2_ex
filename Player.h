#pragma once
#include "Object.h"
#include "Bullet.h"
#include "iostream"
#include <vector>

class Player : public Object {
public:
	Player();
	~Player();

	void Update(char preKeys[256], char keys[256]);
	void Draw() override;

	int GetAlive() { return isAlive_; };
	Side GetSide() { return side_; };
	int GetMaxBulletCount() { return maxBulletCount_; };
	bool GetBulletIsShot(const int& i) { return bullet_[i]->GetIsShot(); };
	Side GetBulletSide(const int& i) { return bullet_[i]->GetSide(); };

	void Hit();

private:
	bool isAlive_;
	int image_;

	int shootInterval_;
	int maxBulletCount_;
	Bullet* bullet_[2];

	float theta_;
};

