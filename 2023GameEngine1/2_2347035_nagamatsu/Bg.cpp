#include "Bg.h"
#include "DxLib.h"

Bg::Bg():m_Handle(-1)
{
	m_Handle = LoadGraph("image/Bg/Bg.png");
}

Bg::~Bg()
{
	DeleteGraph(m_Handle);
}

void Bg::Update()
{
}

void Bg::Draw()
{
	DrawGraph(0,0, m_Handle, false);
}

