#pragma once

//2次元ベクトルクラス
class Vector2D
{
public:
	float x;
	float y;

public:
	Vector2D() :x(0.0f), y(0.0f)
	{

	}
	Vector2D(float scaler) :x(scaler), y(scaler)
	{

	}
	Vector2D(float mx, float my) :x(mx), y(my)
	{

	}

public:

};
