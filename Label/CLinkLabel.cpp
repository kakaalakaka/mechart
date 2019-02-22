#include "..\\stdafx.h"
#include "..\\include\\Label\\CLinkLabel.h"
using namespace MeLib;

_int64 CLinkLabelMe::GetPaintingLinkColor()
{
	if (!IsEnabled())
	{
		return m_disabledLinkColor;
	}
	CNativeBaseMe *native = GetNative();
	if (this == native->GetHoveredControl())
	{
		return m_activeLinkColor;
	}
	if (this == native->GetPushedControl())
	{
		return m_activeLinkColor;
	}
	if (m_linkVisited && m_visited)
	{
		return m_visitedLinkColor;
	}
	return m_linkColor;
}

CLinkLabelMe::CLinkLabelMe()
{
	m_activeLinkColor = COLOR::ARGB(255, 0, 0);
	m_disabledLinkColor = COLOR::ARGB(133, 133, 133);
	m_linkColor = COLOR::ARGB(0, 0, 255);
	m_linkVisited = false;
	m_visited = false;
	m_visitedLinkColor = COLOR::ARGB(128, 0, 128);
	SetCursor(CursorsMe_Hand);
}

CLinkLabelMe::~CLinkLabelMe()
{

}

_int64 CLinkLabelMe::GetActiveLinkColor()
{
	return m_activeLinkColor;
}

void CLinkLabelMe::SetActiveLinkColor( _int64 activeLinkColor )
{
	m_activeLinkColor = activeLinkColor;
}

_int64 CLinkLabelMe::GetDisabledLinkColor()
{
	return m_disabledLinkColor;
}

void CLinkLabelMe::SetDisabledLinkColor( _int64 disabledLinkColor )
{
	m_disabledLinkColor = disabledLinkColor;
}

LinkBehaviorMe CLinkLabelMe::GetLinkBehavior()
{
	return m_linkBehavior;
}

void CLinkLabelMe::SetLinkBehavior( LinkBehaviorMe linkBehavior )
{
	m_linkBehavior = linkBehavior;
}

_int64 CLinkLabelMe::GetLinkColor()
{
	return m_linkColor;
}

void CLinkLabelMe::SetLinkColor( _int64 linkColor )
{
	m_linkColor = linkColor;
}

bool CLinkLabelMe::IsLinkVisited()
{
	return m_linkVisited;
}

void CLinkLabelMe::SetLinkVisited( bool linkVisited )
{
	m_linkVisited = linkVisited;
}

_int64 CLinkLabelMe::GetVisitedLinkColor()
{
	return m_visitedLinkColor;
}

void CLinkLabelMe::SetVisitedLinkColor( _int64 visitedLinkColor )
{
	m_visitedLinkColor = visitedLinkColor;
}

String CLinkLabelMe::GetControlType()
{
	return L"LinkLabel";
}

void CLinkLabelMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"activelinkcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetActiveLinkColor());
	}
	else if (name == L"disabledlinkcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetDisabledLinkColor());
	}
	else if (name == L"linkbehavior")
	{
		*type = L"enum:LinkBehaviorMe";
		switch (GetLinkBehavior())
		{
		case LinkBehaviorMe_AlwaysUnderLine:
			*value = L"AlwaysUnderLine";
			return;
		case LinkBehaviorMe_HoverUnderLine:
			*value = L"HoverUnderLine";
			return;
		}
		*value = L"NeverUnderLine";
	}
	else if (name == L"linkcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetLinkColor());
	}
	else if (name == L"linkvisited")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsLinkVisited());
	}
	else if (name == L"visitedlinkcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetVisitedLinkColor());
	}
	else
	{
		CLabelMe::GetProperty(name, value, type);
	}
}

vector<String> CLinkLabelMe::GetPropertyNames()
{
	vector<wstring> propertyNames = CControlMe::GetEventNames();
	propertyNames.push_back(L"ActiveLinkColor");
	propertyNames.push_back(L"DisabledLinkColor");
	propertyNames.push_back(L"LinkBehavior");
	propertyNames.push_back(L"LinkColor");
	propertyNames.push_back(L"LinkVisited");
	propertyNames.push_back(L"VisitedLinkColor");
	return propertyNames;
}

void CLinkLabelMe::OnClick( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnClick(mp, button, clicks, delta);
	if (m_linkVisited)
	{
		m_visited = true;
	}
}

void CLinkLabelMe::OnMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseDown(mp, button, clicks, delta);
	Invalidate();
}

void CLinkLabelMe::OnMouseEnter( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseEnter(mp, button, clicks, delta);
	Invalidate();
}

void CLinkLabelMe::OnMouseLeave( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseLeave(mp, button, clicks, delta);
	Invalidate();
}

void CLinkLabelMe::OnMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CControlMe::OnMouseUp(mp, button, clicks, delta);
	Invalidate();
}

void CLinkLabelMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	String text = GetText();
	if (!text.empty())
	{
		int width = GetWidth();
		int height = GetHeight();
		if (width > 0 && height > 0)
		{
			FONT *font = GetFont();
			SIZE size = paint->TextSize(text.c_str(), font);
			_int64 paintingLinkColor = GetPaintingLinkColor();
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
			if (AutoEllipsis() && (rect.right > clipRect.right || rect.bottom > clipRect.bottom))
			{
				if (rect.right > clipRect.right)
				{
					rect.right = clipRect.right;
				}
				if (rect.bottom > clipRect.bottom)
				{
					rect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(text.c_str(), paintingLinkColor, font, rect);
			}
			else
			{
				paint->DrawText(text.c_str(), paintingLinkColor, font, rect);
			}
			CNativeBaseMe *native = GetNative();
			if (m_linkBehavior == LinkBehaviorMe_AlwaysUnderLine 
				|| m_linkBehavior == LinkBehaviorMe_HoverUnderLine
				&& (this == native->GetPushedControl() || this == native->GetHoveredControl()))
			{
				paint->DrawLine(paintingLinkColor, 1.0f, 0, point.x, point.y + size.cy, point.x + size.cx, point.y + size.cy);
			}
		}
	}
}

void CLinkLabelMe::SetProperty( const String& name, const String& value )
{
	if (name == L"activelinkcolor")
	{
		SetActiveLinkColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"disabledlinkcolor")
	{
		SetDisabledLinkColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"linkbehavior")
	{
		String temp = CStrMe::ToLower(value);
		if (temp == L"alwaysunderline")
		{
			SetLinkBehavior(LinkBehaviorMe_AlwaysUnderLine);
		}
		else if (temp == L"hoverunderline")
		{
			SetLinkBehavior(LinkBehaviorMe_HoverUnderLine);
		}
		else
		{
			SetLinkBehavior(LinkBehaviorMe_NeverUnderLine);
		}
	}
	else if (name == L"linkcolor")
	{
		SetLinkColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"linkvisited")
	{
		SetLinkVisited(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"visitedlinkcolor")
	{
		SetVisitedLinkColor(CStrMe::ConvertStrToColor(value));
	}
	else
	{
		CLabelMe::SetProperty(name, value);
	}
}