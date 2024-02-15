#include"Resource.h"
#include "DxLib.h"

int Resource::number_image[3][10] = {};

void Resource::Initialize()
{
	LoadAndCheck("Resource/images/D&D_Number.png", 10, 10, 1, 20, 30, number_image[0]);
	LoadAndCheck("Resource/images/D&D_Number_Red.png", 10, 10, 1, 20, 30, number_image[1]);
	LoadAndCheck("Resource/images/D&D_Number_White.png", 10, 10, 1, 20, 30, number_image[2]);
}

int Resource::LoadAndCheck(const char* _data)
{
	int image = LoadGraph(_data);
	int sound = LoadSoundMem(_data);
	//-1‚ªo—Í‚³‚ê‚È‚©‚Á‚½•û‚ð•Ô‚·
	if (image != -1)
	{
		return image;
	}
	else if (sound != -1)
	{
		return sound;
	}
	//‚Ç‚¿‚ç‚à-1‚È‚çƒGƒ‰[‚ð•Ô‚·
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

void Resource::DrawNumber(Vector2D location,int draw_num, int size, float font_size,int color)
{
	int a;
	int value = draw_num;
	for (int i = size; i > 0; i--)
	{
		a = value % 10;
		value /= 10;
		//DrawFormatString(x, y + (i * 20), 0x00ff00, "%d", j);
		DrawRotaGraph(location.x + (i * (font_size*10)), location.y, font_size,0,number_image[color][a], TRUE);
	}
}