using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Rendering;

public class MonitorDirector : MonoBehaviour
{
    // プレイヤーが範囲内にいるかどうか.
    private bool _isPlayerCollider;
    // ボタンの状態を渡すためにオブジェクトを取得.
    private GameObject _gameObject;
    // Pause
    public GameObject Pause;

    // Start is called before the first frame update
    void Start()
    {
        // 初期化処理.
        _isPlayerCollider = false;

        // オブジェクトを取得.
        _gameObject = GameObject.Find("GameManager");
    }
    // カメラを切り替える処理
    private void Update()
    {
        // 時間が止まっている場合は止める.
        if (Pause.GetComponent<UpdatePause>()._isPause) return;

        // プレイヤーが判定内にいるとき.
        if (_isPlayerCollider)
        {
            //// Aボタンを押したら
            //if (Input.GetKeyDown("joystick button 3"))
            //{
            //    // ボタンのフラグをオンにする(カメラON).
            //    _gameObject.GetComponent<MonitorCamera131>().SetPushFlag(false);

            //}
            // Xボタンを押したら
            if (Input.GetKeyDown("joystick button 3"))
            {
                // ボタンのフラグをオフにする(カメラOFF).
                _gameObject.GetComponent<MonitorCamera131>().SetPushFlag();
            }
        }
    }

    // 当たり判定の処理
    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            // プレイヤーがコライダーに入ったとき.
            _isPlayerCollider = true;

        }
    }
    void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            // プレイヤーがコライダーから出たとき.
            _isPlayerCollider = false;

        }
    }
}
