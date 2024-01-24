#pragma once
#include "Rect.h"

class Player;
class Bg;
class Map;
class Mushroom;
class Flyingeye;

namespace
{
	//敵の数
	constexpr int kEnemyNum = 20;
}

class SceneStage1
{
public:
	SceneStage1();
	~SceneStage1();

	void Init();
	void Update();
	void Draw();
	void End();

	//プレイヤーに当たる
	void HitPlayer();

	//シーンを終了させるかどうか
	bool IsSceneEnd() const;

private:

	//マッシュルームの生成
	void CreateMushroom();

	//フライアイの生成
	void CreateFlyeye();

	//背景
	Bg* m_pBg;
	//マップ
	Map* m_pMap;
	//プレイヤー
	Player* m_pPlayer;
	//マッシュルーム
	Mushroom* m_pMushroom[kEnemyNum];
	//フライアイ
	Flyingeye* m_pFlyingeye[kEnemyNum];


	bool m_isGameOver;  //ゲームオーバーかどうかのフラグ

	bool m_isSceneEnd;

	//敵の登場間隔
	int m_enemyInterval;

	//敵の数
	int m_enemyNum;

	//フェードイン、アウト
	int m_fadeAlpha;

	//槍の座標
	Rect m_SpearRect;
};

