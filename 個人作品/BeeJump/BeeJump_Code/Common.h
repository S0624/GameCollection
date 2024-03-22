#pragma once
#include <DxLib.h>
#include<tchar.h>
#include "Util/game.h"
#include "Util/Pad.h"
#include "Util/SoundManager.h"

namespace Color
{
	const int kBlack = 0x000000;		// ��
	const int kBrown = 0xA52A2A;		// ��
	const int kRed = 0xff0000;			// ��
	const int kPeach = 0xff00ff;		// ��
	const int kGreen = 0x00ff00;		// ��
	const int kBlue = 0x0000ff;			// ��
	const int kLightBlue = 0x00ffff;	// ��
	const int kYellow = 0xffff00;		// ��
	const int kYellowGreen = 0x9ACD32;	// ����
	const int kWhite = 0xffffff;		// ��
}

namespace font
{
	//�t�H���g�̓ǂݍ���
	void MyFontPath(const TCHAR* path);
};

// �I�΂ꂽ��Փx
enum Mode
{
	Easy,		// �C�[�W�[
	Normal,		// �m�[�}��
	Hard,		// �n�[�h
	Endless,	// �G���h���X
};