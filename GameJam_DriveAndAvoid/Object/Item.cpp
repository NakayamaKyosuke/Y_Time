#include "Item.h"
#include "DxLib.h"

Item::Item() :image(NULL),speed(0.0f), item_span(0)
{

}

Item::~Item()
{
	//�ǂݍ��񂾉摜���폜
	DeleteGraph(image);
}

//����������
void Item::Initialize()
{
	//�ǂ̃A�C�e��������
	item_type = GetRand(1);

	//�A�C�e���ɉ������摜�ƌ��ʎ���
	switch (item_type)
	{
	case 0:

		//�摜�̓ǂݍ��݁i���摜�j
		image = LoadGraph("Resource/images/seed0.jpg");

		//�G���[�`�F�b�N
		if (image == -1)
		{
			throw("Resource/images/seed0.jpg������܂���\n");
		}
		//���ʎ���
		item_span = 250;
		break;
	case 1:

		//�摜�̓ǂݍ��݁i���摜�j
		image = LoadGraph("Resource/images/flashbang.jpg");

		//�G���[�`�F�b�N
		if (image == -1)
		{
			throw("Resource/images/flashbang.jpg������܂���\n");
		}
		//���ʎ���
		item_span = 300;
		break;
	default:
		throw("���m�̃A�C�e���ł�\n");
	}

	//�o��������X���W�p�^�[�����擾
	float random_x = (float)(GetRand(4) * 105 + 40);
	//�����ʒu�̐ݒ�
	location = Vector2D(random_x, -50.0f);
	//�����蔻��̐ݒ�
	box_size = Vector2D(31.0f, 60.0f);
	//�����̐ݒ�
	speed = 3.0f;
}

void Item::Update(float speed)
{
	//�ʒu���Ɉړ��ʂ����Z����
	location += Vector2D(0.0f, this->speed + speed - 6);
}

//�`�揈��
void Item::Draw() const
{
	DrawRotaGraph(location.x, location.y, 1.0, 0.0, image, TRUE);
}

void Item::Finalize()
{

}

//�A�C�e���̃^�C�v���擾
int Item::GetType()
{
	return item_type;
}

//���ʎ��Ԏ擾
int Item::GetItemSpan()
{
	return item_span;
}

//�ʒu�����擾
Vector2D Item::GetLocation()
{
	return location;
}

//�����蔻��̑傫�����擾
Vector2D Item::GetBoxSize()
{
	return box_size;
}