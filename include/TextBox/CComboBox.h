/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCOMBOBOXME_H__
#define __CCOMBOBOXME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CTextBox.h"
#include "..\\Button\\CButton.h"
#include "..\\Menu\\CMenu.h"
#include "..\\Menu\\CMenuItem.h"

namespace MeLib
{
	class  CComboBoxMe;

	class  CComboBoxMenuMe : public CMenuMe
	{
	protected:
		CComboBoxMe *m_comboBox;
	public:
		CComboBoxMenuMe();
		virtual ~CComboBoxMenuMe();
		CComboBoxMe* GetComboBox();
		void SetComboBox(CComboBoxMe *comboBox);
		virtual bool OnAutoHide();
	};

	class  CComboBoxMe : public CTextBoxMe
	{
	protected:
		CButtonMe* m_dropDownButton;
		ControlMouseEvent m_dropDownButtonMouseDownEvent;
		MenuItemMouseEvent m_menuItemClickEvent;
		ControlKeyEvent m_menuKeyDownEvent;
		CComboBoxMenuMe* m_dropDownMenu;
		static void DropDownButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void MenuItemClick(void *sender, CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void MenuKeyDown(void *sender, char key, void *pInvoke);
	public:
		CComboBoxMe();
		virtual ~CComboBoxMe();
		virtual CButtonMe* GetDropDownButton();
		virtual CComboBoxMenuMe* GetDropDownMenu();
		virtual int GetSelectedIndex();
		virtual void SetSelectedIndex(int selectedIndex);
		virtual wstring GetSelectedText();
		virtual void SetSelectedText(const wstring& selectedText);
		virtual wstring GetSelectedValue();
		virtual void SetSelectedValue(const wstring& selectedValue);
	public:
		void AddItem(CMenuItemMe *item);
		void ClearItems();
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		vector<CMenuItemMe*> GetItems();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertItem(int index, CMenuItemMe *item);
		virtual void OnDropDownOpening();
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnSelectedIndexChanged();
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void RemoveItem(CMenuItemMe *item);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif