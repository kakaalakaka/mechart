#include "..\\stdafx.h"
#include "..\\include\\Base\\CWinHost.h"
#include "..\\include\\TextBox\\CDateTimePicker.h"
#include "..\\include\\Layout\\CSplitLayoutDiv.h"
#include "..\\include\\TabControl\\CTabPage.h"
#include "..\\include\\TextBox\\CComboBox.h"
#include "..\\include\\Grid\\CGrid.h"
using namespace MeLib;

SIZE CWinHostMe::GetClientSize()
{
	int cx = 0;
	int cy = 0;
	if (m_native)
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
	}
	SIZE sz = {cx, cy};
	return sz;
}

CWinHostMe::CWinHostMe()
{
	m_allowOperate = true;
	m_allowPartialPaint = true;
	m_hImc = 0;
	m_hWnd = 0;
	m_invokeSerialID = 0;
	m_native = 0;
	m_pInvokeMsgID = 1025;
	m_toolTip = 0;
	::InitializeCriticalSection(&_csLock);
}

CWinHostMe::~CWinHostMe()
{
	if (m_toolTip)
	{
		m_native->RemoveControl(m_toolTip);
		delete m_toolTip;
	}
	m_toolTip = 0;
	m_hImc = 0;
	m_hWnd = 0;
	m_native = 0;
	::DeleteCriticalSection(&_csLock);
}

HWND CWinHostMe::GetHWnd()
{
	return m_hWnd;
}

void CWinHostMe::SetHWnd( HWND hWnd )
{
	m_hWnd = hWnd;
	m_hImc = ImmGetContext(m_hWnd);
	if(m_native){
		m_native->OnResize();
	}
}

CNativeBaseMe* CWinHostMe::GetNative()
{
	return m_native;
}

void CWinHostMe::SetNative( CNativeBaseMe *native )
{
	m_native = native;
}

int CWinHostMe::GetPInvokeMsgID()
{
	return m_pInvokeMsgID;
}

void CWinHostMe::SetPInvokeMsgID( int pInvokeMsgID )
{
	m_pInvokeMsgID = pInvokeMsgID;
}

CControlMe* CWinHostMe::GetToolTip()
{
	return m_toolTip;
}

void CWinHostMe::SetToolTip( CControlMe *toolTip )
{
	m_toolTip = toolTip;
}

void CWinHostMe::ActiveMirror()
{
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		vector<CControlMe*> controls = m_native->GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			CControlMe *control = controls[i];
			if (control->GetNative() != m_native)
			{
				control->SetNative(m_native);
			}
		}
	}
}

bool CWinHostMe::AllowOperate()
{
	return m_allowOperate;
}

bool CWinHostMe::AllowPartialPaint()
{
	return m_allowPartialPaint;
}

void CWinHostMe::BeginInvoke( CControlMe *control, void *args )
{
	Lock();
	m_invokeArgs[m_invokeSerialID] = args;
	m_invokeControls[m_invokeSerialID] = control;
	UnLock();
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		CWinHostMe *host = dynamic_cast<CWinHostMe*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	SendMessage(hWnd, m_pInvokeMsgID, m_invokeSerialID, 0);
	m_invokeSerialID++;
}

void CWinHostMe::Copy( string text )
{
    if (::OpenClipboard(m_hWnd))
    {
		if((int)text.length() > 0)
		{
			::EmptyClipboard();
			size_t cbStr = (text.length() + 1) * sizeof(wchar_t);

			HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, cbStr); 

			if (hMem == NULL) 
			{
				CloseClipboard();
				return; 
			}

			char * lpDest = (char *)GlobalLock(hMem);
			strcpy_s(lpDest, cbStr, text.c_str());

			GlobalUnlock(hMem); 

			UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR))?CF_UNICODETEXT:CF_TEXT;

			if(SetClipboardData(uiFormat, hMem) == NULL)
			{
				CloseClipboard();
				return;
			}
			CloseClipboard();
		}
    }
}

CControlMe* CWinHostMe::CreateInternalControl( CControlMe *parent, const String& clsid )
{
	CCalendarMe *calendar = dynamic_cast<CCalendarMe*>(parent);
	if (calendar)
	{
		if (clsid == L"datetitle")
		{
			return new CDateTitleMe(calendar);
		}
		if (clsid == L"headdiv")
		{
			CHeadDivMe *div = new CHeadDivMe(calendar);
			div->SetWidth(parent->GetWidth());
			div->SetDock(DockStyleMe_Top);
			return div;
		}
		if (clsid == L"lastbutton")
		{
			return new CArrowButtonMe(calendar);
		}
		if (clsid == L"nextbutton")
		{
			CArrowButtonMe *button = new CArrowButtonMe(calendar);
			button->SetToLast(false);
			return button;
		}
	}
	
	if (dynamic_cast<CSplitLayoutDivMe*>(parent) && (clsid == L"splitter"))
	{
		CButtonMe *na = new CButtonMe();
		SIZE sz = {5, 5};
		na->SetSize(sz);
		return na;
	}
	if (dynamic_cast<CScrollBarMe*>(parent))
	{
		if (clsid == L"addbutton")
		{
			CButtonMe *na2 = new CButtonMe();
			SIZE sz = {15, 15};
			na2->SetSize(sz);
			return na2;
		}
		if (clsid == L"backbutton")
		{
			return new CButtonMe();
		}
		if (clsid == L"scrollbutton")
		{
			CButtonMe *na3 = new CButtonMe();
			na3->SetAllowDrag(true);
			return na3;
		}
		if (clsid == L"reducebutton")
		{
			CButtonMe *na4 = new CButtonMe();
			SIZE sz = {15, 15};
			na4->SetSize(sz);
			return na4;
		}
	}
	if (dynamic_cast<CTabPageMe*>(parent) && (clsid == L"headerbutton"))
	{
		CButtonMe *buttonA = new CButtonMe();
		buttonA->SetAllowDrag(true);
		SIZE sz = {100, 20};
		buttonA->SetSize(sz);
		return buttonA;
	}
	CComboBoxMe *comboBoxA = dynamic_cast<CComboBoxMe*>(parent);
	if (comboBoxA)
	{
		if (clsid == L"dropdownbutton")
		{
			CButtonMe *buttonA6 = new CButtonMe();
			buttonA6->SetDisplayOffset(false);
			int width = comboBoxA->GetWidth();
			int height = comboBoxA->GetHeight();
			POINT point = {width - 16, 0};
			buttonA6->SetLocation(point);
			SIZE size2 = {16, height};
			buttonA6->SetSize(size2);
			return buttonA6;
		}
		if (clsid == L"dropdownmenu")
		{
			CComboBoxMenuMe *menu = new CComboBoxMenuMe();
			menu->SetComboBox(comboBoxA);
			menu->SetPopup(true);
			SIZE size3 = {100, 200};
			menu->SetSize(size3);
			return menu;
		}
	}
	CDateTimePickerMe *ra3 = dynamic_cast<CDateTimePickerMe*>(parent);
	if (ra3)
	{
		if (clsid == L"dropdownbutton")
		{
			CButtonMe *buttonA7 = new CButtonMe();
			buttonA7->SetDisplayOffset(false);
			int width = ra3->GetWidth();
			int cy = ra3->GetHeight();
			POINT point2 = {width - 16, 0};
			buttonA7->SetLocation(point2);
			SIZE size4 = {16, cy};
			buttonA7->SetSize(size4);
			return buttonA7;
		}
		if (clsid == L"dropdownmenu")
		{
			CMenuMe *ua = new CMenuMe();
			ua->SetPadding(PADDING(1));
			ua->SetPopup(true);
			SIZE size5 = {200, 200};
			ua->SetSize(size5);
			return ua;
		}
	}
	if (dynamic_cast<CSpinMe*>(parent))
	{
		if (clsid == L"downbutton")
		{
			CButtonMe *na9 = new CButtonMe();
			na9->SetDisplayOffset(false);
			SIZE size6 = {16, 16};
			na9->SetSize(size6);
			return na9;
		}
		if (clsid == L"upbutton")
		{
			CButtonMe *na10 = new CButtonMe();
			na10->SetDisplayOffset(false);
			SIZE size7 = {16, 16};
			na10->SetSize(size7);
			return na10;
		}
	}
	if (dynamic_cast<DivMe*>(parent))
	{
		if (clsid == L"hscrollbar")
		{
			CHScrollBarMe *ra4 = new CHScrollBarMe();
			ra4->SetVisible(false);
			SIZE sz = {15, 15};
			ra4->SetSize(sz);
			return ra4;
		}
		if (clsid == L"vscrollbar")
		{
			CVScrollBarMe *ra5 = new CVScrollBarMe();
			ra5->SetVisible(false);
			SIZE sz = {15, 15};
			ra5->SetSize(sz);
			return ra5;
		}
	}
	if (dynamic_cast<CGridMe*>(parent) && (clsid == L"edittextbox"))
	{
		return new CTextBoxMe();
	}
	return 0;
}

std::string CWinHostMe::GetAppPath()
{
	char exeFullPath[MAX_PATH]; 
	string strPath = "";
	GetModuleFileNameA(0, exeFullPath, MAX_PATH);
	strPath = (string)exeFullPath; 
	int pos = (int)strPath.rfind('\\', strPath.length());
	return strPath.substr(0, pos);
}

CursorsMe CWinHostMe::GetCursor()
{
	if (m_hWnd)
	{
		HCURSOR cursor = ::GetCursor();
		if (!cursor || (cursor == ::LoadCursor(0, IDC_ARROW)))
		{
			return CursorsMe_Arrow;
		}
		if (cursor == ::LoadCursor(0, IDC_APPSTARTING))
		{
			return CursorsMe_AppStarting;
		}
		if (cursor == ::LoadCursor(0, IDC_CROSS))
		{
			return CursorsMe_Cross;
		}
		if (cursor == ::LoadCursor(0, IDC_HAND))
		{
			return CursorsMe_Hand;
		}
		if (cursor == ::LoadCursor(0, IDC_HELP))
		{
			return CursorsMe_Help;
		}
		if (cursor == ::LoadCursor(0, IDC_IBEAM))
		{
			return CursorsMe_IBeam;
		}
		if (cursor == ::LoadCursor(0, IDC_NO))
		{
			return CursorsMe_No;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZEALL))
		{
			return CursorsMe_SizeAll;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENESW))
		{
			return CursorsMe_SizeNESW;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENS))
		{
			return CursorsMe_SizeNS;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZENWSE))
		{
			return CursorsMe_SizeNWSE;
		}
		if (cursor == ::LoadCursor(0, IDC_SIZEWE))
		{
			return CursorsMe_SizeWE;
		}
		if (cursor == ::LoadCursor(0, IDC_UPARROW))
		{
			return CursorsMe_UpArrow;
		}
		if (cursor == ::LoadCursor(0, IDC_WAIT))
		{
			return CursorsMe_WaitCursor;
		}
	}
	return CursorsMe_Arrow;
}

int CWinHostMe::GetIntersectRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return IntersectRect(lpDestRect, lpSrc1Rect, lpSrc2Rect);
}

POINT CWinHostMe::GetMousePoint()
{
	int x = 0;
	int y = 0;
	if (m_hWnd)
	{
		POINT point = {0, 0};
		GetCursorPos(&point);
		ScreenToClient(m_hWnd, &point);
		x = point.x;
		y = point.y;
		if (m_native->AllowScaleSize())
		{
			SIZE clientSize = GetClientSize();
			if (clientSize.cx > 0 && clientSize.cy > 0)
			{
				SIZE scaleSize = m_native->GetScaleSize();
				x = (x * scaleSize.cx) / clientSize.cx;
				y = (y * scaleSize.cy) / clientSize.cy;
			}
		}
	}
	POINT pt = {x, y};
	return pt;
}

SIZE CWinHostMe::GetSize()
{
	if (m_native->AllowScaleSize())
	{
		return m_native->GetScaleSize();
	}
	return GetClientSize();
}

int CWinHostMe::GetUnionRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{
	return UnionRect(lpDestRect, lpSrc1Rect, lpSrc2Rect);
}

void CWinHostMe::Lock()
{
	::EnterCriticalSection(&_csLock);
}

void CWinHostMe::Invalidate()
{
	if (m_hWnd)
	{
		RECT rc;
		SIZE size = GetClientSize();
		rc.left = 0;
		rc.top = 0;
		rc.right = size.cx;
		rc.bottom = size.cy;
		InvalidateRect(m_hWnd, &rc, FALSE);
	}
}

void CWinHostMe::Invalidate( const RECT& rect )
{
	if (m_allowPartialPaint)
	{
		HDC dc = GetDC(m_hWnd);
		OnPaint(dc, rect);
		::ReleaseDC(m_hWnd, dc);
	}
	else
	{
		Invalidate();
	}
}

void CWinHostMe::Invoke( CControlMe *control, void *args )
{
	Lock();
	m_invokeArgs[m_invokeSerialID] = args;
	m_invokeControls[m_invokeSerialID] = control;
	UnLock();
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		CWinHostMe *host = dynamic_cast<CWinHostMe*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	PostMessage(hWnd, m_pInvokeMsgID, m_invokeSerialID, 0);
	m_invokeSerialID++;
}

bool CWinHostMe::IsKeyPress( char key )
{
	int num = GetKeyState(key) & 0x8000;
	return num != 0;
}

void CWinHostMe::OnInvoke( int invokeSerialID )
{
	void *args = 0;
	CControlMe *la = 0;
	Lock();
	if (m_invokeArgs.find(invokeSerialID) != m_invokeArgs.end())
	{
		args = m_invokeArgs[invokeSerialID];
		m_invokeArgs.erase(invokeSerialID);
	}
	if (m_invokeControls.find(invokeSerialID) != m_invokeControls.end())
	{
		la = m_invokeControls[invokeSerialID];
		m_invokeControls.erase(invokeSerialID);
		m_invokeArgs[m_invokeSerialID] = la;
	}
	UnLock();
	if (la != 0)
	{
		la->OnInvoke(args);
	}
}

int CWinHostMe::OnMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	if (m_native)
	{
		if (message == WM_IME_SETCONTEXT && (int)wParam == 1)
		{
			ImmAssociateContext(m_hWnd, m_hImc);
		}
		if (message == m_pInvokeMsgID)
		{
			OnInvoke((int)wParam);
		}
		switch (message)
		{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
			{
				if(m_allowOperate)
				{
					char keyData = (int)wParam;
					if (m_native->OnPreviewsKeyEvent(EVENTID::KEYDOWN, keyData))
					{
						return 1;
					}
					m_native->OnKeyDown(keyData);
				}
				return 0;
			}
		case WM_KEYUP:
		case WM_SYSKEYUP:
			if (m_allowOperate)
			{
				char keyData = (int)wParam;
				m_native->OnKeyUp(keyData);
			}
			break;
		case 5:
			if((int)wParam != 1)
			{
				m_native->OnResize();
			}
			break;

		case WM_CHAR:
			{
				char keyData = (int)wParam;
				if (m_allowOperate && m_native->OnChar(keyData))
				{
					return 1;
				}
				return 0;
			}
		case WM_ERASEBKGND:
			return 1;

		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				BeginPaint(m_hWnd, &ps);
				SIZE displaySize = m_native->GetDisplaySize();
				RECT clipRect = { 0, 0, displaySize.cx, displaySize.cy };
				HDC hdc = ::GetDC(m_hWnd); 
				OnPaint(hdc, clipRect);

				EndPaint(m_hWnd, &ps);
				return 1;
			}
		case WM_MOUSEMOVE:
			if (m_allowOperate)
			{
				m_native->OnMouseMove(MouseButtonsMe_Left, 1, 0);
			}
			break;

		case WM_LBUTTONDOWN:
			if (m_allowOperate)
			{
				ActiveMirror();
				m_native->OnMouseDown(MouseButtonsMe_Left, 1, 0);
			}
			break;

		case WM_LBUTTONUP:
			if (m_allowOperate)
			{
				m_native->OnMouseUp(MouseButtonsMe_Left, 1, 0);
			}
			break;

		case WM_LBUTTONDBLCLK:
			if (m_allowOperate)
			{
				m_native->OnMouseDown(MouseButtonsMe_Left, 2, 0);
				m_native->OnDoubleClick(MouseButtonsMe_Left, 2, 0);
			}
			break;

		case WM_RBUTTONDOWN:
			if (m_allowOperate)
			{
				ActiveMirror();
				m_native->OnMouseDown(MouseButtonsMe_Right, 1, 0);
			}
			break;

		case WM_RBUTTONUP:
			if (m_allowOperate)
			{
				m_native->OnMouseUp(MouseButtonsMe_Right, 1, 0);
			}
			break;

		case WM_RBUTTONDBLCLK:
			if (m_allowOperate)
			{
				m_native->OnMouseDown(MouseButtonsMe_Right, 2, 0);
				m_native->OnDoubleClick(MouseButtonsMe_Right, 2, 0);
			}
			break;

		case WM_MOUSEWHEEL:
			if (m_allowOperate)
			{
				m_native->OnMouseWheel(MouseButtonsMe_None, 0, (int) wParam);
			}
			break;

		case WM_IME_CHAR:
			if ((m_allowOperate && (int)wParam == 1) && m_native->GetFocusedControl())
			{
				int dwBufLen = ImmGetCompositionString(m_hImc, 8, NULL, 0) + 2;
				char *buffer = new char[dwBufLen];
				memset(buffer, 0, dwBufLen);
				ImmGetCompositionString(m_hImc, GCS_RESULTSTR, buffer, dwBufLen);
			}
			break;

		case WM_TIMER:
			if (m_hWnd && hWnd == m_hWnd)
			{
				m_native->OnTimer((int) wParam);
			}
			break;
		}
	}
	return 0;
}

void CWinHostMe::OnPaint( HDC hDC, const RECT& clipRect )
{
	Lock();
	if (m_hWnd != 0)
	{
		SIZE displaySize = m_native->GetDisplaySize();
		double scaleFactorX = 1.0;
		double scaleFactorY = 1.0;
		SIZE clientSize = GetClientSize();
		if (m_native->AllowScaleSize() && clientSize.cx > 0 && clientSize.cy > 0)
		{
			SIZE scaleSize = m_native->GetScaleSize();
			scaleFactorX = ((double) clientSize.cx) / ((double) scaleSize.cx);
			scaleFactorY = ((double) clientSize.cy) / ((double) scaleSize.cy);
		}
		m_native->GetPaint()->SetScaleFactor(scaleFactorX, scaleFactorY);
		RECT rc = {0, 0, clientSize.cx, clientSize.cy};
		m_native->GetPaint()->BeginPaint(hDC, rc, clipRect);
		m_native->OnPaint(clipRect);
		m_native->GetPaint()->EndPaint();
	}
	UnLock();
}

string CWinHostMe::Paste()
{
	string text = "";
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
	if(::OpenClipboard(m_hWnd) && ::IsClipboardFormatAvailable(uiFormat))
    {
        HGLOBAL hMem = GetClipboardData(uiFormat); 
        if (hMem != NULL) 
        { 
            LPCTSTR lpStr = (LPCTSTR)GlobalLock(hMem); 
            if (lpStr != NULL) 
            { 
				CStrMe::wstringTostring(text, lpStr);
            } 
            GlobalUnlock(hMem);
		} 
		CloseClipboard();
    }
	return text;
}

void CWinHostMe::SetAllowOperate( bool allowOperate )
{
	m_allowOperate = allowOperate;
}

void CWinHostMe::SetAllowPartialPaint( bool allowPartialPaint )
{
	m_allowPartialPaint = allowPartialPaint;
}

void CWinHostMe::SetCursor( CursorsMe cursor )
{
	if (m_hWnd != 0)
	{
		switch (cursor)
		{
		case CursorsMe_Arrow:
			::SetCursor(::LoadCursorW(NULL, IDC_ARROW));
			return;

		case CursorsMe_AppStarting:
			::SetCursor(::LoadCursorW(NULL, IDC_APPSTARTING));
			return;

		case CursorsMe_Cross:
			::SetCursor(::LoadCursorW(NULL, IDC_CROSS));
			return;

		case CursorsMe_Hand:
			::SetCursor(::LoadCursorW(NULL, IDC_HAND));
			return;

		case CursorsMe_Help:
			::SetCursor(::LoadCursorW(NULL, IDC_HELP));
			return;

		case CursorsMe_IBeam:
			::SetCursor(::LoadCursorW(NULL, IDC_IBEAM));
			return;

		case CursorsMe_No:
			::SetCursor(::LoadCursorW(NULL, IDC_NO));
			return;

		case CursorsMe_SizeAll:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZEALL));
			return;

		case CursorsMe_SizeNESW:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENESW));
			return;

		case CursorsMe_SizeNS:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENS));
			return;

		case CursorsMe_SizeNWSE:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZENWSE));
			return;

		case CursorsMe_SizeWE:
			::SetCursor(::LoadCursorW(NULL, IDC_SIZEWE));
			return;

		case CursorsMe_UpArrow:
			::SetCursor(::LoadCursorW(NULL, IDC_UPARROW));
			return;

		case CursorsMe_WaitCursor:
			::SetCursor(::LoadCursorW(NULL, IDC_WAIT));
			break;
		}
	}
}

void CWinHostMe::ShowToolTip(void *sender, const wstring& text, const POINT& mp)
{
	if (m_toolTip)
	{
		m_toolTip->SetLocation(mp);
		m_toolTip->SetNative(m_native);
		m_toolTip->SetLocation(mp);
		m_toolTip->SetText(text);
		m_toolTip->Show();
	}
}

void CWinHostMe::StartTimer( int timerID, int interval )
{
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		CWinHostMe *host = dynamic_cast<CWinHostMe*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	SetTimer(hWnd, timerID, interval, 0);
}

void CWinHostMe::StopTimer( int timerID )
{
	HWND hWnd = m_hWnd;
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		CWinHostMe *host = dynamic_cast<CWinHostMe*>(m_native->GetMirrorHost()->GetHost());
		hWnd = host->GetHWnd();
	}
	KillTimer(hWnd, timerID);
}

void CWinHostMe::UnLock()
{
	::LeaveCriticalSection(&_csLock);
}