//实现播放功能的类

#pragma once
#include "./vlc/vlc.h"  //包含头文件
#pragma	comment(lib,"libvlc.lib")//包含库文件
#pragma	comment(lib,"libvlccore.lib")
class CPlay
{
private:
	libvlc_instance_t *m_pVlcInstance;//实例 加载 播放 暂停 音量
	libvlc_media_player_t *m_pVlcPlayer;//对象 

public:
	//初始化实例
	BOOL InitInstance();
	BOOL Play(char *szFilePath,HWND hWnd);//播放  文件的路径 窗口
	BOOL Pause();//暂停
	CPlay();
	~CPlay();
};











