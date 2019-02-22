/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CMONTHDIVME_H__
#define __CMONTHDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CMonthButton.h"
#include "CHeadDiv.h"
#include "CTimeDiv.h"

namespace MeLib
{
	class  CMonthButtonMe;
	class  CHeadDivMe;
	class  CCalendarMe;
	class  CTimeDivMe;

	class  CMonthDivMe
	{
	protected:
		int m_am_Direction;
		int m_am_Tick;
		int m_am_TotalTick;
		CCalendarMe *m_calendar;
		int m_year;
	public:
		vector<CMonthButtonMe*> m_monthButtons;
		vector<CMonthButtonMe*> m_monthButtons_am;
	public:
		CMonthDivMe(CCalendarMe *calendar);
		virtual ~CMonthDivMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual int GetYear();
	public:
		virtual void Hide();
		void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnLoad();
		void OnPaint(CPaintMe *paint, const RECT& clipRect);
		void OnResetDiv(int state);
		virtual void OnTimer();
		virtual void SelectYear(int year);
		virtual void Show();
		void Update();
	};
}
#endif