#include "..\\stdafx.h"
#include "..\\include\\Grid\\CBandedGrid.h"

namespace MeLib
{
	int CBandedGridAMe::GetAllVisibleBandsWidth()
	{
		int num = 0;
        int count = (int)m_bands.size();
        for (int i = 0; i < count; i++)
        {
            CGridBandMe* band = m_bands[i];
			if (band->IsVisible())
            {
                num += band->GetWidth();
            }
        }
        return num;
	}

	CBandedGridAMe::CBandedGridAMe()
	{
	
	}
	
	CBandedGridAMe:: ~CBandedGridAMe()
	{
		
	}
	
	void CBandedGridAMe::AddBand(CGridBandMe *band)
	{
		band->SetGrid(this);
		m_bands.push_back(band);
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			m_bands[i]->SetIndex(i);
		}
		AddControl(band);	
	}
	
	void CBandedGridAMe::AddColumn(CGridColumnMe *column)
	{
		CBandedGridColumnMe* bandedGridColumn = dynamic_cast<CBandedGridColumnMe*>(column);
		if(bandedGridColumn)
		{
			column->SetGrid(this);
			CGridMe::m_columns.push_back(column);
			AddControl(column);
		}	
	}
	
	void CBandedGridAMe::ClearBands()
	{
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			CGridBandMe* control = m_bands[i];
			RemoveControl(control);
			delete control;
			control = 0;
		}
		m_bands.clear();
	}
	
	void CBandedGridAMe::ClearColumns()
	{
		
	}
	vector<CGridBandMe*> CBandedGridAMe::GetBands()
	{
		return m_bands;
	}

	int CBandedGridAMe::GetContentWidth()
	{
        CHScrollBarMe* hScrollBar = GetHScrollBar();
        CVScrollBarMe* vScrollBar = GetVScrollBar();
        int wmax = 0;
        vector<CControlMe*> controls = GetControls();
        int count = (int)controls.size();
        for (int i = 0; i < count; i++)
        {
            CControlMe* la = controls[i];
            if (la->IsVisible() && la != hScrollBar && la != vScrollBar)
            {
                int right = la->GetRight();
                if (right > wmax)
                {
                    wmax = right;
                }
            }
        }
        int allVisibleBandsWidth = GetAllVisibleBandsWidth();
        if (wmax <= allVisibleBandsWidth)
        {
            return allVisibleBandsWidth;
        }
        return wmax;
	}
	
	String CBandedGridAMe::GetControlType()
	{
		return L"BandedGrid";
	}
	
	void CBandedGridAMe::InsertBand(int index, CGridBandMe *band)
	{
        band->SetGrid(this);
		m_bands.insert(m_bands.begin() + index, band);
        int count = (int)m_bands.size();
        for (int i = 0; i < count; i++)
        {
            m_bands[i]->SetIndex(i);
        }
        AddControl(band);		
	}

	void CBandedGridAMe::OnSetEmptyClipRegion()
	{
		vector<CControlMe*> controls = GetControls();
		int count = (int)controls.size();
		RECT rect = {0} ;
		for (int i = 0; i < count; i++)
		{
			CControlMe* control = controls[i];
			CScrollBarMe* scrollBar = dynamic_cast<CScrollBarMe*>(control);
			CGridColumnMe* gridColumn = dynamic_cast<CGridColumnMe*>(control);
			CGridBandMe* gridBand = dynamic_cast<CGridBandMe*>(control);
			if (control != GetEditTextBox() && !scrollBar && !gridColumn && !gridBand)
			{
				control->SetRegion(rect);
			}
		}		
	}
	
	void CBandedGridAMe::RemoveBand(CGridBandMe *band)
	{
		int count = (int)m_bands.size();
		bool isRemove = false;
		for(int i = 0; i < count; i++)
		{
			CGridBandMe* bItem = m_bands[i];
			if(bItem == band)
			{
				m_bands.erase(m_bands.begin() + i);
				isRemove = true;
				break;
			}
		}
		if(isRemove)
		{
			count = (int)m_bands.size();
			for (int i = 0; i < count; i++)
			{
				m_bands[i]->SetIndex(i);
			}
			RemoveControl(band);
		}
	}
	
	void CBandedGridAMe::RemoveColumn(CGridColumnMe *column)
	{
		CBandedGridColumnMe* bandedGridColumn = dynamic_cast<CBandedGridColumnMe*>(column);
		if(bandedGridColumn)
		{
			int size = (int)CGridMe::m_columns.size();
			for(int i = 0; i < size; i++)
			{
				if(CGridMe::m_columns[i] == column)
				{
					CGridMe::m_columns.erase(CGridMe::m_columns.begin() + i);
					RemoveControl(column);
					break;
				}
			}
        }		
	}
	
	void CBandedGridAMe::ResetHeaderLayout()
	{
		int left = 0;
		int top = 0;
		int scrollH = 0;
		CHScrollBarMe* hScrollBar = GetHScrollBar();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			scrollH = -hScrollBar->GetPos();
		}
		int headerHeight = IsHeaderVisible() ? CGridMe::GetHeaderHeight() : 0;
		int horizontalOffset = GetHorizontalOffset();
		int verticalOffset = GetVerticalOffset();
		int count = (int)m_bands.size();
		for (int i = 0; i < count; i++)
		{
			CGridBandMe* band = m_bands[i];
			if (band->IsVisible())
			{
				int bandHeight = (headerHeight < band->GetHeight()) ? headerHeight : band->GetHeight();
				RECT rect;
				rect.left = left + horizontalOffset;
				rect.top = top + verticalOffset;
				rect.right = left + horizontalOffset + band->GetWidth();
				rect.bottom = top + bandHeight + verticalOffset;
				bool hasFrozenColumn = false;
				vector<CBandedGridColumnMe*> allChildColumns = band->GetAllChildColumns();
				int childColumnsCount = (int)allChildColumns.size();
				for (int j = 0; j < childColumnsCount; j++)
				{
					if (allChildColumns[j]->IsFrozen())
					{
						hasFrozenColumn = true;
						break;
					}
				}
				if (!hasFrozenColumn)
				{
					rect.left += scrollH;
					rect.right += scrollH;
				}
				band->SetBounds(rect);
				band->ResetHeaderLayout();
				left += band->GetWidth();
			}
		}		
	}
	
	void CBandedGridAMe::Update()
	{
        if (!CGridMe::m_lockUpdate)
        {
            int count = (int)m_bands.size();
            int col = 0;
            for (int i = 0; i < count; i++)
            {
                vector<CBandedGridColumnMe*> allChildColumns = m_bands[i]->GetAllChildColumns();
                int childColumnsCount = (int)allChildColumns.size();
                for (int j = 0; j < childColumnsCount; j++)
                {
                    CBandedGridColumnMe* column = allChildColumns[j];
                    column->SetIndex(col);
                    col++;
                }
            }
        }
        CGridMe::Update();		
	}
}