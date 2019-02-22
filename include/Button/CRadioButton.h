/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CRADIOBUTTONME_H__
#define __CRADIOBUTTONME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "CCheckBox.h"

namespace MeLib
{
	class  CRadioButtonMe:public CCheckBoxMe
	{
	protected:
		wstring m_groupName;
	public:
		CRadioButtonMe();
		virtual ~CRadioButtonMe();
		virtual wstring GetGroupName();
		virtual void SetGroupName(const wstring& groupName);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintCheckButton(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif