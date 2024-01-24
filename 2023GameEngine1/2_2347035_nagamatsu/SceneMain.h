#pragma once
#include "Vec2.h"
#include <vector>

class Player;
class Bg;
class Map;
class Spear;
class Flyingeye;
class Dragon;
class EnemyBase;
class Mushroom;
class Snails;
class Bee;
class Unicorn;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

	//シーンを終了させるかどうか
	bool IsSceneEnd() const;

private:

	//当たり判定
	void HitPlayer();

	//当たり判定敵
	void HitEnemy();

	//敵キャラクターの生成
	void CreateMushroom();

	//カタツムリの生成
	void CreateSnails();
private:
	//背景
	Bg* m_pBg;
	//マップ
	Map* m_pMap;
	//プレイヤー
	Player* m_pPlayer;
	//マッシュルーム
	Mushroom* m_pMushroom;
	//槍
	Spear* m_pSpear;
	//フライアイ
	Flyingeye* m_pFlyingeye;
	//フライナイト
	Dragon* m_pDragon;
	//カタツムリ
	Snails* m_pSnails;
	//蜂
	Bee* m_pBee;
	//一角獣
	Unicorn* m_pUnicorn;

	bool m_isGameOver;  //ゲームオーバーかどうかのフラグ
	bool m_isSceneEnd;

	Vec2 m_PlayerPos;

	//フェードイン、アウト
	int m_fadeAlpha;
};

