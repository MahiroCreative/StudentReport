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
	//�V�[�����I������������
	bool IsSceneEnd() const;

private:
	int m_handle;

	bool m_isSceneEnd;	//�V�[���I���t���O
	//true ; �^�C�g�����I�����ăQ�[����
};

