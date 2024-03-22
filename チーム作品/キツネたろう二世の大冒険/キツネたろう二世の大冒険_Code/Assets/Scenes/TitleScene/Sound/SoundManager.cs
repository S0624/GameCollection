using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : MonoBehaviour
{
    [System.Serializable]
    // サウンドデータ用の構造体を追加.
    public class SoundData
    {
        [Header("サウンドデータだよ！")]
        public AudioClip sound;// データ.
        public string name;    // 名前.
        public float volume;   // 音量.
    }

    // サウンド再生リソースを取得する.
    private GameObject _sePlayObject;
    private GameObject _bgmPlayObject;

    // サウンド再生用リソース.
    public AudioSource _seSource;
    public AudioSource _bgmSource;

    // SE用サウンドデータ.
    [SerializeField, Header("「 S E 」専用データ")]
    public SoundData[] _seData;

    // BGM用サウンドデータ.
    [SerializeField, Header("「 B G M 」専用データ")]
    public SoundData[] _bgmData;

    // デフォルト音量.
    private float[] _seDefaultVolume;
    private float[] _bgmDefaultVolume;

    // デバッグ用.
    public bool[] _playSeTest;
    public bool[] _playBgmTest;

    // マスターボリューム用.
    [SerializeField] private float _seMasterVolume = 1.0f;
    [SerializeField] private float _bgmMasterVolume = 1.0f;
    // 現在流しているBGMの番号.
    private int _nowPlayBgm;

    private void Awake()
    {
        _seMasterVolume = 1.0f;
        _bgmMasterVolume = 1.0f;
        _nowPlayBgm = 0;

        // オブジェクトを探す.
        _sePlayObject = GameObject.Find("SeSoundPlay");
        _bgmPlayObject = GameObject.Find("BgmSoundPlay");

        // 指定したオブジェクトを削除しない.
        DontDestroyOnLoad(gameObject);
        DontDestroyOnLoad(_sePlayObject);
        DontDestroyOnLoad(_bgmPlayObject);

        // 配列を増やす.
        Array.Resize(ref _seDefaultVolume, _seData.Length);
        Array.Resize(ref _bgmDefaultVolume, _bgmData.Length);

        // 既に調整してある音量を記録.
        for (int i = 0; i < _seData.Length; i++)
        {
            _seDefaultVolume[i] = _seData[i].volume;
        }
        for (int i = 0; i < _bgmData.Length; i++)
        {
            _bgmDefaultVolume[i] = _bgmData[i].volume;
        }

    }

    // デバッグ用.
    private void FixedUpdate()
    {
        for (int i = 0; i < _seData.Length; i++)
        {
            // サウンド音量の調整.
            if (_seData[i].volume > 1.0f)
            {
                _seData[i].volume = 1.0f;
            }
            if (_seData[i].volume < 0.0f)
            {
                _seData[i].volume = 0;
            }

            //// デバッグ用.
            //if (_playSeTest[i])
            //{
            //    _seSource.volume = _seData[i].volume;
            //    _seSource.PlayOneShot(_seData[i].sound);
            //    break;
            //}
        }
        for (int i = 0; i < _bgmData.Length; i++)
        {
            // サウンド音量の調整.
            if (_bgmData[i].volume > 1.0f)
            {
                _bgmData[i].volume = 1.0f;
            }
            if (_bgmData[i].volume < 0.0f)
            {
                _bgmData[i].volume = 0;
            }

            //// デバッグ用.
            //if (_playBgmTest[i])
            //{
            //    _bgmSource.volume = _bgmData[i].volume;
            //    _bgmSource.PlayOneShot(_bgmData[i].sound);
            //}
        }

        //Debug.Log("Fixed " + this._bgmMasterVolume);
    }

    /// <summary>
    /// SEを再生する.
    /// </summary>  
    /// <param name="name">サウンドの名前.</param>
    public void PlaySE(string name)
    {
        // ボリュームを調整する.
        _seSource.volume = _seData[SoundCheck(true, name)].volume * _seMasterVolume;
        // サウンドを再生.
        _seSource.PlayOneShot(_seData[SoundCheck(true, name)].sound);
    }

    /// <summary>
    /// BGMを再生する.
    /// </summary>
    /// <param name="name">サウンドの名前.</param>
    public void PlayBGM(string name)
    {
        // 再生していない場合は再生.
        // 手抜きなので修正が必要な場合は教えてください.
        if (!_bgmSource.isPlaying)
        {
            //Debug.Log("Play " + this._bgmMasterVolume);

            // ループ再生する.
            _bgmSource.loop = true;
            // ボリュームを調整する.
            _bgmSource.volume = _bgmData[SoundCheck(false, name)].volume * this._bgmMasterVolume;
            // サウンドを再生.
            _bgmSource.PlayOneShot(_bgmData[SoundCheck(false, name)].sound);

            // 現在流しているBGMの番号を記憶
            _nowPlayBgm = SoundCheck(false, name);
        }
    }

    /// <summary>
    /// SEの音量を変更します.
    /// </summary>
    /// <param name="name">名前.</param>
    /// <param name="volume">音量.</param>
    public void SetVolumeChangeSe(string name, float volume)
    {
        _seData[SoundCheck(true, name)].volume = volume;
        _seSource.volume = _seData[SoundCheck(true, name)].volume;
    }

    /// <summary>
    /// BGMの音量を変更します.
    /// </summary>
    /// <param name="name">名前.</param>
    /// <param name="volume">音量.</param>
    public void SetVolumeChangeBgm(string name, float volume)
    {
        _bgmData[SoundCheck(false, name)].volume = volume;
        _bgmSource.volume = _bgmData[SoundCheck(false, name)].volume;
    }

    /// <summary>
    /// 全体のSEの音量を変更します.
    /// </summary>
    /// <param name="volume">ボリュームを指定してください、0.0f～1.0fを指定してください.</param>
    public void MasterVolumeChangeSe(float volume)
    {
        _seMasterVolume += volume;
        if (_seMasterVolume > 1.0f)
        {
            _seMasterVolume = 1.0f;
        }
        if (_seMasterVolume < 0.0f)
        {
            _seMasterVolume = 0.0f;
        }
    }

    /// <summary>
    /// 全体のBGMの音量を変更します.
    /// </summary>
    /// <param name="volume">ボリュームを指定してください、0.0f～1.0fを指定してください.</param>
    public void MasterVolumeChangeBgm(float volume)
    {
        this._bgmMasterVolume += volume;
        if(_bgmMasterVolume > 1.0f)
        {
            _bgmMasterVolume = 1.0f;
        }
        if (_bgmMasterVolume < 0.0f)
        {
            _bgmMasterVolume = 0.0f;
        }

        // 現在流しているBGMの元ボリュームでマスターボリュームとかける
        _bgmSource.volume = _bgmData[_nowPlayBgm].volume * _bgmMasterVolume;
    }

    /// <summary>
    /// デフォルトの音量を渡す
    /// </summary>
    /// <param name="name">名前</param>
    /// <returns>音量</returns>
    public float GetDefaultVolumSe(string name)
    {
        return _seDefaultVolume[SoundCheck(true, name)];
    }

    /// <summary>
    /// デフォルトの音量を渡す
    /// </summary>
    /// <param name="name">名前</param>
    /// <returns>音量</returns>
    public float GetDefaultVolumBgm(string name)
    {
        return _bgmDefaultVolume[SoundCheck(false, name)];
    }

    /// <summary>
    /// SEの音量を渡す
    /// </summary>
    /// <returns>SEの音量</returns>
    public float GetVolumeSe()
    {
        return _seMasterVolume;
    }

    /// <summary>
    /// SEの音量を渡す
    /// </summary>
    /// <returns>SEの音量</returns>
    public float GetVolumeBgm()
    {
        return _bgmMasterVolume;
    }

    /// <summary>
    /// SE停止する.
    /// </summary>
    public void StopSe()
    {
        _seSource.Stop();
    }

    /// <summary>
    /// BGM停止する.
    /// </summary>
    public void StopBgm()
    {
        _bgmSource.Stop();
    }

    /// <summary>
    /// サウンドの番号を知る.
    /// </summary>
    /// <param name="isCheck">SEかBGM.</param>
    /// <returns>サウンドの番号、もしサウンドが存在しない場合は-1を返す.</returns>
    private int SoundCheck(bool isCheck, string name)
    {
        // SEの場合
        if (isCheck)
        {
            for (int i = 0; i < _seData.Length; i++)
            {
                if (name == _seData[i].name)
                {
                    return i;
                }
            }
        }
        // BGMの場合
        else
        {
            for (int i = 0; i < _bgmData.Length; i++)
            {
                if (name == _bgmData[i].name)
                {
                    return i;
                }
            }
        }
        return -1;
    }
}
