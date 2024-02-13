#include "Item.h"
#include "DxLib.h"

Item::Item() :image(NULL),speed(0.0f), item_span(0)
{

}

Item::~Item()
{
	//読み込んだ画像を削除
	DeleteGraph(image);
}

//初期化処理
void Item::Initialize()
{
	//どのアイテムか決定
	item_type = GetRand(1);

	//アイテムに応じた画像と効果時間
	switch (item_type)
	{
	case 0:

		//画像の読み込み（仮画像）
		image = LoadGraph("Resource/images/seed0.jpg");

		//エラーチェック
		if (image == -1)
		{
			throw("Resource/images/seed0.jpgがありません\n");
		}
		//効果時間
		item_span = 250;
		break;
	case 1:

		//画像の読み込み（仮画像）
		image = LoadGraph("Resource/images/flashbang.jpg");

		//エラーチェック
		if (image == -1)
		{
			throw("Resource/images/flashbang.jpgがありません\n");
		}
		//効果時間
		item_span = 300;
		break;
	default:
		throw("未知のアイテムです\n");
	}

	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = 3.0f;
}

void Item::Update(float speed)
{
	//位置情報に移動量を加算する
	location += Vector2D(0.0f, this->speed + speed - 6);
}

//描画処理
void Item::Draw() const
{
	DrawRotaGraph(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Item::Finalize()
{

}

//アイテムのタイプを取得
int Item::GetType()
{
	return item_type;
}

//効果時間取得
int Item::GetItemSpan()
{
	return item_span;
}

//位置情報を取得
Vector2D Item::GetLocation()
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Item::GetBoxSize()
{
	return box_size;
}