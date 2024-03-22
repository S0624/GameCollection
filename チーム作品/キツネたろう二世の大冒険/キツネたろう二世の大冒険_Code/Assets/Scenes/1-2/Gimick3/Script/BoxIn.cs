using UnityEngine;
// Boxが範囲内に入った時のスクリプト.
public class BoxIn : MonoBehaviour
{
    // ディレクター.
    private BoxDirector _director;
    // ギミックの色.
    [SerializeField] private string _color;

    // 初期化処理.
    private void Start()
    {
        // GimmickDirectorの情報を取得する.
        _director = GameObject.Find("GimmickDirector").GetComponent<BoxDirector>();
    }
    // 範囲内に入った時の処理.
    private void OnTriggerEnter(Collider other)
    {
        _director.SetGimmickIn(_color, this.transform.position);
        _director.SetObj(this.gameObject);
    }

    // 範囲外に出た時の処理.
    private void OnTriggerExit(Collider other)
    {
        _director.IsSetFlag(false);
    }
}
