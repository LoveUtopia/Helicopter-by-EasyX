#pragma once
#include <easyx.h>
#include "../config/config.h"
class CPlayer {
public:
	int m_x;
	int m_y;
	int m_showid;
	bool isLive;
	IMAGE m_imgPlayer;
public:
	CPlayer();
	~CPlayer();
	void InitPlayer();
	void ShowPlayer();
	void MovePlayer(unsigned);

};