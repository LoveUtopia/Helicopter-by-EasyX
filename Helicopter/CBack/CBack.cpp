#include "CBack.h"
#include "../config/config.h"
CBack::CBack() :m_x(0), m_y(0) {}
CBack::~CBack() {}
void CBack::InitBack() {
	::loadimage(&m_imgBack, L"./res/back.png"); //ͼƬ·������ڹ���·����˵��
	m_x = 0;
	m_y = 0;
}
void CBack::ShowBack() {
	::putimage(m_x, m_y, &m_imgBack);
}
void CBack::MoveBack() {
	m_x -= BACK_MOVE_STEP;
	if (m_x <= -BACK_WIDTH) {
		m_x = 0;
	}
}