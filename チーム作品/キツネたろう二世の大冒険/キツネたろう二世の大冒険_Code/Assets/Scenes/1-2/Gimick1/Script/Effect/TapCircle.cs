using UnityEngine;

public class TapCircle : MonoBehaviour
{
    // SpriteRendererの取得.
    private SpriteRenderer _spriteRenderer;

    private void Awake()
    {
        _spriteRenderer = this.transform.GetComponent<SpriteRenderer>();
    }
    // 初期化処理.
    private void Start()
    {
        _spriteRenderer.material.SetFloat("_StartTime", Time.time);

        float animationTime = _spriteRenderer.material.GetFloat("_AnimationTime");
        float destroyTime = animationTime;
        destroyTime -= _spriteRenderer.material.GetFloat("_StartWidth") * animationTime;
        destroyTime += _spriteRenderer.material.GetFloat("_Width") * animationTime;
        Destroy(transform.gameObject, destroyTime);
    }
}
