#include "duistd.h"
#include "DuiDropDown.h"

namespace DuiEngine
{

	CDuiDropDownWnd::CDuiDropDownWnd(IDuiDropDownOwner* pOwner)
		:m_pOwner(pOwner)
	{
		MsgFilterRegister(m_pOwner->GetDropDownOwner()->GetContainer()->GetHostHwnd());
	}

	CDuiDropDownWnd::~CDuiDropDownWnd()
	{
		MsgFilterUnregister(m_pOwner->GetDropDownOwner()->GetContainer()->GetHostHwnd());
	}

	void CDuiDropDownWnd::OnFinalMessage(HWND hWnd)
	{
		__super::OnFinalMessage(hWnd);
		delete this;
	}

	void CDuiDropDownWnd::OnKillFocus( HWND wndFocus )
	{
		if(wndFocus != m_hWnd)
		{
			EndDropDown();
		}
	}

	BOOL CDuiDropDownWnd::Create(LPCRECT lpRect ,LPVOID lParam,DWORD dwStyle,DWORD dwExStyle)
	{
		HWND hWnd=CSimpleWnd::Create(NULL,dwStyle,dwExStyle,lpRect->left,lpRect->top,lpRect->right-lpRect->left,lpRect->bottom-lpRect->top,0,0);
		if(!hWnd) return FALSE;
		m_pOwner->OnDropDown(this);
		return TRUE;
	}

	void CDuiDropDownWnd::OnLButtonDown( UINT nFlags, CPoint point )
	{
		CRect rcWnd;
		GetWindowRect(&rcWnd);
		ClientToScreen(&point);
		if(!rcWnd.PtInRect(point))
		{
			EndDropDown();
		}else
		{
			SetMsgHandled(FALSE);
		}
	}

	void CDuiDropDownWnd::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
	{
		if(nChar==VK_ESCAPE) EndDropDown();
		else SetMsgHandled(FALSE);
	}

	void CDuiDropDownWnd::EndDropDown()
	{
		DestroyWindow();
	}

	void CDuiDropDownWnd::OnDestroy()
	{
		m_pOwner->OnCloseUp(this);
		SetMsgHandled(FALSE);
	}

	BOOL CDuiDropDownWnd::PreTranslateMessage( MSG* pMsg )
	{
		if(!(pMsg->message>=WM_KEYFIRST && pMsg->message<=WM_KEYLAST)) return FALSE;
		if(!_PreTranslateMessage(pMsg))
		{
			SendMessage(pMsg->message,pMsg->wParam,pMsg->lParam);
		}
		return TRUE;
	}
}//end of namespace DuiEngine