#pragma once
#include "Matrix.h"
#include "Vector2.h"
class Screen{
public:

	Screen();

	// ワールド座標系からスクリーン座標系に変換
	Vector2 ScreenTransform(const Vector2 &worldPos);
	
	/// <summary>
	/// ローカル座標系からスクリーン座標系に変換
	/// </summary>
	/// <param name="localPos">ローカル座標(中心から見た頂点座標など)</param>
	/// /// <param name="scale">拡大縮小</param>
	/// <param name="theta">回転</param>
	/// <param name="worldPos">ワールド座標(中心座標など)</param>
	Vector2 ScreenTransform(const Vector2 localPos, const Vector2 scale, const float theta, const Vector2& worldPos);
	
	// シェイクの設定
	void Shake(const Vector2& amplitude);
private:

	// 行列の計算
	Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2); // 積
	Vector2 Transform(Vector2 vector, Matrix3x3 matrix); // ベクトルx行列
	Matrix3x3 Inverse(const Matrix3x3& matrix); // 逆行列

	// 行列の作成
	Matrix3x3 MakeAffineMatrix(const Vector2& scale, const float& theta, const Vector2& translate);
	Matrix3x3 MakeViewMatrix(const Vector2& cameraPosition);
	Matrix3x3 MakeOrthographicMatrix(const float& left, const float& top, const float& right, const float& bottom);
	Matrix3x3 MakeViewportMatrix(const float &left, const float &top, const float &width, const float &height);

	// 行列
	Matrix3x3 worldMatrix_ = { 0 };
	Matrix3x3 wvpVpMatrix_ = { 0 };
	Matrix3x3 viewMatrix_ = { 0 };
	Matrix3x3 orthographicMatrix_ = { 0 };
	Matrix3x3 viewportMatrix_ = { 0 };

	// 画面
	Vector2 cameraPos_;
	float width_;
	float height_;
	Vector2 shake_;
};

