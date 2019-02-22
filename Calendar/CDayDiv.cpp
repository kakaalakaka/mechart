#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CDayDiv.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CDayDivMe::CDayDivMe(CCalendarMe *calendar)
{
	m_am_ClickRowFrom = 0;
	m_am_ClickRowTo = 0;
	m_am_Direction = 0;
	m_am_Tick = 0;
	m_am_TotalTick = 40;
	m_calendar = calendar;
	OnLoad();
}

CDayDivMe::~CDayDivMe()
{
	m_calendar = 0;
	m_dayButtons.clear();
	m_dayButtons_am.clear();
}

CCalendarMe* CDayDivMe::GetCalendar()
{
	return m_calendar;
}

void CDayDivMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDayDivMe::Hide()
{
	int count = (int)m_dayButtons.size();
	for (int i = 0; i < count; i++)
	{
		CDayButtonMe *button = m_dayButtons[i];
		button->SetVisible(false);
	}
}

void CDayDivMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	int count = (int)m_dayButtons.size();
	for (int i = 0; i < count; i++)
	{
		CDayButtonMe *dayButton = m_dayButtons[i];
		if (dayButton->IsVisible())
		{
			RECT bounds = dayButton->GetBounds();
			if (mp.x >= bounds.left && mp.x <= bounds.right && mp.y >= bounds.top && mp.y <= bounds.bottom)
			{
				dayButton->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}

	int countAm = (int)m_dayButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		CDayButtonMe *dayButtonAm = m_dayButtons_am[j];
		if (dayButtonAm->IsVisible())
		{
			RECT amRect = dayButtonAm->GetBounds();
			if (mp.x >= amRect.left && mp.x <= amRect.right && mp.y >= amRect.top && mp.y <= amRect.bottom)
			{
				dayButtonAm->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
}

void CDayDivMe::OnLoad()
{
	if (m_calendar)
	{
		CControlHostMe *host = m_calendar->GetNative()->GetHost();
		if ((int)m_dayButtons.size() == 0 || (int)m_dayButtons_am.size() == 0)
		{
			m_dayButtons.clear();
			m_dayButtons_am.clear();
			for (int i = 0; i < 42; i++)
			{
				CDayButtonMe *dayButton = new CDayButtonMe(m_calendar);
				m_dayButtons.push_back(dayButton);
				CDayButtonMe *dayButtonAm = new CDayButtonMe(m_calendar);
				dayButtonAm->SetVisible(false);
				m_dayButtons_am.push_back(dayButtonAm);
			}
		}
	}
}

void CDayDivMe::OnPaint(CPaintMe *paint, const RECT& clipRect)
{
	int count = (int)m_dayButtons.size();
	for (int i = 0; i < count; i++)
	{
		CDayButtonMe *button = m_dayButtons[i];
		if (button->IsVisible())
		{
			RECT bounds = button->GetBounds();
			button->OnPaintBackGround(paint, bounds);
			button->OnPaintForeground(paint, bounds);
			button->OnPaintBorder(paint, bounds);
		}
	}
	int countAm = (int)m_dayButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		CDayButtonMe *buttonAm = m_dayButtons_am[j];
		if (buttonAm->IsVisible())
		{
			RECT rectAm = buttonAm->GetBounds();
			buttonAm->OnPaintBackGround(paint, rectAm);
			buttonAm->OnPaintForeground(paint, rectAm);
			buttonAm->OnPaintBorder(paint, rectAm);
		}
	}
}

void CDayDivMe::OnResetDiv(int state)
{
	if (m_calendar)
	{
		int num = 0;
		CMonthMe *month = m_calendar->GetMonth();
		CMonthMe *lastMonth = m_calendar->GetLastMonth(month->GetYear(), month->GetMonth());
		CMonthMe *nextMonth = m_calendar->GetNextMonth(month->GetYear(), month->GetMonth());
		int x = 0;
		int heightHeadDiv = m_calendar->GetHeadDiv()->GetHeight();
		int height = heightHeadDiv;
		int width = m_calendar->GetWidth();
		int dateDivHeight = m_calendar->GetHeight();
		int timeDivHeight = m_calendar->GetTimeDiv()->GetHeight();
		dateDivHeight -= timeDivHeight;
		int dayHeight = dateDivHeight - height;
		if (dayHeight < 1)
		{
			dayHeight = 1;
		}
		int v63 = 0;
		int v62 = 0;
		vector<CDayButtonMe*> dayButtons;
		if (m_am_Direction == 1)
		{
			v63 = (6 - (m_am_ClickRowTo - m_am_ClickRowFrom)) * (dayHeight / 6);
			v62 = (-dateDivHeight + v63) + heightHeadDiv;
			v62 = (v62 * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				month = nextMonth;
				lastMonth = m_calendar->GetLastMonth(month->GetYear(), month->GetMonth());
				nextMonth = m_calendar->GetNextMonth(month->GetYear(), month->GetMonth());
			}
		}
		else if (m_am_Direction == 2)
		{
			v63 = (6 - (m_am_ClickRowFrom - m_am_ClickRowTo)) * (dayHeight / 6);
			v62 = (dateDivHeight - v63) - heightHeadDiv;
			v62 = (v62 * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				month = lastMonth;
				lastMonth = m_calendar->GetLastMonth(month->GetYear(), month->GetMonth());
				nextMonth = m_calendar->GetNextMonth(month->GetYear(), month->GetMonth());
			}
		}
		if (state == 0)
		{
			dayButtons = m_dayButtons;
		}
		else if (state == 1)
		{
			dayButtons = m_dayButtons_am;
		}
		int cy = dayHeight / 6;
		map<int, CDayMe*> days = month->Days;
		CDayMe *day = days[1];
		int yearVal = day->GetYear();
		int monthVal = day->GetMonth();
		int dayVal = day->GetDay();
		int dayOfWeek = m_calendar->DayOfWeek(yearVal, monthVal, dayVal);
		int count = (int)dayButtons.size();
		for (int i = 0; i < count; i++)
		{
			if (i == 35)
			{
				cy = dateDivHeight - height;
			}
			CDayButtonMe *button = dayButtons[i];
			int num14 = 0;
			if (state == 1)
			{
				if (m_am_Tick > 0)
				{
					button->SetVisible(true);
					if (m_am_Direction == 1)
					{
						num14 = v62 + dayHeight;
					}
					else if (m_am_Direction == 2)
					{
						num14 = v62 - dayHeight;
					}
				}
				else
				{
					button->SetVisible(false);
					continue;
				}
			}
			else
			{
				num14 = v62;
			}
			if (((i + 1) % 7) == 0)
			{
				POINT point = {x, height + num14};
				SIZE size = {width - x, cy};
				RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
				button->SetBounds(rect);
				x = 0;
				if (i != 0 && i != num - 1)
				{
					height += cy;
				}
			}
			else
			{
				POINT point2 = {x, height + num14};
				SIZE size2 = {(width / 7) + (((i + 1) % 7) % 2), cy};
				RECT rect2 = {point2.x, point2.y, point2.x + size2.cx, point2.y + size2.cy};
				button->SetBounds(rect2);
				x += size2.cx;
			}
			CDayMe *day2 = 0;
			button->SetThisMonth(false);
			if (i >= dayOfWeek && i <= dayOfWeek + (int)days.size() - 1)
			{
				day2 = days[(i - dayOfWeek) + 1];
				button->SetThisMonth(true);
			}
			else if (i < dayOfWeek)
			{
				day2 = lastMonth->Days[(int)lastMonth->Days.size() - dayOfWeek + i + 1];
			}
			else if (i > ((dayOfWeek + (int)days.size()) - 1))
			{
				day2 = nextMonth->Days[((i - dayOfWeek) - (int)days.size()) + 1];
			}
			int num1 = day2->GetDay();
			button->SetDay(day2);
			if ((state == 0 && button->GetDay()) && (button->GetDay() == m_calendar->GetSelectedDay()))
			{
				button->SetSelected(true);
			}
			else
			{
				button->SetSelected(false);
			}
		}
	}
}

void CDayDivMe::OnTimer()
{
	if (m_am_Tick > 0)
	{
		m_am_Tick = (int) ((m_am_Tick * 2.0) / 3.0);
		if (m_calendar)
		{
			m_calendar->Update();
			m_calendar->Invalidate();
		}
	}
}

void CDayDivMe::SelectDay(CDayMe *selectedDay)
{			
	if (m_calendar)
	{
		CMonthMe *selectedMonth = m_calendar->GetYears()->GetYear(selectedDay->GetYear())->Months[selectedDay->GetMonth()];
		CMonthMe *calendarMonth = m_calendar->GetMonth();
		if (selectedMonth != calendarMonth)
		{
			if (calendarMonth->GetYear() * 12 + calendarMonth->GetMonth() > selectedMonth->GetYear() * 12 + selectedMonth->GetMonth())
			{
				m_am_Direction = 1;
			}
			else
			{
				m_am_Direction = 2;
			}
			int count = (int)m_dayButtons.size();
			for (int i = 0; i < count; i++)
			{
				CDayButtonMe *button = m_dayButtons[i];
				if ((m_am_Direction == 1 && button->GetDay() == calendarMonth->GetFirstDay())
					|| (m_am_Direction == 2 && button->GetDay() == calendarMonth->GetLastDay()))
				{
					m_am_ClickRowFrom = i / 7;
					if ((i % 7) != 0)
					{
						m_am_ClickRowFrom++;
					}
				}
			}
			m_calendar->SetMonth(selectedMonth);
			OnResetDiv(0);
			int countAm = (int)m_dayButtons_am.size();
			for (int j = 0; j < countAm; j++)
			{
				CDayButtonMe *buttonAm = m_dayButtons_am[j];
				if ((m_am_Direction == 1 && buttonAm->GetDay() == selectedMonth->GetLastDay())
					|| (m_am_Direction == 2 && buttonAm->GetDay() == selectedMonth->GetFirstDay()))
				{
					m_am_ClickRowTo = j / 7;
					if ((j % 7) != 0)
					{
						m_am_ClickRowTo++;
					}
				}
			}
			if (m_calendar->UseAnimation())
			{
				m_am_Tick = m_am_TotalTick;
			}
		}
		else
		{
			int count = (int)m_dayButtons.size();
			for (int k = 0; k < count; k++)
			{
				CDayButtonMe *button = m_dayButtons[k];
				if (button->GetDay() != selectedDay)
				{
					button->SetSelected(false);
				}
			}
			m_calendar->SetMonth(selectedMonth);
		}
	}
}

void CDayDivMe::Show()
{
	int count = (int)m_dayButtons.size();
	for (int i = 0; i < count; i++)
	{
		CDayButtonMe *button = m_dayButtons[i];
		button->SetVisible(true);
	}
}

void CDayDivMe::Update()
{
	OnResetDiv(0);
	OnResetDiv(1);
}
