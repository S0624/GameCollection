#include "Pad.h"
#include "DxLib.h"

namespace
{
	constexpr int kLogNum = 16;
	// 入力ログ	0が最新の状態
	int padLog1[kLogNum];

	int padLog2[kLogNum];
}

namespace Pad
{
	// パッドの入力状態取得
	void Update()
	{
		// 現在のパッドの状態を取得
		int padState1 = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// ログの更新
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			padLog1[i] = padLog1[i-1];
		}
		// 最新の状態
		padLog1[0] = padState1;


		// 現在のパッドの状態を取得
		int padState2 = GetJoypadInputState(DX_INPUT_PAD2);

		// ログの更新
		for (int i = kLogNum - 1; i >= 1; i--)
		{
			padLog2[i] = padLog2[i - 1];
		}
		// 最新の状態
		padLog2[0] = padState2;
	}

	// 押し下げ判定
	bool IsPress(int button,int padNum)
	{
		if(padNum == 1) return (padLog1[0] & button);
			
		if(padNum == 2) return (padLog2[0] & button);

		return false;
	}
	// トリガー判定
	bool IsTrigger(int button, int padNum)
	{
		bool isNow = false;	// 現在の状態
		bool isLast = false;	// １フレーム前の状態

		if (padNum == 1)
		{
			isNow = (padLog1[0] & button);
			isLast = (padLog1[1] & button);
		}

		if (padNum == 2)
		{
			isNow = (padLog2[0] & button);
			isLast = (padLog2[1] & button);
		}


		return (isNow && !isLast);
	}
	// 離した判定
	bool IsRelase(int button, int padNum)
	{
		bool isNow = false;	// 現在の状態
		bool isLast = false;	// １フレーム前の状態

		if (padNum == 1)
		{
			isNow = (padLog1[0] & button);
			isLast = (padLog1[1] & button);
		}

		if (padNum == 2)
		{
			isNow = (padLog2[0] & button);
			isLast = (padLog2[1] & button);
		}

		return (!isNow && isLast);
	}
}