#pragma once

//読込、描画関連のプログラム
class Resource
{
private:
	static int number_imaga[3];	//数字の画像
public:
	static void Initialize();
	static int LoadAndCheck(const char* _data);	 //画像、音声の読込＆エラーチェック
	static void LoadAndCheck(const char* _data,int AllNum, int XNum, int YNum, int XSize, int YSize, int* HandleArray); //分割画像の読込＆エラーチェック
	static void DrawNumber(int draw_num, int color);	//数字を描画する（colorの種類は 0=黒 1=赤 2=白）
};
