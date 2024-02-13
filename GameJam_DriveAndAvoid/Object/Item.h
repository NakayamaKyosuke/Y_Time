#pragma once

#include"../Utility/Vector2D.h"

class Item
{
private:
	int item_type;	//�A�C�e���̎�� 0:���P�b�g�G���W�� 1:��ʑj�Q
	int image;		//�u�[�X�g�摜
	float item_span; //�A�C�e�����ʎ���
	float speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��

public:
	Item();	
	~Item();

	void Initialize();		//����������
	void Update(float speed);	//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I��������

	int GetType();		//�^�C�v�擾
	int GetItemSpan();		//���ʎ��Ԏ擾
	Vector2D GetLocation();	//�ʒu���̎擾
	Vector2D GetBoxSize();	//�����蔻��̑傫�����擾
};