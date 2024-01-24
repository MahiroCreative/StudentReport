#pragma once
#include "Rect.h"

class Player;
class Bg;
class Map;
class Mushroom;
class Flyingeye;
class Timer;

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

	//クリアをさせるかどうか
	bool IsSceneClear() const;

private:

	//マッシュルームの生成
	void CreateMushroom();

	//フライアイの生成
	void CreateFlyeye();

	//制限時間までによけきったら
	void GameClear();

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
	//タイマー
	Timer* m_pTimer;


	bool m_isGameOver;  //ゲームオーバーかどうかのフラグ

	bool m_isGameClear; //ゲームクリアかどうかのフラグ

	bool m_isSceneEnd;

	//敵の登場間隔
	int m_enemyInterval;

	//敵の数
	int m_enemyNum;

	//時間
	int time;
	//カウント
	int count;

	//フェードイン、アウト
	int m_fadeAlpha;

	//槍の座標
	Rect m_SpearRect;
};

