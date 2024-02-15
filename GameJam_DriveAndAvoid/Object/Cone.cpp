#include "Cone.h"
#include "DxLib.h"
#include "Enemy.h"

Cone::Cone() : wait(0), image(NULL)
{
	//�摜�̓ǂݍ���
	image = LoadGraph("Resource/images/cone.png");

	//�G���[�`�F�b�N
	if (image == -1)
	{
		throw("Resource/images/cone.��png����܂���\n");
	}
}

Cone::~Cone() 
{
	DeleteGraph(image);
}

void Cone::Initialize()
{
	wait = 240;
	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = 3.0f;
}

void Cone::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
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

//�ʒu�����擾
Vector2D Cone::GetLocation()const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Cone::GetBoxSize()const
{
	return box_size;
}