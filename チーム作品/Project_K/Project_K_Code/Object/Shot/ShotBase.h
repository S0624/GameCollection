#pragma once
#include"../../Util/Vec2.h"
#include"../../Util/game.h"
class ShotBase
{
protected:
	struct Data
	{
		Vec2 Pos;
		Vec2 Vec;

		int shotSizeLeft = 0;
		int shotSizeTop = 0;
		int shotSizeRight = 0;
		int shotSizeBottom = 0;
	};

	Data m_Shot;

	bool m_Exist = false; // 存在するかどうか
	bool m_NullShot = false;	  // NullShotであるかどうか

	int m_handle = -1; //ショットハンドル

	int m_imageNum = 0; //画像番号
	int m_imageMaxNum; //画像最大番号
	Vec2 m_imageSize;//画像サイズ
	int m_changeSpeed = 0; //画像変更スピード
	int m_changeFrame;//画像変更フレーム
	int m_imageScale = 1;// 画像全体の大きさ
	bool m_isTrans = true;// 画像の反転

	void ChangeImage();//画像変更

public:
	ShotBase();

	virtual ~ShotBase();

	virtual void Update();
	virtual void Draw();

	virtual Vec2 GetPos() { return m_Shot.Pos; }
	virtual int GetSizeLeft() { return m_Shot.shotSizeLeft; }
	virtual int GetSizeTop() { return m_Shot.shotSizeTop; }
	virtual int GetSizeRight() { return m_Shot.shotSizeRight; }
	virtual int GetSizeBottom() { return m_Shot.shotSizeBottom; }

	virtual bool IsExist();

	virtual bool GetExist() { return m_Exist; }
	bool SetExist() { 
		m_Exist = false; 
		return m_Exist; 
	}

	virtual bool GetNullShot() { return m_NullShot; }

	void SetHandle(int handle) { m_handle = handle; }
	void IsSetDir(bool isTrans) { m_isTrans = isTrans; }


};

