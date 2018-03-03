
// MFCRecorderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCRecorder.h"
#include "MFCRecorderDlg.h"
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


// CMFCRecorderDlg �Ի���



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


// CMFCRecorderDlg ��Ϣ�������

BOOL CMFCRecorderDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�


void CMFCRecorderDlg::OnPaint()
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
		CPaintDC dc(this);
		m_str.Format(L"%02d:%02d:%02d", m_nHour, m_nHour, m_nSec); 
		

		//��������
		CFont font;
		font.CreatePointFont(400, L"΢���ź�");
		dc.SelectObject(font);
		dc.SetTextColor(RGB(255, 0, 0));//����������ɫ
		dc.SetBkMode(TRANSPARENT);//����ͬ��
		dc.TextOut(50, 10, m_str);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCRecorderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




//�ر� ֹͣ ֱ��ֹͣ����
//���� ·��

//������Ƶ
void CMFCRecorderDlg::OnBnClickedButSave()
{
	CTime time = CTime::GetCurrentTime();//��ȡϵͳ��ǰʱ��
	CFileDialog dlg(FALSE,//FALSE ���Ϊ   TRUE ��
		L"wav",
		time.Format(L"%Y%m%d%H%M%S"),
		OFN_PATHMUSTEXIST,
		L"WAV�ļ�(*.wav)|*.wav|�����ļ�(*.*)|*.*||"	);

	if (IDCANCEL==dlg.DoModal())//ȡ��
		return;


	//����
	//�����豸
	MCI_SAVE_PARMS saveParms = { 0 };//������豸
	CString str = dlg.GetPathName();
	//���
	saveParms.lpfilename = str;//�ļ�����

	//
	mciSendCommand(m_IdDevice,MCI_SAVE,MCI_SAVE_FILE|
		MCI_WAIT ,//�ȴ��´ε�¼��
		(DWORD)&saveParms);


	mciSendCommand(m_IdDevice, MCI_CLOSE, NULL, NULL);//�ر��豸 ���ռ��
	m_IdDevice = NULL;

	//�����ļ�ʱ,����ʱ����0
	m_nHour = 0;
	m_nSec = 0;
	m_nMin = 0;
	Invalidate(true);
}





//��ʼ¼��
void CMFCRecorderDlg::OnBnClickedButRecord()
{
	/*
	MCIERROR mciSendCommand(
MCIDEVICEID wIDDevice, ��//�豸��ID���ڴ��豸ʱ���øò��� //NULL ��ɺ�ֵ
UINT��uMsg, ��//������Ϣ //�� ¼�� ���� ���� ��ͣ ����
DWORD ��fdwCommand, //������Ϣ�ı�־ //��¼�ƶ��� ��ʽ ���� ������ ���ݿ�Ķ��뵥λ
DWORD ��dwParam ��//ָ�����������Ϣ�����Ľṹ //�ṹ
); //���ɹ��򷵻�0�����򷵻ش�����
ʹ��ʱ����ӣ�
#include <MMSystem.h>
#pragma comment(lib, "WINMM.LIB")*/

	//1.�ر�  ��ֹ�ڴ����������ݵ��´���
	mciSendCommand(m_IdDevice,MCI_CLOSE,NULL,NULL);//����֮�� ��ĳһ�豸������ָ��
	
	//2.��
	//a.�����豸  ��
	MCI_OPEN_PARMS openParms;
	//b.���ṹ

	openParms.lpstrDeviceType =(LPCWSTR) MCI_DEVTYPE_WAVEFORM_AUDIO;
	openParms.lpstrElementName = L"";
	 //c.����ʩ��
	mciSendCommand(NULL, MCI_OPEN,
						MCI_OPEN_TYPE|
							MCI_OPEN_ELEMENT|
								MCI_OPEN_TYPE_ID,
									(DWORD)&openParms);

	//��ֵ��ʼ��
	m_IdDevice = openParms.wDeviceID;//������򿪵���Ƶ

	//3.����
	//a.�����豸 ����
	MCI_WAVE_SET_PARMS setParms;//
	//b.���ṹ
	setParms.wFormatTag = WAVE_FORMAT_PCM;//�����ļ�Ҳ��PCM ��ʽ
	setParms.nChannels = 2;//1 ������ 2 ������
	setParms.nSamplesPerSec = 11025;//������
	setParms.nAvgBytesPerSec = 11025 * 2;
	setParms.nBlockAlign = 2;//���ݿ����
	setParms.wBitsPerSample = 8;//��������ݿ��λ
		//c.����ʩ��
	mciSendCommand(m_IdDevice, 
						MCI_SET, 
							MCI_WAVE_SET_FORMATTAG | //��ʽ
								MCI_WAVE_SET_CHANNELS | //����
								MCI_WAVE_SET_BITSPERSAMPLE, //ÿ�����ݿ�λ�Ĵ�С
										(DWORD)&setParms);
	
	//4.¼��
	//a.���ö�����豸
	MCI_RECORD_PARMS recordParms = {0};
	//b.���ṹ��
	//c.����ʩ��
	mciSendCommand(m_IdDevice, MCI_RECORD, NULL, (DWORD)&recordParms);


	SetTimer(1, 1000, NULL);//�򿪶�ʱ��

}







//ֹͣ¼��
void CMFCRecorderDlg::OnBnClickedButStop()
{	

	mciSendCommand(m_IdDevice, MCI_STOP, NULL, NULL);
	KillTimer(1);//�رն�ʱ��
}


//void CAboutDlg::OnTimer(UINT_PTR nIDEvent)
//{
//	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//	CDialogEx::OnTimer(nIDEvent);
//}



//��ʱ��

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
		Invalidate(true);//ˢ����Ļ
	}



	CDialogEx::OnTimer(nIDEvent);
}


BOOL CMFCRecorderDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);//��ȡ�Ի���ľ���
	rect.bottom = 20;
	pDC->FillSolidRect(&rect,RGB(0,100,255));//�����ɫ
	
	
	CRect rectClient;
	GetClientRect(&rectClient);
	rectClient.top = 20;
	pDC->FillSolidRect(&rectClient, RGB(0, 200, 255));//�����ɫ

	pDC->SetBkMode(TRANSPARENT);//����͸��
	pDC->SetTextColor(RGB(0, 0, 0));//����������ɫ

	CFont font;
	font.CreatePointFont(100, L"΢���ź�");
	pDC->SelectObject(&font);
	pDC->TextOut(3, 0, L"ʱ��Կ��");//����

	return TRUE;
}




LRESULT CMFCRecorderDlg::OnNcHitTest(CPoint point)
{
	
	UINT nHitTest = CDialogEx::OnNcHitTest(point);
	if (nHitTest == HTCLIENT) //HTCLIENT �ͻ���
	{
		nHitTest = HTCAPTION;//�ͻ���
	}

	return nHitTest;
}
