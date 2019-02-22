#include "..\\stdafx.h"
#include "..\\include\\Base\\CControl.h"
using namespace MeLib;

void CControlMe::CallEvents( int eventID )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlEvent func = (ControlEvent)(*list)[i];
			if (func != 0)
			{
				func(this, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallInvokeEvents( int eventID, void *args )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlInvokeEvent func = (ControlInvokeEvent)(*list)[i];
			if (func != 0)
			{
				func(this, args, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallKeyEvents( int eventID, char key )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlKeyEvent func = (ControlKeyEvent)(*list)[i];
			if (func != 0)
			{
				func(this, key, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallMouseEvents( int eventID, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlMouseEvent func = (ControlMouseEvent)(*list)[i];
			if (func != 0)
			{
				func(this, mp, button, clicks, delta, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallPaintEvents( int eventID, CPaintMe *paint, const RECT& clipRect )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlPaintEvent func = (ControlPaintEvent)(*list)[i];
			if (func != 0)
			{
				func(this, paint, clipRect, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallTimerEvents( int eventID, int timerID )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlTimerEvent func = (ControlTimerEvent)(*list)[i];
			if (func != 0)
			{
				func(this, timerID, (*listInvoke)[i]);
			}
		}
	}
}

void CControlMe::CallTouchEvents( int eventID, vector<CTouchMe> *touches )
{
	if (m_canRaiseEvents && m_events.find(eventID) != m_events.end())
	{
		vector<void*> *list = m_events[eventID];
		vector<void*> *listInvoke = m_invokes[eventID];
		int count = (int)list->size();
		for (int i = 0; i < count; i++)
		{
			ControlTouchEvent func = (ControlTouchEvent)(*list)[i];
			if (func != 0)
			{
				func(this, touches, (*listInvoke)[i]);
			}
		}
	}
}

_int64 CControlMe::GetPaintingBackColor()
{
	if ((m_backColor == COLOR_EMPTY) || COLOR_DISABLEDCONTROL != COLOR_EMPTY || !IsPaintEnabled(this))
	{
		return m_backColor;
	}
	else
	{
		return COLOR_DISABLEDCONTROL;
	}
}

String CControlMe::GetPaintingBackImage()
{
	return m_backImage;
}

_int64 CControlMe::GetPaintingBorderColor()
{
	return m_borderColor;
}

_int64 CControlMe::GetPaintingForeColor()
{
	if (m_foreColor == COLOR_CONTROLTEXT || COLOR_DISABLEDCONTROLTEXT == COLOR_EMPTY || IsPaintEnabled(this))
	{
		return m_foreColor;
	}
	else
	{
		return COLOR_DISABLEDCONTROLTEXT;
	}
}

static int m_timerID = 10000;
CControlMe::CControlMe()
{
	m_align = HorizontalAlignMe_Left;
	m_allowDrag = false;
	m_allowPreviewsEvent = false;
	m_autoEllipsis = false;
	m_autoShowToolTip = false;
	m_autoSize = false;
	m_anchor = ANCHOR(true, true, false, false);
	m_backColor = COLOR_CONTROL;
	m_backImage = L"";
	m_borderColor = COLOR_CONTROLBORDER;
	m_canFocus = true;
	m_canRaiseEvents = true;
	m_cursor = CursorsMe_Arrow;
	m_displayOffset = true;
	m_dock = DockStyleMe_None;
	m_enabled = true;
	m_focused = 0;
	m_font = new FONT(L"Î¢ÈíÑÅºÚ", 14, false, false, false);
	m_foreColor = COLOR_CONTROLTEXT;
	m_hasPopupMenu = false;
	m_isDragging = false;
	m_isWindow = false;
	m_location.x = 0;
	m_location.y = 0;
	m_maximumSize.cx = 100000;
	m_maximumSize.cy = 100000;
	m_minimumSize.cx = 0;
	m_minimumSize.cy = 0;
	m_margin.left = 0;
	m_margin.top = 0;
	m_margin.right = 0;
	m_margin.bottom = 0;
	m_name = L"";
	m_native = 0;
	m_oldLocation.x = 0;
	m_oldLocation.y = 0;
	m_oldSize.cx = 0;
	m_oldSize.cy = 0;
	m_opacity = 1.0f;
	m_padding = PADDING(0);
	m_parent = 0;
	m_percentLocation = 0;
	m_percentSize = 0;
	m_region.bottom = 0;
	m_region.left = 0;
	m_region.right = 0;
	m_region.top = 0;
	m_resourcePath = L"";
	m_size.cx = 0;
	m_size.cy = 0;
	m_tabIndex = 0;
	m_tabStop = false;
	m_tag = 0;
	m_text = L"";
	m_topMost = false;
	m_useRegion = false;
	m_verticalAlign = VerticalAlignMe_Top;
	m_visible = true;
}

CControlMe::~CControlMe()
{	
	if(m_font)
	{
		delete m_font;
		m_font = 0;
	}
	map<int, vector<void*>*>::iterator sIterEvents = m_events.begin();
	for(; sIterEvents != m_events.end(); ++sIterEvents)
	{
		vector<void*>::iterator sIterInner = sIterEvents->second->begin();
		for(; sIterInner !=  sIterEvents->second->end(); ++sIterInner)
		{
			*sIterInner = 0;
		}
		sIterEvents->second->clear();
		delete sIterEvents->second;
		sIterEvents->second = 0;
	}
	m_events.clear();

	map<int, vector<void*>*>::iterator sIterInvokes = m_invokes.begin();
	for(; sIterInvokes != m_invokes.end(); ++sIterInvokes)
	{
		sIterInvokes->second->clear();
		delete sIterInvokes->second;
		sIterInvokes->second = 0;
	}
	m_invokes.clear();

	if(m_parent)
	{
		delete m_parent;
		m_parent = 0;
	}
	if(m_percentLocation)
	{
		delete m_percentLocation;
		m_percentLocation = 0;
	}
	ClearControls();
	m_native = 0;
	m_parent = 0;
}

HorizontalAlignMe CControlMe::GetAlign()
{
	return m_align;
}

void CControlMe::SetAlign( HorizontalAlignMe align )
{
	m_align = align;
}

bool CControlMe::AllowDrag()
{
	return m_allowDrag;
}

void CControlMe::SetAllowDrag( bool allowDrag )
{
	m_allowDrag = allowDrag;
}

bool CControlMe::AllowPreviewsEvent()
{
	return m_allowPreviewsEvent;
}

void CControlMe::SetAllowPreviewsEvent( bool allowPreviewsEvent )
{
	m_allowPreviewsEvent = allowPreviewsEvent;
}

ANCHOR CControlMe::GetAnchor()
{
	return m_anchor;
}

void CControlMe::SetAnchor( const ANCHOR& anchor )
{
	m_anchor = anchor;
}

bool CControlMe::AutoEllipsis()
{
	return m_autoEllipsis;
}

void CControlMe::SetAutoEllipsis( bool autoEllipsis )
{
	m_autoEllipsis = autoEllipsis;
}

bool CControlMe::AutoSize()
{
	return m_autoSize;
}

void CControlMe::SetAutoSize( bool autoSize )
{
	if (m_autoSize != autoSize)
	{
		m_autoSize = autoSize;
		OnAutoSizeChanged();
	}
}

_int64 CControlMe::GetBackColor()
{
	return m_backColor;
}

void CControlMe::SetBackColor( _int64 backColor )
{
	if (m_backColor != backColor)
	{
		m_backColor = backColor;
		OnBackColorChanged();
	}
}

String CControlMe::GetBackImage()
{
	return m_backImage;
}

void CControlMe::SetBackImage( const String& backImage )
{
	if (m_backImage != backImage)
	{
		m_backImage = backImage;
		OnBackImageChanged();
	}
}

_int64 CControlMe::GetBorderColor()
{
	return m_borderColor;
}

void CControlMe::SetBorderColor( _int64 borderColor )
{
	m_borderColor = borderColor;
}

int CControlMe::GetBottom()
{
	return GetTop() + GetHeight();
}

RECT CControlMe::GetBounds()
{
	RECT rect = {GetLeft(), GetTop(), GetRight(), GetBottom()};
	return rect;
}

void CControlMe::SetBounds( const RECT& rect )
{
	POINT pt = {rect.left, rect.top};
	SetLocation(pt);
	SIZE sz = {rect.right - rect.left, rect.bottom - rect.top};
	SetSize(sz);
}

bool CControlMe::CanFocus()
{
	return m_canFocus;
}

void CControlMe::SetCanFocus( bool canFocus )
{
	m_canFocus = canFocus;
}

bool CControlMe::CanRaiseEvents()
{
	return m_canRaiseEvents;
}

void CControlMe::SetCanRaiseEvents( bool canRaiseEvents )
{
	m_canRaiseEvents = canRaiseEvents;
}

bool CControlMe::IsCapture()
{
	if (m_native)
	{
		if ((m_native->GetHoveredControl() == this) || (m_native->GetPushedControl() == this))
		{
			return true;
		}
	}
	return false;
}

CursorsMe CControlMe::GetCursor()
{
	return m_cursor;
}

void CControlMe::SetCursor( CursorsMe cursor )
{
	m_cursor = cursor;
}

bool CControlMe::DisplayOffset()
{
	return m_displayOffset;
}

void CControlMe::SetDisplayOffset( bool displayOffset )
{
	m_displayOffset = displayOffset;
}

RECT CControlMe::GetDisplayRect()
{
	if (m_useRegion)
	{
		return m_region;
	}
	RECT rc = {0, 0, GetWidth(), GetHeight()};
	return rc;
}

DockStyleMe CControlMe::GetDock()
{
	return m_dock;
}

void CControlMe::SetDock( DockStyleMe dock )
{
	if (m_dock != dock)
	{
		m_dock = dock;
		OnDockChanged();
	}
}

bool CControlMe::IsEnabled()
{
	return m_enabled;
}

void CControlMe::SetEnabled( bool enabled )
{
	if (m_enabled != enabled)
	{
		m_enabled = enabled;
		OnEnableChanged();
	}
}

bool CControlMe::AutoShowToolTip()
{
	return m_autoShowToolTip;
}

void CControlMe::SetAutoShowToolTip(bool autoShowToolTip)
{
	m_autoShowToolTip = autoShowToolTip;
}

bool CControlMe::IsFocused()
{
	return m_native != 0 && m_native->GetFocusedControl() == this;
}

void CControlMe::SetFocused( bool focused )
{
	if (m_native)
	{
		if (focused)
		{
			m_native->SetFocusedControl(this);
		}
		else
		{
			if(m_native->GetFocusedControl() == this)
			{
				m_native->SetFocusedControl(0);
			}
		}
	}
}

FONT* CControlMe::GetFont()
{
	return m_font;
}

void CControlMe::SetFont( FONT *font )
{
	if(m_font)
	{
		m_font->Copy(font);
	}
	OnFontChanged();
}

_int64 CControlMe::GetForeColor()
{
	return m_foreColor;
}

void CControlMe::SetForeColor( _int64 foreColor )
{
	if (m_foreColor != foreColor)
	{
		m_foreColor = foreColor;
		OnForeColorChanged();
	}
}

bool CControlMe::HasPopupMenu()
{
	return m_hasPopupMenu;
}

void CControlMe::SetHasPopupMenu( bool hasPopupMenu )
{
	m_hasPopupMenu = hasPopupMenu;
}

int CControlMe::GetHeight()
{
	if (m_percentSize && m_percentSize->cy != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cy * m_percentSize->cy);
	}
	return m_size.cy;
}

void CControlMe::SetHeight( int height )
{
	if (m_percentSize && m_percentSize->cy != -1.0f)
	{
		return;
	}
	SIZE sz = {m_size.cx, height};
	SetSize(sz);
}

bool CControlMe::IsDragging()
{
	return m_isDragging;
}

bool CControlMe::IsWindow()
{
	return m_isWindow;
}

void CControlMe::SetWindow( bool isWindow )
{
	m_isWindow = isWindow;
}

int CControlMe::GetLeft()
{
	if (m_percentLocation && m_percentLocation->x != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cx * m_percentLocation->x);
	}
	return m_location.x;
}

void CControlMe::SetLeft( int left )
{
	if (m_percentLocation == 0 || m_percentLocation->x == -1.0f)
	{
		POINT pt = {left, m_location.y};
		SetLocation(pt);
	}
}

POINT CControlMe::GetLocation()
{
	if (m_percentLocation)
	{
		POINT pt = {GetLeft(), GetTop()};
		return pt;
	}
	return m_location;
}

void CControlMe::SetLocation( const POINT& location )
{
	if (m_location.x != location.x || m_location.y != location.y)
	{
		if (m_percentLocation)
		{
			m_oldLocation = GetLocation();
			if (m_percentLocation->x == -1.0f)
			{
				m_location.x = location.x;
			}
			if (m_percentLocation->y == -1.0f)
			{
				m_location.y = location.y;
			}
		}
		else
		{
			m_oldLocation.x = m_location.x;
			m_oldLocation.y = m_location.y;
			m_location.x = location.x;
			m_location.y = location.y;
		}
		OnLocationChanged();
	}
}

PADDING CControlMe::GetMargin()
{
	return m_margin;
}

void CControlMe::SetMargin( const PADDING& margin )
{
	m_margin = margin;
	OnMarginChanged();
}

SIZE CControlMe::GetMaximumSize()
{
	return m_maximumSize;
}

void CControlMe::SetMaximumSize( SIZE maxinumSize )
{
	m_maximumSize = maxinumSize;
}

SIZE CControlMe::GetMinimumSize()
{
	return m_minimumSize;
}

void CControlMe::SetMinimumSize( SIZE minimumSize )
{
	m_minimumSize = minimumSize;
}

POINT CControlMe::GetMousePoint()
{
	if(m_native)
	{
		POINT mousePoint = m_native->GetMousePoint();
		return PointToControl(mousePoint);
	}
	else
	{
		POINT mousePoint;
		mousePoint.x = 0;
		mousePoint.y = 0;
		return mousePoint;
	}
}

String CControlMe::GetName()
{
	return m_name;
}

void CControlMe::SetName( const String& name )
{
	m_name = name;
}

CNativeBaseMe* CControlMe::GetNative()
{
	return m_native;
}

void CControlMe::SetNative( CNativeBaseMe *native )
{
	m_native = native;
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->SetNative(native);
	}
	OnLoad();
}

float CControlMe::GetOpacity()
{
	return m_opacity;
}

void CControlMe::SetOpacity( float opacity )
{
	m_opacity = opacity;
}

PADDING CControlMe::GetPadding()
{
	return m_padding;
}

void CControlMe::SetPadding( const PADDING& padding )
{
	m_padding = padding;
	OnPaddingChanged();
}

CControlMe* CControlMe::GetParent()
{
	return m_parent;
}

void CControlMe::SetParent( CControlMe *control )
{
	if (m_parent != control)
	{
		m_parent = control;
		OnParentChanged();
	}
}

RECT CControlMe::GetRegion()
{
	return m_region;
}

void CControlMe::SetRegion( const RECT& region )
{
	m_useRegion = true;
	m_region = region;
	OnRegionChanged();
}

String CControlMe::GetResourcePath()
{
	return m_resourcePath;
}

void CControlMe::SetResourcePath( const String& resourcePath )
{
	m_resourcePath = resourcePath;
}

int CControlMe::GetRight()
{
	return GetLeft() + GetWidth();
}

SIZE CControlMe::GetSize()
{
	if (m_percentSize)
	{
		SIZE sz = {GetWidth(), GetHeight()};
		return sz;
	}
	return m_size;
}

void CControlMe::SetSize( const SIZE& sz )
{
	SIZE size = sz;
	if (size.cx > m_maximumSize.cx)
	{
		size.cx = m_maximumSize.cx;
	}
	if (size.cy > m_maximumSize.cy)
	{
		size.cy = m_maximumSize.cy;
	}
	if (size.cx < m_minimumSize.cx)
	{
		size.cx = m_minimumSize.cx;
	}
	if (size.cy < m_minimumSize.cy)
	{
		size.cy = m_minimumSize.cy;
	}
	if (m_size.cx != size.cx || m_size.cy != size.cy)
	{
		if (m_percentSize)
		{
			m_oldSize = GetSize();
			if (m_percentSize->cx == -1.0f)
			{
				m_size.cx = size.cx;
			}
			if (m_percentSize->cy == -1.0f)
			{
				m_size.cy = size.cy;
			}
		}
		else
		{
			m_oldSize = m_size;
			m_size = size;
		}
		OnSizeChanged();
		Update();
	}
}

int CControlMe::GetTabIndex()
{
	return m_tabIndex;
}

void CControlMe::SetTabIndex( int tabIndex )
{
	if (m_tabIndex != tabIndex)
	{
		m_tabIndex = tabIndex;
		OnTabIndexChanged();
	}
}

bool CControlMe::IsTabStop()
{
	return m_tabStop;
}

void CControlMe::SetTabStop( bool tabStop )
{
	if (m_tabStop != tabStop)
	{
		m_tabStop = tabStop;
		OnTabStopChanged();
	}
}

void* CControlMe::GetTag()
{
	return m_tag;
}

void CControlMe::SetTag( void *tag )
{
	m_tag = tag;
}

String CControlMe::GetText()
{
	return m_text;
}

void CControlMe::SetText( const String& text )
{
	if (m_text != text)
	{
		m_text = text;
		OnTextChanged();
	}
}

int CControlMe::GetTop()
{
	if (m_percentLocation && m_percentLocation->y != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cy * m_percentLocation->y);
	}
	return m_location.y;
}

void CControlMe::SetTop( int top )
{
	if (m_percentLocation == 0 || m_percentLocation->y == -1.0f)
	{
		POINT pt = {m_location.x, top};
		SetLocation(pt);
	}
}

bool CControlMe::IsTopMost()
{
	return m_topMost;
}

void CControlMe::SetTopMost( bool topMost )
{
	m_topMost = topMost;
}

bool CControlMe::UseRegion()
{
	return m_useRegion;
}

VerticalAlignMe CControlMe::GetVerticalAlign()
{
	return m_verticalAlign;
}

void CControlMe::SetVerticalAlign( VerticalAlignMe verticalAlign )
{
	m_verticalAlign = verticalAlign;
}

bool CControlMe::IsVisible()
{
	return m_visible;
}

void CControlMe::SetVisible( bool visible )
{
	if (m_visible != visible)
	{
		m_visible = visible;
		OnVisibleChanged();
	}
}

int CControlMe::GetWidth()
{
	if (m_percentSize && m_percentSize->cx != -1.0f)
	{
		SIZE size = m_parent != 0 ? m_parent->GetSize() : m_native->GetDisplaySize();
		return (int) (size.cx * m_percentSize->cx);
	}
	return m_size.cx;
}

void CControlMe::SetWidth( int width )
{
	if (!m_percentSize || m_percentSize->cx == -1.0f)
	{
		SIZE sz = {width, m_size.cy};
		SetSize(sz);
	}
}

void CControlMe::AddControl( CControlMe *control )
{
	control->SetParent(this);
	control->SetNative(m_native);
	m_controls.push_back(control);
	control->OnAdd();
}

void CControlMe::BeginInvoke( void *args )
{
	if (m_native)
	{
		m_native->GetHost()->BeginInvoke(this, args);
	}
}

void CControlMe::BringChildToFront( CControlMe *childControl )
{
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == childControl)
		{
			m_controls.erase(it);
			break;
		}
	}
	m_controls.push_back(childControl);
}

void CControlMe::BringToFront()
{
	if (m_native)
	{
		m_native->BringToFront(this);
	}
}

void CControlMe::ClearControls()
{
	vector<CControlMe*> controlsTemp;
	String name = GetName();
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		CControlMe* control = (*it);
		controlsTemp.push_back(control);
	}

	for (vector<CControlMe*>::iterator it = controlsTemp.begin(); it != controlsTemp.end(); it++)
	{
		CControlMe* control = (*it);
		control->OnRemove();
	}
	controlsTemp.clear();
	m_controls.clear();
}

bool CControlMe::ContainsControl( CControlMe *control )
{
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			return true;
		}
	}
	return false;
}

bool CControlMe::ContainsPoint( const POINT& mp )
{
	POINT point2 = PointToControl(mp);
	SIZE size = GetSize();
	if (point2.x >= 0 && point2.x <= size.cx && point2.y >= 0 && point2.y <= size.cy)
	{
		if (!m_useRegion)
		{
			return true;
		}
		if (point2.x >= m_region.left 
			&& point2.x <= m_region.right 
			&& point2.y >= m_region.top 
			&& point2.y <= m_region.bottom)
		{
			return true;
		}
	}
	return false;
}

void CControlMe::Focus()
{
	SetFocused(true);
}

vector<CControlMe*> CControlMe::GetControls()
{
	return m_controls;
}

String CControlMe::GetControlType()
{
	return L"Control";
}

POINT CControlMe::GetDisplayOffset()
{
	POINT pt = {0, 0};
	return pt;
}

vector<wstring> CControlMe::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"Add");
	ws.push_back(L"BackColorChanged");
	ws.push_back(L"BackImageChanged");
	ws.push_back(L"Char");
	ws.push_back(L"Click");
	ws.push_back(L"Copy");
	ws.push_back(L"Cut");
	ws.push_back(L"DockChanged");
	ws.push_back(L"DoubleClick");
	ws.push_back(L"DragBegin");
	ws.push_back(L"DragEnd");
	ws.push_back(L"Dragging");
	ws.push_back(L"EnabledChanged");
	ws.push_back(L"FontChanged");
	ws.push_back(L"ForeColorChanged");
	ws.push_back(L"GotFocus");
	ws.push_back(L"Invoke");
	ws.push_back(L"KeyDown");
	ws.push_back(L"KeyUp");
	ws.push_back(L"Load");
	ws.push_back(L"LocationChanged");
	ws.push_back(L"LostFocus");
	ws.push_back(L"MarginChanged");
	ws.push_back(L"MouseDown");
	ws.push_back(L"MouseEnter");
	ws.push_back(L"MouseLeave");
	ws.push_back(L"MouseMove");
	ws.push_back(L"MouseUp");
	ws.push_back(L"MouseWheel");
	ws.push_back(L"PaddingChanged");
	ws.push_back(L"ParentChanged");
	ws.push_back(L"Paint");
	ws.push_back(L"PaintBorder");
	ws.push_back(L"Paste");
	ws.push_back(L"RegionChanged");
	ws.push_back(L"Remove");
	ws.push_back(L"SizeChanged");
	ws.push_back(L"TabIndexChanged");
	ws.push_back(L"TabStop");
	ws.push_back(L"TabStopChanged");
	ws.push_back(L"TextChanged");
	ws.push_back(L"Timer");
	ws.push_back(L"VisibleChanged");
	return ws;
}

int CControlMe::GetNewTimerID()
{
	return m_timerID++;
}

CControlMe* CControlMe::GetPopupMenuContext( CControlMe *control )
{
	if (m_hasPopupMenu)
	{
		return this;
	}
	if (m_parent)
	{
		return GetPopupMenuContext(m_parent);
	}
	return 0;
}

void CControlMe::GetProperty( const String& name, String *value, String *type )
{
	int len = (int)name.length();
	switch (len)
	{
	case 3:
		if (name != L"top")
		{
			break;
		}
		*type = L"float";
		if (m_percentLocation == 0 || m_percentLocation->y == -1.0f)
		{
			*value = CStrMe::ConvertIntToStr(GetTop());
			return;
		}
		*value = L"%" + CStrMe::ConvertFloatToStr(100.0f * m_percentLocation->y);
		return;

	case 4:
		if (name != L"dock")
		{
			if (name == L"font")
			{
				*type = L"font";
				*value = CStrMe::ConvertFontToStr(GetFont());
				return;
			}
			if (name == L"left")
			{
				*type = L"float";
				if ((m_percentLocation != 0) && (m_percentLocation->x != -1.0f))
				{
					*value = L"%" + CStrMe::ConvertFloatToStr(100.0f * m_percentLocation->x);
					return;
				}
				*value = CStrMe::ConvertIntToStr(GetLeft());
				return;
			}
			if (name == L"name")
			{
				*type = L"text";
				*value = GetName();
				return;
			}
			if (name == L"size")
			{
				*type = L"size";
				if (m_percentSize != 0)
				{
					String str;
					String str2;
					String str3;
					GetProperty(L"width", &str, &str3);
					GetProperty(L"height", &str2, &str3);
					*value = str + L"," + str2;
					return;
				}
				*value = CStrMe::ConvertSizeToStr(GetSize());
				return;
			}
			if (name != L"text")
			{
				break;
			}
			*type = L"text";
			*value = GetText();
			return;
		}
		*type = L"enum:DockStyleMe";
		*value = CStrMe::ConvertDockToStr(GetDock());
		return;

	case 5:
		if (name != L"align")
		{
			if (name != L"width")
			{
				break;
			}
			*type = L"float";
			if ((m_percentSize != 0) && (m_percentSize->cx != -1.0f))
			{
				*value = L"%" + CStrMe::ConvertFloatToStr(100.0f * m_percentSize->cx);
				return;
			}
			*value = CStrMe::ConvertIntToStr(GetWidth());
			return;
		}
		*type = L"enum:HorizontalAlignMe";
		*value = CStrMe::ConvertHorizontalAlignToStr(GetAlign());
		return;

	case 6:
		if (name != L"anchor")
		{
			if (name == L"bounds")
			{
				*type = L"rect";
				*value = CStrMe::ConvertRectToStr(GetBounds());
				return;
			}
			if (name == L"cursor")
			{
				*type = L"enum:CursorsMe";
				*value = CStrMe::ConvertCursorToStr(GetCursor());
				return;
			}
			if (name == L"height")
			{
				*type = L"float";
				if ((m_percentSize != 0) && (m_percentSize->cy != -1.0f))
				{
					*value = L"%" + CStrMe::ConvertFloatToStr(100.0f * m_percentSize->cy);
					return;
				}
				*value = CStrMe::ConvertIntToStr(GetHeight());
				return;
			}
			if (name == L"margin")
			{
				*type = L"margin";
				*value = CStrMe::ConvertPaddingToStr(GetMargin());
				return;
			}
			if (name != L"region")
			{
				break;
			}
			*type = L"rect";
			*value = CStrMe::ConvertRectToStr(GetRegion());
			return;
		}
		*type = L"anchor";
		*value = CStrMe::ConvertAnchorToStr(GetAnchor());
		return;

	case 7:
		if (name != L"enabled")
		{
			if (name == L"focused")
			{
				*type = L"bool";
				*value = CStrMe::ConvertBoolToStr(IsFocused());
				return;
			}
			if (name == L"opacity")
			{
				*type = L"float";
				*value = CStrMe::ConvertFloatToStr(GetOpacity());
				return;
			}
			if (name == L"padding")
			{
				*type = L"padding";
				*value = CStrMe::ConvertPaddingToStr(GetPadding());
				return;
			}
			if (name == L"tabstop")
			{
				*type = L"bool";
				*value = CStrMe::ConvertBoolToStr(IsTabStop());
				return;
			}
			if (name == L"topmost")
			{
				*type = L"bool";
				*value = CStrMe::ConvertBoolToStr(IsTopMost());
				return;
			}
			if (name != L"visible")
			{
				break;
			}
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(IsVisible());
			return;
		}
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsEnabled());
		return;

	case 8:
		if (name != L"autosize")
		{
			if (name == L"canfocus")
			{
				*type = L"bool";
				*value = CStrMe::ConvertBoolToStr(CanFocus());
				return;
			}
			if (name == L"iswindow")
			{
				*type = L"bool";
				*value = CStrMe::ConvertBoolToStr(IsWindow());
				return;
			}
			if (name == L"location")
			{
				*type = L"point";
				if (m_percentLocation != 0)
				{
					String str4;
					String str5;
					String str6;
					GetProperty(L"left", &str4, &str6);
					GetProperty(L"top", &str5, &str6);
					*value = str4 + L"," + str5;
					return;
				}
				*value = CStrMe::ConvertPointToStr(GetLocation());
				return;
			}
			if (name != L"tabindex")
			{
				break;
			}
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetTabIndex());
			return;
		}
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AutoSize());
		return;

	case 9:
		if (name != L"allowdrag")
		{
			if (name == L"backcolor")
			{
				*type = L"color";
				*value = CStrMe::ConvertColorToStr(GetBackColor());
				return;
			}
			if (name == L"backimage")
			{
				*type = L"text";
				*value = GetBackImage();
				return;
			}
			if (name != L"forecolor")
			{
				break;
			}
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetForeColor());
			return;
		}
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowDrag());
		return;

	default:
		if (name == L"allowpreviewsevent")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowPreviewsEvent());
			return;
		}
		if (name == L"autoellipsis")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AutoEllipsis());
			return;
		}
		if (name == L"bordercolor")
		{
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetBorderColor());
			return;
		}
		if (name == L"canraiseevents")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanRaiseEvents());
			return;
		}
		if (name == L"displayoffset")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(DisplayOffset());
			return;
		}
		if (name == L"haspopupmenu")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(HasPopupMenu());
			return;
		}
		if (name == L"maximumsize")
		{
			*type = L"size";
			*value = CStrMe::ConvertSizeToStr(GetMaximumSize());
			return;
		}
		if (name == L"minimumsize")
		{
			*type = L"size";
			*value = CStrMe::ConvertSizeToStr(GetMinimumSize());
			return;
		}
		if (name == L"resourcepath")
		{
			*type = L"text";
			*value = GetResourcePath();
			return;
		}
		if (name == L"vertical-align")
		{
			*type = L"enum:VerticalAlignMe";
			*value = CStrMe::ConvertVerticalAlignToStr(GetVerticalAlign());
		}
		break;
	}
}

vector<String> CControlMe::GetPropertyNames()
{
	static String arry[] = {L"Align", L"AllowDrag", L"AllowPreviewsEvent", L"Anchor", L"AutoEllipsis", L"AutoSize", 
		L"BackColor", L"BackImage", L"BorderColor", L"Bounds", 
		L"CanFocus", L"CanRaiseEvents", L"Cursor", L"DisplayOffset", L"Dock", L"Enabled",
		L"Focused", L"Font", L"ForeColor", L"HasPopupMenu", L"Height", L"IsWindow", L"Left", L"Location"
		, L"Margin", L"MaximumSize", L"MinimumSize", L"Name", L"Opacity", L"Padding", L"Region", L"ResourcePath",
		L"Size", L"TabIndex", L"TabStop", L"Text", L"Top", L"TopMost", L"Vertical-Align", L"Visible", L"Width"};
	vector<String> propertyNames(arry, arry + _countof(arry));
	return propertyNames;
}

bool CControlMe::HasChildren()
{
	return !m_controls.empty();
}

void CControlMe::Hide()
{
	SetVisible(false);
}

void CControlMe::InsertControl( int index, CControlMe *control )
{
	m_controls.insert(m_controls.begin() + index, control);
}

void CControlMe::Invalidate()
{
	if (m_native)
	{
		m_native->Invalidate(this);
	}
}

void CControlMe::Invoke( void *args )
{
	if (m_native)
	{
		m_native->GetHost()->Invoke(this, args);
	}
}

bool CControlMe::IsPaintEnabled( CControlMe *control )
{
	if (!control->IsEnabled())
	{
		return false;
	}
	CControlMe *parent = control->GetParent();
	if (parent)
	{
		return IsPaintEnabled(parent);
	}
	return true;
}

bool CControlMe::IsPaintVisible( CControlMe *control )
{
	if (!control->IsVisible())
	{
		return false;
	}
	CControlMe *parent = control->GetParent();
	if (parent != 0)
	{
		return IsPaintVisible(parent);
	}
	return true;
}

void CControlMe::OnAdd()
{
	CallEvents(EVENTID::ADD);
}

void CControlMe::OnAutoSizeChanged()
{
	CallEvents(EVENTID::AUTOSIZECHANGED);
}

void CControlMe::OnBackColorChanged()
{
	CallEvents(EVENTID::BACKCOLORCHANGED);
}

void CControlMe::OnBackImageChanged()
{
	CallEvents(EVENTID::BACKIMAGECHANGED);
}

void CControlMe::OnChar( wchar_t ch )
{
	CallKeyEvents(EVENTID::CHAR, ch);
}

void CControlMe::OnClick( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::CLICK, mp, button, clicks, delta);
}

void CControlMe::OnCopy()
{
	CallEvents(EVENTID::COPY);
}

void CControlMe::OnCut()
{
	CallEvents(EVENTID::CUT);
}

void CControlMe::OnDockChanged()
{
	CallEvents(EVENTID::DOCKCHANGED);
}

void CControlMe::OnDoubleClick( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::DOUBLECLICK, mp, button, clicks, delta);
}

bool CControlMe::OnDragBegin()
{
	CallEvents(EVENTID::DRAGBEGIN);
	return true;
}

void CControlMe::OnDragEnd()
{
	m_isDragging = false;
	CallEvents(EVENTID::DRAGEND);
}

void CControlMe::OnDragging()
{
	m_isDragging = true;
	CallEvents(EVENTID::DRAGGING);
}

void CControlMe::OnDragReady( POINT *startOffset )
{
	startOffset->x = 5;
	startOffset->y = 5;
}

void CControlMe::OnEnableChanged()
{
	CallEvents(EVENTID::ENABLECHANGED);
}

void CControlMe::OnFontChanged()
{
	CallEvents(EVENTID::FONTCHANGED);
}

void CControlMe::OnForeColorChanged()
{
	CallEvents(EVENTID::FORECOLORCHANGED);
}

void CControlMe::OnGotFocus()
{
	CallEvents(EVENTID::GOTFOCUS);
}

void CControlMe::OnInvoke( void *args )
{
	CallInvokeEvents(EVENTID::INVOKE, args);
}

void CControlMe::OnLoad()
{
	CallEvents(EVENTID::LOAD);
}

void CControlMe::OnLocationChanged()
{
	CallEvents(EVENTID::LOCATIONCHANGED);
}

void CControlMe::OnLostFocus()
{
	CallEvents(EVENTID::LOSTFOCUS);
}

void CControlMe::OnKeyDown( char key )
{
	CallKeyEvents(EVENTID::KEYDOWN, key);
	if (GetNative()->GetHost()->IsKeyPress(0x11))
	{
		if (key == 'C')
		{
			OnCopy();
		}
		else if (key == 'V')
		{
			OnPaste();
		}
		else if (key == 'X')
		{
			OnCut();
		}
	}
}

void CControlMe::OnKeyUp( char key )
{
	CallKeyEvents(EVENTID::KEYUP, key);
}

void CControlMe::OnMarginChanged()
{
	CallEvents(EVENTID::MARGINCHANGED);
}

void CControlMe::OnMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEDOWN, mp, button, clicks, delta);
}

void CControlMe::OnMouseEnter( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEENTER, mp, button, clicks, delta);
	if (m_autoShowToolTip && !m_text.empty())
	{
		m_native->GetHost()->ShowToolTip(this, m_text, m_native->GetMousePoint());
	}
}

void CControlMe::OnMouseLeave( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSELEAVE, mp, button, clicks, delta);
}

void CControlMe::OnMouseMove( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEMOVE, mp, button, clicks, delta);
}

void CControlMe::OnMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEUP, mp, button, clicks, delta);
}

void CControlMe::OnMouseWheel( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CallMouseEvents(EVENTID::MOUSEWHEEL, mp, button, clicks, delta);
}

void CControlMe::OnPaddingChanged()
{
	CallEvents(EVENTID::PADDINGCHANGED);
}

void CControlMe::OnPaint( CPaintMe *paint, const RECT& clipRect )
{
	OnPaintBackground(paint, clipRect);
	OnPaintForeground(paint, clipRect);
	CallPaintEvents(EVENTID::PAINT, paint, clipRect);
}

void CControlMe::OnPaintBackground( CPaintMe *paint, const RECT& clipRect )
{
	RECT rect = {0, 0, GetWidth(), GetHeight()};
	paint->FillRect(GetPaintingBackColor(), rect);
	String paintingBackImage = GetPaintingBackImage();
	if ((int)paintingBackImage.size() > 0)
	{
		paint->DrawImage(paintingBackImage.c_str(), rect);
	}
}

void CControlMe::OnPaintBorder( CPaintMe *paint, const RECT& clipRect )
{
	RECT rect = {0, 0, GetWidth(), GetHeight()};
	paint->DrawRect(GetPaintingBorderColor(), 1.0f, 0, rect);
	CallPaintEvents(EVENTID::PAINTBORDER, paint, clipRect);
}

void CControlMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{

}

void CControlMe::OnParentChanged()
{
	CallEvents(EVENTID::PARENTCHANGED);
}

void CControlMe::OnPaste()
{
	CallEvents(EVENTID::PASTE);
}

void CControlMe::OnPrePaint( CPaintMe *paint, const RECT& clipRect )
{

}

bool CControlMe::OnPreviewsKeyEvent( int eventID, char key )
{
	return false;
}

bool CControlMe::OnPreviewsMouseEvent( int eventID, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	return false;
}

void CControlMe::OnRegionChanged()
{
	CallEvents(EVENTID::REGIONCHANGED);
}

void CControlMe::OnRemove()
{
	CallEvents(EVENTID::REMOVE);
}

void CControlMe::OnSizeChanged()
{
	CallEvents(EVENTID::SIZECHANGED);
}

void CControlMe::OnTabIndexChanged()
{
	CallEvents(EVENTID::TABINDEXCHANGED);
}

void CControlMe::OnTabStop()
{
	CallEvents(EVENTID::TABSTOP);
}

void CControlMe::OnTabStopChanged()
{
	CallEvents(EVENTID::TABSTOPCHANGED);
}

void CControlMe::OnTextChanged()
{
	CallEvents(EVENTID::TEXTCHANGED);
}

void CControlMe::OnTimer( int timerID )
{
	CallTimerEvents(EVENTID::TIMER, timerID);
}

void CControlMe::OnTouchBegin( vector<CTouchMe> *touches )
{
	CallTouchEvents(EVENTID::TOUCHBEGIN, touches);
}

void CControlMe::OnTouchCancel( vector<CTouchMe> *touches )
{
	CallTouchEvents(EVENTID::TOUCHCANCEL, touches);
}

void CControlMe::OnTouchEnd( vector<CTouchMe> *touches )
{
	CallTouchEvents(EVENTID::TOUCHEND, touches);
}

void CControlMe::OnTouchMove( vector<CTouchMe> *touches )
{
	CallTouchEvents(EVENTID::TOUCHMOVE, touches);
}

void CControlMe::OnVisibleChanged()
{
	CallEvents(EVENTID::VISIBLECHANGED);
}

POINT CControlMe::PointToControl( const POINT& mp )
{
	if (m_native)
	{
		int clientX = m_native->ClientX(this);
		int clientY = m_native->ClientY(this);
		POINT pt = {mp.x - clientX, mp.y - clientY};
		return pt;
	}
	return mp;
}

POINT CControlMe::PointToNative( const POINT& mp )
{
	if (m_native)
	{
		int clientX = m_native->ClientX(this);
		int clientY = m_native->ClientY(this);
		POINT pt = {mp.x + clientX, mp.y + clientY};
		return pt;
	}
	return mp;
}

void CControlMe::RegisterEvent( void *func, int eventID, void *pInvoke )
{
	vector<void*> *list = 0;
	if (m_events.find(eventID) != m_events.end())
	{
		list = m_events[eventID];
	}
	else
	{
		list = new vector<void*>();
		m_events[eventID] = list;
	}
	list->push_back(func);
	
	vector<void*> *listInvoke = 0;
	if (m_invokes.find(eventID) != m_invokes.end())
	{
		listInvoke = m_invokes[eventID];
	}
	else
	{
		listInvoke = new vector<void*>();
		m_invokes[eventID] = listInvoke;
	}
	listInvoke->push_back(pInvoke);
}

void CControlMe::RemoveControl( CControlMe *control )
{
	if (m_native)
	{
		m_native->RemoveControl(control);
	}
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			m_controls.erase(it);
			break;
		}
	}
	control->OnRemove();
	control->SetParent(0);
}

void CControlMe::SendChildToBack( CControlMe *childControl )
{
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == childControl)
		{
			m_controls.erase(it);
			break;
		}
	}
	m_controls.insert(m_controls.begin(), childControl);
}

void CControlMe::SendToBack()
{
	if (m_native)
	{
		m_native->SendToBack(this);
	}
}

void CControlMe::SetProperty( const String& name, const String& value )
{
	int len = (int)name.length();
	switch (len)
	{
	case 3:
		{
			if (name != L"top")
			{
				break;
			}
			if (value.find(L"%") == -1)
			{
				if (m_percentLocation)
				{
					m_percentLocation->y = -1.0f;
				}
				SetTop(CStrMe::ConvertStrToInt(value));
				return;
			}
			float num2 = CStrMe::ConvertStrToFloat(value) / 100.0f;
			if (m_percentLocation == 0)
			{
				m_percentLocation = new POINTF();
				m_percentLocation->x = -1.0f;
			}
			m_percentLocation->y = num2;
			return;
		}
	case 4:
		if (name != L"dock")
		{
			if (name == L"font")
			{
				SetFont(CStrMe::ConvertStrToFont(value));
				return;
			}
			if (name == L"left")
			{
				if (value.find(L"%") != -1)
				{
					float num3 = CStrMe::ConvertStrToFloat(value) / 100.0f;
					if (m_percentLocation == 0)
					{
						m_percentLocation = new POINTF();
						m_percentLocation->y = -1.0f;
					}
					m_percentLocation->x = num3;
					return;
				}
				if (m_percentLocation != 0)
				{
					m_percentLocation->x = -1.0f;
				}
				SetLeft(CStrMe::ConvertStrToInt(value));
				return;
			}
			if (name == L"name")
			{
				SetName(value);
				return;
			}
			if (name == L"size")
			{
				if (value.find(L"%") == -1)
				{
					SetSize(CStrMe::ConvertStrToSize(value));
					return;
				}
				vector<String> strArray = CStrMe::Split(value, L",");
				SetProperty(L"width", strArray[0]);
				SetProperty(L"height", strArray[1]);
				return;
			}
			if (name != L"text")
			{
				break;
			}
			SetText(value);
			return;
		}
		SetDock(CStrMe::ConvertStrToDock(value));
		return;

	case 5:
		if (name != L"align")
		{
			if (name != L"width")
			{
				break;
			}
			if (value.find(L"%") != -1)
			{
				float num4 = CStrMe::ConvertStrToFloat(value) / 100.0f;
				if (m_percentSize == 0)
				{
					m_percentSize = new SIZEF();
					m_percentSize->cy = -1.0f;
				}
				m_percentSize->cx = num4;
				return;
			}
			if (m_percentSize != 0)
			{
				m_percentSize->cx = -1.0f;
			}
			SetWidth(CStrMe::ConvertStrToInt(value));
			return;
		}
		SetAlign(CStrMe::ConvertStrToHorizontalAlign(value));
		return;

	case 6:
		if (name != L"anchor")
		{
			if (name == L"bounds")
			{
				SetBounds(CStrMe::ConvertStrToRect(value));
				return;
			}
			if (name == L"cursor")
			{
				SetCursor(CStrMe::ConvertStrToCursor(value));
				return;
			}
			if (name == L"height")
			{
				if (value.find(L"%") != -1)
				{
					float num5 = CStrMe::ConvertStrToFloat(value) / 100.0f;
					if (m_percentSize == 0)
					{
						m_percentSize = new SIZEF();
						m_percentSize->cx = -1.0f;
					}
					m_percentSize->cy = num5;
					return;
				}
				if (m_percentSize != 0)
				{
					m_percentSize->cy = -1.0f;
				}
				SetHeight(CStrMe::ConvertStrToInt(value));
				return;
			}
			if (name == L"margin")
			{
				SetMargin(CStrMe::ConvertStrToPadding(value));
				return;
			}
			if (name != L"region")
			{
				break;
			}
			SetRegion(CStrMe::ConvertStrToRect(value));
			return;
		}
		SetAnchor(CStrMe::ConvertStrToAnchor(value));
		return;

	case 7:
		if (name != L"enabled")
		{
			if (name == L"focused")
			{
				SetFocused(CStrMe::ConvertStrToBool(value));
				return;
			}
			if (name == L"opacity")
			{
				SetOpacity(CStrMe::ConvertStrToFloat(value));
				return;
			}
			if (name == L"padding")
			{
				SetPadding(CStrMe::ConvertStrToPadding(value));
				return;
			}
			if (name == L"tabstop")
			{
				SetTabStop(CStrMe::ConvertStrToBool(value));
				return;
			}
			if (name == L"topmost")
			{
				SetTopMost(CStrMe::ConvertStrToBool(value));
				return;
			}
			if (name != L"visible")
			{
				break;
			}
			SetVisible(CStrMe::ConvertStrToBool(value));
			return;
		}
		SetEnabled(CStrMe::ConvertStrToBool(value));
		return;

	case 8:
		if (name != L"autosize")
		{
			if (name == L"canfocus")
			{
				SetCanFocus(CStrMe::ConvertStrToBool(value));
				return;
			}
			if (name == L"iswindow")
			{
				SetWindow(CStrMe::ConvertStrToBool(value));
				return;
			}
			if (name == L"location")
			{
				if (value.find(L"%") == -1)
				{
					SetLocation(CStrMe::ConvertStrToPoint(value));
					return;
				}
				vector<String> strArray2 = CStrMe::Split(value, L",");
				SetProperty(L"left", strArray2[0]);
				SetProperty(L"top", strArray2[1]);
				return;
			}
			if (name != L"tabindex")
			{
				break;
			}
			SetTabIndex(CStrMe::ConvertStrToInt(value));
			return;
		}
		SetAutoSize(CStrMe::ConvertStrToBool(value));
		return;

	case 9:
		if (name != L"allowdrag")
		{
			if (name == L"backcolor")
			{
				SetBackColor(CStrMe::ConvertStrToColor(value));
				return;
			}
			if (name == L"backimage")
			{
				SetBackImage(value);
				return;
			}
			if (name != L"forecolor")
			{
				break;
			}
			SetForeColor(CStrMe::ConvertStrToColor(value));
			return;
		}
		SetAllowDrag(CStrMe::ConvertStrToBool(value));
		return;

	default:
		if (name == L"allowpreviewsevent")
		{
			SetAllowPreviewsEvent(CStrMe::ConvertStrToBool(value));
			return;
		}
		if (name == L"autoellipsis")
		{
			SetAutoEllipsis(CStrMe::ConvertStrToBool(value));
			return;
		}
		if (name == L"bordercolor")
		{
			SetBorderColor(CStrMe::ConvertStrToColor(value));
			return;
		}
		if (name == L"canraiseevents")
		{
			SetCanRaiseEvents(CStrMe::ConvertStrToBool(value));
			return;
		}
		if (name == L"displayoffset")
		{
			SetDisplayOffset(CStrMe::ConvertStrToBool(value));
			return;
		}
		if (name == L"haspopupmenu")
		{
			SetHasPopupMenu(CStrMe::ConvertStrToBool(value));
			return;
		}
		if (name == L"maximumsize")
		{
			SetMaximumSize(CStrMe::ConvertStrToSize(value));
			return;
		}
		if (name == L"minimumsize")
		{
			SetMinimumSize(CStrMe::ConvertStrToSize(value));
			return;
		}
		if (name == L"resourcepath")
		{
			SetResourcePath(value);
			return;
		}
		if (name == L"vertical-align")
		{
			SetVerticalAlign(CStrMe::ConvertStrToVerticalAlign(value));
		}
		break;
	}
}

void CControlMe::Show()
{
	SetVisible(true);
}

void CControlMe::StartTimer( int timerID, int interval )
{
	if (m_native)
	{
		m_native->StartTimer(this, timerID, interval);
	}
}

void CControlMe::StopTimer( int timerID )
{
	if (m_native)
	{
		m_native->StopTimer(timerID);
	}
}

void CControlMe::UnRegisterEvent( void *func, int eventID )
{
	map<int, vector<void*>*>::iterator it = m_events.find(eventID);
	if (it != m_events.end())
	{
		vector<void*> *vec = it->second;
		int size = (int)vec->size();
		int index = -1;
		if(size > 0)
		{
			for(int i = 0; i < size; i++)
			{
				if((*vec)[i] = func)
				{
					index = i;
					break;
				}
			}
		}
		if(index > 0)
		{
			int count = 0;
			for (vector<void*>::iterator iter = vec->begin(); iter != vec->end(); iter++)
			{
				if (count == index)
				{
					vec->erase(iter);
					break;
				}
				++count;
			}
			map<int, vector<void*>*>::iterator itInvokes = m_invokes.find(eventID);
			count = 0;
			for (vector<void*>::iterator iter = itInvokes->second->begin(); iter != itInvokes->second->end(); iter++)
			{
				if (count == index)
				{
					itInvokes->second->erase(iter);
					break;
				}
				++count;
			}
		}
	}
}

void CControlMe::Update()
{
	if (m_native)
	{
		m_native->SetAlign(&m_controls);
		if (m_oldSize.cx > 0 && m_oldSize.cy > 0)
		{
			m_native->SetAnchor(&m_controls, m_oldSize);
		}
		m_native->SetDock(&m_controls);
		m_oldLocation = GetLocation();
		m_oldSize = GetSize();
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			m_controls[i]->Update();
		}
	}
}