#include"Oil.h"
#include"DxLib.h"

int sounds;
Oil::Oil() : image(NULL), speed(0.0f), location(0.0f), box_size(0.0f)
{
	//�摜�ǂݍ���
	image = LoadGraph("Resource/images/Oil.bmp");
	

	//�G���[�`�F�b�N
	if (image == 1)
	{
		throw("Resource/images/Oil.bmp������܂���\n");
	}
}

Oil::~Oil()
{
	DeleteGraph(image);
}

//����������
void Oil::Initialize()
{
	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = 0.01;
}

void Oil::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

void Oil::Draw()const
{
	//�G�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Oil::Finalize()
{

}


//�ʒu�����擾
Vector2D Oil::GetLocation()const
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Oil::GetBoxSize()const
{
	return box_size;
}