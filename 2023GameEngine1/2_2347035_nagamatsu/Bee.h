#pragma once
#include "Vec2.h"
#include "Rect.h"
class Bee
{
public:
	Bee();
	~Bee();

	void Update();
	void Draw();

	//�����蔻������
	void UpdateCollision();

	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }

private:

	int m_handle;

	//�����A�j���[�V����
	int m_AnimFrame;

	//�����蔻��
	Rect m_colRect;

	//�v���C���[�̕���
	int m_dir;

	//����܂ōs������
	bool upperlimit;

	//�ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
	Vec2 m_vec;

	//�G�l�~�[�̍��W
	Vec2 m_pos;

	//�������[�V����
	void MoveMotion();
};

