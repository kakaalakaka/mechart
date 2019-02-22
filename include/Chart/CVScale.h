/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CVSCALEME_H__
#define __CVSCALEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CEnums.h"
#include "CTable.h"
#include "CCrossLineTip.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;
	class  CCrossLineTipMe;

	class  CVScaleMe : public CPropertyMe
	{
	protected:
		bool m_allowUserPaint;
		bool m_autoMaxMin;
		int m_baseField;
		CCrossLineTipMe *m_crossLineTip;
		int m_digit;
		FONT *m_font;
		_int64 m_foreColor;
		_int64 m_foreColor2;
		int m_magnitude;
		double m_midValue;
		NumberStyle m_numberStyle;
		int m_paddingBottom;
		int m_paddingTop;
		bool m_reverse;
		_int64 m_scaleColor;
		vector<double> m_scaleSteps;
		VScaleSystem m_system;
		VScaleType m_type;
		double m_visibleMax;
		double m_visibleMin;
	public:
		CVScaleMe();
		virtual ~CVScaleMe();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual bool AutoMaxMin();
		virtual void SetAutoMaxMin(bool autoMaxMin);
		virtual int GetBaseField();
		virtual void SetBaseField(int baseField);
		virtual CCrossLineTipMe* GetCrossLineTip();
		virtual int GetDigit();
		virtual void SetDigit(int digit);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual _int64 GetForeColor2();
		virtual void SetForeColor2(_int64 foreColor2);
		virtual int GetMagnitude();
		virtual void SetMagnitude(int magnitude);
		virtual double GetMidValue();
		virtual void SetMidValue(double midValue);
		virtual NumberStyle GetNumberStyle();
		virtual void SetNumberStyle(NumberStyle numberStyle);
		virtual int GetPaddingBottom();
		virtual void SetPaddingBottom(int paddingBottom);
		virtual int GetPaddingTop();
		virtual void SetPaddingTop(int paddingTop);
		virtual bool IsReverse();
		virtual void SetReverse(bool reverse);
		virtual _int64 GetScaleColor();
		virtual void SetScaleColor(_int64 scaleColor);
		virtual VScaleSystem GetSystem();
		virtual void SetSystem(VScaleSystem system);
		virtual VScaleType GetType();
		virtual void SetType(VScaleType type);
		virtual double GetVisibleMax();
		virtual void SetVisibleMax(double visibleMax);
		virtual double GetVisibleMin();
		virtual void SetVisibleMin(double visibleMin);
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