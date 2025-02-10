#pragma once

struct Vector2 {
	float x;
	float y;

	// 二次元ベクトル同士の四則演算を可能にする
	void operator+=(const Vector2& vec);
	void operator-=(const Vector2& vec);
	void operator*=(const Vector2& vec);
	void operator/=(const Vector2& vec);

	Vector2 operator+(const Vector2& vec);
	Vector2 operator-(const Vector2& vec);
	Vector2 operator*(const Vector2& vec);
	Vector2 operator/(const Vector2& vec);

	// ベクトルx,y両方をスカラーで掛ける割る
	void operator*=(const float& scalar);
	void operator/=(const float& scalar);
};