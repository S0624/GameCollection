#pragma once

// コントローラーの入力状態を取得する
namespace Pad
{
	// パッドの入力状態取得
	void Update();

	// 押し下げ判定
	bool IsPress(int button, int padNum);
	// トリガー判定
	bool IsTrigger(int button, int padNum);
	// 離した判定
	bool IsRelase(int button, int padNum);
}
