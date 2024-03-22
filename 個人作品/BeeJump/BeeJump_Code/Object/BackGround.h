#pragma once
class BackGround
{
public:
	BackGround(); // コンストラクタ
	~BackGround();// デストラクタ

	void Update();// 更新処理
	void Draw();  // 描画処理
private:
	int m_handle;
	int m_scroll;
	float m_imgIndexWidth;
	float m_imgIndexHight;
};

