#include "stdafx.h"
#include "Play.h"


CPlay::CPlay()//初始化
{
	m_pVlcInstance = NULL;
	m_pVlcPlayer = NULL;
}


CPlay::~CPlay()
{




}




BOOL CPlay::InitInstance()//初始化实例
{
	if (!m_pVlcInstance)//没有实例
	{
		m_pVlcInstance = libvlc_new(0, NULL);
		if (!m_pVlcInstance)//初始化实例失败
		{
			return FALSE;
		}
	}
	return TRUE;
}




BOOL CPlay::Play(char *szFilePath, HWND hWnd)//播放  文件的路径 窗口句柄
{
	if (strlen(szFilePath)==0)
	{
		return FALSE;
	}
	 
	InitInstance();
	libvlc_media_t *m_pVlcMedia = libvlc_media_new_path(m_pVlcInstance,szFilePath);//将视频的路径与实例绑定
	m_pVlcPlayer = libvlc_media_player_new_from_media(m_pVlcMedia);//播放的对象

	//播放
	//设置指定窗口
	libvlc_media_player_set_hwnd(m_pVlcPlayer,hWnd);
	//播放
	libvlc_media_player_play(m_pVlcPlayer);


	return TRUE;

}
BOOL CPlay::Pause()//暂停
{
	if (!m_pVlcInstance)
	{
		return FALSE;
	}
	if (libvlc_media_player_can_pause(m_pVlcPlayer))//视频是否可以暂停
	{
		libvlc_media_player_pause(m_pVlcPlayer);
	}

	return TRUE;
}