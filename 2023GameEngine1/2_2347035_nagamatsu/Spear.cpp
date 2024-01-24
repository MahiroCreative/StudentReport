#include "Spear.h"
#include "DxLib.h"

namespace
{
	
}

Spear::Spear( Vec2 pos):m_move(5.0f,0), m_pos(pos)
{
	m_handle = LoadGraph("image/spear.png");
	// 弾のグラフィックのサイズをえる
	GetGraphSize(m_handle, &SpearW, &SpearH);
}

Spear::~Spear()
{
	DeleteGraph(m_handle);
}

void Spear::Update()
{
	m_pos += m_move;

	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, SpearW, SpearH);

	Draw();
}

void Spear::Draw()
{
	DrawGraph(m_pos.x,m_pos.y,m_handle,TRUE);

#ifdef _DEBUG
	//　当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}