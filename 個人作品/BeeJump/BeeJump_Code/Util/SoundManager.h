#pragma once

// サウンド関連処理
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		TitleBGM,		// タイトル画面のBGM
		SelectBGM,		// 選択画面のBGM
		MainBGM,		// ゲーム画面のBGM
		ResultBGM,		// リザルト画面のBGM

		// SE
		PushButton,
		Cursor,
		Jump,
		GameClear,
		GameOver,

		SoundId_Num
	}SoundId;

	// ロード、アンロード
	void LoadSound();
	void UnLoadSound();

	// BGMの再生
	void StartBGM(SoundId id, int volume = 255);
	void StopBGM(SoundId id);
	void LoopBGM(SoundId id);
	void SetLoopBGM(int loopTime,SoundId id);

	// 効果音の再生
	void PlaySE(SoundId id);

	// 音量設定	0~255
	void SetVolume(SoundId id, int volume);
}