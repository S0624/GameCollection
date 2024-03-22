using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxMove : MonoBehaviour
{
	// Rigidbodyの取得.
	Rigidbody _rb;
	// プレイヤーの押す力.
	public float _pushPower = 4.0f;
	// 押している方向.
	Vector3 _pushDir;
	private Vector3 _prevPos = Vector3.zero;
	private Vector3 _nowPos = Vector3.zero;
	private PlayerAnim3D _playerAnim;
	// Start is called before the first frame update
	void Start()
    {
        _prevPos = transform.position;
		_nowPos = transform.position;
		_playerAnim = GameObject.Find("3DPlayer").GetComponent<PlayerAnim3D>();

	}
	// 前フレームの時と一緒の位置にいないかどうか.
	private void UpdatePosition()
    {
        _nowPos = transform.position;
        if (_nowPos != _prevPos)
        {
   //         Vector3 difference = _nowPos - _prevPos;
			//Debug.Log("おしてる");
			_playerAnim._isPushing = true;
			//Debug.Log("差    :" + difference);
			//Debug.Log("ﾁｶﾞｳ");
		}
		else
        {
			_playerAnim._isPushing = false;
			//Debug.Log("だけ");
		}
		_prevPos = _nowPos;
    }
	private void OnCollisionStay(Collision collision)
    {
        if(collision.transform.tag == "Player")
        {
			UpdatePosition();
        }
    }
	private void OnCollisionExit(Collision collision)
	{
		_playerAnim._isPushing = false;
	}

 //   void OnControllerColliderHit(ControllerColliderHit hit)
	//{
	//	Debug.Log("ositeru");
	//	_rb = hit.collider.attachedRigidbody;
	//	// 相手のオブジェクトにRigidbodyがついていなかったり、isKinematicにチェックが入っている場合には押せない.
	//	if (_rb == null || _rb.isKinematic)
	//	{
	//		return;
	//	}

	//	if (hit.moveDirection.y < -0.3f)
	//	{
	//		return;
	//	}
	//	// 押している方向を取得する
	//	_pushDir = new Vector3(hit.moveDirection.x, 0, hit.moveDirection.z);
	//	// 押している方向に押している力を掛けて移動させる
	//	_rb.velocity = _pushDir * _pushPower;
	//}
}
