#pragma once
#include "../Util/common.h"

// ゲームシーン基底クラス
class SceneBase
{
public:
	SceneBase();
	virtual ~SceneBase() {}

	virtual void Init        () {			   }// 初期化
	virtual void End         ()	{			   }// 終了
	virtual SceneBase* Update() { return this; }// 毎フレームの処理
	virtual void Draw        ()	{              }// 描画

	// フェード関連
	void UpdateFade();// フェード更新
	void DrawFade() const;// フェード描画
	bool IsFadingIn() const;// フェードイン中
	bool IsFadingOut() const;// フェードアウト中
	bool IsFading() const { return IsFadingIn() || IsFadingOut(); }// フェードインorアウト中

	void StartFadeOut();// フェードアウト開始

protected:
	// フェード関連処理
	int m_fadeColor;
	int m_fadeBright;
	int m_fadeSpeed;

	bool m_isFadeOut;// フェードアウトを行っているかどうか

	bool m_isBackScene;
};

