#include "Pad.h"
#include "Player.h"
#include "Rect.h"
#include "DxLib.h"
#include "Map.h"
#include "Game.h"

#define MOVE_FRAME      15          // �ړ��ɂ�����t���[����

namespace
{
	// �d��
	constexpr float kGravity = 0.5f;
	// �W�����v��
	constexpr float kJumpPower = -8.0f;

	//�v���C���[�̍ő�HP
	constexpr int kMaxHp = 2;

	float kSpeed = 4.0f;
	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 80;
	constexpr int kHeight = 52;
	//�W�����v���̃L�����N�^�[�T�C�Y
	//constexpr int kJumpWideth = 64;
	//constexpr int kJumpHeight = 64;
	//���u���̃L�����N�^�[�T�C�Y
	constexpr int kIdleWideth = 64;
	constexpr int kIdleHeight = 80;
	//���S���̃L�����N�^�[�T�C�Y
	constexpr int kDeadWideth = 80;
	constexpr int kDeadHeight = 64;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//�W�����v�̃A�j���[�V����
	//constexpr int kUseJumpFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	//���u���̃A�j���[�V����
	constexpr int kUseIdleFrame[] = { 0,1,2,3 };
	//���S���̃A�j���[�V����
	constexpr int kUseDeadFrame[] = { 0,1,2,3,4,5,6,7 };


	//�A�j���[�V�����P�R�}�̃t���[����
	constexpr int kAnimaFrameNum = 8;
	//�W�����v�A�j���[�V�����P�R�}�̃t���[����
	//constexpr int kJumpAnimFrameNum = 15;
	//�ҋ@���A�j���[�V�����P�R�}�̃t���[����
	constexpr int kIdleAnimFrameNum = 4;
	//���S���A�j���[�V�����P�R�}�̃t���[����
	constexpr int kDeadAnimFrameNum = 8;

	//�A�j���[�V�����P�T�C�N���̃t���[����
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//�W�����v�A�j���[�V�����P�T�C�N���̃t���[����
	//constexpr int kJumpAnimFrameCycle = _countof(kUseJumpFrame) * kJumpAnimFrameNum;
	//���u���A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kIdleAnimFrameCycle = _countof(kUseIdleFrame) * kIdleAnimFrameNum;
	//���S���A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kDeadAnimFrameCycle = _countof(kUseDeadFrame) * kDeadAnimFrameNum;
}

Player::Player()
{
	
}

Player::~Player()
{
}

void Player::Init()
{ 
	m_Hp = kMaxHp;
	m_walkAnimFrame = 0;
	m_jumpAnimFrame = 0;
	m_IdleAnimFrame = 0;
	m_pos = { Game::kScreenWindidth / 2, 600 };
	m_dir = kDirRight;
	m_JumpPower = 0;
	m_pSpear = nullptr;
	m_pSceneGameOver = nullptr;
	isJump = true;
	isMove = false;

	m_Runhandle = LoadGraph("image/character/Run.png");
	m_Waitinghandle = LoadGraph("image/character/Idle.png");
	m_Jumphamdle = LoadGraph("image/character/Jump.png");
	m_Deadhandle = LoadGraph("image/character/Dead.png");
}

void Player::Update()
{
	//�p�b�g�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	if (pad & PAD_INPUT_LEFT)
	{
		move.x -= kSpeed;
		m_dir = kDirLeft;
		isMove = true;
	}
	if (pad & PAD_INPUT_RIGHT)
	{
		move.x += kSpeed;
		m_dir = kDirRight;
		isMove = true;
	}

	// �W�����v�{�^���������Ă��āA�n�ʂɂ��Ă�����W�����v
	if (pad & PAD_INPUT_C)
	{
		m_JumpPower = 20;
		isJump = true;
	}

	move.y -= m_JumpPower;
	m_JumpPower -= 1;


	m_pos += move;

	if (m_pos.y > 600)
	{
		m_pos.y = 600;
		m_JumpPower = 0;
	}

	////if (pad & PAD_INPUT_B)
	////{
	////	Attack();
	////}
	////�󒆂ɂ���
	//if (isJump == true)
	//{
	//	move.y += kGravity;
	//	m_pos.x += move.x;
	//	// �����瓖�����������`�F�b�N����
	//	Rect chipRect;
	//	if (m_pMap->IsCollision(GetRect(), chipRect))
	//	{
	//		// ������Ԃ������ꍇ�̏���
	//		// ���E�ǂ��炩�瓖�����������f�o�b�O�\��
	//		if (move.x > 0.0f) // �v���C���[���E�����Ɉړ����Ă���
	//		{
	//			printfDx("�E�����Ԃ�����\n");
	//			m_pos.x = chipRect.left - kWidth / 2 - 1; // �}�b�v�`�b�v�̍������傤�ǂԂ���Ȃ��ʒu�ɕ␳
	//			
	//		}
	//		else if (move.x < 0.0f)
	//		{
	//			printfDx("�������Ԃ�����\n");
	//			m_pos.x = chipRect.right + kWidth / 2 + 1; // �}�b�v�`�b�v�̉E�����傤�ǂԂ���Ȃ��ʒu�ɕ␳
	//		}
	//	}
	//	m_pos.y += move.y;
	//}
	////�n�ʂɕt���Ă�
	//else if(isJump == false)
	//{
	//	
	//	m_pos += move;
	//	Rect chipRect;
	//	if (m_pMap->IsCollision(GetRect(), chipRect))
	//	{
	//		// ������Ԃ������ꍇ�̏���
	//		// ���E�ǂ��炩�瓖�����������f�o�b�O�\��
	//		if (move.x > 0.0f) // �v���C���[���E�����Ɉړ����Ă���
	//		{
	//			printfDx("�E�����Ԃ�����\n");
	//			m_pos.x = chipRect.left - kWidth / 2 - 1; // �}�b�v�`�b�v�̍������傤�ǂԂ���Ȃ��ʒu�ɕ␳
	//		}
	//		else if (move.x < 0.0f)
	//		{
	//			printfDx("�������Ԃ�����\n");
	//			m_pos.x = chipRect.right + kWidth / 2 + 1; // �}�b�v�`�b�v�̉E�����傤�ǂԂ���Ȃ��ʒu�ɕ␳
	//		}
	//	}
	//}

	
	
	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	
	//���̈ړ�
	if (m_pSpear != nullptr)
	{
		m_pSpear->Update();
		m_SpearRect = m_pSpear->GetColRect();
	}
}

void Player::Draw()
{
	if (isMove == true)
	{
		//�����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimaFrameCycle) m_walkAnimFrame = 0; isMove = false;

		RunMotion();
	}
	else if(isMove == false)
	{
		//���u�A�j���[�V����
		m_IdleAnimFrame++;
		if (m_IdleAnimFrame >= kIdleAnimFrameCycle) m_IdleAnimFrame = 0;
		IdleMotion();
	}
#ifdef _DEBUG
	//�@�����蔻��̕\��
	m_colRect.Draw(GetColor(0, 0, 255), false);
	DrawFormatString(80, 80, GetColor(255, 255, 255), "�v���C���[�̍��W(%.2f,%.5f)", m_pos.x, m_pos.y);
#endif
}

void Player::End()
{
	DeleteGraph(m_Runhandle);
	DeleteGraph(m_Jumphamdle);
	DeleteGraph(m_Waitinghandle);
	DeleteGraph(m_Deadhandle);
}

void Player::Attack()
{
	

	m_pSpear = new Spear(m_pos);
}

void Player::IdleMotion()
{
	int animFrame = m_IdleAnimFrame / kIdleAnimFrameNum;
	int srcX = kUseIdleFrame[animFrame] * kIdleWideth;
	int srcY = kIdleHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kIdleWideth, kIdleHeight,2.0, 0.0, m_Waitinghandle, true, false);

}

void Player::RunMotion()
{
	int animFrame = m_walkAnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;
	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_Runhandle, true, false);
}

float Player::GetLeft()
{
	return m_pos.x - kWidth / 2;
}

float Player::GetRight()
{
	return m_pos.x + kWidth / 2;
}

float Player::GetTop()
{
	return m_pos.y - kHeight/2;
}

float Player::GetBottom()
{
	return m_pos.y + kHeight/2;
}

Rect Player::GetRect()
{
	Rect rect;
	rect.top = GetTop();
	rect.bottom = GetBottom();
	rect.left = GetLeft();
	rect.right = GetRight();

	return rect;
}

void Player::OnDamege()
{
	m_Hp -= 1;
	if (m_Hp == 0)
	{
		m_Hp = 0;
	}
}
