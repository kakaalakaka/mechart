#include "..\\stdafx.h"
#include "..\\include\\Layout\\Div.h"
#include "..\\include\\Grid\\CGridColumn.h"
using namespace MeLib;

void DivMe::ScrollButtonKeyDown( void *sender, char key, void *pInvoke )
{
	DivMe *divA = (DivMe *)pInvoke;
	if(divA)
	{
		divA->OnKeyDown(key);
	}
}

void DivMe::ScrollButtonMouseWheel( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	DivMe *divA = (DivMe *)pInvoke;
	if(divA)
	{
		divA->OnMouseWheel(mp, button, clicks, delta);
	}
}

DivMe::DivMe()
{
	m_allowDragScroll = false;
	m_hScrollBar = 0;
	m_isDragScrolling = false;
	m_isDragScrolling2 = false;
	m_readyToDragScroll = false;
	m_scrollButtonKeyDownEvent = &ScrollButtonKeyDown;
	m_scrollButtonMouseWheelEvent = &ScrollButtonMouseWheel;
	m_showHScrollBar = false;
	m_showVScrollBar = false;
	m_startMovePoint.x = 0;
	m_startMovePoint.y = 0;
	m_startMovePosX = 0;
	m_startMovePosY = 0;
	m_startMoveTime = 0;
	m_vScrollBar = 0;
	SIZE sz = {200, 200};
	SetSize(sz);
}

DivMe::~DivMe()
{
	m_hScrollBar = 0;
	m_scrollButtonKeyDownEvent = 0;
	m_scrollButtonMouseWheelEvent = 0;
	m_vScrollBar = 0;
}

bool DivMe::AllowDragScroll()
{
	return m_allowDragScroll;
}

void DivMe::SetAllowDragScroll( bool allowDragScroll )
{
	m_allowDragScroll = allowDragScroll;
}

CHScrollBarMe* DivMe::GetHScrollBar()
{
	CNativeBaseMe* base = GetNative();
	if (!base || !m_showHScrollBar)
	{
		return 0;
	}
	if (!m_hScrollBar)
	{
		CControlHostMe *host = base->GetHost();
		m_hScrollBar = (CHScrollBarMe *)host->CreateInternalControl(this, L"hscrollbar");
		AddControl(m_hScrollBar);
		m_hScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_hScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_hScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
	}
	return m_hScrollBar;
}

bool DivMe::ShowHScrollBar()
{
	return m_showHScrollBar;
}

void DivMe::SetShowHScrollBar( bool showHScrollBar )
{
	m_showHScrollBar = showHScrollBar;
}

bool DivMe::IsDragScrolling()
{
	return m_isDragScrolling;
}

bool DivMe::ShowVScrollBar()
{
	return m_showVScrollBar;
}

void DivMe::SetShowVScrollBar( bool showVScrollBar )
{
	m_showVScrollBar = showVScrollBar;
}

CVScrollBarMe* DivMe::GetVScrollBar()
{
	if (!GetNative() || !m_showVScrollBar)
	{
		return 0;
	}
	if (!m_vScrollBar)
	{
		CControlHostMe *host = GetNative()->GetHost();
		m_vScrollBar = (CVScrollBarMe *)host->CreateInternalControl(this, L"vscrollbar");
		AddControl(m_vScrollBar);
		m_vScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetAddButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetBackButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetReduceButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		m_vScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonKeyDownEvent, EVENTID::KEYDOWN, this);
		m_vScrollBar->GetScrollButton()->RegisterEvent(m_scrollButtonMouseWheelEvent, EVENTID::MOUSEWHEEL, this);
	}
	return m_vScrollBar;
}

int DivMe::GetContentHeight()
{
	CHScrollBarMe *hScrollBar = GetHScrollBar();
	CVScrollBarMe *vScrollBar = GetVScrollBar();
	int hmax = 0;
	vector<CControlMe*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *control = controls[i];
		if ((control->IsVisible() && (control != hScrollBar)) && (control != vScrollBar))
		{
			int bottom = control->GetBottom();
			if (bottom > hmax)
			{
				hmax = bottom;
			}
		}
	}
	return hmax;
}

int DivMe::GetContentWidth()
{
	CHScrollBarMe *hScrollBar = GetHScrollBar();
	CVScrollBarMe *vScrollBar = GetVScrollBar();
	int wmax = 0;
	vector<CControlMe*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *control = controls[i];
		if ((control->IsVisible() && (control != hScrollBar)) && (control != vScrollBar))
		{
			int right = control->GetRight();
			if (right > wmax)
			{
				wmax = right;
			}
		}
	}
	return wmax;
}

String DivMe::GetControlType()
{
	return L"Div";
}

POINT DivMe::GetDisplayOffset()
{
	POINT point = {0, 0};
	if (IsVisible())
	{
		point.x = m_hScrollBar && m_hScrollBar->IsVisible() ? m_hScrollBar->GetPos() : 0;
		point.y = m_vScrollBar && m_vScrollBar->IsVisible() ? m_vScrollBar->GetPos() : 0;
	}
	return point;
}

void DivMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"allowdragscroll")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowDragScroll());
	}
	else if (name == L"showhscrollbar")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(ShowHScrollBar());
	}
	else if (name == L"showvscrollbar")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(ShowVScrollBar());
	}
	else
	{
		CControlMe::GetProperty(name, value, type);
	}
}

vector<String> DivMe::GetPropertyNames()
{
	vector<String> propertyNames = CControlMe::GetPropertyNames();
	propertyNames.push_back(L"AllowDragScroll");
	propertyNames.push_back(L"ShowHScrollBar");
	propertyNames.push_back(L"ShowVScrollBar");
	return propertyNames;
}

void DivMe::LineDown()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->LineAdd();
	}
}

void DivMe::LineLeft()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->LineReduce();
	}
}

void DivMe::LineRight()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->LineAdd();
	}
}

void DivMe::LineUp()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->LineReduce();
	}
}

void DivMe::OnDragReady( POINT *startOffset )
{
	startOffset->x = 0;
	startOffset->y = 0;
}

void DivMe::OnDragScrollEnd()
{
	m_allowDragScroll = false;
	if (m_readyToDragScroll)
	{
		DWORD now = GetTickCount();
		POINT mousePoint = GetNative()->GetMousePoint();
		if (m_hScrollBar && m_hScrollBar->IsVisible())
		{
			m_hScrollBar->OnAddSpeedScrollStart(m_startMoveTime, now, m_startMovePoint.x, mousePoint.x);
		}
		if (m_vScrollBar && m_vScrollBar->IsVisible())
		{
			m_vScrollBar->OnAddSpeedScrollStart(m_startMoveTime, now, m_startMovePoint.y, mousePoint.y);
		}
		m_readyToDragScroll = false;
		Invalidate();
	}
}

void DivMe::OnDragScrolling()
{
	int width = GetWidth();
	int height = GetHeight();
	if (m_allowDragScroll && m_readyToDragScroll)
	{
		if (!OnDragScrollPermit())
		{
			m_readyToDragScroll = false;
		}
		else
		{
			bool paint = false;
			POINT newPoint = GetNative()->GetMousePoint();
			if (m_hScrollBar && m_hScrollBar->IsVisible())
			{
				if (abs(m_startMovePoint.x - newPoint.x) > width / 10) {
					m_isDragScrolling2 = true;
				}
				int newPos = m_startMovePosX + m_startMovePoint.x - newPoint.x;
				if (newPos != m_hScrollBar->GetPos())
				{
					m_hScrollBar->SetPos(newPos);
					m_hScrollBar->Update();
					paint = true;
				}
			}
			if (m_vScrollBar && m_vScrollBar->IsVisible())
			{
				if (abs(m_startMovePoint.y - newPoint.y) > height / 10) {
					m_isDragScrolling2 = true;
				}
				int vPos = m_startMovePosY + m_startMovePoint.y - newPoint.y;
				if (vPos != m_vScrollBar->GetPos())
				{
					m_vScrollBar->SetPos(vPos);
					m_vScrollBar->Update();
					paint = true;
				}
			}
			if (paint)
			{
				m_isDragScrolling = true;
				Invalidate();
			}
		}
	}
}

bool DivMe::OnDragScrollPermit()
{
	CControlMe *focusedControl = GetNative()->GetFocusedControl();
	if (focusedControl)
	{
		if (focusedControl->IsDragging())
		{
			return false;
		}
		if (dynamic_cast<CGridColumnMe*>(focusedControl))
		{
			return false;
		}
		if (focusedControl->GetParent() && dynamic_cast<CScrollBarMe*>(focusedControl->GetParent()))
		{
			return false;
		}
	}
	return true;
}

void DivMe::OnDragScrollStart()
{
	m_isDragScrolling = false;
	m_isDragScrolling2 = false;
	CControlMe *focusedControl = GetNative()->GetFocusedControl();
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		if((focusedControl == m_hScrollBar->GetAddButton() && 
			m_hScrollBar->GetAddButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetBackButton() && 
			m_hScrollBar->GetBackButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetReduceButton() && 
			m_hScrollBar->GetReduceButton()->IsVisible())
			|| (focusedControl == m_hScrollBar->GetScrollButton() && 
			m_hScrollBar->GetScrollButton()->IsVisible()))
		{
			m_hScrollBar->SetAddSpeed(0);
		}
	}
	else if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		if((focusedControl == m_vScrollBar->GetAddButton() && 
			m_hScrollBar->GetAddButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetBackButton() && 
			m_vScrollBar->GetBackButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetReduceButton() && 
			m_hScrollBar->GetReduceButton()->IsVisible())
			|| (focusedControl == m_vScrollBar->GetScrollButton() && 
			m_vScrollBar->GetScrollButton()->IsVisible()))
		{
			m_hScrollBar->SetAddSpeed(0);
		}
	}
	else if (m_allowDragScroll)
	{
		if (m_hScrollBar && m_hScrollBar->IsVisible())
		{
			m_startMovePosX = m_hScrollBar->GetPos();
			m_hScrollBar->SetAddSpeed(0);
			m_readyToDragScroll = true;
		}
		if (m_vScrollBar && m_vScrollBar->IsVisible())
		{
			m_startMovePosY = m_vScrollBar->GetPos();
			m_vScrollBar->SetAddSpeed(0);
			m_readyToDragScroll = true;
		}
		if (m_readyToDragScroll)
		{
			m_startMovePoint = GetNative()->GetMousePoint();
			m_startMoveTime =  GetTickCount();
		}
	}
}

void DivMe::OnKeyDown( char key )
{
	CControlMe::OnKeyDown(key);
	CControlHostMe *host = GetNative()->GetHost();
	if ((!host->IsKeyPress(0x10) && !host->IsKeyPress(0x11)) && !host->IsKeyPress(0x12))
	{
		if (key == '&')
		{
			LineUp();
		}
		else if (key == '(')
		{
			LineDown();
		}
		Invalidate();
	}
}

void DivMe::OnMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseDown(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrollStart();
	}
}

void DivMe::OnMouseMove( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseMove(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrolling();
	}
}

void DivMe::OnMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseUp(mp, button, clicks, delta);
	if (!m_allowPreviewsEvent)
	{
		OnDragScrollEnd();
	}
}

void DivMe::OnMouseWheel( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseWheel(mp, button, clicks, delta);
	if (delta > 0)
	{
		LineUp();
		Invalidate();
	}
	else if (delta < 0)
	{
		LineDown();
		Invalidate();
	}
}

bool DivMe::OnPreviewsMouseEvent( int eventID, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	if (m_allowPreviewsEvent)
	{
		if (eventID == EVENTID::MOUSEDOWN)
		{
			OnDragScrollStart();
		}
		else if (eventID == EVENTID::MOUSEMOVE)
		{
			OnDragScrolling();
		}
		else if (eventID == EVENTID::MOUSEUP)
		{
			bool isDragScrolling = m_isDragScrolling;
			OnDragScrollEnd();
			if(isDragScrolling)
			{
				if(!m_isDragScrolling2)
				{
					return false;
				}
			}
		}
	}
	return false;
}

void DivMe::PageDown()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->PageAdd();
	}
}

void DivMe::PageLeft()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->PageReduce();
	}
}

void DivMe::PageRight()
{
	if (m_hScrollBar && m_hScrollBar->IsVisible())
	{
		m_hScrollBar->PageAdd();
	}
}

void DivMe::PageUp()
{
	if (m_vScrollBar && m_vScrollBar->IsVisible())
	{
		m_vScrollBar->PageReduce();
	}
}

void DivMe::SetProperty( const String& name, const String& value )
{
	if (name == L"allowdragscroll")
	{
		SetAllowDragScroll(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"showhscrollbar")
	{
		SetShowHScrollBar(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"showvscrollbar")
	{
		SetShowVScrollBar(CStrMe::ConvertStrToBool(value));
	}
	else
	{
		CControlMe::SetProperty(name, value);
	}
}

void DivMe::Update()
{
	CControlMe::Update();
	UpdateScrollBar();
}

void DivMe::UpdateScrollBar()
{
	if (GetNative())
	{
		CHScrollBarMe *hScrollBar = GetHScrollBar();
		CVScrollBarMe *vScrollBar = GetVScrollBar();
		if (IsVisible())
		{
			int width = GetWidth();
			int height = GetHeight();
			int cy = hScrollBar ? hScrollBar->GetHeight(): 0;
			int cx = vScrollBar ? vScrollBar->GetWidth() : 0;
			int contentWidth = GetContentWidth();
			int contentHeight = GetContentHeight();
			if (hScrollBar)
			{
				hScrollBar->SetContentSize(contentWidth);
				SIZE sz = {width - cx, cy};
				hScrollBar->SetSize(sz);
				hScrollBar->SetPageSize(width - cx);
				POINT pptt = {0, height - cy};
				hScrollBar->SetLocation(pptt);
				if (contentWidth <= width)
				{
					hScrollBar->SetVisible(false);
				}
				else
				{
					hScrollBar->SetVisible(true);
				}
			}
			if (vScrollBar)
			{
				vScrollBar->SetContentSize(contentHeight);
				SIZE sz = {cx, height - cy};
				vScrollBar->SetSize(sz);
				vScrollBar->SetPageSize(height - cy);
				POINT pptt = {width - cx, 0};
				vScrollBar->SetLocation(pptt);
				int num7 = (hScrollBar && hScrollBar->IsVisible()) ? (height - cy) : height;
				if (contentHeight <= num7)
				{
					vScrollBar->SetVisible(false);
				}
				else
				{
					vScrollBar->SetVisible(true);
				}
			}
			if (hScrollBar && vScrollBar)
			{
				if (hScrollBar->IsVisible() && !vScrollBar->IsVisible())
				{
					hScrollBar->SetWidth(width);
					hScrollBar->SetPageSize(width);
				}
				else if (!hScrollBar->IsVisible() && vScrollBar->IsVisible())
				{
					vScrollBar->SetHeight(height);
					vScrollBar->SetPageSize(height);
				}
			}
			if (hScrollBar && hScrollBar->IsVisible())
			{
				hScrollBar->Update();
			}
			if (vScrollBar && vScrollBar->IsVisible())
			{
				vScrollBar->Update();
			}
		}
	}
}
