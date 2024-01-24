#include "Mushroom.h"
#include "DxLib.h"
#include "Vec2.h"
#include "Game.h"
#include "Player.h"

namespace
{
	//初期位置
	constexpr float kGroundY = 150.0f;

	//右から出る場合の座標
	constexpr float kRight = 1150.0f;

	//左から出る場合
	constexpr float kLeft = 100.0f;

	float kSpeed = 6.0f;
	//画像のサイズ
	constexpr int kWidth = 150;
	constexpr int kHeight = 150;

	//発生してから消えるまでのフレーム数
	constexpr int kExistFrame = 60 * 5;

	//攻撃・移動時のアニメーション
	constexpr int kUseFrame[] = { 0,1,2,3,4,5,6,7 };
	//死亡時のアニメーション
	constexpr int kDiedUseFrame[] = { 0,1,2,3 };

	//攻撃・移動時アニメーション１コマのフレーム数
	constexpr int kAnimaFrameNum= 8;
	//死亡時アニメーション１コマのフレーム数
	constexpr int kDiedAnimaFrameNum = 4;

	//攻撃・移動時アニメーション１サイクルのフレーム数
	constexpr int kAnimaFrameCycle = _countof(kUseFrame) * kAnimaFrameNum;
	//死亡時アニメーション1サイクルのフレーム数
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
	//当たり判定の更新
	UpdateCollision();
}

void Mushroom::Draw()
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
	//中心座標を指定して当たり判定のRectを生成する
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
	//敵の初期位置からターゲット位置に向かうベクトルを生成する
	//始点から終点に向かうベクトルを求める場合、終点の座標-始点の座標で求める
	Vec2 toTarget = playerPos - m_pos;

	//ベクトルの長さをkSpeedにしてやる
	//ベクトルの正規化　長さを１にする
	toTarget.normalize();
	//kSpeedでかける
	m_vec = toTarget * kSpeed;
}

