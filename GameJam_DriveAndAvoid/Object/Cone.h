#pragma once

#include "../Utility/Vector2D.h"

class Cone {
private:
	int wait;	//x\¦Ô
	int draw_timer;	//x\¦_Åp
	int image;
	int danger_image;	//xæ
	int danger_se;		//xSE
	float speed;
	Vector2D location;
	Vector2D box_size;

public:
	Cone();
	~Cone();

	void Initialize();
	void Update(float speed);
	void Draw() const;

	Vector2D GetLocation() const;	//ÊuîñÌæ¾
	Vector2D GetBoxSize() const;	//½è»èÌå«³ðæ¾

};

