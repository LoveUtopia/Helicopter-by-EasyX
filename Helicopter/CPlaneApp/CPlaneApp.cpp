#include "CPlaneApp.h"
void CPlaneApp::Init(){
	m_back.InitBack();
	m_player.InitPlayer();
	SetTimer();
}
void CPlaneApp::Paint(){
	m_back.ShowBack();
	m_player.ShowPlayer();
	m_lstObs.ShowAllObs();
	ShowScore();
}
void CPlaneApp::Close(){
	KillTimer();
}
void CPlaneApp::AddMsg(){
	ADD_MSG(WM_TIMER, EX_WINDOW, CPlaneApp)
    ADD_MSG(WM_KEYDOWN,EX_KEY,CPlaneApp)
	CGameFrame::AddMsg();
}
void CPlaneApp::ShowScore(){
	WCHAR arr[5] = { 0 };
	_itow_s(m_score, arr, 10);
	wstring str = L"����:";
	str += arr;
	::setbkmode(TRANSPARENT);
	::settextcolor(RGB(30, 200, 166));
	RECT rect = { 0,0, 60, 30 };
	//��ʾ���ֵ�ָ��λ�ã����ã�ˮƽ����ֱ����
	::drawtext(str.c_str(), &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void CPlaneApp::SetTimer(){
	::SetTimer(m_hWnd, BACK_MOVE_TIMERID/*��ʱ��id*/, BACK_MOVE_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, PLAYER_MOVE_TIMERID/*��ʱ��id*/, PLAYER_MOVE_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, CHANGE_PIC_TIMERID/*��ʱ��id*/, CHANGE_PIC_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, OBST_CREATE_TIMERID/*��ʱ��id*/, OBST_CREATE_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, OBSF_CREATE_TIMERID/*��ʱ��id*/, OBSF_CREATE_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, OBS_MOVE_TIMERID/*��ʱ��id*/, OBS_MOVE_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, DELETE_OBS_TIMERID/*��ʱ��id*/, DELETE_OBS_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, CHECK_BOOM_TIMERID/*��ʱ��id*/, CHECK_BOOM_INTERVAL/*Ƶ��*/, nullptr);
	::SetTimer(m_hWnd, SCORE_TIMERID/*��ʱ��id*/, SCORE_INTERVAL/*Ƶ��*/, nullptr);
	
}
void CPlaneApp::KillTimer(){
	::KillTimer(m_hWnd, BACK_MOVE_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, PLAYER_MOVE_TIMERID/*��ʱ��id*/);

	::KillTimer(m_hWnd, OBST_CREATE_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, OBSF_CREATE_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, OBS_MOVE_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, DELETE_OBS_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, CHECK_BOOM_TIMERID/*��ʱ��id*/);
	::KillTimer(m_hWnd, SCORE_TIMERID);
	
}
void CPlaneApp::On_WM_TIMER(WPARAM w, LPARAM l){
	switch (w) {
	case BACK_MOVE_TIMERID:
		m_back.MoveBack();
		break;
	case PLAYER_MOVE_TIMERID:
		m_player.MovePlayer(NULL);
		break;
	case CHANGE_PIC_TIMERID:
		if (++m_player.m_showid > 3&&m_player.isLive) {
			m_player.m_showid = 0;
		}
		else {
			++m_player.m_showid;
		}
		break;
	case OBST_CREATE_TIMERID:{
		CObsTop* obsTop = new CObsTop;
		obsTop->InitObs();
		m_lstObs.m_lstObs.push_back(obsTop); 
	}
	    break;
	case OBSF_CREATE_TIMERID: {
		CObsFloat* obsFloat = new CObsFloat;
		obsFloat->InitObs();
		m_lstObs.m_lstObs.push_back(obsFloat);
	}   break;
	case DELETE_OBS_TIMERID:{
		list<CObstacle*>::iterator it = m_lstObs.m_lstObs.begin();
		while (it != m_lstObs.m_lstObs.end()||!m_player.isLive) {
			if ((*it)->m_x <= -OBS_WIDTH) {
				delete* it;
				*it = nullptr;
				it = m_lstObs.m_lstObs.erase(it);
				continue;
			}
			it++;
		}
	}
	    break;
	case OBS_MOVE_TIMERID: {
		m_lstObs.MoveAllObs();
	}break;
	case CHECK_BOOM_TIMERID: {
		list<CObstacle*>::iterator it = m_lstObs.m_lstObs.begin();
		while (it != m_lstObs.m_lstObs.end()) {
			if ((*it)->IsHitplayer(m_player) || !m_player.isLive) {
				KillTimer();
				::MessageBox(m_hWnd, L"GameOver", L"��ʾ", MB_OK);
				::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
			}
			it++;
		}
	}
	break;
	case SCORE_TIMERID: {
		++m_score;
	}
	break;
	}
}
void CPlaneApp::On_WM_KEYDOWN(BYTE key) {
	m_player.MovePlayer(key);
}