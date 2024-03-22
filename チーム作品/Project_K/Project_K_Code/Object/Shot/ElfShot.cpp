#include "ElfShot.h"

ElfShot::~ElfShot()
{
}

void ElfShot::Update()
{
	m_Shot.Pos += m_Shot.Vec;

	ShotBase::Update();
}

