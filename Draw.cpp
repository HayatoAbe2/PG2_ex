#include "Draw.h"

Draw::Draw(){
	screen_ = new Screen;
	backGround = Novice::LoadTexture("./NoviceResources/white1x1.png");
	player = Novice::LoadTexture("./NoviceResources/white1x1.png");
	enemy = Novice::LoadTexture("./NoviceResources/white1x1.png");
	bullet = Novice::LoadTexture("./NoviceResources/white1x1.png");
}

Draw::~Draw(){
	delete screen_;
}

void Draw::DrawObj(const Vector2& pos,const Rectangle::Vertex& localVertex,const int image) {
	screenPos_ = screen_->ScreenTransform(pos);
	screenVertex_.leftTop = screen_->ScreenTransform(localVertex.leftTop, { 1,1 }, 0, pos);

	Novice::DrawQuad(
		static_cast<int>(screenVertex_.leftTop.x), static_cast<int>(screenVertex_.leftTop.y),
		static_cast<int>(screenVertex_.rightTop.x), static_cast<int>(screenVertex_.rightTop.y),
		static_cast<int>(screenVertex_.leftBottom.x), static_cast<int>(screenVertex_.leftBottom.y),
		static_cast<int>(screenVertex_.rightBottom.x), static_cast<int>(screenVertex_.rightBottom.y),
		0, 0, 1, 1, image, WHITE);
}