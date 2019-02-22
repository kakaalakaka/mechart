/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CHEADDIVME_H__
#define __CHEADDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"
#include "CCalendar.h"
#include "CDateTitle.h"

namespace MeLib
{
	class  CArrowButtonMe;
	class  CDateTitleMe;

	class  CHeadDivMe:public CControlMe
	{
	protected:
		CCalendarMe *m_calendar;
		CDateTitleMe *m_dateTitle;
		CArrowButtonMe *m_lastBtn;
		CArrowButtonMe *m_nextBtn;
		wstring m_weekStrings[7];
	public:
		CHeadDivMe(CCalendarMe *calendar);
		virtual ~CHeadDivMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual CDateTitleMe* GetDateTitle();
		virtual void SetDateTitle(CDateTitleMe *dateTitle);
		virtual CArrowButtonMe* GetLastBtn();
		virtual void SetLastBtn(CArrowButtonMe *lastBtn);
		virtual CArrowButtonMe* GetNextBtn();
		virtual void SetNextBtn(CArrowButtonMe *nextBtn);
	public:
		virtual wstring GetControlType();
		virtual void OnLoad();
		virtual void OnPaintBackground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintBorder(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void Update();
	};
}

#endif