
// FileEDSoftware.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFileEDSoftwareApp: 
// �йش����ʵ�֣������ FileEDSoftware.cpp
//

class CFileEDSoftwareApp : public CWinApp
{
public:
	CFileEDSoftwareApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFileEDSoftwareApp theApp;