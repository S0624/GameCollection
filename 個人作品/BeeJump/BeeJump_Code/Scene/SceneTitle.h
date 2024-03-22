#pragma once
#include "SceneBase.h"
#include"../Common.h"

class BackGround;

class SceneTitle :
    public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

	virtual void ShaderInit();
private:
	BackGround* m_pBack;// 背景のポインタ
	int m_titleHandle;
	int m_guidefont;	// 下のガイドに使用するフォント
	int m_cursolNum;	// 選択中の番号
	int m_guideHandle;	// 説明のハンドル
	int m_frameHandle;	// 説明のフレーム

	bool m_pushButton;	// ぼたんをおしたかどうか

	int m_makeScreen;	// シェーダーをかけた画像を表示する変数
	int m_pshandle;		// シェーダーをよみこむ変数
	VERTEX2DSHADER m_vert[6];	// シェーダーを表示するのに使用する頂点
};