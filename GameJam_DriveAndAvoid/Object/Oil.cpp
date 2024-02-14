#include"Oil.h"
#include"DxLib.h"

int sounds;
Oil::Oil() : image(NULL), speed(0.0f), location(0.0f), box_size(0.0f)
{
	//画像読み込み
	image = LoadGraph("Resource/images/Oil.bmp");
	

	//エラーチェック
	if (image == 1)
	{
		throw("Resource/images/Oil.bmpがありません\n");
	}
}

Oil::~Oil()
{
	DeleteGraph(image);
}

//初期化処理
void Oil::Initialize()
{
	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = 0.01;
}

void Oil::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Oil::Draw()const
{
	//敵画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
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