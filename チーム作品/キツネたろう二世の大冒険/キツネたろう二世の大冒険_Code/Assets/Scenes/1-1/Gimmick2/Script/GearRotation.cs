using UnityEngine;
// ギミックの回転を管理するスクリプト.
public class GearRotation : MonoBehaviour
{
    // オブジェクトのRigidbodyを取得.
    private Rigidbody _rigidbody;
    // 回転度合.
    private Vector3 _rotaDegrees;
    // 回転.
    private Quaternion _rotation;
    // 一回転したかのフラグ(クリアした判定にも使用).
    private bool _playerRotation;
    // プレイヤーが範囲内にいるかどうかのフラグ.
    private bool _colRange;
    // ギア(手持ちハンドル)の回転させる角度.
    private float _gearRote;
    // 今の回転率.
    private int _nowAngel;
    // 前フレームの回転率.
    private int _prevAngle;
    // 回転率.
    private int _angle;
    private float _localAngle = 0;

    // インスタンスの作成.
    void Start()
    {
        // 初期化.
        _rotaDegrees += new Vector3(0.0f, -1.0f, 0.0f);
        _rotation = Quaternion.AngleAxis(0.0f, _rotaDegrees);
        _playerRotation = false;
        _colRange = false;
        _rigidbody = GetComponent<Rigidbody>();
        _gearRote = 1.5f;
        _localAngle = this.transform.localEulerAngles.y % 360;
        _nowAngel = (int)_localAngle;
        _prevAngle = (int)_localAngle;
        _angle = 360;
    }

    // オブジェクトを回転させる.
    public void GearRotate()
    {
        // プレイヤーが持ち手を持って一回転したら.
        if (_playerRotation)
        {
            // 回転度合をかけて足す(ずっと回転させる).
            this.transform.rotation = _rotation * this.transform.rotation;
        }
    }

    // プレイヤーが範囲内にいた時の処理.
    public void PlayerColRange()
    {
        // 判定内にいたら.
        if (_colRange)
        {
            // 回転を調べる処理.
            CheckRotation();
        }
    }

    // 回転を調べる処理.
    private void CheckRotation()
    {
        // 一回転していなかったら.
        if (!_playerRotation)
        {
            GearRotaRete();

            // ボタンを押したら回転できるようにする.
            if (Input.GetKeyDown("joystick button 1"))
            {
                // rigidbodyのFreezeを解除する.
                _rigidbody.constraints = RigidbodyConstraints.FreezePosition
                 | RigidbodyConstraints.FreezeRotationX
                 | RigidbodyConstraints.FreezeRotationZ;
            }
            // 一回転したら.
            if (_angle < 0.0f)
            {
                _playerRotation = true;
                // RigidbodyのRotationを固定させる.
                _rigidbody.freezeRotation = true;
                // 回転速度を固定させる.
                _rotation = Quaternion.AngleAxis(_gearRote, _rotaDegrees);
            }
        }
    }
    // ギミックの回転率を調べる処理.
    private void GearRotaRete()
    {
        // 今のアングルを取得.
        _localAngle = this.transform.localEulerAngles.y % 360;
        // 回転させる計算.
        // 前のフレームの回転率.
        _prevAngle = _nowAngel;
        // 現在の回転率.
        _nowAngel = (int)_localAngle;

        // 現在のフレームより前のフレームが小さければ.
        // 指定した方向と逆回転しているので処理をしない.
        if (_nowAngel >_prevAngle || _nowAngel - _prevAngle > 0 || _nowAngel - _prevAngle < -10)
        {
            return;
        }
        // 現在のフレームより前のフレームがおおきければ.
        // 指定した方向の回転しているので処理をする.
        else if (_nowAngel < _prevAngle )
        {
            if (_prevAngle != _nowAngel)
            {
                // 現在の回転率と前フレームの回転率を減算して.
                // 差をアングルに入れる.
                _angle += _nowAngel - _prevAngle;
            }
        }
    }
    // オブジェクト(ギア)が一回転したかどうか.
    public bool IsGearRotated()
    {
        return _playerRotation;
    }
    // プレイヤーがコライダー内にいるとき.
    void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Player")
        {
            _colRange = true;
        }
    }
    // プレイヤーがコライダー外に出たとき.
    void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            _colRange = false;
            _rigidbody.freezeRotation = true;
        }
    }

}
