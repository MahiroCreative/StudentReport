#pragma once
#include "Game.h"
#include "Rect.h"
#include "Player.h"
// �}�b�v�̍\����

class Map
{
public:
	Map();
	~Map();

	void Init();
	void Update();
	void Draw();

	// �v���C���[�Ɠ������Ă��邩����
	bool IsColPlayer();

	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const noexcept { return m_colRect; }

	void setPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }

	// �w�肵����`�Ɠ������Ă��邩����
	// �Q�Ƃ��g�p���ĂԂ������}�b�v�`�b�v�̋�`�����擾���� chipRect
	bool IsCollision(Rect rect, Rect& chipRect);

private:

	Player* m_pPlayer;

	//map�̃n���h��
	int m_Handle;

	//�O���t�B�b�N�Ɋ܂܂��}�b�v�`�b�v�̐�
	int m_MapNumX;
	int m_MapNumY;

	//�����蔻��p�̋�`
	Rect m_colRect;
};

