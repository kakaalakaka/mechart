/*****************************************************************************\
*                                                                             *
* GannSquare.h -  GannSquare functions, types, and definitions              *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's square. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __EASY_GANNSQUARE_H__
#define __EASY_GANNSQUARE_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "GSEnums.h"
#include "SquareCell.h"
using namespace OwLib;

namespace OwLib
{
	class SquareCell;
	class GannSquare:public ControlA
	{
	private:
		BolsterOrStress m_bolsterOrStress;
		FONT *m_cellFont;
		vector<SquareCell*> m_cells;
		SIZE m_cellSize;
		int m_digit;
		_int64 m_majorColor;
		_int64 m_minorColor;
		_int64 m_normalColor;
		int m_number;
		_int64 m_selectedColor;
		double m_startValue;
		SquareStyle m_style;
		wstring m_suffix;
		double m_unit;
	public:
		GannSquare();
		virtual ~GannSquare();
		BolsterOrStress GetBolsterOrStress();
		void SetBolsterOrStress(BolsterOrStress bolsterOrStress);
		FONT* GetCellFont();
		void SetCellFont(FONT *cellFont);
		SIZE GetCellSize();
		void SetCellSize(SIZE cellSize);
		int GetDigit();
		void SetDigit(int digit);
		_int64 GetMajorColor();
		void SetMajorColor(_int64 majorColor);
		_int64 GetMinorColor();
		void SetMinorColor(_int64 minorColor);
		_int64 GetNormalColor();
		void SetNormalColor(_int64 normalColor);
		int GetNumber();
		void SetNumber(int number);
		_int64 GetSelectedColor();
		void SetSelectedColor(_int64 selectedColor);
		double GetSelectedValue();
		double GetStartValue();
		void SetStartValue(double startValue);
		SquareStyle GetStyle();
		void SetStyle(SquareStyle style);
		wstring GetSuffix();
		void SetSuffix(const wstring& suffix);
		double GetUnit();
		void SetUnit(double unit);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta);
		virtual void OnPaintBackground(CPaint *paint, const RECT& clipRect);
		void ReCreate();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}
#endif