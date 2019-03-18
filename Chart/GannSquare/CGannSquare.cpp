#include "..\\..\\stdafx.h"
#include "CGannSquare.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CGannSquareMe::CGannSquareMe()
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

CGannSquareMe::~CGannSquareMe()
{
	vector<CSquareCellMe*>::iterator sIter = m_cells.begin();
	for(; sIter != m_cells.end(); ++sIter)
	{
		delete *sIter;
		*sIter = 0;
	}
	m_cells.clear();
}

BolsterOrStress CGannSquareMe::GetBolsterOrStress()
{
	return m_bolsterOrStress;
}

void CGannSquareMe::SetBolsterOrStress(BolsterOrStress bolsterOrStress)
{
	m_bolsterOrStress = bolsterOrStress;
}

FONT* CGannSquareMe::GetCellFont()
{
	return m_cellFont;
}

void CGannSquareMe::SetCellFont(FONT *cellFont)
{
	m_cellFont = cellFont;
}

SIZE CGannSquareMe::GetCellSize()
{
	return m_cellSize;
}

void CGannSquareMe::SetCellSize(SIZE cellSize)
{
	m_cellSize = m_cellSize;
}

int CGannSquareMe::GetDigit()
{
	return m_digit;
}

void CGannSquareMe::SetDigit(int digit)
{
	m_digit = digit;
}

_int64 CGannSquareMe::GetMajorColor()
{
	return m_majorColor;
}

void CGannSquareMe::SetMajorColor(_int64 majorColor)
{
	m_majorColor = majorColor;
}

_int64 CGannSquareMe::GetMinorColor()
{
	return m_minorColor;
}

void CGannSquareMe::SetMinorColor(_int64 minorColor)
{
	m_minorColor = minorColor;
}

_int64 CGannSquareMe::GetNormalColor()
{
	return m_normalColor;
}

void CGannSquareMe::SetNormalColor(_int64 normalColor)
{
	m_normalColor = normalColor;
}

int CGannSquareMe::GetNumber()
{
	return m_number;
}

void CGannSquareMe::SetNumber(int number)
{
	m_number = number;
}

_int64 CGannSquareMe::GetSelectedColor()
{
	return m_selectedColor;
}

void CGannSquareMe::SetSelectedColor(_int64 selectedColor)
{
	m_selectedColor = selectedColor;
}

double CGannSquareMe::GetSelectedValue()
{
	return 0;
}

double CGannSquareMe::GetStartValue()
{
	return m_startValue;
}

void CGannSquareMe::SetStartValue(double startValue)
{
	m_startValue = startValue;
}

SquareStyle CGannSquareMe::GetStyle()
{
	return m_style;
}

void CGannSquareMe::SetStyle(SquareStyle style)
{
	m_style = style;
}

wstring CGannSquareMe::GetSuffix()
{
	return m_suffix;
}

void CGannSquareMe::SetSuffix(const wstring& suffix)
{
	m_suffix = suffix;
}

double CGannSquareMe::GetUnit()
{
	return m_unit;
}

void CGannSquareMe::SetUnit(double unit)
{
	m_unit = unit;
}


void CGannSquareMe::GetProperty(const wstring& name, wstring *value, wstring *type)
{
}

vector<wstring> CGannSquareMe::GetPropertyNames()
{
	vector<wstring> lst;
	return lst;
}

void CGannSquareMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
}

void CGannSquareMe::OnPaintBackground(CPaintMe *paint, const RECT& clipRect)
{
}

void CGannSquareMe::ReCreate()
{
}

void CGannSquareMe::SetProperty(const wstring& name, const wstring& value)
{
}

void CGannSquareMe::Update()
{
}
