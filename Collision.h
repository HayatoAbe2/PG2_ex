#pragma once
#include "Rectangle.h"
#include "Player.h"
#include "Enemy.h"
class Collision{
public:
	void Update(Player& player, Enemy** enemy);
	bool HitCheck(const Rectangle::Side &side1, const Rectangle::Side &side2);

private:

};

