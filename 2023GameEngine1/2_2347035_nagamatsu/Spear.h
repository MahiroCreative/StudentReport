#pragma once
#include "Vec2.h"
#include "Rect.h"

class Spear
{
public:
	Spear(Vec2 pos);
	~Spear();


	//���̓����蔻����擾����
	Rect GetColRect() const noexcept { return m_colRect; }

	void Update();
	void Draw();
private:
	int m_handle;

	//�O���t�B�b�N�̃T�C�Y
	int SpearW, SpearH;

	Rect m_colRect;

	Vec2 m_pos;

	Vec2 m_move;

};

