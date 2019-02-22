#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CHeadDiv.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CHeadDivMe::CHeadDivMe(CCalendarMe *calendar)
{
	m_calendar = calendar;
	m_dateTitle = 0;
	m_lastBtn = 0;
	m_nextBtn = 0;
	m_weekStrings[0] = L"周日";
	m_weekStrings[1] = L"周一";
	m_weekStrings[2] = L"周二";
	m_weekStrings[3] = L"周三";
	m_weekStrings[4] = L"周四";
	m_weekStrings[5] = L"周五";
	m_weekStrings[6] = L"周六";
	FONT font(L"Simsun", 14, true, false, false);
	SetFont(&font);
	SetHeight(55);
}

CHeadDivMe::~CHeadDivMe()
{
	m_calendar = 0;
	m_dateTitle = 0;
	m_lastBtn = 0;
	m_nextBtn = 0;
}

CCalendarMe* CHeadDivMe::GetCalendar()
{
	return m_calendar;
}

void CHeadDivMe::SetCalendar(CCalendarMe *calendar)
{
	m_calendar = calendar;
}

CDateTitleMe* CHeadDivMe::GetDateTitle()
{
	return m_dateTitle;
}

void CHeadDivMe::SetDateTitle(CDateTitleMe *dateTitle)
{
	m_dateTitle = dateTitle;
}

CArrowButtonMe* CHeadDivMe::GetLastBtn()
{
	return m_lastBtn;
}

void CHeadDivMe::SetLastBtn(CArrowButtonMe *lastBtn)
{
	m_lastBtn = lastBtn;
}

CArrowButtonMe* CHeadDivMe::GetNextBtn()
{
	return m_nextBtn;
}

void CHeadDivMe::SetNextBtn(CArrowButtonMe *nextBtn)
{
	m_nextBtn = nextBtn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

String CHeadDivMe::GetControlType()
{
	return L"HeadDiv";
}

void CHeadDivMe::OnLoad()
{
	CControlMe::OnLoad();
	CControlHostMe *host = GetNative()->GetHost();
	if (!m_dateTitle)
	{
		m_dateTitle = dynamic_cast<CDateTitleMe*>(host->CreateInternalControl(m_calendar, L"datetitle"));
		AddControl(m_dateTitle);
	}
	if (!m_lastBtn)
	{
		m_lastBtn = dynamic_cast<CArrowButtonMe*>(host->CreateInternalControl(m_calendar, L"lastbutton"));
		AddControl(m_lastBtn);
	}
	if (!m_nextBtn)
	{
		m_nextBtn = dynamic_cast<CArrowButtonMe*>(host->CreateInternalControl(m_calendar, L"nextbutton"));
		AddControl(m_nextBtn);
	}
}

void CHeadDivMe::OnPaintBackground(CPaintMe *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	RECT rect = {0, 0, width, height};
	paint->FillRect(GetPaintingBackColor(), rect);
}

void CHeadDivMe::OnPaintBorder(CPaintMe *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	paint->DrawLine(GetPaintingBorderColor(), 1, 0, 0, height, width, height);
}

void CHeadDivMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	if (m_calendar->GetMode() == CalendarMode_Day)
	{
		float num3 = 0;
		SIZE size;
		FONT *font = GetFont();
		__int64 paintingForeColor = GetPaintingForeColor();
		for (int i = 0; i < (int)m_weekStrings->length(); i++)
		{
			size = paint->TextSize(m_weekStrings[i].c_str(), font);
			float left = (num3 + ((float) width / 7 / 2) - ((float) size.cx / 2));
			float top = (float)(height - size.cy);
			RECT rect = {(LONG)left, (LONG)top, (LONG)(left + size.cx), (LONG)(top + size.cy)};
			paint->DrawText(m_weekStrings[i].c_str(), paintingForeColor, font, rect);
			num3 += ((float) width) / 7;
		}
	}
}

void CHeadDivMe::Update()
{
	CControlMe::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dateTitle)
	{
		POINT point = { (width - m_dateTitle->GetWidth()) / 2, (height - m_dateTitle->GetHeight()) / 2 };
		m_dateTitle->SetLocation(point);
	}
	if (m_lastBtn)
	{
		POINT point = { 2, (height - m_lastBtn->GetHeight()) / 2};
		m_lastBtn->SetLocation(point);
	}
	if (m_nextBtn)
	{
		POINT point = { (width - m_nextBtn->GetWidth()) - 2, (height - m_nextBtn->GetHeight()) / 2};
		m_lastBtn->SetLocation(point);
	}
}