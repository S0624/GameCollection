using UnityEngine;

// 溶岩に当たった時.
public class LavaCol : MonoBehaviour
{
    // 跳ね返る力.
    readonly Vector3 kjumpForce = new Vector3(0, 30.0f, 0);
    // Rigidbodyの取得
    private Rigidbody _rb;

    void OnCollisionEnter(Collision other)
    {
        // 判定にいるのがプレイヤーであったら.
        if (other.gameObject.CompareTag("Player"))
        {
            // プレイヤーを跳ね返す.
            _rb = other.gameObject.GetComponent<Rigidbody>();
            _rb.velocity = kjumpForce;
        }
    }
}
