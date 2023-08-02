
#include "CObsTop.h"
#include <list>
using namespace std;
class CObstacleList {
public:
	list<CObstacle*> m_lstObs;
	CObstacleList();
	~CObstacleList();
	void ShowAllObs();
	void MoveAllObs();
};