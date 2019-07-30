#pragma once
#include "HexEdit.h"
#include "afxwin.h"
#include<afxdialogex.h>


// CDialogDec �Ի���

class CDialogDec : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogDec)

public:
	CDialogDec(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogDec();

// �Ի�������
	enum { IDD = IDD_DIALOG_DEC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadio(UINT idCtl);
	afx_msg void OnBnClickedButton1();
public:
	CWnd* mHexEdit1;
	CWnd* mHexEdit2;
	CEdit cTrlKey;
public:
	CString mKey;
public:
	void SetKey(CString);
};
