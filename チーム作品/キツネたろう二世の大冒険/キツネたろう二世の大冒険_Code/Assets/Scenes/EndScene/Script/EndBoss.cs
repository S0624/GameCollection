using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static TMPro.SpriteAssetUtilities.TexturePacker_JsonArray;

public class EndBoss : MonoBehaviour
{
    private const int kMoveFrame = 50 * 12;
    private const int kWaitFrame = kMoveFrame * 3;
    private const int kLapsNo = 2;

    private Vector3 _startPos;
    private Vector3 _move;
    int _frame;

    int _lapsNum;

    private ParticleSystem _partic;

    private void Start()
    {
        _startPos = transform.position;
        _move = new Vector3(-0.1f, 0, 0);
        _frame = kMoveFrame;
        _lapsNum = 0;

        _partic = GameObject.Find("Smoke").GetComponent<ParticleSystem>();
    }

    public void BossUpdate()
    {
        // 周回数超えたら処理しない
        if (_lapsNum > kLapsNo) return;

        _frame++;

        if (_frame < kMoveFrame)
        {
            transform.position += _move;
        }
        else if (_frame < kWaitFrame)
        {
            _partic.Stop();
            // 何もしない    
        }
        else
        {
            _lapsNum++;
            _frame = 0;
            transform.position = _startPos;
            _partic.Play();
        }
    }
}
