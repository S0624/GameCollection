#pragma once
#include "SceneBase.h"

class BackGround;
class SceneSelect :
	public SceneBase
{
public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

	// カーソルのUpdate処理
	void UpdateCursol();
	// cursorのフラグ処理
	void CursolFlag();
	// オプションのcursor処理
	void CursolOption(int cursol);
	// オプションの描画処理
	void OptionDraw();
	// 選ばれたオプションの描画処理
	void SelectOptionDraw();

private:
	BackGround* m_pBack;// 背景のポインタ
	int m_selectHandle; // select画面の画像の読み込み
	int m_optionHandle; // option画面の画像の読み込み
	int m_guideHandle;  // 操作説明画像の読み込み
	int m_frameDown;	// 説明のフレーム
	int m_frameWidth;	// 説明のフレーム
	int m_guidefont;	// 下のガイドに使用するフォント

	// TODO テスト実装
	int m_test;			// テスト、設定画面を開いたときにスライドさせる
	bool m_option;		// optionを選択しているかどうか
	bool m_optinPush;	// optionを押したかどうか
	int m_optionCursorNum; // optionの選んでいる番号
	int m_cursorNum;	// カーソルのさしている番号
	int m_max;			// マックス値の設定
};