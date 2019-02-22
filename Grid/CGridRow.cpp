#include "..\\stdafx.h"
#include "..\\include\\Grid\\CGridRow.h"

namespace MeLib
{
	CGridRowStyleMe::CGridRowStyleMe()
	{
		m_backColor = COLOR_CONTROL;
		m_font = new FONT(L"Simsun", 14, false, false, false);
		m_foreColor = COLOR_CONTROLTEXT;
		m_hoveredBackColor = COLOR::ARGB(150, 150, 150);
		m_hoveredForeColor = COLOR_CONTROLTEXT;
		m_selectedBackColor = COLOR::ARGB(100, 100, 100);
		m_selectedForeColor = COLOR_CONTROLTEXT;
	}
	
	CGridRowStyleMe::~CGridRowStyleMe()
	{
		if(m_font)
		{
			delete m_font;
		}
		m_font = 0;
	
	}
	
	_int64 CGridRowStyleMe::GetBackColor()
	{
		return m_backColor;
	}

	void CGridRowStyleMe::SetBackColor(_int64 backColor)
	{
		m_backColor = backColor;
	}

	FONT* CGridRowStyleMe::GetFont()
	{
		return m_font;
	}

	void CGridRowStyleMe::SetFont(FONT *font)
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
	
	_int64 CGridRowStyleMe::GetForeColor()
	{
		return m_foreColor;
	}

	void CGridRowStyleMe::SetForeColor(_int64 foreColor)
	{
		m_foreColor = foreColor;
	}

	_int64 CGridRowStyleMe::GetHoveredBackColor()
	{
		return m_hoveredBackColor;
	}

	void CGridRowStyleMe::SetHoveredBackColor(_int64 hoveredBackColor)
	{
		m_hoveredBackColor = hoveredBackColor;
	}

	_int64 CGridRowStyleMe::GetHoveredForeColor()
	{
		return m_hoveredForeColor;
	}

	void CGridRowStyleMe::SetHoveredForeColor(_int64 hoveredForeColor)
	{
		m_hoveredForeColor = hoveredForeColor;
	}
	
	_int64 CGridRowStyleMe::GetSelectedBackColor()
	{
		return m_selectedBackColor;
	}
	
	void CGridRowStyleMe::SetSelectedBackColor(_int64 selectedBackColor)
	{
		m_selectedBackColor = selectedBackColor;
	}
	
	_int64 CGridRowStyleMe::GetSelectedForeColor()
	{
		return m_selectedForeColor;
	}
	
	void CGridRowStyleMe::SetSelectedForeColor(_int64 selectedForeColor)
	{
		m_selectedForeColor = selectedForeColor;
	}

	void CGridRowStyleMe::Copy(CGridRowStyleMe *style)
	{
		m_backColor = style->m_backColor;
		m_font->Copy(style->m_font);
		m_foreColor = style->m_foreColor;
		m_hoveredBackColor = style->m_hoveredBackColor;
		m_hoveredForeColor = style->m_hoveredForeColor;
		m_selectedBackColor = style->m_selectedBackColor;
		m_selectedForeColor = style->m_selectedForeColor;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////
	CGridRowMe::CGridRowMe()
	{
		m_allowEdit = false;
		m_bounds.bottom = 0;
		m_bounds.left = 0;
		m_bounds.right = 0;
		m_bounds.top = 0;
		m_editButton = 0;
		m_grid = 0;
		m_height = 20;
		m_horizontalOffset = 0;
		m_index = -1;
		m_tag = 0;
		m_visible = true;
		m_visibleIndex = -1;
	}

	CGridRowMe::~CGridRowMe()
	{
		ClearCells();
	}
	
	bool CGridRowMe::AllowEdit()
	{
		return m_allowEdit;
	}
	
	void CGridRowMe::SetAllowEdit(bool allowEdit)
	{
		m_allowEdit = allowEdit;
	}
	
	RECT CGridRowMe::GetBounds()
	{
		return m_bounds;
	}
	
	void CGridRowMe::SetBounds(RECT bounds)
	{
		m_bounds = bounds;
	}
	
	CControlMe* CGridRowMe::GetEditButton()
	{
		return m_editButton;
	}
	
	void CGridRowMe::SetEditButton(CControlMe *editButton)
	{
		m_editButton = editButton;
	}

	CGridMe* CGridRowMe::GetGrid()
	{
		return m_grid;
	}
	
	void CGridRowMe::SetGrid(CGridMe *grid)
	{
		m_grid = grid;
	}
	
	int CGridRowMe::GetHeight()
	{
		return m_height;
	}
	
	void CGridRowMe::SetHeight(int height)
	{
		m_height = height;
	}
	
	int CGridRowMe::GetHorizontalOffset()
	{
		return m_horizontalOffset;
	}
	
	void CGridRowMe::SetHorizontalOffset(int horizontalOffset)
	{
		m_horizontalOffset = horizontalOffset;
	}
	
	int CGridRowMe::GetIndex()
	{
		return m_index;
	}
	
	void CGridRowMe::SetIndex(int index)
	{
		m_index = index;
	}
	
	void* CGridRowMe::GetTag()
	{
		return m_tag;
	}
	
	void CGridRowMe::SetTag(void *tag)
	{
		m_tag = tag;
	}
	
	bool CGridRowMe::IsVisible()
	{
		return m_visible;
	}
	
	void CGridRowMe::SetVisible(bool visible)
	{
		m_visible = visible;
	}
	
	int CGridRowMe::GetVisibleIndex()
	{
		return m_visibleIndex;
	}
	
	void CGridRowMe::SetVisibleIndex(int visibleIndex)
	{
		m_visibleIndex = visibleIndex;
	}

	void CGridRowMe::AddCell(int columnIndex, CGridCellMe *cell)
	{
		cell->SetGrid(m_grid);
		cell->SetColumn(m_grid->GetColumn(columnIndex));
		cell->SetRow(this);
		m_cells.push_back(cell);
		cell->OnAdd();		
	}
	
	void CGridRowMe::AddCell(const String& columnName, CGridCellMe *cell)
	{
		cell->SetGrid(m_grid);
		cell->SetColumn(m_grid->GetColumn(columnName));
		cell->SetRow(this);
		m_cells.push_back(cell);
		cell->OnAdd();		
	}
	
	void CGridRowMe::ClearCells()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnRemove();
			delete m_cells[i];
			m_cells[i] = 0;
		}
		m_cells.clear();
	}
	
	CGridCellMe* CGridRowMe::GetCell(int columnIndex)
	{
		int count = (int)m_cells.size();
		if (count > 0)
		{
			if (columnIndex >= 0 && columnIndex < count && m_cells[columnIndex]->GetColumn()->GetIndex() == columnIndex)
			{
				return m_cells[columnIndex];
			}
			for (int i = 0; i < count; i++)
			{
				if (m_cells[i]->GetColumn()->GetIndex() == columnIndex)
				{
					return m_cells[i];
				}
			}
		}
		return 0;	
	}
	
	CGridCellMe* CGridRowMe::GetCell(String columnName)
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			if (m_cells[i]->GetColumn()->GetName() == columnName)
			{
				return m_cells[i];
			}
		}
		return NULL;
	}

	vector<CGridCellMe*> CGridRowMe::GetCells()
	{
		return m_cells;
	}
	
	void CGridRowMe::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"allowedit")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowEdit());
		}
		else if (name == L"height")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetHeight());
		}
		else if (name == L"visible")
		{
			*type = L"int";
			*value = CStrMe::ConvertBoolToStr(IsVisible());
		}
		else
		{
			*type = L"undefined";
			*value = L"";
		}
	}
	
	vector<String> CGridRowMe::GetPropertyNames()
	{
		vector<String> list;
		list.push_back(L"AllowEdit");
		list.push_back(L"Height");
		list.push_back(L"Visible");
		return list;			
	}
	
	void CGridRowMe::OnAdd()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnAdd();
		}		
	}
	
	void CGridRowMe::OnPaint(CPaintMe *paint, const RECT& clipRect, bool isAlternate)
	{
		
	}
	
	void CGridRowMe::OnPaintBorder(CPaintMe *paint, const RECT& clipRect, bool isAlternate)
	{
		
	}
	
	void CGridRowMe::OnRemove()
	{
		int count = (int)m_cells.size();
		for (int i = 0; i < count; i++)
		{
			m_cells[i]->OnRemove();
		}
	}
	
	void CGridRowMe::RemoveCell(int columnIndex)
	{
		int count = (int)m_cells.size();
		if (columnIndex >= 0 && columnIndex < count)
		{
			CGridCellMe* item = m_cells[columnIndex];
			if (item->GetColumn()->GetIndex() == columnIndex)
			{
				m_cells.erase(m_cells.begin() + columnIndex);
				item->OnRemove();
				return;
			}
			else
			{
				for (int i = 0; i < count; i++)
				{
					item = m_cells[i];
					if (item->GetColumn()->GetIndex() == columnIndex)
					{
						m_cells.erase(m_cells.begin() + columnIndex);
						item->OnRemove();
						return;
					}
				}
			}
		}
	}
	
	void CGridRowMe::SetProperty(const String& name, const String& value)
	{
		if (name == L"allowedit")
		{
			SetAllowEdit(CStrMe::ConvertStrToBool(value));
		}
		else if (name == L"height")
		{
			SetHeight(CStrMe::ConvertStrToInt(value));
		}
		else if (name == L"visible")
		{
			SetVisible(CStrMe::ConvertStrToBool(value));
		}
	}
}