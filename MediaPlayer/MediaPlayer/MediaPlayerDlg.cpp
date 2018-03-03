
// MediaPlayerDlg.cpp : ʵ���ļ�
//



#include "stdafx.h"
#include "MediaPlayer.h"
#include "MediaPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




// CMediaPlayerDlg �Ի���



//ͼ��
CMediaPlayerDlg::CMediaPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMediaPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMediaPlayerDlg::DoDataExchange(CDataExchange* pDX)//��ؼ��󶨵ı���
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


// CMediaPlayerDlg ��Ϣ�������

BOOL CMediaPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//��ʾ���� �б�
	m_list.InsertColumn(0, _T("�����б�"), LVCFMT_CENTER, 205);


	//�̶��Ի��� 
	//��ȡ�Ի���ķ��
	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
	dwStyle = dwStyle&~WS_MAXIMIZEBOX;//ȥ�����
	dwStyle = dwStyle&~WS_MAXIMIZE;//ȥ�����߿�
	dwStyle = dwStyle&~WS_SIZEBOX;//��ֹ����

	//��������
	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMediaPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	} 
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	//	m_play.Play((CW2A)str, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//ʵ�ֲ���

	//CW2A ʵ�ִ�CString ��char*��ת��

	POSITION pos = m_list.GetFirstSelectedItemPosition();//��ȡ��һ��ѡ�еĿؼ���Ϣ
	int nSel = m_list.GetNextSelectedItem(pos);//ѡ��
	if (nSel<0)
	{
		MessageBox(_T("����ѡ�к���ڲ���"),_T("��Ƶ������"));
		return;
	}

	CString strPath = m_list.GetItemText(nSel,0);//��ѡ�е�·����ֵ

	m_play.Play((CW2A)strPath, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//ʵ�ֲ���
}





//pause
void CMediaPlayerDlg::OnBnClickedBtnPause()
{
	m_play.Pause(); 
}



//ʵ����ק�ļ�
void CMediaPlayerDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFileName[MAX_PATH];//260
	UINT nCount = DragQueryFile(hDropInfo,0xffffffff,NULL,0);//��ק��·������
	
	for (UINT i = 0; i < nCount; i++)
	{
		DragQueryFile(hDropInfo,i,szFileName,MAX_PATH);
		m_list.InsertItem(i, szFileName);//��ʾ·��
	//	AfxMessageBox(szFileName);
	}
	

	DragFinish(hDropInfo);
	CDialogEx::OnDropFiles(hDropInfo);//�ݹ�
}


void CMediaPlayerDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	int nItem = pNMItemActivate->iItem;

	if (nItem<0)//û��ѡ��
	{
		return;
	}
	//����
	CString strPath = m_list.GetItemText(nItem, 0);
	m_play.Play((CW2A)strPath, GetDlgItem(IDC_STATIC)->GetSafeHwnd());//ʵ�ֲ���


	*pResult = 0;
}
