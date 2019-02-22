#include "..\\stdafx.h"
#include "..\\include\\Chart\\CDiv.h"

namespace MeLib
{
	bool CDivMe::ShapesAsc(CBaseShapeMe *x, CBaseShapeMe *y)
	{
		return x->GetZOrder() < y->GetZOrder();
	}

	bool CDivMe::ShapesDesc(CBaseShapeMe *x, CBaseShapeMe *y)
	{
		return x->GetZOrder() > y->GetZOrder();
	}

	bool CDivMe::PlotsAsc(CPlotMe *x, CPlotMe *y)
	{
		return x->GetZOrder() < y->GetZOrder();
	}

	bool CDivMe::PlotsDesc(CPlotMe *x, CPlotMe *y)
	{
		return x->GetZOrder() > y->GetZOrder();
	}
	
	CDivMe::CDivMe()
	{
		m_allowUserPaint = false;
		m_borderColor = COLOR_EMPTY;
        m_chart = 0;
        m_crossLine = new CCrossLineMe();
        m_font = new FONT(L"Arial", 12, false, false, false);
        m_hGrid = new CScaleGridMe();
        m_hScale = new CHScaleMe();
        m_leftVScale = new CVScaleMe();
		m_location.x = 0;
		m_location.y = 0;
		m_px = 0;
		m_py = 0;
        m_rightVScale = new CVScaleMe();
		m_size.cx = 0;
		m_size.cy = 0;
        m_selectArea = new CSelectAreaMe();
        m_selected = false;
        m_showSelect = true;
        m_title = new CTitleBarMe();
        m_toolTip = new CToolTipMe();
        m_verticalPercent = 0;
        m_vGrid = new CScaleGridMe();
        m_vGrid->SetVisible(false);
	}

	CDivMe::~CDivMe()
	{
		if(m_crossLine) 
		{
			delete m_crossLine;
			m_crossLine = 0;
		}

		if(m_font)
		{
			delete m_font;
			m_font = 0;
		}

		if(m_hGrid)
		{
			delete m_hGrid;
			m_hGrid = 0;
		}
		if(m_hScale)
		{
			delete m_hScale;
			m_hScale = 0;
		}
		if(m_leftVScale) 
		{
			delete m_leftVScale;
			m_leftVScale = 0;
		}
		if(m_rightVScale)
		{
			delete m_rightVScale;
			m_rightVScale = 0;
		}
		if(m_selectArea)
		{
			delete m_selectArea;
			m_selectArea = 0;
		}
		if(m_title) 
		{
			delete m_title;
			m_title = 0;
		}
		if(m_toolTip) 
		{
			delete m_toolTip;
			m_toolTip = 0;
		}	
		if(m_vGrid) 
		{
			delete m_vGrid;
			m_vGrid = 0;
		}
		vector<CPlotMe*>::iterator it2 = m_plots.begin();
		for(; it2 != m_plots.end(); it2++)
		{
			CPlotMe* plot = *it2;
			delete plot;
		}
		m_plots.clear();

		vector<CBaseShapeMe*>::iterator it = m_shapes.begin();
		for(; it != m_shapes.end(); it++)
		{
			CBaseShapeMe* baseShape = *it;
			delete baseShape;
		}
		m_shapes.clear();
	}
	
	bool CDivMe::AllowUserPaint()
	{
		return m_allowUserPaint;
	}
	
	void CDivMe::SetAllowUserPaint(bool allowUserPaint)
	{
		m_allowUserPaint = allowUserPaint;
	}
	
	_int64 CDivMe::GetBackColor()
	{
		return m_backColor;
	}
	
	void CDivMe::SetBackColor(_int64 backColor)
	{
		m_backColor = backColor;
	}
	
	_int64 CDivMe::GetBorderColor()
	{
		return m_borderColor;
	}

	void CDivMe::SetBorderColor(_int64 borderColor)
	{
		m_borderColor = borderColor;
	}

	int CDivMe::GetBottom()
	{
		return m_location.y + m_size.cy;
	}

	RECT CDivMe::GetBounds()
	{
		RECT rect = {m_location.x, m_location.y, m_location.x + m_size.cx, m_location.y + m_size.cy};
		return rect;
	}

	void CDivMe::SetBounds(RECT bounds)
	{
		m_location.x = bounds.left;
		m_location.y = bounds.top;
		m_size.cx = bounds.right - bounds.left;
		m_size.cy = bounds.bottom - bounds.top;
	}

	CCrossLineMe* CDivMe::GetCrossLine()
	{
		return m_crossLine;
	}

	void CDivMe::SetCrossLine(CCrossLineMe *crossLine)
	{
		if(m_crossLine)
		{
			delete m_crossLine;
			m_crossLine = 0;
		}
		m_crossLine = crossLine;
	}

	FONT* CDivMe::GetFont()
	{
		return m_font;
	}
	
	void CDivMe::SetFont(FONT *font)
	{
		m_font->Copy(font);
	}

	int CDivMe::GetHeight()
	{
		return m_size.cy;
	}

	CScaleGridMe* CDivMe::GetHGrid()
	{
		return m_hGrid;
	}

	void CDivMe::SetHGrid(CScaleGridMe *hGrid)
	{
		if(m_hGrid)
		{
			delete m_hGrid;
			m_hGrid = 0;
		}
		m_hGrid = hGrid;
	}

	CHScaleMe* CDivMe::GetHScale()
	{
		return m_hScale;
	}

	void CDivMe::SetHScale(CHScaleMe *hScale)
	{
		if(m_hScale)
		{
			delete m_hScale;
			m_hScale = 0;
		}
		m_hScale = hScale;
	}

	CChartMe* CDivMe::GetChart()
	{
		return m_chart;
	}

	void CDivMe::SetChart(CChartMe *chart)
	{
		m_chart = chart;
	}

	int CDivMe::GetLeft()
	{
		return m_location.x;
	}

	CVScaleMe* CDivMe::GetLeftVScale()
	{
		return m_leftVScale;
	}

	void CDivMe::SetLeftVScale(CVScaleMe *leftVScale)
	{
		if(m_leftVScale)
		{
			delete m_leftVScale;
			m_leftVScale = 0;
		}
		m_leftVScale = leftVScale;
	}

	POINT CDivMe::GetLocation()
	{
		POINT point = {m_location.x, m_location.y};
		return point;
	}

	int CDivMe::GetPx()
	{
		return m_px;
	}

	void CDivMe::SetPx(int px)
	{
		m_px = px;
	}

	int CDivMe::GetPy()
	{
		return m_py;
	}

	void CDivMe::SetPy(int py)
	{
		m_py = py;
	}
	
	int CDivMe::GetRight()
	{
		return m_size.cx + m_location.x;
	}
	
	CVScaleMe* CDivMe::GetRightVScale()
	{
		return m_rightVScale;
	}
	
	void CDivMe::SetRightVScale(CVScaleMe *rightVScale)
	{
		if(m_rightVScale)
		{
			delete m_rightVScale;
			m_rightVScale = 0;
		}
		m_rightVScale = rightVScale;
	}
	
	CSelectAreaMe* CDivMe::GetSelectArea()
	{
		return m_selectArea;
	}

	void CDivMe::SetSelectArea(CSelectAreaMe *selectArea)
	{
		if(m_selectArea)
		{
			delete m_selectArea;
			m_selectArea = 0;
		}
		m_selectArea = selectArea;
	}

	bool CDivMe::IsSelected()
	{
		return m_selected;
	}
	
	void CDivMe::SetSelected(bool selected)
	{
		m_selected = selected;
	}
	
	bool CDivMe::IsShowSelect()
	{
		return m_showSelect;
	}

	void CDivMe::SetShowSelect(bool showSelect)
	{
		m_showSelect = showSelect;
	}
	
	CTitleBarMe* CDivMe::GetTitleBar()
	{
		return m_title;
	}
	
	void CDivMe::SetTitleBar(CTitleBarMe *title)
	{
		if(m_title)
		{
			delete m_title;
			m_title = 0;
		}
		m_title = title;
	}

	CToolTipMe* CDivMe::GetToolTip()
	{
		return m_toolTip;
	}
	
	void CDivMe::SetToolTip(CToolTipMe *toolTip)
	{
		if(m_toolTip)
		{
			delete m_toolTip;
			m_toolTip = 0;
		}
		m_toolTip = toolTip;
	}
	
	int CDivMe::GetTop()
	{
		return m_location.y;
	}

	int CDivMe::GetVerticalPercent()
	{
		return m_verticalPercent;
	}
	
	void CDivMe::SetVerticalPercent(int verticalPercent)
	{
		m_verticalPercent = verticalPercent;
	}
	
	CScaleGridMe* CDivMe::GetVGrid()
	{
		return m_vGrid;
	}
	
	void CDivMe::SetVGrid(CScaleGridMe *vGrid)
	{
		if(m_vGrid)
		{
			delete m_vGrid;
			m_vGrid = 0;
		}
		m_vGrid = vGrid;
	}
	
	int CDivMe::GetWidth()
	{
		return m_size.cx;
	}
	
	int CDivMe::GetWorkingAreaHeight()
	{
		return m_workingAreaHeight;
	}
	
	void CDivMe::SetWorkingAreaHeight(int workingAreaHeight)
	{
		m_workingAreaHeight = workingAreaHeight;
	}		
	
	void CDivMe::AddPlot(CPlotMe *plot)
	{
		m_plots.push_back(plot);
	}
	
	void CDivMe::AddShape(CBaseShapeMe *shape)
	{
		m_shapes.push_back(shape);
	}
	
	bool CDivMe::ContainsShape(CBaseShapeMe *shape)
	{
		vector<CBaseShapeMe*> shapesCopy = GetShapes(SORTTYPE_NONE);
		vector<CBaseShapeMe*>::iterator it = shapesCopy.begin();
		for(; it != shapesCopy.end(); it++)
		{
			CBaseShapeMe* shape2 = *it;
			if(shape2 == shape)
			{
				return true;
			}
		}
		return false;
	}
	
	vector<CPlotMe*> CDivMe::GetPlots(SORTTYPE sortType)
	{
		vector<CPlotMe*> plist;		 
		int plotsSize = (int)m_plots.size();
		for (int i = 0; i < plotsSize; i++) 
		{
			plist.push_back(m_plots.at(i));
		}
		if (sortType == SORTTYPE_ASC) 
		{			
			std::sort(plist.begin(), plist.end(), PlotsAsc);
		} 
		else if (sortType == SORTTYPE_DESC) 
		{
			std::sort(plist.begin(), plist.end(), PlotsAsc);
		}
		return plist;
	}

	void CDivMe::GetProperty(const String& name, String *value, String *type)
	{
		if(name == L"allowuserpaint") 
		{
            *type = L"bool";
            *value = CStrMe::ConvertBoolToStr(AllowUserPaint());
        } else if(name == L"backcolor") 
		{
			*type = L"color";
            *value = CStrMe::ConvertColorToStr(GetBackColor());
        } else if(name == L"bordercolor") 
		{
			*type = L"color";
            *value = CStrMe::ConvertColorToStr(GetBorderColor());
        } else if(name == L"showselect") 
		{
           * type = L"bool";
           * value = CStrMe::ConvertBoolToStr(IsShowSelect());
        }
	}

	vector<String> CDivMe::GetPropertyNames()
	{
	    vector<String> propertyNames;
        propertyNames.push_back(L"AllowUserPaint");
		propertyNames.push_back(L"BackColor");
		propertyNames.push_back(L"BorderColor");
		propertyNames.push_back(L"ShowSelect");
        return propertyNames;
	}

	vector<CBaseShapeMe*> CDivMe::GetShapes(SORTTYPE sortType)
	{
		vector<CBaseShapeMe*> slist ;
		int shapesSize = (int)m_shapes.size();
        for(int i = 0; i < shapesSize; ++i) 
		{
            slist.push_back(m_shapes.at(i));
        }
        if(sortType == SORTTYPE_ASC) 
		{
			std::sort(slist.begin(), slist.end(), ShapesAsc);
        } 
		else if(sortType == SORTTYPE_DESC) 
		{
			std::sort(slist.begin(), slist.end(), ShapesDesc);
        }
        return slist;
	}

	CVScaleMe* CDivMe::GetVScale(AttachVScale attachVScale)
	{
        return attachVScale == AttachVScale_Left ? m_leftVScale : m_rightVScale;
	}

	void CDivMe::OnPaint(CPaintMe *paint, const RECT& rect)
	{
	}

	void CDivMe::RemovePlot(CPlotMe *plot)
	{
		vector<CPlotMe*>::iterator it = m_plots.begin();
		for(; it != m_plots.end(); it++)
		{
			CPlotMe* item = *it;
			if(item == plot)
			{
				m_plots.erase(it);
				delete item;
				break;
			}
		}
	}

	void CDivMe::RemoveShape(CBaseShapeMe *shape)
	{
		vector<CBaseShapeMe*>::iterator it = m_shapes.begin();
		for(; it!=m_shapes.end(); it++)
		{
			CBaseShapeMe* bs = *it;
			if(bs == shape)
			{
				m_shapes.erase(it);
				delete bs;
				break;
			}
		}

	}
	void CDivMe::SetProperty(const String& name, const String& value)
	{
        if(name == L"allowuserpaint") 
		{
            SetAllowUserPaint(CStrMe::ConvertStrToBool(value));
        } else if(name == L"backcolor") 
		{
            SetBackColor(CStrMe::ConvertStrToColor(value));
        } else if(name == L"bordercolor") 
		{
            SetBorderColor(CStrMe::ConvertStrToColor(value));
        } else if(name == L"showselect") 
		{
            SetShowSelect(CStrMe::ConvertStrToBool(value));
        }	
	}
}