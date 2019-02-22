/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CDATETITLEME_H__
#define __CDATETITLEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "CCalendar.h"

namespace MeLib
{
	class  CCalendarMe;

	class  CDateTitleMe : public CButtonMe
	{
	protected:
		CCalendarMe *m_calendar;
	public:
		CDateTitleMe(CCalendarMe *calendar);
		virtual ~CDateTitleMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
	public:
		virtual wstring GetControlType();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
	};
}
#endif