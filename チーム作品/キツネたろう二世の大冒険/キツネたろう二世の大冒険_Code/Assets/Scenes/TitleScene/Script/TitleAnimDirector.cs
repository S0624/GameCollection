using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleAnimDirector : MonoBehaviour
{
    // プレイヤーのアニメ
    public TitleAnimePlayer PlayerAnim;

    // 
    private bool _isStart;

    // Update is called once per frame
    private void FixedUpdate()
    {
        if (_isStart)
        {
            PlayerAnim.PlayStart();
        }
        else
        {
            PlayerAnim.AnimUpdate();
        }
    }

    // スタートボタンを押したらtrueにする
    public void SetStart()
    {
        _isStart = true;
    }
}
