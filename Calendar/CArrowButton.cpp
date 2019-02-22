#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CArrowButton.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CArrowButtonMe::CArrowButtonMe(CCalendarMe *calendar)
{
	m_calendar = calendar;
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SIZE size = {16, 16};
	SetSize(size);
	m_toLast = true;
}

CArrowButtonMe::~CArrowButtonMe()
{
	m_calendar = 0;
}

CCalendarMe* CArrowButtonMe::GetCalendar()
{
	return m_calendar;
}

void CArrowButtonMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

bool CArrowButtonMe::IsToLast()
{
	return m_toLast;
}

void CArrowButtonMe::SetToLast(bool toLast)
{
	m_toLast = toLast;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CArrowButtonMe::GetControlType()
{
	return L"ArrowButton";
}

void CArrowButtonMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnClick(mp, button, clicks, delta);
	if (m_calendar)
	{
		switch (m_calendar->GetMode())
		{
		case CalendarMode_Day:
			if (m_toLast)
			{
				m_calendar->GoLastMonth();
			}
			else
			{
				m_calendar->GoNextMonth();
			}
			break;

		case CalendarMode_Month:
			{
				CMonthDivMe *monthDiv = m_calendar->GetMonthDiv();
				if (monthDiv)
				{
					int year = monthDiv->GetYear();
					if (m_toLast)
					{
						monthDiv->SelectYear(year - 1);
					}
					else
					{
						monthDiv->SelectYear(year + 1);
					}
				}
				break;
			}
		case CalendarMode_Year:
			{
				CYearDivMe *yearDiv = m_calendar->GetYearDiv();
				if (yearDiv)
				{
					int startYear = yearDiv->GetStartYear();
					if (m_toLast)
					{
						yearDiv->SelectStartYear(startYear - 12);
					}
					else
					{
						yearDiv->SelectStartYear(startYear + 12);
					}
				}
				break;
			}
		}
		m_calendar->Invalidate();
	}
}

void CArrowButtonMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	POINT point = {0, 0};
	POINT point2 = {0, 0};
	POINT point3 = {0, 0};
	if (m_toLast)
	{
		point.x = 0;
		point.y = height / 2;
		point2.x = width;
		point2.y = 0;
		point3.x = width;
		point3.y = height;
	}
	else
	{
		point.x = 0;
		point.y = 0;
		point2.x = 0;
		point2.y = height;
		point3.x = width;
		point3.y = height / 2;
	}
	POINT *points = new POINT[3];
	points[0] = point;
	points[1] = point2;
	points[2] = point3;
	paint->FillPolygon(GetPaintingBackColor(), points, 3);
}