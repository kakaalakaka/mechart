/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CDATETIMEPICKERME_H__
#define __CDATETIMEPICKERME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CTextBox.h"
#include "..\\Button\\CButton.h"
#include "..\\Menu\\CMenu.h"
#include "..\\Menu\\CMenuItem.h"
#include "..\\Calendar\\CCalendar.h"

namespace MeLib
{
	class  CDateTimePickerMe : public CTextBoxMe
	{
	protected:
		CCalendarMe *m_calendar;
		wstring m_customFormat;
		CButtonMe *m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		CMenuMe *m_dropDownMenu;
		ControlEvent m_selectedTimeChangedEvent;
		bool m_showTime;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void SelectedTimeChanged(void *sender, void *pInvoke);
	public:
		CDateTimePickerMe();
		virtual ~CDateTimePickerMe();
		virtual CCalendarMe* GetCalendar();
		virtual wstring GetCustomFormat();
		virtual void SetCustomFormat(const wstring& customFormat);
		virtual CButtonMe* GetDropDownButton();
		virtual CMenuMe* GetDropDownMenu();
		virtual bool ShowTime();
		virtual void SetShowTime(bool showTime);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnDropDownOpening();
		virtual void OnLoad();
		virtual void OnSelectedTimeChanged();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif