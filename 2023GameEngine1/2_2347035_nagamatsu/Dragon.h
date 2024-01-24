#pragma once
#include "Vec2.h"
#include "Rect.h"
#include "Player.h"

class Dragon
{
public:
    Dragon();
    ~Dragon();

    void Update();
    void Draw();
    void OnDamege();

    //�����o�[�ϐ��ɃA�N�Z�X����
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    //�����蔻��̋�`���擾����
    Rect GetColRect() const { return m_colRect; }
    //�����蔻������
    void UpdateCollision();

    //HP
    int Hp;

private:
    Player* m_pPlayer;

    //�摜�̃n���h��
    int m_handle;

    //�v���C���[�̕���
    int m_dir;
    //���񂾕���
    int m_Dieddir;
    //���݂��Ă��邩�ǂ���
    bool m_isExist = true;
    //�[�܂ōs������
    bool m_isEdge;

    //�����A�j���[�V����
    int m_AnimFrame;
    //�W�����v�A�j���[�V����
    int m_DiedAnimFrame;

    //�G�l�~�[�̍��W
    Vec2 m_pos;
    //�ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
    Vec2 m_vec;
    //�����蔻��̋�`
    Rect m_colRect;

    //�������[�V����
    void MoveMotion();
    //���S���[�V����
    void DiedMotion();
};


