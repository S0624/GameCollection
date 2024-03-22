#pragma once

#include<map>
#include<vector>
#include<string>

enum class InputType {
	next,	//次へ行くボタン
	back,	//前に戻るボタン
	pause,	//ポーズボタン
	up,			//上
	down,		//下
	right,		//右
	left,		//左
	end,		//終わる
	change,		//変更
	max			//最大入力インデックス
};

/// <summary>
/// 入力装置カテゴリ
/// </summary>
enum class InputCategory
{
	keybd,	//キーボード
	pad,	//ゲームパッド
};

struct InputInfo
{
	InputCategory cat;	//入力装置カテゴリ
	int id;	//入力ID(KEY_INPUT～	PAD～_INPUT		MOUSE～_INPUT)
};


class InputState
{
private:
	//仮想入力情報と実際の入力テーブルを作る
	//キー（first） = InputType
	//値（second） = std::vector<InputInfo>
	using InputMap_t = std::map<InputType, std::vector<InputInfo>>;		//実際の入力と対応のボタン
	InputMap_t m_inputMapTable;		//実際の入力と対応のボタン

	//書き換えようの一時的なinputMapTable_のコピー
	//いきなり書き換えてしまわないように
	InputMap_t m_tempMapTable;

	//リセット用のマップテーブル
	InputMap_t m_defaultMapTable;

	//入力タイプとその名前
	std::map<InputType, std::wstring>m_inputNameTable;

	std::vector<bool> m_currentInput;		//現在の入力方法(押しているか押していないか)
	std::vector<bool> m_lastInput;			//直前の入力情報(直前押しているか押していないか)

public:
	InputState();
	/// <summary>
	/// 押した瞬間にTrueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押した瞬間ならTrue、それ以外ならFalse</returns>
	bool IsTrigger(InputType type)const;
	/// <summary>
	/// 押されてたらTrueになる
	/// </summary>
	/// <param name="type">InputType</param>
	/// <returns>押されてたらTrue、それ以外はFlase</returns>
	bool IsPressed(InputType type)const;
	/// <summary>
	/// 入力状態を更新
	/// （注意）毎フレームUpdateをよばなければ更新されない
	/// </summary>
	void Update();

	/// <summary>
	/// 入力情報を更新
	/// </summary>
	/// <param name="type">ゲームにおける入力種別</param>
	/// <param name="cat">入力カテゴリ</param>
	/// <param name="id">実際の入力</param>
	void RewriteInpurInfo(InputType type, InputCategory cat, int id){};

	/// <summary>
	/// 現在編集中のキーコンフィグを確定する
	/// </summary>
	void CommitChangedInputInfo(){};

	/// <summary>
	/// 現在編集中のキーコンフィグの変更をなかったことにする
	/// </summary>
	void RollbackChangedInputInfo(){};
};

