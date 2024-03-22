using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.UI;

public class SlideGimmickDirector : MonoBehaviour
{
    // 縦・横に並んでいるブロックの数.
    private const int kRaw = 4;
    private const int kCol = 4;
    // ブロックの総数.
    private const int kBlockNum = kRaw * kCol + 1;
    // 最後のブロックを空白とする.
    private const int kNoneBlockNo = kBlockNum - 2;
    private const int kClearBlockNo = kBlockNum - 1;

    // 現在の手の位置からの上下左右.
    private const int kDirUp = -kRaw;
    private const int kDirDown = kRaw;
    private const int kDirLeft = -1;
    private const int kDirRight = 1;
    // 上下左右の方向の数.
    private const int kDirNum = 4;

    // 入れ替えにかけるフレーム数.
    private const int kMoveFrame = 10;

    // リセット反映させるまでのフレーム数.
    private const int kResetFrame = 50;

    // 光る用の値
    private const float kAlpha = 0.008f;
    private const float kMaxAlpha = 0.4f;

    // クリア後の待機時間
    private const int kWaitClearFrame = 50 * 2;

    // プレイヤーの手.
    private GameObject _playerHand;
    // 音用変数
    private SoundManager Sound;
    
    // ギミック子オブジェ.
    private GameObject[] _gimmickObj;

    // 要素の番号.
    private int[] _eles;

    // 現在の要素.
    private int _nowEle;

    // はじめの要素情報を入れるよう.
    private int[] _startEles;
    // ひとつ前に動かした場所情報1
    Stack<int> _endEle1;
    // ひとつ前に動かした場所情報2
    Stack<int> _endEle2;

    // 入れ替え用.
    private Vector3 _tempPos1;
    private Vector3 _tempPos2;
    private int _tempEle;

    // 入れ替え時間カウント用.
    private int _moveCount;
    private int _moveEle;
    // 入れ替えをしているか.
    private bool _isChange;

    // リセットの反映カウント用.
    private int _resetCount;
    // リセット反映するかのフラグ
    private bool _isResetCheck;

    // クリアしているかしていないか.
    private bool _isClear;

    // クリア後の待機時間(絵を見せるよう)
    private int _waitClearFrame;

    // 光る用のブロック
    private MeshRenderer[] _lightGimmick;
    float _alpha;
    Color _color;

    // Reset, OneBackのテキストを入れるよう
    public GameObject ResetText;
    public GameObject OneBackText;
    // Canvasを入れるよう
    public GameObject Canvas;
    // ゲージ入れるよう
    public GameObject Gauge;
    // フェード
    private Fade _fade;

    // ギミックの説明描画用.
    public TipsDrawer _tipsDrawer;
    [SerializeField] private PauseController _pauseController;

    private void Start()
    {
        
        // 初期化
        _playerHand = new GameObject();

        _gimmickObj = new GameObject[kBlockNum];

        _eles = new int[kBlockNum];

        _nowEle = kNoneBlockNo;

        _startEles = new int[kBlockNum];
        _endEle1 = new Stack<int>();
        _endEle2 = new Stack<int>();

        _tempPos1 = new Vector3();
        _tempPos2 = new Vector3();
        _tempEle = 0;

        _moveCount = 0;
        _moveEle = 0;
        _isChange = false;

        _isClear = false;
        _waitClearFrame = 0;

        // プレイヤーを探す
        _playerHand = GameObject.Find("FoxHand");

        // サウンドマネージャーを探す.
        Sound = GameObject.Find("SoundManager").GetComponent<SoundManager>();

        // 親オブジェクトを探す(光るやつ).
        GameObject _parentObj = GameObject.Find("PieceLightBox");
        _lightGimmick = new MeshRenderer[kBlockNum];
        for (int i = 0; i < kClearBlockNo; i++)
        {
            _lightGimmick[i] = _parentObj.transform.GetChild(i).GetComponent<MeshRenderer>();
        }

        // 親オブジェを探す(ピース).
        _parentObj = GameObject.Find("Box");
        for (int i = 0; i < kClearBlockNo; i += kRaw)
        {
            for (int j = 0; j < kRaw; j++)
            {
                // 子オブジェを探す.
                if (i < kClearBlockNo - kRaw)
                {
                    _gimmickObj[i + j] = _parentObj.transform.GetChild(i + (kRaw - j - 1)).gameObject;
                }
                else
                {
                    _gimmickObj[i + j] = _parentObj.transform.GetChild(i + (kRaw - j - 2)).gameObject;
                    if(j + i >= kNoneBlockNo)
                    {
                        _gimmickObj[i + j] = _parentObj.transform.GetChild(kNoneBlockNo).gameObject;
                    }
                }
            }
        }

        _gimmickObj[kClearBlockNo] = _parentObj.transform.GetChild(kClearBlockNo).gameObject;
        _gimmickObj[kClearBlockNo].SetActive(false);


        // 要素番号の代入.
        for (int i = 0; i < kClearBlockNo; i++)
        {
            _eles[i] = i;
        }


        int[] _dirNum = { kDirDown, kDirUp, kDirLeft, kDirRight };
        int _changeDir;

        // シャッフル.
        for (int i = 0; i < 48; i++)
        {
            // 0~空白地前までのブロックで動かすようにする.
            _nowEle = Random.Range(0, kNoneBlockNo);

            // 動かす位置が空白でない場合のみ動かす.
            // 動かせないor空白地である場合は
            // もう一度繰り返し処理を行うようにする.
            // 繰り返すのは奇数回しか動かしていない場合積み配置が出来てしまうため.
            _changeDir = _dirNum[Random.Range(0, kDirNum)];
            if (MoveCheck(_changeDir, true)) ChangeTrs(_nowEle + _changeDir, false);
            else i--;
        }

        // 初めの状態を保存
        for (int i = 0; i < kBlockNum; i++)
        {
            _startEles[i] = _eles[i];
        }
        _alpha = 0;
        _color = Color.black;

        // 説明を描画.
        _tipsDrawer.IsDownSlider();
        _fade = GameObject.Find("FadeCanvas").GetComponent<Fade>();
    }

    private void Update()
    {
        // 手がアクティブでない場合は処理を行わない
        if (!_playerHand.activeSelf) return;

        _playerHand.GetComponent<GimmickHand>().HandUpdate();

        // クリアしていたら移動以外処理しない.
        if (_isClear) return;

        // 入れ替えしていたら処理しない.
        if (_isChange) return;

        // 特定のボタンを押したらギミックの処理.
        // 現状Bボタン.
        if (Input.GetKeyDown(KeyCode.F) || Input.GetKeyDown("joystick button 1"))
        {
            // 現在プレイヤーの手がある位置を保存.
            _nowEle = _playerHand.GetComponent<GimmickHand>().HitNo;

            Sound.PlaySE("1_3_1_Push");
            // 動かせるかどうかの判定をしていく.
            EleCheck();
        }

        // ワンバック関係
        if (Input.GetKeyDown("joystick button 2"))
        {
            Sound.PlaySE("1_3_1_OneBack");
            BackOneStep();
        }

        // リセットボタン関係
        if (Input.GetKeyDown("joystick button 0"))
        {
            Gauge.SetActive(true);
            Gauge.transform.GetComponent<Image>().fillAmount = 0;
            _isResetCheck = true;
            _resetCount = 0;
        }
        if (Input.GetKeyUp("joystick button 0"))
        {
            Gauge.SetActive(false);
            _isResetCheck = false;
        }
    }

    private void FixedUpdate()
    {
        // クリアしていたら光らせる処理のみする.
        if (_isClear)
        {
            if (kMaxAlpha <= _color.r) _alpha = -kAlpha;
            if (_color.r <= 0.0f) _alpha = kAlpha;

            _color.r += _alpha;
            _color.g += _alpha;
            _color.b += _alpha;

            for (int i = 0; i < kNoneBlockNo; i++)
            {
                _gimmickObj[i].GetComponent<MeshRenderer>().material.EnableKeyword("_EMISSION");
                _gimmickObj[i].GetComponent<MeshRenderer>().material.SetColor("_EmissionColor", _color);
            }
            _gimmickObj[kClearBlockNo].GetComponent<MeshRenderer>().material.EnableKeyword("_EMISSION");
            _gimmickObj[kClearBlockNo].GetComponent<MeshRenderer>().material.SetColor("_EmissionColor", _color);

            _waitClearFrame++;

            if (_fade.cutoutRange == 1.0f)
            {
                Sound.StopBgm();
            }

            return;
        }

        if (_isResetCheck)
        {
            _resetCount++;
            Gauge.transform.GetComponent<Image>().fillAmount = (float)_resetCount / (float)kResetFrame;

            if (_resetCount > kResetFrame)
            {
                _isResetCheck = false;

                Sound.PlaySE("1_3_1_Reset");
                ResetBlock();
            }
        }

        if (_isChange)
        {
            _moveCount++;

            // 少しずつ動かしていく.
            _gimmickObj[_eles[_moveEle]].transform.position += _tempPos2;

            // 時間がたったら動かないようにする.
            if (kMoveFrame <= _moveCount) _isChange = false;

            // 動き終わるまで下の処理は行わないようする.
            return;
        }

        // 要素が番号通りに並んでいるか確認.
        for (int i = 0; i < kClearBlockNo; i++)
        {
            // 要素番号通りでないならここでの処理終了.
            if (_eles[i] != i) return;
        }

        // ここまで来たらクリアしているので完了とする.
        _isClear = true;
        _gimmickObj[kClearBlockNo].SetActive(true);

        // 手の位置を光らせるブロックを削除する
        foreach(var obj in _lightGimmick)
        {
            Destroy(obj);
        }
    }

    // 1つ前の情報に戻す
    private void BackOneStep()
    {
        // データが入ってない場合はやらない
        if (_endEle1.Count <= 0) return;

        _nowEle = _endEle1.Pop();
        ChangeTrs(_endEle2.Pop(), false);

        // OneBackしたことをテキストで表示
        GameObject clone = Instantiate(OneBackText);
        clone.transform.SetParent(Canvas.transform, false);
    }

    // はじめの状態に戻す
    private void ResetBlock()
    {
        for (int i = 0; i < kBlockNum; i++)
        {
            _nowEle = i;

            // 現在の位置の物がはじめと一緒の場合次のに移る
            if (_eles[i] == _startEles[_nowEle]) continue;

            // それ以外は探しだす
            for (int j = i + 1; j < kBlockNum; j++)
            {
                // 初めの場所を見つけたらそこと場所替え
                if (_eles[j] != _startEles[_nowEle]) continue;

                ChangeTrs(j, false);

                // 探し作業終了
                break;
            }
        }

        // 1つ前に戻したという情報を全て消去
        _endEle1.Clear();
        _endEle2.Clear();

        // Resetしたことをテキストで表示
        GameObject clone = Instantiate(ResetText);
        clone.transform.SetParent(Canvas.transform, false);
    }

    private void EleCheck()
    {
        // 要素番号の位置が空白地なら何もしない.
        if (_eles[_nowEle] == kNoneBlockNo) return;

        // 上のチェック.
        if (DirCheck(kDirUp)) return;
        // 下のチェック.
        if (DirCheck(kDirDown)) return;
        // 左のチェック.
        if (DirCheck(kDirLeft)) return;
        // 右のチェック.
        if (DirCheck(kDirRight)) return;
    }

    // その方向に動かせるかどうか.
    private bool DirCheck(int dir)
    {
        // その方向に動かせるかの確認.
        if (!MoveCheck(dir, false)) return false;
        
        ChangeTrs(_nowEle + dir, true);

        return true;
    }

    // 方向の細かいチェック.
    // 動かす向き、シャッフルかどうか.
    bool MoveCheck(int dir, bool isShuffle)
    {
        // 要素数ないにいなければ確認しない.
        if ((_nowEle + dir) < 0 ||
            kClearBlockNo <= (_nowEle + dir))
        {
            return false;
        }
        // 左右の場合端にあれば確認しない.
        if (dir == kDirLeft &&
            (_nowEle % kRaw) == 0)
        {
            return false;
        }
        if (dir == kDirRight &&
            (_nowEle % kRaw) == (kRaw - 1))
        {
            return false;
        }

        // シャッフルの場合.
        if (isShuffle)
        {
            // dirの方向のものが空白以外の場合動かす.
            if (_eles[_nowEle + dir] != kNoneBlockNo)
            {
                return true;
            }
        }
        else
        // シャッフルでない場合.
        {
            // dirの方向のものが空白の場合動かす.
            if (_eles[_nowEle + dir] == kNoneBlockNo)
            {
                return true;
            }
        }

        return false;

    }

    // 位置の変更.
    // 動かす位置、シャッフルかどうか.
    private void ChangeTrs(int ele, bool isNormal)
    {
        // それぞれの位置を保存.
        _tempPos1 = _gimmickObj[_eles[_nowEle]].transform.position;
        _tempPos2 = _gimmickObj[_eles[ele]].transform.position;

        // 保存した位置を使い、位置の入れ替え.
        // 空白地はすぐに移動.
        _gimmickObj[_eles[ele]].transform.position = _tempPos1;
        // 通常の動き以外すぐに動かす.
        if (!isNormal) _gimmickObj[_eles[_nowEle]].transform.position = _tempPos2;
        // 通常の場合は動きを実装.
        else MoveEfeStart(ele);

        // 通常の動きの場合は動かした情報位置を保存する.
        if (isNormal)
        {
            _endEle1.Push(_nowEle);
            _endEle2.Push(ele);
        }
        // 要素の番号を変更.
        _tempEle = _eles[_nowEle];
        _eles[_nowEle] = _eles[ele];
        _eles[ele] = _tempEle;
    }

    void MoveEfeStart(int ele)
    {
        // 動く配列を選択する.
        _moveEle = ele;
        // カウントの初期化.
        _moveCount = 0;

        // 動く位置までベクトルを求め、移動時間で割る.
        _tempPos2 = _tempPos2 - _tempPos1;
        _tempPos2 /= kMoveFrame;

        // 動くようにする.
        _isChange = true;
    }

    // 現在選択している場所を光らせる
    public void OnLight(int no)
    {
        // クリアしている時は処理を行わない
        if (_isClear) return;

        // 配列範囲外が送られてきた場合は以下の処理はしないようにする
        if (no < 0) return;
        if (no >= kClearBlockNo) return;

        _lightGimmick[no].material.EnableKeyword("_EMISSION");
        _lightGimmick[no].material.SetColor("_EmissionColor", Color.white);
    }

    // 元々光らせていたら光らせないようにする
    public void OffLight(int no)
    {
        // クリアしている時は処理を行わない
        if (_isClear) return;

        // 配列範囲外が送られてきた場合は以下の処理はしないようにする
        if (no < 0) return;
        if (no >= kClearBlockNo) return;

        _lightGimmick[no].material.EnableKeyword("_EMISSION");
        _lightGimmick[no].material.SetColor("_EmissionColor", Color.black);
    }

    public bool GetResult()
    {
        if(_waitClearFrame > kWaitClearFrame)
        {
            _pauseController._getResult = true;
            return true;
        }
        else
        {
            return false;
        }
    }
}
