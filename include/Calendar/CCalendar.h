/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCALENDARME_H__
#define __CCALENDARME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "CYears.h"
#include "CMonth.h"
#include "CArrowButton.h"
#include "CDateTitle.h"
#include "CDayButton.h"
#include "CDayDiv.h"
#include "CHeadDiv.h"
#include "CMonthButton.h"
#include "CMonthDiv.h"
#include "CTimeDiv.h"
#include "CYearButton.h"
#include "CYearDiv.h"

namespace MeLib
{
	class  CArrowButtonMe;
	class  CDateTitleMe;
	class  CDayButtonMe;
	class  CDayDivMe;
	class  CHeadDivMe;
	class  CMonthButtonMe;
	class  CMonthDivMe;
	class  CTimeDivMe;
	class  CYearButtonMe;
	class  CYearDivMe;

	typedef enum  CalendarMode
	{
		CalendarMode_Day,
		CalendarMode_Month,
		CalendarMode_Year
	};

	class  CCalendarMe : public CControlMe
	{
	private:
		int m_timerID;;
	protected:
		CDayDivMe *m_dayDiv;
		CHeadDivMe *m_headDiv;
		CalendarMode m_mode;
		int m_month;
		CMonthDivMe *m_monthDiv;
		CDayMe *m_selectedDay;
		CTimeDivMe *m_timeDiv;
		bool m_useAnimation;
		int m_year;
		CYearDivMe *m_yearDiv;
		CYearsMe *m_years;
	public:
		CCalendarMe();
		virtual ~CCalendarMe();
		virtual CDayMe* GetDayInMonth(CMonthMe *month, int day);
		virtual CDayDivMe* GetDayDiv();
		virtual void SetDayDiv(CDayDivMe *dayDiv);
		virtual CHeadDivMe* GetHeadDiv();
		virtual void SetHeadDiv(CHeadDivMe *headDiv);
		virtual CalendarMode GetMode();
		virtual void SetMode(CalendarMode mode);
		virtual CMonthMe* GetMonth();
		virtual CMonthMe* GetMonth(int year, int month);
		virtual void SetMonth(CMonthMe *month);
		virtual CMonthDivMe* GetMonthDiv();
		virtual void SetMonthDiv(CMonthDivMe *monthDiv);
		virtual CDayMe* GetSelectedDay();
		virtual void SetSelectedDay(CDayMe *day);
		virtual CTimeDivMe* GetTimeDiv();
		virtual void SetTimeDiv(CTimeDivMe *timeDiv);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
		virtual CYearDivMe* GetYearDiv();
		virtual void SetYearDiv(CYearDivMe *yearDiv);
		virtual CYearsMe* GetYears();
		virtual void SetYears(CYearsMe *years);
	public:
		int DayOfWeek(int y, int m, int d);
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		CMonthMe* GetLastMonth(int year, int month);
		CMonthMe* GetNextMonth(int year, int month);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void GoLastMonth();
		void GoNextMonth();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnLoad();
		virtual void OnKeyDown(char key);
		virtual void OnPaintBackground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnSelectedTimeChanged();
		virtual void OnTimer(int timerID);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}
#endif