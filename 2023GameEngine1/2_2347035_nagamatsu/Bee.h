#pragma once
#include "Vec2.h"
#include "Rect.h"
class Bee
{
public:
	Bee();
	~Bee();

	void Update();
	void Draw();

	//当たり判定を作る
	void UpdateCollision();

	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }

private:

	int m_handle;

	//歩きアニメーション
	int m_AnimFrame;

	//当たり判定
	Rect m_colRect;

	//プレイヤーの方向
	int m_dir;

	//上限まで行ったか
	bool upperlimit;

	//移動量 1フレーム当たりの移動ベクトルを入れる　　　
	Vec2 m_vec;

	//エネミーの座標
	Vec2 m_pos;

	//歩くモーション
	void MoveMotion();
};

