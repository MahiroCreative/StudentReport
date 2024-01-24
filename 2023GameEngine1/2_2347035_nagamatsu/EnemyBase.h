#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>

class Player;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init();

	virtual void Update();
	virtual void Draw();

	bool isExist() const { return m_isExist; }

	//�ʒu�̎擾
	Vec2 GetPos() const { return m_pos; }

	//�����蔻��̋�`���擾����
	Rect GetColRect() const { return m_colRect; }
	//�G�L�����N�^�[���X�^�[�g������
	virtual void start() = 0;

protected:

	//private:�@�p���悩����Q�Ƃł��Ȃ�
protected: //�p���悩��Q�Ƃł���
	int m_handle; //�O���t�B�b�N�̃n���h��

	bool m_isExist; //���݂��邩�t���O(�g�p�����ǂ���)

	//�\���ʒu
	Vec2 m_pos;
	//�����蔻��̋�`
	Rect m_colRect;
	//�ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
	Vec2 m_vec;
};

