#include "SceneManager.h"
#include "SceneMain.h"
#include"Pad.h"

SceneManager::SceneManager():m_runScene(kSceneKindTitle), m_start(), m_select(), m_result()   
	//クラスの初期化時は()の中にコンストラクタの引数を書く
    //今回はどのシーンもコンストラクタで引数を要求しないので
    //m_title()のような書き方でOK
{
	
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//初期化処理
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_start.Init();
		break;
	case kSceneKindSelect:
		m_select.Init();
		break;
	case kSceneKindMain1:
		m_stage1.Init();
		break;
	case kSceneKindMain2:
		m_stage2.Init();
		break;
	case kSceneKindResult:
		m_result.Init();
		break;
	case kSceneKindClear:
		m_clear.Init();
	default:
		break;
	}
}

void SceneManager::End()
{
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_start.End();
		break;
	case kSceneKindSelect:
		m_select.End();
		break;
	case kSceneKindMain1:
		m_stage1.End();
		break;
	case kSceneKindMain2:
		m_stage2.End();
		break;
	case kSceneKindResult:
		m_result.End();
		break;
	case kSceneKindClear:
		m_clear.End();
	default:
		break;
	}
}

void SceneManager::Update()
{
	Pad::Update;
	//前のフレームの時点で処理が終わっていたらシーンの切り替え
//シーンの切り替えを行う

	switch (m_runScene)
	{
	case kSceneKindTitle:
		//タイトル画面の終了チェック
		if (m_start.IsSceneEnd())
		{
			m_start.End();  //実行していたシーンの終了処理

			//ゲームシーン
			m_runScene = kSceneKindSelect;	//次のフレーム以降、実行したいシーン
			m_select.Init();//変更先シーンの初期化

		}break;
	case kSceneKindSelect:
		if (m_select.IsSceneEnd())
		{
			m_select.End();  //実行していたシーンの終了処理
			if (m_select.selectNum == 1)
			{
				m_runScene = kSceneKindMain1; //次のフレーム以降、実行したいシーン
				m_stage1.Init(); //変更先シーンの初期化
			}
			if (m_select.selectNum == 2)
			{
				m_runScene = kSceneKindMain2; //次のフレーム以降、実行したいシーン
				m_stage2.Init(); //変更先シーンの初期化
			}
			
		}break;
	case kSceneKindMain1:
		if (m_stage1.IsSceneEnd())
		{
			m_stage1.End();  //実行していたシーンの終了処理

			m_runScene = kSceneKindResult; //次のフレーム以降、実行したいシーン
			m_result.Init(); //変更先シーンの初期化
		}
		if (m_stage1.IsSceneClear())
		{
			m_stage1.End();  //実行していたシーンの終了処理

			m_runScene = kSceneKindClear; //次のフレーム以降、実行したいシーン
			m_clear.Init(); //変更先シーンの初期化
		}
		break;
	case kSceneKindMain2:
		if (m_stage2.IsSceneEnd())
		{
			m_stage2.End();  //実行していたシーンの終了処理

			m_runScene = kSceneKindResult; //次のフレーム以降、実行したいシーン
			m_result.Init(); //変更先シーンの初期化
		}break;
	case kSceneKindResult:
		if (m_result.IsSceneEnd())
		{
			m_result.End();  //実行していたシーンの終了処理

			m_runScene = kSceneKindTitle; //次のフレーム以降、実行したいシーン
			m_start.Init(); //変更先シーンの初期化
		}break;
	case kSceneKindClear:
		if (m_clear.IsSceneEnd())
		{
			m_clear.End();//実行していたシーンの終了処理

			m_runScene = kSceneKindTitle; //次のフレーム以降、実行したいシーン
			m_start.Init();//変更先シーンの初期化
		}
	}

	//各シーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_start.Update();
		break;
	case kSceneKindSelect:
		m_select.Update();
		break;
	case kSceneKindMain1:
		m_stage1.Update();
		break;
	case kSceneKindMain2:
		m_stage2.Update();
		break;
	case kSceneKindResult:
		m_result.Update();
		break;
	case kSceneKindClear:
		m_clear.Update();
	default:
		break;
	}
}

void SceneManager::Draw()
{
	//各シーンの更新を行う
	switch (m_runScene)
	{
	case kSceneKindTitle:
		m_start.Draw();
		break;
	case kSceneKindSelect:
		m_select.Draw();
		break;
	case kSceneKindMain1:
		m_stage1.Draw();
		break;
	case kSceneKindMain2:
		m_stage2.Draw();
		break;
	case kSceneKindResult:
		m_result.Draw();
		break;
	case kSceneKindClear:
		m_clear.Draw();
	default:
		break;
	}
}
