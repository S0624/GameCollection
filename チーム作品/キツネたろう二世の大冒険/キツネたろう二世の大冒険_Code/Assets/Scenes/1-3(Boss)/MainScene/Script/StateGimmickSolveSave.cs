// ギミックのクリア状況を保存.

using UnityEngine;
using UnityEngine.SceneManagement;

public class StateGimmickSolveSave : MonoBehaviour
{
    public static StateGimmickSolveSave singleton;
    private GateFlag _transitionScene;

    private void Awake()
    {
        if(singleton == null)
        {
            DontDestroyOnLoad(gameObject);
            singleton = this;
        }
        else
        {
            Destroy(gameObject);
        }
    }

    private void Start()
    {
        _transitionScene = GameObject.FindWithTag("Player").GetComponent<GateFlag>();
        
    }

    private void FixedUpdate()
    {
        if(_transitionScene._isGoal1_3)
        {
            SceneManager.MoveGameObjectToScene(gameObject, SceneManager.GetActiveScene());
        }
    }
}
