//ʵ�ֲ��Ź��ܵ���

#pragma once
#include "./vlc/vlc.h"  //����ͷ�ļ�
#pragma	comment(lib,"libvlc.lib")//�������ļ�
#pragma	comment(lib,"libvlccore.lib")
class CPlay
{
private:
	libvlc_instance_t *m_pVlcInstance;//ʵ�� ���� ���� ��ͣ ����
	libvlc_media_player_t *m_pVlcPlayer;//���� 

public:
	//��ʼ��ʵ��
	BOOL InitInstance();
	BOOL Play(char *szFilePath,HWND hWnd);//����  �ļ���·�� ����
	BOOL Pause();//��ͣ
	CPlay();
	~CPlay();
};











