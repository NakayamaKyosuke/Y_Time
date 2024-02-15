#include"Credit.h"
#include"Utility/inputControl.h"
#include"Utility/Resource.h"
#include"DxLib.h"

CreditScene::CreditScene() : background_image(NULL)
{

}

CreditScene::~CreditScene()
{

}

//初期化処理
void CreditScene::Initialize()
{
	//画像の読み込み
	background_image = Resource::LoadAndCheck("Resource/images/credit.jpg");

	
}

//更新処理
eSceneType CreditScene::Update()
{
	//Aボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonUp(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

//描画処理
void CreditScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);

	//ゲーム説明
	SetFontSize(60);
	SetFontThickness(9);
	ChangeFont("ＭＳ 明朝");
	DrawString(170, 0, "クレジット", 0x000000, 0);
	SetFontSize(50);
	DrawString(200, 110, "効果音ラボ", 0x000000, 0);
	DrawString(130, 170, "ポケットサウンド", 0x000000, 0);
	DrawString(200, 230, "いらすとや", 0x000000, 0);
	DrawString(230, 280, "photoAC", 0x000000, 0);
	DrawString(170, 330, "海外系効果音", 0x000000, 0);
	DrawString(240, 380, "魔王魂", 0x000000, 0);
	SetFontSize(16);
	DrawString(150, 450, "---- Aボタンを押してタイトルへ戻る ----", 0x000000, 0);
}

//終了時処理
void CreditScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);
}

//現在のシーン情報を取得
eSceneType CreditScene::GetNowScene() const
{
	return eSceneType::E_CREDIT;
}