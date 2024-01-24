#include "SceneSelect.h"
#include "DxLib.h"

SceneSelect::SceneSelect()
{
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Init()
{
	m_isSceneEnd = false;
	m_cursorX = 650.0f;
	m_cursorY = 36.0f;
	m_handle = LoadGraph("image/Bg/select.png");
}

void SceneSelect::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_UP)
	{
		m_cursorY -= 50.0f;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		m_cursorY += 50.0f;
	}
	if (pad & PAD_INPUT_LEFT)
	{
		m_cursorX -= 50.0f;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		m_cursorX += 50.0f;
	}

	if (pad & PAD_INPUT_1 && m_cursorY == 36.0f && m_cursorX == 650.0f)
	{
		selectNum = 1;
		m_isSceneEnd = true;
	}

	if (pad & PAD_INPUT_1 && m_cursorY == 36.0f && m_cursorX == 960.0f)
	{
		selectNum = 2;
		m_isSceneEnd = true;
	}
	
	if (m_cursorX < 650.0f)
	{
		m_cursorX = 650.0f;
	}
	if (m_cursorX > 960.0f)
	{
		m_cursorX = 960.0f;
	}
	if (m_cursorY > 560.0f)
	{
		m_cursorY = 560.0f;
	}
	if (m_cursorY < 36.0f)
	{
		m_cursorY = 36.0f;
	}

}

void SceneSelect::Draw()
{
	DrawGraph(0, 0, m_handle, true);
	DrawBox(m_cursorX, m_cursorY, m_cursorX+250, m_cursorY +150, GetColor(255, 255, 255), false);
}

void SceneSelect::End()
{
}

bool SceneSelect::IsSceneEnd() const
{
	return m_isSceneEnd && selectNum;
}
