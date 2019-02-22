/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CLABELME_H__
#define __CLABELME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	class  CLabelMe : public CControlMe
	{
	protected:
		ContentAlignmentMe m_textAlign;
	public:
		CLabelMe();
		virtual ~CLabelMe();
		virtual ContentAlignmentMe GetTextAlign();
		virtual void SetTextAlign(ContentAlignmentMe textAlign);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPrePaint(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif