#pragma once
#include "Rect.h"
#include "Vec2.h"
class Player;
class Snails
{
public:
	Snails();
	~Snails();

	void Update();

	void Draw();

	void TrackingBall();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
	//�J�^�c�����̓����蔻����擾����
	Rect GetColRect() const noexcept { return m_colRect; }
	//�ʂ̓����蔻����擾����
	Rect GetBallRect() const noexcept { return m_ballRect; }

	//�����蔻������
	void UpdateCollision();

	
private:

	int m_handle;

	int m_ballHandle;

	//����W �^�E�����Ɉړ��������W
	   //y������sin�̒l�𑫂��ď㉺�ɓ����悤�ɂ���
	Vec2 m_pos;

	Player* m_pPlayer;

	//�v���C���[�̍��W
	Vec2 m_playerPos;
	//�v���C���[�̓����蔻��
	Rect m_colRect;

	//�v���C���[�̕���
	int m_dir;

	//�U�����̃A�j���[�V����
	int m_AnimFrame;

	
	//���˂����ʂ̍��W
	Vec2 m_ballPos;
	//�ʂ̓����蔻��
	Rect m_ballRect;
	//�ʂ̈ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
	Vec2 m_vec;

	//�U�����̃��[�V����
	void AttackMotion();

};

