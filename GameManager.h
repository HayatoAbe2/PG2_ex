#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
class GameManager{
public:

	GameManager();
	~GameManager();

	void Update(char preKeys[256], char keys[256]);
	void Draw();

	void Transition();

private:

	int maxEnemyCount_;
	int timeCount_;
	float escalation_;
	Player *player_;
	Enemy *enemy_[32];
	Collision* collision_;

	bool isSceneChanging_;
	float sceneChangeProgress_;
	int color_;

	enum Scene {
		TITLE,
		GAME,
		RESULT
	};
	int currentScene_;
	int nextScene_;
};

