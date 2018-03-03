#include "stdafx.h"
#include "Play.h"


CPlay::CPlay()//��ʼ��
{
	m_pVlcInstance = NULL;
	m_pVlcPlayer = NULL;
}


CPlay::~CPlay()
{




}




BOOL CPlay::InitInstance()//��ʼ��ʵ��
{
	if (!m_pVlcInstance)//û��ʵ��
	{
		m_pVlcInstance = libvlc_new(0, NULL);
		if (!m_pVlcInstance)//��ʼ��ʵ��ʧ��
		{
			return FALSE;
		}
	}
	return TRUE;
}




BOOL CPlay::Play(char *szFilePath, HWND hWnd)//����  �ļ���·�� ���ھ��
{
	if (strlen(szFilePath)==0)
	{
		return FALSE;
	}
	 
	InitInstance();
	libvlc_media_t *m_pVlcMedia = libvlc_media_new_path(m_pVlcInstance,szFilePath);//����Ƶ��·����ʵ����
	m_pVlcPlayer = libvlc_media_player_new_from_media(m_pVlcMedia);//���ŵĶ���

	//����
	//����ָ������
	libvlc_media_player_set_hwnd(m_pVlcPlayer,hWnd);
	//����
	libvlc_media_player_play(m_pVlcPlayer);


	return TRUE;

}
BOOL CPlay::Pause()//��ͣ
{
	if (!m_pVlcInstance)
	{
		return FALSE;
	}
	if (libvlc_media_player_can_pause(m_pVlcPlayer))//��Ƶ�Ƿ������ͣ
	{
		libvlc_media_player_pause(m_pVlcPlayer);
	}

	return TRUE;
}