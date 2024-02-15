#pragma once
#include"Vector2D.h"

//読込、描画関連のプログラム
class Resource
{
private:
	static int number_image[3][10];	//数字の画像
public:
	static void Initialize();
	static int LoadAndCheck(const char* _data);	 //画像、音声の読込＆エラーチェック
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //分割画像の読込＆エラーチェック
	static void DrawNumber(Vector2D location,int draw_num, int size, float font_size, int color);	//数字を描画する(location:描画位置, draw_num:描画する数字, size:何桁か(右詰め), font_size:フォントのサイズ, color:0=黒 1=赤 2=白)
};
