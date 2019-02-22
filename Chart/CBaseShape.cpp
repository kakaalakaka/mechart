#include "..\\stdafx.h"
#include "..\\include\\Chart\\CBaseShape.h"

namespace MeLib
{
	CBaseShapeMe::CBaseShapeMe()
	{
		m_allowUserPaint = false;
		m_attachVScale = AttachVScale_Left;
		m_selected = false;
		m_visible = true;
		m_zOrder = 0;
	}

	CBaseShapeMe::~CBaseShapeMe()
	{		
	}

	bool CBaseShapeMe::AllowUserPaint()
	{
		return m_allowUserPaint;
	}

	void CBaseShapeMe::SetAllowUserPaint(bool allowUserPaint)
	{
		m_allowUserPaint = allowUserPaint;
	}
	
	AttachVScale CBaseShapeMe::GetAttachVScale()
	{
		return m_attachVScale;
	}
	
	void CBaseShapeMe::SetAttachVScale(AttachVScale attachVScale)
	{
		m_attachVScale = attachVScale;
	}
	
	bool CBaseShapeMe::IsSelected()
	{
		return m_selected;
	}
	
	void CBaseShapeMe::SetSelected(bool selected)
	{
		m_selected = selected;
	}
	
	bool CBaseShapeMe::IsVisible()
	{
		return m_visible;
	}
	
	void CBaseShapeMe::SetVisible(bool visible)
	{
		m_visible = visible;
	}
	
	int CBaseShapeMe::GetZOrder()
	{
		return m_zOrder;
	}
	
	void CBaseShapeMe::SetZOrder(int zOrder)
	{
		m_zOrder = zOrder;
	}
	
	int CBaseShapeMe::GetBaseField()
	{
		return CTableMe::NULLFIELD();
	}
	
	String CBaseShapeMe::GetFieldText(int fieldName)
	{
		return L"";
	}
	
	int* CBaseShapeMe::GetFields(int *length)
	{
		return NULL;
	}
	
	void CBaseShapeMe::GetProperty(const String& name, String *value, String *type)
	{
		if(name == L"allowuserpaint") 
		{
            *type = L"bool";
            *value = CStrMe::ConvertBoolToStr(AllowUserPaint());
        } 
		else if(name == L"attachvscale") 
		{
            *type = L"enum:AttachVScale";
            if(GetAttachVScale() == AttachVScale_Left) 
			{
                *value = L"Left";
            } 
			else 
			{
                *value = L"Right";
            }
        } 
		else if(name == L"selected") 
		{
            *type = L"bool";
            *value = CStrMe::ConvertBoolToStr(IsSelected());
        } 
		else if(name == L"visible") 
		{
            *type = L"bool";
            *value = CStrMe::ConvertBoolToStr(IsVisible());
        } 
		else if(name == L"zorder") 
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetZOrder());
        } 
		else 
		{
            *type = L"undefined";
            *value = L"";
        }		
	}
	
	vector<String> CBaseShapeMe::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"AllowUserPaint");
		propertyNames.push_back(L"AttachVScale");
		propertyNames.push_back(L"Selected");
		propertyNames.push_back(L"Visible");
		propertyNames.push_back(L"ZOrder");
        return propertyNames;
	}
	
	_int64 CBaseShapeMe::GetSelectedColor()
	{
		return 0;
	}
	
	void CBaseShapeMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
	{
		
	}
	
	void CBaseShapeMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		if(szName == L"allowuserpaint") 
		{
			SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
		}
		else if(szName == L"attachvscale") 
		{
			String szValue = CStrMe::ToLower(value);
            if(szValue == L"left")
			{
                SetAttachVScale(AttachVScale_Left);
            } 
			else 
			{
                SetAttachVScale(AttachVScale_Right);
            }
		}
		else if(szName == L"selected") 
		{
			SetSelected(CStrMe::ConvertStrToBool(value));
		}
		else if(szName == L"visible") 
		{
			SetVisible(CStrMe::ConvertStrToBool(value));
		}
		else if(szName == L"zorder") 
		{
			SetZOrder(CStrMe::ConvertStrToInt(value));
		}
	}
		
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CCandleShapeMe::CCandleShapeMe()
	{
		m_closeField = CTableMe::NULLFIELD();
		m_closeFieldText = L"";
		m_colorField = CTableMe::NULLFIELD();
		m_downColor = COLOR::ARGB(84, 255, 255);
        m_highField = CTableMe::NULLFIELD();
		m_highFieldText = L"";
        m_lowField = CTableMe::NULLFIELD();
		m_lowFieldText = L"";
        m_openField = CTableMe::NULLFIELD();
		m_openFieldText = L"";
        m_showMaxMin = true;
		m_style = CandleStyle_Rect;
		m_styleField = CTableMe::NULLFIELD();
        m_tagColor = COLOR::ARGB(255, 255, 255);
        m_upColor = COLOR::ARGB(255, 82, 82);
        m_zOrder = 1;
	}

	int CCandleShapeMe::GetCloseField()
	{
		return m_closeField;
	}
		
	void CCandleShapeMe::SetCloseField(int closeField)
	{
		m_closeField = closeField;
	}
	
	String CCandleShapeMe::GetCloseFieldText()
	{
		return m_closeFieldText;
	}
	
	void CCandleShapeMe::SetCloseFieldText(const String& closeFieldText)
	{
		m_closeFieldText = closeFieldText;
	}
	
	int CCandleShapeMe::GetColorField()
	{
		return m_colorField;
	}
	
	void CCandleShapeMe::SetColorField(int colorField)
	{
		m_colorField = colorField;
	}
	
	_int64 CCandleShapeMe::GetDownColor()
	{
		return m_downColor;
	}
	
	void CCandleShapeMe::SetDownColor(_int64 downColor)
	{
		m_downColor = downColor;
	}
	
	int CCandleShapeMe::GetHighField()
	{
		return m_highField;
	}
		
	void CCandleShapeMe::SetHighField(int highField)
	{
		m_highField = highField;
	}
	
	String CCandleShapeMe::GetHighFieldText()
	{
		return m_highFieldText;
	}
	
	void CCandleShapeMe::SetHighFieldText(const String& highFieldText)
	{
		m_highFieldText = highFieldText;
	}
	
	int CCandleShapeMe::GetLowField()
	{
		return m_lowField;
	}
	
	void CCandleShapeMe::SetLowField(int lowField)
	{
		m_lowField = lowField;
	}
	
	String CCandleShapeMe::GetLowFieldText()
	{
		return m_lowFieldText;
	}
	
	void CCandleShapeMe::SetLowFieldText(const String& lowFieldText)
	{
		m_lowFieldText = lowFieldText;
	}
	
	int CCandleShapeMe::GetOpenField()
	{
		return m_openField;
	}
	
	void CCandleShapeMe::SetOpenField(int openField)
	{
		m_openField = openField;
	}
	
	String CCandleShapeMe::GetOpenFieldText()
	{
		return m_openFieldText;
	}
	
	void CCandleShapeMe::SetOpenFieldText(const String& openFieldText)
	{
		m_openFieldText = openFieldText;
	}
	
	bool CCandleShapeMe::GetShowMaxMin()
	{
		return m_showMaxMin;
	}
	
	void CCandleShapeMe::SetShowMaxMin(bool showMaxMin)
	{
		m_showMaxMin = showMaxMin;
	}
	
	CandleStyle CCandleShapeMe::GetStyle()
	{
		return m_style;
	}
	
	void CCandleShapeMe::SetStyle(CandleStyle style)
	{
		m_style = style;
	}
	
	int CCandleShapeMe::GetStyleField()
	{
		return m_styleField;
	}
	
	void CCandleShapeMe::SetStyleField(int styleField)
	{
		m_styleField = styleField;
	}
		
	_int64 CCandleShapeMe::GetTagColor()
	{
		return m_tagColor;
	}
	
	void CCandleShapeMe::SetTagColor(_int64 tagColor)
	{
		m_tagColor = tagColor;
	}
	
	_int64 CCandleShapeMe::GetUpColor()
	{
		return m_upColor;
	}
	
	void CCandleShapeMe::SetUpColor(_int64 upColor)
	{
		m_upColor = upColor;
	}
	
	int CCandleShapeMe::GetBaseField()
	{
		return m_closeField;
	}
	
	String CCandleShapeMe::GetFieldText(int fieldName)
	{
		return fieldName == m_closeField ? GetCloseFieldText() :
			(fieldName == m_highField ? GetHighFieldText() : (
			fieldName == m_lowField ? GetLowFieldText() : (
			fieldName == m_openField ? GetOpenFieldText() : L"")));
	}
	
	int* CCandleShapeMe::GetFields(int *length)
	{
		*length = 4;
		int *fields = new int[4];
		fields[0] = m_closeField;
		fields[1] = m_openField;
		fields[2] = m_highField;
		fields[3] = m_lowField;
		return fields;
	}
	
	void CCandleShapeMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);
		
		if(szName == L"closefield")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetCloseField());
        } 
		else if(szName == L"colorfield")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetColorField());
        } 
		else if(szName == L"closefieldtext")
		{
            *type = L"string";
            *value = GetCloseFieldText();
        } 
		else if(szName == L"downcolor")
		{
            *type = L"color";
            *value = CStrMe::ConvertColorToStr(GetDownColor());
        } 
		else if(szName == L"highfield") 
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetHighField());
        } 
		else if(szName == L"highfieldtext") 
		{
            *type = L"string";
            *value = GetHighFieldText();
        } 
		else if(szName == L"lowfield") 
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetLowField());
        } 
		else if(szName == L"lowfieldtext") 
		{
            *type = L"string";
            *value = GetLowFieldText();
        } 
		else if(szName == L"openfield") 
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetOpenField());
        } 
		else if(szName == L"openfieldtext") 
		{
            *type = L"string";
            *value = GetOpenFieldText();
        } 
		else if(szName == L"showmaxmin") 
		{
            *type = L"bool";
            *value = CStrMe::ConvertBoolToStr(GetShowMaxMin());
        } 
		else if(szName == L"style") 
		{
            *type = L"enum:CandleStyle";
            CandleStyle style = GetStyle();
			if(style == CandleStyle_American) 
			{
                *value = L"American";
            } 
			else if(style == CandleStyle_CloseLine) 
			{
                *value = L"CloseLine";
            } 
			else if(style == CandleStyle_Tower) 
			{
                *value = L"Tower";
            } 
			else 
			{
                *value = L"Rect";
            }
        } 
		else if(szName == L"stylefield") 
		{
			*type = L"int";
            *value = CStrMe::ConvertIntToStr(GetStyleField());
        } 
		else if(szName == L"tagcolor") 
		{
            *type = L"double";
            *value = CStrMe::ConvertDoubleToStr((double)GetTagColor());
        } 
		else if(szName == L"upcolor") 
		{
            *type = L"color";
            *value = CStrMe::ConvertDoubleToStr((double)GetUpColor());
        }
		else 
		{
            CBaseShapeMe::GetProperty(name, value, type);
        }
	}
	
	vector<String> CCandleShapeMe::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"CloseField");
		propertyNames.push_back(L"ColorField");
		propertyNames.push_back(L"CloseFieldText");
		propertyNames.push_back(L"DownColor");
		propertyNames.push_back(L"HighFieldText");
		propertyNames.push_back(L"LowField");
		propertyNames.push_back(L"LowFieldText");
		propertyNames.push_back(L"OpenField");
		propertyNames.push_back(L"OpenFieldText");
		propertyNames.push_back(L"ShowMaxMin");
		propertyNames.push_back(L"Style");
		propertyNames.push_back(L"StyleField");
		propertyNames.push_back(L"TagColor");
		propertyNames.push_back(L"UpColor");
        return propertyNames;
	}
	
	_int64 CCandleShapeMe::GetSelectedColor()
	{
		return m_downColor;
	}
	
	void CCandleShapeMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		if(szName == L"closefield")
		{
            SetCloseField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"colorfield")
		{
            SetColorField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"closefieldtext")
		{
			SetCloseFieldText(value);
        } 
		else if(szName == L"downcolor")
		{
            SetDownColor(CStrMe::ConvertStrToColor(value));
        } 
		else if(szName == L"highfield") 
		{
            SetHighField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"highfieldtext") 
		{
            SetHighFieldText(value);
        } 
		else if(szName == L"lowfield") 
		{
            SetLowField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"lowfieldtext") 
		{
            SetLowFieldText(value);
        } 
		else if(szName == L"openfield") 
		{
			SetOpenField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"openfieldtext") 
		{
            SetOpenField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"showmaxmin") 
		{
            SetShowMaxMin(CStrMe::ConvertStrToBool(value));
        } 
		else if(szName == L"style") 
		{
			String szValue = CStrMe::ToLower(value);
            if(szValue == L"american")
			{
				SetStyle(CandleStyle_American);
            } 
			else if(szValue == L"closeline")
			{
				SetStyle(CandleStyle_CloseLine);
            } 
			else if(szValue == L"tower")
			{
				SetStyle(CandleStyle_Tower);
            } 
			else 
			{
				SetStyle(CandleStyle_Rect);
            }      
        } 
		else if(szName == L"stylefield") 
		{
            SetStyleField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"tagcolor") 
		{
            SetTagColor(CStrMe::ConvertStrToColor(value));
        } 
		else if(szName == L"upcolor") 
		{
            SetUpColor(CStrMe::ConvertStrToColor(value));
        }
		else 
		{
            CBaseShapeMe::SetProperty(name, value);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CBarShapeMe::CBarShapeMe()
	{
		m_colorField = CTableMe::NULLFIELD();
        m_downColor = COLOR::ARGB(84, 255, 255);
        m_fieldName = CTableMe::NULLFIELD();
        m_fieldName2 = CTableMe::NULLFIELD();
        m_fieldText = L"";
        m_fieldText2 = L"";
        m_lineWidth = 1.0;
		m_style = BarStyle_Rect;
        m_styleField = CTableMe::NULLFIELD();
        m_upColor = COLOR::ARGB(255, 82, 82);
        SetZOrder(0);
	}
	
	int CBarShapeMe::GetColorField()
	{
		return m_colorField;
	}
	
	void CBarShapeMe::SetColorField(int colorField)
	{
		m_colorField = colorField;
	}
	
	_int64 CBarShapeMe::GetDownColor()
	{
		return m_downColor;
	}
	
	void CBarShapeMe::SetDownColor(_int64 downColor)
	{
		m_downColor = downColor;
	}
	
	int CBarShapeMe::GetFieldName()
	{
		return m_fieldName;
	}
	
	void CBarShapeMe::SetFieldName(int fieldName)
	{
		m_fieldName = fieldName;
	}
	
	int CBarShapeMe::GetFieldName2()
	{
		return m_fieldName2;
	}
	
	void CBarShapeMe::SetFieldName2(int fieldName2)
	{
		m_fieldName2 = fieldName2;
	}
	
	String CBarShapeMe::GetFieldText()
	{
		return m_fieldText;
	}
	
	void CBarShapeMe::SetFieldText(const String& fieldText)
	{
		m_fieldText = fieldText;
	}
	
	String CBarShapeMe::GetFieldText2()
	{
		return m_fieldText2;
	}
	
	void CBarShapeMe::SetFieldText2(const String& fieldText2)
	{
		m_fieldText2 = fieldText2;
	}
	
	float CBarShapeMe::GetLineWidth()
	{
		return m_lineWidth;
	}
	
	void CBarShapeMe::SetLineWidth(float lineWidth)
	{
		m_lineWidth = lineWidth;
	}
	
	BarStyle CBarShapeMe::GetStyle()
	{
		return m_style;
	}
	
	void CBarShapeMe::SetStyle(BarStyle style)
	{
		m_style = style;
	}
	
	int CBarShapeMe::GetStyleField()
	{
		return m_styleField;
	}
	
	void CBarShapeMe::SetStyleField(int styleField)
	{
		m_styleField = styleField;
	}
	
	_int64 CBarShapeMe::GetUpColor()
	{
		return m_upColor;
	}
	
	void CBarShapeMe::SetUpColor(_int64 upColor)
	{
		m_upColor = upColor;
	}
	
	int CBarShapeMe::GetBaseField()
	{
		return m_fieldName;	
	}
	
	String CBarShapeMe::GetFieldText(int fieldName)
	{
		return fieldName == m_fieldName ? GetFieldText() : (fieldName == m_fieldName2 ? GetFieldText2() : L"");
	}
	
	int* CBarShapeMe::GetFields(int *length)
	{
		if(m_fieldName2 == CTableMe::NULLFIELD())
		{
			*length = 1;
			int *fields = new int[1];
			fields[0] = m_fieldName;
			return fields;
		}
		else
		{
			*length = 2;
			int *fields = new int[2];
			fields[0] = m_fieldName;
			fields[1] = m_fieldName2;
			return fields;
		}
	}
	
	void CBarShapeMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);
		
		if(szName == L"colorfield")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetColorField());
        } 
		else if(szName == L"downcolor")
		{
            *type = L"color";
            *value = CStrMe::ConvertColorToStr(GetDownColor());
        } 
		else if(szName == L"fieldname")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetFieldName());
        } 
		else if(szName == L"fieldname2")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetFieldName2());
        } 
		else if(szName == L"fieldtext")
		{
            *type = L"string";
            *value = GetFieldText();
        } 
		else if(szName == L"fieldtext2")
		{
            *type = L"string";
            *value = GetFieldText2();
        } 
		else if(szName == L"linewidth")
			{
            *type = L"float";
            *value = CStrMe::ConvertFloatToStr(GetLineWidth());
        } 
		else if(szName == L"style")
		{
            *type = L"enum:BarStyle";
            BarStyle style = GetStyle();
			if(style == BarStyle_Line) 
			{
                *value = L"Line";
            } else {
                *value = L"Rect";
            }
        } 
		else if(szName == L"stylefield")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetStyleField());
        } 
		else if(szName == L"upcolor")
		{
            *type = L"double";
            *value = CStrMe::ConvertColorToStr(GetUpColor());
        } 
		else 
		{
            CBaseShapeMe::GetProperty(name, value, type);
        }
	}
	
	vector<String> CBarShapeMe::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"ColorField");
		propertyNames.push_back(L"DownColor");
		propertyNames.push_back(L"FieldName");
		propertyNames.push_back(L"FieldName2");
		propertyNames.push_back(L"FieldText");
		propertyNames.push_back(L"FieldText2");
		propertyNames.push_back(L"LineWidth");
		propertyNames.push_back(L"Style");
		propertyNames.push_back(L"StyleField");
		propertyNames.push_back(L"UpColor");
        return propertyNames;
	}
	
	_int64 CBarShapeMe::GetSelectedColor()
	{
		return m_downColor;
	}
	
	void CBarShapeMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		
		if(szName == L"colorfield")
		{
            SetColorField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"downcolor")
		{
            SetDownColor(CStrMe::ConvertStrToColor(value));
        } 
		else if(szName == L"fieldname")
		{
            SetFieldName(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"fieldname2")
		{
            SetFieldName2(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"fieldtext")
		{
            SetFieldText(value);
        } 
		else if(szName == L"fieldtext2")
		{
            SetFieldText2(value);
        } 
		else if(szName == L"linewidth")
		{
            SetLineWidth(CStrMe::ConvertStrToFloat(value));
        } 
		else if(szName == L"style")
		{
			String szValue = CStrMe::ToLower(value);
            if(szValue == L"line") 
			{
				SetStyle(BarStyle_Line);
            } 
			else 
			{
				SetStyle(BarStyle_Rect);
            }
        } 
		else if(szName == L"stylefield")
		{
            SetStyleField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"upcolor")
		{
            SetUpColor(CStrMe::ConvertStrToColor(value));
        } 
		else 
		{
            CBaseShapeMe::SetProperty(name, value);
        }	
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	CPolylineShapeMe::CPolylineShapeMe()
	{
		m_color = COLOR::ARGB(255, 255, 255);
		m_colorField = CTableMe::NULLFIELD();
        m_fieldName = CTableMe::NULLFIELD();
        m_fieldText = L"";
        m_fillColor = COLOR_EMPTY;
		m_style = PolylineStyle_SolidLine;
        m_width = 1.0;
        SetZOrder(2);
	}
	
	_int64 CPolylineShapeMe::GetColor()
	{
		return m_color;
	}
	
	void CPolylineShapeMe::SetColor(_int64 color)
	{
		m_color = color;
	}

	int CPolylineShapeMe::GetColorField()
	{
		return m_colorField;
	}

	void CPolylineShapeMe::SetColorField(int colorField)
	{
		m_colorField = colorField;
	}
	
	int CPolylineShapeMe::GetFieldName()
	{
		return m_fieldName;
	}
	
	void CPolylineShapeMe::SetFieldName(int fieldName)
	{
		m_fieldName = fieldName;
	}
	
	String CPolylineShapeMe::GetFieldText()
	{
		return m_fieldText;
	}
	
	void CPolylineShapeMe::SetFieldText(const String& fieldText)
	{
		m_fieldText = fieldText;
	}
	
	_int64 CPolylineShapeMe::GetFillColor()
	{
		return m_fillColor;
	}
	
	void CPolylineShapeMe::SetFillColor(_int64 fillColor)
	{
		m_fillColor = fillColor;
	}
	
	PolylineStyle CPolylineShapeMe::GetStyle()
	{
		return m_style;
	}
	
	void CPolylineShapeMe::SetStyle(PolylineStyle style)
	{
		m_style = style;
	}
	
	float CPolylineShapeMe::GetWidth()
	{
		return m_width;
	}

	void CPolylineShapeMe::SetWidth(float width)
	{
		m_width = width;
	}

	int CPolylineShapeMe::GetBaseField()
	{
		return m_fieldName;
	}
	
	String CPolylineShapeMe::GetFieldText(int fieldName)
	{
        return fieldName == m_fieldName ? GetFieldText() : L"";
	}
	
	int* CPolylineShapeMe::GetFields(int *length)
	{
		*length = 1;
		int *fields = new int[1];
		fields[0] = m_fieldName;
		return fields;
	}
	
	void CPolylineShapeMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);		
		if(szName == L"color")
		{
            *type = L"color";
            *value = CStrMe::ConvertColorToStr(GetColor());
        } 
		else if(szName == L"colorfield")
		{
           * type = L"int";
            *value = CStrMe::ConvertIntToStr(GetColorField());
        } 
		else if(szName == L"fieldname")
		{
            *type = L"int";
            *value = CStrMe::ConvertIntToStr(GetFieldName());
        } 
		else if(szName == L"fieldtext")
		{
            *type = L"string";
            *value = GetFieldText();
        }
		else if(szName == L"fillcolor")
		{
            *type = L"color";
            *value = CStrMe::ConvertColorToStr(GetFillColor());
        }
		else if(szName == L"style") 
		{
            *type = L"enum:PolylineStyle";
            PolylineStyle style = GetStyle();
			if(style == PolylineStyle_Cycle) 
			{
                *value = L"Cycle";
            } 
			else if(style == PolylineStyle_DashLine) 
			{
                *value = L"DashLine";
            } 
			else if(style == PolylineStyle_DotLine) 
			{
                *value = L"DotLine";
            } 
			else 
			{
                *value = L"SolidLine";
            }
        } 
		else if(szName == L"width")
		{
            *type = L"float";
            *value = CStrMe::ConvertFloatToStr(GetWidth());
        }
		else
		{
            CBaseShapeMe::GetProperty(name, value, type);
        }
	}

	vector<String> CPolylineShapeMe::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"Color");
		propertyNames.push_back(L"ColorField");
		propertyNames.push_back(L"FieldName");
		propertyNames.push_back(L"FieldText");
		propertyNames.push_back(L"FillColor");
		propertyNames.push_back(L"Style");
		propertyNames.push_back(L"Width");
        return propertyNames;
	}

	_int64 CPolylineShapeMe::GetSelectedColor()
	{
		return m_color;
	}

	void CPolylineShapeMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);		
		if(szName == L"color")
		{
            SetColor(CStrMe::ConvertStrToColor(value));
        } 
		else if(szName == L"colorfield")
		{
            SetColorField(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"fieldname")
		{
            SetFieldName(CStrMe::ConvertStrToInt(value));
        } 
		else if(szName == L"fieldtext")
		{
			SetFieldText(value);
        }
		else if(szName == L"fillcolor")
		{
            SetFillColor(CStrMe::ConvertStrToColor(value));
        }
		else if(szName == L"style") 
		{
            String szValue = CStrMe::ToLower(value);
            if(szValue == L"cyle") 
			{
				SetStyle(PolylineStyle_Cycle);
            } 
			else if(szValue == L"dashline")
			{
				SetStyle(PolylineStyle_DashLine);
            } 
			else if(szValue == L"dotline")
			{
				SetStyle(PolylineStyle_DotLine);
            } 
			else 
			{
				SetStyle(PolylineStyle_SolidLine);
            }
        } 
		else if(szName == L"width")
		{
            SetWidth(CStrMe::ConvertStrToFloat(value));
        }
		else
		{
            CBaseShapeMe::SetProperty(name, value);
        }
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CTextShapeMe::CTextShapeMe()
	{
		m_colorField = CTableMe::NULLFIELD();
		m_fieldName = CTableMe::NULLFIELD();
		m_font = new FONT();
		m_foreColor = COLOR::ARGB(255, 255, 255);
		m_styleField = CTableMe::NULLFIELD();
		SetZOrder(4);
	}
	
	CTextShapeMe::~CTextShapeMe()
	{
		if(m_font)
		{
			delete m_font;
		}
		m_font = 0;
	}
	
	int CTextShapeMe::GetColorField()
	{
		return m_colorField;
	}
	
	void CTextShapeMe::SetColorField(int colorField)
	{
		m_colorField = colorField;
	}
	
	int CTextShapeMe::GetFieldName()
	{
		return m_fieldName;
	}
	
	void CTextShapeMe::SetFieldName(int fieldName)
	{
		m_fieldName = fieldName;
	}
	
	FONT* CTextShapeMe::GetFont()
	{
		return m_font;
	}
	
	void CTextShapeMe::SetFont(FONT *font)
	{
		m_font->Copy(font);
	}
	
	_int64 CTextShapeMe::GetForeColor()
	{
		return m_foreColor;
	}
	
	void CTextShapeMe::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}
	
	int CTextShapeMe::GetStyleField()
	{
		return m_styleField;
	}

	void CTextShapeMe::SetStyleField(int styleField)
	{
		m_styleField = styleField;
	}
	
	String CTextShapeMe::GetText()
	{
		return m_text;
	}
	
	void CTextShapeMe::SetText(const String& text)
	{
		m_text = text;
	}
	
	void CTextShapeMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);
		
		if(szName == L"colorfield")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetColorField());
		} 
		else if(szName == L"fieldname")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetFieldName());
		} 
		else if(szName == L"font")
		{
			*type = L"font";
			*value = CStrMe::ConvertFontToStr(GetFont());
		} 
		else if(szName == L"forecolor")
		{
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetForeColor());
		} 
		else if(szName == L"stylefield")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetStyleField());
		} 
		else if(szName == L"text")
		{
			*type = L"string";
			*value = GetText();
		} 
		else 
		{
			CBaseShapeMe::GetProperty(name, value, type);
		}
	}
	
	vector<String> CTextShapeMe::GetPropertyNames()
	{
		 vector<String> propertyNames;
		 propertyNames.push_back(L"ColorField");
		 propertyNames.push_back(L"FieldName");
		 propertyNames.push_back(L"Font");
		 propertyNames.push_back(L"ForeColor");
		 propertyNames.push_back(L"StyleField");
		 propertyNames.push_back(L"Text");
		return propertyNames;
	}
	
	void CTextShapeMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		
		if(szName == L"colorfield")
		{
			SetColorField(CStrMe::ConvertStrToInt(value));
		} 
		else if(szName == L"fieldname")
		{
			SetFieldName(CStrMe::ConvertStrToInt(value));
		}
		else if(szName == L"font")
		{
			SetFont(CStrMe::ConvertStrToFont(value));
		}
		else if(szName == L"forecolor")
		{
			SetForeColor(CStrMe::ConvertStrToColor(value));
		}
		else if(szName == L"stylefield")
		{
			SetStyleField(CStrMe::ConvertStrToInt(value));
		}
		else if(szName == L"text")
		{
			SetText(value);
		} 
		else 
		{
			CBaseShapeMe::SetProperty(name, value);
		}
	}
}