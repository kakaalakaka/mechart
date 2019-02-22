#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CTimeDiv.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTimeDivMe::SelectedTimeChanged(void *sender, void *pInvoke)
{
	CTimeDivMe *div = (CTimeDivMe*)pInvoke;
	if(div)
	{
		div->OnSelectedTimeChanged();
	}
}

_int64 CTimeDivMe::GetPaintingBackColor()
{
	return COLOR_CONTROL;
}

_int64 CTimeDivMe::GetPaintingBorderColor()
{
	return COLOR_CONTROLBORDER;
}

_int64 CTimeDivMe::GetPaintingForeColor()
{
	return COLOR_CONTROLTEXT;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTimeDivMe::CTimeDivMe(CCalendarMe *calendar)
{
	m_calendar = calendar;
	m_height = 40;
	m_spinHour = 0;
	m_spinMinute = 0;
	m_spinSecond = 0;
	OnLoad();
}

CTimeDivMe::~CTimeDivMe()
{
	m_calendar = 0;
	m_spinHour = 0;
	m_spinMinute = 0;
	m_spinSecond = 0;
}

CCalendarMe* CTimeDivMe::GetCalendar()
{
	return m_calendar;
}

void CTimeDivMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

int CTimeDivMe::GetHeight()
{
	return m_height;
}

void CTimeDivMe::SetHeight(int height)
{
	m_height = height;
}

int CTimeDivMe::GetHour()
{
	if (m_spinHour)
	{
		return (int)m_spinHour->GetValue();
	}
	return 0;
}

void CTimeDivMe::SetHour(int hour)
{
	if (m_spinHour)
	{
		m_spinHour->SetValue(hour);
	}
}

int CTimeDivMe::GetMinute()
{
	if (m_spinMinute)
	{
		return (int)m_spinMinute->GetValue();
	}
	return 0;
}

void CTimeDivMe::SetMinute(int minute)
{
	if (m_spinMinute)
	{
		m_spinMinute->SetValue(minute);
	}
}

int CTimeDivMe::GetSecond()
{
	if (m_spinSecond)
	{
		return (int)m_spinSecond->GetValue();
	}
	return 0;
}

void CTimeDivMe::SetSecond(int second)
{
	if (m_spinSecond)
	{
		m_spinSecond->SetValue(second);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTimeDivMe::OnLoad()
{
	if (m_calendar)
	{
		CControlHostMe *host = m_calendar->GetNative()->GetHost();
		if (!m_spinHour)
		{
			m_spinHour = new CSpinMe();
			m_spinHour->SetMaximum(23.0);
			m_spinHour->SetTextAlign(HorizontalAlignMe_Right);
			m_calendar->AddControl(m_spinHour);
			m_spinHour->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
		if (!m_spinMinute)
		{
			m_spinMinute = new CSpinMe();
			m_spinMinute->SetMaximum(59.0);
			m_spinMinute->SetTextAlign(HorizontalAlignMe_Right);
			m_calendar->AddControl(m_spinMinute);
			m_spinMinute->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
		if (!m_spinSecond)
		{
			m_spinSecond = new CSpinMe();
			m_spinSecond->SetMaximum(59.0);
			m_spinSecond->SetTextAlign(HorizontalAlignMe_Right);
			m_calendar->AddControl(m_spinSecond);
			m_spinSecond->RegisterEvent(SelectedTimeChanged, EVENTID::SELECTEDTIMECHANGED, this);
		}
	}
}

void CTimeDivMe::OnPaint(CPaintMe *paint, const RECT& clipRect)
{
	int width = m_calendar->GetWidth();
	int height = m_calendar->GetHeight();
	int num3 = height - m_height;
	RECT rect = {0, height - m_height, width, height};
	paint->FillRect(GetPaintingBackColor(), rect);
	if (m_height > 0)
	{
		_int64 paintingForeColor = GetPaintingForeColor();
		FONT *font = m_calendar->GetFont();
		SIZE size = paint->TextSize(L"时", font);
		RECT rectHour;
		rectHour.left = (width / 3) - size.cx;
		rectHour.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectHour.right = rectHour.left + size.cx;
		rectHour.bottom = rectHour.top + size.cy;
		paint->DrawText(L"时", paintingForeColor, font, rectHour);
		size = paint->TextSize(L"分", font);
		RECT rectMinute;
		rectMinute.left = ((width * 2) / 3) - size.cx;
		rectMinute.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectMinute.right = rectHour.left + size.cx;
		rectMinute.bottom = rectHour.top + size.cy;
		paint->DrawText(L"分", paintingForeColor, font, rectMinute);
		size = paint->TextSize(L"秒", font);
		RECT rectSecond;
		rectSecond.left = (width - size.cx) - 5;
		rectSecond.top = (num3 + (m_height / 2)) - (size.cy / 2);
		rectSecond.right = rectHour.left + size.cx;
		rectSecond.bottom = rectHour.top + size.cy;
		paint->DrawText(L"秒", paintingForeColor, font, rectSecond);
	}
}

void CTimeDivMe::OnSelectedTimeChanged()
{
	if (m_calendar)
	{
		m_calendar->OnSelectedTimeChanged();
	}
}

void CTimeDivMe::OnTimer()
{
}

void CTimeDivMe::Update()
{
	if (m_height > 0)
	{
		int width = m_calendar->GetWidth();
		int height = m_calendar->GetHeight() - m_height;
		int x = 5;
		if (m_spinHour)
		{
			m_spinHour->SetVisible(true);
			POINT point = {x, (height + (m_height / 2)) - (m_spinHour->GetRight() / 2)};
			m_spinHour->SetLocation(point);
			m_spinHour->SetWidth(((width - 15) / 3) - 20);
		}
		if (m_spinMinute)
		{
			m_spinMinute->SetVisible(true);
			POINT point = {(width / 3) + 5, (height + (m_height / 2)) - (m_spinMinute->GetHeight() / 2)};
			m_spinMinute->SetLocation(point);
			m_spinMinute->SetWidth(((width - 15) / 3) - 20);
		}
		if (m_spinSecond)
		{
			m_spinSecond->SetVisible(true);
			POINT point = {((width * 2) / 3) + 5, (height + (m_height / 2)) - (m_spinSecond->GetHeight() / 2)};
			m_spinSecond->SetLocation(point);
			m_spinSecond->SetWidth(((width - 15) / 3) - 20);
		}
	}
	else
	{
		if (m_spinHour)
		{
			m_spinHour->SetVisible(false);
		}
		if (m_spinMinute)
		{
			m_spinMinute->SetVisible(false);
		}
		if (m_spinSecond)
		{
			m_spinSecond->SetVisible(false);
		}
	}
}