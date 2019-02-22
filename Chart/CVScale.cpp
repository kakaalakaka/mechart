#include "..\\stdafx.h"
#include "..\\include\\Chart\\CVScale.h"
using namespace MeLib;

CVScaleMe::CVScaleMe()
{
	m_allowUserPaint = false;
	m_autoMaxMin = true;
	m_baseField = CTableMe::NULLFIELD();
	m_crossLineTip = new CCrossLineTipMe();
	m_digit = 0;
	m_font = new FONT(L"Arial", 14.0f, true, false, false, false);
	m_foreColor = COLOR::ARGB(255, 82, 82);
	m_foreColor2 = COLOR_EMPTY;
	m_magnitude = 1;
	m_midValue = 0;
	m_numberStyle = NumberStyle_Standard;
	m_paddingBottom = 0;
	m_paddingTop = 0;
	m_reverse = false;
	m_scaleColor = COLOR::ARGB(150, 0, 0);
	m_system = VScaleSystem_Standard;
	m_type = VScaleType_EqualDiff;
	m_visibleMax = 0.0;
	m_visibleMin = 0.0;
}

CVScaleMe::~CVScaleMe()
{
	if (m_crossLineTip)
	{
		delete m_crossLineTip;
	}
	m_crossLineTip = 0;
	if (m_font)
	{
		delete m_font;
	}
	m_font = 0;
	m_scaleSteps.clear();
}

bool CVScaleMe::AllowUserPaint()
{
	return m_allowUserPaint;
}

void CVScaleMe::SetAllowUserPaint( bool allowUserPaint )
{
	m_allowUserPaint = allowUserPaint;
}

bool CVScaleMe::AutoMaxMin()
{
	return m_autoMaxMin;
}

void CVScaleMe::SetAutoMaxMin( bool autoMaxMin )
{	
	m_autoMaxMin = autoMaxMin;
}

int CVScaleMe::GetBaseField()
{
	return m_baseField;
}

void CVScaleMe::SetBaseField( int baseField )
{
	m_baseField = baseField;
}

CCrossLineTipMe* CVScaleMe::GetCrossLineTip()
{
	return m_crossLineTip;
}

int CVScaleMe::GetDigit()
{
	return m_digit;
}

void CVScaleMe::SetDigit( int digit )
{
	m_digit = digit;
}

FONT* CVScaleMe::GetFont()
{
	return m_font;
}

void CVScaleMe::SetFont( FONT *font )
{
	m_font->Copy(font);
}

_int64 CVScaleMe::GetForeColor()
{
	return m_foreColor;
}

void CVScaleMe::SetForeColor( _int64 foreColor )
{
	m_foreColor = foreColor;
}

_int64 CVScaleMe::GetForeColor2()
{
	return m_foreColor2;
}

void CVScaleMe::SetForeColor2( _int64 foreColor2 )
{
	m_foreColor2 = foreColor2;
}

int CVScaleMe::GetMagnitude()
{
	return m_magnitude;
}

void CVScaleMe::SetMagnitude( int magnitude )
{
	m_magnitude = magnitude;
}

double CVScaleMe::GetMidValue()
{
	return m_midValue;
}

void CVScaleMe::SetMidValue( double midValue )
{
	m_midValue = midValue;
}

NumberStyle CVScaleMe::GetNumberStyle()
{
	return m_numberStyle;
}

void CVScaleMe::SetNumberStyle( NumberStyle numberStyle )
{
	m_numberStyle = numberStyle;
}

int CVScaleMe::GetPaddingBottom()
{
	return m_paddingBottom;
}

void CVScaleMe::SetPaddingBottom( int paddingBottom )
{
	m_paddingBottom = paddingBottom;
}

int CVScaleMe::GetPaddingTop()
{
	return m_paddingTop;
}

void CVScaleMe::SetPaddingTop( int paddingTop )
{
	m_paddingTop = paddingTop;
}

bool CVScaleMe::IsReverse()
{
	return m_reverse;
}

void CVScaleMe::SetReverse( bool reverse )
{
	m_reverse = reverse;
}

_int64 CVScaleMe::GetScaleColor()
{
	return m_scaleColor;
}

void CVScaleMe::SetScaleColor( _int64 scaleColor )
{
	m_scaleColor = scaleColor;
}

VScaleSystem CVScaleMe::GetSystem()
{
	return m_system;
}

void CVScaleMe::SetSystem( VScaleSystem system )
{
	m_system = system;
}

VScaleType CVScaleMe::GetType()
{
	return m_type;
}

void CVScaleMe::SetType( VScaleType type )
{
	m_type = type;
}

double CVScaleMe::GetVisibleMax()
{
	return m_visibleMax;
}

void CVScaleMe::SetVisibleMax( double visibleMax )
{
	m_visibleMax = visibleMax;
}

double CVScaleMe::GetVisibleMin()
{
	return m_visibleMin;
}

void CVScaleMe::SetVisibleMin( double visibleMin )
{
	m_visibleMin = visibleMin;
}

void CVScaleMe::GetProperty( const String& name, String *value, String *type )
{
	if(name == L"allowuserpaint")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
	}
	else if(name == L"automaxmin")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AutoMaxMin());
	}
	else if(name == L"basefield")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetBaseField());
	}
	else if(name == L"digit")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetDigit());
	}
	else if(name == L"font")
	{
		*type = L"font";
		*value = CStrMe::ConvertFontToStr(GetFont());
	}
	else if(name == L"forecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetForeColor());
	}
	else if(name == L"forecolor2")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetForeColor2());
	}
	else if(name == L"magnitude")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetMagnitude());
	}
	else if(name == L"midvalue")
	{
		*type = L"double";
		*value = CStrMe::ConvertDoubleToStr(GetMidValue());
	}
	else if(name == L"numberstyle")
	{
		*type = L"enum:NumberStyle";
		NumberStyle style = GetNumberStyle();
		if(style == NumberStyle_Standard)
		{
			*value = L"Standard";
		}
		else
		{
			*value = L"UnderLine";
		}
	}
	else if(name == L"paddingbottom")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetPaddingBottom());
	}
	else if(name == L"paddingtop")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetPaddingTop());
	}
	else if(name == L"reverse")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsReverse());
	}
	else if(name == L"scalecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetScaleColor());
	}
	else if(name == L"system")
	{
		*type = L"enum:VScaleSystem";
		VScaleSystem system = GetSystem();
		if(system == VScaleSystem_Logarithmic)
		{
			*value = L"Log";
		} 
		else
		{
			*value = L"Standard";
		}
	}
	else if(name == L"type")
	{
		*type = L"enum:VScaleType";
		VScaleType vScaleType = GetType();
		if(vScaleType == VScaleType_Divide)
		{
			*value = L"Divide";
		}
		else if(vScaleType == VScaleType_EqualDiff)
		{
			*value = L"EqualDiff";
		}
		else if(vScaleType == VScaleType_EqualRatio)
		{
			*value = L"EqualRatio";
		}
		else if(vScaleType == VScaleType_GoldenRatio)
		{
			*value = L"GoldenRatio";
		}
		else
		{
			*value = L"Percent";
		}
	}
	else if(name == L"visiblemax")
	{
		*type = L"double";
		*value = CStrMe::ConvertDoubleToStr(GetVisibleMax());
	}
	else if(name == L"visiblemin")
	{
		*type = L"double";
		*value = CStrMe::ConvertDoubleToStr(GetVisibleMin());
	}
}

vector<String> CVScaleMe::GetPropertyNames()
{
	static String arr[] = {L"AllowUserPaint", L"AutoMaxMin", L"BaseField", L"Digit", L"Font", 
		L"ForeColor", L"ForeColor2", L"Magnitude", L"MidValue", L"NumberStyle", L"PaddingBottom", 
		L"PaddingTop", L"Reverse", L"ScaleColor", L"System", L"Type", L"VisibleMax", L"VisibleMin"};
	vector<String> propertyNames(arr, arr + _countof(arr));
	return propertyNames;
}

vector<double> CVScaleMe::GetScaleSteps()
{
	return m_scaleSteps;
}

void CVScaleMe::OnPaint( CPaintMe *paint, CDivMe *div, const RECT& rect )
{

}

void CVScaleMe::SetProperty( const String& name, const String& value )
{
	if(name == L"allowuserpaint")
	{
		SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
	}
	else if(name == L"automaxmin")
	{
		SetAutoMaxMin(CStrMe::ConvertStrToBool(value));
	}
	else if(name == L"basefield")
	{
		SetBaseField(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"digit")
	{
		SetDigit(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"font")
	{
		SetFont(CStrMe::ConvertStrToFont(value));
	}
	else if(name == L"forecolor")
	{
		SetForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"forecolor2")
	{
		SetForeColor2(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"magnitude")
	{
		SetMagnitude(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"midvalue")
	{
		SetMidValue(CStrMe::ConvertStrToDouble(value));
	}
	else if(name == L"numberstyle")
	{
		String temp = CStrMe::ToLower(value);
		if(temp == L"standard")
		{
			SetNumberStyle(NumberStyle_Standard);
		}
		else
		{
			SetNumberStyle(NumberStyle_Underline);
		}
	}
	else if(name == L"paddingbottom")
	{
		SetPaddingBottom(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"paddingtop")
	{
		SetPaddingTop(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"reverse")
	{
		SetReverse(CStrMe::ConvertStrToBool(value));
	}
	else if(name == L"scalecolor")
	{
		SetScaleColor(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"system")
	{
		if(value == L"log")
		{
			SetSystem(VScaleSystem_Logarithmic);
		}
		else
		{
			SetSystem(VScaleSystem_Standard);
		}
	}
	else if(name == L"type")
	{
		if(value == L"Divide")
		{
			SetType(VScaleType_Divide);
		}
		else if(value == L"equaldiff")
		{
			SetType(VScaleType_EqualDiff);
		}
		else if(value == L"equalratio")
		{
			SetType(VScaleType_EqualRatio);
		}
		else if(value == L"goldenratio")
		{
			SetType(VScaleType_GoldenRatio);
		}
		else
		{
			SetType(VScaleType_Percent);
		}
	}
	else if(name == L"visiblemax")
	{
		SetVisibleMax(CStrMe::ConvertStrToDouble(value));
	}
	else if(name == L"visiblemin")
	{
		SetVisibleMin(CStrMe::ConvertStrToDouble(value));
	}
}

void CVScaleMe::SetScaleSteps( vector<double> scaleSteps )
{
	m_scaleSteps = scaleSteps;
}