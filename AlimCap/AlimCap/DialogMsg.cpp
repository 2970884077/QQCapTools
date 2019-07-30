// DialogMsg.cpp : ʵ���ļ�
//

#include "AlimCap.h"
#include "DialogMsg.h"
#include"mymsg.h"
#include"QQSendPack.h"
#include"SendMsg.h"


// CDialogMsg �Ի���

IMPLEMENT_DYNAMIC(CDialogMsg, CDialogEx)

CDialogMsg::CDialogMsg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogMsg::IDD, pParent)
	, mQQ(_T(""))
	, mText(_T(""))
	, mSrcIP(0)
	, mSrcMac(_T(""))
	, mSrcPort(_T(""))
	, mDstIP(0)
	, mDstMac(_T(""))
	, mDstPort(_T(""))
	, mKey(_T(""))
{

}

CDialogMsg::~CDialogMsg()
{
}

void CDialogMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mQQ);
	DDX_Text(pDX, IDC_EDIT8, mText);
	DDX_Control(pDX, IDC_LIST1, mList);
	DDX_IPAddress(pDX, IDC_IPADDRESS1, mSrcIP);
	DDX_Text(pDX, IDC_EDIT3, mSrcMac);
	DDX_Text(pDX, IDC_EDIT5, mSrcPort);
	DDX_IPAddress(pDX, IDC_IPADDRESS2, mDstIP);
	DDX_Text(pDX, IDC_EDIT4, mDstMac);
	DDX_Text(pDX, IDC_EDIT9, mDstPort);
	DDX_Text(pDX, IDC_EDIT2, mKey);
}


BEGIN_MESSAGE_MAP(CDialogMsg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialogMsg::OnBnClickedButton1)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON2, &CDialogMsg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialogMsg ��Ϣ�������


BOOL CDialogMsg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CenterWindow();

	char _column[][MAX_HEADLENGTH] = { "���", "Ŀ��QQ", "����" };
	this->mList.SetHeaders(_column, sizeof(_column) / sizeof(*_column));
	this->mList.SetColumnWidth(0, 50);
	this->mList.SetColumnWidth(1, 80);
	this->mList.EnsureVisible(mList.GetItemCount() - 1, FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

//������Ϣ
void CDialogMsg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CQQSendPack send;
	this->UpdateData(TRUE);
	send.send(mKey,mQQ, mSrcIP, mSrcPort, mSrcMac, mDstIP, mDstPort, mDstMac,mText);
}


BOOL CDialogMsg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (pCopyDataStruct->dwData)
	{
	case WM_SNIFFER_SEND:
	case WM_MAIN_SEND:
		{
			CSendMsg *pSend = (CSendMsg*)pCopyDataStruct->lpData;
			char buf[0x10] = { 0 };
			ultoa(htons(pSend->mNetInfo.srcport), buf, 10);
			std::string strMac = GetCACap()->HexToStr(pSend->mMacInfo.srcMac, MAC_LEN);
			this->SetSrcInfo(htonl(pSend->mNetInfo.srcip), buf, strMac.c_str());
			ultoa(htons(pSend->mNetInfo.dstport), buf, 10);
			strMac = GetCACap()->HexToStr(pSend->mMacInfo.dstMac, MAC_LEN);
			this->SetDstInfo(htonl(pSend->mNetInfo.dstip), buf, strMac.c_str());
			this->UpdateData(FALSE);
		}break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

//�����շ���ַ
void CDialogMsg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData(TRUE);
	DWORD _mSrcIP = mSrcIP;
	CString _mSrcMac = mSrcMac;
	CString _mSrcPort = mSrcPort;
	mSrcIP = mDstIP;
	mSrcMac = mDstMac;
	mSrcPort = mDstPort;
	mDstIP = _mSrcIP;
	mDstMac = _mSrcMac;
	mDstPort = _mSrcPort;
	this->UpdateData(FALSE);
}
