#include"CObsFloat.h"
#include"../CPlayer/CPlayer.h"
CObsFloat::~CObsFloat() {}
void CObsFloat::InitObs() {
	m_x = BACK_WIDTH;
	m_y = (rd())%204+64;
	::loadimage(&m_imgObs, L"./res/obstacle.png");
}
void CObsFloat::ShowObs() {
	::putimage(m_x, m_y, &m_imgObs);
}
bool CObsFloat::IsHitplayer(CPlayer& player) {
	int x1 = player.m_x + 61;
	int y1 = player.m_y + 15;
	if (x1 >= m_x && x1 <= m_x + OBS_WIDTH && y1 <= m_y + OBS_HEIGHT && y1 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x2 = player.m_x + 41;
	int y2 = player.m_y + 30;
	if (x2 >= m_x && x2 <= m_x + OBS_WIDTH && y2 <= m_y + OBS_HEIGHT && y2 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x3 = player.m_x + 39;
	int y3 = player.m_y + 10;
	if (x3 >= m_x && x3 <= m_x + OBS_WIDTH && y3 <= m_y + OBS_HEIGHT && y3 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x4 = player.m_x + 20;
	int y4 = player.m_y + 12;
	if (x4 >= m_x && x4 <= m_x + OBS_WIDTH && y4 <= m_y + OBS_HEIGHT && y4 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x5 = player.m_x + 5;
	int y5 = player.m_y + 15;
	if (x5 >= m_x && x5 <= m_x + OBS_WIDTH && y5 <= m_y + OBS_HEIGHT && y5 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x6 = player.m_x + 30;
	int y6 = player.m_y + 30;
	if (x6 >= m_x && x6 <= m_x + OBS_WIDTH && y6 <= m_y + OBS_HEIGHT && y6 >= m_y) {
		player.isLive = false;
		return true;
	}

	int x7 = player.m_x + 55;
	int y7 = player.m_y + 30;
	if (x7 >= m_x && x7 <= m_x + OBS_WIDTH && y7 <= m_y + OBS_HEIGHT && y7 >= m_y) {
		player.isLive = false;
		return true;
	}
	return false;
}