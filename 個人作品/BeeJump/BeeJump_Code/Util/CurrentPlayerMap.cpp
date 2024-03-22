#include "CurrentPlayerMap.h"

CurrentPlayerMap::CurrentPlayerMap(int maxMapPosX):
	m_maxMapPosX(maxMapPosX),
	m_minMapHandle(-1),
	m_playerHandle(-1),
	m_playerStartPos(0),
	m_playerPosX(0),
	m_playerMove(0),
	m_mapRate(3.0f),
	m_mapHandleSizeWidth(),
	m_mapHandleSizeHight(),
	m_playerHandleSizeWidth(),
	m_playerHandleSizeHight()
{
	// 画像のロード
	m_minMapHandle = LoadGraph("Data/Img/MinMap.png");
	m_playerHandle = LoadGraph("Data/Img/Bee.png");

	// 画像サイズの取得
	GetGraphSize(m_minMapHandle,&m_mapHandleSizeWidth, &m_mapHandleSizeHight);
	GetGraphSize(m_playerHandle,&m_playerHandleSizeWidth, &m_playerHandleSizeHight);

	// プレイヤー(画像)のスタート地
	m_playerStartPos = 220 - (m_mapHandleSizeWidth / 2 + m_playerHandleSizeWidth / 2);
	// プレイヤー(画像)の現在地
	m_playerPosX = m_playerStartPos;
}

CurrentPlayerMap::~CurrentPlayerMap()
{
	// 画像の削除処理
	DeleteGraph(m_minMapHandle);
	DeleteGraph(m_playerHandle);
}

void CurrentPlayerMap::Update()
{
	// プレイヤー(画像)をスクロールさせる
	m_playerMove++;
	// 最大値よりスクロールしないように処理
	if (m_playerMove > m_maxMapPosX)
	{
		m_playerMove = m_maxMapPosX;
	}
	// プレイヤー(画像)の移動させる
	// 今の場所　 = 進んだ距離 * ゲージの長さ/ゲージの最大数
	m_playerPosX = m_playerStartPos + (m_playerMove * (100 * m_mapRate) / m_maxMapPosX);

}

void CurrentPlayerMap::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);			// ブレンドモードをいじってスコアのパネルを半透明にする
	DrawBox(20, 30, 400, 180, 0x000000, true);
														// スコア版の表示
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);			//通常描画に戻す

	// マップ(画像)の表示
	DrawRectRotaGraph(200, 70,
		0, 0, m_mapHandleSizeWidth, m_mapHandleSizeHight,
		m_mapRate, 0.0f,
		m_minMapHandle,
		true, false);

	// プレイヤー(画像)の表示
	DrawRectRotaGraph(m_playerPosX, 70,
		0, 0, m_playerHandleSizeWidth, m_playerHandleSizeHight,
		0.35f, 0.0f,
		m_playerHandle,
		true, false);
}
