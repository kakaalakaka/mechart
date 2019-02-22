#include "..\\stdafx.h"
#include "..\\include\\Chart\\CCrossLine.h"

namespace MeLib
{
	CCrossLineMe::CCrossLineMe()
	{
		m_allowUserPaint = false;
		m_allowDoubleClick = true;
		m_attachVScale = AttachVScale_Left;
		m_lineColor = COLOR::ARGB(100, 100, 100);
	}

	CCrossLineMe::~CCrossLineMe()
	{
	
	}

	bool CCrossLineMe::AllowDoubleClick()
	{
		return m_allowDoubleClick;
	}

	void CCrossLineMe::SetAllowDoubleClick(bool allowDoubleClick)
	{
		m_allowDoubleClick = allowDoubleClick;
	}

	bool CCrossLineMe::AllowUserPaint()
	{
		return m_allowUserPaint;
	}

	void CCrossLineMe::SetAllowUserPaint(bool allowUserPaint)
	{
		m_allowUserPaint = allowUserPaint;
	}

	AttachVScale CCrossLineMe::GetAttachVScale()
	{
		return m_attachVScale;
	}

	void CCrossLineMe::SetAttachVScale(AttachVScale attachVScale)
	{
		m_attachVScale = attachVScale;
	}

	_int64 CCrossLineMe::GetLineColor()
	{
		return m_lineColor;
	}

	void CCrossLineMe::SetLineColor(_int64 lineColor)
	{
		m_lineColor = lineColor;
	}

	void CCrossLineMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);
		if (szName == L"allowdoubleclick")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowDoubleClick());
		}
		else if (szName == L"allowuserpaint")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
		}
		else if (szName == L"attachvscale")
		{
			*type = L"enum:AttachVScale";
			if (GetAttachVScale() == AttachVScale_Left) 
			{
				*value = L"Left";
			} 
			else 
			{
				*value = L"Right";
			}
		}
		else if (szName == L"linecolor")
		{
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetLineColor());
		}
	}

	vector<String> CCrossLineMe::GetPropertyNames()
	{
		vector<String> propertyNames;
		propertyNames.push_back(L"AllowDoubleClick");
		propertyNames.push_back(L"AllowUserPaint");
		propertyNames.push_back(L"AttachVScale");
		propertyNames.push_back(L"LineColor");
		return propertyNames;
	}

	void CCrossLineMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
	{
	}

	void CCrossLineMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		if (szName == L"allowdoubleclick")
		{
			SetAllowDoubleClick(CStrMe::ConvertStrToBool(value));
		}
		else if (szName == L"allowuserpaint")
		{
			SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
		}
		else if (szName == L"attachvscale")
		{
			String szValue = CStrMe::ToLower(value);
			if (szValue == L"left")
			{
				SetAttachVScale(AttachVScale_Left);
			} 
			else 
			{
				SetAttachVScale(AttachVScale_Right);
			}
		}
		else if (szName == L"linecolor")
		{
			SetLineColor(CStrMe::ConvertStrToColor(value));
		}
	}
}