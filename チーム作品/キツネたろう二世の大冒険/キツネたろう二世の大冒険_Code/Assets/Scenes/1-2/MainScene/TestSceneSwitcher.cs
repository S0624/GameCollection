using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class TestSceneSwitcher : MonoBehaviour
{
    public static TestSceneSwitcher _instance;
    // プレイヤーのHpを受け取る.
    public int _PlayerHp;

    private void Awake()
    {
        if( _instance == null )
        {
            _instance = new TestSceneSwitcher();
        }
        else
        {
            Destroy(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        //_PlayerHp = Player2DMove._instance.GetHp();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown("joystick button 5"))
        {
            SceneManager.LoadScene("test3D");
        }
    }

    public void SwitchToNextScene(int Hp)
    {

        if (Input.GetKeyDown("joystick button 5"))
        {
            //Player2DMove._instance._hp = Hp;
            SceneManager.LoadScene("test3D");
        }
        
    }
}
