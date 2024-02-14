#pragma once

#include "../Utility/Vector2D.h"

class Cone {
private:
	int image;
	float speed;
	Vector2D location;
	Vector2D box_size;

public:
	Cone();
	~Cone();

	void Initialize();
	void Update(float speed);
	void Draw() const;

	int GetType() const;		//�^�C�v�擾
	Vector2D GetLocation() const;	//�ʒu���̎擾
	Vector2D GetBoxSize() const;	//�����蔻��̑傫�����擾

};

