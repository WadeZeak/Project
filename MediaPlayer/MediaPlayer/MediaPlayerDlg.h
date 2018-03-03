
// MediaPlayerDlg.h : 头文件
//
#include"Play.h"//播放的头文件

#pragma once


// CMediaPlayerDlg 对话框
class CMediaPlayerDlg : public CDialogEx
{

private:
	CPlay m_play;

// 构造
public:
	CMediaPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MEDIAPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
};
