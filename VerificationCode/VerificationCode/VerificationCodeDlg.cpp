
// VerificationCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VerificationCode.h"
#include "VerificationCodeDlg.h"
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
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CVerificationCodeDlg �Ի���


//���캯��
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


// CVerificationCodeDlg ��Ϣ�������

BOOL CVerificationCodeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_sSta = _T("�ȴ�������֤��");
	m_cSta.SetWindowTextW(m_sSta);
	srand((unsigned)time(NULL));//���������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVerificationCodeDlg::OnPaint()
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
HCURSOR CVerificationCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�����ť

void CVerificationCodeDlg::OnBnClickedButtonCls()
{
	UpdateData(FALSE);
	m_sSta.Empty();

	m_sSta = _T("�ȴ���֤�������....\r\n\n");
	m_cSta.SetWindowTextW(m_sSta);//��ʾ ���ֽ�

}


//������֤��
void CVerificationCodeDlg::OnBnClickedButtonDo()
{
	m_cSta.SetWindowTextW(_T(""));
	UpdateData(TRUE);//��ȡ����
	if (m_iCount>100)
		m_iCount = 100;
	if (m_iLong>100)
		m_iLong = 00;
	CString cstr;
	UpdateData(TRUE);//��������

	//������֤��
	for (int i = 0; i < m_iCount; i++)//m_iCount �� m_iLong ���ȵ���֤��
	{
		cstr = Generate(m_iLong, m_bCkCase, m_bCkNum, m_bOnlyNum);
		m_sSta += cstr;
		m_sSta += "\r\n";//����
	}

	
	m_cSta.SetRedraw(FALSE);//��ֹ����
	m_cSta.SetWindowTextW(m_sSta);
	m_cSta.LineScroll(m_cSta.GetLineCount());
	m_cSta.SetRedraw(TRUE);


}

 
CString CVerificationCodeDlg::Generate(int iLong, bool bUpLow, bool bNum, bool bNumOnly)
{

	int iFlag = 26;//Ĭ��ֻ��Сд��ĸ
	CString cstr;
	if ( bUpLow)
		iFlag = 52;//���ִ�Сд
	if (bNum)
		iFlag = 62;//��ѡ��������
	if (bNumOnly)
		iFlag = 10;//ֻ��������

	for (int i = 0; i < iLong; i++)
	{
		cstr += getChar(iFlag);
	}


	if (bNum&&(!bUpLow))//��ѡ�������֣����ǲ���ѡ���ִ�Сд
		cstr.MakeLower();//��дת��ΪСд


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


//ֻ��������
void CVerificationCodeDlg::OnBnClickedCheckNumonly()
{
	UpdateData(TRUE);
	if (m_bOnlyNum)
	{
		GetDlgItem(IDC_CHECK_CASE)->EnableWindow(FALSE);//���ִ�Сд������
		GetDlgItem(IDC_CHECK_CHECKNUM)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHECK_CASE)->EnableWindow(TRUE);//���ִ�Сд������
		GetDlgItem(IDC_CHECK_CHECKNUM)->EnableWindow(TRUE);

	}

}
