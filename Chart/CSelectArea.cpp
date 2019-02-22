#include "..\\stdafx.h"
#include "..\\include\\Chart\\CSelectArea.h"
using namespace MeLib;

CSelectAreaMe::CSelectAreaMe()
{
	m_allowUserPaint = false;
	m_backColor = COLOR_EMPTY;
	m_enabled = true;
	m_canResize = true;
	m_lineColor = COLOR::ARGB(255, 255, 255);
	m_visible = false;
}

CSelectAreaMe::~CSelectAreaMe()
{

}

bool CSelectAreaMe::AllowUserPaint()
{
	return m_allowUserPaint;
}

void CSelectAreaMe::SetAllowUserPaint( bool allowUserPaint )
{
	m_allowUserPaint = allowUserPaint;
}

_int64 CSelectAreaMe::GetBackColor()
{
	return m_backColor;
}

void CSelectAreaMe::SetBackColor( _int64 backColor )
{
	m_backColor = backColor;
}

RECT CSelectAreaMe::GetBounds()
{
	return m_bounds;
}

void CSelectAreaMe::SetBounds( RECT bounds )
{
	m_bounds = bounds;
}

bool CSelectAreaMe::CanResize()
{
	return m_canResize;
}

void CSelectAreaMe::SetCanResize( bool canResize )
{
	m_canResize = canResize;
}

bool CSelectAreaMe::IsEnabled()
{
	return m_enabled;
}

void CSelectAreaMe::SetEnabled( bool enabled )
{
	m_enabled = enabled;
}

_int64 CSelectAreaMe::GetLineColor()
{
	return m_lineColor;
}

void CSelectAreaMe::SetLineColor( _int64 lineColor )
{
	m_lineColor = lineColor;
}

bool CSelectAreaMe::IsVisible()
{
	return m_visible;
}

void CSelectAreaMe::SetVisible( bool visible )
{
	m_visible = visible;
}

void CSelectAreaMe::Close()
{
    m_visible = false;
    m_canResize = false;
}

void CSelectAreaMe::GetProperty( const String& name, String *value, String *type )
{
	String szName = CStrMe::ToLower(name);
	if (szName == L"allowuserpaint")
    {
      *type = L"bool";
      *value = CStrMe::ConvertBoolToStr(AllowUserPaint());
    }
    else if (szName == L"enabled")
    {
      *type = L"bool";
      *value = CStrMe::ConvertBoolToStr(IsEnabled());
    }
    else if (szName == L"linecolor")
    {
      *type = L"color";
      *value = CStrMe::ConvertColorToStr(GetLineColor());
    }
}

vector<String> CSelectAreaMe::GetPropertyNames()
{
	vector<String> propertyNames;
    propertyNames.push_back(L"AllowUserPaint");
    propertyNames.push_back(L"Enabled");
    propertyNames.push_back(L"LineColor");
    return propertyNames;
}

void CSelectAreaMe::OnPaint( CPaintMe *paint, CDivMe *div, const RECT& rect )
{

}

void CSelectAreaMe::SetProperty( const String& name, const String& value )
{
	String szName = CStrMe::ToLower(name);
	if (szName == L"allowuserpaint")
    {
      SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
    }
    else if (szName == L"enabled")
    {
      SetEnabled(CStrMe::ConvertStrToBool(value));
    }
    else if (szName == L"linecolor")
    {
     SetLineColor(CStrMe::ConvertStrToColor(value));
    }
}