#include "Timer.h"
#include "DxLib.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::Init()
{
	timer = 1800.0f;
	isTimeUp = false;
}

void Timer::Update()
{
	if (timer <= 0)
	{
		timer = 0;
		isTimeUp = true;
	}

	timer--;
}

void Timer::Draw()
{
	DrawFormatString(100,100,GetColor(255, 255, 255),"Žc‚èŽžŠÔ:(%.2f)", timer/60);
}

void Timer::End()
{
}
