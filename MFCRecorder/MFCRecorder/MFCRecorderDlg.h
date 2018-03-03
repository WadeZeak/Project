
// MFCRecorderDlg.h : 头文件
//
//pragma 预处理指令

/*
预处理 
pragma define if include  条件编译
*/

#pragma once

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

//MCI media control interface 


// CMFCRecorderDlg 对话框
class CMFCRecorderDlg : public CDialogEx
{


private:
	MCIDEVICEID m_IdDevice;//ID标识 打开设备 设置设备 录制设备  播放设备 停止设备 保存设备

	//定义计时器
	int m_nHour=0;
	int m_nMin=0;
	int m_nSec=0;
	CString m_str;//保存时分秒字符串

// 构造
public:
	CMFCRecorderDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCRECORDER_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButSave();
	afx_msg void OnBnClickedButRecord();
	afx_msg void OnBnClickedButStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
