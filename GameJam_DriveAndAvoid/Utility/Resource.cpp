#include"Resource.h"
#include "DxLib.h"

int Resource::number_image[NUMBER_IMAGE_NUM][10] = {};

void Resource::Initialize()
{
	for (int i = 0; i < NUMBER_IMAGE_NUM; i++)
	{
		LoadAndCheck(number_image_data[i], 10, 10, 1, 20, 30, number_image[i]);
	}
}

int Resource::LoadAndCheck(const char* _data)
{
	int image = LoadGraph(_data);
	int sound = LoadSoundMem(_data);
	//-1が出力されなかった方を返す
	if (image != -1)
	{
		return image;
	}
	else if (sound != -1)
	{
		return sound;
	}
	//どちらも-1ならエラーを返す
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
	//colorが、読み込んだ画像数以上の数字の場合はエラー
	if (NUMBER_IMAGE_NUM <= color)
	{
		throw("数字画像");
	}
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