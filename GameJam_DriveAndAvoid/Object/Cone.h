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

	Vector2D GetLocation() const;	//ˆÊ’uî•ñ‚Ìæ“¾
	Vector2D GetBoxSize() const;	//“–‚½‚è”»’è‚Ì‘å‚«‚³‚ğæ“¾

};

