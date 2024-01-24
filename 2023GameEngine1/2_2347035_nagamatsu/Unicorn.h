#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;

class Unicorn
{
public:
	Unicorn();
	~Unicorn();

	void Update();
	void Draw();
	//当たり判定を作る
	void UpdateCollision();

	//カタツムリの当たり判定を取得する
	Rect GetColRect() const noexcept { return m_colRect; }
	//玉の当たり判定を取得する
	Rect GetBallRect() const noexcept { return m_ballRect; }

private:

	Player* m_pPlayer;

	//ハンドル
	int m_workHandle;
	int m_attackHandle;
	int m_ballHendle;

	//プレイヤーの座標
	Vec2 m_playerPos;

	//プレイヤーの方向
	int m_dir;

	//Unicornの座標
	Vec2 m_pos;
	//Unicorn当たり判定
	Rect m_colRect;

	//移動量
	Vec2 m_vec;

	//玉の座標
	Vec2 m_ballPos;
	//玉の当たり判定
	Rect m_ballRect;

	//玉を発射する
	void shootBall();

	//歩きアニメーション
	int m_AnimFrame;
	//攻撃アニメーション
	int m_AttackAnimFrame;

	

	//歩くモーション
	void workMotion();

	//攻撃モーション
	void attackMotion();

};

