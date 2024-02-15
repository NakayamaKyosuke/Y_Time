#pragma once

#include"../Utility/Vector2D.h"

class Oil
{
private:
	int wait;	//�x���\������
	int draw_timer;	//�x���\���_�ŗp
	int image;				//�摜
	int danger_image;		//�x���摜
	int danger_se;			//�x��SE
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

	
	Vector2D GetLocation() const;	//�ʒu���̎擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫�����擾
};
