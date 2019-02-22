/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CMONTHBUTTONME_H__
#define __CMONTHBUTTONME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "CCalendar.h"

namespace MeLib
{
	class  CCalendarMe;

	class  CMonthButtonMe:public CButtonMe
	{
	protected:
		RECT m_bounds;
		CCalendarMe *m_calendar;
		int m_month;
		bool m_visible;
		int m_year;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		CMonthButtonMe(CCalendarMe *calendar);
		virtual ~CMonthButtonMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual RECT GetBounds();
		virtual void SetBounds(const RECT& bounds);
		virtual int GetMonth();
		virtual CMonthMe* GetMonth(int year, int month);
		virtual void SetMonth(int month);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetYear();
		virtual void SetYear(int year);
	public:
		virtual wstring GetMonthStr();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintBackGround(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
	};
}
#endif