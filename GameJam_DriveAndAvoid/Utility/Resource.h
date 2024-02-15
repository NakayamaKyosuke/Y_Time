#pragma once

//読込、描画関連のプログラム
class Resource
{
public:
	static int LoadAndCheck(const char* _data);	 //画像、音声の読込＆エラーチェック
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //分割画像の読込＆エラーチェック
};
