#include"CObstacle.h"
#include"../config/config.h"
class CObsTop :public CObstacle {
public:
	int m_height;
	~CObsTop();
	void InitObs();
	void ShowObs();
	bool IsHitplayer(CPlayer& player);
};