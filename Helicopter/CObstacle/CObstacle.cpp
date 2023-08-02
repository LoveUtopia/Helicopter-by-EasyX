#include"CObstacle.h"
random_device CObstacle::rd;
CObstacle::CObstacle():m_x(0),m_y(0){}
CObstacle:: ~CObstacle(){}
void CObstacle::MoveObs() {
	m_x -= OBS_MOVE_STEP;
}
