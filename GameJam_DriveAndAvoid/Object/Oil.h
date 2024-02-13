#pragma once

#include"../Utility/Vector2D.h"

class Oil
{
private:
	int oil_image;//�I�C���摜
	int image;				//�摜
	int sounds;
	float speed;			//����
	Vector2D location;		//�ʒu���
	Vector2D box_size;		//�����蔻��̑傫��

public:
	Oil();
	~Oil();

	void Initialize();		//����������
	void Update(float speed);	//�X�V����
	void Draw() const;			//�`�揈��
	void Finalize();			//�I��������

	//int GetType() const;		//�^�C�v�擾
	Vector2D GetLocation() const;	//�ʒu���̎擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫�����擾
};
