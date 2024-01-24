#include "DxLib.h"
#include "Flyingeye.h"
#include "Game.h"
#include "Player.h"
namespace
{
	//�����̍���
	constexpr int kInitialHeight = 500;

	//����
	float kSpeed = 4.0f;
	//�摜�̃T�C�Y
	constexpr int kWidth = 150;
	constexpr int kHeight = 33;

	//�ړ����̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };

	//�ړ����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 8;

	//�ړ����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
}

Flyingeye::Flyingeye()
{
	m_handle = LoadGraph("image/Enemy/Flyingeye.png");
}

Flyingeye::~Flyingeye()
{
	DeleteGraph(m_handle);
}

void Flyingeye::Init()
{
	m_pos = { Game::kScreenWindidth, kInitialHeight };
	m_AnimFrame = 0;
	m_isGround = true;
	m_isExist = false;
}

void Flyingeye::Update()
{
	if (!m_isExist) return;
	m_pos += m_vec;

	//�����蔻��̍X�V
	UpdateCollision();
}

void Flyingeye::Draw()
{
	if (!m_isExist) return;

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	MoveMotion();

#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Flyingeye::start()
{
	m_isExist = true;

	m_pos.x = m_pos.x = static_cast<float>(GetRand(Game::kScreenWindidth - kWidth) + kWidth / 2);
	m_pos.y = static_cast<float>(-kHeight / 2); //��ʏォ������Ă���

	Vec2 playerPos = m_pPlayer->GetPos();

	//�G�̏����ʒu����^�[�Q�b�g�ʒu�Ɍ������x�N�g���𐶐�����
	//�n�_����I�_�Ɍ������x�N�g�������߂�ꍇ�A�I�_�̍��W-�n�_�̍��W�ŋ��߂�
	Vec2 toTarget = playerPos - m_pos;

	//�x�N�g���̒�����kSpeed�ɂ��Ă��
	//�x�N�g���̐��K���@�������P�ɂ���
	toTarget.normalize();
	//kSpeed�ł�����
	m_vec = toTarget * kSpeed;
}

void Flyingeye::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth / 2, kHeight );
}

void Flyingeye::MoveMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_handle, true, false);
}
