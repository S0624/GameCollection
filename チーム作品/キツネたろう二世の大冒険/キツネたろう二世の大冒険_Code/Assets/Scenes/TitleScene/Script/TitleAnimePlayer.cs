using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TitleAnimePlayer : MonoBehaviour
{
    // 動くフレーム
    private const int kMoveFrame = 50 * 2;
    // 回転フレーム
    private const int kRotFrame = 50 * 1;
    // 初めのダッシュフレーム
    private const int kRunFrame = kMoveFrame;
    // 正面向かせるフレーム
    private const int kRotFrontFrame = kRunFrame + kRotFrame;
    // 立っているフレーム
    private const int kStandFrame = kRotFrontFrame + 50 * 5;
    // 手を振るフレーム
    private const int kWaveHandFrame = kStandFrame + 50 * 3;
    // 戻る方向向くフレーム
    private const int kRotOutRageFrame = kWaveHandFrame + kRotFrame;
    // まえに進むフレーム
    private const int kMoveFrontFrame = kRotOutRageFrame + kMoveFrame;
    // 画面内にダッシュするほうを向くフレーム
    private const int kRotStartFrame = kMoveFrontFrame + kRotFrame;
    // プレイヤーの待機時間
    private const int kWaitFrame = kRotStartFrame + 50 * 10;

    private int _frame;
    private PlayerAnim _anim;

    private Vector3 _move;

    private Quaternion _rotFront;
    private Quaternion _rotOutRage;
    private Quaternion _rotStart;

    private Vector3 _lookPos;

    void Start()
    {
        _frame = 0;
        _anim = GetComponent<PlayerAnim>();

        _move = new Vector3(20f / kMoveFrame, 0, 0);

        float angle = -60.0f / kRotFrame;
        _rotFront = Quaternion.AngleAxis(angle, new Vector3(0, 1.0f, 0)); ;
        angle = -90.0f / kRotFrame;
        _rotOutRage = Quaternion.AngleAxis(angle, new Vector3(0, 1.0f, 0));
        angle = 150f / kRotFrame;
        _rotStart = Quaternion.AngleAxis(angle, new Vector3(0, 1.0f, 0));

        _lookPos = transform.position;
        _lookPos.x = -20;
    }

    public void PlayStart()
    {
        _anim._waveHands = false;
        _anim._run = true;

        this.transform.LookAt(_lookPos);
        transform.position += -_move;
    }

    public void AnimUpdate()
    {
        _frame++;

        // 画面外から画面内にダッシュ
        if (_frame < kRunFrame)
        {
            _anim._run = true;
            this.transform.position += -_move;
        }
        // 正面向かる
        else if (_frame < kRotFrontFrame)
        {
            _anim._run = false;
            this.transform.rotation = this.transform.rotation * _rotFront;
        }
        // 立つだけ
        else if (_frame < kStandFrame)
        {

        }
        // 手を振る
        else if (_frame < kWaveHandFrame)
        {
            _anim._waveHands = true;
        }
        // 画面外に向かせる
        else if (_frame < kRotOutRageFrame)
        {
            _anim._waveHands = false;
            this.transform.rotation = this.transform.rotation * _rotOutRage;
        }
        // 画面外にダッシュ
        else if (_frame < kMoveFrontFrame)
        {
            _anim._run = true;
            this.transform.position += _move;
        }
        // 元の方向を向かせる
        else if (_frame < kRotStartFrame)
        {
            _anim._run = false;
            this.transform.rotation = this.transform.rotation * _rotStart;
        }
        // 何もしない
        else if (_frame < kWaitFrame)
        {
        }
        else
        {
            _frame = 0;
        }
    }
}
