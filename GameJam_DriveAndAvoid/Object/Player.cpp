#include"Player.h"
#include "../Utility/inputControl.h"
#include"DxLib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f), angle(0.0f), speed(0.0f), old_speed(0.0f), move_speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0), barrier(nullptr), boost_img(NULL),boost_flg(false), boost_time(0.0f), obstruct_time(0.0f)
{

}

Player::~Player()
{

}

//����������
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

	//�摜�̓Ǎ�
	image = LoadGraph("Resource/images/car1pol.bmp");
	boost_img = LoadGraph("Resource/images/seed1.jpg");


	//�����ǂݍ���
	sounds = LoadSoundMem("Resource/sound/carcheice.mp3");
	

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw ("Resource/images/car1pol.bmp������܂���\n");
	}
	if (boost_img == -1)
	{
		throw ("Resource/images/seed1.jpg������܂���\n");
	}

	if (sounds == -1)
	{
		throw ("Resource/sounds/carcheice.mp3������܂���\n");
	}
	
}

void Player::Update()
{
	//�����u�[�X�g����
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
	//��ʑj�Q����
	if (obstruct_time > 0)
	{
		obstruct_time -= 2.0f;
	}
	//����s��Ԃł���΁A���M����]������
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

	//�R���̏���
	fuel -= speed;
	fuel -= move_speed - 1;

	//�ړ�����
	Movement();

	//�����x����
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}

	//������
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		PlaySoundMem(sounds, DX_PLAYTYPE_BACK);
	}
	if (InputControl::GetButtonUp(XINPUT_BUTTON_X))
	{
		StopSoundMem(sounds);
	}
	//�o���A����
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}
	//�o���A����������Ă�����A�X�V���s��
	if (barrier != nullptr)
	{
		//�o���A���Ԃ��o�߂������H���Ă�����A�폜����
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;
		}
	}
	//�����u�[�X�g���͐���s�\
	if (boost_time <= 0)
	{
		//�u�[�X�g����
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
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	//�o���A���������ꂽ������A�`����s��
	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}

	//�������x�A�b�v�̍ŏ��̕����Ŏ튄��
	if (boost_time > 200)
	{
		DrawRotaGraphF(location.x, location.y-100, 1.0, angle, boost_img, TRUE);
	}
}

void Player::Finalize()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);

	//�o���A����������Ă�����A�폜����
	if (barrier != nullptr)
	{
		delete barrier;
	}
}

//��Ԑݒ菈��
void Player::SetActive(bool flg)
{
	this->is_active = flg;
}

//�̗͌�������
void Player::DecreaseHp(float value)
{
	this->hp += value;
}

//�ʒu���擾����
Vector2D Player::GetLocation()const
{
	return this->location;
}

//�ʒu���擾����
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}

//�����擾����
float Player::GetSpeed()const
{
	return this->speed;
}

//�R���擾����
float Player::GetFuel()const
{
	return this->fuel;
}

//�̗͎擾����
float Player::GetHp()const
{
	return this->hp;
}

//�o���A�����擾����
int Player::GetBarrierCount()const
{
	return this->barrier_count;
}

//�o���A�L�����H���擾
bool Player::IsBarrier()const
{
	return (barrier != nullptr);
}

//�A�C�e���ɂ���ċN������ʂ̊J�n
void Player::SetItemPower(Item* item)
{
	switch (item->GetType())
	{
	case 0:
		if (boost_flg == false)
		{
			//���������O�̑��x��ێ�
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

//��ʑj�Q�̎��Ԃ��擾
int Player::GetObstructTime()const
{
	return obstruct_time;
}

//�ړ�����
void Player::Movement()
{
	Vector2D move = Vector2D(0.0f);
	angle = 0.0f;

	//�\���ړ�����
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

	//��ʊO�ɍs���Ȃ��悤�ɐ�������
	if ((location.x < box_size.x) ||
		(location.x >= 640.0f - 180.0f) ||
		(location.y < box_size.y) ||
		(location.y >= 480.0f - box_size.y)
		)
	{
		location -= move;
	}
}

//����������
void Player::Acceleration()
{
	//�����������łȂ��Ȃ�A���x�����ł���
	if (boost_flg == false)
	{
		//LB�{�^���������ꂽ��A��������
		if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 3.0f)
		{
			speed -= 1.0f;
		}
		//RB�{�^���������ꂽ��A��������
		if (InputControl::GetButtonDown(XINPUT_BUTTON_RIGHT_SHOULDER) && speed < 10.0f)
		{
			speed += 1.0f;
		}
	}
}
