#pragma once
class SceneStart
{
public:
	SceneStart();
	~SceneStart();

	void Init();
	void Update();
	void Draw();
	void End();

	//シーンを終了させたいか
	bool IsSceneEnd() const;

private:
	bool m_isSceneEnd;	//シーン終了フラグ
	//true ; タイトルを終了してゲームへ
	
	//タイトル画面に表示する画像のハンドル
	int m_handle;

	//フェードイン、アウト
	int m_fadeAlpha;

	//カーソルの位置
	float cursorY;

};



