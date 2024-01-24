#pragma once
class SceneStage2
{
public:
	SceneStage2();
	~SceneStage2();

	void Init();
	void Update();
	void Draw();
	void End();

	//シーンを終了させたいか
	bool IsSceneEnd() const;

private:

	bool m_isGameOver;  //ゲームオーバーかどうかのフラグ
};

