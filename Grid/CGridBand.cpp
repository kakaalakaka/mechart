#include "..\\stdafx.h"
#include "..\\include\\Grid\\CGridBand.h"

namespace MeLib
{
	CGridBandMe::CGridBandMe()
	{
		m_beginWidth = 0;
		m_allowResize = 0;
		m_grid = 0;
		m_index = -1;
		m_mouseDownPoint.x = 0;
		m_mouseDownPoint.y = 0;
		m_parentBand = 0;
		m_resizeState = 0;
		SetWidth(100);
	}
	
	CGridBandMe::~CGridBandMe()
	{
		ClearBands();
		ClearColumns();
		m_grid = 0;
		m_parentBand = 0;		
	}

	bool CGridBandMe::AllowResize()
	{
		return m_allowResize;
	}
	
	void CGridBandMe::SetAllowResize(bool allowResize)
	{
		m_allowResize = allowResize;
	}
	
	CBandedGridMe* CGridBandMe::GetGrid()
	{
		return m_grid;
	}
	
	void CGridBandMe::SetGrid(CBandedGridMe *grid)
	{
		m_grid = grid;
	}
	
	int CGridBandMe::GetIndex()
	{
		return m_index;
	}
	void CGridBandMe::SetIndex(int index)
	{
		m_index = index;
	}
	
	CGridBandMe* CGridBandMe::GetParentBand()
	{
		return m_parentBand;
	}

	void CGridBandMe::SetParentBand(CGridBandMe *parentBand)
	{
		m_parentBand = parentBand;
	}

	void CGridBandMe::AddBand(CGridBandMe *band)
	{
		band->SetGrid(m_grid);
		band->SetParentBand(this);
		m_bands.push_back(band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		m_grid->AddControl(band);
	}

	void CGridBandMe::AddColumn(CBandedGridColumnMe *column)
	{
		column->SetBand(this);
		m_columns.push_back(column);
		m_grid->AddColumn(column);		
	}
	
	void CGridBandMe::ClearBands()
	{
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			CGridBandMe* control = m_bands[i];
			m_grid->RemoveControl(control);
			delete control;
			control = 0;
		}
		m_bands.clear();
	}
	
	void CGridBandMe::ClearColumns()
	{
		int count = (int)m_columns.size();
		for (int i = 0; i < count; i++)
		{
			CBandedGridColumnMe* column = m_columns[i];
			m_grid->RemoveColumn(column);
			delete column;
			column = 0;
		}
		m_columns.clear();
	}
	
	vector<CBandedGridColumnMe*> CGridBandMe::GetAllChildColumns()
	{
		vector<CBandedGridColumnMe*> list;
		int count = (int)m_columns.size();
		for (int i = 0; i < count; i++)
		{
			CBandedGridColumnMe* item = m_columns[i];
			list.push_back(item);
		}
		int bandCount = (int)m_bands.size();
		for (int j = 0; j < bandCount; j++)
		{
			vector<CBandedGridColumnMe*> allChildColumns = m_bands[j]->GetAllChildColumns();
			int childColumnsCount = (int)allChildColumns.size();
			for (int k = 0; k < childColumnsCount; k++)
			{
				CBandedGridColumnMe* column2 = allChildColumns[k];
				list.push_back(column2);
			}
		}
		return list;		
		
	}
	
	vector<CGridBandMe*> CGridBandMe::GetBands()
	{
		return m_bands;
	}
	
	vector<CBandedGridColumnMe*> CGridBandMe::GetColumns()
	{
		return m_columns;
	}
	
	String CGridBandMe::GetControlType()
	{
		return L"GridBand";
	}

	void CGridBandMe::GetProperty(const String& name, String *value, String *type)
	{
		if (name == L"allowresize")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AllowResize());
		}
		else
		{
			CButtonMe::GetProperty(name, value, type);
		}
	}
	vector<String> CGridBandMe::GetPropertyNames()
	{
		vector<String> propertyNames = CButtonMe::GetPropertyNames();
		propertyNames.push_back(L"AllowResize" );
		return propertyNames;
	}
	
	void CGridBandMe::InsertBand(int index, CGridBandMe *band)
	{
		band->SetGrid(m_grid);
		band->SetParentBand(this);
		m_bands.insert(m_bands.begin() + index, band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		m_grid->AddControl(band);
	}
	
	void CGridBandMe::InsertColumn(int index, CBandedGridColumnMe *column)
	{
        column->SetBand(this);
		m_columns.insert(m_columns.begin() + index, column);
        m_grid->AddColumn(column);		
	}

	void CGridBandMe::OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CButtonMe::OnMouseDown(mp, button, clicks, delta);
        if ((button == MouseButtonsMe_Left && clicks == 1) && m_allowResize)
        {
            vector<CGridBandMe*> bands;
            if (m_parentBand)
            {
                bands = m_parentBand->GetBands();
            }
            else
            {
                bands = m_grid->GetBands();
            }
            int count = (int)bands.size();
            if (m_index > 0 && mp.x < 5)
            {
                m_resizeState = 1;
                m_beginWidth = bands[m_index - 1]->GetWidth();
            }
            else if ((!m_parentBand || m_index < count - 1) && mp.x > GetWidth() - 5)
            {
                m_resizeState = 2;
                m_beginWidth = GetWidth();
            }
            m_mouseDownPoint = GetNative()->GetMousePoint();
        }
	}

	void CGridBandMe::OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CButtonMe::OnMouseMove(mp, button, clicks, delta);
        if (m_allowResize)
        {
            vector<CGridBandMe*> bands;
            if (m_parentBand)
            {
                bands = m_parentBand->GetBands();
            }
            else
            {
                bands = m_grid->GetBands();
            }
            int count = (int)bands.size();
            int width = GetWidth();
            if (m_resizeState > 0)
            {
                POINT curPoint = GetNative()->GetMousePoint();
                int newWidth = m_beginWidth + curPoint.x - m_mouseDownPoint.x;
                if (newWidth > 0)
                {
                    if (m_resizeState == 1)
                    {
                        CGridBandMe* leftBand = bands[m_index - 1];
                        int leftWidth = leftBand->GetWidth();
                        leftBand->SetWidth(newWidth);
                        width += leftWidth - newWidth;
                        SetWidth(width);
                    }
                    else if (m_resizeState == 2)
                    {
                        SetWidth(newWidth);
                        if (m_index < count - 1)
                        {
                            CGridBandMe* rightBand = bands[m_index + 1];
                            int rightWidth = rightBand->GetWidth() + width - newWidth;
                            rightBand->SetWidth(rightWidth);
                        }
                        else if (m_grid)
                        {
                            m_grid->ResetHeaderLayout();
                            m_grid->Update();
                        }
                    }
                }
                if (m_grid)
                {
                    m_grid->Invalidate();
                }
            }
            else if ((m_index <= 0 || mp.x >= 5) && m_parentBand && (m_index >= count - 1 || mp.x <= width - 5))
            {
				SetCursor(CursorsMe_Arrow);
            }
            else
			{
				SetCursor(CursorsMe_SizeWE);
            }
        }
	}
	void CGridBandMe::OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		if (m_resizeState != 0)
		{
			CButtonMe::OnMouseUp(mp, button, clicks, delta);
			SetCursor(CursorsMe_Arrow);
			m_resizeState = 0;
			if (m_grid)
			{
				m_grid->Invalidate();
			}
		}
	}
	
	void CGridBandMe::RemoveBand(CGridBandMe *band)
	{
		int size = (int)m_bands.size();
		bool flag = false;
		for(int i = 0; i < size; i++)
		{
			CGridBandMe* item = m_bands[i];
			if(item == band)
			{
				m_bands.erase(m_bands.begin() + i);
				flag = true;
				break;
			}
		}
		if(flag)
		{
			int count = (int)m_bands.size();
			for (int i = 0; i < count; i++)
			{
				m_bands[i]->SetIndex(i);
			}
			m_grid->RemoveControl(band);
		}
	}

	void CGridBandMe::RemoveColumn(CBandedGridColumnMe *column)
	{
		int size = (int)m_columns.size();
		for(int i = 0; i < size; i++)
		{
			CBandedGridColumnMe* item = m_columns[i];
			if(item == column)
			{
				m_columns.erase(m_columns.begin() + i);
				m_grid->RemoveColumn(column);
				break;
			}			
		}	
	}
	
	void CGridBandMe::ResetHeaderLayout()
	{
		int bandsSize = (int)m_bands.size();
		RECT bounds = GetBounds();
		int left = bounds.left;
		int width = GetWidth();
		if (bandsSize == 0)
		{
			int scrollH = 0;
			CHScrollBarMe* hScrollBar = GetGrid()->GetHScrollBar();
			if (hScrollBar && hScrollBar->IsVisible())
			{
				scrollH = -hScrollBar->GetPos();
			}
			int columnsSize = (int)m_columns.size();
			for (int i = 0; i < columnsSize; i++)
			{
				CBandedGridColumnMe* column = m_columns[i];
				if (column->IsVisible())
				{
					int columnWidth = column->GetWidth();
					if (i == columnsSize - 1 || left + columnWidth > width + bounds.left)
					{
						columnWidth = width + bounds.left - left;
					}
					RECT cellRect;
					cellRect.left = left;
					cellRect.top = bounds.bottom;
					cellRect.right = left + columnWidth;
					cellRect.bottom = bounds.bottom + column->GetHeight();
					column->SetBounds(cellRect);
					cellRect.left -= scrollH;
					cellRect.right -= scrollH;
					column->SetHeaderRect(cellRect);
					left += columnWidth;
				}
			}
		}
		else
		{
			for (int j = 0; j < bandsSize; j++)
			{
				CGridBandMe *band = m_bands[j];
				if (band->IsVisible())
				{
					int bandWidth = band->GetWidth();
					if (j == bandsSize - 1 || left + bandWidth > width + bounds.left)
					{
						bandWidth = width + bounds.left - left;
					}
					RECT cellRect ;
					cellRect.left = left;
					cellRect.top = bounds.bottom;
					cellRect.right = left + bandWidth;
					cellRect.bottom = bounds.bottom + band->GetHeight();
					band->SetBounds(cellRect);
					band->ResetHeaderLayout();
					left += bandWidth;
				}
			}
		}	
	}

	void CGridBandMe::SetProperty(const String& name, const String& value)
	{
		if (name == L"allowresize")
		{
			SetAllowResize(CStrMe::ConvertStrToBool(value));
		}
		else
		{
			CButtonMe::SetProperty(name, value);
		}		
	}
}