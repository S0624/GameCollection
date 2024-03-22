#include "BackGround.h"
#include"../Common.h"

BackGround::BackGround() :
    m_scroll(0),
    m_imgIndexWidth(800 * 2.0f),
    m_imgIndexHight(450 * 2.0f)
{
 	m_handle = LoadGraph("Data/Img/kumo.png");
	
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
    // îwåiâÊëúÇÃÉXÉNÉçÅ[Éã
    m_scroll --;
    //m_scroll1 -= 5;
    if (m_scroll < -1600)
    {
        m_scroll = 0;
    }
}

void BackGround::Draw()
{
    // îwåiâÊëúÇÃï\é¶
    DrawExtendGraph(0 + m_scroll, 0, 
                    static_cast<int>(m_imgIndexWidth) + m_scroll, static_cast<int>(m_imgIndexHight),
                    m_handle, false);
    DrawExtendGraph(1600 + m_scroll, 0, 
                    1600 + static_cast<int>(m_imgIndexWidth) + m_scroll, static_cast<int>(m_imgIndexHight),
                    m_handle, false);
 
}
