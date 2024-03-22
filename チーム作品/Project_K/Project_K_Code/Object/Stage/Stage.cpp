#include <Dxlib.h>
#include<vector>
#include<iostream>
#include<cassert>
#include "Stage.h"
#include "../../Util/game.h"

namespace
{
	// テクスチャ情報
	const char* kFileName = "Data/Image/Stage/Wizard/Wizard.png";
	const char* kBgFileName = "Data/Image/Stage/Wizard/WizardBg0.png";

	// マップチップ一つのサイズ
	constexpr int kMapChipSize = 64;

	// マップのタテヨコのマップチップの数
	constexpr int kMapHeight = 16;
	constexpr int kMapWidth = 30;
}

Stage::Stage() : 
	m_pos(0, 700),
	m_handle(-1),
	m_bgHandle(-1)

{
}

Stage::~Stage()
{
}

void Stage::Init()
{
	m_handle = LoadGraph(kFileName, false);
	m_bgHandle = LoadGraph(kBgFileName, false);
	MapRead();
}

void Stage::Update()
{
	
}

void Stage::Draw()
{
	DrawExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, m_bgHandle, false);

	for (auto& data : m_data)
	{
		int scrX = data.m_chipNo % 16;
		int scrY = data.m_chipNo / 16;
		DrawRectGraph(static_cast<int>(data.m_pos.x), static_cast<int>(data.m_pos.y),
			scrX * kMapChipSize, scrY * kMapChipSize,
			kMapChipSize, kMapChipSize,
			m_handle,
			true, false);
	}
}

int Stage::MapRead()
{
	 // csvファイルを読み込んで数字の配列にしたい

	 FILE* fp;

	 errno_t error = fopen_s(&fp, "Data/Image/Stage/Wizard/Wizard.csv","r");
	 
	 // 1文字ずつ読み込んで表示
	 int chr;

	 // ファイルから1文字ずつ読み込んでファイルの終わりまでループ
	 std::vector<int> dataTbl;
	 // 横の要素数
	 int wNum = -1;	// 未確定
	 // 横の要素数数えるよう
	 int tempW = 0;

	 int tempNum = 0;

	 while (true)
	 {
		 chr = fgetc(fp);	// 1文字読み込み
		 // 区切り文字が見つかった
		 if (chr == ',' ||
			 chr == '\n' ||
			 chr == EOF)
		 {
			 // dataTblにデータを入れる
			 dataTbl.push_back(tempNum);
			 tempNum = 0;

			 // ファイルの終端に来たら終了
			 if (chr == EOF)
			 {
				 break;
			 }
			 else if (chr == ',')
			 {
				 tempW++;	// 要素数数える
			 }
			 else     // chr == '\n'
			 {
				 tempW++;	// 要素数数える
				 if (wNum < 0)
				 {
					 wNum = tempW;		// 要素数確定
				 }
				 else
				 {
				 //  assert(wNum == tempW);	// 横の要素数は固定なので違ったらassert
				 }
				 tempW = 0;
			 }

			 // まだ終わってないので続けて読み込み
			 continue;
		 }

		 // データは数字のみのはず
		 assert(chr >= '0' && chr <= '9');

		 // 数字なのは確定
		 // 文字列を数値に変換したい

		 tempNum = (tempNum * 10) + chr - '0';

		 // データの区切りが見つかった時点でそこまでがデータのひとまとまり
	 }

	 MapInfo mapinfo;
	 // m_dataにdataTblの中身を入れてる
	 for (int i = 0; i < dataTbl.size(); i++)
	 {
		 int X = (i % kMapWidth) * kMapChipSize;
		 int Y = (i / kMapWidth) * kMapChipSize;

		 Vec2 pos = { static_cast<float>(X),static_cast<float>(Y)};

		 mapinfo.m_pos = pos;
		 mapinfo.m_chipNo = dataTbl[i];

		 m_data.push_back(mapinfo);
	 }

	 // dataTblに正しく数字が入っているかチェック
	 int count = 0;
	 for (auto& num : dataTbl)
	 {
		 if (count % wNum == 0)
		 {
			 printf("\n");
		 }
		 else
		 {
			 printf(",");
		 }
		 printf("%d, ", num);
		 count++;
	 }

	 // ファイルを閉じる
	 fclose(fp);

	 return 0;
}
