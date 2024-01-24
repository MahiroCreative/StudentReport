#pragma once
#include "Game.h"
#include "Rect.h"
#include "Player.h"
// マップの構造体

class Map
{
public:
	Map();
	~Map();

	void Init();
	void Update();
	void Draw();

	// プレイヤーと当たっているか判定
	bool IsColPlayer();

	//プレイヤーの当たり判定を取得する
	Rect GetColRect() const noexcept { return m_colRect; }

	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// 指定した矩形と当たっているか判定
	// 参照を使用してぶつかったマップチップの矩形情報を取得する chipRect
	bool IsCollision(Rect rect, Rect& chipRect);

private:

	Player* m_pPlayer;

	//mapのハンドル
	int m_Handle;

	//グラフィックに含まれるマップチップの数
	int m_MapNumX;
	int m_MapNumY;

	//当たり判定用の矩形
	Rect m_colRect;
};

