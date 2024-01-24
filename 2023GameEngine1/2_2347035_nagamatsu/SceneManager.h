#pragma once
#include "SceneStart.h"
#include "SceneMain.h"
#include "SceneStage1.h"
#include "SceneStage2.h"
#include "SceneSelect.h"
#include "SceneClear.h"
#include "SceneGameOver.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void Init();
	void End();

	void Update();
	void Draw();

private:

	//定数の定義
	enum SceneKind
	{
		kSceneKindTitle,
		kSceneKindSelect,
		kSceneKindMain1,
		kSceneKindMain2,
		kSceneKindMain3,
		kSceneKindMain4,
		kSceneKindMain5,
		kSceneKindMain6,
		kSceneKindResult,
		kSceneKindClear
	};

private:
	//現在実行中のシーン
	SceneKind m_runScene;

	//SceneManagerで管理する各シーン
	SceneStart m_start;
	SceneSelect m_select;
	SceneStage1 m_stage1;
	SceneStage2 m_stage2;
	SceneMain m_main;
	SceneGameOver m_result;
	SceneClear m_clear;
};

