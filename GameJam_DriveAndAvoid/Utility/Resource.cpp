#include"Resource.h"
#include "DxLib.h"

int Resource::number_imaga[3] = {};

void Resource::Initialize()
{
	number_imaga[0] = LoadAndCheck("Resource/images/D&D_Number.png");
	number_imaga[1] = LoadAndCheck("Resource/images/D&D_Number_Red.png");
	number_imaga[2] = LoadAndCheck("Resource/images/D&D_Number_White.png");
}

int Resource::LoadAndCheck(const char* _data)
{
	int image = LoadGraph(_data);
	int sound = LoadSoundMem(_data);
	//-1���o�͂���Ȃ���������Ԃ�
	if (image != -1)
	{
		return image;
	}
	else if (sound != -1)
	{
		return sound;
	}
	//�ǂ����-1�Ȃ�G���[��Ԃ�
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