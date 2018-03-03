
// KuWoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KuWo.h"
#include "KuWoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CKuWoDlg �Ի���



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


// CKuWoDlg ��Ϣ�������

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


	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CKuWoDlg::OnPaint()
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
HCURSOR CKuWoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ͼƬ���г�ʼ��
void CKuWoDlg::InitUI()
{
	m_kugouUI.width = 204;
	m_kugouUI.height = 209;
	
	m_kugouUI.main = MakeUiItem(48, 48, 106, 106, 51, 99, true);//��ʾ�м䲿��
	m_kugouUI.left = MakeUiItem(0, 54,98, 100, 110, 0,0);//���
	m_kugouUI.right = MakeUiItem(106, 54, 98, 100,110, 0,0);//�ұ�
	m_kugouUI.top = MakeUiItem(53, 0, 98, 100, 110, 0,0);//����
	m_kugouUI.bottom = MakeUiItem(53,109,98,100,110,0,0);//�ײ�

	m_kugouUI.item[0] = MakeUiItem(30,90,24,24,113,179,0);
	m_kugouUI.item[1] = MakeUiItem(91,24,24,24,113,154,0);
	m_kugouUI.item[2] = MakeUiItem(158,90,24,24,138,179,0);
	m_kugouUI.item[3] = MakeUiItem(91,157,24,24,138,154,0);


	LoadRecImage(IDB_PNG1, m_pSrcImage);//������Դ�е�PNGͼƬ
	ModifyStyleEx(0, WS_EX_LAYERED);



}






// ������ÿ��С��Ƭ���д���
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


// �����Ӹ���Դ�ļ��л�ȡͼƬ
int CKuWoDlg::LoadRecImage(int nRecID, Image* img)
{
	//��ȡ��ԴID
	HINSTANCE hIns=AfxGetInstanceHandle();//��ȡ��ǰʵ�����

	
	HRSRC hRsrc=::FindResource(hIns,MAKEINTRESOURCE(nRecID),_T("png"));//������Դ�������ؾ��

	if (!hRsrc)
		return 0;

	DWORD len=SizeofResource(hIns,hRsrc);//��ȡ��Դ��С,�������ڴ��д����Դ
	BYTE *LpRsrc=(BYTE *)LoadResource(hIns, hRsrc);//������Դ���ڴ�

	 HGLOBAL m_hMem=GlobalAlloc(GMEM_FIXED,len);//����16λ�����������ڴ�  ���ؾ��
	 BYTE *pmem = (BYTE *)GlobalLock(m_hMem);//�ڴ����  

	 memcpy(pmem, LpRsrc, len);//�����ݷ����ڴ�ռ�

	 IStream *pstm;
	 CreateStreamOnHGlobal(m_hMem,false,&pstm);//������ȫ�ֵ���
	img= Gdiplus::Image::FromStream(pstm);
	GlobalUnlock(m_hMem); //�����ڴ�
	pstm->Release();//�ͷ�
	FreeResource(LpRsrc);//�ͷ���Դ
	return 0;
}
