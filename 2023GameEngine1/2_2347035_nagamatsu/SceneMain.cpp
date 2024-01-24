#include "SceneMain.h"
#include "Bg.h"
#include "Map.h"
#include"Player.h"
#include "Mushroom.h"
#include "Flyingeye.h"
#include "Spear.h"
#include "Dragon.h"
#include "Vec2.h"
#include "EnemyBase.h"
#include "Snails.h"
#include "Bee.h"
#include "Unicorn.h"
#include "DxLib.h"
#include "Game.h"
#include <memory>

namespace
{
	//��x�ɓo�ꂷ��G�̐�
	constexpr int kEnemyMax = 32;

}

SceneMain::SceneMain():m_isGameOver(false), m_isSceneEnd(false)
{
	//�������m��
	m_pBg = new Bg;
	m_pPlayer = new Player;
	m_pMap = new Map;
	m_pMushroom = new Mushroom;
	m_pFlyingeye = new Flyingeye;
	m_pDragon = new Dragon;
	m_pSnails = new Snails;
	m_pBee = new Bee;
	m_pUnicorn = new Unicorn;

	m_pPlayer->SetMap(m_pMap);
	m_pMap->setPlayer(m_pPlayer);
	
}

SceneMain::~SceneMain()
{
	
}

void SceneMain::Init()
{
	m_isGameOver = false;
	m_isSceneEnd = false;
	m_pMap->Init();
	m_pPlayer->Init();
}

void SceneMain::Update()
{
	m_pMap->Update();
	m_pMushroom->Update();
	m_pPlayer->Update();
	m_pFlyingeye->Update();
	m_pDragon->Update();
	m_pSnails->Update();
	m_pBee->Update();
	m_pUnicorn->Update();

	//�P�{�^��orZ�L�[�������ꂽ��Q�[���I�[�o�[��ʂ�
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (pad & PAD_INPUT_6) //1�{�^���������ꂽ
	{
		m_isSceneEnd = true;
	}


	HitPlayer();
}

void SceneMain::Draw()
{
	m_pMap->Draw();
	m_pPlayer->Draw();
	m_pMushroom->Draw();
	m_pFlyingeye->Draw();
	m_pDragon->Draw();
	m_pSnails->Draw();
	m_pBee->Draw();
	m_pUnicorn->Draw();


	//�t�F�[�h�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_fadeAlpha); //�������ŕ\��
	DrawBox(0, 0, Game::kScreenWindidth, Game::kScreenHeight, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //�s�����ɖ߂��Ă���

}

void SceneMain::End()
{
	m_pPlayer->End();


	//�N���X�̃��������������
	delete m_pBg;
	m_pBg = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
	delete m_pMushroom;
	m_pMushroom = nullptr;
	delete m_pFlyingeye;
	m_pFlyingeye = nullptr;
	delete m_pDragon;
	m_pDragon = nullptr;
	delete m_pSnails;
	m_pSnails = nullptr;
	delete m_pBee;
	m_pBee = nullptr;
	delete m_pUnicorn;
	m_pUnicorn = nullptr;
}

bool SceneMain::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

void SceneMain::HitPlayer()
{
	Rect PlayerRect = m_pPlayer->GetColRect();
	Rect MushroomRect = m_pMushroom->GetColRect();
	Rect MapRect = m_pMap->GetColRect();
	Rect FlyingeyeRect = m_pFlyingeye->GetColRect();
	Rect DragonRect = m_pDragon->GetColRect();
	Rect SnailsRect = m_pSnails->GetColRect();
	Rect SnailsAttackRect = m_pSnails->GetBallRect();
	Rect BeeRect = m_pBee->GetColRect();
	Rect UnicornRect = m_pUnicorn->GetColRect();
	Rect UnicornAttackRect = m_pUnicorn->GetBallRect();

	int Hp = m_pPlayer->GetHp();

	if (PlayerRect.IsCollsion(MushroomRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(FlyingeyeRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(DragonRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(SnailsRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(SnailsAttackRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(BeeRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(UnicornRect))
	{
		m_pPlayer->OnDamege();
	}
	if (PlayerRect.IsCollsion(UnicornAttackRect))
	{
		m_pPlayer->OnDamege();
	}

	if (Hp <= 0)
	{
		m_isSceneEnd = true;
		if (m_isSceneEnd)
		{
			// �t�F�[�h�A�E�g
			m_fadeAlpha += 8;

			if (m_fadeAlpha > 255)
			{
				m_fadeAlpha = 255;
			}

		}
	}
}

void SceneMain::HitEnemy()
{

}

void SceneMain::CreateMushroom()
{
}

void SceneMain::CreateSnails()
{
	
}
