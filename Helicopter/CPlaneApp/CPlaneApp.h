#include "../CGameFrame/GameFrame.h"
#include "../CBack/CBack.h"
#include "../CPlayer/CPlayer.h"
#include "../CObstacle/CObstacleList.h"
#include "../CObstacle/CObsFloat.h"
#include "../config/config.h"
WND_PARAM(BACK_WIDTH + 16, BACK_HEIGHT + 38, 400, 400, L"Ö±Éý»ú")
class CPlaneApp :public CGameFrame {
public:
	int m_score;
	IMAGE m_imgBoard;
	CBack m_back;
	CPlayer m_player;
	CObstacleList m_lstObs;
	virtual void Init();
	virtual void Paint();
	virtual void Close();
	virtual void AddMsg();
	void ShowScore();
	void SetTimer();
	void KillTimer();
	void On_WM_TIMER(WPARAM, LPARAM);
	void On_WM_KEYDOWN(BYTE key);
};
CREATE_OBJECT(CPlaneApp)