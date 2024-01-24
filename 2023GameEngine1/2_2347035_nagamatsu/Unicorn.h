#pragma once
#include "Vec2.h"
#include "Rect.h"

class Player;

class Unicorn
{
public:
	Unicorn();
	~Unicorn();

	void Update();
	void Draw();
	//�����蔻������
	void UpdateCollision();

	//�J�^�c�����̓����蔻����擾����
	Rect GetColRect() const noexcept { return m_colRect; }
	//�ʂ̓����蔻����擾����
	Rect GetBallRect() const noexcept { return m_ballRect; }

private:

	Player* m_pPlayer;

	//�n���h��
	int m_workHandle;
	int m_attackHandle;
	int m_ballHendle;

	//�v���C���[�̍��W
	Vec2 m_playerPos;

	//�v���C���[�̕���
	int m_dir;

	//Unicorn�̍��W
	Vec2 m_pos;
	//Unicorn�����蔻��
	Rect m_colRect;

	//�ړ���
	Vec2 m_vec;

	//�ʂ̍��W
	Vec2 m_ballPos;
	//�ʂ̓����蔻��
	Rect m_ballRect;

	//�ʂ𔭎˂���
	void shootBall();

	//�����A�j���[�V����
	int m_AnimFrame;
	//�U���A�j���[�V����
	int m_AttackAnimFrame;

	

	//�������[�V����
	void workMotion();

	//�U�����[�V����
	void attackMotion();

};

