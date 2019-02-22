/*****************************************************************************\
*                                                                             *
* SquareCell.h -  SquareCell functions, types, and definitions                *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's square. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __SQUARECELL_H__
#define __SQUARECELL_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "GSEnums.h"
#include "GannSquare.h"

namespace OwLib
{
	class GannSquare;
	class SquareCell
	{
	private:
		RECT m_bounds;
		int m_number;
		bool m_selected;
		SquareCellStyle m_style;
	public:
		SquareCell();
		virtual ~SquareCell();
		_int64 GetBackColor();
		RECT GetBounds();
		void SetBounds(RECT bounds);
		_int64 GetForeColor();
		GannSquare *m_gannSquare;
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