/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CMENUITEMME_H__
#define __CMENUITEMME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "CMenu.h"

namespace MeLib
{
	class  CMenuMe;

	class  CMenuItemMe : public CButtonMe
	{
	protected:
		bool m_checked;
		CMenuMe *m_dropDownMenu;
		CMenuItemMe *m_parentItem;
		CMenuMe *m_parentMenu;
		wstring m_value;
	public:
		vector<CMenuItemMe*> m_items;
		CMenuItemMe();
		CMenuItemMe(const wstring& text);
		virtual ~CMenuItemMe();
		bool IsChecked();
		void SetChecked(bool checked);
		CMenuMe* GetDropDownMenu();
		void SetDropDownMenu(CMenuMe *dropDownMenu);
		CMenuItemMe* GetParentItem();
		void SetParentItem(CMenuItemMe *parentItem);
		CMenuMe* GetParentMenu();
		void SetParentMenu(CMenuMe *parentMenu);
		wstring GetValue();
		void SetValue(const wstring& value);
	public:
		void AddItem(CMenuItemMe *item);
		void ClearItems();
		virtual wstring GetControlType();
		vector<CMenuItemMe*> GetItems();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertItem(int index, CMenuItemMe *item);
		virtual void OnAddingItem(int index);
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnRemovingItem();
		void RemoveItem(CMenuItemMe *item);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif