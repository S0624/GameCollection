using UnityEngine;

// 時間で落下する床の処理.
public class FallBlock : MonoBehaviour
{
    // サウンドの取得
    private GameObject _gameObject;
    private Gimick1_3_4Manager _manager;
    //プレイヤーがブロックに乗ったか判断する.
    private bool _isPlayerColl;
    //ブロックの最初のポジション.
    private Vector3 _blockPos;
    //ブロックの動く位置.
    private Vector3 _blockMoveVec;
    //ブロックの落ちる速度.
    private Vector3 kfallVel = new Vector3(0, -0.1f, 0);
    private float kfallSpeed = 0.1f;
    //板が落ちる時間.
    private int kfallTime = 50;
    private int _frameCount;
    // ブロックが落下する最大値
    readonly int _blockFallMax = -3;
    // Start is called before the first frame update
    void Start()
    {
        // 初期化処理.
        _gameObject = GameObject.Find("GameObject");
        _manager = _gameObject.GetComponent<Gimick1_3_4Manager>();
        _frameCount = 0;
        _isPlayerColl = false;
        _blockPos = this.transform.position;
        _blockMoveVec.y = kfallSpeed;
    }

    void FixedUpdate()
    {
        // ブロックを落とす処理の更新処理.
        BlockFall();
    }

    // ブロックを落とす処理.
    private void BlockFall()
    {
        // プレイヤーが判定内にいたら.
        if (_isPlayerColl)
        {
            // フレームをカウントする.
            _frameCount++;
            // 触れたブロックを揺らす処理.
            if (transform.position.y > _blockPos.y + 0.05f)
            {
                _blockMoveVec.y = -kfallSpeed;
            }
            else if (transform.position.y < _blockPos.y - 0.05f)
            {
                _blockMoveVec.y = kfallSpeed;
            }
            this.transform.Translate(_blockMoveVec);
        }
        // フレームカウントが設定した時間より大きくなったら.
        if (_frameCount > kfallTime)
        {
            _isPlayerColl = false;
            // ブロックを落とす.
            transform.Translate(kfallVel);
        }
        // ブロックが設定した位置より低く落下したら.
        if (this.transform.position.y < _blockFallMax)
        {
            // ブロックを削除する.
            Destroy(this.gameObject);
        }
    }
    // プレイヤーが判定内にいるかどうか.
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.CompareTag("Player"))
        {
            // 落ちるときのSEを流す
            _manager.FallSEPlay();
            // プレイヤーが判定内にいるフラグを立てる.
            _isPlayerColl = true;
        }
    }
}
