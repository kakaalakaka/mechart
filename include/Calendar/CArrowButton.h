/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CARROWBUTTONME_H__
#define __CARROWBUTTONME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "CCalendar.h"
#include "CYearDiv.h"

namespace MeLib
{
	class CCalendarMe;

	class CArrowButtonMe:public CButtonMe
	{
	protected:
		CCalendarMe *m_calendar;
		bool m_toLast;
	public:
		CArrowButtonMe(CCalendarMe *calendar);
		virtual ~CArrowButtonMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual bool IsToLast();
		virtual void SetToLast(bool toLast);
	public:
		virtual wstring GetControlType();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
	};
}
#endif