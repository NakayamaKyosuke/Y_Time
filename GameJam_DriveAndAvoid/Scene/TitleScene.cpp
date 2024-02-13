#include"TitleScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

TitleScene::TitleScene() : wait(0),timer(0),background_image(NULL), menu_image(NULL), menu_image_num{0}, cursor_image(NULL), menu_cursor(0)
{

}

TitleScene::~TitleScene()
{

}

//初期化処理
void TitleScene::Initialize()
{
	wait = 20;
	//画像の読み込み
	background_image = LoadGraph("Resource/images/Title.bmp");
	menu_image = LoadGraph("Resource/images/menu.bmp");
	cursor_image = LoadGraph("Resource/images/cone.bmp");
	if (LoadDivGraph("Resource/images/menu.bmp", 4, 1, 4, 195, 40, menu_image_num) == -1)
	{
		throw("Resource/images/menu.bmpの読込に失敗しました。\n");
	}

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/Title.bmpがありません\n");
	}
	if (menu_image == -1)
	{
		throw("Resource/images/menu.bmpがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.bmpがありません\n");
	}
}

//更新処理
eSceneType TitleScene::Update()
{
	//時間測定
	timer++;
	//一定時間入力を受け付けない(誤入力防止)
	if (--wait <= 0)
	{
		wait = 0;
		//カーソル下移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
		{
			menu_cursor++;
			//一番下に到達したら、一番上にする
			if (menu_cursor > 3)
			{
				menu_cursor = 0;
			}
		}

		//カーソル上移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		{
			menu_cursor--;
			//一番上に到達したら、一番下にする
			if (menu_cursor < 0)
			{
				menu_cursor = 3;
			}
		}

		//カーソル決定（決定した画面に遷移する）
		if (InputControl::GetButtonUp(XINPUT_BUTTON_B))
		{
			switch (menu_cursor)
			{
			case 0:
				return eSceneType::E_MAIN;
			case 1:
				return eSceneType::E_RANKING_DISP;
			case 2:
				return eSceneType::E_HELP;
			case 3:
				return eSceneType::E_END;
			}
		}

	}
	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	//タイトル画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//メニュー画像の描画
	for (int i = 0; i < 4; i++)
	{
		if (i == menu_cursor && InputControl::GetButton(XINPUT_BUTTON_B) == false)
		{
			DrawRotaGraph(230, 220 + i * 40, 1.2, 0, menu_image_num[i], TRUE);
		}
		else
		{
			DrawRotaGraph(230, 220 + i * 40, 1.0, 0, menu_image_num[i], TRUE);
		}
	}

	//カーソル画像の描画
	DrawRotaGraph(90+2*cosf(2*(timer/5)+M_PI/3), 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(menu_image);
	DeleteGraph(cursor_image);
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}