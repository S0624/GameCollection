#pragma once
#include "SceneBase.h"

class InputState;
class SceneManager;
class SceneMain;
//ポーズシーン
class ScenePause :public SceneBase
{
private:
    SceneMain* pMain = 0;
    void SetField(SceneMain* pMain) { pMain = pMain; }
    int m_handle = 0;
    int m_pauseFont = 0;
    int m_guideFont = 0;

    int m_pausehandle = 0;

    double m_Increase = 0.1;
    float m_magnification = 0.0f;
    bool m_cursolFlag = false;

public:
    //コンストラクタ
    ScenePause(SceneManager& manager);
    //デストラクタ
    ~ScenePause();
    //初期化
    virtual void PauseInit();

    //更新処理
    virtual void Update(const InputState& input);
    //描画処理
    void Draw();
    //カーソルの更新処理
    int CursolUpdate();
};

