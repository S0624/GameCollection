using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class SlideGimmickText : MonoBehaviour
{
    // 32フレームで消えるように.
    const float kAlpha = 0.03125f;

    // 色を入れるよう.
    private Color _color;

    private void Start()
    {
        _color = gameObject.GetComponent<Image>().color;
        _color.a = 1f;
    }

    private void FixedUpdate()
    {
        _color.a -= kAlpha;
        gameObject.GetComponent<Image>().color = _color;

        if(_color.a < 0.0f)
        {
            Destroy(gameObject);
        }
    }
}
