using System.Collections.Generic;
using UnityEngine;
// 引っ張る処理.
public class BoxPull : MonoBehaviour
{
    // ギミックブロックの長さ.
    private readonly static float kGimmickLength = 0.7f;

    // ブロックを追加する距離.
    private float _longDis;
    // ブロックを減らす距離.
    private float _shortDis;

    // ディレクター.
    private BoxDirector _director;
    // プレイヤーの位置情報.
    private Transform _player;

    // サウンド用
    private SoundManager Sound;

    // ギミックの色.
    public string Color;
    // ギミックオブジェ.
    private GameObject _gimmick;
    private GameObject _gimmickClear;
    private GameObject _gimmickSpher;
    private List<GameObject> _gimmicks;
    // クリアオブジェ.

    // 引っ張れる範囲にいるかの.
    private bool _isPullRange;
    // 引っ張っているか.
    private bool _isPull;

    // ギミッククリアしているか.
    private bool _isClear;

    // 引っ張り始めたギミック位置.
    private Vector3 _startGimmickPos;
    // 引っ張り始めたプレイヤーの位置
    private Vector3 _startPlayerPos;

    // 移動ベクトル.
    private Vector3 _moveVec;

    // 角度を入れるよう.
    private float _angleSide = 0.0f;
    private float _angleCenter = 0.0f;
    // 軸用.
    private Vector3 _axisSide;
    private Vector3 _axisCenter;

    // 初期化処理.
    private void Start()
    {
        _director = GameObject.Find("GimmickDirector").GetComponent<BoxDirector>();

        _player = GameObject.Find("3DPlayer").GetComponent<Transform>();

        Sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();

        // クリア前までのオブジェ.
        _gimmick = (GameObject)Resources.Load(Color + "Cube");
        _gimmickClear = (GameObject)Resources.Load(Color + "Cylinder");
        _gimmickSpher = (GameObject)Resources.Load(Color + "Sphere");

        _gimmicks = new List<GameObject>();

        _longDis = 0.0f;
        _shortDis = 0.0f;

        // bool関係をすべてfalseに.
        _isPullRange = false;
        _isPull = false;
        _isClear = false;

        _startGimmickPos = new Vector3();
        _startPlayerPos = new Vector3();
        _moveVec = new Vector3();

        _axisSide = new Vector3(0.0f, 1.0f, 0.0f);
        _axisCenter = new Vector3();
}

    // Update is called once per frame
    private void Update()
    {
        // ギミックをクリアしていたら処理をしない.
        if (_isClear) return;

        if ((Input.GetKeyDown("joystick button 1") || Input.GetKeyDown(KeyCode.F)) && _isPullRange)
        {
            Sound.PlaySE("1_2_3_Pull");
            // 引っ張り始めた位置の保存.
            _startPlayerPos = _player.position;

            // 初めに二つ追加する.
            _gimmicks.Add(Instantiate(_gimmick, this.transform.position, Quaternion.identity));
            _gimmicks.Add(Instantiate(_gimmick, this.transform.position, Quaternion.identity));
            _shortDis = 0;
            _longDis = kGimmickLength;

            _director.SetGimmickOut(Color);

            _isPull = true;
        }

        if ((Input.GetKeyUp("joystick button 1") || Input.GetKeyUp(KeyCode.F)) && _isPull)
        {
            Sound.PlaySE("1_2_3_Push");
            // オブジェクトを削除する
            foreach (var temp in _gimmicks)
            {
                Destroy(temp.gameObject);
            }
            _gimmicks.Clear();

            _isPull = false;

            // 離した色が引っ張り始めた色と同じか.
            // ギミッククリア範囲内にいるか.
            // 違うなら処理終了.
            if (!_director.IsSameColor()) return;

            // ここまで来たらギミックをクリアしてる.
            _isClear = true;

            VectorAngleCal(_director.GetGimmickPos(), _startGimmickPos);

            // スケールを入れる用の変数.
            Vector3 scale = new Vector3(0.8f, 0.8f, 0.8f);

            // 形をきれいに見せるように球体を作成.
            GameObject instance = Instantiate(_gimmickSpher, _startGimmickPos, Quaternion.identity);
            instance.transform.localScale = scale;

            // 1階2階で繋がっていない.
            if (Mathf.Abs(_moveVec.y) < 1)
            {
                _moveVec *= 0.5f;
                instance = Instantiate(_gimmickClear, this.transform.position + _moveVec, Quaternion.AngleAxis(90, _axisCenter) * Quaternion.AngleAxis(_angleSide, _axisSide));
                scale.y = _moveVec.magnitude;
                instance.transform.localScale = scale;
            }
            // 1階2階で繋がっている.
            else
            {
                // 合成クオータニオン.
                Quaternion compositeAngle = Quaternion.AngleAxis(90, _axisCenter) * Quaternion.AngleAxis(_angleSide, _axisSide);

                // 初めに移動量を1/4に
                _moveVec *= 0.25f;

                // 1つ目のブロック.
                // 移動量を入れる.
                Vector3 tempPos = _moveVec;
                // 高さの移動は無しとする.
                tempPos.y = 0;

                float scaleY = tempPos.magnitude;

                instance = Instantiate(_gimmickClear, this.transform.position + tempPos, compositeAngle);
                scale.y = scaleY;
                instance.transform.localScale = scale;

                // 2つ目.
                // 高さそのままでx,zを元の2倍.
                tempPos *= 2f;
                instance = Instantiate(_gimmickSpher, this.transform.position + tempPos, Quaternion.identity);
                scale.y = 0.8f;
                instance.transform.localScale = scale;

                // 3つ目.
                // x,zそのままで高さを半分の地点に.
                tempPos = _moveVec * 2f;
                instance = Instantiate(_gimmickClear, this.transform.position + tempPos, Quaternion.AngleAxis(_angleSide, _axisSide));
                scale.y = 4f;
                instance.transform.localScale = scale;

                // 4つ目.
                // x, yそのままで高さを一番下or一番上にする.
                tempPos.y = _moveVec.y * 4f;
                instance = Instantiate(_gimmickSpher, this.transform.position + tempPos, Quaternion.identity);
                scale.y = 0.8f;
                instance.transform.localScale = scale;

                // 5つ目.
                // 高さそのままでx, yを元の3倍.
                // 移動量の3倍を入れる.
                tempPos = _moveVec * 3f;
                tempPos.y = _moveVec.y * 4f;
                instance = Instantiate(_gimmickClear, this.transform.position + tempPos, compositeAngle);
                scale.y = scaleY;
                instance.transform.localScale = scale;
            }

            // 形をきれいに見せるように球体を作成
            instance = Instantiate(_gimmickSpher, _director.GetGimmickPos(), Quaternion.identity);
            scale.y = 0.8f;
            instance.transform.localScale = scale;
        }
    }

    void FixedUpdate()
    {
        // ギミックをクリアしていたら処理をしない.
        if (_isClear) return;

        if (_isPull)
        {
            ObjPlacement();
        }
    }

    // 範囲内に入った場合引っ張れるようにする.
    void OnTriggerEnter(Collider other)
    {
        _isPullRange = true;
        _startGimmickPos = this.transform.position;
    }

    // 範囲外に出たら引っ張れないようにする.
    void OnTriggerExit(Collider other)
    {
        _isPullRange = false;
    }

    // 移動量分ずらしてオブジェクトの設置.
    void ObjPlacement()
    {
        VectorAngleCal(_player.position, _startPlayerPos);

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

    void VectorAngleCal(Vector3 pos1, Vector3 pos2)
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
}
