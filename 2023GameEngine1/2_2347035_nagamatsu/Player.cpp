#include "Pad.h"
#include "Player.h"
#include "Rect.h"
#include "DxLib.h"
#include "Map.h"
#include "Game.h"

#define MOVE_FRAME      15          // 移動にかけるフレーム数

namespace
{
	// 重力
	constexpr float kGravity = 0.5f;
	// ジャンプ力
	constexpr float kJumpPower = -8.0f;

	//プレイヤーの最大HP
	constexpr int kMaxHp = 2;

	float kSpeed = 4.0f;
	//キャラクターのサイズ
	constexpr int kWidth = 80;
	constexpr int kHeight = 52;
	//ジャンプ時のキャラクターサイズ
	//constexpr int kJumpWideth = 64;
	//constexpr int kJumpHeight = 64;
	//放置時のキャラクターサイズ
	constexpr int kIdleWideth = 64;
	constexpr int kIdleHeight = 80;
	//死亡時のキャラクターサイズ
	constexpr int kDeadWideth = 80;
	constexpr int kDeadHeight = 64;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//ジャンプのアニメーション
	//constexpr int kUseJumpFrame[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	//放置時のアニメーション
	constexpr int kUseIdleFrame[] = { 0,1,2,3 };
	//死亡時のアニメーション
	constexpr int kUseDeadFrame[] = { 0,1,2,3,4,5,6,7 };


	//アニメーション１コマのフレーム数
	constexpr int kAnimaFrameNum = 8;
	//ジャンプアニメーション１コマのフレーム数
	//constexpr int kJumpAnimFrameNum = 15;
	//待機時アニメーション１コマのフレーム数
	constexpr int kIdleAnimFrameNum = 4;
	//死亡時アニメーション１コマのフレーム数
	constexpr int kDeadAnimFrameNum = 8;

	//アニメーション１サイクルのフレーム数
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//ジャンプアニメーション１サイクルのフレーム数
	//constexpr int kJumpAnimFrameCycle = _countof(kUseJumpFrame) * kJumpAnimFrameNum;
	//放置時アニメーション1サイクルのフレーム数
	constexpr int kIdleAnimFrameCycle = _countof(kUseIdleFrame) * kIdleAnimFrameNum;
	//死亡時アニメーション1サイクルのフレーム数
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
	//パットの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	//移動量を持つようにする
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

	// ジャンプボタンを押していて、地面についていたらジャンプ
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
	////空中にいる
	//if (isJump == true)
	//{
	//	move.y += kGravity;
	//	m_pos.x += move.x;
	//	// 横から当たったかをチェックする
	//	Rect chipRect;
	//	if (m_pMap->IsCollision(GetRect(), chipRect))
	//	{
	//		// 横からぶつかった場合の処理
	//		// 左右どちらから当たったかをデバッグ表示
	//		if (move.x > 0.0f) // プレイヤーが右方向に移動している
	//		{
	//			printfDx("右側がぶつかった\n");
	//			m_pos.x = chipRect.left - kWidth / 2 - 1; // マップチップの左側ちょうどぶつからない位置に補正
	//			
	//		}
	//		else if (move.x < 0.0f)
	//		{
	//			printfDx("左側がぶつかった\n");
	//			m_pos.x = chipRect.right + kWidth / 2 + 1; // マップチップの右側ちょうどぶつからない位置に補正
	//		}
	//	}
	//	m_pos.y += move.y;
	//}
	////地面に付いてる
	//else if(isJump == false)
	//{
	//	
	//	m_pos += move;
	//	Rect chipRect;
	//	if (m_pMap->IsCollision(GetRect(), chipRect))
	//	{
	//		// 横からぶつかった場合の処理
	//		// 左右どちらから当たったかをデバッグ表示
	//		if (move.x > 0.0f) // プレイヤーが右方向に移動している
	//		{
	//			printfDx("右側がぶつかった\n");
	//			m_pos.x = chipRect.left - kWidth / 2 - 1; // マップチップの左側ちょうどぶつからない位置に補正
	//		}
	//		else if (move.x < 0.0f)
	//		{
	//			printfDx("左側がぶつかった\n");
	//			m_pos.x = chipRect.right + kWidth / 2 + 1; // マップチップの右側ちょうどぶつからない位置に補正
	//		}
	//	}
	//}

	
	
	//当たり判定の更新
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth, kHeight);
	
	//槍の移動
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
		//歩きアニメーション
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kAnimaFrameCycle) m_walkAnimFrame = 0; isMove = false;

		RunMotion();
	}
	else if(isMove == false)
	{
		//放置アニメーション
		m_IdleAnimFrame++;
		if (m_IdleAnimFrame >= kIdleAnimFrameCycle) m_IdleAnimFrame = 0;
		IdleMotion();
	}
#ifdef _DEBUG
	//　当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
	DrawFormatString(80, 80, GetColor(255, 255, 255), "プレイヤーの座標(%.2f,%.5f)", m_pos.x, m_pos.y);
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
