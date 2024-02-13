#pragma once

#include "../Utility/Vector2D.h"
#include "Barrier.h"
#include "Item.h"

class Player
{
private:
	bool is_active;			//有効状態か？
	int image;				//画像データ
	Vector2D location;		//位置座標
	Vector2D box_size;		//当たり判定の大きさ
	float angle;			//角度
	float speed;			//速さ
	float move_speed;		//画面上で上下左右する時の速さ
	float old_speed;		//ブーストに入る前の速さ
	float hp;				//体力
	float fuel;				//燃料
	int barrier_count;		//バリアの枚数
	Barrier* barrier;		//バリア
	bool boost_flg;			//強制加速のフラグ
	int boost_img;			//強制加速の有効時間
	int boost_time;			//強制加速の有効時間
	int obstruct_time;		//画面阻害の有効時間
public:
	Player();
	~Player();

	void Initialize();		//初期化処理
	void Update();	//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理

public:
	void SetActive(bool flg);		//有効フラグ設定
	void DecreaseHp(float value);	//体力減少処理
	Vector2D GetLocation()const;	//位置座標取得
	Vector2D GetBoxSize()const;		//当たり判定の大きさ取得
	float GetSpeed()const;			//速さ取得処理
	float GetFuel()const;			//燃料取得
	float GetHp()const;				//体力取得
	int GetBarrierCount()const;		//バリアの枚数取得
	bool IsBarrier()const;			//バリア有効か？を取得
	void SetItemPower(Item* item);  //アイテムによって起こる効果の開始
	int GetObstructTime()const;			//画面阻害の時間を取得
private:
	void Movement();				//移動処理
	void Acceleration();			//加速処理
};
