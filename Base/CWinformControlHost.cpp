#include "..\\stdafx.h"
#include "..\\include\\Base\\CWinformControlHost.h"
using namespace MeLib;

SIZE WinformControlHost::GetClientSize()
{
	int cx = 0;
	int cy = 0;
	if (m_hWnd)
	{
		RECT rc;
		::GetClientRect(m_hWnd, &rc);
		cx = rc.right - rc.left;
		cy = rc.top - rc.bottom;
	}
	SIZE sz = {cx, cy};
	return sz;
}

WinformControlHost::WinformControlHost()
{
	::InitializeCriticalSection(&_csLock);
	m_allowOperate = true;
	m_allowPartialPaint = true;
	m_invokeSerialID = 0;
	m_native = 0;
	m_pInvokeMsgID = 0x401;
}

WinformControlHost::~WinformControlHost()
{
	::DeleteCriticalSection(&_csLock);
}

HWND WinformControlHost::GetHWnd()
{
	return m_hWnd;
}

void WinformControlHost::SetHWnd( HWND hWnd )
{
	m_hWnd = hWnd;
}

CNativeBaseMe* WinformControlHost::GetNative()
{
	return m_native;
}

void WinformControlHost::SetNative(CNativeBaseMe *native)
{
	m_native = native;
}

int WinformControlHost::GetPInvokeMsgID()
{
	return m_pInvokeMsgID;
}

void WinformControlHost::SetPInvokeMsgID( int pInvokeMsgID )
{
	m_pInvokeMsgID = pInvokeMsgID;
}

void WinformControlHost::ActiveMirror()
{
	if (m_native->GetMirrorMode() != MirrorMode_None)
	{
		vector<CControlMe*> controls = m_native->GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			CControlMe *la = controls.at(i);
			if (la->GetNative() != m_native)
			{
				la->SetNative(m_native);
			}
		}
	}
}

bool WinformControlHost::AllowOperate()
{
	return m_allowOperate;
}

bool WinformControlHost::AllowPartialPaint()
{
	return m_allowPartialPaint;
}

void WinformControlHost::BeginInvoke( CControlMe *control, void *args )
{

}

void WinformControlHost::Copy( string text )
{

}

CControlMe* WinformControlHost::CreateInternalControl( CControlMe *parent, const String& clsid )
{

	return 0;
}

std::string WinformControlHost::GetAppPath()
{
	return "";
}

CursorsMe WinformControlHost::GetCursor()
{
	CursorsMe cursorsA = CursorsMe_No;
	return cursorsA;
}

int WinformControlHost::GetIntersectRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{

	return 0;
}

POINT WinformControlHost::GetMousePoint()
{
	POINT point = {0, 0};
	return point;
}

SIZE WinformControlHost::GetSize()
{

	SIZE size = {0, 0};
	return size;
}

int WinformControlHost::GetUnionRect( LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect )
{

	return 0;
}

void WinformControlHost::Lock()
{

}

void WinformControlHost::Invalidate()
{

}

void WinformControlHost::Invalidate( const RECT& rect )
{

}

void WinformControlHost::Invoke( CControlMe *control, void *args )
{

}

bool WinformControlHost::IsKeyPress( char key )
{

	return false;
}

void WinformControlHost::OnInvoke( int invokeSerialID )
{

}

int WinformControlHost::OnMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{

	return  0;
}

void WinformControlHost::OnPaint( HDC hDC, const RECT& rect )
{

}

string WinformControlHost::Paste()
{
	return "";
}

void WinformControlHost::SetAllowOperate( bool allowOperate )
{

}

void WinformControlHost::SetAllowPartialPaint( bool allowPartialPaint )
{

}

void WinformControlHost::SetCursor( CursorsMe cursor )
{

}

void WinformControlHost::StartTimer( int timerID, int interval )
{

}

void WinformControlHost::StopTimer( int timerID )
{

}

void WinformControlHost::UnLock()
{

}
