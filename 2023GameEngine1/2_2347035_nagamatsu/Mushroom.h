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

    //メンバー変数にアクセスする
    void SetPlayer(Player* pPlayer) { m_pPlayer = pPlayer; }
    //当たり判定の矩形を取得する
    Rect GetColRect() const { return m_colRect; }
    //当たり判定を作る
    void UpdateCollision();
    //生きているかどうか
    bool isExist() const { return m_isExist; }

    //出現場所の指定
    void start();

    //HP
    int Hp;

private:
    Player* m_pPlayer;

    //画像のハンドル
    int m_handle;
    //一定時間で消える
    int m_frameCount;
    //プレイヤーの方向
    int m_dir;
    //死んだ方向
    int m_Dieddir;
    //存在しているかどうか
    bool m_isExist;
  

    //歩きアニメーション
    int m_AnimFrame;
    //死亡アニメーション
    int m_DiedAnimFrame;

    //エネミーの座標
    Vec2 m_pos;
    //移動量 1フレーム当たりの移動ベクトルを入れる　　　
    Vec2 m_vec;
    //当たり判定の矩形
    Rect m_colRect;

    //プレイヤーの座標
    Vec2 m_playerPos;

    //歩くモーション
    void MoveMotion();
    //死亡モーション
    void DiedMotion();
};


