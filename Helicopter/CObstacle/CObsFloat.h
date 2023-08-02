#include"CObstacle.h"
class CObsFloat :public CObstacle {
public:
	~CObsFloat();
	void InitObs();
	void ShowObs();
	bool IsHitplayer(CPlayer& player);
};