#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CCalendar.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CCalendarMe::CCalendarMe()
{
	m_dayDiv = 0;
	m_headDiv = 0;
	m_month = 0;
	m_mode = CalendarMode_Year;
	m_monthDiv = 0;
	m_years = new CYearsMe();
	CMonthMe* month = GetMonth();
	if(month)
	{
		map<int,CDayMe*> days = month->Days;
		map<int,CDayMe*>::iterator sIter = days.find(1);
		if(sIter != days.end())
		{
			m_selectedDay = sIter->second;
		}
	}
	m_selectedDay = 0;
	m_timeDiv = 0;
	m_timerID = CControlMe::GetNewTimerID();
	m_useAnimation = false;
	m_year = 2014;
	m_yearDiv = 0;
	SIZE size = {200, 200};
	SetSize(size);
}

CCalendarMe::~CCalendarMe()
{
	if (m_dayDiv)
	{
		delete m_dayDiv;
	}
	m_dayDiv = 0;
	m_headDiv = 0;
	if (m_monthDiv)
	{
		delete m_monthDiv;
	}
	m_monthDiv = 0;
	m_selectedDay = 0;
	if (m_timeDiv)
	{
		delete m_timeDiv;
	}
	m_timeDiv = 0;
	if (m_yearDiv)
	{
		delete m_yearDiv;
	}
	m_yearDiv = 0;
	if (m_years)
	{
		delete m_years;
	}
	m_years = 0;
	StopTimer(m_timerID);
}

CDayDivMe* CCalendarMe::GetDayDiv()
{
	return m_dayDiv;
}

void CCalendarMe::SetDayDiv(CDayDivMe *dayDiv)
{
	m_dayDiv = dayDiv;
}

CHeadDivMe* CCalendarMe::GetHeadDiv()
{
	return m_headDiv;
}

void CCalendarMe::SetHeadDiv(CHeadDivMe *headDiv)
{
	m_headDiv = headDiv;
}

CalendarMode CCalendarMe::GetMode()
{
	return m_mode;
}

void CCalendarMe::SetMode(CalendarMode mode)
{ 
	if (m_mode != mode)
	{
		m_mode = mode;
		if (m_mode == CalendarMode_Month)
		{
			if (m_dayDiv)
			{
				m_dayDiv->Hide();
			}
			if (m_yearDiv)
			{
				m_yearDiv->Hide();
			}
			if (!m_monthDiv)
			{
				m_monthDiv = new CMonthDivMe(this);
			}
			if (mode == CalendarMode_Day)
			{
				m_monthDiv->SelectYear(m_year);
			}
			m_monthDiv->Show();
		}
		else if (m_mode == CalendarMode_Year)
		{
			if (m_dayDiv)
			{
				m_dayDiv->Hide();
			}
			int year = m_year;
			if (m_monthDiv)
			{
				year = m_monthDiv->GetYear();
				m_monthDiv->Hide();
			}
			if (!m_yearDiv)
			{
				m_yearDiv = new CYearDivMe(this);
			}
			m_yearDiv->SelectStartYear(year);
			m_yearDiv->Show();
		}
		else
		{
			if (m_monthDiv)
			{
				m_monthDiv->Hide();
			}
			if (m_yearDiv)
			{
				m_yearDiv->Hide();
			}
			m_dayDiv->Show();
		}
	}
}

CMonthMe* CCalendarMe::GetMonth()
{
	map<int,CMonthMe*> months = m_years->GetYear(m_year)->Months;
	map<int,CMonthMe*>::iterator sIter = months.find(m_month);
	if(sIter != months.end())
	{
		return sIter->second;
	}
	return 0;
}

void CCalendarMe::SetMonth(CMonthMe *month)
{
	m_year = month->GetYear();
	m_month = month->GetMonth();
	Update();
}

CMonthDivMe* CCalendarMe::GetMonthDiv()
{
	return m_monthDiv;
}

void CCalendarMe::SetMonthDiv(CMonthDivMe *monthDiv)
{
	m_monthDiv = monthDiv;
}

CDayMe* CCalendarMe::GetSelectedDay()
{
	return m_selectedDay;
}

void CCalendarMe::SetSelectedDay(CDayMe *day)
{
	if (m_selectedDay != day)
	{
		m_selectedDay = day;
		if (m_dayDiv)
		{
			m_dayDiv->SelectDay(m_selectedDay);
		}
		Invalidate();
		OnSelectedTimeChanged();
	}
}

CTimeDivMe* CCalendarMe::GetTimeDiv()
{
	return m_timeDiv;
}

void CCalendarMe::SetTimeDiv(CTimeDivMe *timeDiv)
{
	m_timeDiv = timeDiv;
}

bool CCalendarMe::UseAnimation()
{
	return m_useAnimation;
}

void CCalendarMe::SetUseAnimation(bool useAnimation)
{
	m_useAnimation = useAnimation;
	if (m_useAnimation)
	{
		StartTimer(m_timerID, 20);
	}
	else
	{
		StopTimer(m_timerID);
	}
}

CYearDivMe* CCalendarMe::GetYearDiv()
{
	return m_yearDiv;
}

void CCalendarMe::SetYearDiv(CYearDivMe *yearDiv)
{
	m_yearDiv = yearDiv;
}

CYearsMe* CCalendarMe::GetYears()
{
	return m_years;
}

void CCalendarMe::SetYears(CYearsMe *years)
{
	m_years = years;
	Update();
	CMonthMe* month = GetMonth();	
	map<int,CDayMe*> days = month->Days;
	map<int,CDayMe*>::iterator sIter = days.find(1);
	if(sIter != days.end())
	{
		SetSelectedDay(sIter->second);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CCalendarMe::DayOfWeek(int y, int m, int d)
{
	if(m == 1 || m == 2)
	{
		m += 12;
		--y;
	}
	return (y / 4 + y + d + 2 * m + 3 * (m + 1) / 5 - y / 100 + y / 400) % 7;
}

String CCalendarMe::GetControlType()
{
	return L"Calendar";
}

CDayMe* CCalendarMe::GetDayInMonth(CMonthMe *month, int day)
{
	map<int,CDayMe*> days = month->Days;
	map<int,CDayMe*>::iterator sIter = days.find(day);
	if(sIter != days.end())
	{
		return sIter->second;
	}
	return 0;
}

vector<String> CCalendarMe::GetEventNames()
{
	vector<String> eventNames = CControlMe::GetEventNames();
	eventNames.push_back(L"SelectedTimeChanged");
	return eventNames;
}

CMonthMe* CCalendarMe::GetLastMonth(int year, int month)
{
	int lastMonth = month - 1;
	int nowYear = year;
	if (lastMonth == 0)
	{
		lastMonth = 12;
		nowYear--;
	}
	return GetMonth(nowYear, lastMonth);
}

CMonthMe* CCalendarMe::GetMonth(int year, int month)
{
	map<int,CMonthMe*> months = m_years->GetYear(year)->Months;
	map<int,CMonthMe*>::iterator sIter = months.find(month);
	if(sIter != months.end())
	{
		return sIter->second;
	}
	return 0;
}

CMonthMe* CCalendarMe::GetNextMonth(int year, int month)
{
	int nextMonth = month + 1;
	int nowYear = year;
	if (nextMonth == 13)
	{
		nextMonth = 1;
		nowYear++;
	}
	return GetMonth(nowYear, nextMonth);
}

void CCalendarMe::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"selectedday")
	{
		*type = L"string";
		wchar_t calendarValue[100] = {0};
		swprintf_s(calendarValue, 99, L"%d-%02d-%02d", m_year, m_month, m_selectedDay->GetDay());
		*value = String(calendarValue);
	}
	else if (name == L"useanimation")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(UseAnimation());
	}
	else
	{
		CControlMe::GetProperty(name, value, type);
	}
}

vector<String> CCalendarMe::GetPropertyNames()
{
	vector<String> propertyNames = CControlMe::GetPropertyNames();
	propertyNames.push_back(L"SeletedDay");
	propertyNames.push_back(L"UseAnimation");
	return propertyNames;
}

void CCalendarMe::GoLastMonth()
{
	CMonthMe* month = GetLastMonth(m_year, m_month);
	map<int,CDayMe*> days = month->Days;
	map<int,CDayMe*>::iterator sIter = days.find(1);
	if(sIter != days.end())
	{
		SetSelectedDay(sIter->second);
	}
}

void CCalendarMe::GoNextMonth()
{
	CMonthMe* month = GetNextMonth(m_year, m_month);
	map<int,CDayMe*> days = month->Days;
	map<int,CDayMe*>::iterator sIter = days.find(1);
	if(sIter != days.end())
	{
		SetSelectedDay(sIter->second);
	}
}

void CCalendarMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnClick(mp, button, clicks, delta);
	if (m_dayDiv)
	{
		m_dayDiv->OnClick(mp, button, clicks, delta);
	}
	if (m_monthDiv)
	{
		m_monthDiv->OnClick(mp, button, clicks, delta);
	}
	if (m_yearDiv)
	{
		m_yearDiv->OnClick(mp, button, clicks, delta);
	}
}

void CCalendarMe::OnKeyDown(char key)
{
	CControlMe::OnKeyDown(key);
	CControlHostMe *host = GetNative()->GetHost();
	if (!host->IsKeyPress(VK_SHIFT)
		&& !host->IsKeyPress(VK_CONTROL)
		&& !host->IsKeyPress(VK_MENU))
	{
		CMonthMe *month = GetMonth();
		CMonthMe *lastMonth = GetLastMonth(m_year, m_month);
		CMonthMe *nextMonth = GetNextMonth(m_year, m_month);
		int day = m_selectedDay->GetDay();
		if (key >= '%' && key <= '(')
		{
			switch (key)
			{
			case '%':
				if (m_selectedDay != month->GetFirstDay())
				{
					SetSelectedDay(GetDayInMonth(month, day - 1));
				}
				else
				{
					SetSelectedDay(lastMonth->GetLastDay());
				}
				return;
			case '&':
				if (day > 7)
				{
					SetSelectedDay(GetDayInMonth(month, m_selectedDay->GetDay() - 7));
				}
				else
				{
					SetSelectedDay(GetDayInMonth(lastMonth, (int)lastMonth->Days.size() - (7 - day)));
				}
				return;
			case '\'':
				if (m_selectedDay != month->GetLastDay())
				{
					SetSelectedDay(GetDayInMonth(month, day + 1));
				}
				else
				{
					SetSelectedDay(nextMonth->GetFirstDay());
				}
				return;
			case '(':
				int size = (int)month->Days.size();
				if (day <= size - 7)
				{
					SetSelectedDay(GetDayInMonth(month, day + 7));
				}
				else
				{
					SetSelectedDay(GetDayInMonth(nextMonth, 7 - (size - day)));
				}
				return;
			}
		}
	}
}

void CCalendarMe::OnLoad()
{
	CControlMe::OnLoad();
	CControlHostMe *host = GetNative()->GetHost();
	if (!m_dayDiv)
	{
		m_dayDiv = new CDayDivMe(this);
	}
	if (!m_timeDiv)
	{
		m_timeDiv = new CTimeDivMe(this);
	}
	if (!m_headDiv)
	{
		m_headDiv = dynamic_cast<CHeadDivMe*>(host->CreateInternalControl(this, L"headdiv"));
		AddControl(m_headDiv);
	}
	if (m_useAnimation)
	{
		StartTimer(m_timerID, 20);
	}
	else
	{
		StopTimer(m_timerID);
	}
	if (m_years && m_year == 0 && m_month == 0)
	{
		SYSTEMTIME SystemTime;
		GetLocalTime(&SystemTime);
		m_year = SystemTime.wYear;
		m_month = SystemTime.wMonth;
		CMonthMe *month = GetMonth(m_year, m_month);
		if(month)
		{
			map<int,CDayMe*> days = month->Days;
			map<int,CDayMe*>::iterator sIter = days.find(1);
			if(sIter != days.end())
			{
				SetSelectedDay(sIter->second);
			}
		}
	}
}

void CCalendarMe::OnPaintBackground(CPaintMe *paint, const RECT& clipRect)
{
	CControlMe::OnPaintBackground(paint, clipRect);
	if (m_dayDiv)
	{
		m_dayDiv->OnPaint(paint, clipRect);
	}
	if (m_monthDiv)
	{
		m_monthDiv->OnPaint(paint, clipRect);
	}
	if (m_yearDiv)
	{
		m_yearDiv->OnPaint(paint, clipRect);
	}
	if (m_timeDiv)
	{
		m_timeDiv->OnPaint(paint, clipRect);
	}
}

void CCalendarMe::OnSelectedTimeChanged()
{
	CControlMe::CallEvents(EVENTID::SELECTEDTIMECHANGED);
}

void CCalendarMe::OnTimer(int timerID)
{
	CControlMe::OnTimer(timerID);
	if (m_timerID == timerID)
	{
		if (m_dayDiv)
		{
			m_dayDiv->OnTimer();
		}
		if (m_monthDiv)
		{
			m_monthDiv->OnTimer();
		}
		if (m_yearDiv)
		{
			m_yearDiv->OnTimer();
		}
		if (m_timeDiv)
		{
			m_timeDiv->OnTimer();
		}
	}
}

void CCalendarMe::SetProperty(const String& name, const String& value)
{
	if (name == L"selectedday")
	{ 
		int year, month, day;  
		string strValue = "";
		CStrMe::wstringTostring(strValue, value);
		sscanf(strValue.c_str(), "%d-%02d-%02d", &year, &month, &day);
		m_year = year;
		m_month = month;
		CMonthMe *cmonth = GetMonth(m_year, m_month);
		SetSelectedDay(GetDayInMonth(cmonth, day));
	}
	else if (name == L"useanimation")
	{
		SetUseAnimation(CStrMe::ConvertStrToBool(value));
	}
	else
	{
		CControlMe::SetProperty(name, value);
	}
}

void CCalendarMe::Update()
{
	CControlMe::Update();
	if (m_dayDiv)
	{
		m_dayDiv->Update();
	}
	if (m_headDiv)
	{
		m_headDiv->BringToFront();
		m_headDiv->Update();
	}
	if (m_monthDiv)
	{
		m_monthDiv->Update();
	}
	if (m_yearDiv)
	{
		m_yearDiv->Update();
	}
	if (m_timeDiv)
	{
		m_timeDiv->Update();
	}
}