#include "..\\stdafx.h"
#include "..\\include\\Layout\\CTableLayoutDiv.h"
using namespace MeLib;

CColumnStyleMe::CColumnStyleMe( SizeTypeMe sizeType, float width )
{
	m_sizeType = sizeType;
	m_width = width;
}

CColumnStyleMe::~CColumnStyleMe()
{

}

SizeTypeMe CColumnStyleMe::GetSizeType()
{
	return m_sizeType;
}

void CColumnStyleMe::SetSizeTypeMe( SizeTypeMe sizeType )
{
	m_sizeType = sizeType;
}

float CColumnStyleMe::GetWidth()
{
	return m_width;
}

void CColumnStyleMe::SetWidth( float width )
{
	m_width = width;
}

void CColumnStyleMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"sizetype")
	{
		*type = L"enum:SizeType";
		if (m_sizeType == SizeTypeMe_AbsoluteSize)
		{
			*value = L"absolutesize";
		}
		else if (m_sizeType == SizeTypeMe_AutoFill)
		{
			*value = L"autofill";
		}
		else if (m_sizeType == SizeTypeMe_PercentSize)
		{
			*value = L"percentsize";
		}
	}
	else if (name == L"width")
	{
		*type = L"float";
		*value = CStrMe::ConvertFloatToStr(GetWidth());
	}
}

vector<String> CColumnStyleMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"SizeType");
	propertyNames.push_back(L"Width");
	return propertyNames;
}

void CColumnStyleMe::SetProperty( const String& name, const String& value )
{
	if (name == L"sizetype")
	{
		String temp = CStrMe::ToLower(value);
		if (temp == L"absolutesize")
		{
			m_sizeType = SizeTypeMe_AbsoluteSize;
		}
		else if (temp == L"autofill")
		{
			m_sizeType = SizeTypeMe_AutoFill;
		}
		else if (temp == L"percentsize")
		{
			m_sizeType = SizeTypeMe_PercentSize;
		}
	}
	else if (name == L"width")
	{
		SetWidth(CStrMe::ConvertStrToFloat(value));
	}
}

CRowStyleMe::CRowStyleMe( SizeTypeMe sizeType, float height )
{
	m_sizeType = sizeType;
	m_height = height;
}

CRowStyleMe::~CRowStyleMe()
{

}

float CRowStyleMe::GetHeight()
{
	return m_height;
}

void CRowStyleMe::SetHeight( float height )
{
	m_height = height;
}

SizeTypeMe CRowStyleMe::GetSizeType()
{
	return m_sizeType;
}

void CRowStyleMe::SetSizeTypeMe( SizeTypeMe sizeType )
{
	m_sizeType = sizeType;
}

void CRowStyleMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"sizetype")
	{
		*type = L"enum:SizeType";
		if (m_sizeType == SizeTypeMe_AbsoluteSize)
		{
			*value = L"absolutesize";
		}
		else if (m_sizeType == SizeTypeMe_AutoFill)
		{
			*value = L"autofill";
		}
		else if (m_sizeType == SizeTypeMe_PercentSize)
		{
			*value = L"percentsize";
		}
	}
	else if (name == L"height")
	{
		*type = L"float";
		*value = CStrMe::ConvertFloatToStr(GetHeight());
	}
}

vector<String> CRowStyleMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"SizeType");
	propertyNames.push_back(L"Height");
	return propertyNames;
}

void CRowStyleMe::SetProperty( const String& name, const String& value )
{
	if (name == L"sizetype")
	{
		String temp = CStrMe::ToLower(value);
		if (value == L"absolutesize")
		{
			m_sizeType = SizeTypeMe_AbsoluteSize;
		}
		else if (value == L"autofill")
		{
			m_sizeType = SizeTypeMe_AutoFill;
		}
		else if (value == L"percentsize")
		{
			m_sizeType = SizeTypeMe_PercentSize;
		}
	}
	else if (name == L"height")
	{
		SetHeight(CStrMe::ConvertStrToFloat(value));
	}
}

CTableLayoutDivMe::CTableLayoutDivMe()
{
	m_columnsCount = 0;
	m_rowsCount = 0;
}

CTableLayoutDivMe::~CTableLayoutDivMe()
{
	m_columns.clear();
	m_columnsCount = 0;
	m_rows.clear();
	m_rowsCount = 0;
	m_tableControls.clear();
	m_columnStyles.clear();
	m_rowStyles.clear();
}

int CTableLayoutDivMe::GetColumnsCount()
{
	return m_columnsCount;
}

void CTableLayoutDivMe::SetColumnsCount( int columnsCount )
{
	m_columnsCount = columnsCount;
}

int CTableLayoutDivMe::GetRowsCount()
{
	return m_rowsCount;
}

void CTableLayoutDivMe::SetRowsCount( int rowsCount )
{
	m_rowsCount = rowsCount;
}

void CTableLayoutDivMe::AddControl( CControlMe *control )
{
	int count = (int)GetControls().size();
	CControlMe::AddControl(control);
	int column = count % m_columnsCount;
	int row = count / m_columnsCount;
	m_columns.push_back(column);
	m_rows.push_back(row);
	m_tableControls.push_back(control);
}

void CTableLayoutDivMe::AddControl( CControlMe *control, int column, int row )
{
	CControlMe::AddControl(control);
	m_columns.push_back(column);
	m_rows.push_back(row);
	m_tableControls.push_back(control);
}

String CTableLayoutDivMe::GetControlType()
{
	return L"TableLayoutDiv";
}

void CTableLayoutDivMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"columnscount")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetColumnsCount());
	}
	else if (name == L"rowscount")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetRowsCount());
	}
	else
	{
		CControlMe::GetProperty(name, value, type);
	}
}

vector<String> CTableLayoutDivMe::GetPropertyNames()
{
	vector<String> propertyNames;
	propertyNames.push_back(L"ColumnsCount");
	propertyNames.push_back(L"RowsCount");
	return propertyNames;
}

bool CTableLayoutDivMe::OnResetLayout()
{
	if (GetNative() && m_columnsCount > 0 && m_rowsCount > 0 && !m_columnStyles.empty() && !m_rowStyles.empty())
	{
		int width = GetWidth();
		int height = GetHeight();
		int count = (int)m_tableControls.size();
		int *columnWidths = new int[m_columnsCount];
		int *rowHeights = new int[m_rowsCount];
		int allWidth = 0;
		int allHeight = 0;
		for (int i = 0; i < m_columnsCount; i++)
		{
			CColumnStyleMe columnStyleA = m_columnStyles[i];
			int cWidth = 0;
			SizeTypeMe sizeType = columnStyleA.GetSizeType();
			float sWidth = columnStyleA.GetWidth();
			switch (sizeType)
			{
			case SizeTypeMe_AbsoluteSize:
				cWidth = (int) sWidth;
				break;

			case SizeTypeMe_AutoFill:
				cWidth = width - allWidth;
				break;

			case SizeTypeMe_PercentSize:
				cWidth = (int) (width * sWidth);
				break;
			}
			columnWidths[i] = cWidth;
			allWidth += cWidth;
		}
		for (int j = 0; j < m_rowsCount; j++)
		{
			CRowStyleMe rowStyle = m_rowStyles[j];
			int rHeight = 0;
			SizeTypeMe sizeType = rowStyle.GetSizeType();
			float sHeight = rowStyle.GetHeight();
			switch (sizeType)
			{
			case SizeTypeMe_AbsoluteSize:
				rHeight = (int) sHeight;
				break;

			case SizeTypeMe_AutoFill:
				rHeight = height - allHeight;
				break;

			case SizeTypeMe_PercentSize:
				rHeight = (int) (height * sHeight);
				break;
			}
			rowHeights[j] = rHeight;
			allHeight += rHeight;
		}
		for (int k = 0; k < count; k++)
		{
			CControlMe *control = m_tableControls[k];
			int column = m_columns[k];
			int row = m_rows[k];
			PADDING margin = control->GetMargin();
			int cLeft = 0;
			int cTop = 0;
			for (int m = 0; m < column; m++)
			{
				cLeft += columnWidths[m];
			}
			for (int n = 0; n < row; n++)
			{
				cTop += rowHeights[n];
			}
			int cRight = cLeft + columnWidths[column] - margin.right;
			int cBottom = cTop + rowHeights[row] - margin.bottom;
			cLeft += margin.left;
			cTop += margin.top;
			if (cRight < cLeft)
			{
				cRight = cLeft;
			}
			if (cBottom < cTop)
			{
				cBottom = cTop;
			}
			RECT rc = {cLeft, cTop, cRight, cBottom};
			control->SetBounds(rc);
		}

		delete []columnWidths;
		columnWidths = 0;
		delete []rowHeights;
		rowHeights = 0;
	}
	return true;
}

void CTableLayoutDivMe::RemoveControl( CControlMe *control )
{
	int count = (int)m_tableControls.size();
	int index = -1;
	for (int i = 0; i < count; i++)
	{
		if (control == m_tableControls[i])
		{
			index = i;
			break;
		}
	}
	if (index != -1)
	{
		m_columns.erase(m_columns.begin() + index);
		m_rows.erase(m_rows.begin() + index);
		m_tableControls.erase(m_tableControls.begin() + index);
	}
	CControlMe::RemoveControl(control);
}

void CTableLayoutDivMe::SetProperty( const String& name, const String& value )
{
	if (name == L"columnscount")
	{
		SetColumnsCount(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"rowscount")
	{
		SetRowsCount(CStrMe::ConvertStrToInt(value));
	}
	else
	{
		CControlMe::SetProperty(name, value);
	}
}

void CTableLayoutDivMe::Update()
{
	OnResetLayout();
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->Update();
	}
	UpdateScrollBar();
}