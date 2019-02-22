/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CLINKLABELME_H__
#define __CLINKLABELME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CLabel.h"

namespace MeLib
{
	typedef enum  LinkBehaviorMe
	{
		LinkBehaviorMe_AlwaysUnderLine,
		LinkBehaviorMe_HoverUnderLine,
		LinkBehaviorMe_NeverUnderLine
	};

	class  CLabelMe;

	class  CLinkLabelMe : public CLabelMe
	{
	protected:
		_int64 m_activeLinkColor;
		_int64 m_disabledLinkColor;
		LinkBehaviorMe m_linkBehavior;
		_int64 m_linkColor;
		bool m_linkVisited;
		bool m_visited;
		_int64 m_visitedLinkColor;
	protected:
		virtual _int64 GetPaintingLinkColor();
	public:
		CLinkLabelMe();
		virtual ~CLinkLabelMe();
		virtual _int64 GetActiveLinkColor();
		virtual void SetActiveLinkColor(_int64 activeLinkColor);
		virtual _int64 GetDisabledLinkColor();
		virtual void SetDisabledLinkColor(_int64 disabledLinkColor);
		virtual LinkBehaviorMe GetLinkBehavior();
		virtual void SetLinkBehavior(LinkBehaviorMe linkBehavior);
		virtual _int64 GetLinkColor();
		virtual void SetLinkColor(_int64 linkColor);
		virtual bool IsLinkVisited();
		virtual void SetLinkVisited(bool linkVisited);
		virtual _int64 GetVisitedLinkColor();
		virtual void SetVisitedLinkColor(_int64 visitedLinkColor);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseEnter(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseLeave(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif