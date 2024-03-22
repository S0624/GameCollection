#pragma once
#include "SceneBase.h"
class MapChip;
class InputState;


class SceneSelect : public SceneBase
{
private:
	MapChip* m_pMap;
	static constexpr int m_fadeInterval = 30;
	int m_fadeTimer = m_fadeInterval; //フェードタイマー
	float m_fadeValue = 255; //黒矩形とのブレンド具合

	//フェードインの時のUpdeta関数
	void FadeInUpdate(const InputState& input);
	//通常状態のUpdate関数
	void NormalUpdate(const InputState& input);
	//フェードアウトの時のUpdate関数
	void FadeOutUpdate(const InputState& input);
	//Update用メンバ関数ポインタ
	void (SceneSelect::* m_updateFunc)(const InputState& input);

	//int m_test;
	int m_handle;		//画像
	int m_backHandle;
	int m_BgSound;
	int m_selectFont;	//フォント
	int m_guideFont;	//説明文のフォント
	int m_strTitle;		//文字列の長さ
	int m_strEx;		//説明文の長さ
	int m_strNum;		//文字列の長さ
	int m_fontSize;
	int m_freamAnime = 0;	//アニメーションを行うフレーム
	int m_freamStop = 0;	//アニメーションを止めているフレーム
	int m_animeNum = 0;		//アニメーションの番号
	int m_countNum = 0;
	int m_displayCount = 0;
	int m_buttonHandle = 0;
	int m_animation = 0;
	int m_boxHandle = 0;
	int m_selectNumIndex = -1;
	int moveindex = 1;
	int frame = 0;

public:
	SceneSelect(SceneManager& manager);
	~SceneSelect();

	void Update(const InputState& input);
	void Draw();
	void DrawBackground();
	void DrawSelectNum();
	int SelectNum(int num);
	//カーソルの移動処理
	void MoveCursor(const InputState& input);
	//イラストのアニメーション
	void Animation();
};

