#include"Resource.h"
#include "DxLib.h"

int Resource::number_imaga[3][10] = {};

void Resource::Initialize()
{
	LoadAndCheck("Resource/images/D&D_Number.png", 10, 10, 1, 20, 30, number_imaga[0]);
	LoadAndCheck("Resource/images/D&D_Number_Red.png", 10, 10, 1, 20, 30, number_imaga[1]);
	LoadAndCheck("Resource/images/D&D_Number_White.png", 10, 10, 1, 20, 30, number_imaga[2]);
}

int Resource::LoadAndCheck(const char* _data)
{
	int image = LoadGraph(_data);
	int sound = LoadSoundMem(_data);
	//-1‚ªo—Í‚³‚ê‚È‚©‚Á‚½•û‚ğ•Ô‚·
	if (image != -1)
	{
		return image;
	}
	else if (sound != -1)
	{
		return sound;
	}
	//‚Ç‚¿‚ç‚à-1‚È‚çƒGƒ‰[‚ğ•Ô‚·
	else
	{
		throw(_data);
	}
}

void Resource::LoadAndCheck(const char* _data, int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray)
{
	if (LoadDivGraph(_data, AllNum, XNum, YNum, XSize, YSize, HandleArray) == -1)
	{
		throw(_data);
	}
}

void Resource::DrawNumber(Vector2D location,int draw_num, int color)
{
	switch (color)
	{
	case 0:
		
		break;
	case 1:

		break;
	case 2:

		break;
	default:
		break;
	}
}