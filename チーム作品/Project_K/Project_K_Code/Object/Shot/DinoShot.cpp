#include "DinoShot.h"

DinoShot::~DinoShot()
{
}

void DinoShot::Update()
{
	m_Shot.Pos += m_Shot.Vec;

	ShotBase::Update();
	ChangeImage();
}
