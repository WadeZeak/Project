#include "stdafx.h"
#include "SendMessage.h"


QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}

//��ں���
void QQMessage::Start(const wchar_t *msg)
{
	m_msg = CString(msg);
	_beginthreadex(NULL,0,QQMessage::RunThreadProc,NULL,0,NULL);//�����߳� ÿ���߳�ӵ�е������ڴ�ռ�,�洢���� ÿ���߳̾�ֻ����ʺ��޸��Լ������ݶ�����ȥ�۸������̵߳�����
}


unsigned int QQMessage::RunThreadProc(void *param)//��ʼ�߳�
{
	//��ʼ���͵�������
	QQMessage::Instance()->SendAll();
	return 0;
}

//���͵ĺ���
void QQMessage::SendAll()
{
	//���Ƶ�������
	AddTextToClipboard();
	int errortime = 0;//�������

	//�ҵ�QQ������
	while (errortime<=4)
	{
		HWND qqhWnd = FindQQWindow();
		HWND fronthWnd = GetForegroundWindow();//�õ�������ǰ���Ĵ���
		if (qqhWnd != fronthWnd)
		{
			if (!SetForegroundWindow(qqhWnd))//ǿ���Եİ�qq���ڷŵ���ǰ,���ʧ�ܣ�����QQ����û��
			{
				MessageBox(NULL, L"û���ҵ�QQ����", NULL, NULL);
				break;
			}
		}

		
		//�򿪴��� 
	
		//ģ������Tab ÿ�η���ֻ��Ҫ��һ��
		if (errortime==0)
		{
			PressKey(VK_TAB);
			PressKey(VK_TAB);	
		}
		
		//��
		PressKey(VK_DOWN);
		//�س�
		PressKey(VK_RETURN);
		//ճ����QQ�Ի���
		////ctr+v
		//PressKey(VK_CONTROL);
		//PressKey(0x56);
		////����
		//PressKey(VK_RETURN);
		////�ر�
		//PressKey(VK_ESCAPE);

		//���촰��
		HWND curFrontWindow = GetForegroundWindow();//��ȡ��ǰ��ǰ������,����Ӧ��Ϊ���촰��
		if (curFrontWindow==qqhWnd)//û���ҵ����촰��
		{
			errortime++;
			continue;
		}
		errortime = 0;

		SendMsg();
	}
	

}

//�ҵ�QQ���� ���
HWND QQMessage::FindQQWindow()
{
	HWND hWnd;
	hWnd = FindWindow(L"TXGuiFoundation",L"QQ");//�����ҵ�windowsϵͳ�����д��ھ��
	return hWnd;
}

//ģ�ⰴ�� �ô���ʵ��
void QQMessage::PressKey(BYTE vkey)//vkey ���̵������ֵ
{
	/***********************************************
	WINAPI
keybd_event(
    _In_ BYTE bVk,//��ֵ
    _In_ BYTE bScan,
    _In_ DWORD dwFlags,//���λ ���� 0���ߵ��� KEYEVENT_KEYUP
    _In_ ULONG_PTR dwExtraInfo);
	******************************************************/
	keybd_event(vkey, 0, 0, 0);//����
	Sleep(100);//��ӳ��ʱ��100ms
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);//����
	Sleep(100);
}


void QQMessage::SendMsg()//������Ϣ
{
	//ctr+v
	//����
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(100);
	keybd_event(0X56, 0, 0, 0);
	Sleep(100);

	//����
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	//enter   ����ctr+enter
	//ctr+enter
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_RETURN, 0, 0, 0);
	Sleep(100);

	//����
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	PressKey(VK_ESCAPE);
	Sleep(100);

}

//���ƺ��� ��ѡ�������ݱ��浽���а�
void QQMessage::AddTextToClipboard()
{

	//����ȫ���ڴ�,�洢����
	int memlen = m_msg.GetLength()*sizeof(wchar_t)+2;
	HANDLE hGlobalMen=GlobalAlloc(GHND, memlen);//����ȫ���ڴ�

	void *memAddr = GlobalLock(hGlobalMen);//����
	ZeroMemory(memAddr, memlen);//�ڴ�����

	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memlen);//��ָ��λ�ÿ�������
	GlobalUnlock(hGlobalMen);//����


	OpenClipboard(NULL);//��ճ����
	EmptyClipboard();//���ԭ�еļ�����

	SetClipboardData(CF_UNICODETEXT,hGlobalMen );//��������
	CloseClipboard();//�ر�
}