#include"CObstacle.h"
class CObsHorizon:public CObstacle{
public:
	~CObsHorizon();
	void InitObs();
	void ShowObs();
	bool IsHitplayer(CPlayer& player);
};