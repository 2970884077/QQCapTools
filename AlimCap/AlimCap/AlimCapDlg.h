
// AlimCapDlg.h : ͷ�ļ�
//

#pragma once
#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include"MyEditBrowseCtrl.h"
#include"AnalysisCap.h"
#include "afxwin.h"
#include"MyListCtrl.h"
#include "HexEdit.h"
#include"DialogDec.h"
#include"DialogPwd.h"
#include"DialogSniffer.h"
#include"DialogMsg.h"
#include"ScanMemKeyDialog.h"


// CAlimCapDlg �Ի���
class CAlimCapDlg : public CDialogEx
{
// ����
public:
	CAlimCapDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CAlimCapDlg();

// �Ի�������
	enum { IDD = IDD_ALIMCAP_DIALOG };

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
	CMyEditBrowseCtrl mFileEditBox;
	//cap�ļ�ѡ������
	CString mCapFile;
	// ���ݰ��Ự����
	CString mPassWord;
	// �û�ID�б�
	CComboBox mUserList;
	//CString mUserId;
	// SessionKey
	//CComboBox mSessionKeys;
	CString mSessionKey;
	// ������ʾ�ؼ�
	MyListCtrl m_List;
	CWnd*		mHexEdit;
	CWnd*		mHexEditText;
	CComboBox cbSessions;
	//�Ի���
	CDialogPwd *pPwdDialog;
	CDialogSniffer *pSnifferDialog;
	CDialogDec *pDialogDec;
	CScanMemKeyDialog *pDialogScanKey;
	POINT old;
	CStatic mResult;//�����ʾ
	CIPAddressCtrl mFilterSrcIp;
	CIPAddressCtrl mFilterDstIp;
	CEdit mFilterSrcPort;
	CEdit mFilterDstPort;
public:
	afx_msg void OnBnClickedMfcbutton2();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedRadio(UINT idCtl);
	afx_msg void OnSessionSelchange();
	afx_msg void OnMenuDec();
	afx_msg void OnSetPwd();
	afx_msg void OnSniferDialog();
	afx_msg void OnSendMsg();
	afx_msg void OnScanMemECDHKEY();
	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	void ReSize();
	void ClearControl();
	bool GetLocalPwdHash();
	bool SaveLocalPwdHash();
	void GetFilterInfo();
	CAnalysisCap* GetCACap(){ return &(((CAlimCapApp*)AfxGetApp())->CACap); };
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedCheck5();
};
