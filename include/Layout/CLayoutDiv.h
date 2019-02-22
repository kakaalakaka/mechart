/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CLAYOUTDIVME_H__
#define __CLAYOUTDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "Div.h"

namespace MeLib
{
	class  CLayoutDivMe : public DivMe
	{
	protected:
		bool m_autoWrap;
		LayoutStyleMe m_layoutStyle;
	public:
		CLayoutDivMe();
		virtual ~CLayoutDivMe();
		virtual bool AutoWrap();
		virtual void SetAutoWrap(bool autoWrap);
		virtual LayoutStyleMe GetLayoutStyle();
		virtual void SetLayoutStyle(LayoutStyleMe layoutStyle);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual bool OnResetLayout();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif