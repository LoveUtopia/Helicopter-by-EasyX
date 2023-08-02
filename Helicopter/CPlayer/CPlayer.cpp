#include "CPlayer.h"
CPlayer::CPlayer():m_x(0),m_y(0),m_showid(0),isLive(true){}
CPlayer::~CPlayer(){}
void CPlayer::InitPlayer(){
	m_x = PLAYER_INIT_X;
	m_y = PLAYER_INIT_Y;
	::loadimage(&m_imgPlayer, L"./res/player.png");
}
void CPlayer::ShowPlayer(){
   
	::putimage(m_x, m_y, PLAYER_WIDTH, PLAYER_HEIGHT, &m_imgPlayer, m_showid * PLAYER_WIDTH, 0,SRCPAINT);
}
void CPlayer::MovePlayer(unsigned key){
    if (key == VK_UP) {
        m_y -= PLAYER_UP_MOVE_STEP;
    }
    else if (key == NULL) {
        if (m_y <= 0 || (m_y += PLAYER_DOWN_MOVE_STEP) >=BACK_HEIGHT-PLAYER_HEIGHT+5) {
            isLive = false; 
        }
    }
}