using UnityEngine;

// 爆発エフェクトの生成
public class BourstEffectPlay : MonoBehaviour
{
    // 爆発エフェクトの取得.
    [SerializeField, Header("爆発エフェクト")] private GameObject _bourst = default;
    // エフェクトの再生.
    private GameObject _effectBurst;
    // エフェクトの再生が終わったかどうか.
    private bool _isEffectNowPlay = false;


    public void BourstEffectCreate(bool bourst,SoundManager sound)
    {
        // 壁がすべて降りて溶岩で満たしていたら.
        if (bourst && !_isEffectNowPlay)
        {
            if (_effectBurst == null)
            {
                sound.PlaySE("1_3_4_Bourst");
                // エフェクトを生成.
                _effectBurst = Instantiate(_bourst, this.transform.position,
                                                        Quaternion.identity);
            }
            else
            {
                EffectPlaying();
            }
        }
    }
    private void EffectPlaying()
    {
        //  エフェクトの再生が終わっていたらclear判定にする.
        if (!_effectBurst.GetComponent<ParticleSystem>().isPlaying)
        {
            // エフェクトの中身を全部消す.
            Destroy(_effectBurst);
            _isEffectNowPlay = true;
        }
    }
    // エフェクトが再生中かどうか.
    public bool IsEffectPlay()
    {
        return _isEffectNowPlay;
    }
}
