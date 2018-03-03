
// MediaPlayerDlg.h : ͷ�ļ�
//
#include"Play.h"//���ŵ�ͷ�ļ�

#pragma once


// CMediaPlayerDlg �Ի���
class CMediaPlayerDlg : public CDialogEx
{

private:
	CPlay m_play;

// ����
public:
	CMediaPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEDIAPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
