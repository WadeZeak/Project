
// MFCRecorderDlg.h : ͷ�ļ�
//
//pragma Ԥ����ָ��

/*
Ԥ���� 
pragma define if include  ��������
*/

#pragma once

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

//MCI media control interface 


// CMFCRecorderDlg �Ի���
class CMFCRecorderDlg : public CDialogEx
{


private:
	MCIDEVICEID m_IdDevice;//ID��ʶ ���豸 �����豸 ¼���豸  �����豸 ֹͣ�豸 �����豸

	//�����ʱ��
	int m_nHour=0;
	int m_nMin=0;
	int m_nSec=0;
	CString m_str;//����ʱ�����ַ���

// ����
public:
	CMFCRecorderDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCRECORDER_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButSave();
	afx_msg void OnBnClickedButRecord();
	afx_msg void OnBnClickedButStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
