using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick1_3_2Manager : MonoBehaviour
{
    [SerializeField] private ResetButton _reset;
    private SoundManager _sound;
    [SerializeField] private TipsDrawer _tips;

    //private Vector3 _tempPlayerLocalSize = Vector3.zero;
    //private Vector3 _tempPlayerLossySize = Vector3.zero;

    private Vector3 _playerLocalSize = Vector3.zero;
    private Vector3 _playerLossySize = Vector3.zero;

    public GameObject _player;
    // Start is called before the first frame update
    void Start()
    {
        _tips.IsDownSlider();

        _playerLocalSize = _player.transform.localScale;
        _playerLossySize = _player.transform.lossyScale;

        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        _reset.SoundDataSet(_sound);
    }

    // Update is called once per frame
    void Update()
    {
        // リセットボタンの処理.
        _reset.ResetPush();
    }

    // プレイヤーのサイズ
    public Vector3 GetPlayerLocalScale()
    {
        return _playerLocalSize;
    }
    public Vector3 GetPlayerLossyScale()
    {
        return _playerLossySize;
    }
}
