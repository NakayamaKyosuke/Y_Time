#include"Player.h"
#include "../Utility/inputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f), speed(0.0f), old_speed(0.0f), move_speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr), boost_img(NULL),boost_flg(false), boost_time(0.0f), obstruct_time(0.0f)
{

}

Player::~Player()
{

}

//初期化処理
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	move_speed = 1.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;

	//画像の読込
	image = LoadGraph("Resource/images/car1pol.bmp");
	boost_img = LoadGraph("Resource/images/seed1.jpg");


	//音源読み込み
	sounds = LoadSoundMem("Resource/sound/carcheice.mp3");
	

	//エラーチェック
	if (image == -1)
	{
		throw ("Resource/images/car1pol.bmpがありません\n");
	}
	if (boost_img == -1)
	{
		throw ("Resource/images/seed1.jpgがありません\n");
	}

	if (sounds == -1)
	{
		throw ("Resource/sounds/carcheice.mp3がありません\n");
	}
	
}

void Player::Update()
{
	//強制ブースト処理
	if (--boost_time <= 0 && boost_flg == true)
	{
		boost_flg = false;
		speed = old_speed;
	}
	if (boost_flg == true)
	{
		move_speed = 10.0f;
		speed = 10.0f;
	}
	//画面阻害処理
	if (obstruct_time > 0)
	{
		obstruct_time -= 2.0f;
	}
	//操作不可状態であれば、自信を回転させる
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}

	//燃料の消費
	fuel -= speed;
	fuel -= move_speed - 1;

	//移動処理
	Movement();

	//加速度処理
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//加速音
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		PlaySoundMem(sounds, DX_PLAYTYPE_BACK);
	}
	if (InputControl::GetButtonUp(XINPUT_BUTTON_X))
	{
		StopSoundMem(sounds);
	}
	//バリア処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}
	//バリアが生成されていたら、更新を行う
	if (barrier != nullptr)
	{
		//バリア時間が経過したか？していたら、削除する
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
	//強制ブースト中は制御不能
	if (boost_time <= 0)
	{
		//ブースト処理
		if (InputControl::GetButton(XINPUT_BUTTON_X))
		{
			move_speed = 3.0f;
		}
		else
		{
			move_speed = 1.0f;
		}
	}
}

void Player::Draw()const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//バリアが生成されたいたら、描画を行う
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	//強制速度アップの最初の部分で種割れ
	if (boost_time > 200)
	{
		DrawRotaGraphF(location.x, location.y-100, 1.0, angle, boost_img, TRUE);
	}
}

void Player::Finalize()
{
	//読み込んだ画像を削除
	DeleteGraph(image);

	//バリアが生成されていたら、削除する
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//状態設定処理
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//体力減少処理
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//位置情報取得処理
Vector2D Player::GetLocation()const
{
	return this->location;
}

//位置情報取得処理
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//速さ取得処理
float Player::GetSpeed()const
{
	return this->speed;
}

//燃料取得処理
float Player::GetFuel()const
{
	return this->fuel;
}

//体力取得処理
float Player::GetHp()const
{
	return this->hp;
}

//バリア枚数取得処理
int Player::GetBarrierCount()const
{
	return this->barrier_count;
}

//バリア有効か？を取得
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}

//アイテムによって起こる効果の開始
void Player::SetItemPower(Item* item)
{
	switch (item->GetType())
	{
	case 0:
		if (boost_flg == false)
		{
			//強制加速前の速度を保持
			old_speed = speed;
		}
		boost_flg = true;
		boost_time = item->GetItemSpan();
		break;
	case 1:
		obstruct_time = item->GetItemSpan();
		break;
	default:
		break;
	}
}

//画面阻害の時間を取得
int Player::GetObstructTime()const
{
	return obstruct_time;
}

//移動処理
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//十字移動処理
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		move += Vector2D(-move_speed, 0.0f);
		angle = -DX_PI_F / (16 - move_speed*3);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		move += Vector2D(move_speed, 0.0f);
		angle = DX_PI_F / (16 - move_speed*3);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		move += Vector2D(0.0f, -move_speed);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		move += Vector2D(0.0f, move_speed);
	}
	location += move;

	//画面外に行かないように制限する
	if ((location.x < box_size.x) ||
		(location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) ||
		(location.y >= 480.0f - box_size.y)
		)
	{
		location -= move;
	}
}

//加減速処理
void Player::Acceleration()
{
	//強制加速中でないなら、速度調整できる
	if (boost_flg == false)
	{
		//LBボタンが押されたら、減速する
		if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 3.0f)
		{
			speed -= 1.0f;
		}
		//RBボタンが押されたら、減速する
		if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
		{
			speed += 1.0f;
		}
	}
}
