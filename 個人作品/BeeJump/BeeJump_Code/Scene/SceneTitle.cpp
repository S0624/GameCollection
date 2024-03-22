#include "SceneTitle.h"
#include"SceneSelect.h"
#include"../Object/BackGround.h"

SceneTitle::SceneTitle():
	m_titleHandle(0),
	m_guidefont(0),
	m_cursolNum(0),
	m_guideHandle(0),
	m_frameHandle(0),
	m_pushButton(0),
	m_makeScreen(0),
	m_pshandle(0),
	m_vert()
{
	m_pBack = new BackGround();
	// BGM 再生
	Sound::StartBGM(Sound::TitleBGM, 255);
}

SceneTitle::~SceneTitle()
{
	// BGM 停止
	Sound::StopBGM(Sound::TitleBGM);
	delete(m_pBack);
	DeleteGraph(m_titleHandle);
	DeleteFontToHandle(m_guidefont);
	DeleteGraph(m_guideHandle);
	DeleteGraph(m_frameHandle);
	DeleteGraph(m_makeScreen);
	DeleteShader(m_pshandle);
}

void SceneTitle::Init()
{
	// フェード関係の初期化
	m_isFadeOut = IsFadingOut();
	//SetUseASyncLoadFlag(true);	// 非同期読み込みを行いたい

	m_titleHandle = LoadGraph("Data/Img/Title.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン
	// 画像の読み込み
	m_guideHandle = LoadGraph("Data/Img/Main.png");
	m_frameHandle = LoadGraph("Data/Img/MainFrame.png");

	ShaderInit();
	//SetUseASyncLoadFlag(false);	// 非同期読み込みを行いたい

}

void SceneTitle::End()
{
	
}

SceneBase* SceneTitle::Update()
{
	m_pBack->Update(); // 背景の更新処理
	Sound::LoopBGM(Sound::TitleBGM);
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			if (m_cursolNum != 1)
			{
				return (new SceneSelect);
			}
			else
			{
				DxLib_End();                // ＤＸライブラリ使用の終了処理
			}
		}
	}

	// フェードインアウトしていなかったら
	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::PushButton);
			// ボタンが押されたらフレームの色を反転する
			m_pushButton = true;
			StartFadeOut();
		}
		
		// cursor処理
		if (Pad::IsTrigger(PAD_INPUT_UP))
		{
			Sound::PlaySE(Sound::Cursor);
			m_cursolNum++;
		}
		if (Pad::IsTrigger(PAD_INPUT_DOWN))
		{
			Sound::PlaySE(Sound::Cursor);
			m_cursolNum--;
		}
	}
	// 範囲外の数字に行かないようにする
	if (m_cursolNum > 1)
	{
		m_cursolNum = 0;
	}
	else if (m_cursolNum < 0)
	{
		m_cursolNum = 1;
	}

	return this;
}

void SceneTitle::Draw()
{
	m_pBack->Draw();	// 背景の表示

	// 説明の画像の表示
	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight - 230,
		0, 0,
		760, 425,
		1.0f, 0.0f,
		m_guideHandle, true,
		false, false);


	// シェーダの実装
	SetDrawScreen(m_makeScreen);
	// クリアしないとデータが残るためクリアする
	ClearDrawScreen();

	// 選択フレームの画像の表示
	DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
		0, 0,
		760, 425,
		1.0f, 0.0f,
		m_frameHandle, true,
		false, false);
	
		DrawPrimitive2DToShader(m_vert, 6, DX_PRIMTYPE_TRIANGLELIST);
		SetDrawScreen(DX_SCREEN_BACK);			//通常描画に戻す
	// 描画
	if (m_pushButton)
	{
		// シェーダをかけた画像の表示
		DrawGraph(0, 0, m_makeScreen, true);
	}
	// 選択フレームの画像の表示
	else if (!m_pushButton)
	{
		DrawRectRotaGraph(Game::kScreenWidth / 2, (Game::kScreenHeight - 230) + (210 * m_cursolNum),
			0, 0,
			760, 425,
			1.0f, 0.0f,
			m_frameHandle, true,
			false, false);
	}

	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("ステージセレクト ", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 370, "ステージセレクト ", 0xffffff, m_guidefont);
	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("ゲームをおわる ", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 160, "ゲームをおわる ", 0xffffff, m_guidefont);


	// タイトルの文字の表示 
	DrawRotaGraph(Game::kScreenWidth / 2, 250,	// 位置の指定
		1.0f, 0.0f,					// 拡大率、回転率
		m_titleHandle, true, false);	// ハンドル、透過、反転

	// フェードの表示
	SceneBase::DrawFade();
}

void SceneTitle::ShaderInit()
{
	// 画像の読み込み(画像を透過するためにTrueにする)
	m_makeScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// ピクセルシェーダーバイナリコードの読み込み
	m_pshandle = LoadPixelShader("Shader/SamplePS.pso");

	// 頂点データの準備
	m_vert[0].pos = VGet(0.0f, 0.0f, 0.0f);
	m_vert[1].pos = VGet(Game::kScreenWidth - 1, 0.0f, 0.0f);
	m_vert[2].pos = VGet(0.0f, Game::kScreenHeight - 1, 0.0f);
	m_vert[3].pos = VGet(Game::kScreenWidth - 1, Game::kScreenHeight - 1, 0.0f);
	m_vert[0].dif = GetColorU8(255, 255, 255, 255);
	m_vert[0].spc = GetColorU8(0, 0, 0, 0);
	m_vert[0].u = 0.0f; m_vert[0].v = 0.0f;
	m_vert[1].u = 1.0f; m_vert[1].v = 0.0f;
	m_vert[2].u = 0.0f; m_vert[2].v = 1.0f;
	m_vert[3].u = 1.0f; m_vert[3].v = 1.0f;
	m_vert[0].su = 0.0f; m_vert[0].sv = 0.0f;
	m_vert[1].su = 1.0f; m_vert[1].sv = 0.0f;
	m_vert[2].su = 0.0f; m_vert[2].sv = 1.0f;
	m_vert[3].su = 1.0f; m_vert[3].sv = 1.0f;
	m_vert[0].rhw = 1.0f;
	m_vert[1].rhw = 1.0f;
	m_vert[2].rhw = 1.0f;
	m_vert[3].rhw = 1.0f;
	m_vert[4] = m_vert[2];
	m_vert[5] = m_vert[1];

	// 使用するテクスチャをセット
	SetUseTextureToShader(0, m_makeScreen);

	// 使用するピクセルシェーダーをセット
	SetUsePixelShader(m_pshandle);
}
