#include "Collision.h"

void Collision::Update(Player& player, Enemy** enemy) {
	// 敵と弾の判定
	for (int i = 0; i < player.GetMaxBulletCount(); i++) { //  弾が撃たれているか確認
		if (player.GetBulletIsShot(i)) {

			for (int j = 0; j < 32; j++) { // 敵が生きているか確認
				if (enemy[j]->GetAlive()) {

					if (HitCheck(player.GetBulletSide(i), enemy[j]->GetSide())) {
						enemy[j]->Hit();
					}
				}
			}
		}
	}

	// プレイヤーと敵の判定
	for (int i = 0; i < 32; i++) { // 弾が撃たれているか確認
		if (enemy[i]->GetAlive()) {
			if (player.GetAlive()) { // プレイヤーが生きているか確認

				if (HitCheck(enemy[i]->GetSide(), player.GetSide())) {
					player.Hit();
				}
			}
		}
	}
}


bool Collision::HitCheck(const Rectangle::Side& side1, const Rectangle::Side& side2) {
	// 当たり判定
	if (side1.left < side2.right && side2.left < side1.right &&
		side1.bottom < side2.top && side2.bottom < side1.top) {
		return true;
	}
	return false;
}
