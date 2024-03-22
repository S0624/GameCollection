using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sound_1_2_2 : MonoBehaviour
{
    private SoundManager _sound;
    // 床の効果音を鳴らす,
    public bool _isPlaneFlag { get; set; }
    // レバーの効果音を鳴らす,
    public bool _isLeverFlag { get; set; }
    // 一回なったらもう鳴らさない,
    private bool _isPlaying = false;
    //連続でならないようにする
    private int _count = 0;
    [SerializeField] private Switch_1_2_2 _switch;

    private void Start()
    {
        _sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();
    }

    void FixedUpdate()
    {
        _count++;
        // BGMを鳴らす
        if (_switch.GetResult())
        {
            _sound.StopBgm();
        }
        else
        {
            _sound.PlayBGM("1_2_2_BGM");
        }
        if(_count < 30)
        {
            _isPlaneFlag = false;
        }
        if(_isPlaneFlag && _count > 30)
        {
            // 床の効果音を鳴らす,
            _sound.PlaySE("1_2_2plane");
            _isPlaneFlag = false;
            _count = 0;
        }
        if(_isLeverFlag && !_isPlaying)
        {
            // レバーの効果音を鳴らす,
            _sound.PlaySE("1_2_2lever");
            // 一回なったらもうならないようにする,
            _isPlaying = true;
        }
    }
}
