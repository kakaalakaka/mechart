/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CSCALEGRIDME_H__
#define __CSCALEGRIDME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;

	class  CScaleGridMe : public CPropertyMe
	{
	protected:
		bool m_allowUserPaint;
		int m_distance;
		_int64 m_gridColor;
		int m_lineStyle;
		bool m_visible;
	public:
		CScaleGridMe();
		virtual ~CScaleGridMe();
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual int GetDistance();
		virtual void SetDistance(int distance);
		virtual _int64 GetGridColor();
		virtual void SetGridColor(_int64 gridColor);
		virtual int GetLineStyle();
		virtual void SetLineStyle(int lineStyle);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif