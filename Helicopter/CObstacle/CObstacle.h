#pragma once
#include <easyx.h>
#include"../CPlayer/CPlayer.h"
#include"../config/config.h"
#include <random>
using namespace std;
class CObstacle {
public:
	int m_x;
	int m_y;
	IMAGE m_imgObs;
	static random_device rd;
public:
	CObstacle();
	virtual ~CObstacle();
	virtual void InitObs() = 0;
	virtual void ShowObs() = 0;
	void MoveObs();
	virtual bool IsHitplayer(CPlayer& player) = 0;
};