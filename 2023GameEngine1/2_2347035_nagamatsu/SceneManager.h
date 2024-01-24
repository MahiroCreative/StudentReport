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

	//�萔�̒�`
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
	//���ݎ��s���̃V�[��
	SceneKind m_runScene;

	//SceneManager�ŊǗ�����e�V�[��
	SceneStart m_start;
	SceneSelect m_select;
	SceneStage1 m_stage1;
	SceneStage2 m_stage2;
	SceneMain m_main;
	SceneGameOver m_result;
	SceneClear m_clear;
};

