/*敵を燃やす処理*/

using UnityEngine;

public class FireGimmick : MonoBehaviour
{
    private SolveGimmickManager _gimmickManager;

    // パーティクルオブジェクト
    [SerializeField] private ParticleSystem _particleSystem;

    // デバッグ用ゲームオブジェクト(Enemy)
    [SerializeField] private GameObject _debugEnemyObject;

    // 炎が燃え続ける最大時間
    //public int _burningMaxCount;

    // サウンドマネージャー.
    private SoundManager _soundManager;

    // 炎が燃え続けている時間
    //private int _burningCount;

    //owl
    GameObject _owl;

    void Start()
    {
        _gimmickManager = GameObject.FindWithTag("GimmickManager").GetComponent<SolveGimmickManager>();
        _particleSystem.Pause();
        _soundManager = GameObject.Find("SoundManager").GetComponent<SoundManager>();
        _owl = GameObject.Find("owlMaster (3)");
    }

    private void FixedUpdate()
    {
        if (_gimmickManager._solve[3])
        {
            UpdateFire();
        }

        //フクロウが一定以上上昇したら
        if(_owl.transform.position.y > 24.0f)
        {
            _particleSystem.Stop();
        }
    }

    private void UpdateFire()
    {
        // パーティクル再生.
        _particleSystem.Play();

        //SE再生
        _soundManager.PlaySE("1_2_0_Fire");

        //_debugEnemyObject.transform.position += new Vector3(0.0f, 0.12f, 0.0f);

        //if( _burningCount < _burningMaxCount )
        //{
        //    _burningCount = _burningCount + 1;
        //}

        //// デバッグ用Enemy消去
        //if(_burningCount == _burningMaxCount / 2)
        //_debugEnemyObject.SetActive(false);
    }


}
