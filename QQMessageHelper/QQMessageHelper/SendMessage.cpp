#include "stdafx.h"
#include "SendMessage.h"


QQMessage::QQMessage()
{
}


QQMessage::~QQMessage()
{
}

//入口函数
void QQMessage::Start(const wchar_t *msg)
{
	m_msg = CString(msg);
	_beginthreadex(NULL,0,QQMessage::RunThreadProc,NULL,0,NULL);//创建线程 每个线程拥有单独的内存空间,存储数据 每个线程就只会访问和修改自己的数据而不会去篡改其它线程的数据
}


unsigned int QQMessage::RunThreadProc(void *param)//开始线程
{
	//开始发送的主函数
	QQMessage::Instance()->SendAll();
	return 0;
}

//发送的函数
void QQMessage::SendAll()
{
	//复制到剪贴板
	AddTextToClipboard();
	int errortime = 0;//错误次数

	//找到QQ主窗口
	while (errortime<=4)
	{
		HWND qqhWnd = FindQQWindow();
		HWND fronthWnd = GetForegroundWindow();//得到桌面最前方的窗口
		if (qqhWnd != fronthWnd)
		{
			if (!SetForegroundWindow(qqhWnd))//强制性的吧qq窗口放到最前,如果失败，表明QQ窗口没打开
			{
				MessageBox(NULL, L"没有找到QQ窗口", NULL, NULL);
				break;
			}
		}

		
		//打开窗口 
	
		//模拟两次Tab 每次发送只需要按一下
		if (errortime==0)
		{
			PressKey(VK_TAB);
			PressKey(VK_TAB);	
		}
		
		//下
		PressKey(VK_DOWN);
		//回车
		PressKey(VK_RETURN);
		//粘贴到QQ对话框
		////ctr+v
		//PressKey(VK_CONTROL);
		//PressKey(0x56);
		////发送
		//PressKey(VK_RETURN);
		////关闭
		//PressKey(VK_ESCAPE);

		//聊天窗口
		HWND curFrontWindow = GetForegroundWindow();//获取当前最前方窗口,正常应该为聊天窗口
		if (curFrontWindow==qqhWnd)//没有找到聊天窗口
		{
			errortime++;
			continue;
		}
		errortime = 0;

		SendMsg();
	}
	

}

//找到QQ窗口 句柄
HWND QQMessage::FindQQWindow()
{
	HWND hWnd;
	hWnd = FindWindow(L"TXGuiFoundation",L"QQ");//可以找到windows系统中所有窗口句柄
	return hWnd;
}

//模拟按键 用代码实现
void QQMessage::PressKey(BYTE vkey)//vkey 键盘的虚拟键值
{
	/***********************************************
	WINAPI
keybd_event(
    _In_ BYTE bVk,//键值
    _In_ BYTE bScan,
    _In_ DWORD dwFlags,//标记位 按下 0或者弹起 KEYEVENT_KEYUP
    _In_ ULONG_PTR dwExtraInfo);
	******************************************************/
	keybd_event(vkey, 0, 0, 0);//按下
	Sleep(100);//反映的时间100ms
	keybd_event(vkey, 0, KEYEVENTF_KEYUP, 0);//弹起
	Sleep(100);
}


void QQMessage::SendMsg()//发送消息
{
	//ctr+v
	//按下
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(100);
	keybd_event(0X56, 0, 0, 0);
	Sleep(100);

	//弹起
	keybd_event(0x56, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	//enter   或者ctr+enter
	//ctr+enter
	keybd_event(VK_CONTROL, 0, 0, 0);
	Sleep(100);
	keybd_event(VK_RETURN, 0, 0, 0);
	Sleep(100);

	//弹起
	keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);
	keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
	Sleep(100);

	PressKey(VK_ESCAPE);
	Sleep(100);

}

//复制函数 将选定的内容保存到剪切板
void QQMessage::AddTextToClipboard()
{

	//分配全局内存,存储数据
	int memlen = m_msg.GetLength()*sizeof(wchar_t)+2;
	HANDLE hGlobalMen=GlobalAlloc(GHND, memlen);//分配全局内存

	void *memAddr = GlobalLock(hGlobalMen);//上锁
	ZeroMemory(memAddr, memlen);//内存清零

	memcpy(memAddr, (const void*)m_msg.GetBuffer(), memlen);//在指定位置拷贝数据
	GlobalUnlock(hGlobalMen);//解锁


	OpenClipboard(NULL);//打开粘贴板
	EmptyClipboard();//清空原有的剪贴板

	SetClipboardData(CF_UNICODETEXT,hGlobalMen );//设置数据
	CloseClipboard();//关闭
}