using UnityEngine;

// 機械(オブジェクト)を削除するスクリプト.
public class MachineDestory : MonoBehaviour
{
    // 機械を破壊する.
    public void ObjectDestory(bool destory)
    {
        // 溶岩で満たされていたら.
        if (destory)
        {
            // オブジェクトの削除
            Destroy(gameObject);
        }
    }
}
