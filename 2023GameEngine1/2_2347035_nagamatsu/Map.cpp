#include "Map.h"
#include "DxLib.h"
#include "Player.h"
#include "Rect.h"

namespace
{
	//マップチップの大きさ
	constexpr int kChipWidth = 40;
	constexpr int kChipHeight = 40;

	//縦横のチップの数
	//スクロールさせたいので画面サイズを640*480より広くする
	constexpr int kChipNumX = 32;
	constexpr int kChipNumY = 18;

	//マップチップの配列情報
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
	//マップチップの数を数える
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
			//マップ情報から置くチップをとってくる
			int chipNo = kChipData[y][x];

			// チップがない場合はそもそも出さない
			if (chipNo == 3) continue;

			//マップチップのグラフィック切り出し座標
			int srcX = kChipWidth * (chipNo % m_MapNumX);
			int srcY = kChipHeight * (chipNo / m_MapNumY);

			DrawRectGraph(x * kChipWidth, y * kChipHeight, srcX, srcY, kChipWidth, kChipHeight, m_Handle, true);
#ifdef _DEBUG
			//　当たり判定の表示
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
		// ここの処理を工夫してもっと処理を速く

		for (int y = 0; y < kChipNumY; y++)
		{
			// 壁以外とは当たらない
			if (kChipData[y][x] == 3) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			// 絶対に当たらない場合次へ
			if (chipLeft > playerRight) continue;
			if (chipTop > playerBottom) continue;
			if (chipRight < playerLeft) continue;
			if (chipBottom < playerTop) continue;

			// いずれのチップと当たっていたら終了
			return true;
		}
	}
	// 全てのチップをチェックして1つも当たっていなければ当たっていない
	return false;
}

bool Map::IsCollision(Rect rect, Rect& chipRect)
{
	for (int x = 0; x < kChipNumX; x++)
	{
		// ここの処理を工夫してもっと処理を速く

		for (int y = 0; y < kChipNumY; y++)
		{
			// 壁以外とは当たらない
			if (kChipData[y][x] == 3) continue;

			int chipLeft = kChipWidth * x;
			int chipRight = chipLeft + kChipWidth;
			int chipTop = kChipHeight * y;
			int chipBottom = chipTop + kChipHeight;

			// 絶対に当たらない場合次へ
			if (chipLeft > rect.right) continue;
			if (chipTop > rect.bottom) continue;
			if (chipRight < rect.left) continue;
			if (chipBottom < rect.top) continue;

			// ぶつかったマップチップの矩形を設定する
			chipRect.left = chipLeft;
			chipRect.right = chipRight;
			chipRect.top = chipTop;
			chipRect.bottom = chipBottom;

			// いずれのチップと当たっていたら終了
			return true;
		}
	}
	// 全てのチップをチェックして1つも当たっていなければ当たっていない
	return false;
}
