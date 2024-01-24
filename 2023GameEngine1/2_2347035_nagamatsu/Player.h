#pragma once
#include"Vec2.h"
#include"Rect.h"
#include "Spear.h"
#include "SceneGameOver.h"

class Map;
class Player
{
	//向いている方向
	enum Dir
	{
		kDirRight, //右　＝0
		kDirLeft, //左　＝1
	};

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();
	void Attack();

	// マップのポインタを設定する
	void SetMap(Map* pMap) { m_pMap = pMap; }

	//プレイヤーの現在位置を取得する
	Vec2 GetPos() const { return m_pos; }

	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const noexcept { return m_colRect;}

	//槍の当たり判定取得する
	Rect GetSpearRect() const noexcept { return m_SpearRect;}

	//プレイヤーのHpを取得する
	int GetHp() const noexcept { return m_Hp; }

	// プレイヤーの上下左右座標を取得
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	//敵に当たった時の処理
	void OnDamege();
private:

	Spear* m_pSpear;
	SceneGameOver* m_pSceneGameOver;

	Map* m_pMap;

	//プレイヤーが歩く時のハンドル
	int m_Runhandle;
	//プレイヤーが止まっているときのハンドル
	int m_Waitinghandle;
	//プレイヤーがジャンプするときのハンドル
	int m_Jumphamdle;
	//プレイヤーが死亡時のハンドル
	int m_Deadhandle;
	// 移動し始めてから何フレーム経過したかを保持する変数
	int MoveCounter;

	//歩きアニメーション
	int m_walkAnimFrame;
	//ジャンプアニメーション
	int m_jumpAnimFrame;
	//放置時アニメーション
	int m_IdleAnimFrame;
	//死亡時のアニメーション
	int m_DeadAnimFrame;

	//歩きモーション
	void RunMotion();
	//放置時モーション
	void IdleMotion();

	//プレイヤーのHP
	int m_Hp;

	//プレイヤーの座標
	Vec2 m_pos;
	//向いている方向
	Dir m_dir;

	//当たり判定用の矩形
	Rect m_colRect;

	//槍の当たり判定用の矩形
	Rect m_SpearRect;

	//ジャンプ力
	int m_JumpPower;

	// ジャンプしているかどうか
	bool isJump;

	bool isMove;   //移動中かどうか

	//キーが押されているフレーム数を格納する
	char key[256];

	// 現在のプレイヤーの矩形情報を取得
	Rect GetRect();
};