#pragma once
#include "Player.h"
#include "Vec2.h"
#include "Rect.h"
class Mushroom
{
public:
    Mushroom();
    ~Mushroom();

    void Init();
    void Update();
    void Draw();
    void OnDamege();

    //�����o�[�ϐ��ɃA�N�Z�X����
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    //�����蔻��̋�`���擾����
    Rect GetColRect() const { return m_colRect; }
    //�����蔻������
    void UpdateCollision();
    //�����Ă��邩�ǂ���
    bool isExist() const { return m_isExist; }

    //�o���ꏊ�̎w��
    void start();

    //HP
    int Hp;

private:
    Player* m_pPlayer;

    //�摜�̃n���h��
    int m_handle;
    //��莞�Ԃŏ�����
    int m_frameCount;
    //�v���C���[�̕���
    int m_dir;
    //���񂾕���
    int m_Dieddir;
    //���݂��Ă��邩�ǂ���
    bool m_isExist;
  

    //�����A�j���[�V����
    int m_AnimFrame;
    //���S�A�j���[�V����
    int m_DiedAnimFrame;

    //�G�l�~�[�̍��W
    Vec2 m_pos;
    //�ړ��� 1�t���[��������̈ړ��x�N�g��������@�@�@
    Vec2 m_vec;
    //�����蔻��̋�`
    Rect m_colRect;

    //�v���C���[�̍��W
    Vec2 m_playerPos;

    //�������[�V����
    void MoveMotion();
    //���S���[�V����
    void DiedMotion();
};


