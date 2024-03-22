#pragma once

// サウンド関連処理
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		TitleBgm,		// タイトル画面のBGM
		SelectBgm,		// 選択画面のBGM
		MainBgm,		// 戦闘画面のBGM
		ResultBgm,		// リザルト画面のBGM

		// SE
		// だいなそー
		DinoAttack1,
		DinoAttack2,
		DinoAttack3,
		DinoAttack4,

		// エルフ
		ElfAttack1,
		ElfAttack2,
		ElfAttack3,
		ElfAttack4,

		// きんにくん
		KinnikuAttack1,
		KinnikuAttack2,
		KinnikuAttack3,
		KinnikuAttack4,

		// 魔女
		WitchAttack1,
		WitchAttack2,
		WitchAttack3,
		WitchAttack4,
		WitchCharge,

		SoundId_Num
	}SoundId;

	// ロード、アンロード
	void load();
	void unload();

	// BGMの再生
	void startBgm(SoundId id, int volume = 255);
	void stopBgm(SoundId id);
	void loopBgm(SoundId id);

	// 効果音の再生
	void play(SoundId id);

	// 音量設定	0~255
	void setVolume(SoundId id, int volume);
}


