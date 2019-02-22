/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CTABCONTROLME_H__
#define __CTABCONTROLME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "..\\Layout\\Div.h"
#include "CTabPage.h"

namespace MeLib
{
	typedef enum  TabPageLayout
	{
		TabPageLayout_Bottom,
		TabPageLayout_Left,
		TabPageLayout_Right,
		TabPageLayout_Top
	};
	
	class  CTabPageMe;

	class  CTabControlMe:public DivMe
	{
	private:
		int m_timerID;
	protected:
		int m_animationState;
		TabPageLayout m_layout;
		int m_selectedIndex;	
		bool m_useAnimation;
		void DrawMoving();
		int GetTabPageIndex(CTabPageMe *tabPage);
	public:
		vector<CTabPageMe*> m_tabPages;
		CTabControlMe();
		virtual ~CTabControlMe();
		virtual TabPageLayout GetLayout();
		virtual void SetLayout(TabPageLayout layout);
		virtual int GetSelectedIndex();
		virtual void SetSelectedIndex(int selectedIndex);
		virtual CTabPageMe* GetSelectedTabPage();
		virtual void SetSelectedTabPage(CTabPageMe *selectedTabPage);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
	public:
		virtual void AddControl(CControlMe *control);
		virtual wstring GetControlType();
		virtual void ClearControls();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void InsertControl(int index, CControlMe *control);
        virtual void OnDragTabHeaderBegin(CTabPageMe *tabPage);
        virtual void OnDragTabHeaderEnd(CTabPageMe *tabPage);
        virtual void OnDraggingTabHeader(CTabPageMe *tabPage);
		virtual void OnLoad();
		virtual void OnSelectedTabPageChanged();
		virtual void OnTimer(int timerID);
		virtual void RemoveControl(CControlMe *control);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif