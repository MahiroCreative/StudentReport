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

	//�V�[�����I������������
	bool IsSceneEnd() const;

private:

	bool m_isGameOver;  //�Q�[���I�[�o�[���ǂ����̃t���O
};

