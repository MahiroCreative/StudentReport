#include "SceneGameOver.h"
#include "DxLib.h"

SceneGameOver::SceneGameOver():m_handle(-1), m_isSceneEnd(false)
{
}

SceneGameOver::~SceneGameOver()
{
}

void SceneGameOver::Init()
{
	m_handle = LoadGraph("image/Bg/GameOver.png");
}

void SceneGameOver::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_6)
	{
		m_isSceneEnd = true;
	}
}

void SceneGameOver::Draw()
{
	DrawGraph(0, 0, m_handle, true);
}

void SceneGameOver::End()
{
	DeleteGraph(m_handle);
}

bool SceneGameOver::IsSceneEnd() const
{
	return m_isSceneEnd;
}