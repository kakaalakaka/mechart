#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CMonthDiv.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMonthDivMe::CMonthDivMe(CCalendarMe *calendar)
{
	m_am_Direction = 0;
	m_am_Tick = 0;
	m_am_TotalTick = 40;
	m_year = 0;
	m_calendar = calendar;
	OnLoad();
}

CMonthDivMe::~CMonthDivMe()
{
	m_calendar = 0;
	m_monthButtons.clear();
	m_monthButtons_am.clear();
}

CCalendarMe* CMonthDivMe::GetCalendar()
{
	return m_calendar;
}

void CMonthDivMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

int CMonthDivMe::GetYear()
{
	return m_year;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMonthDivMe::Hide()
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		CMonthButtonMe *button = m_monthButtons[i];
		button->SetVisible(false);
	}
}

void CMonthDivMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		CMonthButtonMe *monthButton = m_monthButtons[i];
		if (monthButton->IsVisible())
		{
			RECT bounds = monthButton->GetBounds();
			if ((mp.x >= bounds.left && mp.x <= bounds.right) && (mp.y >= bounds.top && mp.y <= bounds.bottom))
			{
				monthButton->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
	int countAm = (int)m_monthButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		CMonthButtonMe *monthButtonAm = m_monthButtons_am[j];
		if (monthButtonAm->IsVisible())
		{
			RECT rectAm = monthButtonAm->GetBounds();
			if ((mp.x >= rectAm.left && mp.x <= rectAm.right) && (mp.y >= rectAm.top && mp.y <= rectAm.bottom))
			{
				monthButtonAm->OnClick(mp, button, clicks, delta);
				return;
			}
		}
	}
}

void CMonthDivMe::OnLoad()
{
	if (m_calendar)
	{
		CControlHostMe *host = m_calendar->GetNative()->GetHost();
		if (((int)m_monthButtons.size() == 0) || ((int)m_monthButtons_am.size() == 0))
		{
			m_monthButtons.clear();
			m_monthButtons_am.clear();
			for (int i = 0; i < 12; i++)
			{
				CMonthButtonMe *item = new CMonthButtonMe(m_calendar);
				item->SetMonth(i + 1);
				m_monthButtons.push_back(item);
				CMonthButtonMe *itemAm = new CMonthButtonMe(m_calendar);
				item->SetMonth(i + 1);
				itemAm->SetVisible(false);
				m_monthButtons_am.push_back(itemAm);
			}
		}
	}
}

void CMonthDivMe::OnPaint(CPaintMe *paint, const RECT& clipRect)
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		CMonthButtonMe *button = m_monthButtons[i];
		if (button->IsVisible())
		{
			RECT bounds = button->GetBounds();
			button->OnPaintBackground(paint, bounds);
			button->OnPaintForeground(paint, bounds);
			button->OnPaintBorder(paint, bounds);
		}
	}
	int countAm = (int)m_monthButtons_am.size();
	for (int j = 0; j < countAm; j++)
	{
		CMonthButtonMe *buttonAm = m_monthButtons_am[j];
		if (buttonAm->IsVisible())
		{
			RECT rectAm = buttonAm->GetBounds();
			buttonAm->OnPaintBackground(paint, rectAm);
			buttonAm->OnPaintForeground(paint, rectAm);
			buttonAm->OnPaintBorder(paint, rectAm);
		}
	}
}

void CMonthDivMe::OnResetDiv(int state)
{
	if (m_calendar)
	{
		int year = m_year;
		int preYear = m_year - 1;
		int nextYear = m_year + 1;
		int x = 0;
		int height = m_calendar->GetHeadDiv()->GetHeight();
		int width = m_calendar->GetWidth();
		int dayHeight = m_calendar->GetHeight() - m_calendar->GetTimeDiv()->GetHeight();
		int pureHeight = dayHeight - height;
		if (pureHeight < 1)
		{
			pureHeight = 1;
		}
		int curHeight = 0;
		vector<CMonthButtonMe*> monthButtons;
		if (m_am_Direction == 1)
		{
			curHeight = (pureHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				year = nextYear;
				preYear = year - 1;
				nextYear = year + 1;
			}
		}
		else if (m_am_Direction == 2)
		{
			curHeight = (-pureHeight * m_am_Tick) / m_am_TotalTick;
			if (state == 1)
			{
				year = preYear;
				preYear = year - 1;
				nextYear = year + 1;
			}
		}
		if (state == 0)
		{
			monthButtons = m_monthButtons;
		}
		else if (state == 1)
		{
			monthButtons = m_monthButtons_am;
		}
		int cy = pureHeight / 3;
		int count = (int)monthButtons.size();
		for (int i = 0; i < count; i++)
		{
			if (i == 8)
			{
				cy = dayHeight - height;
			}
			CMonthButtonMe *button = monthButtons[i];
			button->SetYear(year);
			int tHeight = 0;
			if (state == 1)
			{
				if (m_am_Tick <= 0)
				{
					button->SetVisible(false);
					continue;
				}
				else
				{
					button->SetVisible(true);
					if (m_am_Direction == 1)
					{
						tHeight = curHeight - pureHeight;
					}
					else if (m_am_Direction == 2)
					{
						tHeight = curHeight + pureHeight;
					}
				}
			}
			else
			{
				tHeight = curHeight;
			}
			if (((i + 1) % 4) == 0)
			{
				POINT point = {x, height + tHeight};
				SIZE size = {width - x, cy};
				RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
				button->SetBounds(rect);
				x = 0;
				if (i != 0 && i != count - 1)
				{
					height += cy;
				}
			}
			else
			{
				POINT point2 = {x, height + tHeight};
				SIZE size2 = {(width / 4) + (((i + 1) % 4) % 2), cy};
				RECT rect = {point2.x, point2.y, point2.x + size2.cx, point2.y + size2.cy};
				button->SetBounds(rect);
				x += size2.cx;
			}
		}
	}
}

void CMonthDivMe::OnTimer()
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

void CMonthDivMe::SelectYear(int year)
{
	if (m_calendar && m_year != year)
	{
		if (year > m_year)
		{
			m_am_Direction = 1;
		}
		else
		{
			m_am_Direction = 2;
		}
		if (m_calendar->UseAnimation())
		{
			m_am_Tick = m_am_TotalTick;
		}
		m_year = year;
	}
}

void CMonthDivMe::Show()
{
	int count = (int)m_monthButtons.size();
	for (int i = 0; i < count; i++)
	{
		CMonthButtonMe *button = m_monthButtons[i];
		button->SetVisible(true);
	}
}

void CMonthDivMe::Update()
{
	OnResetDiv(0);
	OnResetDiv(1);
}