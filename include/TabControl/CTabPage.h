/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CTABPAGEME_H__
#define __CTABPAGEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Layout\\Div.h"
#include "..\\Button\\CButton.h"
#include "CTabControl.h"

namespace MeLib
{
	class  CTabControlMe;

	class  CTabPageMe:public DivMe
	{
	protected:
        ControlEvent m_dragHeaderBeginEvent;
        ControlEvent m_dragHeaderEndEvent;
        ControlEvent m_draggingHeaderEvent;
		CButtonMe *m_headerButton;
		POINT m_headerLocation;
		ControlMouseEvent m_headerMouseDownEvent;
		CTabControlMe *m_tabControl;
        static void DragHeaderBegin(void *sender, void *pInvoke);
        static void DragHeaderEnd(void *sender, void *pInvoke);
        static void DraggingHeader(void *sender, void *pInvoke);
		static void HeaderMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
	public:
		CTabPageMe();
		virtual ~CTabPageMe();
		virtual CButtonMe* GetHeaderButton();
		virtual void SetHeaderButton(CButtonMe *headerButton);		
		virtual POINT GetHeaderLocation();
		virtual void SetHeaderLocation(POINT headerLocation);
		virtual bool IsHeaderVisible();
		virtual void SetHeaderVisible(bool visible);
		virtual CTabControlMe* GetTabControl();
		virtual void SetTabControl(CTabControlMe *tabControl);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnLoad();
		virtual void OnTextChanged();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif