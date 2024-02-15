#include "Cone.h"
#include "DxLib.h"
#include "Enemy.h"

Cone::Cone() : wait(0), image(NULL)
{
	//画像の読み込み
	image = LoadGraph("Resource/images/cone.png");

	//エラーチェック
	if (image == -1)
	{
		throw("Resource/images/cone.がpngありません\n");
	}
}

Cone::~Cone() 
{
	DeleteGraph(image);
}

void Cone::Initialize()
{
	wait = 240;
	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = 3.0f;
}

void Cone::Update(float speed)
{
	//位置情報に移動量を加算する
	if (--wait < 0)
	{
		location += Vector2D(0.0f, this->speed + speed - 6);
	}
}

void Cone::Draw()const
{
	if (wait > 0)
	{
		DrawRotaGraphF(location.x, 0, 1.0, 0.0, image, TRUE);
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
}

//位置情報を取得
Vector2D Cone::GetLocation()const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Cone::GetBoxSize()const
{
	return box_size;
}