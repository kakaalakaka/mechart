#include "..\\stdafx.h"
#include "..\\include\\Grid\\CGridCell.h"

namespace MeLib
{
	GridCellStyle::GridCellStyle()
	{
		m_align = HorizontalAlignMe_Inherit;
		m_autoEllipsis = false;
		m_backColor = COLOR_EMPTY;
		m_foreColor = COLOR_EMPTY;
		m_font = 0;
	}
	
	GridCellStyle::~GridCellStyle()
	{
		if(m_font)
		{
			delete m_font;
			m_font = 0;
		}
	}
	
	HorizontalAlignMe GridCellStyle::GetAlign()
	{
		return m_align;
	}
	
	void GridCellStyle::SetAlign(HorizontalAlignMe align)
	{
		m_align = align;
	}
	
	bool GridCellStyle::AutoEllipsis()
	{
		return m_autoEllipsis;
	}
	
	void GridCellStyle::SetAutoEllipsis(bool autoEllipsis)
	{
		m_autoEllipsis = autoEllipsis;
	}
	
	_int64 GridCellStyle::GetBackColor()
	{
		return m_backColor;
	}
	
	void GridCellStyle::SetBackColor(_int64 backColor)
	{
		m_backColor = backColor;
	}

	FONT* GridCellStyle::GetFont()
	{
		return m_font;
	}
	
	void GridCellStyle::SetFont(FONT *font)
	{
		if(font)
		{
			if(!m_font)
			{
				m_font = new FONT();
			}
			m_font->Copy(font);
		}
		else
		{
			if(m_font)
			{
				delete m_font;
				m_font = 0;
			}
		}
	}
	
	_int64 GridCellStyle::GetForeColor()
	{
		return m_foreColor;
	}
	
	void GridCellStyle::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}

	void GridCellStyle::Copy(GridCellStyle *style)
	{
		this->m_align = style->m_align;
		this->m_autoEllipsis = style->m_autoEllipsis;
		if(!m_font)
		{
			m_font = new FONT();
		}
		m_font->Copy(style->m_font);
		this->m_foreColor = style->m_foreColor;
		this->m_backColor = style->m_backColor;
	}
	////////////////////////////////////////////////////////////////////////

	CGridCellMe::CGridCellMe()
	{
		m_allowEdit = false;
		m_colSpan = 1;
		m_column = 0;
		m_grid = 0;
		m_row = 0;
		m_rowSpan = 1;
		m_style = 0;
		m_tag = 0;
	}
	
	CGridCellMe::~CGridCellMe()
	{
		m_column = 0;
		m_grid = 0;
		m_row = 0;
		if(m_style)
		{
			delete m_style;
			m_style = 0;
		}
		m_tag = 0;
	}
	
	bool CGridCellMe::AllowEdit()
	{
		return m_allowEdit;
	}
	
	void CGridCellMe::SetAllowEdit(bool allowEdit)
	{
		m_allowEdit = allowEdit;
	}
	
	int CGridCellMe::GetColSpan()
	{
		return m_colSpan;
	}
	
	void CGridCellMe::SetColSpan(int colSpan)
	{
		m_colSpan = colSpan;
	}
	
	CGridColumnMe* CGridCellMe::GetColumn()
	{
		return m_column;
	}
	
	void CGridCellMe::SetColumn(CGridColumnMe *column)
	{
		m_column = column;
	}
	
	CGridMe* CGridCellMe::GetGrid()
	{
		return m_grid;
	}
	
	void CGridCellMe::SetGrid(CGridMe *grid)
	{
		m_grid = grid;
	}

	String CGridCellMe::GetName()
	{
		return m_name;
	}
	
	void CGridCellMe::SetName(const String& name)
	{
		m_name = name;
	}
	
	CGridRowMe* CGridCellMe::GetRow()
	{
		return m_row;
	}

	void CGridCellMe::SetRow(CGridRowMe *row)
	{
		m_row = row;
	}

	int CGridCellMe::GetRowSpan()
	{
		return m_rowSpan;
	}

	void CGridCellMe::SetRowSpan(int rowSpan)
	{
		m_rowSpan = rowSpan;
	}

	GridCellStyle* CGridCellMe::GetStyle()
	{
		return m_style;
	}

	void CGridCellMe::SetStyle(GridCellStyle *style)
	{		
		if(style)
		{
			if(!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->Copy(style);
		}
		else if(m_style)
		{
			delete m_style;
			m_style = 0;
		}
	}

	void* CGridCellMe::GetTag()
	{
		return m_tag;
	}
	
	void CGridCellMe::SetTag(void *tag)
	{
		m_tag = tag;
	}

	String CGridCellMe::GetText()
	{
		return GetString();
	}
	
	void CGridCellMe::SetText(const String& text)
	{
		SetString(text);
	}

	int CGridCellMe::CompareTo(CGridCellMe *cell)
	{
		return 0;
	}
	
	bool CGridCellMe::GetBool()
	{
		return false;
	}
	
	double CGridCellMe::GetDouble()
	{
		return 0;
	}
	
	float CGridCellMe::GetFloat()
	{
		return 0;
	}
	
	int CGridCellMe::GetInt()
	{
		return 0;
	}
	
	_int64 CGridCellMe::GetLong()
	{
		return 0;
	}
	
	String CGridCellMe::GetPaintText()
	{
		return GetText();
	}
	
	void CGridCellMe::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"align")
		{
			*type = L"enum:HorizontalAlignMe";
			GridCellStyle* style = GetStyle();
			if (style != NULL)
			{
				*value = CStrMe::ConvertHorizontalAlignToStr(style->GetAlign());
			}
		}
		else if (name == L"allowedit")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowEdit());
		}
		else if (name == L"autoellipsis")
		{
			*type = L"bool";
			GridCellStyle* style2 = GetStyle();
			if (style2 != NULL)
			{
				*value = CStrMe::ConvertBoolToStr(style2->AutoEllipsis());
			}
		}
		else if (name == L"backcolor")
		{
			*type = L"color";
			GridCellStyle* style3 = GetStyle();
			if (style3 != NULL)
			{
				*value = CStrMe::ConvertColorToStr(style3->GetBackColor());
			}
		}
		else if (name == L"colspan")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetColSpan());
		}
		else if (name == L"font")
		{
			*type = L"font";
			GridCellStyle* style4 = GetStyle();
			if ((style4 != NULL) && (style4->GetFont() != NULL))
			{
				*value = CStrMe::ConvertFontToStr(style4->GetFont());
			}
		}
		else if (name == L"forecolor")
		{
			*type = L"color";
			GridCellStyle* style5 = GetStyle();
			if (style5 != NULL)
			{
				*value = CStrMe::ConvertColorToStr(style5->GetForeColor());
			}
		}
		else if (name == L"name")
		{
			*type = L"String";
			*value = GetName();
		}
		else if (name == L"rowspan")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetRowSpan());
		}
		else if (name == L"text")
		{
			*type = L"String";
			*value = GetText();
		}
		else
		{
			*type = L"undefined";
			*value = L"";
		}
	}
	
	vector<String> CGridCellMe::GetPropertyNames()
	{
		vector<String> list;
		list.push_back(L"Align");
		list.push_back(L"AllowEdit");
		list.push_back(L"AutoEllipsis");
		list.push_back(L"BackColor");
		list.push_back(L"ColSpan");
		list.push_back(L"Font");
		list.push_back(L"ForeColor");
		list.push_back(L"Name");
		list.push_back(L"RowSpan");
		list.push_back(L"Text");
		return list;
	}
	
	String CGridCellMe::GetString()
	{
		return L"";
	}
	
	void CGridCellMe::OnAdd()
	{
		
	}
	
	void CGridCellMe::OnPaint(CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate)
	{
		int clipW = clipRect.right - clipRect.left;
		int clipH = clipRect.bottom - clipRect.top;
		if (clipW > 0 && clipH > 0 && m_grid && m_row && m_column)
		{
			String paintText = GetPaintText();
			bool selected = false;
			if (m_grid->GetSelectionMode() == GridSelectionMode_SelectCell)
			{
				vector<CGridCellMe*> selectedCells = m_grid->GetSelectedCells();
				int selectedCellSize = (int)selectedCells.size();
				for (int i = 0; i < selectedCellSize; i++)
				{
					if (selectedCells[i] == this)
					{
						selected = true;
						break;
					}
				}
			}
			else if (m_grid->GetSelectionMode() == GridSelectionMode_SelectFullColumn)
			{
				vector<CGridColumnMe*> selectedColumns = m_grid->GetSelectedColumns();
				int selectedColumnsSize = (int)selectedColumns.size();
				for (int j = 0; j < selectedColumnsSize; j++)
				{
					if (selectedColumns[j] == m_column)
					{
						selected = true;
						break;
					}
				}
			}
			else if (m_grid->GetSelectionMode() == GridSelectionMode_SelectFullRow)
			{
				vector<CGridRowMe*> selectedRows = m_grid->GetSelectedRows();
				int selectedRowsSize = (int)selectedRows.size();
				for (int k = 0; k < selectedRowsSize; k++)
				{
					if (selectedRows[k] == m_row)
					{
						selected = true;
						break;
					}
				}
			}
			FONT* font = 0;
			_int64 backColor = COLOR_EMPTY;
			_int64 foreColor = COLOR_EMPTY;
			bool autoEllipsis = m_grid->AutoEllipsis();
			HorizontalAlignMe cellAlign = m_column->GetCellAlign();
			if (m_style)
			{
				if (m_style->AutoEllipsis())
				{
					autoEllipsis = m_style->AutoEllipsis();
				}
				backColor = m_style->GetBackColor();
				if (m_style->GetFont())
				{
					font = m_style->GetFont();
				}
				foreColor = m_style->GetForeColor();
				if (m_style->GetAlign() != HorizontalAlignMe_Inherit)
				{
					cellAlign = m_style->GetAlign();
				}
			}
			CGridRowStyleMe* rowStyle = m_grid->GetRowStyle();
			if (isAlternate)
			{
				CGridRowStyleMe* alternateRowStyle = m_grid->GetAlternateRowStyle();
				if (alternateRowStyle)
				{
					rowStyle = alternateRowStyle;
				}
			}
			if (rowStyle)
			{
				if (backColor == COLOR_EMPTY)
				{
					if (selected)
					{
						backColor = rowStyle->GetSelectedBackColor();
					}
					else if (m_row == m_grid->GetHoveredRow())
					{
						backColor = rowStyle->GetHoveredBackColor();
					}
					else
					{
						backColor = rowStyle->GetBackColor();
					}
				}
				if (!font)
				{
					font = rowStyle->GetFont();
				}
				if (foreColor == COLOR_EMPTY)
				{
					if (selected)
					{
						foreColor = rowStyle->GetSelectedForeColor();
					}
					else if (m_row == m_grid->GetHoveredRow())
					{
						foreColor = rowStyle->GetHoveredForeColor();
					}
					else
					{
						foreColor = rowStyle->GetForeColor();
					}
				}
			}
			paint->FillRect(backColor, rect);
			SIZE tSize = paint->TextSize(paintText.c_str(), font);
			POINT tPoint = {0, 0};
			tPoint.x = rect.left + 1;
			tPoint.y = rect.top + (clipH / 2) - (tSize.cy / 2);
			if( tSize.cx < rect.right - rect.left)
			{
				switch (cellAlign)
				{
					case HorizontalAlignMe_Center:
						tPoint.x = rect.left + (rect.right - rect.left - tSize.cx) / 2;
						break;

					case HorizontalAlignMe_Right:
						tPoint.x = rect.right - tSize.cx - 2;
						break;
				}
			}
			RECT tRect;
			tRect.left = tPoint.x;
			tRect.top = tPoint.y;
			tRect.right = tPoint.x + tSize.cx;
			tRect.bottom = tPoint.y + tSize.cy;
			if (autoEllipsis && (tRect.right < clipRect.right || tRect.bottom < clipRect.bottom))
			{
				if (tRect.right < clipRect.right)
				{
					tRect.right = clipRect.right;
				}
				if (tRect.bottom < clipRect.bottom)
				{
					tRect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(paintText.c_str(), foreColor, font, tRect);
			}
			else
			{
				paint->DrawText(paintText.c_str(), foreColor, font, tRect);
			}
		}
	}

	void CGridCellMe::OnRemove()
	{

	}
    
	void CGridCellMe::SetBool(bool value)
	{
		
	}
    
	void CGridCellMe::SetDouble(double value)
	{
		
	}
    
	void CGridCellMe::SetFloat(float value)
	{
		
	}
    
	void CGridCellMe::SetInt(int value)
	{
		
	}
    
	void CGridCellMe::SetLong(_int64 value)
	{
		
	}
		
	void CGridCellMe::SetProperty(const String& name, const String& value)
	{
		if (name == L"align")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetAlign(CStrMe::ConvertStrToHorizontalAlign(value));
		}
		else if (name == L"allowedit")
		{
			SetAllowEdit(CStrMe::ConvertStrToBool(value));
		}
		else if (name == L"autoellipsis")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetAutoEllipsis(CStrMe::ConvertStrToBool(value));
		}
		else if (name == L"backcolor")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetBackColor(CStrMe::ConvertStrToColor(value));
		}
		else if (name == L"colspan")
		{
			SetColSpan(CStrMe::ConvertStrToInt(value));
		}
		else if (name == L"font")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetFont(CStrMe::ConvertStrToFont(value));
		}
		else if (name == L"forecolor")
		{
			if (!m_style)
			{
				m_style = new GridCellStyle();
			}
			m_style->SetForeColor(CStrMe::ConvertStrToColor(value));
		}
		else if (name == L"name")
		{
			SetName(value);
		}
		else if (name == L"rowspan")
		{
			SetRowSpan(CStrMe::ConvertStrToInt(value));
		}
		else if (name == L"text")
		{
			SetText(value);
		}		
	}
        
	void CGridCellMe::SetString(const String& value)
	{
		
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	void CGridControlCellMe::ControlMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke)
	{
		CGridControlCellMe* gridControlCell = (CGridControlCellMe*)pInvoke;
		gridControlCell->OnControlMouseDown(mp, button, clicks, delta);
	}

	void CGridControlCellMe::ControlMouseMove(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke)
	{
		CGridControlCellMe* gridControlCell = (CGridControlCellMe*)pInvoke;
		gridControlCell->OnControlMouseMove( mp, button, clicks, delta);
	}

	void CGridControlCellMe::ControlMouseUp(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke)
	{
		CGridControlCellMe* gridControlCell = (CGridControlCellMe*)pInvoke;
		gridControlCell->OnControlMouseUp( mp, button, clicks, delta);
	}

	void CGridControlCellMe::ControlMouseWheel(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke)
	{
		CGridControlCellMe* gridControlCell = (CGridControlCellMe*)pInvoke;
		gridControlCell->OnControlMouseWheel( mp, button, clicks, delta);
	}

	CGridControlCellMe::CGridControlCellMe()
	{
		m_control = 0;
        m_mouseDownEvent = &ControlMouseDown;
        m_mouseMoveEvent = &ControlMouseMove;
        m_mouseUpEvent = &ControlMouseUp;
        m_mouseWheelEvent = &ControlMouseWheel;
	}
	
	CGridControlCellMe::~CGridControlCellMe()
	{
		if(m_control)
		{
			delete m_control;
			m_control = 0;
		}
		m_mouseDownEvent = 0;
		m_mouseMoveEvent = 0;
		m_mouseUpEvent = 0;
		m_mouseWheelEvent = 0;
	}
	
	CControlMe* CGridControlCellMe::GetControl()
	{
		return m_control;
	}
	
	void CGridControlCellMe::SetControl(CControlMe *control)
	{
		m_control = control;
	}
	
	String CGridControlCellMe::GetString()
	{
		if (m_control)
		{
			m_control->GetText();
		}
		return L"";
	}
	
	String CGridControlCellMe::GetPaintText()
	{
		return L"";
	}
	
	void CGridControlCellMe::OnAdd()
	{
		 CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			grid->AddControl(m_control);
			m_control->RegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN, this);
			m_control->RegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE, this);
			m_control->RegisterEvent(m_mouseUpEvent, EVENTID::MOUSEUP, this);
			m_control->RegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		}
	}
	
	void CGridControlCellMe::OnControlMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseDown(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void CGridControlCellMe::OnControlMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseMove(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void CGridControlCellMe::OnControlMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseUp(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void CGridControlCellMe::OnControlMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			grid->OnMouseWheel(grid->PointToControl(m_control->PointToNative(mp)), button, clicks, delta);
		}
	}
	
	void CGridControlCellMe::OnPaint(CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate)
	{
		CGridCellMe::OnPaint(paint, rect, clipRect, isAlternate);
        OnPaintControl(paint, rect, clipRect);
	}

	void CGridControlCellMe::OnPaintControl(CPaintMe *paint, const RECT& rect, const RECT& clipRect)
	{
		if (m_control)
		{
			RECT rect2;
			rect2.left = rect.left + 1;
			rect2.top = rect.top + 1;
			rect2.right = rect.right - 1;
			rect2.bottom = rect.bottom - 1;
			m_control->SetBounds(rect2);
			RECT clipR;
			clipR.left = clipRect.left - rect.left;
			clipR.top = clipRect.top - rect.top;
			clipR.right = clipRect.right - rect.left;
			clipR.bottom = clipRect.bottom - rect.top;
			m_control->SetRegion(clipR);
		}
	}
	
	void CGridControlCellMe::OnRemove()
	{
		CGridMe* grid = GetGrid();
		if (m_control && grid)
		{
			m_control->UnRegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN);
			m_control->UnRegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE);
			m_control->UnRegisterEvent(m_mouseUpEvent, EVENTID::MOUSEUP);
			m_control->UnRegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL);
			grid->RemoveControl(m_control);
		}
	}
	
	void CGridControlCellMe::SetString(const String& value)
	{
		if (m_control)
		{
			m_control->SetText(value);
		}
	}
}