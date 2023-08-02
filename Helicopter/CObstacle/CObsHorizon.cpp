#include"CObsHorizon.h"
CObsHorizon::~CObsHorizon(){}
void CObsHorizon::InitObs(){
	m_x = 1000;
	m_y = 1000;
}
void CObsHorizon::ShowObs(){
}
bool CObsHorizon::IsHitplayer(CPlayer& player){
	if(player.m_y >= 120)
	return true;
	else
	return false;
}