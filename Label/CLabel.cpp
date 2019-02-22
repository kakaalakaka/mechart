#include "..\\stdafx.h"
#include "..\\include\\Label\\CLabel.h"
using namespace MeLib;

CLabelMe::CLabelMe()
{
	SetAutoSize(true);
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SetCanFocus(false);
	SIZE sz = {100, 20};
	SetSize(sz);
}

CLabelMe::~CLabelMe()
{

}

ContentAlignmentMe CLabelMe::GetTextAlign()
{
	return m_textAlign;
}

void CLabelMe::SetTextAlign( ContentAlignmentMe textAlign )
{
	m_textAlign = textAlign;
}

String CLabelMe::GetControlType()
{
	return L"Label";
}

void CLabelMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"textalign")
	{
		*type = L"enum:ContentAlignmentMe";
		*value = CStrMe::ConvertContentAlignmentToStr(m_textAlign);
	}
	else
	{
		CControlMe::GetProperty(name, value, type);
	}
}

vector<String> CLabelMe::GetPropertyNames()
{
	vector<String> names = CControlMe::GetPropertyNames();
	names.push_back(L"TextAlign");
	return names;
}

void CLabelMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	String text = GetText();
	if ((int)text.length() > 0)
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			POINT point = {(width - size.cx) / 2, (height - size.cy) / 2};
			PADDING padding = GetPadding();
			switch (m_textAlign)
			{
			case ContentAlignmentMe_BottomCenter:
				point.y = height - size.cy;
				break;

			case ContentAlignmentMe_BottomLeft:
				point.x = padding.left;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentMe_BottomRight:
				point.x = width - size.cx - padding.right;
				point.y = height - size.cy - padding.bottom;
				break;

			case ContentAlignmentMe_MiddleLeft:
				point.x = padding.left;
				break;

			case ContentAlignmentMe_MiddleRight:
				point.x = width - size.cx - padding.right;
				break;

			case ContentAlignmentMe_TopCenter:
				point.y = padding.top;
				break;

			case ContentAlignmentMe_TopLeft:
				point.x = padding.left;
				point.y = padding.top;
				break;

			case ContentAlignmentMe_TopRight:
				point.x = width - size.cx - padding.right;
				point.y = padding.top;
				break;
			}
			RECT rect = {point.x, point.y, point.x + size.cx, point.y + size.cy};
			_int64 paintingForeColor = GetPaintingForeColor();
			if (AutoEllipsis() && (rect.right < clipRect.right || rect.bottom < clipRect.bottom))
			{
				if (rect.right < clipRect.right)
				{
					rect.right = clipRect.right;
				}
				if (rect.bottom < clipRect.bottom)
				{
					rect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(text.c_str(), paintingForeColor, font, rect);
			}
			else
			{
				paint->DrawText(text.c_str(), paintingForeColor, font, rect);
			}
		}
	}
}

void CLabelMe::OnPrePaint( CPaintMe *paint, const RECT& clipRect )
{
	CControlMe::OnPrePaint(paint, clipRect);
	if (AutoSize())
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			String text = GetText();
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			if (AutoSize())
			{
				int cx = size.cx + 4;
				int cy = size.cy + 4;
				if (cx != width || cy != height)
				{
					SIZE sz = {cx, cy};
					SetSize(sz);
				}
			}
		}
	}
}

void CLabelMe::SetProperty( const String& name, const String& value )
{
	if (name == L"textalign")
	{
		SetTextAlign(CStrMe::ConvertStrToContentAlignment(value));
	}
	else
	{
		CControlMe::SetProperty(name, value);
	}
}
