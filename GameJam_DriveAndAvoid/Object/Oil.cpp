#include"Oil.h"
#include"../Utility/Resource.h"
#include"DxLib.h"

int sounds;
Oil::Oil() : wait(0), draw_timer(0), image(NULL), speed(0.0f), location(0.0f), box_size(0.0f), danger_image(NULL), danger_se(NULL)
{
	
}

Oil::~Oil()
{
	DeleteGraph(image);
}

//初期化処理
void Oil::Initialize()
{
	//画像読み込み
	image = Resource::LoadAndCheck("Resource/images/Oil.bmp");
	danger_image = Resource::LoadAndCheck("Resource/images/danger.png");
	danger_se = Resource::LoadAndCheck("Resource/sound/警告音1.mp3");
	PlaySoundMem(danger_se, DX_PLAYTYPE_BACK);

	wait = 60;
	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = 5.0f;
}

void Oil::Update(float speed)
{
	//点滅用
	if (draw_timer++ > 14)
	{
		draw_timer = 0;
	}
	//位置情報に移動量を加算する
	if (--wait < 0)
	{
		location += Vector2D(0.0f, this->speed + speed);
	}
}

void Oil::Draw()const
{
	if (wait > 0)
	{
		if (draw_timer > 7)
		{
			DrawRotaGraphF(location.x, 32, 1.0, 0.0, danger_image, TRUE);
		}
	}
	else
	{
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
}

void Oil::Finalize()
{

}


//位置情報を取得
Vector2D Oil::GetLocation()const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Oil::GetBoxSize()const
{
	return box_size;
}