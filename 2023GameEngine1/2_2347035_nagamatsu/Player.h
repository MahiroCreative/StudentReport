#pragma once
#include"Vec2.h"
#include"Rect.h"
#include "Spear.h"
#include "SceneGameOver.h"

class Map;
class Player
{
	//�����Ă������
	enum Dir
	{
		kDirRight, //�E�@��0
		kDirLeft, //���@��1
	};

public:
	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void End();
	void Attack();

	// �}�b�v�̃|�C���^��ݒ肷��
	void SetMap(Map* pMap) { m_pMap = pMap; }

	//�v���C���[�̌��݈ʒu���擾����
	Vec2 GetPos() const { return m_pos; }

	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const noexcept { return m_colRect;}

	//���̓����蔻��擾����
	Rect GetSpearRect() const noexcept { return m_SpearRect;}

	//�v���C���[��Hp���擾����
	int GetHp() const noexcept { return m_Hp; }

	// �v���C���[�̏㉺���E���W���擾
	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();

	//�G�ɓ����������̏���
	void OnDamege();
private:

	Spear* m_pSpear;
	SceneGameOver* m_pSceneGameOver;

	Map* m_pMap;

	//�v���C���[���������̃n���h��
	int m_Runhandle;
	//�v���C���[���~�܂��Ă���Ƃ��̃n���h��
	int m_Waitinghandle;
	//�v���C���[���W�����v����Ƃ��̃n���h��
	int m_Jumphamdle;
	//�v���C���[�����S���̃n���h��
	int m_Deadhandle;
	// �ړ����n�߂Ă��牽�t���[���o�߂�������ێ�����ϐ�
	int MoveCounter;

	//�����A�j���[�V����
	int m_walkAnimFrame;
	//�W�����v�A�j���[�V����
	int m_jumpAnimFrame;
	//���u���A�j���[�V����
	int m_IdleAnimFrame;
	//���S���̃A�j���[�V����
	int m_DeadAnimFrame;

	//�������[�V����
	void RunMotion();
	//���u�����[�V����
	void IdleMotion();

	//�v���C���[��HP
	int m_Hp;

	//�v���C���[�̍��W
	Vec2 m_pos;
	//�����Ă������
	Dir m_dir;

	//�����蔻��p�̋�`
	Rect m_colRect;

	//���̓����蔻��p�̋�`
	Rect m_SpearRect;

	//�W�����v��
	int m_JumpPower;

	// �W�����v���Ă��邩�ǂ���
	bool isJump;

	bool isMove;   //�ړ������ǂ���

	//�L�[��������Ă���t���[�������i�[����
	char key[256];

	// ���݂̃v���C���[�̋�`�����擾
	Rect GetRect();
};