#include "SoundManager.h"
#include"DxLib.h"

//サウンドのロード
int SoundManager::LoadSoundFile(const wchar_t* fileName)
{
	std::wstring path = L"../Sound/SE/";
	path += fileName;
	path += L".mp3";
	int handle = LoadSoundMem(path.c_str());
	m_nameAndHandleTable[fileName] = handle;
	return handle;
}

//コンストラクタ
SoundManager::SoundManager()
{
	m_enterSE = LoadSoundFile(L"SE1");
	m_moveSE = LoadSoundFile(L"SE2");
	m_pauseOpenSE = LoadSoundFile(L"Pause1");
	m_pauseBackSE = LoadSoundFile(L"Pause2");
	m_clearSE = LoadSoundFile(L"GameClear");
	m_overSE = LoadSoundFile(L"GameOver");
	m_fireSE = LoadSoundFile(L"fireflower");
	m_stepSE = LoadSoundFile(L"StepSE");
	m_backSE = LoadSoundFile(L"BackSE");
	SetSEVolume(m_volumeSE);
	SetBGMVolume(m_volumeBGM);
}
//デストラクタ
SoundManager::~SoundManager()
{
	DeleteSoundMem(m_enterSE);
	DeleteSoundMem(m_moveSE);
	DeleteSoundMem(m_pauseOpenSE);
	DeleteSoundMem(m_pauseBackSE);
	DeleteSoundMem(m_clearSE);
	DeleteSoundMem(m_overSE);
	DeleteSoundMem(m_fireSE);
	DeleteSoundMem(m_stepSE);
	DeleteSoundMem(m_backSE);
}

//SE
void SoundManager::Play(const wchar_t* name)
{
	PlaySoundMem(m_nameAndHandleTable[name], DX_PLAYTYPE_BACK);
}

//BGM
void SoundManager::PlayMusic(const int  path)
//void SoundManager::PlayMusic(const wchar_t* path)
{
	DxLib::PlaySoundMem(path, DX_PLAYTYPE_LOOP);
	SetVolumeMusic(m_volumeBGM);
}

//SEの音量
void SoundManager::SetSEVolume(int volume)
{
	for (auto& record : m_nameAndHandleTable) {
		ChangeVolumeSoundMem(volume, record.second);
	}
	m_volumeSE = volume;
}

//SEの音量を返す
int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

//BGMの音量
void SoundManager::SetBGMVolume(int volume)
{
	SetVolumeMusic(volume);
	m_volumeBGM = volume;
}

//BGMの音量を返す
int SoundManager::GetBGVolume() const
{
	return m_volumeBGM;
}

//SEとBGMの音を止める
void SoundManager::StopBGMAndSE()
{
	StopSoundMem(m_overSE);
	StopSoundMem(m_clearSE);
	StopSoundMem(m_fireSE);
}
