#pragma once
class Timer
{
public:
	Timer();
	~Timer();

	void Init();
	void Update();
	void Draw();
	void End();

	int GetTimer() const { return timer; }

private:

	//30�b��������
	bool isTimeUp;

	//�^�C�}�[
	float timer;
};

