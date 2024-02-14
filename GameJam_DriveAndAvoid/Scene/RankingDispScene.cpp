#include"RankingDispScene.h"
#include"../Utility/inputControl.h"
#include"DxLib.h"

RankingDispScene::RankingDispScene() : background_image(NULL), ranking(nullptr)
{

}

RankingDispScene::~RankingDispScene()
{

}

//初期化処理
void RankingDispScene::Initialize()
{
	//画像の読み込み
	background_image = LoadGraph("Resource/images/ranking.png");

	//エラーチェック
	if (background_image == -1)
	{
		throw("Resource/images/ranking.png");
	}

	//ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();
}

//更新処理
eSceneType RankingDispScene::Update()
{
	//Bボタンが押されたら、タイトルに戻る
	if (InputControl::GetButtonUp(XINPUT_BUTTON_A))
	{
		return eSceneType::E_TITLE;
	}
	return GetNowScene();
}

//描画処理
void RankingDispScene::Draw() const
{
	//背景画像の描画
	DrawGraph(0, 0, background_image, FALSE);
	//文字の大きさ変更
	SetFontSize(40);
	//取得したランキングデータを描画する
	for (int i = 0; i < 5; i++)
	{
		DrawFormatString(0, 160 + i * 59, 0xff00ff, "%2d %-15s %6d",
		ranking->GetRank(i), ranking->GetName(i), ranking->GetScore(i));
	}
	SetFontSize(16);
	DrawString(150, 450, "---- Aボタンを押してタイトルへ戻る ----", 0x000000, 0);
}

//終了時処理
void RankingDispScene::Finalize()
{
	//読み込んだ画像の削除
	DeleteGraph(background_image);

	//動的メモリの解放
	ranking->Finalize();
	delete ranking;
}

//現在のシーン情報を取得
eSceneType RankingDispScene::GetNowScene() const
{
	return eSceneType::E_RANKING_DISP;
}