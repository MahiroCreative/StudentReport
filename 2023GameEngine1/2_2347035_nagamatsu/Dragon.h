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

    //メンバー変数にアクセスする
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    //当たり判定の矩形を取得する
    Rect GetColRect() const { return m_colRect; }
    //当たり判定を作る
    void UpdateCollision();

    //HP
    int Hp;

private:
    Player* m_pPlayer;

    //画像のハンドル
    int m_handle;

    //プレイヤーの方向
    int m_dir;
    //死んだ方向
    int m_Dieddir;
    //存在しているかどうか
    bool m_isExist = true;
    //端まで行ったか
    bool m_isEdge;

    //歩きアニメーション
    int m_AnimFrame;
    //ジャンプアニメーション
    int m_DiedAnimFrame;

    //エネミーの座標
    Vec2 m_pos;
    //移動量 1フレーム当たりの移動ベクトルを入れる　　　
    Vec2 m_vec;
    //当たり判定の矩形
    Rect m_colRect;

    //歩くモーション
    void MoveMotion();
    //死亡モーション
    void DiedMotion();
};


