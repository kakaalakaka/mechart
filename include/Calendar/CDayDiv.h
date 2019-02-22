/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CDAYDIVME_H__
#define __CDAYDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDayButton.h"
#include "CYears.h"
#include "CMonth.h"
#include "CDay.h"
#include "CHeadDiv.h"
#include "CTimeDiv.h"

namespace MeLib
{
	class  CDayButtonMe;
	class  CHeadDivMe;
	class  CCalendarMe;
	class  CTimeDivMe;

	class  CDayDivMe
	{
	protected:
		int m_am_ClickRowFrom;
		int m_am_ClickRowTo;
		int m_am_Direction;
		int m_am_Tick;
		int m_am_TotalTick;
		CCalendarMe *m_calendar;
	public:
		vector<CDayButtonMe*> m_dayButtons;
		vector<CDayButtonMe*> m_dayButtons_am;
	public:
		CDayDivMe(CCalendarMe *calendar);
		virtual ~CDayDivMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
	public:
		void Hide();
		void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnLoad();
		void OnPaint(CPaintMe *paint, const RECT& clipRect);
		void OnResetDiv(int state);
		void OnTimer();
		void SelectDay(CDayMe *selectedDay);
		void Show();
		void Update();
	};
}
#endif