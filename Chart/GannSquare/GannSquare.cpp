#include "..\\..\\stdafx.h"
#include "GannSquare.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GannSquare::GannSquare()
{
	m_bolsterOrStress = BolsterOrStress_Bolster;
	m_cellFont = NULL;
	m_digit = 0;
	m_number = 0;
	m_startValue = 0;
	m_style = SquareStyle_Normal;
	m_suffix = L"";
	m_unit = 0;
}

GannSquare::~GannSquare()
{
	vector<SquareCell*>::iterator sIter = m_cells.begin();
	for(; sIter != m_cells.end(); ++sIter)
	{
		delete *sIter;
		*sIter = 0;
	}
	m_cells.clear();
}

BolsterOrStress GannSquare::GetBolsterOrStress()
{
	return m_bolsterOrStress;
}

void GannSquare::SetBolsterOrStress(BolsterOrStress bolsterOrStress)
{
	m_bolsterOrStress = bolsterOrStress;
}

FONT* GannSquare::GetCellFont()
{
	return m_cellFont;
}

void GannSquare::SetCellFont(FONT *cellFont)
{
	m_cellFont = cellFont;
}

SIZE GannSquare::GetCellSize()
{
	return m_cellSize;
}

void GannSquare::SetCellSize(SIZE cellSize)
{
	m_cellSize = m_cellSize;
}

int GannSquare::GetDigit()
{
	return m_digit;
}

void GannSquare::SetDigit(int digit)
{
	m_digit = digit;
}

_int64 GannSquare::GetMajorColor()
{
	return m_majorColor;
}

void GannSquare::SetMajorColor(_int64 majorColor)
{
	m_majorColor = majorColor;
}

_int64 GannSquare::GetMinorColor()
{
	return m_minorColor;
}

void GannSquare::SetMinorColor(_int64 minorColor)
{
	m_minorColor = minorColor;
}

_int64 GannSquare::GetNormalColor()
{
	return m_normalColor;
}

void GannSquare::SetNormalColor(_int64 normalColor)
{
	m_normalColor = normalColor;
}

int GannSquare::GetNumber()
{
	return m_number;
}

void GannSquare::SetNumber(int number)
{
	m_number = number;
}

_int64 GannSquare::GetSelectedColor()
{
	return m_selectedColor;
}

void GannSquare::SetSelectedColor(_int64 selectedColor)
{
	m_selectedColor = selectedColor;
}

double GannSquare::GetSelectedValue()
{
	return 0;
}

double GannSquare::GetStartValue()
{
	return m_startValue;
}

void GannSquare::SetStartValue(double startValue)
{
	m_startValue = startValue;
}

SquareStyle GannSquare::GetStyle()
{
	return m_style;
}

void GannSquare::SetStyle(SquareStyle style)
{
	m_style = style;
}

wstring GannSquare::GetSuffix()
{
	return m_suffix;
}

void GannSquare::SetSuffix(const wstring& suffix)
{
	m_suffix = suffix;
}

double GannSquare::GetUnit()
{
	return m_unit;
}

void GannSquare::SetUnit(double unit)
{
	m_unit = unit;
}


void GannSquare::GetProperty(const wstring& name, wstring *value, wstring *type)
{
}

vector<wstring> GannSquare::GetPropertyNames()
{
	vector<wstring> lst;
	return lst;
}

void GannSquare::OnClick(const POINT& mp, MouseButtonsA button, int clicks, int delta)
{
}

void GannSquare::OnPaintBackground(CPaint *paint, const RECT& clipRect)
{
}

void GannSquare::ReCreate()
{
}

void GannSquare::SetProperty(const wstring& name, const wstring& value)
{
}

void GannSquare::Update()
{
}
