#include "SoundManager.h"
#include <DxLib.h>
#include <vector>

namespace
{
	// サウンドハンドル
	std::vector<int>	m_soundHandle;

	// サウンドファイル名
	const char* const kFileName[Sound::SoundId_Num] =
	{
		// BGM
		"Data/Sound/BGM/Title.mp3",
		"Data/Sound/BGM/Select.mp3",
		"Data/Sound/BGM/Main.mp3",
		"Data/Sound/BGM/Result.mp3",

		// SE
		"Data/Sound/SE/Push.wav",
		"Data/Sound/SE/Cursor.wav",
		"Data/Sound/SE/Jump.wav",
		"Data/Sound/SE/GameClear.mp3",
		"Data/Sound/SE/GameOver.mp3",

	};
}

namespace Sound
{
	void LoadSound()
	{
		// サウンドデータの読み込み
		for (auto& fileName : kFileName)
		{
			int handle = LoadSoundMem(fileName);
			m_soundHandle.push_back(handle);
		}
	}
	void UnLoadSound()
	{
		// サウンドデータの解放
		for (auto& handle : m_soundHandle)
		{
			DeleteSoundMem(handle);
			handle = -1;
		}
	}

	// BGMの再生
	void StartBGM(SoundId id, int volume)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		SetVolume(id, volume);
	}
	void StopBGM(SoundId id)
	{
		StopSoundMem(m_soundHandle[id]);
	}
	void LoopBGM(SoundId id)
	{
		if (CheckSoundMem(m_soundHandle[id]) != 1)
		{
			PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
			//SetVolume(id, volume);
		}
	}
	void SetLoopBGM(int loopTime, SoundId id)
	{
		SetLoopPosSoundMem(loopTime, m_soundHandle[id]);
		if (CheckSoundMem(m_soundHandle[id]) != 1)
		{
			PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
			//SetVolume(id, volume);
		}
	}
	// 効果音の再生
	void PlaySE(SoundId id)
	{
		PlaySoundMem(m_soundHandle[id], DX_PLAYTYPE_BACK, true);
		//SetVolume(id, volume);

	}

	// 音量設定	0~255
	void SetVolume(SoundId id, int volume)
	{
		ChangeVolumeSoundMem(volume, m_soundHandle[id]);
	}
}
