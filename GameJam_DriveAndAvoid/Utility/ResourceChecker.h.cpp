#include"ResourceChecker.h"
#include "DxLib.h"

//画像、音声の読込＆エラーチェック
int Resource::LoadAndCheck(const char* _data)
{
	int resource;
	if (LoadGraph(_data) != -1)
	{
		return LoadGraph(_data);
	}
	else if (LoadSoundMem(_data) != -1)
	{
		return LoadSoundMem(_data);
	}
	else
	{
		throw(_data);
	}
}