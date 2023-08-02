
#include"GameFrame.h"

void CGameFrame::InitGame(int width, int height, int x, int y, LPCWSTR title) {
	//创建窗口
	m_hWnd = ::initgraph(width, height);

	//设定窗口的背景色为白色
	::setbkcolor(RGB(255, 255, 255));
	::cleardevice();   //1. 及时更新背景色

	//移动窗口
	::MoveWindow(m_hWnd, x, y, width, height, TRUE);
	//设置窗口标题
	::SetWindowText(m_hWnd, title);

	//添加消息
	AddMsg();

	//设置窗口的属性  , 
	::SetWindowLong(m_hWnd, GWL_WNDPROC/*  此宏为32位下的宏  */,(LONG)&CGameFrame::RunGame); //设置窗口的回调函数

	//具体游戏的初始化
	Init();

}

void CGameFrame::AddMsg() {
	/*m_msgMap[WM_LBUTTONDOWN] = new MsgTypeFun{ EX_MOUSE };
	m_msgMap[WM_LBUTTONDOWN]->p_fun_EX_MOUSE = &CGameFrame::On_WM_LBUTTONDOWN;*/
	
	ADD_MSG(WM_CLOSE, EX_WINDOW,CGameFrame)
	ADD_MSG(WM_PAINT, EX_WINDOW,CGameFrame)
}

void CGameFrame::On_WM_PAINT(WPARAM, LPARAM) {
	::BeginBatchDraw();   //开始批量绘图
	//2. 每次贴图之前，应当清空
	::cleardevice();
	//具体游戏的重绘
	Paint();
	::EndBatchDraw();  //结束批量绘图
}

//void CGameFrame::RunGame() {
//	PaintGame();  //先显示一下
//	ExMessage msg;
//	while (1) {
//		getmessage(&msg);  //默认获取全量的消息
//		if (msg.message == WM_LBUTTONDOWN )   //鼠标左键按下，WM : Windows  Message
//		{
//			On_WM_LBUTTONDOWN(msg.x, msg.y);  //具体游戏的处理函数
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

//hwnd: 窗口句柄
// msg: 消息ID ==  msg.message
// WPARAM，LPARAM  : 消息携带的信息
LRESULT  CGameFrame::RunGame(HWND hwnd,UINT msg,WPARAM w,LPARAM l) {


	//pGame->PaintGame();

	//-------------------------------------------------
	if (pGame->m_msgMap.count(msg))   //判断map中谋个一消息ID（键值） 是否存在
	{
		switch (pGame->m_msgMap[msg]->MsgType)
		{
		case EX_MOUSE: {
		
			//(对象->*函数指针)();
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
		//将整个窗口的设置为无效，系统会判断其为过时了，会主动发送
		//WM_PAINT 来告诉程序，应当即使刷新，保证窗口最新
		RECT rect{ wnd_width, wnd_height };
		::InvalidateRect(hwnd,&rect,false);  //设置窗口的无效区

	}
	



	return ::DefWindowProc(hwnd, msg, w,l);   //默认的窗口回调，一般处理不太关心的消息
}


void CGameFrame::On_WM_CLOSE(WPARAM, LPARAM) {
	//具体游戏的关闭
	Close();
	::closegraph();  //关闭窗口

	m_isQuit = true;  //告诉主函数的循环该退出了
}



int main() {
	//指向子类对象
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