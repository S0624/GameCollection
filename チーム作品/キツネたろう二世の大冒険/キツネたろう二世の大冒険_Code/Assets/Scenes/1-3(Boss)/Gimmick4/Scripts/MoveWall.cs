using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveWall : MonoBehaviour
{
    //private float kwallHeight = 1.5f;//最初の壁の高さ
    //private float kclearHeight = -5.0f;//この高さまで壁を下げたらクリア
    private float kclearLavaPos = 9.2f;//クリアした際の溶岩のポジション
    private Vector3 klavaSpeed = new Vector3(0.03f, 0, 0);

    //下がる壁のゲームオブジェクト
    private GameObject _wall;
    //動く溶岩のゲームオブジェクト
    private GameObject _lava;
    //動く壁のポジション
    private Vector3 _wallPos;
    //引っ張ったロープの長さ
    private float kclearHeight = 0;//この高さまで壁を下げたらクリア
    // 今のフレームのロープの長さ
    private float _nowRopeLength;
    // 前のフレームのロープの長さ
    private float _prevRopeLength = 0.0f;
    //溶岩を流す.
    private bool _isLavaFlow;
    // クリアフラグ
    private bool _isFlowFlag = false;
    // Start is called before the first frame update
    void Start()
    {
        _wall = GameObject.Find("Door");
        _lava = GameObject.Find("MoveLava");
        //壁のポジションを取得.
        _wallPos = _wall.transform.position;
        // HACK あとできれいに書き直す
        // (当たり判定を半分引いて 下げる位置を計算している)
        kclearHeight = _lava.transform.position.y - (_wall.GetComponent<BoxCollider>().bounds.size.y * 0.5f);
    }

    // 壁の計算の更新処理.
    public void WallUpdate(PullRope rope,SoundManager sound)
    {
        // 今のロープの長さを取得する.
        _nowRopeLength = rope.GetNowLength();
        // 今のロープの位置と前フレームのロープの位置が同じじゃなければ処理をする.
        if (_nowRopeLength != _prevRopeLength)
        {
            // 前のフレームから引っ張った分の長さの差分を出す.
            var addLength = _nowRopeLength - _prevRopeLength;
            //壁の高さがクリアの高さよりも低くなるまで動く.
            if (_nowRopeLength > 0 && _wallPos.y > kclearHeight)
            {
                sound.PlaySE("1_3_4_Door");
                _wallPos.y = _wall.transform.position.y - addLength;
                _wall.transform.position = _wallPos;
            }
        }
        // クリア位置まで壁が下がったら溶岩を流すフラグを立てる.
        if (_wallPos.y <= kclearHeight)
        {
            _isLavaFlow = true;
        }

        // 溶岩を流す処理.
        if (_isLavaFlow)
        {
            if (_lava.transform.position.x < kclearLavaPos)
            {
                _lava.transform.Translate(klavaSpeed);
            }
            // 溶岩で満たされたらクリア判定にする.
            else
            {
                _isFlowFlag = true;
            }
        }
        // ロープの位置の更新.
        _prevRopeLength = _nowRopeLength;
    }
    // クリア判定.
    public bool GetFlawFlag()
    {
        return _isFlowFlag;
    }
}
