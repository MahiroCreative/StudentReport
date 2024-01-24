#include "Snails.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	//�ʂ̑���
	constexpr float kSpeed = 2.0f;
	//�ʂ̃T�C�Y
	constexpr int kBallWideth = 32;
	constexpr int kBallHeight = 32;

	//�摜�̃T�C�Y
	constexpr int kWidth = 47;
	constexpr int kHeight = 22;

	//�U�����̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };

	//�U�����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 8;

	//�U�����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
}

Snails::Snails():m_pPlayer(nullptr),m_handle(-1), m_ballHandle(-1), m_ballPos(200, 100), m_pos(200, 100)
{
	m_handle = LoadGraph("image/Enemy/Snails.png");
	m_ballHandle = LoadGraph("image/Enemy/ball.png");
	m_pPlayer = new Player;
}

Snails::~Snails()
{
	DeleteGraph(m_handle, m_ballHandle);
}

void Snails::Update()
{
	UpdateCollision();

	//�^�[�Q�b�g�ʒu
	m_playerPos = m_pPlayer->GetPos();

	TrackingBall();
	if (m_playerPos.x > m_pos.x)
	{
		m_dir = 1;
	}
	else if (m_playerPos.x < m_pos.x)
	{
		m_dir = 0;
	}

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	AttackMotion();
}

void Snails::Draw()
{
#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
	m_ballRect.Draw(GetColor(0, 0, 255), false);
#endif

	DrawGraph(m_ballPos.x, m_ballPos.y, m_ballHandle, true);
}

void Snails::TrackingBall()
{
	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = m_playerPos - m_pos;

	//�x�N�g���̒�����kSpeed�ɂ��Ă��
	//�x�N�g���̐��K���@�������P�ɂ���
	toTarget.normalize();
	//kSpeed�ł�����
	m_vec = toTarget * kSpeed;

	m_ballPos += m_vec;
}

void Snails::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
		//���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight*2);
	m_ballRect.SetCenter(m_ballPos.x+16, m_ballPos.y+16, kBallWideth / 2,kBallHeight/2);
}

void Snails::AttackMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight,2.0,0.0, m_handle, true, false);
}
