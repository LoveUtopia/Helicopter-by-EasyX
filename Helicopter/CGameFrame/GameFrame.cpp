
#include"GameFrame.h"

void CGameFrame::InitGame(int width, int height, int x, int y, LPCWSTR title) {
	//��������
	m_hWnd = ::initgraph(width, height);

	//�趨���ڵı���ɫΪ��ɫ
	::setbkcolor(RGB(255, 255, 255));
	::cleardevice();   //1. ��ʱ���±���ɫ

	//�ƶ�����
	::MoveWindow(m_hWnd, x, y, width, height, TRUE);
	//���ô��ڱ���
	::SetWindowText(m_hWnd, title);

	//�����Ϣ
	AddMsg();

	//���ô��ڵ�����  , 
	::SetWindowLong(m_hWnd, GWL_WNDPROC/*  �˺�Ϊ32λ�µĺ�  */,(LONG)&CGameFrame::RunGame); //���ô��ڵĻص�����

	//������Ϸ�ĳ�ʼ��
	Init();

}

void CGameFrame::AddMsg() {
	/*m_msgMap[WM_LBUTTONDOWN] = new MsgTypeFun{ EX_MOUSE };
	m_msgMap[WM_LBUTTONDOWN]->p_fun_EX_MOUSE = &CGameFrame::On_WM_LBUTTONDOWN;*/
	
	ADD_MSG(WM_CLOSE, EX_WINDOW,CGameFrame)
	ADD_MSG(WM_PAINT, EX_WINDOW,CGameFrame)
}

void CGameFrame::On_WM_PAINT(WPARAM, LPARAM) {
	::BeginBatchDraw();   //��ʼ������ͼ
	//2. ÿ����ͼ֮ǰ��Ӧ�����
	::cleardevice();
	//������Ϸ���ػ�
	Paint();
	::EndBatchDraw();  //����������ͼ
}

//void CGameFrame::RunGame() {
//	PaintGame();  //����ʾһ��
//	ExMessage msg;
//	while (1) {
//		getmessage(&msg);  //Ĭ�ϻ�ȡȫ������Ϣ
//		if (msg.message == WM_LBUTTONDOWN )   //���������£�WM : Windows  Message
//		{
//			On_WM_LBUTTONDOWN(msg.x, msg.y);  //������Ϸ�Ĵ�����
//
//			
//		}
//
//		if (msg.message == WM_KEYDOWN) {
//			On_WM_KEYDOWN(msg.vkcode);
//		}
//
//		if (msg.message == WM_CLOSE) {
//			CloseGame();
//			break;
//			
//		}
//	}
//}

CGameFrame* pGame = nullptr;
CGameFrame* CreateObject();
extern int	wnd_width;
extern int	wnd_height;
extern int	wnd_x;
extern int	wnd_y;
extern TCHAR* pTitle;

//hwnd: ���ھ��
// msg: ��ϢID ==  msg.message
// WPARAM��LPARAM  : ��ϢЯ������Ϣ
LRESULT  CGameFrame::RunGame(HWND hwnd,UINT msg,WPARAM w,LPARAM l) {


	//pGame->PaintGame();

	//-------------------------------------------------
	if (pGame->m_msgMap.count(msg))   //�ж�map��ı��һ��ϢID����ֵ�� �Ƿ����
	{
		switch (pGame->m_msgMap[msg]->MsgType)
		{
		case EX_MOUSE: {
		
			//(����->*����ָ��)();
			(pGame->*pGame->m_msgMap[msg]->p_fun_EX_MOUSE)(GET_X_LPARAM(l), GET_Y_LPARAM(l));
		}
			break;
		case EX_KEY: {
			(pGame->*pGame->m_msgMap[msg]->p_fun_EX_KEY)(w);
		}
		break;
		case EX_CHAR: {
			//WM_CHAR;->WPARAM w
			//void On_WM_CHAR(WPARAM);
			(pGame->*pGame->m_msgMap[msg]->p_fun_EX_CHAR)(w);
		}
		break;
		case EX_WINDOW: {
			(pGame->*pGame->m_msgMap[msg]->p_fun_EX_WINDOW)(w,l);
		}
		break;
		}

		//;
		//pGame->PaintGame();
		//���������ڵ�����Ϊ��Ч��ϵͳ���ж���Ϊ��ʱ�ˣ�����������
		//WM_PAINT �����߳���Ӧ����ʹˢ�£���֤��������
		RECT rect{ wnd_width, wnd_height };
		::InvalidateRect(hwnd,&rect,false);  //���ô��ڵ���Ч��

	}
	



	return ::DefWindowProc(hwnd, msg, w,l);   //Ĭ�ϵĴ��ڻص���һ�㴦��̫���ĵ���Ϣ
}


void CGameFrame::On_WM_CLOSE(WPARAM, LPARAM) {
	//������Ϸ�Ĺر�
	Close();
	::closegraph();  //�رմ���

	m_isQuit = true;  //������������ѭ�����˳���
}



int main() {
	//ָ���������
	pGame = CreateObject();

	pGame->InitGame(wnd_width, wnd_height, wnd_x, wnd_y, pTitle);
	pGame->On_WM_PAINT(0,0);

	while (!pGame->m_isQuit) {
	
		Sleep(1000);
	}

	delete pGame;
	pGame = nullptr;
	return 0;
}