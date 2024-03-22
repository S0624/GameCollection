#pragma once
#include <vector>
#include <memory>
#include "ButtonNo.h"

class ImageAnimation;
/// <summary>
/// UI画像作成クラス
/// </summary>
class UIAnimation
{
public:
	UIAnimation();
	virtual ~UIAnimation() {};

	/// <summary>
	/// ボタン画像のアニメーション
	/// </summary>
	/// <param name="x">位置</param>
	/// <param name="y">位置</param>
	/// <param name="size">大きさ</param>
	/// <param name="animSpeedint">アニメーションの再生スピード</param>
	/// <param name="buttonNo">どのボタンをアニメーションさせるか</param>
	void AddButton(int x,int y,int size,int animSpeedint , ButtonNo buttonNo);
	void Init();
	void End();
	void Update();
	void Draw();
private:
	std::vector<std::shared_ptr<ImageAnimation>>m_pAnimUi;
};

/// <summary>
/// UI画像を複製してアニメーションするクラス
/// </summary>
class ImageAnimation
{
public:
	ImageAnimation(int x, int y, int size, int animSpeed, ButtonNo buttonNo);
	virtual ~ImageAnimation();

	void Init();
	void End();
	void Update();
	void Draw();
	int ImageCut(int cutLeftUpX, int cutLeftUpY,
		int cutRightDownX, int cutRightDownY,
		const char* handle);

private:
	int m_handle;// ボタン画像ハンドル
	const char* m_filmName;
	int m_x;// 位置
	int m_y;// 位置
	int m_size;// 大きさ
	int m_animSpeed;// アニメーションスピード
	ButtonNo m_buttomNo;// どのボタンを描画させるか
	int m_imgX;// 画像の左上
	int m_imgY;// 画像の左上
	int m_imgBottomX;
	int m_imgBottomY;
	int m_frameCount;
	int m_hButton;
	// ごり押し処理用
	// 縦に画像を読み込むか
	// 横に読み込むか
	bool m_isAnimXY;
	bool m_isNoMove;
};
