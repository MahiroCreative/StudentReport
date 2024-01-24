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

	//�V�[�����I������������
	bool IsSceneEnd() const;

private:
	bool m_isSceneEnd;	//�V�[���I���t���O
	//true ; �^�C�g�����I�����ăQ�[����
	
	//�^�C�g����ʂɕ\������摜�̃n���h��
	int m_handle;

	//�t�F�[�h�C���A�A�E�g
	int m_fadeAlpha;

	//�J�[�\���̈ʒu
	float cursorY;

};



