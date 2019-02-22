/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCROSSLINEME_H__
#define __CCROSSLINEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CEnums.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;

	class  CCrossLineMe : CPropertyMe
	{
	protected:
		bool m_allowUserPaint;
		bool m_allowDoubleClick;
		AttachVScale m_attachVScale;
		_int64 m_lineColor;
	public:
		CCrossLineMe();
		virtual ~CCrossLineMe();
		virtual bool AllowDoubleClick();
		virtual void SetAllowDoubleClick(bool allowDoubleClick);
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual _int64 GetLineColor();
		virtual void SetLineColor(_int64 lineColor);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif