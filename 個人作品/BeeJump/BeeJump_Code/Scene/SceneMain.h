#pragma once
#include "SceneBase.h"

// クラスの宣言
class Player;
class Map;
class BackGround;
class Camera;
class GameObject;
class Effect;

// シーンベースクラスを継承してシーンを作成する
class SceneMain :
	public SceneBase
{
public:
	// コンストラクタ
	SceneMain(int selectNum);
	// デストラクタ
	virtual ~SceneMain();

	// 初期化
	virtual void Init();
	// エンド処理
	virtual void End();
	// 更新処理
	virtual SceneBase* Update() override;
	// 描画処理
	virtual void Draw();

	// ステージが始まった時のカウントダウンをする処理
	bool Timer();
	// ゲームクリア、オーバー時に表示する説明を描画する処理
	void DrawGuide();

private:
	Player* m_pPlayer;	// プレイヤーのポインタ
	Map* m_pMap;		// マップのポインタ
	BackGround* m_pBack;// 背景のポインタ
	Camera* m_pCamera;	// カメラのポインタ
	Effect* m_pEffect;

	int m_scoreHandle;	// スコアを表示するパネル
	int m_guideHandle;	// クリア、ゲームオーバー時の選択画面
	int m_frameHandle;	// クリア、ゲームオーバー時のフレーム画像
	int m_selectNum;	// クリア、ゲームオーバー時の選んだ番号
	int m_gameHandle;	// クリア、ゲームオーバーの画像

	int m_gamefont;		// カウントダウンなどに使用するフォント
	int m_guidefont;	// 下のガイドに使用するフォント

	int m_teimer;		// タイマー(始まる前のカウントダウンに使用)

	bool m_seFlag;		// SEを再生したかどうか

	int m_cursolNum;	// クリア、ゲームオーバー時の選んだ番号

	int m_scoreCount;	// スコアをカウントする用の変数

	int m_makeScreen;	// メイクスクリーンをする変数

	// TODO シャドウマップを付けようとしてできなかったのであとで追加する
	int	m_shadowMap;	// シャドウマップ(影)のための変数
};

