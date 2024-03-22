using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HandlePos : MonoBehaviour
{
    // プレイヤー.
    GameObject _player;
    // ハンドルの差し込み口.
    [SerializeField] GameObject[] _handleWall;
    // ハンドルの回転フレームを測る.
    private int _rotaFrameHandle;
    // Start is called before the first frame update.
    void Start()
    {
        _rotaFrameHandle = 0;
        // プレイヤーを取得する.
        _player = GameObject.Find("3DPlayer");
    }
    // ハンドルをプレイヤーの位置に移動.
    public void HandlePosIsPlayer()
    {
        Vector3 pos;
        pos.x = _player.transform.position.x;
        pos.y = _player.transform.position.y + 3.3f;
        pos.z = _player.transform.position.z;
        this.transform.position = pos;
    }

    // ハンドルを差し込み位置に移動.
    public void HandlePosIsHandleWall(int no)
    {
        Vector3 pos;
        pos.x = _handleWall[no].transform.position.x;
        pos.y = _handleWall[no].transform.position.y;
        pos.z = _handleWall[no].transform.position.z - 0.4f;
        this.transform.position = pos;
    }

    // ハンドルの回転.
    public void Rota(float speed)
    {
        this.transform.Rotate(0, 0, speed);
        _rotaFrameHandle++;
    }
    // ハンドルの回転が終了したか.
    public bool IsGetRotaTimeOver(int frame)
    {
        if(_rotaFrameHandle > frame)
        {
            return true;
        }

        return false;
    }
}
