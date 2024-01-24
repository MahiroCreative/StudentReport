#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Player;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();

	virtual void Update();
	virtual void Draw();

	bool isExist() const { return m_isExist; }

	//位置の取得
	Vec2 GetPos() const { return m_pos; }

	//当たり判定の矩形を取得する
	Rect GetColRect() const { return m_colRect; }
	//敵キャラクターをスタートさせる
	virtual void start() = 0;

protected:

	//private:　継承先からも参照できない
protected: //継承先から参照できる
	int m_handle; //グラフィックのハンドル

	bool m_isExist; //存在するかフラグ(使用中かどうか)

	//表示位置
	Vec2 m_pos;
	//当たり判定の矩形
	Rect m_colRect;
	//移動量 1フレーム当たりの移動ベクトルを入れる　　　
	Vec2 m_vec;
};

