#pragma once
class Bg
{
public:
	Bg();
	~Bg();

	void Update();
	void Draw();

private:
	//Bgのハンドル
	int m_Handle;
};

