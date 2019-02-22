#include "..\\stdafx.h"
#include "..\\include\\Chart\\CScaleGrid.h"

namespace MeLib
{
	CScaleGridMe::CScaleGridMe()
	{
		m_allowUserPaint = false;
		m_distance = 30;
		m_gridColor = COLOR::ARGB(80, 0, 0);
		m_lineStyle = 2;
		m_visible = false;
	}

	CScaleGridMe::~CScaleGridMe()
	{
	}

	bool CScaleGridMe::AllowUserPaint()
	{
		return m_allowUserPaint;
	}

	void CScaleGridMe::SetAllowUserPaint(bool allowUserPaint)
	{
		m_allowUserPaint = allowUserPaint;
	}

	int CScaleGridMe::GetDistance()
	{
		return m_distance;
	}
	void CScaleGridMe::SetDistance(int distance)
	{
		m_distance = distance;
	}

	_int64 CScaleGridMe::GetGridColor()
	{
		return m_gridColor;
	}

	void CScaleGridMe::SetGridColor(_int64 gridColor)
	{
		m_gridColor = gridColor;
	}

	int CScaleGridMe::GetLineStyle()
	{
		return m_lineStyle;
	}

	void CScaleGridMe::SetLineStyle(int lineStyle)
	{
		m_lineStyle = lineStyle;
	}

	bool CScaleGridMe::IsVisible()
	{
		return m_visible;
	}

	void CScaleGridMe::SetVisible(bool visible)
	{
		m_visible = visible;
	}

	void CScaleGridMe::GetProperty(const String& name, String *value, String *type)
	{
		String szName = CStrMe::ToLower(name);
		if (szName == L"allowuserpaint")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowUserPaint());
		}
		else if (szName == L"distance")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetDistance());
		}
		else if (szName == L"gridcolor")
		{
			*type = L"color";
			*value = CStrMe::ConvertColorToStr(GetGridColor());
		}
		else if (szName == L"linestyle")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetLineStyle());
		}
		else if (szName == L"visible")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(IsVisible());
		}
	}

	vector<String> CScaleGridMe::GetPropertyNames()
	{
		 vector<String> propertyNames;
		 propertyNames.push_back(L"AllowUserPaint");
		 propertyNames.push_back(L"Distance");
		 propertyNames.push_back(L"GridColor");
		 propertyNames.push_back(L"LineStyle");
		 propertyNames.push_back(L"Visible");
		return propertyNames;
	}

	void CScaleGridMe::OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect)
	{

	}

	void CScaleGridMe::SetProperty(const String& name, const String& value)
	{
		String szName = CStrMe::ToLower(name);
		if (szName == L"allowuserpaint")
		{
			SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
		}
		else if (szName == L"distance")
		{
			SetDistance(CStrMe::ConvertStrToInt(value));
		}
		else if (szName == L"gridcolor")
		{
			SetGridColor(CStrMe::ConvertStrToColor(value));
		}
		else if (szName == L"linestyle")
		{
			SetLineStyle(CStrMe::ConvertStrToInt(value));
		}
		else if (szName == L"visible")
		{
			SetVisible(CStrMe::ConvertStrToBool(value));
		}
	}
}