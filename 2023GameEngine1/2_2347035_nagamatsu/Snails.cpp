#include "Snails.h"
#include "Player.h"
#include "DxLib.h"

namespace
{
	//玉の速さ
	constexpr float kSpeed = 2.0f;
	//玉のサイズ
	constexpr int kBallWideth = 32;
	constexpr int kBallHeight = 32;

	//画像のサイズ
	constexpr int kWidth = 47;
	constexpr int kHeight = 22;

	//攻撃時のアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };

	//攻撃時アニメーション１コマのフレーム数
	constexpr int kAnimaFrameNum = 8;

	//攻撃時アニメーション１サイクルのフレーム数
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

	//ターゲット位置
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
	//　当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
	m_ballRect.Draw(GetColor(0, 0, 255), false);
#endif

	DrawGraph(m_ballPos.x, m_ballPos.y, m_ballHandle, true);
}

void Snails::TrackingBall()
{
	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = m_playerPos - m_pos;

	//ベクトルの長さをkSpeedにしてやる
	//ベクトルの正規化　長さを１にする
	toTarget.normalize();
	//kSpeedでかける
	m_vec = toTarget * kSpeed;

	m_ballPos += m_vec;
}

void Snails::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
		//中心座標を指定して当たり判定のRectを生成する
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
