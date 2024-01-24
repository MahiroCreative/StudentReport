#pragma once
class SceneClear
{
public:
	SceneClear();
	~SceneClear();

	void Init();
	void Update();
	void Draw();
	void End();

	//シーンを終了させるかどうか
	bool IsSceneEnd() const;

private:

	int m_handel;
	bool m_isSceneEnd;	//シーン終了フラグ
	//true ; タイトルを終了してゲームへ

};

