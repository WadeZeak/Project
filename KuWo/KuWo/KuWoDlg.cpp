
// KuWoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "KuWo.h"
#include "KuWoDlg.h"
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


// CKuWoDlg 对话框



CKuWoDlg::CKuWoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKuWoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKuWoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKuWoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CKuWoDlg 消息处理程序

BOOL CKuWoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();



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


	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CKuWoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKuWoDlg::OnPaint()
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
HCURSOR CKuWoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//对图片进行初始化
void CKuWoDlg::InitUI()
{
	m_kugouUI.width = 204;
	m_kugouUI.height = 209;
	
	m_kugouUI.main = MakeUiItem(48, 48, 106, 106, 51, 99, true);//显示中间部分
	m_kugouUI.left = MakeUiItem(0, 54,98, 100, 110, 0,0);//左边
	m_kugouUI.right = MakeUiItem(106, 54, 98, 100,110, 0,0);//右边
	m_kugouUI.top = MakeUiItem(53, 0, 98, 100, 110, 0,0);//顶部
	m_kugouUI.bottom = MakeUiItem(53,109,98,100,110,0,0);//底部

	m_kugouUI.item[0] = MakeUiItem(30,90,24,24,113,179,0);
	m_kugouUI.item[1] = MakeUiItem(91,24,24,24,113,154,0);
	m_kugouUI.item[2] = MakeUiItem(158,90,24,24,138,179,0);
	m_kugouUI.item[3] = MakeUiItem(91,157,24,24,138,154,0);


	LoadRecImage(IDB_PNG1, m_pSrcImage);//载入资源中的PNG图片
	ModifyStyleEx(0, WS_EX_LAYERED);



}






// 用来对每个小方片进行处理
UIITEM CKuWoDlg::MakeUiItem(int x, int y, int height, int width, 
	int SrcX, int SrcY, bool Show)
{
	UIITEM item;
	item.x = x;
	item.y = y;
	item.width = width;
	item.height = height;
	item.SrcX = SrcX;
	item.SrcY = SrcY;
	item.Show = Show;
	return item;
}


// 用来从个资源文件中获取图片
int CKuWoDlg::LoadRecImage(int nRecID, Image* img)
{
	//获取资源ID
	HINSTANCE hIns=AfxGetInstanceHandle();//获取当前实例句柄

	
	HRSRC hRsrc=::FindResource(hIns,MAKEINTRESOURCE(nRecID),_T("png"));//查找资源，并返回句柄

	if (!hRsrc)
		return 0;

	DWORD len=SizeofResource(hIns,hRsrc);//获取资源大小,在虚拟内存中存放资源
	BYTE *LpRsrc=(BYTE *)LoadResource(hIns, hRsrc);//加载资源进内村

	 HGLOBAL m_hMem=GlobalAlloc(GMEM_FIXED,len);//兼容16位，申请虚拟内存  返回句柄
	 BYTE *pmem = (BYTE *)GlobalLock(m_hMem);//内存加锁  

	 memcpy(pmem, LpRsrc, len);//将内容放入内存空间

	 IStream *pstm;
	 CreateStreamOnHGlobal(m_hMem,false,&pstm);//创建在全局的流
	img= Gdiplus::Image::FromStream(pstm);
	GlobalUnlock(m_hMem); //解锁内存
	pstm->Release();//释放
	FreeResource(LpRsrc);//释放资源
	return 0;
}
