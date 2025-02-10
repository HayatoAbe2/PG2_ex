#pragma once
#include "Object.h"
#include "Bullet.h"
class Enemy : Object {
public:

	static int enemyCount_;
	Enemy();
	~Enemy();

	bool GetAlive() { return isAlive_; };
	Vector2 GetPos() { return pos_; };
	Side GetSide() { return side_; };

	void Update(const float &escalation);

	void Spawn(const float &escalation);
	void Hit();
	void Despawn();

	void Draw() override;

private:

	bool isAlive_;
	int respawnTimer_;

	float theta_;
};

