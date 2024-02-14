#pragma once

#include"SceneBase.h"

class TitleScene : public SceneBase
{
private:

private:
	int timer;			//何フレーム経過したか測定
	int wait;			//入力可能までの時間を測る
	int background_image; //背景画像
	int menu_image; //メニュー画像
	int menu_image_num[4]; //メニュー画像(分割読み込み用)
	int cursor_image; //カーソル画像
	int menu_cursor; //メニューカーソル番号

public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

};