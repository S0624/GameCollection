using UnityEngine;
// ボタンの状態を管理しているスクリプト.
public class ButtonState : MonoBehaviour
{
    // ボタンの押した状態を保存するためにSerializeFieldで管理する.
    [SerializeField] private GameObject[] _objGet;
    // 押したボタンの名前を取得する.
    private string _buttonName;
    // ボタンの状態(ボタンが押されたかどうか)を取得する.
    private bool _isButtonState = false;
    // 配列を管理するために用意.
    private int _numCount;
    // 配列の最大値.
    private int _indexMax;
    // 名前をチェックするために用意.
    private bool _isNameCheck = false;
    // ボタンの状態を渡すためにオブジェクトを取得.
    private PlayerHand _playerObject;
    // ボタンの取得.
    private GimickButton[] _getButton;
    // 答えのボタンの名前.
    [SerializeField] private GameObject[] _objAnswerName;
    // エフェクトをリセットするフラグ.
    private bool _isEffectResetFlag = false;
    // ギミックをクリアしたというフラグ.
    private bool _isGimmickClear = false;
    // 初期化処理.
    private void Start()
    {
        // 初期化処理.
        _buttonName = "";
        _isButtonState = false;
        _numCount = 0;
        _indexMax = 5;
        _isNameCheck = false;

        // 配列の最大数を定義.
        _getButton = new GimickButton[_indexMax];
    }
    // プレイヤーの手の情報を取得する.
    public void GetPlayerObject(GameObject handobj)
    {
        // オブジェクトを取得.
        _playerObject = handobj.GetComponent<PlayerHand>();
    }
    // ボタンの状態
    public void ButtonAcquisition()
    {
        // エフェクトのリセットフラグの初期化.
        _isEffectResetFlag = false;

        // ボタンが押されたかどうかを取得する.
        _isButtonState = _playerObject.IsGetButtonState();
        // ボタンが押されていたら.
        if (_isButtonState)
        {
            // ボタンの名前を取得する.
            _buttonName = _playerObject.IsGetButtonName();
            // ボタンが保存できるかどうか.
            _isNameCheck = IsButtonKeep();
            // ボタンの状態を保存する.
            ButtonStateKeep();
        }
        // ボタンが押されていなかったら.
        else
        {
            _isButtonState = false;
            _isNameCheck = false;
        }

        // ボタンのチェック.
        CheckButtonAnswer();
    }
    // ボタンが保存できるかどうか.
    private bool IsButtonKeep()
    {
        // _numが0だったら.
        // (for文だと0のままだと回らないために0番目のみ処理).
        if (_numCount == 0)
        {
            // 0番目に保存.
            _objGet[_numCount] = GameObject.Find(_buttonName);
            return true;
        }
        // for文で処理を回す.
        for (int obj = 0; obj < _numCount; obj++)
        {
            // 取得したボタンの名前と今保存しているボタンの名前が一緒だったら.
            if (_objGet[obj].gameObject.name == _buttonName)
            {
                // もう取得したボタンなので保存しないフラグを立てる.
                return false;
            }

        }
        // ここまできたら一緒じゃなかったことになる.
        return true;
    }
    // ボタンの状態を保存する.
    private void ButtonStateKeep()
    {
        //　保存するフラグがたっていたら.
        if (_isNameCheck)
        {
            // _num番目に要素を保存.
            _objGet[_numCount] = GameObject.Find(_buttonName);
            _numCount++;
        }
    }
    // ボタンの正誤チェック.
    private void CheckButtonAnswer()
    {
        // 答えと違ったらボタンの状態をリセットする.
        if (_numCount == _indexMax && isCheckColor())
        {
            for (int obj = 0; obj < _indexMax; obj++)
            {
                // 答えと押されたボタンの名前が違ったら.
                if (_objGet[obj].name != _objAnswerName[obj].name)
                {
                    // 取得したボタンを初期化する.
                    ObjGetInit();
                    _isEffectResetFlag = true;
                    break;
                }
                // 最後まで間違いがなかった場合
                else if (obj == _indexMax - 1)
                {
                    _isGimmickClear = true;
                }
            }
        }
    }
    // ボタンの情報のリセット.
    public void ButtnReset()
    {
        if (_objGet[_objGet.Length - 1] == null)
        {
            ObjGetInit();
        }
    }
    // 取得したオブジェクト(ボタン)の情報を初期化する.
    private void ObjGetInit()
    {
        for (int obj = 0; obj < _getButton.Length; obj++)
        {
            if (_objGet[obj] != null)
            {
                _getButton[obj] = _objGet[obj].GetComponent<GimickButton>();
                // 初期化する際に色も元に戻す.
                _getButton[obj].ChengeColor(true);
                // None(何も入っていない状態)にする.
                _objGet[obj] = GameObject.Find("");
                // ここのフラグをfalseにしておかないとずっと白色のままになってしまう.
                _getButton[obj].ChengeColor(false);
            }
        }
        _numCount = 0;
    }
    // ボタンの色チェック.
    private bool isCheckColor()
    {
        for (int obj = 0; obj < _indexMax; obj++)
        {
            // ボタンの情報をここで取得する.
            _getButton[obj] = _objGet[obj].GetComponent<GimickButton>();
            // ひとつでもボタンの色が緑ではなかったら押し終わってないことになるのでチェックする.
            if(_getButton[obj].IsCheckColor() != Color.green)
            {
                return false;
            }
        }
        return true;
    }
    // ボタンの名前を返す.
    public bool isCheckButton()
    {
        return _isNameCheck;
    }
    // リセットするフラグを返す.
    public bool IsResetFlag()
    {
        return _isEffectResetFlag;
    }
    // ギミックをクリアしたかのフラグを返す.
    public bool IsGimckClear()
    {
        return _isGimmickClear;
    }
}
