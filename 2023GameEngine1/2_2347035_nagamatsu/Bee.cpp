#include "Bee.h"
#include "DxLib.h"
namespace
{
	constexpr int kSpeed = 2;

	//�摜�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//�ړ����̃A�j���[�V����
	constexpr int kUseFrame[] = {0,1,2,3};

	//�ړ����A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 4;

	//�ړ����A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
}

Bee::Bee(): m_handle(-1), m_AnimFrame(0), m_pos(1000,100), upperlimit(true)
{
	m_handle = LoadGraph("image/Enemy/bee.png");
}

Bee::~Bee()
{
	DeleteGraph(m_handle);
}

void Bee::Update()
{
	UpdateCollision();

	m_pos.x -= kSpeed;

	if (upperlimit == true)
	{
		m_pos.y += 5;

		if (m_pos.y >= 600)
		{
			upperlimit = false;
		}
	}
	if (upperlimit == false)
	{
		m_pos.y -= 5;

		if (m_pos.y <= 100)
		{
			upperlimit = true;
		}
	}
	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	MoveMotion();
}

void Bee::Draw()
{
#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Bee::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	//���S���W���w�肵�ē����蔻���Rect�𐶐�����
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
}

void Bee::MoveMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * 0;

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_handle, true, false);
}
