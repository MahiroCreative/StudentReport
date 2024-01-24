#include "SceneStart.h"
#include "DxLib.h" 
#include "Game.h"

SceneStart::SceneStart():m_isSceneEnd(false),m_handle(-1), m_fadeAlpha(0), cursorY(440)
{
	
}

SceneStart::~SceneStart()
{
}

void SceneStart::Init()
{
	m_handle = LoadGraph("image/Bg/start.png");
	m_isSceneEnd = false;
}

void SceneStart::Update()
{
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_UP)
	{
		cursorY -= 40.0f;
	}
	if (pad & PAD_INPUT_DOWN)
	{
		cursorY += 40.0f;
	}
	if (pad & PAD_INPUT_1 && cursorY == 440.0f)
	{
		m_isSceneEnd = true;
	}
	if (pad & PAD_INPUT_1 && cursorY == 480.0f)
	{
		
	}

	if (cursorY > 480.0f)
	{
		cursorY = 440.0f;
	}
	if (cursorY < 440.0f)
	{
		cursorY = 480.0f;
	}



	if (m_isSceneEnd)
	{
		m_fadeAlpha += 8;
		if (m_fadeAlpha > 255)
		{
			m_fadeAlpha = 255;
		}
	}
	else
	{
		m_fadeAlpha -= 8;
		if (m_fadeAlpha < 0)
		{
			m_fadeAlpha = 0;
		}
	}
}

void SceneStart::Draw()
{
	DrawGraph(0, 0, m_handle, true);
	DrawString(Game::kScreenWindidth/2, Game::kScreenHeight-280, "ゲームスタート", GetColor(255, 255, 255));
	DrawString(Game::kScreenWindidth / 2, Game::kScreenHeight-240, "ゲーム終了", GetColor(255, 255, 255));
	DrawBox(Game::kScreenWindidth / 2, cursorY, Game::kScreenWindidth / 2 +120,cursorY + 20.0f,GetColor(255, 0, 0), false);

	//フェードの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha); //半透明で表示
	DrawBox(0, 0, Game::kScreenWindidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //不透明に戻しておく
}

void SceneStart::End()
{
	DeleteGraph(m_handle);
}

bool SceneStart::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}
