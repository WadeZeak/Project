
// FileEDSoftwareDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileEDSoftware.h"
#include "FileEDSoftwareDlg.h"
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


// CFileEDSoftwareDlg 对话框



CFileEDSoftwareDlg::CFileEDSoftwareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileEDSoftwareDlg::IDD, pParent)
	, m_Path(_T(""))
	, m_pass(_T(""))
	, m_cpass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileEDSoftwareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EPATH, m_Path);
	DDX_Text(pDX, IDC_EPASS, m_pass);
	DDX_Text(pDX, IDC_ECPASS, m_cpass);
}

BEGIN_MESSAGE_MAP(CFileEDSoftwareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BEXIT, &CFileEDSoftwareDlg::OnBnClickedBexit)
	ON_BN_CLICKED(IDC_BENCRYPTION, &CFileEDSoftwareDlg::OnBnClickedBencryption)
	ON_BN_CLICKED(IDC_BDECRYPTION, &CFileEDSoftwareDlg::OnBnClickedBdecryption)
	ON_BN_CLICKED(IDC_BSELECT, &CFileEDSoftwareDlg::OnBnClickedBselect)
END_MESSAGE_MAP()


// CFileEDSoftwareDlg 消息处理程序

BOOL CFileEDSoftwareDlg::OnInitDialog()
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

void CFileEDSoftwareDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileEDSoftwareDlg::OnPaint()
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
HCURSOR CFileEDSoftwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





//退出
void CFileEDSoftwareDlg::OnBnClickedBexit()
{
	this->EndDialog(true);
}


//加密
void CFileEDSoftwareDlg::OnBnClickedBencryption()
{
	// TODO:  在此添加控件通知处理程序代码


	UpdateData(TRUE);//更新数据   将路径显示到窗口
	if (m_Path == "")//路径为空
	{
		MessageBox("请选择要加密的文件", "错误", MB_ICONINFORMATION);
		return;
	}

	UpdateData(true);//口令不能为空
	if (m_pass==""||m_cpass=="")
	{
		MessageBox("数据文件加密口令不能为空", "错误",MB_ICONINFORMATION);
		return;
	}

	if (m_pass!=m_cpass)
	{
		MessageBox("两次口令输入不一致,请重新输入", "错误",MB_ICONINFORMATION);

	}
	//当两次口令不一致,自动清除加密口令和确认口令两个编辑框内的字符,光标转到加密口令编辑框

	//实现加密
	if (ecflie(m_Path))
	{
		MessageBox("此数据文件已加密成功", "成功",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("加密失败", "失败", MB_ICONINFORMATION);

	}


}


//解密
void CFileEDSoftwareDlg::OnBnClickedBdecryption()
{
	
	UpdateData(TRUE);//更新数据   将路径显示到窗口
	if (m_Path == "")//路径为空
	{
		MessageBox("请选择已加密的文件", "错误", MB_ICONINFORMATION);
		return;
	}

	UpdateData(true);//口令不能为空
	if (m_pass == "" )
	{
		MessageBox("请输入揭秘口令", "错误", MB_ICONINFORMATION);
		return;
	}

	//实现加密
	if (dcfile(m_Path))
	{
		MessageBox("数据文件已解密成功", "成功", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("解密失败", "失败", MB_ICONINFORMATION);

	}

}

//自己设计的成员函数
//////////////////////////////////////////

//获得密码
__int64 CFileEDSoftwareDlg::epass()
{
	DWORD plen;//密码长度
	char *ppass;
	__int64 mc = 9979989969999;
	UpdateData(TRUE);

	//多字节编码
	ppass = m_pass.GetBuffer(0);//获取密码

	plen = strlen(ppass);

	//加密算法 
	for (int i = 0; i < (int)plen; i++)
	{
		mc ^= ppass[i] | 128;//对密码进行异或

	}

	return mc;


}





BOOL CFileEDSoftwareDlg::ecflie(LPCTSTR fpath)
{

	char *data;
	CFile *file;//文件
	DWORD flen;//文件长度

	m_password = epass();
	file = new CFile;

	if (!file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite));//读取文件
	{
		MessageBox("文件打开失败!!", "错误");
		return false;
	}
	flen = file->GetLength();
	data = new char[(int)flen];//开辟数组 存储数据
	file->SeekToBegin();//文件指针位于文件首部
	file->Read(data, flen);//读取


	//数据加密
	for (int i = 0; i < (int)flen; i++)
	{
		data[i] ^= m_password;
		data[i] ^= flen;
	}

	file->SeekToBegin();
	file->Write(data, flen);//写入
	delete[] data;

	//添加密码验证信息
	char cpass[5] = "wang";//最后一位 \0
	for (int i = 0; i < 5; i++)
	{
		cpass[i] ^= m_password;
	}

	file->SeekToBegin();
	file->Write(&cpass, 5);//在文件末未写入密码校验
	file->Close();
	delete file;
	return TRUE;

}




//选择路径
void CFileEDSoftwareDlg::OnBnClickedBselect()
{
	CFileDialog dlg(TRUE);
	
	if (dlg.DoModal()==IDOK)
	{
		m_Path = dlg.GetPathName();//获取对话框里的路径
		UpdateData(FALSE);

	}
	else
		return;

}






BOOL CFileEDSoftwareDlg::dcfile(LPCTSTR fpath)
{

	char *data;
	CFile *file;//文件
	DWORD flen;//文件长度
	char checkcode[5];

	file = new CFile;

	if (!file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite));//读取文件
	{
		MessageBox("文件打开失败!!", "错误");
		return false;
	}


	flen = file->GetLength();
	data = new char[(int)flen];//开辟数组 存储数据

	//实习按密码验证是否正确
	file->Seek(-5, CFile::end);
	file->Read(&checkcode, 5);
	m_password = epass();

	for (int i = 0; i < 5; i++)
	{
		checkcode[i] ^= m_password;

	}

	if (strcmp(checkcode,"wang")!=0)//密码校验不一致
	{
		MessageBox("密码校验不一致", "错误");
		return FALSE;
	}


	//解密
	file->SeekToBegin();
	file->Read(data, flen);

	for (int i = 0; i < (int)flen; i++)
	{
		data[i] ^= m_password;
		data[i] ^= (flen - 5);
	}

	file->SeekToBegin();
	file->Write(data, flen);//写入文件
	file->SetLength(flen - 5);//文件大小
	file->Close();

	delete[]data;
	delete file;


	return  TRUE;
}







