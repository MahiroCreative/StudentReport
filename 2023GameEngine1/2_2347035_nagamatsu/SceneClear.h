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

	//�V�[�����I�������邩�ǂ���
	bool IsSceneEnd() const;

private:

	int m_handel;
	bool m_isSceneEnd;	//�V�[���I���t���O
	//true ; �^�C�g�����I�����ăQ�[����

};

