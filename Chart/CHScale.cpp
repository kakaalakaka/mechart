#include "..\\stdafx.h"
#include "..\\include\\Chart\\CHScale.h"
using namespace MeLib;

CHScaleMe::CHScaleMe()
{
	m_dateColors.insert(make_pair(DateType_Year, COLOR::ARGB(255, 255, 255)));	
	m_dateColors.insert(make_pair(DateType_Month, COLOR::ARGB(150, 0, 0)));
	m_dateColors.insert(make_pair(DateType_Day, COLOR::ARGB(100, 100, 100)));
	m_dateColors.insert(make_pair(DateType_Hour, COLOR::ARGB(0, 0, 255)));
	m_dateColors.insert(make_pair(DateType_Minute, COLOR::ARGB(255, 255, 0)));
	m_dateColors.insert(make_pair(DateType_Second, COLOR::ARGB(255, 0, 255)));
	m_dateColors.insert(make_pair(DateType_Millisecond, COLOR::ARGB(255, 0, 255)));

	m_allowUserPaint = false;
	m_crossLineTip = new CCrossLineTipMe();
	m_font = new FONT();
	m_foreColor = COLOR::ARGB(255, 255, 255);
	m_height = 0;
	m_hScaleType = HScaleType_Date;
	m_interval = 60;
	m_scaleColor = COLOR::ARGB(150, 0, 0);
	m_visible = true;

}

CHScaleMe::~CHScaleMe()
{
	if(m_crossLineTip)
	{
		delete m_crossLineTip;
	}
	m_crossLineTip = 0;
	m_dateColors.clear();
	if(m_font)
	{
		delete m_font;
	}
	m_font = 0;
}

bool CHScaleMe::AllowUserPaint()
{
	return m_allowUserPaint;
}

void CHScaleMe::SetAllowUserPaint(bool allowUserPaint)
{
	m_allowUserPaint = allowUserPaint;
}

CCrossLineTipMe* CHScaleMe::GetCrossLineTip()
{
	return m_crossLineTip;
}

_int64 CHScaleMe::GetDateColor(DateType dateType)
{
	map<DateType, _int64>::iterator it = m_dateColors.find(dateType);
	if(it != m_dateColors.end())
	{
		return it->second;
	}
	return 0;
}

void CHScaleMe::SetDateColor(DateType dateType, _int64 color)
{
	map<DateType, _int64>::iterator it = m_dateColors.find(dateType);
	if(it != m_dateColors.end())
	{
		it->second = color;
	}
	else
	{
		m_dateColors.insert(make_pair(dateType, color));
	}
}

FONT* CHScaleMe::GetFont()
{
	return m_font;
}

void CHScaleMe::SetFont(FONT *font)
{
	m_font->Copy(font);
}

_int64 CHScaleMe::GetForeColor()
{
	return m_foreColor;
}

void CHScaleMe::SetForeColor(_int64 foreColor)
{
	m_foreColor = foreColor;
}

int CHScaleMe::GetHeight()
{
	return m_height;
}

void CHScaleMe::SetHeight(int height)
{
	m_height = height;
}

HScaleType CHScaleMe::GetHScaleType()
{
	return m_hScaleType;
}

void CHScaleMe::SetHScaleType(HScaleType hScaleType)
{
	m_hScaleType = hScaleType;
}

int CHScaleMe::GetInterval()
{
	return m_interval;
}

void CHScaleMe::SetInterval(int interval)
{
	m_interval = interval;
}

_int64 CHScaleMe::GetScaleColor()
{
	return m_scaleColor;
}

void CHScaleMe::SetScaleColor(_int64 scaleColor)
{
	m_scaleColor = scaleColor;
}

bool CHScaleMe::IsVisible()
{
	return m_visible;
}

void CHScaleMe::SetVisible(bool visible)
{
	m_visible = visible;
}

void CHScaleMe::GetProperty(const String& name, String *value, String *type)
{
	String szName = CStrMe::ToLower(name);

	if (szName == L"allowuserpaint")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
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
	else if (szName == L"height")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetHeight());
	}
	else if (szName == L"interval")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetInterval());
	}
	else if (szName == L"scalecolor") 
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetScaleColor());
	}
	else if (szName == L"type")
	{
		*type = L"enum:HScaleType";
		HScaleType hScaleType = GetHScaleType();
		if (hScaleType == HScaleType_Date) 
		{
			*value = L"Date";
		}
		else
		{
			*value = L"Number";
		}
	}
	else  if (szName == L"visible")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsVisible());
	}

}

vector<String> CHScaleMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"AllowUserPaint");
	propertyNames.push_back(L"Font");
	propertyNames.push_back(L"ForeColor");
	propertyNames.push_back(L"Height");
	propertyNames.push_back(L"Interval");
	propertyNames.push_back(L"ScaleColor");
	propertyNames.push_back(L"Type");
	propertyNames.push_back(L"Visible");
    return propertyNames;
}

vector<double> CHScaleMe::GetScaleSteps()
{
	return  m_scaleSteps;
}

void CHScaleMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
{
}

void CHScaleMe::SetProperty(const String& name, const String& value)
{
	String szName = CStrMe::ToLower(name);

	if (szName == L"allowuserpaint")
	{
		SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
	}
	else if (szName == L"font")
	{
		SetFont(CStrMe::ConvertStrToFont(value));
	}
	else if (szName == L"forecolor")
	{
		SetForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if (szName == L"height")
	{
		SetHeight(CStrMe::ConvertStrToInt(value));
	}
	else if (szName == L"interval")
	{
		SetInterval(CStrMe::ConvertStrToInt(value));
	}
	else if (szName == L"scalecolor") 
	{
		SetScaleColor(CStrMe::ConvertStrToColor(value));
	}
	else if (szName == L"type")
	{
		String szValue = CStrMe::ToLower(value);
		if (szValue == L"date") 
		{
			SetHScaleType(HScaleType_Date);
		} 
		else 
		{
			SetHScaleType(HScaleType_Number);
		}
	}
	else  if (szName == L"visible")
	{
		SetVisible(CStrMe::ConvertStrToBool(value));
	}
}

void CHScaleMe::SetScaleSteps(vector<double> scaleSteps)
{
	m_scaleSteps = scaleSteps;
}