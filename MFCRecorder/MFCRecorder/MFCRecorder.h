
// MFCRecorder.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCRecorderApp: 
// �йش����ʵ�֣������ MFCRecorder.cpp
//

class CMFCRecorderApp : public CWinApp
{
public:
	CMFCRecorderApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCRecorderApp theApp;