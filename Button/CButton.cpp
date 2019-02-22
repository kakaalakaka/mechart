#include "..\\stdafx.h"
#include "..\\include\\Button\\CButton.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_int64 CButtonMe::GetPaintingBackColor()
{
	_int64 paintingBackColor = CControlMe::GetPaintingBackColor();
	if (paintingBackColor != COLOR_EMPTY && CControlMe::IsPaintEnabled(this))
    {
		CNativeBaseMe* native = CControlMe::GetNative();
        if (this == native->GetPushedControl())
        {
            return COLOR_PUSHEDCONTROL;
        }
        if (this == native->GetHoveredControl())
        {
            paintingBackColor = COLOR_HOVEREDCONTROL;
        }
    }
    return paintingBackColor;
}

String CButtonMe::GetPaintingBackImage()
{           
	String pushedBackImage = L"";
	if (CControlMe::IsPaintEnabled(this))
    {
		CNativeBaseMe* native = CControlMe::GetNative();
        if (this == native->GetPushedControl())
        {
            pushedBackImage = m_pushedBackImage;
        }
        else if (this == native->GetHoveredControl())
        {
            pushedBackImage = m_hoveredBackImage;
        }
    }
    else
    {
        pushedBackImage = m_disabledBackImage;
    }
    if (pushedBackImage != L"")
    {
        return pushedBackImage;
    }
	return CControlMe::GetPaintingBackImage();
}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CButtonMe::CButtonMe()
{
	m_disabledBackImage = L"";
	m_hoveredBackImage = L"";
	m_pushedBackImage = L"";
	m_textAlign = ContentAlignmentMe_MiddleCenter; 
	SIZE size = {60, 20};
	SetSize(size);
}

CButtonMe::~CButtonMe()	
{
	m_textAlign = ContentAlignmentMe_MiddleCenter; 
}

String CButtonMe::GetDisabledBackImage()
{
	return m_disabledBackImage;
}

void CButtonMe::SetDisabledBackImage(const String& disabledBackImage)
{
	m_disabledBackImage = disabledBackImage;
}

String CButtonMe::GetHoveredBackImage()
{
	return m_hoveredBackImage;
}

void CButtonMe::SetHoveredBackImage(const String& hoveredBackImage)
{
	m_hoveredBackImage = hoveredBackImage;
}

String CButtonMe::GetPushedBackImage()
{
	return m_pushedBackImage;
}

void CButtonMe::SetPushedBackImage(const String& pushedBackImage)
{
	m_pushedBackImage = pushedBackImage;
}

ContentAlignmentMe CButtonMe::GetTextAlign()
{
	return m_textAlign;
}

void CButtonMe::SetTextAlign(ContentAlignmentMe textAlign)
{
	m_textAlign = textAlign;
}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CButtonMe::GetControlType()
{
	return L"Button";
}

void CButtonMe::GetProperty(const String& name, String *value, String *type)
{
    if (name == L"disabledbackimage")
    {
        *type = L"text";
        *value = GetDisabledBackImage();
    }
    else if (name == L"hoveredbackimage")
    {
        *type = L"text";
        *value = GetHoveredBackImage();
    }
    else if (name == L"pushedbackimage")
    {
        *type = L"text";
        *value = GetPushedBackImage();
    }
    else if (name == L"textalign")
    {
        *type = L"enum:ContentAlignmentMe";
		*value = CStrMe::ConvertContentAlignmentToStr(GetTextAlign());
    }
    else
    {
		CControlMe::GetProperty(name, value, type);
    }
}

vector<String> CButtonMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"DisabledBackImage");
	propertyNames.push_back(L"HoveredBackImage");
	propertyNames.push_back(L"PushedBackImage");
	propertyNames.push_back(L"TextAlign");
	return propertyNames;
}

void CButtonMe::OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnMouseDown(mp, button, clicks, delta);
	Invalidate();
}

void CButtonMe::OnMouseEnter(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnMouseEnter(mp, button, clicks, delta);
	Invalidate();
}

void CButtonMe::OnMouseLeave(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnMouseLeave(mp, button, clicks, delta);
	Invalidate();
}

void CButtonMe::OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CControlMe::OnMouseUp(mp, button, clicks, delta);
	Invalidate();
}

void CButtonMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
    String text = GetText();
	if ((int)text.size() > 0)
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
			if (AutoEllipsis() && (rect.right > clipRect.right || rect.bottom > clipRect.bottom))
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

void CButtonMe::SetProperty(const String& name, const String& value)
{
    if (name == L"disabledbackimage")
    {
        SetDisabledBackImage(value);
    }
    else if (name == L"hoveredbackimage")
    {
        SetHoveredBackImage(value);
    }
    else if (name == L"pushedbackimage")
    {
        SetPushedBackImage(value);
    }
    else if (name == L"textalign")
    {
		SetTextAlign(CStrMe::ConvertStrToContentAlignment(value));
    }
    else
    {
		CControlMe::SetProperty(name, value);
    }
}		