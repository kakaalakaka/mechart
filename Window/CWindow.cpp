#include "..\\stdafx.h"
#include "..\\include\\Window\\CWindow.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace MeLib;

void CWindowMe::CallWindowClosingEvents( int eventID, bool *cancel )
{
	if (m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			WindowClosingEvent event2 = WindowClosingEvent(list->at(i));
			if (event2)
			{
				event2(this, cancel, &eventID);
			}
		}
	}
}

CursorsMe CWindowMe::GetResizeCursor( int state )
{
	switch (state)
	{
	case 0:
		return CursorsMe_SizeNWSE;

	case 1:
		return CursorsMe_SizeNESW;

	case 2:
		return CursorsMe_SizeNESW;

	case 3:
		return CursorsMe_SizeNWSE;

	case 4:
		return CursorsMe_SizeWE;

	case 5:
		return CursorsMe_SizeNS;

	case 6:
		return CursorsMe_SizeWE;

	case 7:
		return CursorsMe_SizeNS;
	}
	return CursorsMe_Arrow;
}

vector<RECT> CWindowMe::GetResizePoints()
{
	int width = GetWidth();
	int height = GetHeight();
	vector<RECT> vec;
	RECT rc1 = {0, 0, m_borderWidth * 2, m_borderWidth * 2};
	RECT rc2 = {0, height - (m_borderWidth * 2), m_borderWidth * 2, height};
	RECT rc3 = {width - (m_borderWidth * 2), 0, width, m_borderWidth * 2};
	RECT rc4 = {width - (m_borderWidth * 2), height - (m_borderWidth * 2), width, height};
	RECT rc5 = {0, 0, m_borderWidth, height};
	RECT rc6 = {0, 0, width, m_borderWidth};
	RECT rc7 = {width - m_borderWidth, 0, width, height};
	RECT rc8 = {0, height - m_borderWidth, width, height };
	vec.push_back(rc1);
	vec.push_back(rc2);
	vec.push_back(rc3);
	vec.push_back(rc4);
	vec.push_back(rc5);
	vec.push_back(rc6);
	vec.push_back(rc7);
	vec.push_back(rc8);
	return vec;
}

int CWindowMe::GetResizeState()
{
	POINT mousePoint = GetMousePoint();
	vector<RECT> resizePoints = GetResizePoints();
	int length = (int)resizePoints.size();
	for (int i = 0; i < length; i++)
	{
		RECT rect = resizePoints[i];
		if (mousePoint.x >= rect.left && mousePoint.x <= rect.right && mousePoint.y >= rect.top && mousePoint.y <= rect.bottom)
		{
			return i;
		}
	}
	return -1;
}

CWindowMe::CWindowMe()
{
	m_borderWidth = 2;
	m_canResize = false;
	m_captionHeight = 20;
	m_frame = 0;
	m_isDialog = false;
	m_resizePoint = -1;
	m_shadowColor = COLOR::ARGB(25, 255, 255, 255);
	m_shadowSize = 10;
	m_startMousePoint.x = 0;
	m_startMousePoint.y = 0;
	m_startRect.bottom = 0;
	m_startRect.left = 0;
	m_startRect.right = 0;
	m_startRect.top = 0;
	SetAllowDrag(true);
	SetWindow(true);
	SetVisible(false);
}

CWindowMe::~CWindowMe()
{
	if (m_frame)
	{
		m_frame->RemoveControl(this);
		GetNative()->RemoveControl(m_frame);
		delete m_frame;
	}
	m_frame = 0;
}

int CWindowMe::GetBorderWidth()
{
	return m_borderWidth;
}

void CWindowMe::SetBorderWidth( int borderWidth )
{
	m_borderWidth = borderWidth;
}

int CWindowMe::GetCaptionHeight()
{
	return m_captionHeight;
}

void CWindowMe::SetCaptionHeight( int captionHeight )
{
	m_captionHeight = captionHeight;
}

bool CWindowMe::CanResize()
{
	return m_canResize;
}

void CWindowMe::SetCanResize( bool canResize )
{
	m_canResize = canResize;
}

CWindowFrameMe* CWindowMe::GetFrame()
{
	return m_frame;
}

void CWindowMe::SetFrame( CWindowFrameMe *frame )
{
	m_frame = frame;
}

bool CWindowMe::IsDialog()
{
	return m_isDialog;
}

_int64 CWindowMe::GetShadowColor()
{
	return m_shadowColor;
}

void CWindowMe::SetShadowColor( _int64 shadowColor )
{
	m_shadowColor = shadowColor;
}

int CWindowMe::GetShadowSize()
{
	return m_shadowSize;
}

void CWindowMe::SetShadowSize( int shadowSize )
{
	m_shadowSize = shadowSize;
}

void CWindowMe::BringToFront()
{
	CControlMe::BringToFront();
	if (m_frame)
	{
		m_frame->BringToFront();
	}
}

void CWindowMe::Close()
{
	bool cancel = false;
	OnWindowClosing(&cancel);
	if (!cancel)
	{
		if (m_frame)
		{
			m_frame->RemoveControl(this);
			GetNative()->RemoveControl(m_frame);
			delete m_frame;
			m_frame = 0;
			SetParent(0);
		}
		else
		{
			GetNative()->RemoveControl(this);
		}
		OnWindowClosed();
	}
}

String CWindowMe::GetControlType()
{
	return L"Window";
}

RECT CWindowMe::GetDynamicPaintRect()
{
	SIZE oldSize = m_oldSize;
	if (oldSize.cx == 0 && oldSize.cy == 0)
	{
		oldSize = GetSize();
	}
	RECT rect;
	rect.left = m_oldLocation.x;
	rect.top = m_oldLocation.y;
	rect.right = m_oldLocation.x + oldSize.cx;
	rect.bottom = m_oldLocation.y + oldSize.cy;
	RECT rect2;
	rect2.left = m_location.x;
	rect2.top = m_location.y;
	rect2.right = m_location.x + GetWidth();
	rect2.bottom = m_location.y + GetHeight();
	RECT rc;
	rc.left = min(rect.left, rect2.left) - m_shadowSize - 10;
	rc.top = min(rect.top, rect2.top) - m_shadowSize - 10;
	rc.right = (max(rect.right, rect2.right) + m_shadowSize) + 10;
	rc.bottom = (max(rect.bottom, rect2.bottom) + m_shadowSize) + 10;
	return rc;
}

vector<wstring> CWindowMe::GetEventNames()
{
	vector<wstring> events = CControlMe::GetEventNames();
	events.push_back(L"WindowClosed");
	events.push_back(L"WindowClosing");
	return events;
}

void CWindowMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"borderwidth")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetBorderWidth());
	}
	else if (name == L"canresize")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(CanResize());
	}
	else if (name == L"captionheight")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetCaptionHeight());
	}
	else if (name == L"shadowcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetShadowColor());
	}
	else if (name == L"shadowsize")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetShadowSize());
	}
	else
	{
		CControlMe::GetProperty(name, value, type);
	}
}

vector<String> CWindowMe::GetPropertyNames()
{
	vector<wstring> propertyNames = CControlMe::GetEventNames();
	propertyNames.push_back(L"BorderWidth");
	propertyNames.push_back(L"CanResize");
	propertyNames.push_back(L"CaptionHeight");
	propertyNames.push_back(L"ShadowColor");
	propertyNames.push_back(L"ShadowSize");
	return propertyNames;
}

bool CWindowMe::OnDragBegin()
{
	POINT mousePoint = GetMousePoint();
	int width = GetWidth();
	int height = GetHeight();
	if (mousePoint.y > m_captionHeight)
	{
		return false;
	}
	if (m_resizePoint != -1)
	{
		return false;
	}
	return CControlMe::OnDragBegin();
}

void CWindowMe::OnDragReady( POINT *startOffset )
{
	startOffset->x = 0;
	startOffset->y = 0;
}

void CWindowMe::OnMouseDown( POINT mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseDown(mp, button, clicks, delta);
	if (button == MouseButtonsMe_Left && clicks == 1 && m_canResize)
	{
		m_resizePoint = GetResizeState();
		SetCursor(GetResizeCursor(m_resizePoint));
		m_startMousePoint = GetNative()->GetMousePoint();
		m_startRect = GetBounds();
	}
	Invalidate();
}

void CWindowMe::OnMouseMove( POINT mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseMove(mp, button, clicks, delta);
	if (m_canResize)
	{
		POINT mousePoint = GetNative()->GetMousePoint();
		if (m_resizePoint != -1)
		{
			int left = m_startRect.left;
			int top = m_startRect.top;
			int right = m_startRect.right;
			int bottom = m_startRect.bottom;
			CMathLibMe::M137(m_resizePoint, &left, &top, &right, &bottom, &mousePoint, &m_startMousePoint);
			RECT rect = {left, top, right, bottom};
			SetBounds(rect);
			GetNative()->Invalidate();
		}
		else
		{
			SetCursor(GetResizeCursor(GetResizeState()));
		}
	}
}

void CWindowMe::OnMouseUp( POINT mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseUp(mp, button, clicks, delta);
	m_resizePoint = -1;
	Invalidate();
}

void CWindowMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	String text = GetText();
	if (!text.empty())
	{
		int width = GetWidth();
		FONT *font = GetFont();
		SIZE size = paint->TextSize(text.c_str(), font);
		POINT point = {0, 0};
		point.x = 5;
		point.y = (m_captionHeight - size.cy) / 2;
		RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}

void CWindowMe::OnVisibleChanged()
{
	CControlMe::OnVisibleChanged();
	CNativeBaseMe *native = GetNative();
	if (native)
	{
		if (IsVisible())
		{
			if (m_frame == 0)
			{
				m_frame = new CWindowFrameMe();
			}
			native->RemoveControl(this);
			native->AddControl(m_frame);
			m_frame->SetSize(native->GetDisplaySize());
			if (!m_frame->ContainsControl(this))
			{
				m_frame->AddControl(this);
			}
		}
		else if (m_frame != 0)
		{
			m_frame->RemoveControl(this);
			native->RemoveControl(m_frame);
		}
	}
}

void CWindowMe::OnWindowClosing( bool *cancel )
{
	CallWindowClosingEvents(EVENTID::WINDOWCLOSING, cancel);
}

void CWindowMe::OnWindowClosed()
{
	CallEvents(EVENTID::WINDOWCLOSED);
}

void CWindowMe::SendToBack()
{
	SendToBack();
	if (m_frame)
	{
		m_frame->SendToBack();
	}
}

void CWindowMe::SetProperty( const String& name, const String& value )
{
	if (name == L"borderwidth")
	{
		SetBorderWidth(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"canresize")
	{
		SetCanResize(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"captionheight")
	{
		SetCaptionHeight(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"shadowcolor")
	{
		SetShadowColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"shadowsize")
	{
		SetShadowSize(CStrMe::ConvertStrToInt(value));
	}
	else
	{
		CControlMe::SetProperty(name, value);
	}
}

void CWindowMe::ShowDialog()
{
	m_isDialog = true;
	Show();
}