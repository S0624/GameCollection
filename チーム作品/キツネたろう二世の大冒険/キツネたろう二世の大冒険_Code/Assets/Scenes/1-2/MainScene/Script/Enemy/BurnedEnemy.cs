/*燃やされた時の敵の処理*/

using UnityEngine;

public class BurnedEnemy : MonoBehaviour
{
    [SerializeField] private GameObject[] _burnedEnemy;

    [Header("燃え尽きるまでの時間")]
    [SerializeField] private int _burnedTime;

    //private Material[] _materials;
    private float _a = 1.0f;


    // Start is called before the first frame update
    void Start()
    {
        for(int objNum = 0; objNum < _burnedEnemy.Length; objNum++)
        {
            //_materials[objNum] = _burnedEnemy[objNum].GetComponent<Material>();
        }

        //_materials[0].color.a = 0.0f;

        //_a = _materials[0].color.a;
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        //Debug.Log(_a);

        if(_a >= 0)
        {
            _a -= 0.1f;
        }
        
    }
}
