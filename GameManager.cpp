#include "GameManager.h"
#include <Novice.h>

GameManager::GameManager() {
	timeCount_ = 0;
	escalation_ = 0;
	maxEnemyCount_ = 10;

	currentScene_ = TITLE;
	nextScene_ = GAME;
	isSceneChanging_ = false;
	sceneChangeProgress_ = 0;
	color_ = 0;

	player_ = new Player;
	for (int i = 0; i < 32; i++) {
		enemy_[i] = new Enemy;
	}
	collision_ = new Collision;
}

GameManager::~GameManager() {
	delete player_;
	for (int i = 0; i < 32; i++) {
		delete enemy_[i];
	}
	delete collision_;
}

void GameManager::Update(char preKeys[256], char keys[256]) {

	switch (currentScene_) {
	case TITLE:

		if (keys[DIK_SPACE]) {
			isSceneChanging_ = true;
			nextScene_ = GAME;
		}
		break;

	case GAME:

		player_->Update(preKeys, keys);
		for (int i = 0; i < maxEnemyCount_; i++) {
			enemy_[i]->Update(escalation_);
		}

		collision_->Update(*player_, enemy_);

		// 時間経過による変更
		timeCount_++;
		escalation_ = timeCount_ / 1200.0f; // 難易度上昇(20秒で1増加)
		maxEnemyCount_ = 10 + static_cast<int>(escalation_);
		if (maxEnemyCount_ > 32) {
			maxEnemyCount_ = 32;
		}

		// シーン遷移
		if (!player_->GetAlive()) {
			isSceneChanging_ = true;
			nextScene_ = RESULT;
		}
		break;

	case RESULT:
		if (keys[DIK_SPACE]) {
			isSceneChanging_ = true;
			nextScene_ = TITLE;
		}
		break;
	}
}

void GameManager::Draw() {

	switch (currentScene_) {
	case TITLE:
		Novice::ScreenPrintf(600, 360, "PRESS [SPACE]");
		break;

	case GAME:
		player_->Draw();
		for (int i = 0; i < maxEnemyCount_; i++) {
			enemy_[i]->Draw();
		}
		break;

	case RESULT:
		Novice::ScreenPrintf(600, 360, "TIME : %ds", (timeCount_ / 60));
		break;
	}

	if (isSceneChanging_) {
		Transition();
	}
}

void GameManager::Transition() {
	sceneChangeProgress_ += 1.0f / 60.0f;

	if (sceneChangeProgress_ <= 0.3f) {
		color_ = static_cast<int>((sceneChangeProgress_ / 0.3f) * 0xFF);

	} else if (sceneChangeProgress_ >= 0.5f && sceneChangeProgress_ < 0.51f) {
		currentScene_ = nextScene_;

	} else if (sceneChangeProgress_ >= 0.7f && !(sceneChangeProgress_ >= 1.0f)) {
		color_ = static_cast<int>(((1.0f - sceneChangeProgress_) / 0.3f) * 0xFF);
	}

	if (sceneChangeProgress_ > 1.0f) {
		isSceneChanging_ = false;
		sceneChangeProgress_ = 0;
	}
	Novice::DrawBox(0, 0, 1280, 720, 0.0f, color_, kFillModeSolid);
}