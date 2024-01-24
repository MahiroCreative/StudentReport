#include "Mushroom.h"
#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//�����ʒu
	constexpr float kGroundY = 150.0f;

	//�E����o��ꍇ�̍��W
	constexpr float kRight = 1150.0f;

	//������o��ꍇ
	constexpr float kLeft = 100.0f;

	float kSpeed = 6.0f;
	//�摜�̃T�C�Y
	constexpr int kWidth = 150;
	constexpr int kHeight = 150;

	//�������Ă��������܂ł̃t���[����
	constexpr int kExistFrame = 60 * 5;

	//�U���E�ړ����̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//���S���̃A�j���[�V����
	constexpr int kDiedUseFrame[] = { 0,1,2,3 };

	//�U���E�ړ����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum= 8;
	//���S���A�j���[�V�����P�R�}�̃t���[����
	constexpr int kDiedAnimaFrameNum = 4;

	//�U���E�ړ����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//���S���A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kDiedAnimaFrameCycle = _countof(kDiedUseFrame) * kDiedAnimaFrameNum;
}

Mushroom::Mushroom()
{
	m_handle = LoadGraph("image/Enemy/Mushroom.png");
}

Mushroom::~Mushroom()
{
	DeleteGraph(m_handle);
}

void Mushroom::Init()
{
	m_pos = { Game::kScreenWindidth, kGroundY };
	m_dir = 0;
	m_Dieddir = 0;
	m_AnimFrame = 0;
	m_DiedAnimFrame = 0;
	Hp = 1;
	m_isExist = false;
}

void Mushroom::Update()
{
	if (!m_isExist) return;

	m_pos += m_vec;
	//�����蔻��̍X�V
	UpdateCollision();
}

void Mushroom::Draw()
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

void Mushroom::OnDamege()
{
	Hp -= 1;
	
	if (Hp <= 0)
	{
		Hp = 0;
		m_isExist = false;
	}

}

void Mushroom::MoveMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_handle, true, false);
}
void Mushroom::DiedMotion()
{
	int animFrame = m_DiedAnimFrame / kDiedAnimaFrameNum;
	int srcX = kDiedUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_handle, true, false);
}

void Mushroom::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth/2, kHeight/2);
}

void Mushroom::start()
{
	m_isExist = true;

	m_dir = 0;
	int num = GetRand(1);
	switch (num)
	{
	case 0:
		m_pos.x = kLeft;
		m_dir = 0;
		break;
	case 1:
		m_pos.x = kRight;
		m_dir = 1;
	default:
		break;
	}
	
	m_pos.y = kGroundY;


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

