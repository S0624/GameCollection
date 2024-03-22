#include "../Base/MoveTypeBase.h"
class WitchRun :
	public MoveTypeBase
{
public:
	WitchRun();// コンストラクタ
	virtual ~WitchRun() {}// デストラクタ

	void Init();// 初期化

	int IndexX() { return m_animeWidth; }// アニメーションのセット用
	int IndexY() { return m_animeHight; }// アニメーションのセット用
	int AnimeMax() { return m_animeMax; }// アニメーションのセット用
private:
	int m_animeWidth;// 横
	int m_animeHight;// 縦
	int m_animeMax;//末尾
};