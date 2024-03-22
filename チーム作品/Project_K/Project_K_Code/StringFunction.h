#pragma once
#include <vector>
#include <memory>

class AddString;

//////////////////
// テキスト設定 //
//////////////////
class StringFunction
{
public:
	StringFunction();
	virtual ~StringFunction();

	/// <summary>
	/// 文字を追加する
	/// </summary>
	/// <param name="x">座標</param>
	/// <param name="y">座標</param>
	/// <param name="text">文字</param>
	/// <param name="color">色</param>
	/// <param name="size">大きさ</param>
	/// <param name="font">フォントパス</param>
	virtual void Add(int x, int y, const char* text, int color, int size, const char* font);

	virtual void Draw();

private:
	std::vector<std::shared_ptr<AddString>>m_pAddString;
};

//////////////////
// テキスト作成 //
//////////////////
class AddString
{
public:
	/// <summary>
	/// 文字を追加する
	/// </summary>
	/// <param name="x">座標</param>
	/// <param name="y">座標</param>
	/// <param name="text">文字</param>
	/// <param name="color">色</param>
	/// <param name="size">大きさ</param>
	/// <param name="font">フォントパス</param>//
	AddString(int x, int y, const char* text, int color, int size, const char* font);
	virtual ~AddString();

	virtual void Draw();
private:
	int m_x;
	int m_y;
	const char* m_text;
	int m_color;
	int m_size;
	const char* m_font;
	int m_fontHandle;
};

