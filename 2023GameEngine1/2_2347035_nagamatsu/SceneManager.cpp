#include "SceneManager.h"
#include "SceneMain.h"
#include"Pad.h"

SceneManager::SceneManager():m_runScene(kSceneKindTitle), m_start(), m_select(), m_result()   
	//�N���X�̏���������()�̒��ɃR���X�g���N�^�̈���������
    //����͂ǂ̃V�[�����R���X�g���N�^�ň�����v�����Ȃ��̂�
    //m_title()�̂悤�ȏ�������OK
{
	
}

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	//����������
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
	//�O�̃t���[���̎��_�ŏ������I����Ă�����V�[���̐؂�ւ�
//�V�[���̐؂�ւ����s��

	switch (m_runScene)
	{
	case kSceneKindTitle:
		//�^�C�g����ʂ̏I���`�F�b�N
		if (m_start.IsSceneEnd())
		{
			m_start.End();  //���s���Ă����V�[���̏I������

			//�Q�[���V�[��
			m_runScene = kSceneKindSelect;	//���̃t���[���ȍ~�A���s�������V�[��
			m_select.Init();//�ύX��V�[���̏�����

		}break;
	case kSceneKindSelect:
		if (m_select.IsSceneEnd())
		{
			m_select.End();  //���s���Ă����V�[���̏I������
			if (m_select.selectNum == 1)
			{
				m_runScene = kSceneKindMain1; //���̃t���[���ȍ~�A���s�������V�[��
				m_stage1.Init(); //�ύX��V�[���̏�����
			}
			if (m_select.selectNum == 2)
			{
				m_runScene = kSceneKindMain2; //���̃t���[���ȍ~�A���s�������V�[��
				m_stage2.Init(); //�ύX��V�[���̏�����
			}
			
		}break;
	case kSceneKindMain1:
		if (m_stage1.IsSceneEnd())
		{
			m_stage1.End();  //���s���Ă����V�[���̏I������

			m_runScene = kSceneKindResult; //���̃t���[���ȍ~�A���s�������V�[��
			m_result.Init(); //�ύX��V�[���̏�����
		}
		if (m_stage1.IsSceneClear())
		{
			m_stage1.End();  //���s���Ă����V�[���̏I������

			m_runScene = kSceneKindClear; //���̃t���[���ȍ~�A���s�������V�[��
			m_clear.Init(); //�ύX��V�[���̏�����
		}
		break;
	case kSceneKindMain2:
		if (m_stage2.IsSceneEnd())
		{
			m_stage2.End();  //���s���Ă����V�[���̏I������

			m_runScene = kSceneKindResult; //���̃t���[���ȍ~�A���s�������V�[��
			m_result.Init(); //�ύX��V�[���̏�����
		}break;
	case kSceneKindResult:
		if (m_result.IsSceneEnd())
		{
			m_result.End();  //���s���Ă����V�[���̏I������

			m_runScene = kSceneKindTitle; //���̃t���[���ȍ~�A���s�������V�[��
			m_start.Init(); //�ύX��V�[���̏�����
		}break;
	case kSceneKindClear:
		if (m_clear.IsSceneEnd())
		{
			m_clear.End();//���s���Ă����V�[���̏I������

			m_runScene = kSceneKindTitle; //���̃t���[���ȍ~�A���s�������V�[��
			m_start.Init();//�ύX��V�[���̏�����
		}
	}

	//�e�V�[���̍X�V���s��
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
	//�e�V�[���̍X�V���s��
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
