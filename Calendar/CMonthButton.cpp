#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CMonthButton.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 CMonthButtonMe::GetPaintingBackColor()
{
	return COLOR_CONTROL;
}

_int64 CMonthButtonMe::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 CMonthButtonMe::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMonthButtonMe::CMonthButtonMe(CCalendarMe *calendar)
{
	m_bounds.left = 0;
	m_bounds.top = 0;
	m_bounds.right = 0;
	m_bounds.bottom = 0;
	m_calendar = calendar;
	m_month = 0;
	m_visible = true;
	m_year = 0;
}

CMonthButtonMe::~CMonthButtonMe()
{
	m_calendar = 0;
}

CCalendarMe* CMonthButtonMe::GetCalendar()
{
	return m_calendar;
}

void CMonthButtonMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

RECT CMonthButtonMe::GetBounds()
{
	return m_bounds;
}

void CMonthButtonMe::SetBounds(const RECT& bounds)
{
	m_bounds = bounds;
}

int CMonthButtonMe::GetMonth()
{
	return m_month;
}

void CMonthButtonMe::SetMonth(int month)
{
	m_month = month;
}

bool CMonthButtonMe::IsVisible()
{
	return m_visible;
}

void CMonthButtonMe::SetVisible(bool visible)
{
	m_visible = visible;
}

int CMonthButtonMe::GetYear()
{
	return m_year;
}

void CMonthButtonMe::SetYear(int year)
{
	m_year = year;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMonthMe* CMonthButtonMe::GetMonth(int year, int month)
{
	map<int,CMonthMe*> months = m_calendar->GetYears()->GetYear(year)->Months;
	map<int,CMonthMe*>::iterator sIter = months.find(month);
	if(sIter != months.end())
	{
		return sIter->second;
	}
	return 0;
}

String CMonthButtonMe::GetMonthStr()
{
	switch (m_month)
	{
	case 1:
		return L"一月";

	case 2:
		return L"二月";

	case 3:
		return L"三月";

	case 4:
		return L"四月";

	case 5:
		return L"五月";

	case 6:
		return L"六月";

	case 7:
		return L"七月";

	case 8:
		return L"八月";

	case 9:
		return L"九月";

	case 10:
		return L"十月";

	case 11:
		return L"十一月";

	case 12:
		return L"十二月";
	}
	return L"";
}

void CMonthButtonMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	if (m_calendar)
	{
		CMonthMe *month = GetMonth(m_calendar->GetMonthDiv()->GetYear(), m_month);
		m_calendar->SetMode(CalendarMode_Day);
		map<int,CDayMe*>::iterator sIter = month->Days.find(1);
		if(sIter != month->Days.end())
		{
			m_calendar->SetSelectedDay(sIter->second);
		}
		m_calendar->Update();
		m_calendar->Invalidate();
	}
}

void CMonthButtonMe::OnPaintBackGround(CPaintMe *paint, const RECT& clipRect)
{
	__int64 paintingBackColor = GetPaintingBackColor();
	paint->FillRect(paintingBackColor, m_bounds);
}

void CMonthButtonMe::OnPaintBorder(CPaintMe *paint, const RECT& clipRect)
{
	__int64 paintingBorderColor = GetPaintingBorderColor();
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.left, m_bounds.bottom - 1,
		m_bounds.right - 1, m_bounds.bottom - 1);
	paint->DrawLine(paintingBorderColor, 1, 0, m_bounds.right - 1, m_bounds.top, 
		m_bounds.right - 1, m_bounds.bottom - 1);
}

void CMonthButtonMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	int width = m_bounds.right - m_bounds.left;
	int height = m_bounds.bottom - m_bounds.top;
	String monthStr = GetMonthStr();
	FONT *font = m_calendar->GetFont();
	SIZE size = paint->TextSize(monthStr.c_str(), font);
	RECT rect;
	rect.left = m_bounds.left + ((width - size.cx) / 2);
	rect.top = m_bounds.top + ((height - size.cy) / 2);
	rect.right = rect.left + size.cx;
	rect.bottom = rect.top + size.cy;
	paint->DrawText(monthStr.c_str(), GetPaintingForeColor(), font, rect);
}