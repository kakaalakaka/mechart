#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CYearButton.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 CYearButtonMe::GetPaintingBackColor()
{
	return COLOR_CONTROL;
}

_int64 CYearButtonMe::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 CYearButtonMe::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CYearButtonMe::CYearButtonMe(CCalendarMe *calendar)
{
	m_bounds.left = 0;
	m_bounds.top = 0;
	m_bounds.right = 0;
	m_bounds.bottom = 0;
	m_calendar = calendar;
	m_visible = true;
	m_year = 0;
}

CYearButtonMe::~CYearButtonMe()
{
	m_calendar = 0;
}

RECT CYearButtonMe::GetBounds()
{
	return m_bounds;
}

void CYearButtonMe::SetBounds(const RECT& bounds)
{
	m_bounds = bounds;
}

CCalendarMe* CYearButtonMe::GetCalendar()
{
	return m_calendar;
}

void CYearButtonMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

bool CYearButtonMe::IsVisible()
{
	return m_visible;
}

void CYearButtonMe::SetVisible(bool visible)
{
	m_visible = visible;
}

int CYearButtonMe::GetYear()
{
	return m_year;
}

void CYearButtonMe::SetYear(int year)
{
	m_year = year;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CYearButtonMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	if (m_calendar)
	{
		m_calendar->SetMode(CalendarMode_Month);
		m_calendar->GetMonthDiv()->SelectYear(m_year);
		m_calendar->Update();
		m_calendar->Invalidate();
	}
}

void CYearButtonMe::OnPaintBackGround(CPaintMe *paint, const RECT& clipRect)
{
	_int64 paintingBackColor = GetPaintingBackColor();
	paint->FillRect(paintingBackColor, m_bounds);
}

void CYearButtonMe::OnPaintBorder(CPaintMe *paint, const RECT& clipRect)
{
	_int64 paintingBorderColor = GetPaintingBorderColor();
	paint->DrawLine(paintingBorderColor, 1, 0, 
		m_bounds.left, 
		m_bounds.bottom - 1, 
		m_bounds.right - 1, 
		m_bounds.bottom - 1);
	paint->DrawLine(paintingBorderColor, 1, 0,
		m_bounds.right - 1, 
		m_bounds.top,
		m_bounds.right - 1, 
		m_bounds.bottom - 1);
}

void CYearButtonMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	int width = m_bounds.right - m_bounds.left;
	int height = m_bounds.bottom - m_bounds.top;
	String text = CStrMe::ConvertIntToStr(m_year);
	FONT *font = m_calendar->GetFont();
	SIZE size = paint->TextSize(text.c_str(), font);
	RECT rect;
	rect.left = m_bounds.left + (width - size.cx) / 2;
	rect.top = m_bounds.top + (height - size.cy) / 2;
	rect.right = rect.left + size.cx;
	rect.bottom = rect.top + size.cy;
	paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
}