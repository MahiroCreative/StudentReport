#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Player.h"

class Flyingeye
{
public:
	Flyingeye();
	~Flyingeye();

	void Init();
	void Update();
	void Draw();
	void start();

	//当たり判定を作る
	void UpdateCollision();

	//メンバー変数にアクセスする
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }
	//生きているかどうか
	bool isExist() const { return m_isExist; }

private:

	Player* m_pPlayer;
	
	//ハンドル
	int m_handle;

	//歩きアニメーション
	int m_AnimFrame;

	//当たり判定
	Rect m_colRect;

	//プレイヤーの方向
	int m_dir;

	//移動量 1フレーム当たりの移動ベクトルを入れる　　　
	Vec2 m_vec;

	//エネミーの座標
	Vec2 m_pos;

	//地面についたか
	bool m_isGround;

	//存在しているかどうか
	bool m_isExist;

	//歩くモーション
	void MoveMotion();
};

