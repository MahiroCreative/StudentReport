#include "Map.h"
#include "DxLib.h"
#include "Player.h"
#include "Rect.h"

namespace
{
	//�}�b�v�`�b�v�̑傫��
	constexpr int kChipWidth = 40;
	constexpr int kChipHeight = 40;

	//�c���̃`�b�v�̐�
	//�X�N���[�����������̂ŉ�ʃT�C�Y��640*480���L������
	constexpr int kChipNumX = 32;
	constexpr int kChipNumY = 18;

	//�}�b�v�`�b�v�̔z����
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,0,1,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,0,1,2,3,36},
		{36,3,7,8,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,7,8,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,36},
		{36,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,36},
		{36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36},

	};
}

Map::Map() :m_Handle(-1), m_MapNumX(0), m_MapNumY(0)
{
	m_Handle = LoadGraph("image/map/texture.png");
	//�}�b�v�`�b�v�̐��𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_Handle, &graphW, &graphH);

	m_MapNumX = graphW / kChipWidth;
	m_MapNumY = graphH / kChipHeight;
}

Map::~Map()
{
}

void Map::Init()
{
	
}

void Map::Update()
{
	IsColPlayer();
}

void Map::Draw()
{

	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			//�}�b�v��񂩂�u���`�b�v���Ƃ��Ă���
			int chipNo = kChipData[y][x];

			// �`�b�v���Ȃ��ꍇ�͂��������o���Ȃ�
			if (chipNo == 3) continue;

			//�}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_MapNumX);
			int srcY = kChipHeight * (chipNo / m_MapNumY);

			DrawRectGraph(x * kChipWidth, y * kChipHeight, srcX, srcY, kChipWidth, kChipHeight, m_Handle, true);
#ifdef _DEBUG
			//�@�����蔻��̕\��
			m_colRect.Draw(GetColor(0, 0, 255), false);
#endif
		}
	}
}

bool Map::IsColPlayer()
{
	float playerLeft = m_pPlayer->GetLeft();
	float playerRight = m_pPlayer->GetRight();
	float playerTop = m_pPlayer->GetTop();
	float playerBottom = m_pPlayer->GetBottom();

	for (int x = 0; x < kChipNumX; x++)
	{
		// �����̏������H�v���Ă����Ə����𑬂�

		for (int y = 0; y < kChipNumY; y++)
		{
			// �ǈȊO�Ƃ͓�����Ȃ�
			if (kChipData[y][x] == 3) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			// ��΂ɓ�����Ȃ��ꍇ����
			if (chipLeft > playerRight) continue;
			if (chipTop > playerBottom) continue;
			if (chipRight < playerLeft) continue;
			if (chipBottom < playerTop) continue;

			// ������̃`�b�v�Ɠ������Ă�����I��
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}

bool Map::IsCollision(Rect rect, Rect& chipRect)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		// �����̏������H�v���Ă����Ə����𑬂�

		for (int y = 0; y < kChipNumY; y++)
		{
			// �ǈȊO�Ƃ͓�����Ȃ�
			if (kChipData[y][x] == 3) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			// ��΂ɓ�����Ȃ��ꍇ����
			if (chipLeft > rect.right) continue;
			if (chipTop > rect.bottom) continue;
			if (chipRight < rect.left) continue;
			if (chipBottom < rect.top) continue;

			// �Ԃ������}�b�v�`�b�v�̋�`��ݒ肷��
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			// ������̃`�b�v�Ɠ������Ă�����I��
			return true;
		}
	}
	// �S�Ẵ`�b�v���`�F�b�N����1���������Ă��Ȃ���Γ������Ă��Ȃ�
	return false;
}
