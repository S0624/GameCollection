// 壁ギミック

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WallGimmick : MonoBehaviour
{
    private SolveGimmickManager _manager;
    private SoundManager _soundManager;

    // 扉が開いた時の最終位置.
    private Vector3 _targetPosition;
    private Vector3 _velocity = Vector3.zero;
    // ターゲット座標にたどり着く時間.
    [SerializeField] private float _time;
    // 作動時間.
    private int _operatingTime = 0;

    private void Start()
    {
        _manager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        _targetPosition = new Vector3(transform.position.x, transform.position.y + 10.0f, transform.position.z);
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
    }

    private void FixedUpdate()
    {
        // カウント開始
        if (_manager._solve[0])
        {
            _operatingTime++;
        }

        if(_operatingTime == 40)
        {
            _soundManager.PlaySE("1_2_0_IronDoor");
        }

        if(_operatingTime == 130)
        {
            _manager._solve[0] = false;
            _operatingTime = 0;
        }

        if(_operatingTime >= 70)
        {
            UpdateWall();
        }
        
    }

    /// <summary>
    /// 壁のギミック更新処理.
    /// </summary>
    public void UpdateWall()
    {
        transform.position = Vector3.SmoothDamp(transform.position, _targetPosition, ref _velocity, _time);
    }
}
