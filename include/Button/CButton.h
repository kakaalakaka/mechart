/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CBUTTONME_H__
#define __CBUTTONME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"

namespace MeLib
{
	class  CButtonMe:public CControlMe
	{
	protected:
		wstring m_disabledBackImage;
		wstring m_hoveredBackImage;
		wstring m_pushedBackImage;
		ContentAlignmentMe m_textAlign;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual wstring GetPaintingBackImage();
	public:
		CButtonMe();
		virtual ~CButtonMe();
		virtual wstring GetDisabledBackImage();
		virtual void SetDisabledBackImage(const wstring& disabledBackImage);
		virtual wstring GetHoveredBackImage();
		virtual void SetHoveredBackImage(const wstring& hoveredBackImage);
		virtual wstring GetPushedBackImage();
		virtual void SetPushedBackImage(const wstring& pushedBackImage);
		virtual ContentAlignmentMe GetTextAlign();
		virtual void SetTextAlign(ContentAlignmentMe textAlign);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseEnter(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseLeave(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif