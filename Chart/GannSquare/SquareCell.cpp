#include "..\\..\\stdafx.h"
#include "SquareCell.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SquareCell::SquareCell()
{
	m_number = 0;
	m_selected = false;
	m_style = SquareCellStyle_Normal;
	m_gannSquare = 0;
}

SquareCell::~SquareCell()
{
}

_int64 SquareCell::GetBackColor()
{
	return COLOR_EMPTY;
}

RECT SquareCell::GetBounds()
{
	return m_bounds;
}

void SquareCell::SetBounds(RECT bounds)
{
	m_bounds = bounds;
}

_int64 SquareCell::GetForeColor()
{
	return COLOR_EMPTY;
}

int SquareCell::GetNumber()
{
	return m_number;
}

void SquareCell::SetNumber(int number)
{
	m_number = number;
}

bool SquareCell::IsSelected()
{
	return m_selected;
}

void SquareCell::SetSelected(bool selected)
{
	m_selected = selected;
}

SquareCellStyle SquareCell::GetStyle()
{
	return m_style;
}

void SquareCell::SetStyle(SquareCellStyle style)
{
	m_style = style;
}

double SquareCell::GetValue()
{
	return 0;
}

void SquareCell::OnPaint()
{
}
