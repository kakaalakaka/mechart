/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CYEARDIVME_H__
#define __CYEARDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CYearButton.h"
#include "CHeadDiv.h"
#include "CTimeDiv.h"

namespace MeLib
{
	class  CCalendarMe;
	class  CHeadDivMe;
	class  CYearButtonMe;
	class  CTimeDivMe;

	class  CYearDivMe
	{
	protected:
		int m_am_Direction;
		int m_am_Tick;
		int m_am_TotalTick;
		CCalendarMe *m_calendar;
		int m_startYear;
	public:
		vector<CYearButtonMe*> m_yearButtons;
		vector<CYearButtonMe*> m_yearButtons_am;
	public:
		CYearDivMe(CCalendarMe *calendar);
		virtual ~CYearDivMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual int GetStartYear();
	public:
		void Hide();
		void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnLoad();
		void OnPaint(CPaintMe *paint, const RECT& clipRect);
		void OnResetDiv(int state);
		void OnTimer();
		void SelectStartYear(int startYear);
		void Show();
		void Update();
	};
}
#endif