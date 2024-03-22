#pragma once
#include<unordered_map>
#include<string>
class SoundManager
{
private:
	int m_enterSE = 0;
	int m_moveSE = 0;
	int m_pauseOpenSE = 0;
	int m_pauseBackSE = 0;
	int m_clearSE = 0;
	int m_overSE = 0;
	int m_fireSE = 0;
	int m_stepSE = 0;
	int m_backSE = 0;
	int m_volumeSE = 180;
	int m_volumeBGM = 200;

	std::unordered_map<std::wstring, int>m_nameAndHandleTable;
	//シングル度パターンなのでコンストラクタはprivateに置く
	int LoadSoundFile(const wchar_t* fileName);
	SoundManager();
	//コピーも代入も禁止する
	SoundManager(const SoundManager&) = delete;	//コピーコンストラクタ
	void operator = (const SoundManager&) = delete;	//代入も禁止
public:
	~SoundManager();
	/// <summary>
	/// SoundManager使用者はGetInstance()を通した参照からしか利用できない
	/// </summary>
	/// <returns></returns>
	static SoundManager& GetInstance()
	{
		static SoundManager instance;	//ここが唯一の実態
		return instance;		//それの参照を返す
	}

	/// <summary>
	/// 指定のサウンドを鳴らす
	/// </summary>
	/// <param name="name"></param>
	void Play(const wchar_t* name);
	void PlayMusic(const int path);
	//void PlayMusic(const wchar_t* path);

	void SetSEVolume(int volume);
	int GetSEVolume() const;

	void SetBGMVolume(int volume);
	int GetBGVolume() const;

	//サウンドを一時停止する
	void StopBGMAndSE();
};

