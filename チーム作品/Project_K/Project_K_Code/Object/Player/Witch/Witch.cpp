#include "Witch.h"
#include"../../Util/game.h"
#include "../../Util/DrawFunctions.h"
#include "../../condition.h"
#include"WitchIdle.h"
#include"WitchRun.h"
#include"WitchShotAttack.h"
#include"WitchLongShotAttack.h"
#include"WitchCharge.h"
#include"Chicken.h"
#include"KnightCat.h"
#include"WitchDead.h"
#include"../../Util/Sound.h"

namespace
{
    const char* const kFilmName = "Data/Image/Player/Witch/Witch.png";// 画像のロード
    const int kShiftX = 100;// 魔女の画像サイズが違うのでその分ずらすための変数
}

// コンストラクタ
Witch::Witch() :
    m_handle(0),// 画像
    m_animeWidth(0),// 画像の横
    m_animeHight(0),// 画像の縦
    m_reversal(false),// 画像を反転させるかどうか
    m_animeLoopCount(1),// チャージするときのループする回数をいれる変数
    m_LoopCount(1),// 何回ループしたか数える変数
    m_animeFrame(0),//アニメーションの速さ
    m_animeMax(0),//アニメーションの最大値
    m_indexX(1),// 画像の横の切り取り幅
    m_playerjudge(0),// 画像によるずれを補正する変数
    m_shiftX(0),// 画像のサイズが違うことによる問題を補正する変数
    m_animeFlag(false),// アニメーションが行われているかのフラグ
    m_temp(),// ジャンプ用に元居た高さをいれる変数
    m_jumpFlag(false),// ジャンプ中かどうかのフラグ
    m_jumpPower(5),// ジャンプのパワー
    m_tempFlag1(false),// 攻撃中か（にわとり）　力業実装のために用意しましたその1
    m_tempFlag2(false),// 攻撃中か（ねこちゃん）力業実装のために用意しましたその2
    m_movement(0)// ジャンプするときにXを動かす分
{
    // 魔女の状態のクラスのロード
    m_pIdle = new WitchIdle;// アイドル状態
    m_pRun = new WitchRun;// 走ってる
    m_pShot = new WitchShotAttack;// ちっちゃい氷
    m_pLongShot = new WitchLongShotAttack;// 四連氷
    m_pCharge = new WitchCharge;// チャージ
    m_pChicken = new Chicken;// にわとり
    m_pKnightCat = new KnightCat;// ねこちゃん
    m_pDead = new WitchDead;// 死亡
}

// デストラクタ
Witch::~Witch()
{
    // クラスのデリート処理
    delete m_pIdle;
    delete m_pRun;
    delete m_pShot;
    delete m_pLongShot;
    delete m_pCharge;
    delete m_pChicken;
    delete m_pKnightCat;
    delete m_pDead;

    my::MyDeleteGraph(m_handle);// 画像のデリート
}

// 初期化
void Witch::Init()
{

    m_handle = my::MyLoadGraph(kFilmName);// 画像のロード

    // クラスの初期化
    m_pIdle->Init();
    m_pRun->Init();
    m_pShot->Init();
    m_pLongShot->Init();
    m_pCharge->Init();
    m_pChicken->Init();
    m_pKnightCat->Init();
    m_pDead->Init();

    CharDefaultPos(m_reversal);
}

// 更新処理
void Witch::Update()
{
    UpdateAttackJudge();//当たり判定を呼び出す
    UpdatePlayerJudge();//当たり判定を呼び出す

    if (m_pos.y > 600.0f)
    {
        m_pos.y = 600.0f;
    }

    m_pChicken->Update();// にわとりの更新処理
    m_pKnightCat->Update();// 猫ちゃんの更新処理
    KnockBack();

    // 死亡したら攻撃できなくする
    if (GetHp() <= 0)// HPが0だったら死亡状態にする
    {
        m_moveType = static_cast<int>(moveType::Dead);// 死亡状態にする
    }
    if (m_moveType == static_cast<int>(moveType::Dead))
    {
        UpdateDead();// 死亡アニメーションを呼び出す
    }
    else// HPが0じゃなかったら普通のアニメーションを呼び出す
    {
        UpdateAnim();
    }
    if (m_jumpFlag)// ジャンプフラグがたったらジャンプする
    {
        UpdateJump();// ジャンプ処理
    }
    if (!m_animeFlag && !m_jumpFlag)// フラグがたってなかったら攻撃できるようにする
    {
        UpdateInputKey();// パッドの処理
        UpdatePlayerState();// プレイヤーの状態
    }
}

// 描画処理
void Witch::Draw()
{
    if (!m_isSpawn)
    {
        CharDefaultPos(m_reversal);
        m_isSpawn = true;
    }
    //プレイヤーの描画
    my::MyDrawRectRotaGraph(static_cast<int>(m_pos.x),
        static_cast<int>(m_pos.y),// 表示座標
        48 * m_animeWidth, 48 * m_animeHight,// 切り取り左上
        48 * m_indexX, 48,// 幅、高さ
        3.0f * m_sizeUp, 0.0f,	// 拡大率、回転角度
        m_handle, true, m_reversal);// 画像、透過するか、画像を反転するかどうか


    m_pChicken->Draw(m_sizeUp);// にわとりの描画
    m_pKnightCat->Draw(m_sizeUp);//ねこちゃんの描画

//    // デバッグ描画
//#if DEBUG
//    //DrawBox(static_cast<int> (m_pos.x) + m_sizeLeft,
//    //    static_cast<int> (m_pos.y) + m_sizeTop,
//    //    static_cast<int> (m_pos.x) + m_sizeRight,
//    //    static_cast<int> (m_pos.y) + m_sizeBottom,
//    //    0x00ff00, false);
//
//    //if (m_attackFlag)
//    //{
//    //    DrawBox(m_attackSizeLeft,
//    //        m_attackSizeTop,
//    //        m_attackSizeRight,
//    //        m_attackSizeBottom,
//    //        0xff0000, false);
//    //}
//
//    if (m_attackFlag)
//    {
//        DrawBox(static_cast<int> (m_pos.x) + m_attackSizeLeft,
//            static_cast<int> (m_pos.y) + m_attackSizeTop,
//            static_cast<int> (m_pos.x) + m_attackSizeRight,
//            static_cast<int> (m_pos.y) + m_attackSizeBottom,
//            0xff0000, false);
//    }
//    DrawFormatString(200, 0, 0xffffff, "%d", m_attackSizeLeft);
//#endif
}

// パッドがおされた時の状態
void Witch::UpdateInputKey()
{
    if (Pad::IsPress(PAD_INPUT_RIGHT, m_padNum))// 右
    {
        m_pos.x += 10;// 移動量
        m_reversal = false;// 画像の反転
        m_moveType = static_cast<int>(moveType::Run);// 走り状態
    }
    else if (Pad::IsPress(PAD_INPUT_LEFT, m_padNum))// 左
    {
        m_pos.x -= 10;//移動量
        m_reversal = true;// 画像の反転
        m_moveType = static_cast<int>(moveType::Run);// 走り状態
    }
    if (!m_tempFlag1 && !m_tempFlag2)// 力業実装、フラグがたってなかったら攻撃できます
    {
        if (Pad::IsPress(PAD_INPUT_UP, m_padNum))// 上
        {
            m_temp = m_pos.y - 150;// ジャンプしたときの上の上限
            m_jumpFlag = true;// ジャンプしたフラグを建設する
        }
        if (Pad::IsPress(PAD_INPUT_UP, m_padNum) && Pad::IsPress(PAD_INPUT_LEFT, m_padNum))// 移動しながらジャンプ
        {
            m_temp = m_pos.y - 150;// ジャンプしたときの上の上限
            m_movement = -10;// 移動量
            m_jumpFlag = true;// ジャンプフラグの建設
        }
        if (Pad::IsPress(PAD_INPUT_UP, m_padNum) && Pad::IsPress(PAD_INPUT_RIGHT, m_padNum))// 移動しながらジャンプ
        {
            m_temp = m_pos.y - 150;// ジャンプしたときの上の上限
            m_movement = 10;// 移動量
            m_jumpFlag = true;// ジャンプフラグの建設
        }
        m_attackFlag = false;// 最初に攻撃中のフラグを初期化してあげる
        if (Pad::IsTrigger(PAD_INPUT_1, m_padNum))// 小攻撃
        {
            m_moveType = static_cast<int>(moveType::Attack1);// 攻撃1状態
            m_animeFlag = true;// アニメーションフラグの建設
            m_attackFlag = true;// 攻撃中のフラグの建設
            m_damage = 7;// ダメージ
            // 画像が反転していた時の処理
            if (m_reversal)
            {
                m_playerjudge = 20;// 画像の「ずれ」を補正
                m_attackSizeLeft = 20 - 100;// 攻撃判定
                m_attackSizeTop = -20;// 攻撃判定
                m_attackSizeRight = 80 - 100;// 攻撃判定
                m_attackSizeBottom = 60;// 攻撃判定
            }
            //そうじゃなかった時の処理 
            else
            {
                m_playerjudge = -20;// 画像の「ずれ」を補正
                m_attackSizeLeft = 20;// 攻撃判定
                m_attackSizeTop = -20;// 攻撃判定
                m_attackSizeRight = 80;// 攻撃判定
                m_attackSizeBottom = 60;// 攻撃判定
            }
        }
        else if (Pad::IsTrigger(PAD_INPUT_2, m_padNum))// 中攻撃
        {
            m_moveType = static_cast<int>(moveType::Attack2);// 攻撃2状態
            m_animeFlag = true;// アニメーションフラグの建設
            m_attackFlag = true;// 攻撃中のフラグの建設
            m_pLongShot->SetReversal(m_reversal);// 反転させるかどうか
            m_damage = 10;// ダメージ量
            // 画像が反転していた時の処理
            if (m_reversal)
            {
                m_pos.x -= kShiftX;//画像サイズが違うのでキャラの位置に違和感を与えないようにずらしてあげる
                m_playerjudge = 100;// 画像の「ずれ」を補正
                m_attackSizeLeft = -140;// 攻撃判定
                m_attackSizeTop = -20;// 攻撃判定
                m_attackSizeRight = 50;// 攻撃判定
                m_attackSizeBottom = 80;// 攻撃判定
            }
            //そうじゃなかった時の処理 
            else
            {
                m_pos.x += kShiftX;//画像サイズが違うのでキャラの位置に違和感を与えないようにずらしてあげる
                m_playerjudge = -100;// 画像の「ずれ」を補正
                m_attackSizeLeft = -50;// 攻撃判定
                m_attackSizeTop = -20;// 攻撃判定
                m_attackSizeRight = 140;// 攻撃判定
                m_attackSizeBottom = 80;// 攻撃判定
            }
        }
        else if (Pad::IsTrigger(PAD_INPUT_3, m_padNum))// 中攻撃
        {
            m_moveType = static_cast<int>(moveType::Attack3);// 攻撃3状態
            m_animeFlag = true;// アニメーションフラグの建設
            m_animeLoopCount = 2;// チャージのアニメーションのループ数
        }
        //強攻撃
        else if (Pad::IsTrigger(PAD_INPUT_4, m_padNum))
        {
            m_moveType = static_cast<int>(moveType::Attack4);// 攻撃4状態
            m_animeFlag = true;// アニメーションフラグの建設
            m_animeLoopCount = 3;// チャージのアニメーションのループ数
        }
    }
}

// プレイヤーの状態
void Witch::UpdatePlayerState()
{
    if (m_moveType == static_cast<int>(moveType::Idol))// 通常状態
    {
        m_animeWidth = m_pIdle->IndexX();// どこの位置からアニメーションするかの指定
        m_animeMax = m_pIdle->AnimeMax();// アニメーションの末尾の設定
    }
    if (m_moveType == static_cast<int>(moveType::Run))// 走り
    {
        m_animeWidth = m_pRun->IndexX();// どこの位置からアニメーションするかの指定
        m_animeMax = m_pRun->AnimeMax();// アニメーションの末尾の設定
    }
    if (m_moveType == static_cast<int>(moveType::Attack1))// 小攻撃（氷）
    {
        m_animeWidth = m_pShot->IndexX();// どこの位置からアニメーションするかの指定
        m_animeHight = m_pShot->IndexY();// 縦の番号を0にもどす
        m_animeMax = m_pShot->AnimeMax();// アニメーションの末尾の設定
        Sound::play(Sound::WitchAttack1);
    }
    if (m_moveType == static_cast<int>(moveType::Attack2))// 中攻撃（氷四連）
    {
        m_pLongShot->Update();
        m_animeWidth = m_pLongShot->IndexX();// どこの位置からアニメーションするかの指定
        m_animeHight = m_pLongShot->IndexY();// 縦の番号を0にもどす
        m_indexX = m_pLongShot->SizeX();// 画像サイズの変更
        m_shiftX = m_pLongShot->ShiftX();// 画像サイズの変更に伴うずらす位置の取得
        m_animeMax = m_pLongShot->AnimeMax();// アニメーションの末尾の設定
        Sound::play(Sound::WitchAttack2);
    }
    if (m_moveType == static_cast<int>(moveType::Attack3))// 中攻撃（ニワトリー）
    {
        m_animeWidth = m_pCharge->IndexX();// どこの位置からアニメーションするかの指定
        m_animeHight = m_pCharge->IndexY();// 縦の番号を0にもどす
        m_animeMax = m_pCharge->AnimeMax();// アニメーションの末尾の設定
        Sound::play(Sound::WitchCharge);// SEをならす
    }
    if (m_moveType == static_cast<int>(moveType::Attack4))// 強攻撃（ねこちゃん）
    {
        m_animeWidth = m_pCharge->IndexX();// どこの位置からアニメーションするかの指定
        m_animeHight = m_pCharge->IndexY();// 縦の番号を0にもどす
        m_animeMax = m_pCharge->AnimeMax();// アニメーションの末尾の設定
        Sound::play(Sound::WitchCharge);// SEをならす
    }
    //if (m_moveType == static_cast<int>(moveType::Damage))// ダメージをうけた
    //{

    //}
    if (m_moveType == static_cast<int>(moveType::Dead))// 死亡
    {
        m_animeWidth = m_pDead->IndexX();// どこの位置からアニメーションするかの指定
        m_animeHight = m_pDead->IndexY();// 縦の番号を0にもどす
        m_animeMax = m_pDead->AnimeMax();// アニメーションの末尾の設定
        m_animeFlag = true;// フラグを立てる
    }
}

// プレイヤーのジャンプ処理
void Witch::UpdateJump()
{
    m_pos.y -= m_jumpPower;// ジャンプパワーを足して飛んでもらう
    m_pos.x += m_movement;// 移動しながらジャンプしてたら飛びながら移動してもらう
    if (m_pos.y < (m_temp))// 保存した数より上に言ったらジャンプパワーをマイナスにして落ちてきていただく
    {
        m_jumpPower = -7;
    }

    if (m_pos.y > m_temp + 150)
    {
        m_jumpFlag = false;// ふらぐをもどす
        m_pos.y = m_temp + 150;// 最初の位置に戻す
        m_jumpPower = 5;// ジャンプパワー
        m_movement = 0;// 移動量の初期化
    }
}

// プレイヤーの通常状態アニメーション処理
void Witch::UpdateAnim()
{
    m_animeFrame++;// アニメーションのインターバル
    if (m_animeFrame > 10)
    {
        m_animeHight++;// アニメーションを足す
        m_animeFrame = 0;// インターバルを戻す
    }
    if (m_animeHight >= m_animeMax)// マックスになったら
    {
        m_LoopCount++;// ループの数を足す
        m_animeHight = 0;// アニメーションを一番上まで戻す
        if (m_LoopCount >= m_animeLoopCount)// ループカウントに一致していたら
        {
            m_indexX = 1;// 1番目（アイドル状態）に戻す
            m_animeFlag = false;// フラグを戻す
            if (m_reversal)// 反転していたらずらした分を-する
            {
                m_shiftX *= -1;
            }
            m_playerjudge = 0;// ずれをもどす
            m_pos.x += m_shiftX;// ずれをもどす
            m_shiftX = 0;// 初期化 
            m_LoopCount = 0;// 初期化
            m_animeLoopCount = 1;// 初期化（１回は必ずアニメーションするので1）

            // チャージが終わって攻撃タイプが3だったら
            if (m_moveType == static_cast<int>(moveType::Attack3))
            {
                if (!m_pChicken->IsExist())
                {
                    m_pChicken->SetReversal(m_reversal);
                    m_pChicken->SetPos(m_pos);
                    m_attackFlag = true;
                    m_damage = 12;// ダメージ量
                }
                m_pChicken->SetFlag(true);
            }
            // チャージが終わって攻撃タイプが4だったら
            if (m_moveType == static_cast<int>(moveType::Attack4))
            {
                if (!m_pKnightCat->IsExist())
                {
                    m_pKnightCat->SetReversal(m_reversal);;
                    m_pKnightCat->SetPos(m_pos);
                    m_attackFlag = true;
                    m_damage = 20;// ダメージ量
                }
                m_pKnightCat->SetFlag(true);
            }
            m_moveType = static_cast<int>(moveType::Idol);
        }
    }
    //このへん超力業実装だから直したいな
    if (m_pChicken->IsExist())// にわとりの当たり判定
    {
        m_attackSizeLeft = static_cast<int>((m_pChicken->GetPos().x - m_pos.x) + (m_pChicken->GetMovePos()) - 20);
        m_attackSizeTop = -50;
        m_attackSizeRight = static_cast<int>((m_pChicken->GetPos().x - m_pos.x) + m_pChicken->GetMovePos()) + 30;
        m_attackSizeBottom = 50;
    }
    else if (m_pKnightCat->IsExist())// ねこちゃんの当たり判定
    {
        m_attackSizeLeft = static_cast<int>((m_pKnightCat->GetPos().x - m_pos.x) + (m_pKnightCat->GetMovePos()) - 20);
        m_attackSizeTop = 0;
        m_attackSizeRight = static_cast<int>((m_pKnightCat->GetPos().x - m_pos.x) + (m_pKnightCat->GetMovePos()) + 40);
        m_attackSizeBottom = 60;
    }
    m_tempFlag1 = m_pChicken->IsExist();// 画面上に存在していたらフラグを立てる
    m_tempFlag2 = m_pKnightCat->IsExist();// 画面上に存在していたらフラグを立てる
}

// プレイヤーの死亡アニメーション処理
void Witch::UpdateDead()
{
    m_animeFrame++;// フレームを足す
    if (m_animeFrame > 10)
    {
        m_animeHight++;// アニメーションを進める
        m_animeFrame = 0;// フレームを戻す
    }
    // アニメーションが最後まで行ったら
    if (m_animeHight >= m_animeMax)
    {
        m_animeHight = m_animeMax;//一番最後の画像で止める（死んでいるので0に戻さなくていい）
    }
}

//プレイヤーの当たり判定
void Witch::UpdatePlayerJudge()
{
    m_sizeLeft = static_cast<int>(-30 + m_playerjudge);// 左
    m_sizeTop = static_cast<int>(-40);// 上
    m_sizeRight = static_cast<int>(30 + m_playerjudge);// 右
    m_sizeBottom = static_cast<int>(40);// 下
}

//プレイヤーの攻撃の当たり判定
void Witch::UpdateAttackJudge()
{
    //フラグがたっていなかったらたらあたりはんていを初期化
    if (!m_attackFlag)
    {
        m_attackSizeLeft = 0;
        m_attackSizeTop = 0;
        m_attackSizeRight = 0;
        m_attackSizeBottom = 0;
        m_damage = 0;
    }

    if (m_tempFlag1 || m_tempFlag2)// どっちかがたってたら攻撃中
    {
        m_attackFlag = true;
    }

}