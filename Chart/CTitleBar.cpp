#include "..\\stdafx.h"
#include "..\\include\\Chart\\CTitleBar.h"
using namespace MeLib;

CTitleMe::CTitleMe( int fieldName, const String& fieldText, _int64 color, int digit, bool visible )
{
	m_digit = digit;
	m_fieldName = fieldName;
	m_fieldText = fieldText;
	m_fieldTextMode = TextMode_Full;
	m_textColor = color;
	m_visible = visible;
	m_fieldTextSeparator = L" ";
}

int CTitleMe::GetDigit()
{
	return m_digit;
}

void CTitleMe::SetDigit( int digit )
{
	m_digit = digit;
}

int CTitleMe::GetFieldName()
{
	return m_fieldName;
}

void CTitleMe::SetFieldName( int fieldName )
{
	m_fieldName = fieldName;
}

String CTitleMe::GetFieldText()
{
	return m_fieldText;
}

void CTitleMe::SetFieldText( const String& fieldText )
{
	m_fieldText = fieldText;
}

TextMode CTitleMe::GetFieldTextMode()
{
	return m_fieldTextMode;
}

void CTitleMe::SetFieldTextMode( TextMode fieldTextMode )
{
	m_fieldTextMode = fieldTextMode;
}

String CTitleMe::GetFieldTextSeparator()
{
	return m_fieldTextSeparator;
}

void CTitleMe::SetFieldTextSeparator( const String& fieldTextSeparator )
{
	m_fieldTextSeparator = fieldTextSeparator;
}

_int64 CTitleMe::GetTextColor()
{
	return m_textColor;
}

void CTitleMe::SetTextColor( _int64 textColor )
{
	m_textColor = textColor;
}

bool CTitleMe::IsVisible()
{
	return m_visible;
}

void CTitleMe::SetVisible( bool visible )
{
	m_visible = visible;
}

void CTitleMe::GetProperty( const String& name, String *value, String *type )
{
	if(name == L"digit")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetDigit());
	}
	else if(name == L"fieldname")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetFieldName());
	}
	else if(name == L"fieldtext")
	{
		*type = L"text";
		*value = GetFieldText();
	}
	else if(name == L"fieldtextmode")
	{
		*type = L"enum:TextMode";
		TextMode fieldTextMode = GetFieldTextMode();
		if(fieldTextMode == TextMode_Field)
		{
			*value = L"field";
		}
		else if(fieldTextMode == TextMode_Full)
		{
			*value = L"full";
		}
		else if(fieldTextMode == TextMode_None)
		{
			*value = L"none";
		}
		else
		{
			*value = L"value";
		}
	}
	else if(name == L"fieldtextseparator")
	{
		*value = GetFieldTextSeparator();
	}
	else if(name == L"textcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetTextColor());
	}
	else if(name == L"visible")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsVisible());
	}
}

vector<String> CTitleMe::GetPropertyNames()
{
	static String arr[] = {L"Digit", L"FieldName", L"FieldText", L"FieldTextMode", L"FieldTextSeparator", L"TextColor", L"Visible"};
	vector<String> propertyNames(arr, arr + _countof(arr));
	return propertyNames;
}

void CTitleMe::SetProperty( const String& name, const String& value )
{
	if(name == L"digit")
	{
		SetDigit(CStrMe::ConvertStrToInt(value));
	} else if(name == L"fieldname")
	{
		SetFieldName(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"fieldtext")
	{
		SetFieldText(value);
	} else if(name == L"fieldtextmode")
	{
		String temp = CStrMe::ToLower(value);
		if(temp == L"field")
		{
			SetFieldTextMode(TextMode_Field);
		}
		else if(temp == L"full")
		{
			SetFieldTextMode(TextMode_Full);
		}
		else if(temp == L"none")
		{
			SetFieldTextMode(TextMode_None);
		}
		else
		{
			SetFieldTextMode(TextMode_None);
		}
	}
	else if(name == L"fieldtextseparator")
	{
		SetFieldTextSeparator(value);
	}
	else if(name == L"textcolor")
	{
		SetTextColor(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"visible")
	{
		SetVisible(CStrMe::ConvertStrToBool(value));
	}
}

CTitleBarMe::CTitleBarMe()
{
	m_allowUserPaint = false;
	m_font = new FONT(L"Arial", 12.0f, true, false, false, false);
	m_foreColor = COLOR::ARGB(255, 255, 255);
	m_height = 22;
	m_maxLine = 5;
	m_showUnderLine = true;
	m_underLineColor = COLOR::ARGB(80, 0, 0);
	m_visible = true;
}

CTitleBarMe::~CTitleBarMe()
{
	if(m_font)
	{
		delete m_font;
	}
	m_font = 0;
	vector<CTitleMe*>::iterator sIter = Titles.begin();
	for(;sIter != Titles.end(); ++sIter)
	{
		if(*sIter)
		{
			delete *sIter;
		}
		*sIter = 0;
	}
	Titles.clear();
}

bool CTitleBarMe::AllowUserPaint()
{
	return m_allowUserPaint;
}

void CTitleBarMe::SetAllowUserPaint( bool allowUserPaint )
{
	m_allowUserPaint = allowUserPaint;
}

FONT* CTitleBarMe::GetFont()
{
	return m_font;
}	

void CTitleBarMe::SetFont( FONT *font )
{
	m_font->Copy(font);
}

_int64 CTitleBarMe::GetForeColor()
{
	return m_foreColor;
}

void CTitleBarMe::SetForeColor( _int64 foreColor )
{
	m_foreColor = foreColor;
}

int CTitleBarMe::GetHeight()
{
	return m_height;
}

void CTitleBarMe::SetHeight( int height )
{
	m_height = height;
}

int CTitleBarMe::GetMaxLine()
{
	return m_maxLine;
}

void CTitleBarMe::SetMaxLine( int maxLine )
{
	m_maxLine = maxLine;
}

bool CTitleBarMe::ShowUnderLine()
{
	return m_showUnderLine;
}

void CTitleBarMe::SetShowUnderLine( bool showUnderLine )
{
	m_showUnderLine = showUnderLine;
}

String CTitleBarMe::GetText()
{
	return m_text;
}

void CTitleBarMe::SetText( const String& text )
{
	m_text = text;
}

_int64 CTitleBarMe::GetUnderLineColor()
{
	return m_underLineColor;
}

void CTitleBarMe::SetUnderLineColor( _int64 underLineColor )
{
	m_underLineColor = underLineColor;
}

bool CTitleBarMe::IsVisible()
{
	return m_visible;
}

void CTitleBarMe::SetVisible( bool visible )
{
	m_visible = visible;
}

void CTitleBarMe::GetProperty( const String& name, String *value, String *type )
{
	if(name == L"allowuserpaint")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
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
	else if(name == L"height")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetHeight());
	}
	else if(name == L"maxline")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetMaxLine());
	}
	else if(name == L"showunderline")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(ShowUnderLine());
	}
	else if(name == L"text")
	{
		*type = L"string";
		*value = GetText();
	}
	else if(name == L"underlinecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetUnderLineColor());
	}
	else if(name == L"visible")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsVisible());
	}
}

vector<String> CTitleBarMe::GetPropertyNames()
{
	static String arr[] = {L"AllowUserPaint", L"Font", L"ForeColor", L"Height", L"MaxLine", L"ShowUnderLine", L"Text", L"UnderLineColor", L"Visible"};
	vector<String> propertyNames(arr, arr + _countof(arr));
	return propertyNames;
}

void CTitleBarMe::OnPaint( CPaintMe *paint, CDivMe *div, const RECT& rect )
{

}

void CTitleBarMe::SetProperty( const String& name, const String& value )
{
	if(name == L"allowuserpaint")
	{
		SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
	}
	else if(name == L"font")
	{
		SetFont(CStrMe::ConvertStrToFont(value));
	}
	else if(name == L"forecolor")
	{
		SetForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"height")
	{
		SetHeight(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"maxline")
	{
		SetMaxLine(CStrMe::ConvertStrToInt(value));
	}
	else if(name == L"showunderline")
	{
		SetShowUnderLine(CStrMe::ConvertStrToBool(value));
	}
	else if(name == L"text")
	{
		SetText(value);
	}
	else if(name == L"underlinecolor")
	{
		SetUnderLineColor(CStrMe::ConvertStrToColor(value));
	}
	else if(name == L"visible")
	{
		SetVisible(CStrMe::ConvertStrToBool(value));
	}
}
