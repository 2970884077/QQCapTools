
// AlimCap.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include<afx.h>
#include<afxshellmanager.h>
#include<Windows.h>
#include<afxdisp.h>

#include "resource.h"		// ������
#include"AnalysisCap.h"


// CAlimCapApp:
// �йش����ʵ�֣������ AlimCap.cpp
//

class CAlimCapApp : public CWinApp
{
public:
	CAlimCapApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()

public:
	//ȫ��cap��������
	CAnalysisCap CACap;
};

extern CAlimCapApp theApp;