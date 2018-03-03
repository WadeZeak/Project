
// IPATTRCDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IPATTRC.h"
#include "IPATTRCDlg.h"
#include "afxdialogex.h"
#include <vector>

#include "Utils.h"

#include <stdio.h>    
#include <string.h>    
#include <WINSOCK2.H>    

#pragma comment(lib,"ws2_32.lib")  

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  _DEBUG 1
#ifdef _DEBUG
#include <FCNTL.H>
#include <io.h>
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIPATTRCDlg 对话框




CIPATTRCDlg::CIPATTRCDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPATTRCDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPATTRCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listctrl);
}

BEGIN_MESSAGE_MAP(CIPATTRCDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CIPATTRCDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CIPATTRCDlg 消息处理程序

BOOL CIPATTRCDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}



	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	LONG lStyle;
	lStyle = GetWindowLong(m_listctrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_listctrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_listctrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_listctrl.SetExtendedStyle(dwStyle); //设置扩展风格
	m_listctrl.InsertColumn( 0, _T("序号"), LVCFMT_LEFT, 80 );//插入列
	m_listctrl.InsertColumn( 1, _T("ID"), LVCFMT_LEFT, 80 );//插入列
	m_listctrl.InsertColumn( 2, _T("协议"), LVCFMT_LEFT, 80 );
	m_listctrl.InsertColumn( 3, _T("包长度"), LVCFMT_LEFT, 80 );
	m_listctrl.InsertColumn( 4, _T("源地址"), LVCFMT_LEFT, 200 );
	m_listctrl.InsertColumn( 5, _T("目的地址"), LVCFMT_LEFT, 200 );
	m_listctrl.InsertColumn( 6, _T("内容"), LVCFMT_LEFT, 500 );

#ifdef _DEBUG //debug
	AllocConsole();
	intptr_t handle= (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle(handle,_O_TEXT);
	FILE * hf = _fdopen( hCrt, "w" );
	*stdout = *hf;

	COORD size = {0, 0};
	char title[1024] ={0};
	sprintf_s(title, 1024, "DebugCosole[%d]", 0);
	SetConsoleTitleA(title);
	SetConsoleTextAttribute((HANDLE)handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	SetConsoleScreenBufferSize((HANDLE)handle, size);

	SMALL_RECT rc = {0, 0, 100, 30};
	SetConsoleWindowInfo((HANDLE)handle, true, &rc);
#endif
	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIPATTRCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIPATTRCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIPATTRCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CIPATTRCDlg::DecodeIP(char *buf, int len)  
{  
	int n = len;  
	if (n >= sizeof(IP_HEAD))  
	{  
		IP_HEAD iphead;  
		iphead = *(IP_HEAD*)buf;  

		cout << "第 "<<cnt++<<" 个IP数据包信息：" << endl;  


		cout << "协议版本:" <<(iphead.ver_hlen >> 4) << endl;  
		cout << "首部长度:" << ((iphead.ver_hlen & 0x0F) << 2) << endl;//单位为4字节  
		cout << "服务类型:Priority: " << (iphead.byTOS >> 5) << ",Service: " << ((iphead.byTOS >> 1) & 0x0f) << endl;  
		cout << "IP包总长度:" << ntohs(iphead.wPacketLen) << endl; //网络字节序转为主机字节序  
		cout << "标识:" << ntohs(iphead.wSequence) << endl;  
		cout << "标志位:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;  
		cout << "片偏移:" << (iphead.FragOf & 0x1fff) << endl;  
		cout << "生存周期:" << (int)iphead.byTTL << endl;  
		cout << "协议类型:" << int(iphead.byProtocolType) << endl;  
		cout << "首部校验和:" << ntohs(iphead.wHeadCheckSum) << endl;  
		cout << "源地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;  
		cout << "目的地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;  

		cout << "==============================================================" << endl << endl;  

		char * stripsrc = "192.168.20.233";
		char * stripdes = "192.168.20.233";
		if (!strcmp( inet_ntoa(*(in_addr*)&iphead.dwIPSrc),stripsrc)&&!strcmp( inet_ntoa(*(in_addr*)&iphead.dwIPDes),stripdes))
		{
			CIPpacket * ipstruct = new CIPpacket;
			ipstruct->setIpHead(&iphead);
			int headlen = ((iphead.ver_hlen & 0x0F) << 2);
			int iplen = ntohs(iphead.wPacketLen);
			int datelen = iplen - headlen;
			ipstruct->setIpLen(datelen);
			buf = (char *)buf + (sizeof(char)*headlen);
			ipstruct->setIpDate(buf,datelen);
			

			if (int(iphead.byProtocolType) == 6)
			{
				DecodeTCP(ipstruct,buf,datelen);
				if (ipstruct->pTcpPakcet == NULL)
				{
					return -1;
				}
			}

			ipPacketList.push_back(ipstruct);

			for (int i = 0; i < (int)ipPacketList.size(); i++)
			{
				CIPpacket * pitem = ipPacketList.at(i);
				printf("111");
			}
			SetEvent(g_event2);
		//}else{
		//	return -1;
		}
		

	}  
	return 0;  
}  

int CIPATTRCDlg::DecodeTCP(CIPpacket *p,char *buf, int len)  
{  
	int n = len;  
	if (n >= sizeof(TCP_HEAD))  
	{  
		TCP_HEAD tcphead;  
		tcphead = *(TCP_HEAD*)buf;  
		/*
		WORD wsrcPort;		//源端口
		WORD wdesPort;		//目的端口
		DWORD dwDateNo;		//数据序号
		DWORD dwAnswerNo;	//确认序号
		union  
		{  
		WORD offset; //偏移  
		WORD reservt;//保留 
		WORD FragOf;//切片标志位 
		}; 
		WORD wwindate; //窗口字段 
		WORD wPcAnd; //包校验和
		WORD wpDenger; //紧急指针
		BYTE Options;          //选项
		*/
		cout << "源端口:" << ntohs(tcphead.wsrcPort) << endl; //源端口
		cout << "目的端口:" << ntohs(tcphead.wdesPort) << endl; //目的端口
		cout << "数据序号:" << ntohl(tcphead.dwDateNo) << endl; //数据序号
		cout << "确认序号:" << ntohl(tcphead.dwAnswerNo) << endl; //确认序号
		cout << "偏移:" << ((tcphead.offset & 0x00f0)>>2)<< endl; //偏移

		cout << "窗口字段:" << ntohs(tcphead.wwindate) << endl; //窗口字段

		p->pTcpPakcet = new CTCPpacket;
		memset(p->pTcpPakcet,0,sizeof(CTCPpacket));
		p->pTcpPakcet->settcpHead(&tcphead);
		int headlen = ((tcphead.offset & 0x00f0)>>2);
		int datelen = len - headlen;
		p->pTcpPakcet->settcpLen(datelen);
		buf = (char *)buf + (sizeof(char)*headlen);
		
		p->pTcpPakcet->settcpDate(buf,datelen);

	}  else{
		p->pTcpPakcet =NULL;
	}
	return 0;  
}  

void CIPATTRCDlg::AutoWSACleanup()  
{  
	::WSACleanup();  
}  

DWORD WINAPI CIPATTRCDlg::ThreadPro(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;

	SetEvent(lp->g_event);
	lp->cnt = 1;  
	char buf[65535];  
	int len = 0;  

	fd_set  fds;
	struct  timeval  timeout={3,0}; //select等待3秒，3秒轮询，要非阻塞就置0
	int maxfdp = 0;
	while(1)
	{
		printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		
		FD_ZERO(&fds); //每次循环都要清空集合，否则不能检测描述符变化
		FD_SET(lp->sock,&fds); //添加描述符
		//maxfdp=sock>fp?sock+1:fp+1;   //描述符最大值加1
		switch(select(maxfdp,&fds,&fds,NULL,&timeout))  //select使用 
		{
		case -1: exit(-1);break; //select错误，退出程序
		case 0: break;  //再次轮询
		default:
			if(FD_ISSET(lp->sock,&fds)) //测试sock是否可读，即是否网络上有数据
			{
				//接受网络数据
				len = recv(lp->sock, buf, sizeof(buf), 0);  
				if (len > 0)  
				{  
					lp->fmutex->lockMutex();
					lp->DecodeIP(buf, len);  
					lp->fmutex->unlockMutex();
				}  
			}// end if break;
		}//end switch
		
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	}//endwhile


	return TRUE;
}
/*
DWORD WINAPI CIPATTRCDlg::ThreadPro(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;

	SetEvent(lp->g_event);
	lp->cnt = 1;  
	char buf[65535];  
	int len = 0;  
	do  
	{  
		len = recv(lp->sock, buf, sizeof(buf), 0);  
		if (len > 0)  
		{  
			lp->DecodeIP(buf, len);  
		}  
		SetEvent(lp->g_event2);
	} while (1);  

	return TRUE;
}
*/
DWORD WINAPI CIPATTRCDlg::ThreadPro2(LPVOID lpParameter)
{
	CIPATTRCDlg * lp=(CIPATTRCDlg *)lpParameter;
	//ResetEvent(lp->g_event2);
	do  
	{  
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");

		WaitForSingleObject(lp->g_event2, INFINITE);

		lp->fmutex->lockMutex();
		int row = lp->m_listctrl.GetItemCount();
		for (int i = row; i < (int)lp->ipPacketList.size(); i++)
		{
			CIPpacket * pitem = lp->ipPacketList.at(i);

			int proteal = pitem->ip_head.byProtocolType;
			char prostr[20];
			itoa(proteal,prostr,10);
			WCHAR * lpszUnicode2 = AnsiToUnicode(prostr);

			int id = ntohs(pitem->ip_head.wSequence);
			//1为ICMP, 2为IGMP, 6为TCP, 17为UDP
			WCHAR lpszUnicode[20];
			switch(proteal)
			{
			case 1:
				StrCpy(lpszUnicode , _T("ICMP"));
				break;
			case 2:
				StrCpy(lpszUnicode , _T("IGMP"));
				break;
			case 6:
				StrCpy(lpszUnicode , _T("TCP"));
				break;
			case 17:
				StrCpy(lpszUnicode , _T("UDP"));
				break;
			default:
				char IDstr[20];
				itoa(id,IDstr,10);

				WCHAR * lpszUnicode = AnsiToUnicode(IDstr);
				break;
			}

			

			char IDstr2[20];
			itoa(i,IDstr2,10);

			WCHAR * lpszUnicode3 = AnsiToUnicode(IDstr2);

			int nRow = lp->m_listctrl.InsertItem(i, lpszUnicode3);//插入行
			lp->m_listctrl.SetItemText(nRow, 1, lpszUnicode);//设置数据
			lp->m_listctrl.SetItemText(nRow, 2, lpszUnicode2);//设置数据

			//len
			char IDstr4[20];
			itoa(pitem->iplen,IDstr4,10);
			WCHAR * lpszUnicode4 = AnsiToUnicode(IDstr4);
			lp->m_listctrl.SetItemText(nRow, 3, lpszUnicode4);//设置数据

			//src ip
			WCHAR * lpszUnicode5 = AnsiToUnicode(inet_ntoa(*(in_addr*)&pitem->ip_head.dwIPSrc));
			lp->m_listctrl.SetItemText(nRow, 4, lpszUnicode5);//设置数据
			//des ip
			WCHAR * lpszUnicode6 = AnsiToUnicode(inet_ntoa(*(in_addr*)&pitem->ip_head.dwIPDes));
			lp->m_listctrl.SetItemText(nRow, 5, lpszUnicode5);//设置数据

			//tcp date
			//WCHAR * lpszUnicode7 = AnsiToUnicode(pitem->date);
			if (pitem->pTcpPakcet->tcplen>0)
			{
			
			string str(pitem->pTcpPakcet->date);
			//CString cstr;
			//cstr.Format(_T("%X"),*pitem->pTcpPakcet->date);
			lp->m_listctrl.SetItemText(nRow, 6, Utf8ToUnicode(str.c_str()));//设置数据
			printf("%s",str);
			}

		}
		ResetEvent(lp->g_event2);
		lp->fmutex->unlockMutex();
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	} while (1);  

	return TRUE;
}

int CIPATTRCDlg::init()
{
	fmutex = new myMutex;
	int n;  
	WSADATA wd;  
	n = WSAStartup(MAKEWORD(2, 2), &wd);  
	if (n)  
	{  
		cout << "WSAStartup函数错误！" << endl;  
		return -1;  
	}  
	atexit(AutoWSACleanup);  
	//创建SOCKET  
	sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);  
	if (sock == INVALID_SOCKET)  
	{  
		cout << WSAGetLastError();  
		return 0;  
	}  
	//获取本机地址  
	char  name[128];  
	if (-1 == gethostname(name, sizeof(name)))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  
	struct hostent * pHostent;  
	pHostent = gethostbyname(name);  
	//绑定本地地址到SOCKET句柄  
	sockaddr_in addr;  
	addr.sin_family = AF_INET;  
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP  
	addr.sin_port = 8888; //端口，IP层端口可随意填  
	if (SOCKET_ERROR == bind(sock, (sockaddr *)&addr, sizeof(addr)))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  

	//设置该SOCKET为接收所有流经绑定的IP的网卡的所有数据，包括接收和发送的数据包  
	u_long sioarg = 1;  
	DWORD wt = 0;  
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  
	//我们只需要接收数据，因此设置为阻塞IO，使用最简单的IO模型  
	u_long bioarg = 0;  
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))  
	{  
		closesocket(sock);  
		cout << WSAGetLastError();  
		return 0;  
	}  
	//开始接收数据  
	//因为前面已经设置为阻塞IO，recv在接收到数据前不会返回。  
	g_event = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(g_event==NULL)  
	{     
		printf("hEvent is null\n");  
		return 0;  
	}  
	hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CIPATTRCDlg::ThreadPro,this,0,0); 
	if(hThread==NULL)  
	{  
		//m_taskdoing = false;
		CloseHandle(hThread);  
		return -1;
	}  

	DWORD dwRet=WaitForSingleObject(g_event, INFINITE);

	g_event2 = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(g_event2==NULL)  
	{     
		printf("hEvent is null\n");  
		return 0;  
	}  
	hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)CIPATTRCDlg::ThreadPro2,this,0,0); 
	if(hThread2==NULL)  
	{  
		//m_taskdoing = false;
		CloseHandle(hThread2);  
		return -1;
	}  

	//closesocket(sock); 
	return 0;
}

void CIPATTRCDlg::OnBnClickedOk()
{
	init();

	// TODO: 在此添加控件通知处理程序代码
}
