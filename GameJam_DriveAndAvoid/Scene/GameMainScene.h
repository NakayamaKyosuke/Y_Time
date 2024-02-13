#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Object/Item.h"

#include "../Object/Oil.h"
//動作確認用
class GameMainScene : public SceneBase
{
private:
	int high_score; //ハイスコア
	int back_ground; //背景画像
	int barrier_image; //バリア画像
	int obstruct_image;		//画面阻害の画像
	int mileage; //走行距離
	int enemy_image[3]; //敵画像
	int enemy_count[3]; //通り過ぎた敵カウント
	Player* player; //プレイヤー
	Enemy** enemy; //敵
	Item** item;   //アイテム（ロケットエンジン、画面阻害）

	Oil* oil;//オイル
public:
	GameMainScene();
	virtual~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;
	
private:
	//ハイスコア読み込み処理
	void ReadHighScore();
	//当たり判定
	bool IsHitCheak(Player* p, Enemy* e);
	//
	bool IsHitCheak(Player* p, Oil* o);
	bool IsHitCheak(Player* p, Item* i);
};