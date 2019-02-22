/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CTIMEDIVME_H__
#define __CTIMEDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CCalendar.h"
#include "..\\TextBox\\CSpin.h"

namespace MeLib
{
	class  CCalendarMe;

	class  CTimeDivMe
	{
	protected:
		static void SelectedTimeChanged(void *sender, void *pInvoke);
	protected:
		CCalendarMe *m_calendar;
		int m_height;
		CSpinMe *m_spinHour;
		CSpinMe *m_spinMinute;
		CSpinMe *m_spinSecond;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingBorderColor();
		virtual _int64 GetPaintingForeColor();
	public:
		CTimeDivMe(CCalendarMe *calendar);
		virtual ~CTimeDivMe();
		virtual CCalendarMe* GetCalendar();
		virtual void SetCalendar(CCalendarMe *calendar);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual int GetHour();
		virtual void SetHour(int hour);
		virtual int GetMinute();
		virtual void SetMinute(int minute);
		virtual int GetSecond();
		virtual void SetSecond(int second);
	public:
		void OnLoad();
		void OnPaint(CPaintMe *paint, const RECT& clipRect);
		void OnSelectedTimeChanged();
		void OnTimer();
		void Update();
	};
}
#endif