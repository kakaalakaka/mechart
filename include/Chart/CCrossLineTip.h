/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CCROSSLINETIPME_H__
#define __CCROSSLINETIPME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;

	class  CCrossLineTipMe
	{
	protected:
		bool m_allowUserPaint;
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
		bool m_visible;
	public:
		CCrossLineTipMe();
		virtual ~CCrossLineTipMe();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif