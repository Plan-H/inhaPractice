#pragma once
#include "SoulEaterState.h"

class cSoulEater_Idle :
	public cSoulEaterState
{
private:
	DWORD m_dwElapsedTime;
	bool  m_IsAnimBlend;
public:
	cSoulEater_Idle();
	cSoulEater_Idle(cDragonSoulEater*);
	~cSoulEater_Idle();
	void handle() override;
};

