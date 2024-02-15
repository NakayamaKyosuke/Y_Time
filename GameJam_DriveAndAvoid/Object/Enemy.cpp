#include"Enemy.h"
#include"DxLib.h"

Enemy::Enemy(int type, int handle) :death_flg(false),type(type), image(handle), explosion_sound(0), speed(0.0f), location(0.0f), box_size(0.0f), wait_timer(0)
{

}

Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	explosion_image = LoadGraph("Resource/images/explosion.png");

	explosion_sound = LoadSoundMem("Resource/sound/����.mp3");
	//�G���[�`�F�b�N
	if (explosion_image == -1)
	{
		throw ("Resource/images/explosion.png������܂���\n");
	}
	if (explosion_sound == -1)
	{
		throw ("Resource/sound/����.mp3������܂���\n");
	}
	wait_timer = 20;
	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = (float)(this->type * 2);
}

void Enemy::Update(float speed)
{
	//�������Ă���ꍇ�v���C���[�̑��x�Ɋ֌W�Ȃ������Ă���
	if (death_flg == false)
	{
		//�ʒu���Ɉړ��ʂ����Z����
		location += Vector2D(0.0f, this->speed + speed - 6);
	}
	else
	{
		//�ʒu���Ɉړ��ʂ����Z����
		location += Vector2D(0.0f, this->speed + speed);
	}
}

void Enemy::Draw()const
{
	if (death_flg == false)
	{
		//�G�摜�̕`��(�ʏ�)
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
	}
	else
	{
		//�G�摜�̕`��(����)
		DrawRotaGraphF(location.x, location.y, 1.0, 0.0, explosion_image, TRUE);
	}
}

void Enemy::Finalize()
{

}

//�G�̃^�C�v���擾
int Enemy::GetType()const
{
	return type;
}

//�ʒu�����擾
Vector2D Enemy::GetLocation()const
{
	return location;
}

//�����蔻��̑傫�����擾
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
