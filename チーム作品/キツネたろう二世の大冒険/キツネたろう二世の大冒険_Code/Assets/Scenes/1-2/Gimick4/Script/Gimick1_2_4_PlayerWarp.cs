using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Gimick1_2_4_PlayerWarp : MonoBehaviour
{
    private Player3DMove _player;

    public void Start()
    {
        _player = GameObject.Find("3DPlayer").GetComponent<Player3DMove>();
    }

    // プレイヤーの座標を強制的に動かす.
    public void NextStagePos()
    {
        _player.transform.position = transform.position;
    }


}
