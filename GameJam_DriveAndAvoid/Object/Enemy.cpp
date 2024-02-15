#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle) :death_flg(false),type(type), image(handle), explosion_sound(0), speed(0.0f), location(0.0f), box_size(0.0f), wait_timer(0)
{

}

Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	explosion_image = LoadGraph("Resource/images/explosion.png");

	explosion_sound = LoadSoundMem("Resource/sound/爆発.mp3");
	//エラーチェック
	if (explosion_image == -1)
	{
		throw ("Resource/images/explosion.pngがありません\n");
	}
	if (explosion_sound == -1)
	{
		throw ("Resource/sound/爆発.mp3がありません\n");
	}
	wait_timer = 20;
	//出現させるX座標パターンを取得
	float random_x = (float)(GetRand(4) * 105 + 40);
	//生成位置の設定
	location = Vector2D(random_x, -50.0f);
	//当たり判定の設定
	box_size = Vector2D(31.0f, 60.0f);
	//速さの設定
	speed = (float)(this->type * 2);
}

void Enemy::Update(float speed)
{
	//爆発している場合プレイヤーの速度に関係なく落ちていく
	if (death_flg == false)
	{
		//位置情報に移動量を加算する
		location += Vector2D(0.0f, this->speed + speed - 6);
	}
	else
	{
		//位置情報に移動量を加算する
		location += Vector2D(0.0f, this->speed + speed);
	}
}

void Enemy::Draw()const
{
	if (death_flg == false)
	{
		//敵画像の描画(通常)
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
	else
	{
		//敵画像の描画(爆死)
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, explosion_image, TRUE);
	}
}

void Enemy::Finalize()
{

}

//敵のタイプを取得
int Enemy::GetType()const
{
	return type;
}

//位置情報を取得
Vector2D Enemy::GetLocation()const
{
	return location;
}

//当たり判定の大きさを取得
Vector2D Enemy::GetBoxSize()const
{
	return box_size;
}

bool Enemy::GetDeathFlg()
{
	return death_flg;
}
void Enemy::SetDeathFlg(bool flg)
{
	death_flg = flg;
	if (death_flg == true)
	{
		PlaySoundMem(explosion_sound, DX_PLAYTYPE_BACK);
	}
}
