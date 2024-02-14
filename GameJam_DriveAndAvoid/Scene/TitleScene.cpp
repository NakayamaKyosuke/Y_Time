#include"TitleScene.h"
#include"../Utility/inputControl.h"
#include"../Utility/ResourceChecker.h"
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

TitleScene::TitleScene() : wait(0),timer(0), titlemenu_image(NULL), menu_image_num{0}, cursor_image(NULL), menu_cursor(0), cursor_sound(0), enter_sound(0)
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
	background_image = Resource::LoadAndCheck("Resource/images/title/D&D_Title.jpg");
	titlemenu_image = LoadGraph("Resource/images/title/D&D_TitleMenu.jpg");
	menupole_image = LoadGraph("Resource/images/title/D&D_MenuPole.jpg");
	cursor_image = LoadGraph("Resource/images/cone.bmp");

	cursor_sound = LoadSoundMem("Resource/sound/カーソル移動8.mp3");
	enter_sound = LoadSoundMem("Resource/sound/爆発.mp3");

	//エラーチェック
	if (LoadDivGraph("Resource/images/title/D&D_Menu2.jpg", MENU_NUM, 1, MENU_NUM, 185, 40, menu_image_num) == -1)
	{
		throw("Resource/images/title/D&D_Menu2.jpgの読込に失敗しました。\n");
	}
	if (titlemenu_image == -1)
	{
		throw("Resource/images/title/D&D_TitleMenu.jpgがありません\n");
	}
	if (menupole_image == -1)
	{
		throw("Resource/images/title/D&D_MenuPole.jpgがありません\n");
	}
	if (cursor_image == -1)
	{
		throw("Resource/images/cone.pngがありません\n");
	}
	if (cursor_sound == -1)
	{
		throw("Resource/sound/カーソル移動8.mp3がありません\n");
	}
	if (enter_sound == -1)
	{
		throw("Resource/sound/爆発.mp3がありません\n");
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
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
			menu_cursor++;
			//一番下に到達したら、一番上にする
			if (menu_cursor > MENU_NUM-1)
			{
				menu_cursor = 0;
			}
		}

		//カーソル上移動
		if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
		{
			PlaySoundMem(cursor_sound, DX_PLAYTYPE_BACK);
			menu_cursor--;
			//一番上に到達したら、一番下にする
			if (menu_cursor < 0)
			{
				menu_cursor = MENU_NUM-1;
			}
		}

		//カーソル決定の音だけ先に鳴らす
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			PlaySoundMem(enter_sound, DX_PLAYTYPE_BACK);
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
				return eSceneType::E_CREDIT;
			case 4:
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
	DrawGraph(180, 255, menupole_image, TRUE);
	DrawGraph(60, 175, titlemenu_image, FALSE);

	//メニュー画像の描画
	for (int i = 0; i < MENU_NUM; i++)
	{
		if (i == menu_cursor && InputControl::GetButton(XINPUT_BUTTON_B) == false)
		{
			DrawRotaGraph(230, 220 + i * 40, 1.2, 0, menu_image_num[i], FALSE);
		}
		else
		{
			DrawRotaGraph(230, 220 + i * 40, 1.0, 0, menu_image_num[i], FALSE);
		}
	}

	//カーソル画像の描画
	DrawRotaGraph(100+2*cosf(2*(timer/5)+M_PI/3), 220 + menu_cursor * 40, 0.7, DX_PI / 2.0, cursor_image, TRUE);
}

//終了時処理
void TitleScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
	DeleteGraph(titlemenu_image);
	DeleteGraph(menupole_image);
	DeleteGraph(cursor_image);
	
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}