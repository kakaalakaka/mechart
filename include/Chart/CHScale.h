/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */


#ifndef __CHSCALEME_H__
#define __CHSCALEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CEnums.h"
#include "CCrossLineTip.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;
	class  CCrossLineTipMe;

	class  CHScaleMe : public CPropertyMe
	{
	protected:
		bool m_allowUserPaint;
		CCrossLineTipMe *m_crossLineTip;
		map<DateType, _int64> m_dateColors;
		FONT *m_font;
		_int64 m_foreColor;
		int m_height;
		HScaleType m_hScaleType;
		int m_interval;
		_int64 m_scaleColor;
		vector<double> m_scaleSteps;
		bool m_visible;
	public:
		CHScaleMe();
		virtual ~CHScaleMe();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual CCrossLineTipMe* GetCrossLineTip();
		virtual _int64 GetDateColor(DateType dateType);
		virtual void SetDateColor(DateType dateType, _int64 color);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual HScaleType GetHScaleType();
		virtual void SetHScaleType(HScaleType hScaleType);
		virtual int GetInterval();
		virtual void SetInterval(int interval);
		virtual _int64 GetScaleColor();
		virtual void SetScaleColor(_int64 scaleColor);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		vector<double> GetScaleSteps();
		virtual void OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
		void SetScaleSteps(vector<double> scaleSteps);
	};
}
#endif