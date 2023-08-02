#include<Windowsx.h>
#include<easyx.h>
#include<map>
using namespace std;

#define   ADD_MSG(MSGID,MSGTYPE,CLASS)\
	m_msgMap[MSGID] = new MsgTypeFun{ MSGTYPE };\
	m_msgMap[MSGID]->p_fun_##MSGTYPE = (PFUN_##MSGTYPE)&CLASS::On_##MSGID;



class CGameFrame {
public:
	HWND m_hWnd;  //窗口句柄 ，标识窗口
	bool m_isQuit;   //标识是否退出， true: 退出，false : 不退出

	
	//#define EX_MOUSE	    1
	//#define EX_KEY		2
	//#define EX_CHAR		4
	//#define EX_WINDOW	    8

	typedef void(CGameFrame::* PFUN_EX_MOUSE)(int, int);   //鼠标类型
	typedef void(CGameFrame::* PFUN_EX_KEY)(BYTE);   //键盘类型
	typedef void(CGameFrame::* PFUN_EX_CHAR)(WPARAM);
	typedef void (CGameFrame::* PFUN_EX_WINDOW)(WPARAM, LPARAM);

	struct MsgTypeFun {
		int MsgType;
		union {
			PFUN_EX_MOUSE  p_fun_EX_MOUSE;
			PFUN_EX_KEY    p_fun_EX_KEY;
			PFUN_EX_CHAR   p_fun_EX_CHAR;
			PFUN_EX_WINDOW p_fun_EX_WINDOW;
		};
	};

	map<UINT, MsgTypeFun*>  m_msgMap;  //消息映射表

	virtual void AddMsg();

	CGameFrame() :m_hWnd(NULL), m_isQuit(false){}
	virtual ~CGameFrame() {
		for (pair<UINT, MsgTypeFun*> pr : m_msgMap) {
			if (pr.second) delete pr.second;   //回收new出的空间
		}
	}

	//1.  初始化游戏的函数  InitGame
	void InitGame(int width, int height, int x, int y, LPCWSTR title);
	//2. 显示 重绘     PaintGame
	void On_WM_PAINT(WPARAM, LPARAM);
	//3. 游戏运行     RunGame
	//void RunGame();
	static LRESULT  RunGame(HWND hwnd, UINT msg, WPARAM w, LPARAM l);
	//4. 销毁        CloseGame
	void On_WM_CLOSE(WPARAM, LPARAM);
	//----具体游戏的函数------------------------------------------------
	virtual void Init() =0;
	virtual void Paint() = 0;
	virtual void Close() = 0;


	
};


#define CREATE_OBJECT(OBJ_CLASS)\
	CGameFrame* CreateObject() {\
		return new OBJ_CLASS;\
	}

#define WND_PARAM(WIDTH,HEIGHT,X,Y,TITLE)\
	int	wnd_width = WIDTH;\
	int	wnd_height= HEIGHT;\
	int	wnd_x = X;\
	int	wnd_y=Y;\
	TCHAR* pTitle=(TCHAR*)TITLE;
#define EX_MOUSE 1
#define EX_KEY 2
#define EX_CHAR 4
#define EX_WINDOW 8