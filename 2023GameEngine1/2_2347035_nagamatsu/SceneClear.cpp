#include "SceneClear.h"
#include "DxLib.h"

SceneClear::SceneClear()
{
}

SceneClear::~SceneClear()
{
	DeleteGraph(m_handel);
}

void SceneClear::Init()
{
	m_handel = LoadGraph("image/Bg/clear.png");
}

void SceneClear::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_6)
	{
		m_isSceneEnd = true;
	}
}

void SceneClear::Draw()
{
	DrawGraph(0,0,m_handel,true);
}

void SceneClear::End()
{
}

bool SceneClear::IsSceneEnd() const
{
	return  m_isSceneEnd;
}
