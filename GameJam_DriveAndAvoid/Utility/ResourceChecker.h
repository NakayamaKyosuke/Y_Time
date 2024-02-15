#pragma once

class Resource
{
public:
	//画像、音声の読込＆エラーチェック
	static int LoadAndCheck(const char* _data);
	static int LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int   XSize, int   YSize, int* HandleArray);
};
