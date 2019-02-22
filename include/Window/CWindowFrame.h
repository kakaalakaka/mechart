/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __WINDOWFRAME_H__
#define __WINDOWFRAME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CWindow.h"

namespace MeLib
{
	class  CWindowFrameMe : public CControlMe
	{
	public:
		CWindowFrameMe();
		virtual ~CWindowFrameMe();
	public:
		virtual bool ContainsPoint(const POINT& point);
		virtual wstring GetControlType();
		virtual void Invalidate();
		virtual void OnPaintBackground(CPaintMe *paint, const RECT& clipRect);
	};
}
#endif