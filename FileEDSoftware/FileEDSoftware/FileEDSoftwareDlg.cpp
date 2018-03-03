
// FileEDSoftwareDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileEDSoftware.h"
#include "FileEDSoftwareDlg.h"
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


// CFileEDSoftwareDlg �Ի���



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


// CFileEDSoftwareDlg ��Ϣ�������

BOOL CFileEDSoftwareDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileEDSoftwareDlg::OnPaint()
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
HCURSOR CFileEDSoftwareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





//�˳�
void CFileEDSoftwareDlg::OnBnClickedBexit()
{
	this->EndDialog(true);
}


//����
void CFileEDSoftwareDlg::OnBnClickedBencryption()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	UpdateData(TRUE);//��������   ��·����ʾ������
	if (m_Path == "")//·��Ϊ��
	{
		MessageBox("��ѡ��Ҫ���ܵ��ļ�", "����", MB_ICONINFORMATION);
		return;
	}

	UpdateData(true);//�����Ϊ��
	if (m_pass==""||m_cpass=="")
	{
		MessageBox("�����ļ����ܿ����Ϊ��", "����",MB_ICONINFORMATION);
		return;
	}

	if (m_pass!=m_cpass)
	{
		MessageBox("���ο������벻һ��,����������", "����",MB_ICONINFORMATION);

	}
	//�����ο��һ��,�Զ�������ܿ����ȷ�Ͽ��������༭���ڵ��ַ�,���ת�����ܿ���༭��

	//ʵ�ּ���
	if (ecflie(m_Path))
	{
		MessageBox("�������ļ��Ѽ��ܳɹ�", "�ɹ�",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("����ʧ��", "ʧ��", MB_ICONINFORMATION);

	}


}


//����
void CFileEDSoftwareDlg::OnBnClickedBdecryption()
{
	
	UpdateData(TRUE);//��������   ��·����ʾ������
	if (m_Path == "")//·��Ϊ��
	{
		MessageBox("��ѡ���Ѽ��ܵ��ļ�", "����", MB_ICONINFORMATION);
		return;
	}

	UpdateData(true);//�����Ϊ��
	if (m_pass == "" )
	{
		MessageBox("��������ؿ���", "����", MB_ICONINFORMATION);
		return;
	}

	//ʵ�ּ���
	if (dcfile(m_Path))
	{
		MessageBox("�����ļ��ѽ��ܳɹ�", "�ɹ�", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("����ʧ��", "ʧ��", MB_ICONINFORMATION);

	}

}

//�Լ���Ƶĳ�Ա����
//////////////////////////////////////////

//�������
__int64 CFileEDSoftwareDlg::epass()
{
	DWORD plen;//���볤��
	char *ppass;
	__int64 mc = 9979989969999;
	UpdateData(TRUE);

	//���ֽڱ���
	ppass = m_pass.GetBuffer(0);//��ȡ����

	plen = strlen(ppass);

	//�����㷨 
	for (int i = 0; i < (int)plen; i++)
	{
		mc ^= ppass[i] | 128;//������������

	}

	return mc;


}





BOOL CFileEDSoftwareDlg::ecflie(LPCTSTR fpath)
{

	char *data;
	CFile *file;//�ļ�
	DWORD flen;//�ļ�����

	m_password = epass();
	file = new CFile;

	if (!file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite));//��ȡ�ļ�
	{
		MessageBox("�ļ���ʧ��!!", "����");
		return false;
	}
	flen = file->GetLength();
	data = new char[(int)flen];//�������� �洢����
	file->SeekToBegin();//�ļ�ָ��λ���ļ��ײ�
	file->Read(data, flen);//��ȡ


	//���ݼ���
	for (int i = 0; i < (int)flen; i++)
	{
		data[i] ^= m_password;
		data[i] ^= flen;
	}

	file->SeekToBegin();
	file->Write(data, flen);//д��
	delete[] data;

	//���������֤��Ϣ
	char cpass[5] = "wang";//���һλ \0
	for (int i = 0; i < 5; i++)
	{
		cpass[i] ^= m_password;
	}

	file->SeekToBegin();
	file->Write(&cpass, 5);//���ļ�ĩδд������У��
	file->Close();
	delete file;
	return TRUE;

}




//ѡ��·��
void CFileEDSoftwareDlg::OnBnClickedBselect()
{
	CFileDialog dlg(TRUE);
	
	if (dlg.DoModal()==IDOK)
	{
		m_Path = dlg.GetPathName();//��ȡ�Ի������·��
		UpdateData(FALSE);

	}
	else
		return;

}






BOOL CFileEDSoftwareDlg::dcfile(LPCTSTR fpath)
{

	char *data;
	CFile *file;//�ļ�
	DWORD flen;//�ļ�����
	char checkcode[5];

	file = new CFile;

	if (!file->Open(fpath, CFile::shareDenyNone | CFile::modeReadWrite));//��ȡ�ļ�
	{
		MessageBox("�ļ���ʧ��!!", "����");
		return false;
	}


	flen = file->GetLength();
	data = new char[(int)flen];//�������� �洢����

	//ʵϰ��������֤�Ƿ���ȷ
	file->Seek(-5, CFile::end);
	file->Read(&checkcode, 5);
	m_password = epass();

	for (int i = 0; i < 5; i++)
	{
		checkcode[i] ^= m_password;

	}

	if (strcmp(checkcode,"wang")!=0)//����У�鲻һ��
	{
		MessageBox("����У�鲻һ��", "����");
		return FALSE;
	}


	//����
	file->SeekToBegin();
	file->Read(data, flen);

	for (int i = 0; i < (int)flen; i++)
	{
		data[i] ^= m_password;
		data[i] ^= (flen - 5);
	}

	file->SeekToBegin();
	file->Write(data, flen);//д���ļ�
	file->SetLength(flen - 5);//�ļ���С
	file->Close();

	delete[]data;
	delete file;


	return  TRUE;
}







