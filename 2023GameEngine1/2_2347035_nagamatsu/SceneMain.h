#pragma once
#include "Vec2.h"
#include <vector>

class Player;
class Bg;
class Map;
class Spear;
class Flyingeye;
class Dragon;
class EnemyBase;
class Mushroom;
class Snails;
class Bee;
class Unicorn;

class SceneMain
{
public:
	SceneMain();
	~SceneMain();

	void Init();
	void Update();
	void Draw();
	void End();

	//�V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

private:

	//�����蔻��
	void HitPlayer();

	//�����蔻��G
	void HitEnemy();

	//�G�L�����N�^�[�̐���
	void CreateMushroom();

	//�J�^�c�����̐���
	void CreateSnails();
private:
	//�w�i
	Bg* m_pBg;
	//�}�b�v
	Map* m_pMap;
	//�v���C���[
	Player* m_pPlayer;
	//�}�b�V�����[��
	Mushroom* m_pMushroom;
	//��
	Spear* m_pSpear;
	//�t���C�A�C
	Flyingeye* m_pFlyingeye;
	//�t���C�i�C�g
	Dragon* m_pDragon;
	//�J�^�c����
	Snails* m_pSnails;
	//�I
	Bee* m_pBee;
	//��p�b
	Unicorn* m_pUnicorn;

	bool m_isGameOver;  //�Q�[���I�[�o�[���ǂ����̃t���O
	bool m_isSceneEnd;

	Vec2 m_PlayerPos;

	//�t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;
};

