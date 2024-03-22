#include "StageBase.h"
#include<cassert>
#include <Dxlib.h>
#include "../../Util/game.h"

namespace
{	
	//**** テクスチャ情報 ****//
	// 恐竜ステージ
	const char* kDinoFile = "Data/Image/Stage/Dino/Dino.png";
	const char* kDinoBgFile = "Data/Image/Stage/Dino/DinoBg.png";
	const char* kDinoFilePath = "Data/Image/Stage/Dino/DinoMap.csv";
	// エルフステージ
	const char* kElfFile = "Data/Image/Stage/elf/elf.png";
	const char* kElfBgFile = "Data/Image/Stage/elf/Background.png";
	const char* kElfFilePath = "Data/Image/Stage/elf/elf.csv";

	// マッチョステージ
	const char* kMachoFile = "Data/Image/Stage/macho/macho.png";
	const char* kMachoBgFile = "Data/Image/Stage/macho/Background_0.png";
	const char* kMachoFilePath = "Data/Image/Stage/macho/macho.csv";

	// 魔女ステージ
	const char* kWizardFile = "Data/Image/Stage/Wizard/Wizard.png";
	const char* kWizardBgFile = "Data/Image/Stage/Wizard/WizardBg0.png";
	const char* kWizardFilePath = "Data/Image/Stage/Wizard/Wizard.csv";

	//**** マップ情報 ****//
	// マップチップ一つのサイズ
	constexpr int kMapChipSize = 64;

	// マップのタテヨコのマップチップの数
	constexpr int kMapHeight = 16;
	constexpr int kMapWidth = 30;
}

StageBase::StageBase(int StageNo):
	m_handle(-1),
	m_bgHandle(-1),
	m_subPos(-1),
	m_startX(0),
	m_startY(700),
	m_endX(Game::kScreenWidth),
	m_endY(0),
	m_stageNo(StageNo),
	m_filePath("")
{
}

StageBase::~StageBase()
{
}

void StageBase::Init()
{
	// マップの状態
	enum StageState
	{
		DinoStage = 1,	// 恐竜ステージ
		ElfStage,		// エルフステージ
		MachoStage,		// マッチョステージ
		WizardStage,	// 魔女ステージ
	};

	switch (m_stageNo)
	{
	case static_cast<int> (DinoStage) :	// 恐竜ステージ
		m_handle = LoadGraph(kDinoFile);
		m_bgHandle = LoadGraph(kDinoBgFile);
		m_filePath = kDinoFilePath;
		m_subPos = 0;
		break;
	case static_cast<int> (ElfStage):		// エルフステージ
		m_handle = LoadGraph(kElfFile);
		m_bgHandle = LoadGraph(kElfBgFile);
		m_filePath = kElfFilePath;
		m_subPos = 0;
		break;
	case static_cast<int> (MachoStage):	// マッチョステージ
		m_handle = LoadGraph(kMachoFile);
		m_bgHandle = LoadGraph(kMachoBgFile);
		m_filePath = kMachoFilePath;
		m_subPos = 0;
		break;
	case static_cast<int> (WizardStage):	// 魔女ステージ
		m_handle = LoadGraph(kWizardFile);
		m_bgHandle = LoadGraph(kWizardBgFile);
		m_filePath = kWizardFilePath;
		m_subPos = 0;
		break;
	default:
		break;
	}

	assert(m_handle != -1);
	assert(m_bgHandle != -1);
	MapRead();
}

void StageBase::Update()
{
}

void StageBase::Draw()
{
	DrawExtendGraph(0, 0 - m_subPos, Game::kScreenWidth, Game::kScreenHeight - m_subPos, m_bgHandle, false);

	for (auto& data : m_data)
	{
		int scrX = data.m_chipNo % 16;
		int scrY = data.m_chipNo / 16;
		DrawRectGraph(static_cast<int>(data.m_pos.x), static_cast<int>(data.m_pos.y) + 10,
			scrX * kMapChipSize, scrY * kMapChipSize,
			kMapChipSize, kMapChipSize,
			m_handle,
			true, false);

	//  printfDx("%d\n", static_cast<int>(data.m_pos.y));
	}

	
}

int StageBase::MapRead()
{
	if (m_filePath == "") return 0;

	FILE* fp;

	// csvファイルを読み込んで数字の配列にしたい
	
	errno_t error = fopen_s(&fp, m_filePath, "r");

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

		Vec2 pos = { static_cast<float>(X),static_cast<float>(Y) };

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
