#include "Screen.h"
#include "Matrix.h"
#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

Screen::Screen() {
	cameraPos_ = { 0,0 };
	width_ = 1280;
	height_ = 720;
	shake_ = {0};
	srand(unsigned int(time(nullptr)));
}

void Screen::Shake(const Vector2& amplitude) {
	shake_ = { rand() % static_cast<int>(amplitude.x) - amplitude.x / 2.0f,rand() % static_cast<int>(amplitude.y) - amplitude.y / 2.0f };
}

Vector2 Screen::ScreenTransform(const Vector2& worldPos) {

	// ビュー座標系
	viewMatrix_ = MakeViewMatrix({ cameraPos_.x + shake_.x,cameraPos_.y + shake_.y });

	// 正規化デバイス座標系
	orthographicMatrix_ = MakeOrthographicMatrix(
		0, height_,
		width_,0);

	// ビューポート行列
	viewportMatrix_ = MakeViewportMatrix(0, 0, width_, height_);

	// 行列の積
	wvpVpMatrix_ = Multiply(viewMatrix_, orthographicMatrix_);
	wvpVpMatrix_ = Multiply(wvpVpMatrix_, viewportMatrix_);

	return Transform(worldPos, wvpVpMatrix_);
}

Vector2 Screen::ScreenTransform(const Vector2 localPos, const Vector2 scale, const float theta, const Vector2& worldPos) {

	// ワールド座標系
	worldMatrix_ = MakeAffineMatrix(scale, theta, worldPos);

	// ビュー座標系
	viewMatrix_ = MakeViewMatrix({ cameraPos_.x + shake_.x,cameraPos_.y + shake_.y });

	// 正規化デバイス座標系
	orthographicMatrix_ = MakeOrthographicMatrix(
		0, height_,
		width_, 0);

	// ビューポート行列
	viewportMatrix_ = MakeViewportMatrix(0, 0, width_, height_);

	// 行列の積
	wvpVpMatrix_ = Multiply(worldMatrix_,viewMatrix_);
	wvpVpMatrix_ = Multiply(wvpVpMatrix_, orthographicMatrix_);
	wvpVpMatrix_ = Multiply(wvpVpMatrix_, viewportMatrix_);

	return Transform(localPos, wvpVpMatrix_);
}

//=======================================
// 行列の計算
//=======================================

Matrix3x3 Screen::Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = 0.0f;
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}

Vector2 Screen::Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

Matrix3x3 Screen::Inverse(const Matrix3x3& matrix) {

	Matrix3x3 result;
	float det =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] +
		matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] +
		matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] -
		matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] -
		matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	result.m[0][0] = 1.0f / det * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]);
	result.m[0][1] = 1.0f / det * -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]);
	result.m[0][2] = 1.0f / det * (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]);
	result.m[1][0] = 1.0f / det * -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]);
	result.m[1][1] = 1.0f / det * (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]);
	result.m[1][2] = 1.0f / det * -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]);
	result.m[2][0] = 1.0f / det * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);
	result.m[2][1] = 1.0f / det * -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]);
	result.m[2][2] = 1.0f / det * (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);

	return result;
}

//=======================================
// 行列の作成
//=======================================

Matrix3x3 Screen::MakeAffineMatrix(const Vector2& scale, const float& theta, const Vector2& translate) {
	Matrix3x3 W; // = SRT
	W.m[0][0] = scale.x * cosf(theta);
	W.m[0][1] = scale.x * sinf(theta);
	W.m[0][2] = 0.0f;
	W.m[1][0] = -scale.y * sinf(theta);
	W.m[1][1] = scale.y * cosf(theta);
	W.m[1][2] = 0.0f;
	W.m[2][0] = translate.x;
	W.m[2][1] = translate.y;
	W.m[2][2] = 1.0f;

	return W;
}

Matrix3x3 Screen::MakeViewMatrix(const Vector2& cameraPosition) {

	// カメラのワールド行列を求める
	Matrix3x3 cameraWorldMatrix
		= MakeAffineMatrix({ 1,1 }, 0, cameraPosition);

	// 逆行列にする
	return Inverse(cameraWorldMatrix);
}

// 正射影行列
Matrix3x3 Screen::MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom) {
	Matrix3x3 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0.0f;
	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1.0f;
	return result;
}

// ビューポート行列
Matrix3x3 Screen::MakeViewportMatrix(const float& left, const float& top, const float& width, const float& height) {
	Matrix3x3 result;
	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[1][0] = 0.0f;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0.0f;
	result.m[2][0] = left + width / 2.0f;
	result.m[2][1] = top + height / 2.0f;
	result.m[2][2] = 1.0f;
	return result;
}