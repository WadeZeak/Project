
// QQMessageHelper.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CQQMessageHelperApp: 
// �йش����ʵ�֣������ QQMessageHelper.cpp
//

class CQQMessageHelperApp : public CWinApp
{
public:
	CQQMessageHelperApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CQQMessageHelperApp theApp;