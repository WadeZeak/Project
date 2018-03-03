
// VerificationCodeDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include<time.h>

// CVerificationCodeDlg �Ի���
class CVerificationCodeDlg : public CDialogEx
{
// ����
public:
	CVerificationCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERIFICATIONCODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	CEdit m_cSta;
	int m_iLong;
	int m_iCount;
	BOOL m_bCkCase;
	BOOL m_bCkNum;
	BOOL m_bOnlyNum;
	CString m_sSta;
	afx_msg void OnBnClickedButtonCls();
	afx_msg void OnBnClickedButtonDo();
	CString Generate(int iLong, bool bUpLow, bool bNum, bool bNumOnly);
	CString getChar(int iflag);

	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedCheckNumonly();
};
