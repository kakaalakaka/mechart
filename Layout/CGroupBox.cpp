#include "..\\stdafx.h"
#include "..\\include\\Layout\\CGroupBox.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CGroupBoxMe::CGroupBoxMe()
{

}

CGroupBoxMe::~CGroupBoxMe()
{

}

String CGroupBoxMe::GetControlType()
{
	return L"GroupBox";
}

void CGroupBoxMe::OnPaintBorder( CPaintMe *paint, const RECT& clipRect )
{
	FONT *font = GetFont();
	int width = GetWidth();
	int height = GetHeight();
	String text = GetText();
	SIZE size;
	if ((int)text.length() > 0)
	{
		size = paint->TextSize(text.c_str(), font);
	}
	else
	{
		size = paint->TextSize(L"0", font);
		size.cx = 0;
	}
	POINT points[6];
	int y = size.cy / 2;
	int x = 2;
	points[0].x = 10;
	points[0].y = y;
	points[1].x = x;
	points[1].y = y;
	points[2].x = x;
	points[2].y = height - x;
	points[3].x = width - x;
	points[3].y = height - x;
	points[4].x = width - x;
	points[4].y = y;
	points[5].x = 14 + size.cx;
	points[5].y = y;
	paint->DrawPolyline(GetPaintingBorderColor(), 1.0f, 0, points, 6);
	CControlMe::CallPaintEvents(EVENTID::PAINTBORDER, paint, clipRect);
}

void CGroupBoxMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	String text = GetText();
	if ((int)text.length() > 0)
	{
		FONT *font = GetFont();
		SIZE size = paint->TextSize(text.c_str(), font);
		RECT rect = {12, 0, 12 + size.cx, size.cy};
		paint->DrawText(text.c_str(), GetPaintingForeColor(), font, rect);
	}
}