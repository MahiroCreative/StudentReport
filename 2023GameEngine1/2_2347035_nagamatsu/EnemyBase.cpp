#include "EnemyBase.h"

EnemyBase::EnemyBase():m_handle(-1),m_isExist(false)
{
}

EnemyBase::~EnemyBase()
{
}

void EnemyBase::Init()
{
}

void EnemyBase::Update()
{
	//存在しない敵の処理はしない
	if (!m_isExist) return;


}

void EnemyBase::Draw()
{
	float fNum = 1.2f;  //32bit
	double dNum = 1.2;  //64bit

	//存在しない敵は描画しない
	if (!m_isExist) return;
}
