#include "DxLib.h"
#include "Flyingeye.h"
#include "Game.h"
#include "Player.h"
namespace
{
	//初期の高さ
	constexpr int kInitialHeight = 500;

	//速さ
	float kSpeed = 4.0f;
	//画像のサイズ
	constexpr int kWidth = 150;
	constexpr int kHeight = 33;

	//移動時のアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };

	//移動時アニメーション１コマのフレーム数
	constexpr int kAnimaFrameNum = 8;

	//移動時アニメーション１サイクルのフレーム数
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

	//当たり判定の更新
	UpdateCollision();
}

void Flyingeye::Draw()
{
	if (!m_isExist) return;

	m_AnimFrame++;
	if (m_AnimFrame >= kAnimaFrameCycle) m_AnimFrame = 0;
	MoveMotion();

#ifdef _DEBUG
	//　当たり判定の表示
	m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
}

void Flyingeye::start()
{
	m_isExist = true;

	m_pos.x = m_pos.x = static_cast<float>(GetRand(Game::kScreenWindidth - kWidth) + kWidth / 2);
	m_pos.y = static_cast<float>(-kHeight / 2); //画面上から入ってくる

	Vec2 playerPos = m_pPlayer->GetPos();

	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = playerPos - m_pos;

	//ベクトルの長さをkSpeedにしてやる
	//ベクトルの正規化　長さを１にする
	toTarget.normalize();
	//kSpeedでかける
	m_vec = toTarget * kSpeed;
}

void Flyingeye::UpdateCollision()
{
	//	m_colRect.SetLT(m_pos.x, m_pos.y, width, height);
	//中心座標を指定して当たり判定のRectを生成する
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth / 2, kHeight );
}

void Flyingeye::MoveMotion()
{
	int animFrame = m_AnimFrame / kAnimaFrameNum;
	int srcX = kUseFrame[animFrame] * kWidth;
	int srcY = kHeight * m_dir;

	DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), srcX, srcY, kWidth, kHeight, 2.0, 0.0, m_handle, true, false);
}
