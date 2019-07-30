// MyListCtrl.cpp : ʵ���ļ�
//

#include"resource.h"
#include "MyListCtrl.h"
#include"mymsg.h"
#include"AnalysisCap.h"
#include"AlimCap.h"
#include"DialogMsg.h"
#include"SendMsg.h"


// MyListCtrl

IMPLEMENT_DYNAMIC(MyListCtrl, CMFCListCtrl)

MyListCtrl::MyListCtrl()
{
	pMsgDialog = NULL;
	nMenu = 0;
	mMainType = 0;
}

MyListCtrl::~MyListCtrl()
{
	if (NULL != pMsgDialog)
	{
		delete pMsgDialog;
		pMsgDialog = NULL;
	}
}


BEGIN_MESSAGE_MAP(MyListCtrl, CMFCListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, &MyListCtrl::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(NM_CLICK, &MyListCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &MyListCtrl::OnLvnItemchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, &MyListCtrl::OnNMRClick)
	ON_COMMAND(ID_32789, &MyListCtrl::OnSendMsg)
	ON_COMMAND(ID_32790, &MyListCtrl::OnDecryptToSave)
	ON_COMMAND(ID_32795, &MyListCtrl::OnDelete)
END_MESSAGE_MAP()

// MyListCtrl ��Ϣ�������

void MyListCtrl::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ�������� 
	lStyle   &=   ~LVS_TYPEMASK;   //�����ʾ��ʽλ 
	lStyle|=(LVS_REPORT);   //������ʾ��ʽΪ����ʽ 
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������

	SetExtendedStyle(GetExtendedStyle()|LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	CMFCListCtrl::PreSubclassWindow();
}

void MyListCtrl::SetHeaders(TCHAR Array[][MAX_HEADLENGTH],int number)
{
	this->DeleteAllItems();
	CRect rect;
	this->GetWindowRect(&rect);
	for(int i=0;i<number;i++)
	{
		LVCOLUMN co;
		co.mask=LVCF_TEXT|LVCF_FMT|LVCF_WIDTH;
		co.fmt=LVCFMT_CENTER;
		co.cx=rect.Width()/number;
		co.pszText=Array[i];
		co.cchTextMax=sizeof(co.pszText);
		co.iSubItem=i;
		co.iOrder=i;
		this->InsertColumn(i,&co);
	}
}

int CALLBACK MyListCtrl::ListCompare(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) 
{
	DATA* pV=static_cast<DATA*>((PVOID)lParamSort); 
     
	int col=pV->m_nSortedCol;//���������ݸ�col,�����жϵ���˵ڼ���  
    //ȡ����ַ���  

	int nItem1,nItem2;
	LVFINDINFO FindInfo;
	FindInfo.flags=LVFI_PARAM;
	FindInfo.lParam=lParam1;
	nItem1=pV->Ctrl->FindItem(&FindInfo,-1);
	FindInfo.lParam=lParam2;
	nItem2=pV->Ctrl->FindItem(&FindInfo,-1);

	if((nItem1==-1)||(nItem2==-1))
	{
	   return 0;
	}
    CString strItem1, strItem2;
	strItem1=pV->Ctrl->GetItemText(lParam1,col);  
    strItem2=pV->Ctrl->GetItemText(lParam2,col);//���Ҫ�Ƚϵ��ַ�
    int iCompRes=0;
    switch(pV->m_nSortedCol) 
    { 
		case(1):
		case(2):
			{
				if(strItem1.CompareNoCase(strItem2)>0)
					iCompRes=1;
				else if(strItem1.CompareNoCase(strItem2)==0)
					iCompRes=0;
				else
					iCompRes=-1;
			}break;
		default: 
			{
				//Ĭ������
				if(StrToInt(strItem1)>StrToInt(strItem2))
					iCompRes=1;
				else if(StrToInt(strItem1)==StrToInt(strItem2))
					iCompRes=0;
				else
					iCompRes=-1;
			}
			break; 
    } 
    ////���ݵ�ǰ������ʽ���е��� 
    if(pV->m_fAsc) 
        return iCompRes; 
    else 
        return iCompRes*-1; 
}

void MyListCtrl::OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	//�ݲ�����
	//DATA da={0};
	//da.Ctrl=this;
	////��������ʽ
 //   if( pNMLV->iSubItem == da.m_nSortedCol ) 
 //       da.m_fAsc = !da.m_fAsc; 
 //   else 
 //   { 
 //       da.m_fAsc = TRUE; 
 //       da.m_nSortedCol = pNMLV->iSubItem; 
 //   } 

	//int    i=this->GetItemCount();                //   �����亯���ǹؼ�Ŷ��������
 //   while(i--) this->SetItemData(i,i);   
 //   //���������� 
 //   this->SortItems( MyListCtrl::ListCompare,(DWORD_PTR)&da);
	*pResult = 0;
}

void MyListCtrl::Clear()
{
	this->DeleteAllItems();
	//ɾ���ؼ���ͷ
	/*int cols=this->GetHeaderCtrl().GetItemCount();
	for(int i=cols-1;i>=0;i--)
	{
		this->DeleteColumn(i);
	}
	*/
}

void MyListCtrl::SetStyle(DWORD style)
{
	LONG   lStyle; 
	lStyle=GetWindowLong(this->m_hWnd,GWL_STYLE);//��ȡ��ǰ��������  
	lStyle|=(style);
	SetWindowLong(this->m_hWnd,GWL_STYLE,lStyle);//���ô�������
}


void MyListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//��Ӵ���

	//���ȵõ������λ�� 
	POSITION pos = GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		//û��ѡ�л��ߵ�ǰû������
		return;
	}
	//�õ��кţ�ͨ��POSITIONת�� 
	int nId = (int)GetNextSelectedItem(pos);
	//�õ����е����ݣ�0��ʾ��һ�У�ͬ��1,2,3...��ʾ�ڶ���������...�У� 
	CString str1 = GetItemText(nId, 0);
	CString str2 = GetItemText(nId, 1);

	HWND msgHandle = GetParent()->GetSafeHwnd();
	COPYDATASTRUCT cpd;
	unsigned int data[2] = { 0 };//����,uuid
	data[0] = nId;
	data[1] = GetItemData(nId);
	cpd.dwData = WM_SEL_LIST; //ѡ�е���                                                                                                         //��־�����ַ���
	cpd.cbData = sizeof(data);
	cpd.lpData = data;
	::SendMessage(msgHandle, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cpd);
	*pResult = 0;
}


void MyListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	
	//checkbox״̬
	if ((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(1)) /* old state : unchecked */
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(2)) /* new state : checked */
		)
	{
		TRACE("Item %d is checked\n", pNMLV->iItem);

		HWND msgHandle = GetParent()->GetSafeHwnd();
		COPYDATASTRUCT cpd;
		unsigned int data[3] = { 0 }; //����,uuid,checked/unchecked
		data[0]= pNMLV->iItem;
		data[1] = GetItemData(pNMLV->iItem);
		data[2] = 1;
		cpd.dwData = WM_SEL_CHECK; //ѡ�е���                                                                                                         //��־�����ַ���
		cpd.cbData = sizeof(data);
		cpd.lpData = data;
		::SendMessage(msgHandle, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cpd);
	}
	else if ((pNMLV->uOldState & INDEXTOSTATEIMAGEMASK(2)) /* old state : checked */
		&& (pNMLV->uNewState & INDEXTOSTATEIMAGEMASK(1)) /* new state : unchecked */
		)
	{
		TRACE("Item %d is unchecked\n", pNMLV->iItem);
		HWND msgHandle = GetParent()->GetSafeHwnd();
		COPYDATASTRUCT cpd;
		unsigned int data[3] = { 0 };//����,uuid,checked/unchecked
		data[0] = pNMLV->iItem;
		data[1] = GetItemData(pNMLV->iItem);
		data[2] = 0;
		cpd.dwData = WM_SEL_CHECK; //ѡ�е���                                                                                                         //��־�����ַ���
		cpd.cbData = sizeof(data);
		cpd.lpData = data;
		::SendMessage(msgHandle, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cpd);
	}
	else
	{
		TRACE("Item %d does't change the check-status\n", pNMLV->iItem);
	}
	*pResult = 0;
}

void MyListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1 && nMenu!=0)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		//����̲߳���
		VERIFY(menu.LoadMenu(IDR_MENU_LIST));			//������������1�ж����MENU���ļ�����
		CMenu* popup = menu.GetSubMenu(nMenu);
		ASSERT(popup != NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	*pResult = 0;
}

void MyListCtrl::OnSendMsg()
{
	// TODO:  �ڴ���������������
	if (NULL == pMsgDialog)
	{
		pMsgDialog = new CDialogMsg();
		pMsgDialog->Create(IDD_DIALOG_MSG, this);
	}
	pMsgDialog->ShowWindow(SW_SHOW);

	POSITION m_pstion = GetFirstSelectedItemPosition();
	int m_nIndex = GetNextSelectedItem(m_pstion);
	HWND msgHandle = this->GetParent()->GetSafeHwnd();
	
	CSendMsg mSend;
	mSend.pMsgDialog = pMsgDialog;
	mSend.nIndex = m_nIndex;

	COPYDATASTRUCT cpd;
	unsigned int num = m_nIndex;
	cpd.dwData = WM_SNIFFER_PARENT; //ѡ�е���                                                                                                         //��־�����ַ���
	cpd.cbData = sizeof(mSend);
	cpd.lpData = &mSend;
	::SendMessage(msgHandle, WM_COPYDATA, 0, (LPARAM)&cpd);
}

//���ܲ�����,��ʱ�������е����ݰ�
void MyListCtrl::OnDecryptToSave()
{
	// TODO:  �ڴ���������������

	POSITION m_pstion = GetFirstSelectedItemPosition();
	int m_nIndex = GetNextSelectedItem(m_pstion);
	HWND msgHandle = this->GetParent()->GetSafeHwnd();

	COPYDATASTRUCT cpd;
	unsigned int num = m_nIndex;
	cpd.dwData = WM_DECRYPTSAVE_PARENT; //ѡ�е���    
	cpd.cbData = sizeof(m_nIndex);
	cpd.lpData = &m_nIndex;
	::SendMessage(msgHandle, WM_COPYDATA, 0, (LPARAM)&cpd);
}


void MyListCtrl::OnDelete()
{
	// TODO:  �ڴ���������������

	POSITION m_pstion = GetFirstSelectedItemPosition();
	int m_nIndex = GetNextSelectedItem(m_pstion);
	HWND msgHandle = this->GetParent()->GetSafeHwnd();

	COPYDATASTRUCT cpd;
	unsigned int data[2] = {0}; //����,uuid
	data[0] = m_nIndex;
	data[1] = GetItemData(m_nIndex);
	cpd.dwData = WM_DELETE_ITEM; //ѡ�е���                                                                                                         //��־�����ַ���
	cpd.cbData = sizeof(data);
	cpd.lpData = data;
	::SendMessage(msgHandle, WM_COPYDATA, (WPARAM)m_hWnd, (LPARAM)&cpd);
}
