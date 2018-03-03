
// VerificationCodeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "VerificationCode.h"
#include "VerificationCodeDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVerificationCodeDlg 对话框


//构造函数
CVerificationCodeDlg::CVerificationCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VERIFICATIONCODE_DIALOG, pParent)
	, m_iLong(4)
	, m_iCount(1)
	, m_bCkCase(FALSE)
	, m_bCkNum(FALSE)
	, m_bOnlyNum(FALSE)
	, m_sSta(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVerificationCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STA, m_cSta);
	DDX_Text(pDX, IDC_EDIT_PASSWDLEN, m_iLong);
	DDV_MinMaxInt(pDX, m_iLong, 1, 100);
	DDX_Text(pDX, IDC_EDIT_PASSWDCOUNT, m_iCount);
	DDV_MinMaxInt(pDX, m_iCount, 1, 100);
	DDX_Check(pDX, IDC_CHECK_CASE, m_bCkCase);
	DDX_Check(pDX, IDC_CHECK_CHECKNUM, m_bCkNum);
	DDX_Check(pDX, IDC_CHECK_NUMONLY, m_bOnlyNum);
	DDX_Text(pDX, IDC_EDIT_STA, m_sSta);
}

BEGIN_MESSAGE_MAP(CVerificationCodeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CLS, &CVerificationCodeDlg::OnBnClickedButtonCls)
	ON_BN_CLICKED(IDC_BUTTON_DO, &CVerificationCodeDlg::OnBnClickedButtonDo)
//	ON_WM_MBUTTONDBLCLK()
ON_WM_LBUTTONDBLCLK()
ON_BN_CLICKED(IDC_CHECK_NUMONLY, &CVerificationCodeDlg::OnBnClickedCheckNumonly)
END_MESSAGE_MAP()


// CVerificationCodeDlg 消息处理程序

BOOL CVerificationCodeDlg::OnInitDialog()
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

	// TODO: 在此添加额外的初始化代码
	
	m_sSta = _T("等待生成验证码");
	m_cSta.SetWindowTextW(m_sSta);
	srand((unsigned)time(NULL));//随机数种子

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVerificationCodeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVerificationCodeDlg::OnPaint()
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
HCURSOR CVerificationCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//清除按钮

void CVerificationCodeDlg::OnBnClickedButtonCls()
{
	UpdateData(FALSE);
	m_sSta.Empty();

	m_sSta = _T("等待验证码的生成....\r\n\n");
	m_cSta.SetWindowTextW(m_sSta);//显示 宽字节

}


//生成验证码
void CVerificationCodeDlg::OnBnClickedButtonDo()
{
	m_cSta.SetWindowTextW(_T(""));
	UpdateData(TRUE);//获取数据
	if (m_iCount>100)
		m_iCount = 100;
	if (m_iLong>100)
		m_iLong = 00;
	CString cstr;
	UpdateData(TRUE);//更新数据

	//生成验证码
	for (int i = 0; i < m_iCount; i++)//m_iCount 个 m_iLong 长度的验证码
	{
		cstr = Generate(m_iLong, m_bCkCase, m_bCkNum, m_bOnlyNum);
		m_sSta += cstr;
		m_sSta += "\r\n";//换行
	}

	
	m_cSta.SetRedraw(FALSE);//防止闪屏
	m_cSta.SetWindowTextW(m_sSta);
	m_cSta.LineScroll(m_cSta.GetLineCount());
	m_cSta.SetRedraw(TRUE);


}

 
CString CVerificationCodeDlg::Generate(int iLong, bool bUpLow, bool bNum, bool bNumOnly)
{

	int iFlag = 26;//默认只有小写字母
	CString cstr;
	if ( bUpLow)
		iFlag = 52;//区分大小写
	if (bNum)
		iFlag = 62;//勾选包含数字
	if (bNumOnly)
		iFlag = 10;//只包含数字

	for (int i = 0; i < iLong; i++)
	{
		cstr += getChar(iFlag);
	}


	if (bNum&&(!bUpLow))//勾选包含数字，但是不勾选区分大小写
		cstr.MakeLower();//大写转换为小写


	return  cstr;
}


CString CVerificationCodeDlg::getChar(int iflag)
{
	
	CString m_sArray=L"abcdefghigklmnopqrstuvwxyzABCDEFGHIGKLMNOPQRSTUWXYZ0123456789";
	CString m_sArray1 = L"1234567890";
	CString s;

	switch (iflag)
	{
	case 10:
	{
		int k = rand() % 10;
		s = m_sArray1.Mid(k, 1);
		break;
	}		
	case 26:
	{
		int k = rand() % 26;
		s = m_sArray.Mid(k, 1);
		break;
	}	
	case  52:
	{
		int  k = rand() % 52;
		s = m_sArray.Mid(k, 1);
		break;
	}
	
	case  62:
	{
		int  k = rand() % 62;
		s = m_sArray.Mid(k, 1);
		break;

	}
	default:
	{
		int	k = rand() % 26;
		s = m_sArray.Mid(k, 1);
		break;
	}	
	}

	return s;
}



void CVerificationCodeDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CAboutDlg dlg;
	dlg.DoModal();

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


//只生成数字
void CVerificationCodeDlg::OnBnClickedCheckNumonly()
{
	UpdateData(TRUE);
	if (m_bOnlyNum)
	{
		GetDlgItem(IDC_CHECK_CASE)->EnableWindow(FALSE);//区分大小写不可用
		GetDlgItem(IDC_CHECK_CHECKNUM)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_CASE)->EnableWindow(TRUE);//区分大小写不可用
		GetDlgItem(IDC_CHECK_CHECKNUM)->EnableWindow(TRUE);

	}

}
