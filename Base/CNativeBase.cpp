#include "..\\stdafx.h"
#include "..\\include\\Base\\CNativeBase.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace MeLib;

CControlMe* CNativeBaseMe::FindControl( const POINT& mp, vector<CControlMe*> *controls )
{
	int count = (int)controls->size();
	for (int i =  count - 1; i >= 0; i--)
	{
		CControlMe *parent = (*controls)[i];
		if (parent->IsVisible() && parent->ContainsPoint(mp))
		{
			vector<CControlMe*> sortedControls;
			GetSortedControls(parent, &sortedControls);
			CControlMe *control = FindControl(mp, &sortedControls);
			if (control)
			{
				return control;
			}
			return parent;
		}
	}
	return 0;
}

CControlMe* CNativeBaseMe::FindControl( const String& name, vector<CControlMe*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *parent = controls->at(i);
		if (parent->GetName() == name)
		{
			return parent;
		}
		vector<CControlMe*> list = parent->GetControls();
		if ((int)list.size() > 0)
		{
			CControlMe *control = FindControl(name, &list);
			if (control)
			{
				return control;
			}
		}
	}
	return 0;
}

CControlMe* CNativeBaseMe::FindPreviewsControl( CControlMe *control )
{
	if (control && !control->AllowPreviewsEvent())
	{
		CControlMe *parent = control->GetParent();
		if (parent)
		{
			return FindPreviewsControl(parent);
		}
	}
	return control;
}

CControlMe* CNativeBaseMe::FindWindow( CControlMe *control )
{
	if (!control->IsWindow())
	{
		CControlMe *parent = control->GetParent();
		if (parent)
		{
			return FindWindow(parent);
		}
	}
	return control;
}

float CNativeBaseMe::GetPaintingOpacity( CControlMe *control )
{
	float opacity = control->GetOpacity();
	CControlMe *parent = control->GetParent();
	if (parent)
	{
		return (opacity * GetPaintingOpacity(parent));
	}
	return (opacity * m_opacity);
}

String CNativeBaseMe::GetPaintingResourcePath( CControlMe *control )
{
	String resourcePath = control->GetResourcePath();
	if ((int)resourcePath.size() > 0)
	{
		return resourcePath;
	}
	CControlMe *parent = control->GetParent();
	if (parent)
	{
		return GetPaintingResourcePath(parent);
	}
	return m_resourcePath;
}

bool CNativeBaseMe::GetSortedControls( CControlMe *parent, vector<CControlMe*> *sortedControls )
{
	vector<CControlMe*> controls;
	if (parent)
	{
		controls = parent->GetControls();
	}
	else
	{
		controls = m_controls;
	}
	int count = (int)controls.size();
	int index = 0;
	for (int i = 0; i < count; i++)
	{
		CControlMe *item = controls[i];
		if (item->IsVisible())
		{
			if (item->IsTopMost())
			{
				sortedControls->push_back(item);
			}
			else
			{
				sortedControls->insert(sortedControls->begin() + index, item);
				index++;
			}
		}
	}
	return (int)sortedControls->size() > 0;
}

void CNativeBaseMe::GetTabStopControls( CControlMe *control, vector<CControlMe*> *tabStopControls )
{
	vector<CControlMe*> controls = control->GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *item = controls[i];
		if (!item->IsWindow())
		{
			if (item->IsEnabled() && item->IsTabStop())
			{
				tabStopControls->push_back(item);
			}
			GetTabStopControls(item, tabStopControls);
		}
	}
}

bool CNativeBaseMe::IsPaintEnabled( CControlMe *control )
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

void CNativeBaseMe::RenderControls( const RECT& rect, vector<CControlMe*> *controls, String resourcePath, float opacity )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *control = (*controls)[i];
		control->OnPrePaint(m_paint, control->GetDisplayRect());
		RECT lpDestRect;
		int left = ClientX(control);
		int top = ClientY(control);
		RECT rect3 = {left, top, left + control->GetWidth(), top + control->GetHeight()};
		if (control->UseRegion())
		{
			RECT region = control->GetRegion();
			rect3.left += region.left;
			rect3.top += region.top;
			rect3.right = rect3.left + region.right - region.left;
			rect3.bottom = rect3.top + region.bottom - region.top;
		}
		if (control->IsVisible() && (m_host->GetIntersectRect(&lpDestRect, &rect, &rect3) > 0))
		{
			RECT clipRect = {lpDestRect.left - left, lpDestRect.top - top, lpDestRect.right - left, lpDestRect.bottom - top};
			String str = control->GetResourcePath();
			if ((int)str.size() == 0)
			{
				str = resourcePath;
			}
			float num5 = control->GetOpacity() * opacity;
			SetPaint(left, top, clipRect, str, num5);
			control->OnPaint(m_paint, clipRect);
			vector<CControlMe*> sortedControls;
			GetSortedControls(control, &sortedControls);
			if ((int)sortedControls.size() > 0)
			{
				RenderControls(lpDestRect, &sortedControls, str, num5);
				sortedControls.clear();
			}
			SetPaint(left, top, clipRect, str, num5);
			control->OnPaintBorder(m_paint, clipRect);
		}
	}
}

void CNativeBaseMe::SetCursor( CControlMe *control )
{
	CursorsMe cursor = control->GetCursor();
	if (!IsPaintEnabled(control))
	{
		cursor = CursorsMe_Arrow;
	}
	if (GetCursor() != cursor)
	{
		SetCursor(cursor);
	}
}

void CNativeBaseMe::SetPaint( int offsetX, int offsetY, const RECT& clipRect, String resourcePath, float opacity )
{
	if (m_paint)
	{
		POINT pt = {offsetX, offsetY};
		m_paint->SetOffset(pt);
		m_paint->SetClip(clipRect);
		m_paint->SetResourcePath(resourcePath);
		m_paint->SetOpacity(opacity);
	}
}

CNativeBaseMe::CNativeBaseMe()
{
	m_allowScaleSize = false;
	m_displaySize.cx = 0;
	m_displaySize.cy = 0;
	m_drawBeginPoint.x = 0;
	m_drawBeginPoint.y = 0;
	m_dragBeginRect.bottom = 0;
	m_dragBeginRect.left = 0;
	m_dragBeginRect.right = 0;
	m_dragBeginRect.top = 0;
	m_dragStartOffset.x = 0;
	m_dragStartOffset.y = 0;
	m_exportingControl = 0;
	m_host = new CWinHostMe();
	m_host->SetNative(this);
	m_mirrorHost = 0;
	m_mirrorMode = MirrorMode_None;
	m_opacity = 1.0f;
	m_paint = new CGdiPaintMe();
	m_mouseDownPoint.x = 0;
	m_mouseDownPoint.y = 0;
	m_resourcePath = L"";
	m_rotateAngle = 0;
	m_scaleSize.cx = 0;
	m_scaleSize.cy = 0;
	m_draggingControl = 0;
	m_focusedControl = 0;
	m_mouseDownControl = 0;
	m_mouseMoveControl = 0;
}

CNativeBaseMe::~CNativeBaseMe()
{
	if (m_host)
	{
		delete m_host;
		m_host = 0;
	}
	m_mirrorHost = 0;
	if (m_paint)
	{
		delete m_paint;
		m_paint = 0;
	}
	m_rotateAngle = 0;
	m_draggingControl = 0;
	m_exportingControl = 0;
	m_focusedControl = 0;
	m_mouseDownControl = 0;
	m_mouseMoveControl = 0;
	m_timers.clear();
	ClearControls();
}

bool CNativeBaseMe::AllowScaleSize()
{
	return m_allowScaleSize;
}

void CNativeBaseMe::SetAllowScaleSize( bool allowScaleSize )
{
	m_allowScaleSize = allowScaleSize;
}

CursorsMe CNativeBaseMe::GetCursor()
{
	if (m_host)
	{
		return m_host->GetCursor();
	}
	return CursorsMe_Arrow;
}

void CNativeBaseMe::SetCursor( CursorsMe cursor )
{
	if (m_host)
	{
		m_host->SetCursor(cursor);
	}
}

SIZE CNativeBaseMe::GetDisplaySize()
{
	return m_displaySize;
}

void CNativeBaseMe::SetDisplaySize( SIZE displaySize )
{
	m_displaySize = displaySize;
}

CControlMe* CNativeBaseMe::GetFocusedControl()
{
	return m_focusedControl;
}

void CNativeBaseMe::SetFocusedControl( CControlMe *focusedControl )
{
	if (m_focusedControl != focusedControl)
	{
		if (m_focusedControl)
		{
			CControlMe *la = m_focusedControl;
			m_focusedControl = 0;
			la->OnLostFocus();
		}
		m_focusedControl = focusedControl;
		if (m_focusedControl)
		{
			m_focusedControl->OnGotFocus();
		}
	}
}

CControlHostMe* CNativeBaseMe::GetHost()
{
	return m_host;
}

void CNativeBaseMe::SetHost( CControlHostMe *host )
{
	m_host = host;
}

CControlMe* CNativeBaseMe::GetHoveredControl()
{
	return m_mouseMoveControl;
}

CNativeBaseMe* CNativeBaseMe::GetMirrorHost()
{
	return m_mirrorHost;
}

MirrorMode CNativeBaseMe::GetMirrorMode()
{
	return m_mirrorMode;
}

void CNativeBaseMe::SetMirrorMode( MirrorMode mirrorMode )
{
	m_mirrorMode = mirrorMode;
}

POINT CNativeBaseMe::GetMousePoint()
{
	if (m_host)
	{
		return m_host->GetMousePoint();
	}
	POINT pt = {0, 0};
	return pt;
}

float CNativeBaseMe::GetOpacity()
{
	return m_opacity;
}

void CNativeBaseMe::SetOpacity( float opacity )
{
	m_opacity = opacity;
}

CPaintMe* CNativeBaseMe::GetPaint()
{
	return m_paint;
}

void CNativeBaseMe::SetPaint( CPaintMe *paint )
{
	m_paint = paint;
}

CControlMe* CNativeBaseMe::GetPushedControl()
{
	return m_mouseDownControl;
}

String CNativeBaseMe::GetResourcePath()
{
	return m_resourcePath;
}

void CNativeBaseMe::SetResourcePath( const String& resourcePath )
{
	m_resourcePath = resourcePath;
}

int CNativeBaseMe::GetRotateAngle()
{
	return m_rotateAngle;
}

void CNativeBaseMe::SetRotateAngle( int rotateAngle )
{
	m_rotateAngle = rotateAngle;
}

SIZE CNativeBaseMe::GetScaleSize()
{
	return m_scaleSize;
}

void CNativeBaseMe::SetScaleSize( SIZE scaleSize )
{
	m_scaleSize = scaleSize;
}

void CNativeBaseMe::AddControl( CControlMe *control )
{
	control->SetNative(this);
	m_controls.push_back(control);
	control->OnAdd();
}

void CNativeBaseMe::AddMirror( CNativeBaseMe *mirrorHost, CControlMe *control )
{
	m_mirrorHost = mirrorHost;
	m_mirrorHost->m_mirrors.push_back(this);
	control->SetNative(this);
	m_controls.push_back(control);
}

void CNativeBaseMe::BringToFront( CControlMe *control )
{
	CControlMe *parent = control->GetParent();
	if (parent)
	{
		parent->BringChildToFront(control);
	}
	else
	{
		int size = (int)m_controls.size();
		if(size > 0)
		{
			for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
			{
				if (*it == control)
				{
					m_controls.erase(it);
					break;
				}
			}
			m_controls.push_back(control);
		}
	}
}

void CNativeBaseMe::CancelDragging()
{
	if (m_draggingControl)
	{
		m_draggingControl->SetBounds(m_dragBeginRect);
		CControlMe *la = m_draggingControl;
		m_draggingControl = 0;
		la->OnDragEnd();
		CControlMe *parent = la->GetParent();
		if (parent)
		{
			parent->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
}

void CNativeBaseMe::ClearControls()
{
	vector<CControlMe*> controls;
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		controls.push_back(*it);
	}

	for (vector<CControlMe*>::iterator it = controls.begin(); it != controls.end(); it++)
	{
		(*it)->OnRemove();
		delete *it;
		*it = 0;
	}
	controls.clear();
	m_controls.clear();
}

int CNativeBaseMe::ClientX( CControlMe *control )
{
	if (!control)
	{
		return 0;
	}
	CControlMe *parent = control->GetParent();
	int left = control->GetLeft();
	if (control == m_exportingControl)
	{
		left = 0;
	}
	if (!parent)
	{
		return left;
	}
	if (m_mirrorMode != MirrorMode_None)
	{
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			if (m_controls[i] == control)
			{
				return left;
			}
		}
	}
	return (left - (control->DisplayOffset() ? parent->GetDisplayOffset().x : 0) + ClientX(parent));
}

int CNativeBaseMe::ClientY( CControlMe *control )
{
	if (!control)
	{
		return 0;
	}
	CControlMe *parent = control->GetParent();
	int top = control->GetTop();
	if (control == m_exportingControl)
	{
		top = 0;
	}
	if (!parent)
	{
		return top;
	}
	if (m_mirrorMode != MirrorMode_None)
	{
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			if (m_controls[i] == control)
			{
				return top;
			}
		}
	}
	return (top - (control->DisplayOffset() ? parent->GetDisplayOffset().y : 0) + ClientY(parent));
}

bool CNativeBaseMe::ContainsControl( CControlMe *control )
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

void CNativeBaseMe::ExportToImage( const String& exportPath )
{
	ExportToImage(exportPath, 0);
}

void CNativeBaseMe::ExportToImage( const String& exportPath, CControlMe *control )
{
	m_exportingControl = control;
	if (control)
	{
		vector<CControlMe*> controls;
		controls.push_back(control);
		RECT rect = {0, 0, control->GetWidth(), control->GetHeight()};
		m_paint->BeginExport(exportPath, rect);
		RenderControls(rect, &controls, GetPaintingResourcePath(control), GetPaintingOpacity(control));
		m_paint->EndExport();
	}
	else
	{
		RECT rect2 = {0, 0, m_displaySize.cx, m_displaySize.cy};
		m_paint->BeginExport(exportPath, rect2);
		vector<CControlMe*> sortedControls;
		GetSortedControls(0, &sortedControls);
		RenderControls(rect2, &sortedControls, m_resourcePath, m_opacity);
		sortedControls.clear();
		m_paint->EndExport();
	}
	m_exportingControl = 0;
}

CControlMe* CNativeBaseMe::FindControl( const POINT& mp )
{
	vector<CControlMe*> sortedControls;
	if(GetSortedControls(0, &sortedControls))
	{
		return FindControl(mp, &sortedControls);
	}
	return 0;
}

CControlMe* CNativeBaseMe::FindControl( const POINT& mp, CControlMe *parent )
{
	vector<CControlMe*> subControls;
	if(GetSortedControls(parent, &subControls))
	{
		return FindControl(mp, &subControls);
	}
	return 0;
}

CControlMe* CNativeBaseMe::FindControl( const String& name )
{
	return FindControl(name, &m_controls);
}

vector<CControlMe*> CNativeBaseMe::GetControls()
{
	return m_controls;
}

void CNativeBaseMe::InsertControl( int index, CControlMe *control )
{
	m_controls.insert(m_controls.begin() + index, control);
}

void CNativeBaseMe::Invalidate()
{
	if (m_host)
	{
		m_host->Invalidate();
	}
}

void CNativeBaseMe::Invalidate( CControlMe *control )
{
	if (m_host)
	{
		int left = ClientX(control);
		int top = ClientY(control);
		RECT rc = {left, top, left + control->GetWidth(), top + control->GetHeight()};
		m_host->Invalidate(rc);
		vector<CNativeBaseMe*> mirrors;
		if (m_mirrorMode == MirrorMode_Shadow)
		{
			left = m_mirrorHost->ClientX(control);
			top = m_mirrorHost->ClientY(control);
			RECT rect = {left, top, left + control->GetWidth(), top + control->GetHeight()};
			m_mirrorHost->GetHost()->Invalidate(rect);
			mirrors = m_mirrorHost->m_mirrors;
		}
		else
		{
			mirrors = m_mirrors;
		}
		int count = (int)mirrors.size();
		for (int i = 0; i < count; i++)
		{
			if (mirrors[i] != this && mirrors[i]->GetMirrorMode() != MirrorMode_BugHole)
			{
				left = mirrors[i]->ClientX(control);
				top = mirrors[i]->ClientY(control);
				RECT rect = {left, top, left + control->GetWidth(), top + control->GetHeight()};
				m_mirrorHost->GetHost()->Invalidate(rect);
			}
		}
	}
}

void CNativeBaseMe::Invalidate( const RECT& rect )
{
	if (m_host)
	{
		m_host->Invalidate(rect);
	}
}

bool CNativeBaseMe::OnChar( wchar_t key )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		if (focusedControl->IsTabStop())
		{
			CControlMe *control = FindWindow(focusedControl);
			if (control && !m_host->IsKeyPress(0x10) && !m_host->IsKeyPress(0x11) && key == L'\t')
			{
				vector<CControlMe*> tabStopControls;
				GetTabStopControls(control, &tabStopControls);
				int count = (int)tabStopControls.size();
				if (count > 0)
				{
					for (int i = 0; i < (count - 1); i++)
					{
						for (int j = 0; j < (count - 1 - i); j++)
						{
							CControlMe *la3 = tabStopControls[j];
							CControlMe *la4 = tabStopControls[j + 1];
							if (la3->GetTabIndex() > la4->GetTabIndex())
							{
								CControlMe *la5 = tabStopControls[j + 1];
								tabStopControls[j + 1] = tabStopControls[j];
								tabStopControls[j] = la5;
							}
						}
					}
					bool flag = false;
					CControlMe *la6 = 0;
					for (int k = 0; k < count; k++)
					{
						CControlMe *la7 = tabStopControls[k];
						if (focusedControl == la7)
						{
							if (k < count - 1)
							{
								la6 = tabStopControls[k + 1];
							}
							else
							{
								la6 = tabStopControls[0];
							}
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						la6 = tabStopControls[0];
					}
					if (la6 != focusedControl)
					{
						la6->SetFocused(true);
						focusedControl = la6;
						focusedControl->OnTabStop();
						control->Invalidate();
						return true;
					}
				}
			}
		}
		focusedControl->OnChar(key);
	}
	return false;
}

void CNativeBaseMe::OnDoubleClick( MouseButtonsMe button, int clicks, int delta )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		POINT mousePoint = GetMousePoint();
		int left = ClientX(focusedControl);
		int top = ClientY(focusedControl);
		POINT mp = {mousePoint.x - left, mousePoint.y - top};
		focusedControl->OnDoubleClick(mp, button, clicks, delta);
	}
}

void CNativeBaseMe::OnKeyDown( char key )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		focusedControl->OnKeyDown(key);
	}
}

void CNativeBaseMe::OnKeyUp( char key )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		focusedControl->OnKeyUp(key);
	}
}

void CNativeBaseMe::OnMouseDown( MouseButtonsMe button, int clicks, int delta )
{
	m_draggingControl = 0;
	m_mouseDownControl = 0;
	POINT mousePoint = GetMousePoint();
	m_mouseDownPoint = mousePoint;
	vector<CControlMe*> sortedControls;
	GetSortedControls(0, &sortedControls);
	CControlMe *control = FindControl(mousePoint, &sortedControls);
	if (control)
	{
		CControlMe *la2 = FindWindow(control);
		if (la2 && la2->IsWindow())
		{
			la2->BringToFront();
		}
		if (IsPaintEnabled(control))
		{
			int left = ClientX(control);
			int top = ClientY(control);
			POINT mp = {mousePoint.x - left, mousePoint.y - top};
			CControlMe *focusedControl = GetFocusedControl();
			m_mouseDownControl = control;
			if (focusedControl == GetFocusedControl())
			{
				if (control->CanFocus())
				{
					if (button == MouseButtonsMe_Left)
					{
						SetFocusedControl(control);
					}
				}
				else
				{
					SetFocusedControl(0);
				}
			}
			if (!OnPreviewsMouseEvent(EVENTID::MOUSEDOWN, m_mouseDownControl, mousePoint, button, clicks, delta))
			{
				if (m_mouseDownControl)
				{
					m_mouseDownControl->OnMouseDown(mp, button, clicks, delta);
					if (m_mouseDownControl)
					{
						m_mouseDownControl->OnDragReady(&m_dragStartOffset);
					}
				}
			}
		}
	}
}

void CNativeBaseMe::OnMouseLeave( MouseButtonsMe button, int clicks, int delta )
{
	if (m_mouseMoveControl && IsPaintEnabled(m_mouseMoveControl))
	{
		POINT mousePoint = GetMousePoint();
		POINT mp = {mousePoint.x - ClientX(m_mouseMoveControl), mousePoint.y - ClientY(m_mouseMoveControl)};
		CControlMe *control = m_mouseMoveControl;
		m_mouseMoveControl = 0;
		if (!OnPreviewsMouseEvent(EVENTID::MOUSELEAVE, m_mouseDownControl, mousePoint, button, clicks, delta))
		{
			control->OnMouseLeave(mp, button, clicks, delta);
		}
	}
}

void CNativeBaseMe::OnMouseMove( MouseButtonsMe button, int clicks, int delta )
{
	POINT mousePoint = GetMousePoint();
	if (m_mouseDownControl)
	{
		if (!OnPreviewsMouseEvent(EVENTID::MOUSEMOVE, m_mouseDownControl, mousePoint, button, clicks, delta))
		{
			POINT mp = {mousePoint.x - ClientX(m_mouseDownControl), mousePoint.y - ClientY(m_mouseDownControl)};
			m_mouseDownControl->OnMouseMove(mp, button, clicks, delta);
			SetCursor(m_mouseDownControl);
			if (((m_mouseDownControl->AllowDrag() && button == MouseButtonsMe_Left && clicks == 1) 
				&& ((abs((int) (mousePoint.x - m_mouseDownPoint.x)) > m_dragStartOffset.x) 
				|| (abs((int) (mousePoint.y - m_mouseDownPoint.y)) > m_dragStartOffset.y))) 
				&& m_mouseDownControl->OnDragBegin())
			{
				m_dragBeginRect = m_mouseDownControl->GetBounds();
				m_drawBeginPoint = m_mouseDownPoint;
				m_draggingControl = m_mouseDownControl;
				m_mouseDownControl = 0;
				CControlMe *parent = m_draggingControl->GetParent();
				if (parent)
				{
					parent->Invalidate();
				}
				else
				{
					Invalidate();
				}
			}
		}
	}
	else if (m_draggingControl)
	{
		CControlMe *la2 = m_draggingControl;
		int num = mousePoint.x - m_drawBeginPoint.x;
		int num2 = mousePoint.y - m_drawBeginPoint.y;
		RECT rect = m_dragBeginRect;
		rect.left += num;
		rect.top += num2;
		rect.right += num;
		rect.bottom += num2;
		la2->SetBounds(rect);
		la2->OnDragging();
		CControlMe *la3 = la2->GetParent();
		if (la3)
		{
			la3->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
	else
	{
		vector<CControlMe*> sortedControls;
		GetSortedControls(0, &sortedControls);
		CControlMe *control = FindControl(mousePoint, &sortedControls);
		if(control && OnPreviewsMouseEvent(EVENTID::MOUSEMOVE, control, mousePoint, button, clicks, delta))
		{
			return;
		}
		sortedControls.clear();
		if (m_mouseMoveControl != control)
		{
			if ((m_mouseMoveControl && IsPaintEnabled(m_mouseMoveControl)) && !m_mouseDownControl)
			{
				POINT point3 = {mousePoint.x - ClientX(m_mouseMoveControl), mousePoint.y - ClientY(m_mouseMoveControl)};
				CControlMe *la5 = m_mouseMoveControl;
				m_mouseMoveControl = control;
				la5->OnMouseLeave(point3, button, clicks, delta);
			}
			if ((control && IsPaintEnabled(control)) && !m_mouseDownControl)
			{
				POINT point4 = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
				m_mouseMoveControl = control;
				control->OnMouseEnter(point4, button, clicks, delta);
				control->OnMouseMove(point4, button, clicks, delta);
				SetCursor(control);
			}
		}
		else if (control && IsPaintEnabled(control))
		{
			POINT point5 = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
			m_mouseMoveControl = control;
			control->OnMouseMove(point5, button, clicks, delta);
			SetCursor(control);
		}
	}
}

void CNativeBaseMe::OnMouseUp( MouseButtonsMe button, int clicks, int delta )
{
	POINT mousePoint = GetMousePoint();
	vector<CControlMe*> sortedControls;
	GetSortedControls(0, &sortedControls);
	if (m_mouseDownControl)
	{
		CControlMe *control = m_mouseDownControl;
		if (OnPreviewsMouseEvent(EVENTID::MOUSEUP, control, mousePoint, button, clicks, delta))
		{
			m_mouseDownControl = 0;
			return;
		}
		if (m_mouseDownControl)
		{
			control = m_mouseDownControl;
			CControlMe *la2 = FindControl(mousePoint, &sortedControls);
			POINT mp = {mousePoint.x - ClientX(control), mousePoint.y - ClientY(control)};
			if (la2 && la2 == control)
			{
				control->OnClick(mp, button, clicks, delta);
			}
			else
			{
				m_mouseMoveControl = 0;
			}
			if (m_mouseDownControl != 0)
			{
				control = m_mouseDownControl;
				m_mouseDownControl = 0;
				control->OnMouseUp(mp, button, clicks, delta);
			}
		}
	}
	else if (m_draggingControl)
	{
		POINT point3 = {mousePoint.x - ClientX(m_mouseDownControl), mousePoint.y - ClientY(m_mouseDownControl)};
		CControlMe *la3 = m_draggingControl;
		m_draggingControl = 0;
		if (OnPreviewsMouseEvent(EVENTID::MOUSEUP, la3, mousePoint, button, clicks, delta))
		{
			return;
		}
		la3->OnMouseUp(point3, button, clicks, delta);
		la3->OnDragEnd();
		CControlMe *parent = la3->GetParent();
		if (parent)
		{
			parent->Invalidate();
		}
		else
		{
			Invalidate();
		}
	}
	sortedControls.clear();
}

void CNativeBaseMe::OnMouseWheel( MouseButtonsMe button, int clicks, int delta )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		POINT mousePoint = GetMousePoint();
		if (!OnPreviewsMouseEvent(EVENTID::MOUSEWHEEL, focusedControl, mousePoint, button, clicks, delta))
		{
			mousePoint.x -= ClientX(focusedControl);
			mousePoint.y -= ClientY(focusedControl);
			focusedControl->OnMouseWheel(mousePoint, button, clicks, delta);
		}
	}
}

void CNativeBaseMe::OnPaint( const RECT& clipRect )
{
	vector<CControlMe*> sortedControls;
	GetSortedControls(0, &sortedControls);
	RenderControls(clipRect, &sortedControls, m_resourcePath, m_opacity);
	sortedControls.clear();
}

bool CNativeBaseMe::OnPreviewsKeyEvent( int eventID, char key )
{
	CControlMe *focusedControl = GetFocusedControl();
	if (focusedControl && IsPaintEnabled(focusedControl))
	{
		CControlMe *la2 = FindWindow(focusedControl);
		if (la2)
		{
			return la2->OnPreviewsKeyEvent(eventID, key);
		}
	}
	return false;
}

bool CNativeBaseMe::OnPreviewsMouseEvent( int eventID, CControlMe *control, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe *la = FindPreviewsControl(control);
	if (la)
	{
		int x = ClientX(la);
		int y = ClientY(la);
		POINT point = {mp.x - x, mp.y - y};
		if (la->OnPreviewsMouseEvent(eventID, point, button, clicks, delta))
		{
			return true;
		}
	}
	return false;
}

void CNativeBaseMe::OnResize()
{
	Update();
}

void CNativeBaseMe::OnTimer( int timerID )
{
	map<int, CControlMe*>::iterator it = m_timers.find(timerID);
	if (it != m_timers.end())
	{
		it->second->OnTimer(timerID);
	}
	for (vector<CNativeBaseMe*>::iterator it = m_mirrors.begin(); it != m_mirrors.end(); it++)
	{
		(*it)->OnTimer(timerID);
	}
}

void CNativeBaseMe::RemoveControl( CControlMe *control )
{
	if (control == m_draggingControl)
	{
		m_draggingControl = 0;
	}
	if (control == m_focusedControl)
	{
		m_focusedControl = 0;
	}
	if (control == m_mouseDownControl)
	{
		m_mouseDownControl = 0;
	}
	if (control == m_mouseMoveControl)
	{
		m_mouseMoveControl = 0;
	}
	for (map<int, CControlMe*>::iterator it = m_timers.begin(); it != m_timers.end(); it++)
	{
		if (it->second == control)
		{
			it->second->StopTimer(it->first);
			break;
		}
	}

	if (!control->GetParent())
	{
		for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
		{
			if (*it == control)
			{
				m_controls.erase(it);
				break;
			}
		}
		control->OnRemove();
	}
}

void CNativeBaseMe::RemoveMirror( CControlMe *control )
{
	for (vector<CNativeBaseMe*>::iterator iter = m_mirrorHost->m_mirrors.begin(); iter != m_mirrorHost->m_mirrors.end(); iter++)
	{
		if (*iter == this)
		{
			m_mirrorHost->m_mirrors.erase(iter);
			break;
		}
	}
	for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
	{
		if (*it == control)
		{
			m_controls.erase(it);
			break;
		}
	}
	control->SetNative(m_mirrorHost);
}

void CNativeBaseMe::SendToBack( CControlMe *control )
{
	CControlMe *parent = control->GetParent();
	if (parent)
	{
		parent->SendChildToBack(control);
	}
	else
	{
		for (vector<CControlMe*>::iterator it = m_controls.begin(); it != m_controls.end(); it++)
		{
			if (*it == control)
			{
				m_controls.erase(it);
				break;
			}
		}
		m_controls.insert(m_controls.begin(), control);
	}
}

void CNativeBaseMe::SetAlign( vector<CControlMe*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *la = (*controls)[i];
		if (la->DisplayOffset())
		{
			SIZE size = m_displaySize;
			CControlMe *parent = la->GetParent();
			if (parent && (m_mirrorMode != MirrorMode_BugHole))
			{
				size = parent->GetSize();
			}
			SIZE size2 = la->GetSize();
			PADDING margin = la->GetMargin();
			PADDING padding;
			if (parent)
			{
				padding = parent->GetPadding();
			}
			if (la->GetAlign() == HorizontalAlignMe_Center)
			{
				la->SetLeft((size.cx - size2.cx) / 2);
			}
			else if (la->GetAlign() == HorizontalAlignMe_Right)
			{
				la->SetLeft(size.cx - size2.cx - margin.right - padding.right);
			}
			if (la->GetVerticalAlign() == VerticalAlignMe_Bottom)
			{
				la->SetTop(size.cy - size2.cy - margin.bottom - padding.bottom);
			}
			else if (la->GetVerticalAlign() == VerticalAlignMe_Middle)
			{
				la->SetTop((size.cy - size2.cy) / 2);
			}
		}
	}
}

void CNativeBaseMe::SetAnchor( vector<CControlMe*> *controls, SIZE oldSize )
{
	if ((oldSize.cx != 0) && (oldSize.cy != 0))
	{
		int count = (int)controls->size();
		for (int i = 0; i < count; i++)
		{
			CControlMe *la = controls->at(i);
			SIZE displaySize = m_displaySize;
			CControlMe *parent = la->GetParent();
			if (parent && m_mirrorMode != MirrorMode_BugHole)
			{
				displaySize = parent->GetSize();
			}
			ANCHOR anchor = la->GetAnchor();
			RECT bounds = la->GetBounds();
			if (anchor.right && !anchor.left)
            {
                bounds.left = bounds.left + displaySize.cx - oldSize.cx;
            }
            if (anchor.bottom && !anchor.top)
            {
                bounds.top = bounds.top + displaySize.cy - oldSize.cy;
            }
            if (anchor.right)
            {
                bounds.right = bounds.right + displaySize.cx - oldSize.cx;
            }
            if (anchor.bottom)
            {
                bounds.bottom = bounds.bottom + displaySize.cy - oldSize.cy;
            }
			la->SetBounds(bounds);
		}
	}
}

void CNativeBaseMe::SetDock( vector<CControlMe*> *controls )
{
	int count = (int)controls->size();
	for (int i = 0; i < count; i++)
	{
		CControlMe *la = (*controls)[i];
		SIZE size = m_displaySize;
		CControlMe *parent = la->GetParent();
		if (parent && m_mirrorMode != MirrorMode_BugHole)
		{
			size = parent->GetSize();
		}
		DockStyleMe dock = la->GetDock();
		if (dock != DockStyleMe_None)
		{
			PADDING padding;
			if (parent)
			{
				padding = parent->GetPadding();
			}
			PADDING margin = la->GetMargin();
			SIZE cSize = la->GetSize();
			RECT spaceRect;
			spaceRect.left = padding.left + margin.left;
			spaceRect.top = padding.top + margin.top;
			spaceRect.right = size.cx - padding.right - margin.right;
			spaceRect.bottom = size.cy - padding.bottom - margin.bottom;
			RECT bounds;
			switch (dock)
            {
                case DockStyleMe_Bottom:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.bottom - size.cy;
                    bounds.right = spaceRect.right;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleMe_Fill:
                    bounds = spaceRect;
                    break;
                case DockStyleMe_Left:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.top;
                    bounds.right = bounds.left + size.cx;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleMe_Right:
                    bounds.left = spaceRect.right - size.cx;
                    bounds.top = spaceRect.top;
                    bounds.right = spaceRect.right;
                    bounds.bottom = spaceRect.bottom;
                    break;
                case DockStyleMe_Top:
                    bounds.left = spaceRect.left;
                    bounds.top = spaceRect.top;
                    bounds.right = spaceRect.right;
                    bounds.bottom = bounds.top + size.cy;
                    break;
            }
			la->SetBounds(bounds);
		}
	}
}

void CNativeBaseMe::StartTimer( CControlMe *control, int timerID, int interval )
{
	m_timers[timerID] = control;
	if (m_host)
	{
		m_host->StartTimer(timerID, interval);
	}
}

void CNativeBaseMe::StopTimer( int timerID )
{
	map<int, CControlMe*>::iterator it = m_timers.find(timerID);
	if (it != m_timers.end())
	{
		if (m_host)
		{
			m_host->StopTimer(timerID);
		}
		m_timers.erase(it);
	}
}

void CNativeBaseMe::Update()
{
	if (m_host)
	{
		SIZE size = m_displaySize;
		m_displaySize = m_host->GetSize();
		if ((m_displaySize.cx != 0) && (m_displaySize.cy != 0))
		{
			SetAlign(&m_controls);
			SetAnchor(&m_controls, size);
			SetDock(&m_controls);
			int size = (int)m_controls.size();
			for (int i = 0; i < size; i++)
			{
				m_controls[i]->Update();
			}
		}
	}
}