#include "Dragon.h"
#include "DxLib.h"

namespace
{
	float kSpeed = 3.0f;
	//�摜�̃T�C�Y
	constexpr int kWidth = 62;
	constexpr int kHeight = 72;

	//�ړ����̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };

	//�ړ����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 8;

	//�ړ����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
}

Dragon::Dragon(): m_handle(-1), m_pos(0, 200), m_AnimFrame(0), m_pPlayer(nullptr),m_isEdge(true)
{
	m_handle = LoadGraph("image/Enemy/Dragon.png");
	m_pPlayer = new Player;
}

Dragon::~Dragon()
{
	DeleteGraph(m_handle);
}

void Dragon::Update()
{
	UpdateCollision();

	if (m_isEdge == true)
	{
		m_pos.x += 5;
		m_dir = 0;

		if (m_pos.x >= 1280)
		{
			m_isEdge = false;
			m_pos.y += 40;
		}
	}
	if (m_isEdge == false)
	{
		m_pos.x -= 5;
		m_dir = 1;

		if (m_pos.x <= 0)
		{
			m_isEdge = true;

			m_pos.y += 40;
		}
	}

	//if (m_pos.y >= 600) m_pos.y = 600;

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	MoveMotion();

}

void Dragon::Draw()
{
#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Dragon::OnDamege()
{
}

void Dragon::UpdateCollision()
{
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void Dragon::MoveMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 1.5, 0.0, m_handle, true, false);
}

void Dragon::DiedMotion()
{
}
