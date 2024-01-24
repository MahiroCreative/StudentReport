#pragma once

class SceneStage1;
class SceneStage2;

class SceneSelect
{
public:
	SceneSelect();
	~SceneSelect();

	void Init();
	void Update();
	void Draw();
	void End();

	//シーンを終了させたいか
	bool IsSceneEnd() const;

	int selectNum;
private:
	SceneStage1* m_pSceneStage1;
	SceneStage2* m_pSceneStage2;

	float m_cursorX;
	float m_cursorY;


	int m_handle;

	bool m_isSceneEnd;	//シーン終了フラグ
	//true ; タイトルを終了してゲームへ
};

