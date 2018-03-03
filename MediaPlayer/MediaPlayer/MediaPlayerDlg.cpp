
// MediaPlayerDlg.cpp : 实现文件
//



#include "stdafx.h"
#include "MediaPlayer.h"
#include "MediaPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CMediaPlayerDlg 对话框



//图标
CMediaPlayerDlg::CMediaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMediaPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)//与控件绑定的变量
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_list);

}

BEGIN_MESSAGE_MAP(CMediaPlayerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_PLAY, &CMediaPlayerDlg::OnBnClickedBtnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CMediaPlayerDlg::OnBnClickedBtnPause)
	ON_WM_DROPFILES()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CMediaPlayerDlg::OnDblclkList)
END_MESSAGE_MAP()


// CMediaPlayerDlg 消息处理程序

BOOL CMediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//显示播放 列表
	m_list.InsertColumn(0, _T("播放列表"), LVCFMT_CENTER, 205);


	//固定对话框 
	//获取对话框的风格
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle = dwStyle&~WS_MAXIMIZEBOX;//去掉最大化
	dwStyle = dwStyle&~WS_MAXIMIZE;//去掉最大边框
	dwStyle = dwStyle&~WS_SIZEBOX;//禁止拉伸

	//重新设置
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMediaPlayerDlg::OnPaint()
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
HCURSOR CMediaPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//play
void CMediaPlayerDlg::OnBnClickedBtnPlay()
{

	//CString str = _T("C:\\Users\\Zeak_K\\Desktop\\test.mp4");
//
	//MessageBox(str);
	//	m_play.Play((CW2A)str, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//实现播放

	//CW2A 实现从CString 到char*的转换

	POSITION pos = m_list.GetFirstSelectedItemPosition();//获取第一个选中的控件信息
	int nSel = m_list.GetNextSelectedItem(pos);//选中
	if (nSel<0)
	{
		MessageBox(_T("请先选中后后在播放"),_T("视频播放器"));
		return;
	}

	CString strPath = m_list.GetItemText(nSel,0);//将选中的路径赋值

	m_play.Play((CW2A)strPath, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//实现播放
}





//pause
void CMediaPlayerDlg::OnBnClickedBtnPause()
{
	m_play.Pause(); 
}



//实现拖拽文件
void CMediaPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH];//260
	UINT nCount = DragQueryFile(hDropInfo,0xffffffff,NULL,0);//拖拽的路径数量
	
	for (UINT i = 0; i < nCount; i++)
	{
		DragQueryFile(hDropInfo,i,szFileName,MAX_PATH);
		m_list.InsertItem(i, szFileName);//显示路径
	//	AfxMessageBox(szFileName);
	}
	

	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);//递归
}


void CMediaPlayerDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码

	int nItem = pNMItemActivate->iItem;

	if (nItem<0)//没有选中
	{
		return;
	}
	//播放
	CString strPath = m_list.GetItemText(nItem, 0);
	m_play.Play((CW2A)strPath, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//实现播放


	*pResult = 0;
}
