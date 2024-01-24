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
	//‘¶İ‚µ‚È‚¢“G‚Ìˆ—‚Í‚µ‚È‚¢
	if (!m_isExist) return;


}

void EnemyBase::Draw()
{
	float fNum = 1.2f;  //32bit
	double dNum = 1.2;  //64bit

	//‘¶İ‚µ‚È‚¢“G‚Í•`‰æ‚µ‚È‚¢
	if (!m_isExist) return;
}
