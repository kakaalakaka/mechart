/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CVSCROLLBARME_H__
#define __CVSCROLLBARME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CScrollBar.h"

namespace MeLib
{
	class  CVScrollBarMe:public CScrollBarMe
	{
	protected:
        ControlMouseEvent m_backButtonMouseDownEvent;
		ControlMouseEvent m_backButtonMouseUpEvent;
		static void BackButtonMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void BackButtonMouseUp(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
	public:
		CVScrollBarMe();
		virtual ~CVScrollBarMe();
		virtual wstring GetControlType();
		void OnBackButtonMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnBackButtonMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnDragScroll();
		virtual void OnLoad();
		virtual void Update();
	};
}

#endif