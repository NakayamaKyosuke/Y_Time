#pragma once

#include "../Utility/Vector2D.h"

class Cone {
private:
	int wait;	//�x���\������
	int draw_timer;	//�x���\���_�ŗp
	int image;
	int danger_image;	//�x���摜
	int danger_se;		//�x��SE
	float speed;
	Vector2D location;
	Vector2D box_size;

public:
	Cone();
	~Cone();

	void Initialize();
	void Update(float speed);
	void Draw() const;

	Vector2D GetLocation() const;	//�ʒu���̎擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫�����擾

};

