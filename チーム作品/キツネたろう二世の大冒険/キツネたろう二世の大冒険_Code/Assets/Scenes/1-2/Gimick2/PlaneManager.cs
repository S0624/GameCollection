using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class PlaneManager : MonoBehaviour
{

    private int temp { get; set; }

    int GetTempA()
    {
        return temp;
    }

    void SetTempA(int num)
    {
        temp = num;
    }

    // 移動パターン.
    private enum MoveNum
    {
        up,
        right,
        down,
        left,
        empty,
    }

    private struct MoveAngle
    {

        public float up;
        public float right;
        public float down;
        public float left;
        public float empty;
    }


    static readonly float AutoMoveSpeed = 0.002f;
    static readonly string PlayerNameTag = "Player";

    // プレイヤーオブジェクト.
    private GameObject _player;
    // プレイヤーマネージャーオブジェクト.
    private GameObject _planeManager;
    // 床オブジェクトの角度.
    private float _tileObj;
    // 床オブジェクトから離れた場合移動をやめる.
    public bool _isExit;
    // 床オブジェクトから離れたかの判定を取る.
    private bool _isExitHit = false;
    // 壁に当たるまで移動を続ける.
    public bool _isWall;
    // 角度を代入.
    MoveAngle _moveAngle;
    //効果音マネージャ
    public Sound_1_2_2 _sound;

    private void Start()
    {
        // オブジェクトの取得.
        _player = GameObject.Find("3DPlayer");
        _planeManager = GameObject.Find("PlaneManager");

        // プレイヤー角度代入
        _tileObj = this.transform.localEulerAngles.y;

        _moveAngle.up = 0;
        _moveAngle.right = 90;
        _moveAngle.down = 180;
        _moveAngle.left = 270; 
    }

    private void Update()
    {
        // 現在の床から離れた場合の処理.
        if(_isExitHit)
        {
            // ギミックの発動を停止する.
            _planeManager.GetComponent<PlaneBool>().SetMoving(false);
            // 角度を初期化する.
            _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.empty);
            // 床から離れた場合の処理を初期化する.
            _isExitHit = false;
        }
    }

    private void FixedUpdate()
    {
        // ギミックのが発動したなら.
        if (_planeManager.GetComponent<PlaneBool>().GetMoving())
        {
            
            // ユーザーがプレイヤーを動かせなくする.
            _player.GetComponent<Player3DMove>()._isController = false;
            //効果音を鳴らす
            _sound._isPlaneFlag = true;
            // プレイヤーの移動パターンを見て.
            // 自動で移動を開始.
            if (_planeManager.GetComponent<PlaneBool>().GetAngle() == (int)MoveNum.up)
            {
                _player.transform.position += new Vector3(-AutoMoveSpeed, 0.0f, 0.0f);
            }
            else if (_planeManager.GetComponent<PlaneBool>().GetAngle() == (int)MoveNum.right)
            {
                _player.transform.position += new Vector3(0.0f, 0.0f, AutoMoveSpeed);
            }
            else if (_planeManager.GetComponent<PlaneBool>().GetAngle() == (int)MoveNum.down)
            {
                _player.transform.position += new Vector3(AutoMoveSpeed, 0.0f, 0.0f);
            }
            else if (_planeManager.GetComponent<PlaneBool>().GetAngle() == (int)MoveNum.left)
            {
                _player.transform.position += new Vector3(0.0f, 0.0f, -AutoMoveSpeed);
            }
        }
        else
        {
            // ユーザーがプレイヤーを動かせるようにする.
            _player.GetComponent<Player3DMove>()._isController = true;
            // 角度を初期化する.
            _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.empty);
        }
    }
    private void OnTriggerStay(Collider other)
    {
        // ふれているタグがプレイヤーだった場合.
        if (other.gameObject.tag == PlayerNameTag)
        {
            // 壁に当たるまでの処理ではない場合(青い床では無かった場合).
            if (!_isWall)
            {
                // 仕掛けを発動するようにする.
                _planeManager.GetComponent<PlaneBool>().SetMoving(true);

                // プレイヤーの角度を見る.
                // 進行方向を決める.
                if ((int)_tileObj == (int)_moveAngle.up)
                {
                    _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.up);
                }
                else if ((int)_tileObj == (int)_moveAngle.right)
                {
                    _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.right);
                }
                else if ((int)_tileObj == (int)_moveAngle.down)
                {
                    _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.down);
                }
                else if ((int)_tileObj == (int)_moveAngle.left)
                {
                    _planeManager.GetComponent<PlaneBool>().SetAngle((int)MoveNum.left);
                }
            }
            else
            {
                _isExitHit = true;
            }
        }
    }

    // 当たっていたオブジェクトから離れた場合.
    private void OnTriggerExit(Collider other)
    {
        // ふれているタグがプレイヤーだった場合.
        if (other.gameObject.tag == PlayerNameTag)
        {
            // 緑の床だった場合緑の床から離れた場合の処理をする.
            if (_isExit)
            {
                _isExitHit = true;
            }
        }
    }
}


