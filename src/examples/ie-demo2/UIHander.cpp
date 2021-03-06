#include "StdAfx.h"
#include "UIHander.h"

#include "MainDlg.h"

#include "DuiWebBrowser.h"

CUIHander::CUIHander(CMainDlg * pMainDlg) : m_pMainDlg(pMainDlg)
{
}

CUIHander::~CUIHander(void)
{
}

LRESULT CUIHander::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	SetMsgHandled(FALSE); 
    return 0; 
}

void CUIHander::OnGoClick()
{
	CDuiWebBrowser * pBrowser = m_pMainDlg->FindChildByName2<CDuiWebBrowser *>("ctrl_ie");
	CDuiEdit * pEdit = m_pMainDlg->FindChildByName2<CDuiEdit *>("edit_url");
	CDuiComPtr<IWebBrowser2> pIE=pBrowser->GetIEObject();
	if(pIE)
	{
		TCHAR szBuf[1024];
		pEdit->GetWindowText(szBuf,1024);
		CDuiStringW strUrl=DUI_CT2W(szBuf);
		HRESULT hr = pIE->Navigate(bstr_t(strUrl), NULL,NULL,NULL,NULL);
	}	
}

