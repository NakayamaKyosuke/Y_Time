#pragma once

#include "../Utility/Vector2D.h"

class Cone {
private:
	int wait;	//警告表示時間
	int image;
	float speed;
	Vector2D location;
	Vector2D box_size;

public:
	Cone();
	~Cone();

	void Initialize();
	void Update(float speed);
	void Draw() const;

	Vector2D GetLocation() const;	//位置情報の取得
	Vector2D GetBoxSize() const;	//当たり判定の大きさを取得

};

