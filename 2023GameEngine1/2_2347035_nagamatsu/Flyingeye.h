#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Player.h"

class Flyingeye
{
public:
	Flyingeye();
	~Flyingeye();

	void Init();
	void Update();
	void Draw();
	void start();

	//�����蔻������
	void UpdateCollision();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }
	//�����Ă��邩�ǂ���
	bool isExist() const { return m_isExist; }

private:

	Player* m_pPlayer;
	
	//�n���h��
	int m_handle;

	//�����A�j���[�V����
	int m_AnimFrame;

	//�����蔻��
	Rect m_colRect;

	//�v���C���[�̕���
	int m_dir;

	//�ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
	Vec2 m_vec;

	//�G�l�~�[�̍��W
	Vec2 m_pos;

	//�n�ʂɂ�����
	bool m_isGround;

	//���݂��Ă��邩�ǂ���
	bool m_isExist;

	//�������[�V����
	void MoveMotion();
};

