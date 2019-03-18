/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CSQUARECELLME_H__
#define __CSQUARECELLME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "CGSEnums.h"
#include "CGannSquare.h"

namespace MeLib
{
	class CGannSquareMe;
	class CSquareCellMe
	{
	private:
		RECT m_bounds;
		int m_number;
		bool m_selected;
		SquareCellStyle m_style;
	public:
		CSquareCellMe();
		virtual ~CSquareCellMe();
		_int64 GetBackColor();
		RECT GetBounds();
		void SetBounds(RECT bounds);
		_int64 GetForeColor();
		CGannSquareMe *m_gannSquare;
		int GetNumber();
		void SetNumber(int number);
		bool IsSelected();
		void SetSelected(bool selected);
		SquareCellStyle GetStyle();
		void SetStyle(SquareCellStyle style);
		double GetValue();
	public:
		void OnPaint();
	};
}
#endif