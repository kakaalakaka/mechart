#include "..\\..\\stdafx.h"
#include "CSquareCell.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSquareCellMe::CSquareCellMe()
{
	m_number = 0;
	m_selected = false;
	m_style = SquareCellStyle_Normal;
	m_gannSquare = 0;
}

CSquareCellMe::~CSquareCellMe()
{
}

_int64 CSquareCellMe::GetBackColor()
{
	return COLOR_EMPTY;
}

RECT CSquareCellMe::GetBounds()
{
	return m_bounds;
}

void CSquareCellMe::SetBounds(RECT bounds)
{
	m_bounds = bounds;
}

_int64 CSquareCellMe::GetForeColor()
{
	return COLOR_EMPTY;
}

int CSquareCellMe::GetNumber()
{
	return m_number;
}

void CSquareCellMe::SetNumber(int number)
{
	m_number = number;
}

bool CSquareCellMe::IsSelected()
{
	return m_selected;
}

void CSquareCellMe::SetSelected(bool selected)
{
	m_selected = selected;
}

SquareCellStyle CSquareCellMe::GetStyle()
{
	return m_style;
}

void CSquareCellMe::SetStyle(SquareCellStyle style)
{
	m_style = style;
}

double CSquareCellMe::GetValue()
{
	return 0;
}

void CSquareCellMe::OnPaint()
{
}
