/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CMENUME_H__
#define __CMENUME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Layout\\CLayoutDiv.h"
#include "CMenuItem.h"

namespace MeLib
{
	class  CMenuItemMe;

	typedef  void (*MenuItemMouseEvent)(void*, CMenuItemMe*, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void*);

	class  CMenuMe : public CLayoutDivMe
	{
	protected:
		bool m_autoHide;
		int m_timerID;
	protected:
		CMenuItemMe *m_parentItem;
		bool m_popup;
		void Adjust(CMenuMe *menu);
		bool CheckDivFocused(vector<CMenuItemMe*> items);
		bool CheckFocused(CControlMe *control);
		bool CloseMenus(vector<CMenuItemMe*> items);
	protected:
		void CallMenuItemMouseEvent(int eventID, CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
	public:
		vector<CMenuItemMe*> m_items;
		CMenuMe();
		virtual ~CMenuMe();
		bool AutoHide();
		void SetAutoHide(bool autoHide);
		CMenuItemMe* GetParentItem();
		void SetParentItem(CMenuItemMe *parentItem);
		bool IsPopup();
		void SetPopup(bool popup);
	public:
		void AddItem(CMenuItemMe *item);
		void ClearItems();
		virtual CMenuMe* CreateDropDownMenu();
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		vector<CMenuItemMe*> GetItems();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertItem(int index, CMenuItemMe *item);
		virtual bool OnAutoHide();
		virtual void OnLoad();
		virtual void OnMenuItemClick(CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMenuItemMouseMove(CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnTimer(int timerID);
		virtual void OnVisibleChanged();
		void RemoveItem(CMenuItemMe *item);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif