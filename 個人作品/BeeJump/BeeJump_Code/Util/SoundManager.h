#pragma once

// �T�E���h�֘A����
namespace Sound
{
	typedef enum SoundId
	{
		// BGM
		TitleBGM,		// �^�C�g����ʂ�BGM
		SelectBGM,		// �I����ʂ�BGM
		MainBGM,		// �Q�[����ʂ�BGM
		ResultBGM,		// ���U���g��ʂ�BGM

		// SE
		PushButton,
		Cursor,
		Jump,
		GameClear,
		GameOver,

		SoundId_Num
	}SoundId;

	// ���[�h�A�A�����[�h
	void LoadSound();
	void UnLoadSound();

	// BGM�̍Đ�
	void StartBGM(SoundId id, int volume = 255);
	void StopBGM(SoundId id);
	void LoopBGM(SoundId id);
	void SetLoopBGM(int loopTime,SoundId id);

	// ���ʉ��̍Đ�
	void PlaySE(SoundId id);

	// ���ʐݒ�	0~255
	void SetVolume(SoundId id, int volume);
}