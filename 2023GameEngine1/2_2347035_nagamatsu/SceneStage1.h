#pragma once
#include "Rect.h"

class Player;
class Bg;
class Map;
class Mushroom;
class Flyingeye;

namespace
{
	//�G�̐�
	constexpr int kEnemyNum = 20;
}

class SceneStage1
{
public:
	SceneStage1();
	~SceneStage1();

	void Init();
	void Update();
	void Draw();
	void End();

	//�v���C���[�ɓ�����
	void HitPlayer();

	//�V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

private:

	//�}�b�V�����[���̐���
	void CreateMushroom();

	//�t���C�A�C�̐���
	void CreateFlyeye();

	//�w�i
	Bg* m_pBg;
	//�}�b�v
	Map* m_pMap;
	//�v���C���[
	Player* m_pPlayer;
	//�}�b�V�����[��
	Mushroom* m_pMushroom[kEnemyNum];
	//�t���C�A�C
	Flyingeye* m_pFlyingeye[kEnemyNum];


	bool m_isGameOver;  //�Q�[���I�[�o�[���ǂ����̃t���O

	bool m_isSceneEnd;

	//�G�̓o��Ԋu
	int m_enemyInterval;

	//�G�̐�
	int m_enemyNum;

	//�t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	//���̍��W
	Rect m_SpearRect;
};

