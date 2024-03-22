#pragma once
#include"Vec2.h"
class StageBase;		// ステージ

class SelectUI
{
private:
	// 構造体
	struct  CharData// 各キャラクタが持つ情報
	{
		float m_posY = 0;// 位置
		int m_imgWidth = 0;// 切り取る幅
		int m_imgHight = 0;// 切り取る高さ
		float m_imgSize = 0;// 画像の大きさ（拡大率）
		int m_handle = -1;// 画像

		int m_maxWidth = 0;// アニメーションの横の最大値
		int m_maxHight = 0;// アニメーションの縦の最大値
		int m_animFrame = 0;// アニメーションの速度（フレーム数）
		const char* m_text = 0;// テキスト（キャラ名）
		int m_font = 0;// 使用するフォント
	};
public:

	SelectUI();// コンストラクタ
	virtual ~SelectUI();// デストラクタ

	void Init(int StageNo);// 初期化
	void Update();// 更新処理
	void Draw();// 描画処理

	void InitLoad();// ロード処理
	void InitFont();// ロード処理
	void InitChar();// キャラクタの初期化処理
	void SetCursor(int cursor1, int cursor2) { m_cursor1 = cursor1; m_cursor2 = cursor2; }// カーソルを受け取る関数
	void SetCursorFlag(bool cursorFlag1, bool cursorFlag2) { m_cursorFlag1 = cursorFlag1; m_cursorFlag2 = cursorFlag2; }// カーソルのフラグを受け取る
	void UpdateAnimation();// アニメーション処理
	void UpdateChar(int cursor, int selectNum);//選ばれているカーソルによって処理を変える
	void UpdateCursor();// カーソルの移動処理
	void DrawChar();// キャラクタの描画処理
	void DrawLetter();//テキストの描画処理
	void DrawCursor();//	カーソルの表示

private:
	/// <summary>
	/// 各キャラクターの初期化
	/// </summary>
	/// <param name="charaData">各キャラクターが持つ情報</param>
	/// <param name="imgWidth">切り取る幅</param>
	/// <param name="imgHight">切り取る高さ</param>
	/// <param name="imgSize">画像の大きさ(拡大率)</param>
	/// <param name="posY">位置</param>
	/// <param name="maxWidth">アニメーションの横の最大値</param>
	/// <param name="maxHight">アニメーションの縦の最大値</param>
	/// <param name="animFrame">アニメーションの速度(フレーム)</param>
	/// <param name="text">テキスト(キャラ名)</param>
	/// <param name="font">使用するフォント</param>
	void InitCharas(CharData& charaData, 
		int imgWidth, int imgHight, 
		float imgSize, int maxWidth, 
		int maxHight, int animFrame, 
		const char* text, int font);

private:
	StageBase* m_pStageBase;	// ステージセレクトシーン

	CharData m_temp;// 一時的に保存する用の変数
	CharData m_player1;// 1P
	CharData m_player2;// 2P
	CharData m_dino;// 恐竜くん
	CharData m_elf;// エルフくん
	CharData m_kinnniku;// 筋肉くん
	CharData m_witch;// 魔女

private:
	//画像を入れる変数
	int m_frameHandle;// 枠
	int m_buttonHandle;// ぼたん
	int m_dinoHandle;// 恐竜くん
	int m_elfHandle;// エルフくん
	int m_kinnikuHandle;// 筋肉くん
	int m_witchHandle;// 魔女

	// アニメーション関係
	int m_frameCount1;// 1Pのアニメーション用フレーム
	int m_indexWidth1;// 1Pのアニメーション用縦
	int m_indexHight1;// 1Pのアニメーション用横
	int m_frameCount2;// 2Pのアニメーション用フレーム
	int m_indexWidth2;// 2Pのアニメーション用縦
	int m_indexHight2;// 2Pのアニメーション用横
	int m_buttonAnimframe;// buttonのアニメーション用フレーム
	int m_animInterval;//buttonのアニメーションが始まるまでのinterval
	int m_buttonIndexWidth;//buttonの画像を変更する

	int m_centerPos1P;// 1Pの名前の中心位置を取得する
	int m_centerPos2P;// 2Pの名前の中心位置を取得する

	int m_cursor1;// カーソルの位置保存1P用
	int m_cursor2;// カーソルの位置保存2P用
	bool m_cursorFlag1;// カーソルのフラグ保存1P用
	bool m_cursorFlag2;// カーソルのフラグ保存2P用

	int m_cursolHeight;// カーソルのYの位置
};