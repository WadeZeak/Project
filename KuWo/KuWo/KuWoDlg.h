
// KuWoDlg.h : ͷ�ļ�
//

#pragma once

typedef struct UIITEM
{
	//ÿ��С��Ƭ�ڽ����е�λ��
	int x;
	int y;

	//ÿ��С��Ƭ�Ĵ�С
	int width;
	int height;

	//ÿ��С��Ƭ��PNGͼ�е�����
	int SrcX;
	int SrcY;

	//ͼƬ�Ƿ���ʾ
	bool Show;

}UITEM,*PUITEM;


//��ÿһ��СͼƬ���з�װ
typedef struct KUGOUUI 
{
	UITEM main;//�м��ͼ��
	UITEM left;//��ߵ�ͼ��
	UITEM right; //�ұߵ�ͼ��
	UITEM bottom;//�ײ���ͼ��
	UITEM top;//������ͼ��
	UITEM item[5];//ͼ���м��Сͼ��

	//��������Ĵ�С
	int height;
	int width;

}KUGOUUI,*PKUGOUUI;




// CKuWoDlg �Ի���
class CKuWoDlg : public CDialogEx
{
// ����
public:
	CKuWoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KUWO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	//�������
	KUGOUUI m_kugouUI;//����Ľ������
	Image *m_pSrcImage; //�����ԴͼƬ  ��������ͼƬ��ָ��
	bool m_Play;//�ж�����Ƿ�������λ��(�Ի�������)





	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void InitUI();
	// ������ÿ��С��Ƭ���д���
	UIITEM MakeUiItem(int x, int y, int height, int width, int SrcX, int SrcY,bool Show);
	// �����Ӹ���Դ�ļ��л�ȡͼƬ
	int LoadRecImage(int nRecID, Image* img);
};
