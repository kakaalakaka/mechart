#include "..\\stdafx.h"
#include "..\\include\\Chart\\CPlot.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
AttachVScale CPlotMe::GetAttachVScale()
{
	return AttachVScale_Left;
}

void CPlotMe::SetAttachVScale(AttachVScale attachVScale)
{
}

_int64 CPlotMe::GetColor()
{
	return COLOR_EMPTY;
}

void CPlotMe::SetColor(_int64 color)
{
}

CDivMe* CPlotMe::GetDiv()
{
	return 0;
}

void CPlotMe::SetDiv(CDivMe *div)
{
}

bool CPlotMe::DrawGhost()
{
	return false;
}

void CPlotMe::SetDrawGhost(bool drawGhost)
{
}

bool CPlotMe::IsEnabled()
{
	return false;
}

void CPlotMe::SetEnabled(bool enabled)
{
}

FONT* CPlotMe::GetFont()
{
	return 0;
}

void CPlotMe::SetFont(FONT *font)
{
}

int CPlotMe::GetLineStyle()
{
	return 0;
}

void CPlotMe::SetLineStyle(int lineStyle)
{
}

int CPlotMe::GetLineWidth()
{
	return 0;
}

void CPlotMe::SetLineWidth(int lineWidth)
{
}

String CPlotMe::GetPlotType()
{
	return L"";
}

void CPlotMe::SetPlotType(const String& plotType)
{
}

bool CPlotMe::IsSelected()
{
	return false;
}

void CPlotMe::SetSelected(bool selected)
{
}

_int64 CPlotMe::GetSelectedColor()
{
	return COLOR_EMPTY;
}

void CPlotMe::SetSelectedColor(_int64 selectedColor)
{
}

SelectPoint CPlotMe::GetSelectedPoint()
{
	return SelectPoint_Rect;
}

void CPlotMe::SetSelectedPoint(SelectPoint selectedPoint)
{
}

String CPlotMe::GetText()
{
	return L"";
}

void CPlotMe::SetText(const String& text)
{
}

bool CPlotMe::IsVisible()
{
	return false;
}

void CPlotMe::SetVisible(bool visible)
{
}

int CPlotMe::GetZOrder()
{
	return 0;
}

void CPlotMe::SetZOrder(int zOrder)
{

}

bool CPlotMe::OnCreate(const POINT& mp)
{
	return false;
}

void CPlotMe::OnMoveEnd()
{
}

void CPlotMe::OnMoveStart()
{
}

void CPlotMe::OnMoving()
{
}

bool CPlotMe::OnSelect()
{
	return false;
}

void CPlotMe::Render(CPaintMe *paint)
{
}