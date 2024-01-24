#pragma once
class SceneGameOver
{
public:
	SceneGameOver();
	~SceneGameOver();

	void Init();
	void Update();
	void Draw();
	void End();
	//シーンを終了させたいか
	bool IsSceneEnd() const;

private:
	int m_handle;

	bool m_isSceneEnd;	//シーン終了フラグ
	//true ; タイトルを終了してゲームへ
};

