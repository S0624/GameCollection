using UnityEngine;

// ボタンの色を変えるスクリプト.
public class GimickButton : MonoBehaviour
{
    // ボタンの状態を渡すためにオブジェクトを取得.
    private GameObject _playerObject;
    private Gimick1_2_1Manager _gameManager;
    private Renderer _renderer;
    private PlayerHand _hand;
    // プレイヤーが触れいているボタンの名前をいれるための変数.
    private string _name;
    // マテリアルの配列の番号
    private int _materialNum;
    // 更新処理.
    void Start()
    {
        // オブジェクトを取得.
        _gameManager = GameObject.Find("GameManager").GetComponent<Gimick1_2_1Manager>();
        _renderer = GetComponent<Renderer>();
        _playerObject = null;
        _materialNum = 1;
    }

    // 更新処理.
    private void Update()
    {
        if (_gameManager.SetHandObject() != null)
        {
            _playerObject = _gameManager.SetHandObject();
            _hand = _playerObject.GetComponent<PlayerHand>();
            ButtonChengeColor();
        }
    }
    // ボタンの色を変える処理.
    public void ButtonChengeColor()
    {
        // 自身の名前とプレイヤーが触れているボタンの名前が一緒だったら.
        if (_name == this.gameObject.name)
        {
            // みどりに色を変える.
            _renderer.materials[_materialNum].color = Color.green;
        }

        // プレイヤーがボタンを押した状態であったら.
        if (_hand.IsGetButtonState())
        {
            // 今触れているボタンの名前を取得する.
            _name = _hand.IsGetButtonName();
        }
        // 押した状態でなければ.
        else
        {
            // 名前には何も入れない
            _name = "";
        }
    }

    // 現在のボタンの色を返す.
    public Color IsCheckColor()
    {
        Color color = _renderer.materials[_materialNum].color;
        return color;
    }
    // ボタンの色を白色に戻す処理.
    public void ChengeColor(bool ischange)
    {
        if(ischange)
        {
            // しろ色を変える.
            _renderer.materials[_materialNum].color = Color.white;
        }
    }
}
