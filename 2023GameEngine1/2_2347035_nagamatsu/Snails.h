#pragma once
#include "Rect.h"
#include "Vec2.h"
class Player;
class Snails
{
public:
	Snails();
	~Snails();

	void Update();

	void Draw();

	void TrackingBall();

	//メンバー変数にアクセスする
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	//カタツムリの当たり判定を取得する
	Rect GetColRect() const noexcept { return m_colRect; }
	//玉の当たり判定を取得する
	Rect GetBallRect() const noexcept { return m_ballRect; }

	//当たり判定を作る
	void UpdateCollision();

	
private:

	int m_handle;

	int m_ballHandle;

	//基準座標 真右方向に移動する基準座標
	   //y成分にsinの値を足して上下に動くようにする
	Vec2 m_pos;

	Player* m_pPlayer;

	//プレイヤーの座標
	Vec2 m_playerPos;
	//プレイヤーの当たり判定
	Rect m_colRect;

	//プレイヤーの方向
	int m_dir;

	//攻撃時のアニメーション
	int m_AnimFrame;

	
	//発射した玉の座標
	Vec2 m_ballPos;
	//玉の当たり判定
	Rect m_ballRect;
	//玉の移動量 1フレーム当たりの移動ベクトルを入れる　　　
	Vec2 m_vec;

	//攻撃時のモーション
	void AttackMotion();

};

