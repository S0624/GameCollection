using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PullRope : MonoBehaviour
{
    // ギミックブロックの長さ
    private readonly float kGimmickLength = 0.75f;
    // プレイヤーの位置情報.
    private Transform _player;
    // ギミックオブジェ.
    [SerializeField] private GameObject _gimmick;
    // 増やす分のギミックをリストで管理する
    private List<GameObject> _gimmicks;
    // ブロックを追加する距離
    private float _longDis;
    // ブロックを減らす距離
    private float _shortDis;
    // 引っ張っているか.
    private bool _isPull;
    // 引っ張り始めたギミック位置.
    private Vector3 _startGimmickPos;
    // 引っ張り始めたプレイヤーの位置
    private Vector3 _startPlayerPos;
    // 移動ベクトル.
    private Vector3 _moveVec;
    // 移動ベクトルを距離に変換
    private float _nowLength;
    // 角度を入れるよう
    //sprivate float _angle = 0.0f;
    // 引っ張れる範囲にいるか
    private bool _isFlag;
    // 角度を入れる用.
    // 横
    private float _angleSide = 0.0f;
    // 縦
    private float _angleCenter = 0.0f;
    // 軸用.
    // 横
    private Vector3 _axisSide;
    // 縦
    private Vector3 _axisCenter;
    // Start is called before the first frame update
    void Start()
    {
        // 初期化処理
        _player = GameObject.Find("3DPlayer").GetComponent<Transform>();

        _gimmicks = new List<GameObject>();

        _longDis = 0.0f;

        _shortDis = 0.0f;
        _isPull = false;
        _isFlag = false;
        _moveVec = new Vector3();

        _startGimmickPos = new Vector3();
        _startPlayerPos = new Vector3();
        _moveVec = new Vector3();

        _axisSide = new Vector3(0.0f, 1.0f, 0.0f);
        _axisCenter = new Vector3();
    }
    public void PullRopeUpdate()
    {
        // プレイヤーがひもを引っ張っていた時の処理
        if ((Input.GetKeyDown("joystick button 1") || Input.GetKeyDown(KeyCode.F)) && _isFlag)
        {
            // 引っ張り始めた位置の保存.
            _startPlayerPos = _player.position;

            // 初めに二つ追加する.
            _gimmicks.Add(Instantiate(_gimmick, this.transform.position, Quaternion.identity));
            _gimmicks.Add(Instantiate(_gimmick, this.transform.position, Quaternion.identity));
            _shortDis = 0;
            _longDis = kGimmickLength;

            _isPull = true;
            _isFlag = false;
        }
        if ((Input.GetKeyUp("joystick button 1") || Input.GetKeyUp(KeyCode.F)) && _isPull)
        {
            foreach (var temp in _gimmicks)
            {
                Destroy(temp.gameObject);
            }
            _gimmicks.Clear();
            _isPull = false;
        }

        // 想定を反対方向に進むとひもを消す
        if (_player.transform.position.x < 0.0f)
        {
            foreach (var temp in _gimmicks)
            {
                Destroy(temp.gameObject);
            }
            _gimmicks.Clear();
            _isPull = false;
        }
    }
    public void PlacementUpdate()
    {
        if (_isPull)
        {
            ObjPlacement();
        }
    }
    // 今の長さを取得する.
    public float GetNowLength() { return _nowLength; }

    // オブジェクトの配置位置の調整
    private void ObjPlacement()
    {
        VectorAngleCal(_player.position, _startPlayerPos);
        _nowLength = _moveVec.magnitude;

        // 距離が伸びたら追加する.
        if (_longDis <= _moveVec.magnitude)
        {
            // 判定距離の更新.
            _longDis += kGimmickLength;
            _shortDis += kGimmickLength;

            // ブロックの追加.
            _gimmicks.Add(Instantiate(_gimmick, this.transform.position, Quaternion.identity));
        }
        // 距離が減ったら削除する.
        else if (_moveVec.magnitude < _shortDis)
        {
            // 判定距離の更新.
            _longDis -= kGimmickLength;
            _shortDis -= kGimmickLength;

            // GameObjectを削除ののち、リストから削除.
            Destroy(_gimmicks[_gimmicks.Count - 1]);
            _gimmicks.RemoveAt(_gimmicks.Count - 1);
        }

        // 出すオブジェクトの量で割る.
        _moveVec /= _gimmicks.Count - 1;

        for (int i = 0; i < _gimmicks.Count; i++)
        {
            _gimmicks[i].transform.position = this.transform.position + _moveVec * (i);
            _gimmicks[i].transform.rotation = Quaternion.AngleAxis(_angleCenter, _axisCenter) * Quaternion.AngleAxis(_angleSide, _axisSide);
        }
    }

    private void VectorAngleCal(Vector3 pos1, Vector3 pos2)
    {
        // 現在までのベクトルを計算.
        _moveVec = pos1 - pos2;

        // 角度を求める.
        _angleSide = Mathf.Atan2(_moveVec.z, _moveVec.x) * Mathf.Rad2Deg * -1;
        // 縦に動いた角度を求める.
        _angleCenter = Mathf.Atan2(_moveVec.y, Mathf.Sqrt(_moveVec.x * _moveVec.x + _moveVec.z * _moveVec.z)) * Mathf.Rad2Deg * -1;
        // 側面の法線ベクトルを軸とする. 
        _axisCenter.x = _moveVec.z;
        _axisCenter.z = -_moveVec.x;
    }
    // プレイヤーが判定内にいるかどうか
    private void OnTriggerStay(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            // プレイヤーが引っ張った初めの位置を取得する
            _startGimmickPos = this.transform.position;
            _isFlag = true;
            if(_isPull)
            {
                _isFlag = false;
            }
        }
    }
}
