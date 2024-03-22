using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollsionHandle : MonoBehaviour
{
    // 判定を取りたいオブジェクトの名前.
    private string _objectName;
    // 当たっているかどうか.
    private bool _isColliding;

    // 判定処理をどうするかを決める.
    public void SetHit(bool isHit)
    {
        _isColliding = isHit;
    }
    // 当たっているかどうか.
    public bool IsGetHit()
    {
        return _isColliding;
    }

    public void SetNameColl(string name)
    {
        _objectName = name;
    }

    // 指定したオブジェクトに当たったら.
    private void OnTriggerStay(Collider other)
    {
        if (other.name == _objectName)
        {
            _isColliding = true;
        }
    }
    // 指定したオブジェクトに当たっていなかったら.
    private void OnTriggerExit(Collider other)
    {
        if (other.name == _objectName)
        {
            _isColliding = false;
        }
    }
}
