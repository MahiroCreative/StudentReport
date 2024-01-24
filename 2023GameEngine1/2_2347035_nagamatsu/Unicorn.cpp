#include "Unicorn.h"]
#include "Player.h"
#include "DxLib.h"

namespace
{
	constexpr int kWorkWideth = 64;
	constexpr int kWorkHeight = 59;
	constexpr int kAttackWideth = 66;
	constexpr int kAttackHeight = 59;

	//玉のサイズ
	constexpr int kBallWideth = 32;
	constexpr int kBallHeight = 32;

	//移動速度
	constexpr int kSpeed = 5;
	//玉の速度
	constexpr int kBallSpeed = 8;

	//移動時のアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//攻撃時のアニメーション
	constexpr int kAttackUseFrame[] = { 0,1,2,3,4 };

	//移動時アニメーション１コマのフレーム数
	constexpr int kAnimaFrameNum = 8;
	//攻撃時アニメーション１コマのフレーム数
	constexpr int kAttackAnimFrameNum = 5;

	//移動時アニメーション１サイクルのフレーム数
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//攻撃時アニメーション1サイクルのフレーム数
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
	
	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = m_playerPos - m_pos;
	
	//ベクトルの長さをkSpeedにしてやる
	//ベクトルの正規化　長さを１にする
	toTarget.normalize();

	if (m_playerPos.x > m_pos.x)
	{
		m_dir = 0;
	}
	else if (m_playerPos.x < m_pos.x)
	{
		m_dir = 1;
	}
	//kSpeedでかける
	m_vec = toTarget * kSpeed;
	m_pos += m_vec;

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	workMotion();
}

void Unicorn::Draw()
{
#ifdef _DEBUG
	//　当たり判定の表示
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
	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = m_playerPos - m_pos;

	//ベクトルの長さをkSpeedにしてやる
	//ベクトルの正規化　長さを１にする
	toTarget.normalize();
	//kSpeedでかける
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
