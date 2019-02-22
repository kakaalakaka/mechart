/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */


#ifndef __DIVME_H__
#define __DIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CControl.h"
#include "..\\ScrollBar\\CScrollBar.h"
#include "..\\ScrollBar\\CHScrollBar.h"
#include "..\\ScrollBar\\CVScrollBar.h"

namespace MeLib
{
	class  CHScrollBarAMe;
	class  CVScrollBarAMe;

	class  DivMe : public CControlMe
	{
	protected:
		bool m_allowDragScroll;
		CHScrollBarMe *m_hScrollBar;
		bool m_isDragScrolling;
		bool m_isDragScrolling2;
		bool m_readyToDragScroll;
		ControlKeyEvent m_scrollButtonKeyDownEvent;
		ControlMouseEvent m_scrollButtonMouseWheelEvent;
		bool m_showHScrollBar;
		bool m_showVScrollBar;
		POINT m_startMovePoint;
		int m_startMovePosX;
		int m_startMovePosY;
		DWORD m_startMoveTime;
		CVScrollBarMe *m_vScrollBar;
		ControlEvent m_vScrollBarScrolledEvent;
		static void ScrollButtonKeyDown(void *sender, char key, void *pInvoke);
		static void ScrollButtonMouseWheel(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
	public:
		DivMe();
		virtual ~DivMe();
		virtual bool AllowDragScroll();
		virtual void SetAllowDragScroll(bool allowDragScroll);
		CHScrollBarMe* GetHScrollBar();
		virtual bool ShowHScrollBar();
		virtual void SetShowHScrollBar(bool showHScrollBar);
		virtual bool IsDragScrolling();
		virtual bool ShowVScrollBar();
		virtual void SetShowVScrollBar(bool showVScrollBar);
		virtual CVScrollBarMe* GetVScrollBar();
	public:
		virtual int GetContentHeight();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		virtual POINT GetDisplayOffset();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void LineDown();
		virtual void LineLeft();
		virtual void LineRight();
		virtual void LineUp();
		virtual void OnDragReady(POINT *startOffset);
		virtual void OnDragScrollEnd();
		virtual void OnDragScrolling();
		virtual bool OnDragScrollPermit();
		virtual void OnDragScrollStart();
		virtual void OnKeyDown(char key);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual bool OnPreviewsMouseEvent(int eventID, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void PageDown();
		virtual void PageLeft();
		virtual void PageRight();
		virtual void PageUp();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
		virtual void UpdateScrollBar();
	};
}

#endif