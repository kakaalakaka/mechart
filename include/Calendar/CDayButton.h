/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CDAYBUTTONME_H__
#define __CDAYBUTTONME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "CCalendar.h"

namespace MeLib
{
	class  CCalendarMe;

	class  CDayButtonMe
	{
	protected:
		RECT m_bounds;
		CCalendarMe *m_calendar;
		CDayMe *m_day;
		bool m_inThisMonth;
		bool m_selected;
		bool m_visible;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		CDayButtonMe(CCalendarMe *calendar);
		virtual ~CDayButtonMe();
		virtual RECT GetBounds();
		virtual void SetBounds(const RECT& bounds);
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual CDayMe* GetDay();
		virtual void SetDay(CDayMe *day);
		virtual bool InThisMonth();
		virtual void SetThisMonth(bool inThisMonth);
		virtual bool IsSelected();
		virtual void SetSelected(bool selected);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintBackGround(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
	};
}
#endif