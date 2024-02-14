#pragma once

class Resource
{
public:
	//画像、音声の読込＆エラーチェック
	static int LoadAndCheck(const char* _data);
};
