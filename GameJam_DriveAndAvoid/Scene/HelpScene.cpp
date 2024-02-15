#include"HelpScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"
#include"../Utility/Resource.h"

HelpScene::HelpScene() : background_image(NULL)
{

}

HelpScene::~HelpScene()
{

}

//初期化処理
void HelpScene::Initialize()
{
	//画像の読み込み
	background_image = Resource::LoadAndCheck("Resource/images/help.png");

}

//更新処理
eSceneType HelpScene::Update()
{
	//Aボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonUp(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void HelpScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(16);
	DrawString(130, 460, "Aボタンを押してタイトルへ戻る",0xff0000, 0);
}

//終了時処理
void HelpScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}