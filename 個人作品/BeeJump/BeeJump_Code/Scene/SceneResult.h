#pragma once
#include "SceneBase.h"

// クラスの宣言
class BackGround;

// シーンベースクラスを継承してシーンを作成する
class SceneResult :
	public SceneBase
{
public:
	// コンストラクタ
	SceneResult(int score);
	// デストラクタ
	virtual ~SceneResult();

	// 初期化
	virtual void Init();
	// エンド処理
	virtual void End();
	// 更新処理
	virtual SceneBase* Update() override;
	// 描画処理
	virtual void Draw();

	// ゲームクリア、オーバー時に表示する説明を描画する処理
	void DrawGuide();

	// ファイルの生成
	void FileGenerate();
	// ファイルの読み込み
	void FileRead();
private:
	BackGround* m_pBack;// 背景のポインタ

	int m_scoreHandle;	// スコアを表示するパネル
	int m_guideHandle;	// クリア、ゲームオーバー時の選択画面
	int m_frameHandle;	// クリア、ゲームオーバー時のフレーム画像
	int m_selectNum;	// クリア、ゲームオーバー時の選んだ番号

	int m_gamefont;		// カウントダウンなどに使用するフォント
	int m_guidefont;	// 下のガイドに使用するフォント

	bool m_seFlag;		// SEを再生したかどうか

	int m_cursolNum;	// クリア、ゲームオーバー時の選んだ番号

	int	m_nowScore;	// 今獲ったスコア
	int m_maxScore;	// スコアをカウントする用の変数
};
