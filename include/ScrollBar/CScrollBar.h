/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CSCROLLBARME_H__
#define __CSCROLLBARME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"

namespace MeLib
{
	class  CScrollBarMe:public CControlMe
	{
	private:
		int m_timerID;
		int m_tick;
	protected:
		CButtonMe *m_addButton;
		int m_addSpeed;
		CButtonMe *m_backButton;
		int m_contentSize;
		bool m_isAdding;
		bool m_isReducing;
		int m_lineSize;
		int m_pageSize;
		int m_pos;
		CButtonMe *m_reduceButton;
		CButtonMe *m_scrollButton;
	protected:
		ControlMouseEvent m_addButtonMouseDownEvent;
		ControlMouseEvent m_addButtonMouseUpEvent;
		ControlMouseEvent m_reduceButtonMouseDownEvent;
		ControlMouseEvent m_reduceButtonMouseUpEvent;
		ControlEvent m_scrollButtonDraggingEvent;
		static void AddButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void AddButtonMouseUp(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ReduceButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ReduceButtonMouseUp(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ScrollButtonDragging(void *sender, void *pInvoke);
	public:
		CScrollBarMe();
		virtual ~CScrollBarMe();
		virtual CButtonMe* GetAddButton();
		virtual int GetAddSpeed();
		virtual void SetAddSpeed(int addSpeed);
		virtual CButtonMe* GetBackButton();
		virtual int GetContentSize();
		virtual void SetContentSize(int contentWidth);
		virtual bool IsAdding();
		virtual void SetIsAdding(bool isAdding);
		virtual bool IsReducing();
		virtual void SetIsReducing(bool isReducing);
		virtual int GetLineSize();
		virtual void SetLineSize(int lineSize);
		virtual int GetPageSize();
		virtual void SetPageSize(int pageSize);
		virtual int GetPos();
		virtual void SetPos(int pos);
		virtual CButtonMe* GetReduceButton();
		virtual CButtonMe* GetScrollButton();
	public:
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		virtual void LineAdd();
		virtual void LineReduce();
		void OnAddButtonMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnAddButtonMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnAddSpeedScrollEnd();
		virtual void OnAddSpeedScrollStart(DWORD startTime, DWORD nowTime, int start, int end);
		virtual int OnAddSpeedScrolling();
		virtual void OnDragScroll();
		virtual void OnLoad();
		void OnReduceButtonMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnReduceButtonMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnScrolled();
		virtual void OnVisibleChanged();
		virtual void PageAdd();
		virtual void PageReduce();
		virtual void ScrollToBegin();
		virtual void ScrollToEnd();
		virtual void OnTimer(int timerID);
	};
}

#endif