
// MFCRecorderDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCRecorder.h"
#include "MFCRecorderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
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
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_TIMER()
END_MESSAGE_MAP()


// CMFCRecorderDlg 对话框



CMFCRecorderDlg::CMFCRecorderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCRecorderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCRecorderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCRecorderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUT_SAVE, &CMFCRecorderDlg::OnBnClickedButSave)
	ON_BN_CLICKED(IDC_BUT_RECORD, &CMFCRecorderDlg::OnBnClickedButRecord)
	ON_BN_CLICKED(IDC_BUT_STOP, &CMFCRecorderDlg::OnBnClickedButStop)
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CMFCRecorderDlg 消息处理程序

BOOL CMFCRecorderDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCRecorderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。


void CMFCRecorderDlg::OnPaint()
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
		CPaintDC dc(this);
		m_str.Format(L"%02d:%02d:%02d", m_nHour, m_nHour, m_nSec); 
		

		//创建字体
		CFont font;
		font.CreatePointFont(400, L"微软雅黑");
		dc.SelectObject(font);
		dc.SetTextColor(RGB(255, 0, 0));//设置字体颜色
		dc.SetBkMode(TRANSPARENT);//背景同名
		dc.TextOut(50, 10, m_str);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCRecorderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//关闭 停止 直接停止即可
//保存 路径

//保存音频
void CMFCRecorderDlg::OnBnClickedButSave()
{
	CTime time = CTime::GetCurrentTime();//获取系统当前时间
	CFileDialog dlg(FALSE,//FALSE 另存为   TRUE 打开
		L"wav",
		time.Format(L"%Y%m%d%H%M%S"),
		OFN_PATHMUSTEXIST,
		L"WAV文件(*.wav)|*.wav|所有文件(*.*)|*.*||"	);

	if (IDCANCEL==dlg.DoModal())//取消
		return;


	//保存
	//定义设备
	MCI_SAVE_PARMS saveParms = { 0 };//保存的设备
	CString str = dlg.GetPathName();
	//填充
	saveParms.lpfilename = str;//文件名称

	//
	mciSendCommand(m_IdDevice,MCI_SAVE,MCI_SAVE_FILE|
		MCI_WAIT ,//等待下次的录制
		(DWORD)&saveParms);


	mciSendCommand(m_IdDevice, MCI_CLOSE, NULL, NULL);//关闭设备 解除占用
	m_IdDevice = NULL;

	//保存文件时,将定时器归0
	m_nHour = 0;
	m_nSec = 0;
	m_nMin = 0;
	Invalidate(true);
}





//开始录制
void CMFCRecorderDlg::OnBnClickedButRecord()
{
	/*
	MCIERROR mciSendCommand(
MCIDEVICEID wIDDevice, 　//设备的ID，在打开设备时不用该参数 //NULL 完成后赋值
UINT　uMsg, 　//命令消息 //打开 录制 播放 设置 暂停 继续
DWORD 　fdwCommand, //命令消息的标志 //对录制而言 格式 声道 采样率 数据块的对齐单位
DWORD 　dwParam 　//指向包含命令消息参数的结构 //结构
); //若成功则返回0，否则返回错误码
使用时请添加：
#include <MMSystem.h>
#pragma comment(lib, "WINMM.LIB")*/

	//1.关闭  防止内存中垃圾数据导致错误
	mciSendCommand(m_IdDevice,MCI_CLOSE,NULL,NULL);//重中之重 对某一设备发出新指令
	
	//2.打开
	//a.定义设备  打开
	MCI_OPEN_PARMS openParms;
	//b.填充结构

	openParms.lpstrDeviceType =(LPCWSTR) MCI_DEVTYPE_WAVEFORM_AUDIO;
	openParms.lpstrElementName = L"";
	 //c.发号施令
	mciSendCommand(NULL, MCI_OPEN,
						MCI_OPEN_TYPE|
							MCI_OPEN_ELEMENT|
								MCI_OPEN_TYPE_ID,
									(DWORD)&openParms);

	//赋值初始化
	m_IdDevice = openParms.wDeviceID;//标记锁打开的音频

	//3.设置
	//a.定义设备 设置
	MCI_WAVE_SET_PARMS setParms;//
	//b.填充结构
	setParms.wFormatTag = WAVE_FORMAT_PCM;//波形文件也是PCM 格式
	setParms.nChannels = 2;//1 单声道 2 多声道
	setParms.nSamplesPerSec = 11025;//采样数
	setParms.nAvgBytesPerSec = 11025 * 2;
	setParms.nBlockAlign = 2;//数据块对其
	setParms.wBitsPerSample = 8;//存放是数据块的位
		//c.发号施令
	mciSendCommand(m_IdDevice, 
						MCI_SET, 
							MCI_WAVE_SET_FORMATTAG | //格式
								MCI_WAVE_SET_CHANNELS | //声道
								MCI_WAVE_SET_BITSPERSAMPLE, //每个数据块位的大小
										(DWORD)&setParms);
	
	//4.录音
	//a.设置定义的设备
	MCI_RECORD_PARMS recordParms = {0};
	//b.填充结构体
	//c.发号施令
	mciSendCommand(m_IdDevice, MCI_RECORD, NULL, (DWORD)&recordParms);


	SetTimer(1, 1000, NULL);//打开定时器

}







//停止录制
void CMFCRecorderDlg::OnBnClickedButStop()
{	

	mciSendCommand(m_IdDevice, MCI_STOP, NULL, NULL);
	KillTimer(1);//关闭定时器
}


//void CAboutDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	CDialogEx::OnTimer(nIDEvent);
//}



//定时器

void CMFCRecorderDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent==1)//1S
	{
		if (++m_nSec>=60)
		{
			m_nSec = 0;
			if (++m_nMin>=60)
			{
				m_nMin = 0;
				++m_nHour;
			}

		}
		Invalidate(true);//刷新屏幕
	}



	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMFCRecorderDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);//获取对话框的矩形
	rect.bottom = 20;
	pDC->FillSolidRect(&rect,RGB(0,100,255));//填充颜色
	
	
	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.top = 20;
	pDC->FillSolidRect(&rectClient, RGB(0, 200, 255));//填充颜色

	pDC->SetBkMode(TRANSPARENT);//背景透明
	pDC->SetTextColor(RGB(0, 0, 0));//标题字体颜色

	CFont font;
	font.CreatePointFont(100, L"微软雅黑");
	pDC->SelectObject(&font);
	pDC->TextOut(3, 0, L"时光钥匙");//标题

	return TRUE;
}




LRESULT CMFCRecorderDlg::OnNcHitTest(CPoint point)
{
	
	UINT nHitTest = CDialogEx::OnNcHitTest(point);
	if (nHitTest == HTCLIENT) //HTCLIENT 客户区
	{
		nHitTest = HTCAPTION;//客户端
	}

	return nHitTest;
}
