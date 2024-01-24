#include "Unicorn.h"]
#include "Player.h"
#include "DxLib.h"

namespace
{
	constexpr int kWorkWideth = 64;
	constexpr int kWorkHeight = 59;
	constexpr int kAttackWideth = 66;
	constexpr int kAttackHeight = 59;

	//�ʂ̃T�C�Y
	constexpr int kBallWideth = 32;
	constexpr int kBallHeight = 32;

	//�ړ����x
	constexpr int kSpeed = 5;
	//�ʂ̑��x
	constexpr int kBallSpeed = 8;

	//�ړ����̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//�U�����̃A�j���[�V����
	constexpr int kAttackUseFrame[] = { 0,1,2,3,4 };

	//�ړ����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 8;
	//�U�����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAttackAnimFrameNum = 5;

	//�ړ����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//�U�����A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAttackAnimFrameCycle = _countof(kAttackUseFrame) * kAttackAnimFrameNum;


}

Unicorn::Unicorn():m_attackHandle(-1), m_dir(0),m_workHandle(-1), m_ballHendle(-1), m_pos(1200, 600), m_ballPos(0, 0)
{
	m_attackHandle = LoadGraph("image/Enemy/unicorn_Attack.png");
	m_workHandle = LoadGraph("image/Enemy/unicorn_work.png");
	m_ballHendle = LoadGraph("image/Enemy/ball2.png");
	m_pPlayer = new Player;
	m_ballPos = m_pos;
}

Unicorn::~Unicorn()
{
	DeleteGraph(m_attackHandle, m_workHandle);
	DeleteGraph(m_ballHendle);
}

void Unicorn::Update()
{
	UpdateCollision();

	m_playerPos = m_pPlayer->GetPos();
	
	shootBall();
	
	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = m_playerPos - m_pos;
	
	//�x�N�g���̒�����kSpeed�ɂ��Ă��
	//�x�N�g���̐��K���@�������P�ɂ���
	toTarget.normalize();

	if (m_playerPos.x > m_pos.x)
	{
		m_dir = 0;
	}
	else if (m_playerPos.x < m_pos.x)
	{
		m_dir = 1;
	}
	//kSpeed�ł�����
	m_vec = toTarget * kSpeed;
	m_pos += m_vec;

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	workMotion();
}

void Unicorn::Draw()
{
#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
	m_ballRect.Draw(GetColor(0, 0, 255), false);
#endif

	DrawGraph(m_ballPos.x, m_ballPos.y, m_ballHendle, true);
}

void Unicorn::UpdateCollision()
{
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWorkWideth, kWorkHeight);
	m_ballRect.SetCenter(m_ballPos.x+8, m_ballPos.y+16, kBallWideth, kBallHeight/2);
}

void Unicorn::shootBall()
{
	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = m_playerPos - m_pos;

	//�x�N�g���̒�����kSpeed�ɂ��Ă��
	//�x�N�g���̐��K���@�������P�ɂ���
	toTarget.normalize();
	//kSpeed�ł�����
	m_vec = toTarget * kBallSpeed;

	m_ballPos += m_vec;
}

void Unicorn::workMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWorkWideth;
	int srcY = kWorkHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWorkWideth, kWorkHeight, 3.0, 0.0, m_workHandle, true, false);
}

void Unicorn::attackMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kAttackWideth;
	int srcY = kAttackHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kAttackWideth, kAttackHeight, 3.0, 0.0, m_attackHandle, true, false);
}
