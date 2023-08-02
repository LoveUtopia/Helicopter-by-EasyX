#include "CObstacleList.h"

void CObstacleList::ShowAllObs()
{
	for (CObstacle* obs : m_lstObs) {
		obs->ShowObs();
	}
}
CObstacleList::CObstacleList(){}
CObstacleList::~CObstacleList(){
	list<CObstacle*>::iterator it = m_lstObs.begin();
	while (it != m_lstObs.end()) {
		if (*it) {
			delete* it;
			*it = nullptr;
			
		}
		it++;
	}
	m_lstObs.clear();
}
void CObstacleList::MoveAllObs(){
	for (CObstacle* obs : m_lstObs) {
		obs->MoveObs();
	}
}