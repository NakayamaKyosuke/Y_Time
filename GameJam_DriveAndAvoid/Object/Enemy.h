#pragma once

#include"../Utility/Vector2D.h"

class Enemy
{
private:
	bool death_flg;			//����ł���true
	int type;				//�^�C�v
	int image;				//�摜
	int explosion_image;	//�����摜
	int explosion_sound;	//�����摜
	float speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��
	int wait_timer;			//�������I���܂ő҂i�v���C���[�ɔj�󂳂ꂽ���j

public:
	Enemy(int type, int handle);
	~Enemy();

	void Initialize();		//����������
	void Update(float speed);	//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I��������

	int GetType() const;		//�^�C�v�擾
	Vector2D GetLocation() const;	//�ʒu���̎擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫�����擾

	bool GetDeathFlg();			//���S�����擾
	void SetDeathFlg(bool flg);			//���S�����ݒ�
};
