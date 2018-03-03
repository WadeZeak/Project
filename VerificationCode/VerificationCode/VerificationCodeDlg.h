
// VerificationCodeDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include<time.h>

// CVerificationCodeDlg 对话框
class CVerificationCodeDlg : public CDialogEx
{
// 构造
public:
	CVerificationCodeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERIFICATIONCODE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
