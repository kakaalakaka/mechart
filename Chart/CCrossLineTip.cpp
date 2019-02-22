#include "..\\stdafx.h"
#include "..\\include\\Chart\\CCrossLineTip.h"

CCrossLineTipMe::CCrossLineTipMe()
{
	m_allowUserPaint = 0;
	m_backColor = COLOR::ARGB(255, 0, 0);
	m_font = new FONT(L"Arial", 12.0, 0, 0, 0, 0);
	m_foreColor = COLOR::ARGB(255, 255, 255);
	m_visible = true;
}

CCrossLineTipMe::~CCrossLineTipMe()
{
	if(m_font)
	{
		delete m_font;
	}
	m_font = 0;
}

bool CCrossLineTipMe::AllowUserPaint()
{
	return m_allowUserPaint;
}

void CCrossLineTipMe::SetAllowUserPaint(bool allowUserPaint)
{
	m_allowUserPaint = allowUserPaint;
}

_int64 CCrossLineTipMe::GetBackColor()
{
	return m_backColor;
}

void CCrossLineTipMe::SetBackColor(_int64 backColor)
{
	m_backColor = backColor;
}

FONT* CCrossLineTipMe::GetFont()
{
	return m_font;
}

void CCrossLineTipMe::SetFont(FONT *font)
{
	m_font->Copy(font);
}

_int64 CCrossLineTipMe::GetForeColor()
{
	 return m_foreColor;
}

void CCrossLineTipMe::SetForeColor(_int64 foreColor)
{
	m_foreColor = foreColor;
}

bool CCrossLineTipMe::IsVisible()
{
	return m_visible;
}

void CCrossLineTipMe::SetVisible(bool visible)
{
	m_visible = visible;
}

void CCrossLineTipMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
{
}

void CCrossLineTipMe::GetProperty(const String& name, String *value, String *type)
{
	String szName = CStrMe::ToLower(name);
	if (szName == L"allowuserpaint")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
	}
	else if (szName == L"backcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetBackColor());
	}
	else if (szName == L"font")
	{
		*type = L"font";
		*value = CStrMe::ConvertFontToStr(GetFont());
	}
	else if (szName == L"forecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetForeColor());
	}
	else if (szName == L"visible")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsVisible());
	}
}

vector<String> CCrossLineTipMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"AllowUserPaint");
	propertyNames.push_back(L"BackColor");
	propertyNames.push_back(L"Font");
	propertyNames.push_back(L"ForeColor");
	propertyNames.push_back(L"Visible");
	return propertyNames;
}

void CCrossLineTipMe::SetProperty(const String& name, const String& value)
{
	String szName = CStrMe::ToLower(name);
	if (szName == L"allowuserpaint")
	{
		SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
	}
	else if (szName == L"backcolor")
	{
		SetBackColor(CStrMe::ConvertStrToColor(value));
	}
	else if (szName == L"font")
	{
		SetFont(CStrMe::ConvertStrToFont(value));
	}
	else if (szName == L"forecolor")
	{
		SetForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if (szName == L"visible")
	{
		SetVisible(CStrMe::ConvertStrToBool(value));
	}
}