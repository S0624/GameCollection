using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlaneBool : MonoBehaviour 
{
    // 動きを有効にするかどうか.
    private bool _isMoving = false;
    // 現在の動き決める.
    private int _tempMoveAngle = 4;

    // 自動で動くかどうか.
    public bool GetMoving() { return _isMoving; }
    // 動きを決める.
    public void SetMoving(bool Moving) { _isMoving = Moving; }
    // 角度を番号をみる.
    public int GetAngle() { return _tempMoveAngle; }
    // 角度の番号を受け取る.
    public void SetAngle(int angle) { _tempMoveAngle = angle; }
}
