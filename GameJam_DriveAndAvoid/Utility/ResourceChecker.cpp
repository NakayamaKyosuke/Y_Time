#include"ResourceChecker.h"
#include "DxLib.h"

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