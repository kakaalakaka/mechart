#include "..\\stdafx.h"
#include "..\\include\\Chart\\CToolTip.h"

namespace MeLib
{
	CToolTipMe::CToolTipMe()
	{
		m_allowUserPaint = false;
		m_backColor = COLOR::ARGB(255, 255, 128);
		m_borderColor = COLOR::ARGB(255, 255, 80);
		m_font = new FONT();
		m_foreColor = COLOR::ARGB(0, 0, 0);
	}
	
	CToolTipMe::~CToolTipMe()
	{
		if(m_font)
		{
			delete m_font;
		}
		m_font = 0;
	}
	
	bool CToolTipMe::AllowUserPaint()
	{
		return m_allowUserPaint;
	}
	
	void CToolTipMe::SetAllowUserPaint(bool allowUserPaint)
	{
		m_allowUserPaint = allowUserPaint;
	}

	_int64 CToolTipMe::GetBackColor()
	{
		return m_backColor;
	}

	void CToolTipMe::SetBackColor(_int64 backColor)
	{
		m_backColor =backColor;
	}

	_int64 CToolTipMe::GetBorderColor()
	{
		return m_borderColor;
	}

	void CToolTipMe::SetBorderColor(_int64 borderColor)
	{
		m_borderColor = borderColor;
	}

	FONT* CToolTipMe::GetFont()
	{
		return m_font;
	}

	void CToolTipMe::SetFont(FONT *font)
	{
		m_font->Copy(font);
	}

	_int64 CToolTipMe::GetForeColor()
	{
		return m_foreColor;
	}

	void CToolTipMe::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}

	void CToolTipMe::GetProperty(const String& name, String *value, String *type)
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
		else if (szName == L"bordercolor")
		{
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetBorderColor());
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
	}
	
	vector<String> CToolTipMe::GetPropertyNames()
	{
		 vector<String> propertyNames;
		 propertyNames.push_back(L"AllowUserPaint");
		 propertyNames.push_back(L"BackColor");
		 propertyNames.push_back(L"BorderColor");
		 propertyNames.push_back(L"Font");
		 propertyNames.push_back(L"ForeColor");
		return propertyNames;
	}

	void CToolTipMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
	{
	}

	void CToolTipMe::SetProperty(const String& name, const String& value)
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
		else if (szName == L"bordercolor")
		{
			SetBorderColor(CStrMe::ConvertStrToColor(value));
		}
		else if (szName == L"font")
		{
			SetFont(CStrMe::ConvertStrToFont(value));
		}
		else if (szName == L"forecolor")
		{
			SetForeColor(CStrMe::ConvertStrToColor(value));
		}
	}
}