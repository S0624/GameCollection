// 橋の処理.

using UnityEngine;
using UnityEngine.Rendering.UI;

public class GimmickBirdge : MonoBehaviour
{
    public static GimmickBirdge _instance;

    //private GimmickManager1_1 _manager;
    private SolveGimmickManager _manager;

    // 橋の通路.
    // 左.
    [SerializeField] private GameObject _birdgeLeft;
    // 右.
    [SerializeField] private GameObject _birdgeRight;

    // 橋にいる敵
    [SerializeField] private GameObject _birdgeEnemy;

    // ギミックが動いた後に敵が動くかどうか
    private bool _isMoveEnemy = false;

    private void Awake()
    {
        if( _instance == null )
        {
            _instance = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void Start()
    {
        _manager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
    }

    private void FixedUpdate()
    {
        //Debug.Log("left" + _birdgeLeft.transform.localEulerAngles.z);
        //Debug.Log("right" + _birdgeRight.transform.localEulerAngles.z);

        if (_manager._solve[0])
        {
            UpdateBirdgeAisle();
            _isMoveEnemy = true;
        }

        if(_isMoveEnemy)
        {
            // 敵の動き
            MoveEnemy();
        }
        
    }

    // 橋がかかる処理.
    private void UpdateBirdgeAisle()
    {
        

        // 橋が架かると以降処理しない.
        if (_birdgeLeft.transform.localEulerAngles.z <= 0.0f ||
           _birdgeRight.transform.localEulerAngles.z <= 0.0f)
        {
            _manager._solve[0] = false;

            return;
        }
        

        // 橋の回転.
        RotateBirdgeAisle(_birdgeLeft, new Vector3(0.0f, 0.0f, -0.5f));
        RotateBirdgeAisle(_birdgeRight, new Vector3(0.0f, 0.0f, 0.5f));
        
    }

    // 一度回転し終わると処理を通さない.
    /// <summary>
    /// 橋のわたる部分の回転.
    /// </summary>
    /// <param name="birdge">回転させる橋のオブジェクト</param>
    /// <param name="rotate">回転</param>
    private void RotateBirdgeAisle(GameObject birdge, Vector3 rotate)
    {
        birdge.transform.Rotate(rotate);
    }

    // 橋が架かった時の敵の移動
    private void MoveEnemy()
    {
        if(!_isMoveEnemy) return;

        if(_birdgeEnemy.transform.position.y <= 20.0f)
        {
            _birdgeEnemy.transform.position += new Vector3(0.1f, 0.1f, 0.0f);
        }
        else
        {
            //_birdgeEnemy.SetActive(false);

            Destroy(_birdgeEnemy);
            _isMoveEnemy = false;
        }
            
    }
}
