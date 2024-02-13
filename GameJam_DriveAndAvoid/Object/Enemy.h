#pragma once

#include"../Utility/Vector2D.h"

class Enemy
{
private:
	bool death_flg;			//死んでたらtrue
	int type;				//タイプ
	int image;				//画像
	int explosion_image;	//爆死画像
	int explosion_sound;	//爆死画像
	float speed;			//速さ
	Vector2D location;		//位置情報
	Vector2D box_size;		//当たり判定の大きさ
	int wait_timer;			//爆発が終わるまで待つ（プレイヤーに破壊された時）

public:
	Enemy(int type, int handle);
	~Enemy();

	void Initialize();		//初期化処理
	void Update(float speed);	//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理

	int GetType() const;		//タイプ取得
	Vector2D GetLocation() const;	//位置情報の取得
	Vector2D GetBoxSize() const;	//当たり判定の大きさを取得

	bool GetDeathFlg();			//死亡中か取得
	void SetDeathFlg(bool flg);			//死亡中か設定
};
