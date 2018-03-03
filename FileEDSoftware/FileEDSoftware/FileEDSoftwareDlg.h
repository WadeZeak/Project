
// FileEDSoftwareDlg.h : 头文件
//

#pragma once


// CFileEDSoftwareDlg 对话框
class CFileEDSoftwareDlg : public CDialogEx
{
// 构造
public:
	CFileEDSoftwareDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FILEEDSOFTWARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//声明成员
	__int64 epass();//64整型 获取密码的函数成员函数
	__int64 m_password;

	BOOL ecflie(LPCTSTR fpath);//加密
	BOOL dcfile(LPCTSTR fpath);//解密

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
	afx_msg void OnBnClickedBexit();
	afx_msg void OnBnClickedBencryption();
	afx_msg void OnBnClickedBdecryption();
	CString m_Path;
	CString m_pass;
	CString m_cpass;
	afx_msg void OnBnClickedBselect();
};
