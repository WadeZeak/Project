
// FileEDSoftwareDlg.h : ͷ�ļ�
//

#pragma once


// CFileEDSoftwareDlg �Ի���
class CFileEDSoftwareDlg : public CDialogEx
{
// ����
public:
	CFileEDSoftwareDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FILEEDSOFTWARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//������Ա
	__int64 epass();//64���� ��ȡ����ĺ�����Ա����
	__int64 m_password;

	BOOL ecflie(LPCTSTR fpath);//����
	BOOL dcfile(LPCTSTR fpath);//����

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBexit();
	afx_msg void OnBnClickedBencryption();
	afx_msg void OnBnClickedBdecryption();
	CString m_Path;
	CString m_pass;
	CString m_cpass;
	afx_msg void OnBnClickedBselect();
};
