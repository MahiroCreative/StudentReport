#include "SceneStage1.h"
#include "Bg.h"
#include "Map.h"
#include "Player.h"
#include "Mushroom.h"
#include "Flyingeye.h"
#include "DxLib.h"
namespace
{
	//何フレームおきに敵が登場するか
	constexpr int kEnemyInterval = 60;

	//最大敵の数
	constexpr int kEnemyMax = 20;
}


SceneStage1::SceneStage1()
{
	//メモリ確保
	m_pBg = new Bg;
	m_pMap = new Map;
	m_pPlayer = new Player;

	m_pPlayer->SetMap(m_pMap);
	m_pMap->setPlayer(m_pPlayer);


	for (int i = 1; i < kEnemyMax; i++)
	{
		m_pMushroom[i] = nullptr;
	}

	for (int f = 0; f < kEnemyMax; f++)
	{
		m_pFlyingeye[f] = nullptr;
	}
}

SceneStage1::~SceneStage1()
{
	delete m_pBg;
	m_pBg = nullptr;
	delete m_pMap;
	m_pMap = nullptr;
	delete m_pPlayer;
	m_pPlayer = nullptr;

	for (int i = 1; i < kEnemyMax; i++)
	{
		delete m_pMushroom[i];
		m_pMushroom[i] = nullptr;
	}
	for (int f = 0; f < kEnemyMax; f++)
	{
		delete m_pFlyingeye[f];
		m_pFlyingeye[f] = nullptr;
	}
}

void SceneStage1::Init()
{
	m_enemyNum = 0;	
	m_pMap->Init();
	m_pPlayer->Init();
}

void SceneStage1::Update()
{
	m_pMap->Update();
	m_pPlayer->Update();
	m_SpearRect = m_pPlayer->GetSpearRect();
	Rect PlayerRect = m_pPlayer->GetColRect();

	for (int i = 1; i < kEnemyMax; i++)
	{
		Rect PlayerRect = m_pPlayer->GetColRect();
		if (m_pMushroom[i])
		{
			m_pMushroom[i]->Update();
			Rect MushroomRect = m_pMushroom[i]->GetColRect();
			if (PlayerRect.IsCollsion(MushroomRect))
			{
				m_pPlayer->OnDamege();
			}
		}
	}

	for (int f = 0; f < kEnemyMax; f++)
	{
		if (m_pFlyingeye[f])
		{
			m_pFlyingeye[f]->Update();
			Rect Flyingeye = m_pFlyingeye[f]->GetColRect();
			if(PlayerRect.IsCollsion(Flyingeye))
			{
				m_pPlayer->OnDamege();
			}
		}
	}
	
	if (m_enemyNum <= kEnemyMax)
	{
		m_enemyInterval++;

		if (m_enemyInterval >= kEnemyInterval)
		{
			m_enemyInterval = 0;
			int num = GetRand(1);
			//ランダムに敵を選択
			switch (num)
			{
			case 0:		//マッシュルーム
				CreateMushroom();
				
				m_enemyNum++;
				break;
			case 1:		//フライアイ
				CreateFlyeye();
				
				m_enemyNum++;
				break;
			}
		}
	}

	
	HitPlayer();
}

void SceneStage1::Draw()
{
	m_pBg->Draw();
	m_pMap->Draw();

	for (int i = 1; i < kEnemyMax; i++)
	{
		if (m_pMushroom[i])
		{
			m_pMushroom[i]->Draw();
		}
		
	}
	for (int f = 0; f < kEnemyMax; f++)
	{
		if (m_pFlyingeye[f])
		{
			m_pFlyingeye[f]->Draw();
		}
	}

	m_pPlayer->Draw();
}

void SceneStage1::End()
{
	
}

void SceneStage1::HitPlayer()
{
	int Hp = m_pPlayer->GetHp();
	
	if (Hp <= 0)
	{
		m_isSceneEnd = true;
		if (m_isSceneEnd)
		{
			// フェードアウト
			m_fadeAlpha += 8;

			if (m_fadeAlpha > 255)
			{
				m_fadeAlpha = 255;
			}

		}
	}
}

bool SceneStage1::IsSceneEnd() const
{
	return m_isSceneEnd && (m_fadeAlpha >= 255);
}

void SceneStage1::CreateMushroom()
{
	for (int i = 1; i < kEnemyMax; i++)
	{
		if (!m_pMushroom[i])
		{
			m_pMushroom[i] = new Mushroom;
			m_pMushroom[i]->Init();
			m_pMushroom[i]->SetPlayer(m_pPlayer);
			m_pMushroom[i]->start();
			return;
		}
	}
}

void SceneStage1::CreateFlyeye()
{
	for (int f = 0; f < kEnemyMax; f++)
	{
		if (!m_pFlyingeye[f])
		{
			m_pFlyingeye[f] = new Flyingeye;
			m_pFlyingeye[f]->Init();
			m_pFlyingeye[f]->SetPlayer(m_pPlayer);
			m_pFlyingeye[f]->start();

			return;
		}
	}
}
