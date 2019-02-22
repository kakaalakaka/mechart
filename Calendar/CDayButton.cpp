#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CDayButton.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 CDayButtonMe::GetPaintingBackColor()
{
	if (m_selected)
	{
		return COLOR_PUSHEDCONTROL;
	}
	if (m_inThisMonth)
	{
		return COLOR_HOVEREDCONTROL;
	}
	return COLOR_CONTROL;
}

_int64 CDayButtonMe::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 CDayButtonMe::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CDayButtonMe::CDayButtonMe(CCalendarMe *calendar)
{
	m_bounds.left = 0;
	m_bounds.top = 0;
	m_bounds.right = 0;
	m_bounds.bottom = 0;
	m_calendar = calendar;
	m_day = 0;
	m_selected = false;
	m_inThisMonth = false;
	m_visible = true;
}

CDayButtonMe::~CDayButtonMe()
{
	m_calendar = 0;
}

RECT CDayButtonMe::GetBounds()
{
	return m_bounds;
}

void CDayButtonMe::SetBounds(const RECT& bounds)
{
	m_bounds = bounds;
}

CCalendarMe* CDayButtonMe::GetCalendar()
{
	return m_calendar;
}

void CDayButtonMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

CDayMe* CDayButtonMe::GetDay()
{
	return m_day;
}

void CDayButtonMe::SetDay(CDayMe *day)
{
	m_day = day;
}

bool CDayButtonMe::InThisMonth()
{
	return m_inThisMonth;
}

void CDayButtonMe::SetThisMonth(bool inThisMonth)
{
	m_inThisMonth = inThisMonth;
}

bool CDayButtonMe::IsSelected()
{
	return m_selected;
}

void CDayButtonMe::SetSelected(bool selected)
{
	m_selected = selected;
}

bool CDayButtonMe::IsVisible()
{
	return m_visible;
}

void CDayButtonMe::SetVisible(bool visible)
{
	m_visible = visible;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDayButtonMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	if (m_calendar && m_day)
	{
		m_calendar->SetSelectedDay(m_day);
	}
}

void CDayButtonMe::OnPaintBackGround(CPaintMe *paint, const RECT& clipRect)
{
	_int64 paintingBackColor = GetPaintingBackColor();
	paint->FillRect(paintingBackColor, m_bounds);
}

void CDayButtonMe::OnPaintBorder(CPaintMe *paint, const RECT& clipRect)
{
	_int64 paintingBorderColor = GetPaintingBorderColor();
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.left, m_bounds.bottom - 1, 
		m_bounds.right - 1, m_bounds.bottom - 1);
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.right - 1, m_bounds.top,
		m_bounds.right - 1, m_bounds.bottom - 1);
}

void CDayButtonMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	if (m_day)
	{
		int width = m_bounds.right - m_bounds.left;
		int height = m_bounds.bottom - m_bounds.top;
		String text = CStrMe::ConvertIntToStr(m_day->GetDay());
		FONT *font = m_calendar->GetFont();
		SIZE size = paint->TextSize(text.c_str(), font);
		RECT rect;
		rect.left = m_bounds.left + ((width - size.cx) / 2);
		rect.top = m_bounds.top + ((height - size.cy) / 2);
		rect.right = rect.left + size.cx;
		rect.bottom = rect.top + size.cy;
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}