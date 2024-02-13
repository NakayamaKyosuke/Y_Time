#pragma once

#include"../Utility/Vector2D.h"

class Item
{
private:
	int item_type;	//アイテムの種類 0:ロケットエンジン 1:画面阻害
	int image;		//ブースト画像
	float item_span; //アイテム効果時間
	float speed;			//速さ
	Vector2D location;		//位置情報
	Vector2D box_size;		//当たり判定の大きさ

public:
	Item();	
	~Item();

	void Initialize();		//初期化処理
	void Update(float speed);	//更新処理
	void Draw() const;			//描画処理
	void Finalize();			//終了時処理

	int GetType();		//タイプ取得
	int GetItemSpan();		//効果時間取得
	Vector2D GetLocation();	//位置情報の取得
	Vector2D GetBoxSize();	//当たり判定の大きさを取得
};