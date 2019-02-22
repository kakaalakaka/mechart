/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CDATEPICKERME_H__
#define __CDATEPICKERME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "CTextBox.h"
#include "..\\Button\\CButton.h"
#include "..\\Menu\\CMenu.h"
#include "..\\Menu\\CMenuItem.h"
#include "..\\Calendar\\CCalendar.h"

namespace MeLib
{
	class CDatePickerMe : public CTextBoxMe
	{
	private:
		CCalendarMe *m_calendar;
		CButtonMe *m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		ControlEvent m_selectedDayChangedEvent;
		CMenuMe *m_dropDownMenu;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void SelectedDayChanged(void *sender, void *pInvoke);
	public:
		CDatePickerMe();
		virtual ~CDatePickerMe();
		CCalendarMe* GetCalendar();
		CButtonMe* GetDropDownButton();
		CMenuMe* GetDropDownMenu();
	public:
		virtual String GetControlType();
		virtual void OnDropDownOpening();
		virtual void OnLoad();
		virtual void OnValueChanged();
		virtual void Update();
	};
}

#endif