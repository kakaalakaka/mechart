#include "..\\stdafx.h"
#include "..\\include\\Chart\\CChart.h"
#include <iterator>

namespace MeLib
{
	CChartMe::CChartMe()
	{
		m_autoFillHScale = false;
		m_blankSpace = 0;
		m_canMoveShape = true;
		m_canResizeV = true;
		m_canResizeH = true;
		m_canScroll = true;
		m_canZoom = true;
		m_crossLineMoveMode = CrossLineMoveMode_FollowMouse;
		m_crossStopIndex = -1;
		m_cross_y = -1;
		m_dataSource = new CTableMe();
		m_firstVisibleIndex = -1;
		m_hResizeType = 0;
		m_hScaleFieldText = L"";
		m_hScalePixel = 7;
		m_isScrollCross = false;
		m_lastRecordIsVisible = false;
		m_lastUnEmptyIndex = -1;
		m_lastVisibleKey = 0;
		m_lastVisibleIndex = -1;
		m_leftVScaleWidth = 80;
		m_maxVisibleRecord = 0;
		m_movingPlot = 0;
		m_movingShape = 0;
	    m_reverseHScale = false;
	    m_rightVScaleWidth = 80;
	    m_scrollAddSpeed = true;
	    m_scrollStep = 1;
	    m_showCrossLine = false;
		m_showingSelectArea = false;
	    m_showingToolTip = false;
		m_timerID = GetNewTimerID();
	    m_tooltip_dely = 1;
	    m_userResizeDiv = 0;
	    m_workingAreaWidth = 0;
		m_cross_y = -1;
		m_scrollStep = 1;
		m_lastMouseMovePoint.x = 0;
		m_lastMouseMovePoint.y = 0;
		m_lastMouseClickPoint.x = 0;
		m_lastMouseClickPoint.y = 0;
		m_lastMouseMoveTime = 0;
		m_isMouseMove = false;
		m_lastMouseMoveTime = 0;
	}

	CChartMe::~CChartMe()
	{
		StopTimer(m_timerID);
		RemoveAll();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool CChartMe::AutoFillHScale()
	{
		return m_autoFillHScale;
	}

	void CChartMe::SetAutoFillHScale(bool autoFillHScale)
	{
		m_autoFillHScale = autoFillHScale;
	}

	int CChartMe::GetBlankSpace()
	{
		return m_blankSpace;
	}

	void CChartMe::SetBlankSpace(int blankSpace)
	{
		m_blankSpace = blankSpace;
	}

	bool CChartMe::CanMoveShape()
	{
		return m_canMoveShape;
	}

	void CChartMe::SetCanMoveShape(bool canMoveShape)
	{
		m_canMoveShape = canMoveShape;
	}

	bool CChartMe::CanResizeV()
	{
		return m_canResizeV;
	}

	void CChartMe::SetCanResizeV(bool canResizeV)
	{
		m_canResizeV = canResizeV;
	}

	bool CChartMe::CanResizeH()
	{
		return m_canResizeH;
	}

	void CChartMe::SetCanResizeH(bool canResizeH)
	{
		m_canResizeH = canResizeH;
	}

	bool CChartMe::CanScroll()
	{
		return m_canScroll;
	}

	void CChartMe::SetCanScroll(bool canScroll)
	{
		m_canScroll = canScroll;
	}

	bool CChartMe::CanZoom()
	{
		return m_canZoom;
	}

	void CChartMe::SetCanZoom(bool canZoom)
	{
		m_canZoom = canZoom;
	}

	CrossLineMoveMode CChartMe::GetCrossLineMoveMode()
	{
		return m_crossLineMoveMode;
	}

	void CChartMe::SetCrossLineMoveMode(CrossLineMoveMode crossLineMoveMode)
	{
		m_crossLineMoveMode = crossLineMoveMode;
	}

	int CChartMe::GetCrossStopIndex()
	{
		return m_crossStopIndex;
	}

	void CChartMe::SetCrossStopIndex(int crossStopIndex)
	{
		m_crossStopIndex = crossStopIndex;
	}

	CTableMe* CChartMe::GetDataSource()
	{
		return m_dataSource;
	}

	void CChartMe::SetDataSource(CTableMe *dataSource)
	{
		m_dataSource = dataSource;
	}

	int CChartMe::GetFirstVisibleIndex()
	{
		return m_firstVisibleIndex;
	}

	void CChartMe::SetFirstVisibleIndex(int firstVisibleIndex)
	{
		m_firstVisibleIndex = firstVisibleIndex;
	}

	String CChartMe::GetHScaleFieldText()
	{
		return m_hScaleFieldText;
	}

	void CChartMe::SetHScaleFieldText(const String& hScaleFieldText)
	{
		m_hScaleFieldText = hScaleFieldText;
	}

	double CChartMe::GetHScalePixel()
	{
		return m_hScalePixel;
	}

	void CChartMe::SetHScalePixel(double hScalePixel)
	{
		m_hScalePixel = hScalePixel;
		if (m_hScalePixel > 1) m_hScalePixel = (int)m_hScalePixel;
        if (m_hScalePixel > 1 && (int)m_hScalePixel % 2 == 0)
        {
            m_hScalePixel += 1;
        }
	}

	int CChartMe::GetLastVisibleIndex()
	{
		return m_lastVisibleIndex;
	}

	void CChartMe::SetLastVisibleIndex(int lastVisibleIndex)
	{
		m_lastVisibleIndex = lastVisibleIndex;
	}

	int CChartMe::GetLeftVScaleWidth()
	{
		return m_leftVScaleWidth;
	}

	void CChartMe::SetLeftVScaleWidth(int leftVScaleWidth)
	{
		m_leftVScaleWidth = leftVScaleWidth;
	}

	int CChartMe::GetMaxVisibleRecord()
	{
		return m_maxVisibleRecord;
	}

	void CChartMe::SetMaxVisibleRecord(int maxVisibleRecord)
	{
		m_maxVisibleRecord = maxVisibleRecord;
	}

	CPlotMe* CChartMe::GetMovingPlot()
	{
		return m_movingPlot;
	}

	CBaseShapeMe* CChartMe::GetMovingShape()
	{
		return m_movingShape;
	}

	bool CChartMe::IsReverseHScale()
	{
		return m_reverseHScale;
	}

	void CChartMe::SetReverseHScale(bool reverseHScale)
	{
		m_reverseHScale = reverseHScale;
	}

	int CChartMe::GetRightVScaleWidth()
	{
		return m_rightVScaleWidth;
	}

	void CChartMe::SetRightVScaleWidth(int rightVScaleWidth)
	{
		m_rightVScaleWidth = rightVScaleWidth;
	}

	bool CChartMe::IsScrollAddSpeed()
	{
		return m_scrollAddSpeed;
	}

	void CChartMe::SetScrollAddSpeed(bool scrollAddSpeed)
	{
		m_scrollAddSpeed = scrollAddSpeed;
	}

	CBaseShapeMe* CChartMe::GetSelectedShape()
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(;sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *shape = *sIter2;
				if(shape->IsSelected())
				{
					return shape;
				}
			}
		}
		return 0;
	}

	void CChartMe::SetSelectedShape(CBaseShapeMe *baseShape)
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(;sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *shape = *sIter2;
				if(shape == baseShape)
				{
					shape->SetSelected(true);
				}
				else
				{
					shape->SetSelected(false);
				}
			}
		}
	}

	CPlotMe* CChartMe::GetSelectedPlot()
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CPlotMe*> plotsCopy = div->GetPlots(SORTTYPE_NONE); 
			vector<CPlotMe*>::iterator sIter2 = plotsCopy.begin();
			for(; sIter2 != plotsCopy.end(); ++sIter2)
			{
				CPlotMe *plot = *sIter2;
				if(plot->IsVisible() && plot->IsSelected())
				{
					return plot;
				}
			}
		}
		return 0;
	}

	void CChartMe::SetSelectedPlot(CPlotMe *selectedPlot)
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CPlotMe*> plotsCopy = div->GetPlots(SORTTYPE_NONE); 
			vector<CPlotMe*>::iterator sIter2 = plotsCopy.begin();
			for(; sIter2 != plotsCopy.end(); ++sIter2)
			{
				CPlotMe *plot = *sIter2;
				if(plot == selectedPlot)
				{
					plot->SetSelected(true);
				}
				else
				{
					plot->SetSelected(false);
				}
			}
		}
	}

	CDivMe* CChartMe::GetSelectedDiv()
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			if(div->IsSelected())
			{
				return div;
			}
		}
		return 0;
	}

	void CChartMe::SetSelectedDiv(CDivMe *selectedDiv)
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
        for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			if(div == selectedDiv)
			{
				div->SetSelected(true);
			}
			else
			{
				div->SetSelected(false);
			}
		}
	}

	bool CChartMe::IsShowCrossLine()
	{
		return m_showCrossLine;
	}

	void CChartMe::SetShowCrossLine(bool showCrossLine)
	{
		m_showCrossLine = showCrossLine;
	}

	int CChartMe::GetWorkingAreaWidth()
	{
		return m_workingAreaWidth;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CDivMe* CChartMe::AddDiv(int vPercent)
	{
		if(vPercent <= 0)
		{
			return 0;
		}
		CDivMe *cDiv = new CDivMe;
		cDiv->SetVerticalPercent(vPercent);
		cDiv->SetChart(this);
		m_divs.push_back(cDiv);
		Update();
		return cDiv;
	}

	CDivMe* CChartMe::AddDiv()
	{
		vector<CDivMe*> divsCopy = GetDivs();
		int pNum = (int)divsCopy.size() + 1;
		return AddDiv(100 / pNum);
	}

	void CChartMe::AddPlot(CPlotMe* bpl, const POINT& mp, CDivMe *div)
    {
        if (div && m_dataSource->RowsCount() >= 2)
        {
            int rIndex = GetIndex(mp);
            if (rIndex < 0 || rIndex > m_lastVisibleIndex)
            {
                return;
            }
            if (bpl)
            {
                bpl->SetDiv(div);
                bpl->SetSelected(true);
				vector<CPlotMe*> plots = div->GetPlots(SORTTYPE_NONE);
				double *zorders = new double[plots.size()];
				vector<CPlotMe*>::iterator sIter = plots.begin();
				int i = 0;
				for(; sIter != plots.end(); ++sIter)
                {
					CPlotMe *plot = *sIter;
					zorders[i] = plot->GetZOrder();
					i++;
				}
                bpl->SetZOrder((int)CMathLibMe::GetMax(zorders, (int)plots.size()) + 1);
                bool flag = bpl->OnCreate(mp);
                if (flag)
                {
                    div->AddPlot(bpl);
                    m_movingPlot = bpl;
                    m_movingPlot->OnSelect();
                }
				delete[] zorders;
				zorders = 0;
            }
            CloseSelectArea();
        }
    }

	void CChartMe::Adjust()
    {
        if (m_workingAreaWidth > 0)
        {
			m_lastUnEmptyIndex = -1;
            if (m_firstVisibleIndex < 0 || m_lastVisibleIndex > m_dataSource->RowsCount() - 1)
            {
                return;
            }
            vector<CDivMe*> divsCopy = GetDivs();
			vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for (; sIter != divsCopy.end(); ++sIter)
            {
				CDivMe *cDiv = *sIter;
				CVScaleMe *leftVScale = cDiv->GetLeftVScale();
				CVScaleMe *rightVScale = cDiv->GetRightVScale();
				cDiv->SetWorkingAreaHeight(cDiv->GetHeight() - cDiv->GetHScale()->GetHeight() - cDiv->GetTitleBar()->GetHeight() - 1);
                vector<CBaseShapeMe*> shapesCopy = cDiv->GetShapes(SORTTYPE_NONE);
                double leftMax = 0, leftMin = 0, rightMax = 0, rightMin = 0;
				bool leftMaxInit = false, leftMinInit = false, rightMaxInit = false, rightMinInit = false;
                if (m_dataSource->RowsCount() > 0)
                {
					vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
                    for(; sIter2 != shapesCopy.end(); ++sIter2)
                    {
						CBaseShapeMe *bs = *sIter2;
						if(!bs->IsVisible())
						{
							continue;
						}
                        CBarShapeMe *bar = dynamic_cast<CBarShapeMe*>(bs);
						int fieldsLength = 0;
                        int *fields = bs->GetFields(&fieldsLength);
						for (int f = 0; f < fieldsLength; f++)
                        {
							int field = m_dataSource->GetColumnIndex(fields[f]);
							for (int m = m_firstVisibleIndex; m <= m_lastVisibleIndex; m++)
							{
								double fieldValue = m_dataSource->Get3(m, field);
								if (!m_dataSource->IsNaN(fieldValue))
								{
									m_lastUnEmptyIndex = m;
									if (bs->GetAttachVScale() == AttachVScale_Left)
									{
										if (fieldValue > leftMax || !leftMaxInit)
										{
											leftMaxInit = true;
											leftMax = fieldValue;
										}
										if (fieldValue < leftMin || !leftMinInit)
										{
											leftMinInit = true;
											leftMin = fieldValue;
										}
									}
									else
									{
										if (fieldValue > rightMax || !rightMaxInit)
										{
											rightMaxInit = true;
											rightMax = fieldValue;
										}
										if (fieldValue < rightMin || !rightMinInit)
										{
											rightMinInit = true;
											rightMin = fieldValue;
										}
									}
								}
							}
                        }
						if (bar)
                        {
                            double midValue = 0;
							if(bar->GetFieldName2() == CTableMe::NULLFIELD())
							{
								if (bs->GetAttachVScale() == AttachVScale_Left)
								{
									if (midValue > leftMax || !leftMaxInit)
									{
										leftMaxInit = true;
										leftMax = midValue;
									}
									if (midValue < leftMin || !leftMinInit)
									{
										leftMinInit = true;
										leftMin = midValue;
									}
								}
								else
								{
									if (midValue > rightMax|| !rightMaxInit)
									{
										rightMaxInit = true;
										rightMax = midValue;
									}
									if (midValue < rightMin || !rightMinInit)
									{
										rightMinInit = true;
										rightMin = midValue;
									}
								}
							}
                        }
						if(fields)
						{
							delete[] fields;
							fields = 0;
						}
                    }
					if(leftMax == leftMin)
					{
						leftMax = leftMax * 1.01;
						leftMin = leftMin * 0.99;
					}
					if(rightMax == rightMin)
					{
						rightMax = rightMax * 1.01;
						rightMin = rightMin * 0.99;
					}
                }
				if(leftVScale->AutoMaxMin())
				{
					leftVScale->SetVisibleMax(leftMax);
					leftVScale->SetVisibleMin(leftMin);
				}
				if(rightVScale->AutoMaxMin())
				{
					rightVScale->SetVisibleMax(rightMax);
					rightVScale->SetVisibleMin(rightMin);
				}
				if (leftVScale->AutoMaxMin() && leftVScale->GetVisibleMax() == 0 && leftVScale->GetVisibleMin() == 0)
				{
					leftVScale->SetVisibleMax(rightVScale->GetVisibleMax());
					leftVScale->SetVisibleMin(rightVScale->GetVisibleMin());
				}
				if (rightVScale->AutoMaxMin() && rightVScale->GetVisibleMax() == 0 && rightVScale->GetVisibleMin() == 0)
				{
					rightVScale->SetVisibleMax(leftVScale->GetVisibleMax());
					rightVScale->SetVisibleMin(leftVScale->GetVisibleMin());
				}
            }
        }
    }

	void CChartMe::ChangeChart(ScrollType scrollType, int limitStep)
    {
        vector<CDivMe*> divsCopy = GetDivs();
        if (divsCopy.size() == 0 || m_dataSource->RowsCount() == 0)
        {
            return;
        }
        int fIndex = m_firstVisibleIndex;
        int lIndex = m_lastVisibleIndex;
        double axis = m_hScalePixel;
        bool flag = false;
        bool locateCrossHairFlag = false;
        switch (scrollType)
        {
            case ScrollType_Left:
                if (m_canScroll)
                {
                    flag = true;
                    if (m_showCrossLine)
                    {
                        if (limitStep > m_scrollStep)
                        {
                            ScrollCrossLineLeft(limitStep);
                        }
                        else
                        {
                            ScrollCrossLineLeft(m_scrollStep);
                        }
                        locateCrossHairFlag = true;
                    }
                    else
                    {
                        if (limitStep > m_scrollStep)
                        {
                            ScrollLeft(limitStep);
                        }
                        else
                        {
                            ScrollLeft(m_scrollStep);
                        }
                    }
                }
                break;
            case ScrollType_Right:
                if (m_canScroll)
                {
                    flag = true;
                    if (m_showCrossLine)
                    {
                        if (limitStep > m_scrollStep)
                        {
                            ScrollCrossLineRight(limitStep);
                        }
                        else
                        {
                            ScrollCrossLineRight(m_scrollStep);
                        }
                        locateCrossHairFlag = true;
                    }
                    else
                    {
                        if (limitStep > m_scrollStep)
                        {
                            ScrollRight(limitStep);
                        }
                        else
                        {
                            ScrollRight(m_scrollStep);
                        }
                    }
                }
                break;
            case ScrollType_ZoomIn:
                if (m_canZoom)
                {
                    flag = true;
                    ZoomIn();
                }
                break;
            case ScrollType_ZoomOut:
                if (m_canZoom)
                {
                    flag = true;
                    ZoomOut();
                }
                break;
        }
        if (flag)
        {
            int fIndex_after = m_firstVisibleIndex;
            int lIndex_after = m_lastVisibleIndex;
            double axis_after = m_hScalePixel;
            CorrectVisibleRecord(m_dataSource->RowsCount(), &m_firstVisibleIndex, &m_lastVisibleIndex);
            if (fIndex != fIndex_after || lIndex != lIndex_after)
            {
                Adjust();
            }
            ResetCrossOverIndex();
            if (locateCrossHairFlag)
            {
                LocateCrossLine();
            }
            if (fIndex == fIndex_after && lIndex == lIndex_after && axis == axis_after)
            {
				Invalidate();
            }
            else
            {
				Update();
				Invalidate();
            }
        }
        if (m_scrollAddSpeed && (scrollType == ScrollType_Left || scrollType == ScrollType_Right))
        {
            if (m_scrollStep < 50)
            {
                m_scrollStep += 5;
            }
        }
        else
        {
            m_scrollStep = 1;
        }
    }

	void CChartMe::CheckLastVisibleIndex()
    {
        if (m_lastVisibleIndex > m_dataSource->RowsCount() - 1)
        {
            m_lastVisibleIndex = m_dataSource->RowsCount() - 1;
        }
        if (m_dataSource->RowsCount() > 0)
        {
            m_lastVisibleKey = m_dataSource->GetXValue(m_lastVisibleIndex);
            if (m_lastVisibleIndex == m_dataSource->RowsCount() - 1)
            {
                m_lastRecordIsVisible = true;
            }
            else
            {
                m_lastRecordIsVisible = false;
            }
        }
        else
        {
            m_lastVisibleKey = 0;
            m_lastRecordIsVisible = true;
        }
	}

	void CChartMe::CheckToolTip()
    {
		SYSTEMTIME t; 
		GetLocalTime(&t); 
		double nowTime = CMathLibMe::M129(t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
		if (m_lastMouseMoveTime + m_tooltip_dely <= nowTime)
		{
			if (m_isMouseMove)
			{
				bool show = true;
				if (IsOperating())
				{
					show = false;
				}
				vector<CDivMe*> divsCopy = GetDivs();
				vector<CDivMe*>::iterator sIter = divsCopy.begin();
				for(;sIter != divsCopy.end();++sIter)
				{
					CDivMe *div = *sIter;
					if (div->GetSelectArea()->IsVisible())
					{
						show = false;
					}
				}
				if (show)
				{
					int curRecord = GetMouseOverIndex();
					CBaseShapeMe *bs = SelectShape(curRecord, 0);
					if (bs)
					{
						m_showingToolTip = true;
						Invalidate();
					}
				}
				m_isMouseMove = false;
			}
		}
    }

	void CChartMe::Clear()
    {
		ClearSelectedShape();
		ClearSelectedPlot();
        vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CPlotMe*> plotsCopy = div->GetPlots(SORTTYPE_NONE); 
			vector<CPlotMe*>::iterator sIter2 = plotsCopy.begin();
			for(; sIter2 != plotsCopy.end(); ++sIter2)
			{
				CPlotMe *plot = *sIter2;
				div->RemovePlot(plot);
				delete plot;
			}
        }
        CloseSelectArea();
        m_dataSource->Clear();
        m_firstVisibleIndex = -1;
        m_lastVisibleIndex = -1;
        m_lastRecordIsVisible = true;
        m_lastVisibleIndex = 0;
        m_lastVisibleKey = 0;
        m_showCrossLine = false;
    }

    void CChartMe::ClearSelectedShape()
    {
        vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *bs = *sIter2;
				bs->SetSelected(false);
			}
		}
		m_movingShape = 0;
	}

	void CChartMe::ClearSelectedPlot()
    {
        vector<CDivMe*> divsCopy = GetDivs();
	    vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CPlotMe*> plotsCopy = div->GetPlots(SORTTYPE_NONE);
			vector<CPlotMe*>::iterator sIter2 = plotsCopy.begin();
			for(; sIter2 != plotsCopy.end(); ++sIter2)
			{
				CPlotMe *plot = *sIter2;
                plot->SetSelected(false);
            }
         }
		m_movingPlot = 0;
    }

	void CChartMe::ClearSelectedDiv()
    {
	    vector<CDivMe*> divsCopy = GetDivs();
	    vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			div->SetSelected(false);
	    }
	}

	void CChartMe::CloseSelectArea()
	{
		vector<CDivMe*> divsCopy = GetDivs();
	    vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *cDiv = *sIter;
			cDiv->GetSelectArea()->Close();
		}
		m_showingSelectArea = false;
	}

	CDivMe* CChartMe::FindDiv(const POINT& mp)
    {
        vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *cDiv = *sIter;
            if (mp.y >= cDiv->GetTop() && mp.y <= cDiv->GetTop() + cDiv->GetHeight())
            {
                return cDiv;
            }
        }
        return 0;
    }

	CDivMe* CChartMe::FindDiv(CBaseShapeMe *shape)
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *div = *sIter;
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *bs = *sIter2;
				if(bs == shape)
				{
					return div;
				}
			}
		}
		return 0;
	}

	String CChartMe::GetControlType()
	{
		return L"Chart";
	}
	
	void CChartMe::GetHScaleDateString(double date, double lDate, DateType *dateType, wchar_t *str)
    {
		int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0, msecond = 0, lyear = 0, lmonth = 0, lday = 0, lhour = 0, lminute = 0, lsecond = 0, lmsecond = 0;	    
		CMathLibMe::M130(date, &year, &month, &day, &hour, &minute, &second, &msecond);
		CMathLibMe::M130(lDate, &lyear, &lmonth, &lday, &lhour, &lminute, &lsecond, &lmsecond);
        if (year > lyear)
        {
            *dateType = DateType_Year;
			_stprintf_s(str, 19, L"%d", year);
			return;
        }
        if (month > lmonth)
        {
            *dateType = DateType_Month;;
			_stprintf_s(str, 19, L"%d", month);
			return;
        }
        if (day > lday)
        {
            *dateType = DateType_Day;
 			_stprintf_s(str, 19, L"%d", day);
			return;
        }
        if (hour > lhour || minute > lminute)
        {
            *dateType = DateType_Minute;
			_stprintf_s(str, 19, L"%d:%02d", hour, minute);
			return;
        }
        if (second > lsecond)
        {
            *dateType = DateType_Second;;
			_stprintf_s(str, 19, L"%d", second);
			return;
        }
        if (msecond > lmsecond)
        {
            *dateType = DateType_Millisecond;
			_stprintf_s(str, 19, L"%d", msecond);
        }
    }

	int CChartMe::GetIndex(const POINT& mp)
	{
		int x = mp.x;
	    if (m_reverseHScale)
        {
            x = m_workingAreaWidth - (x - m_leftVScaleWidth) + m_leftVScaleWidth;
        }
        double pixel = m_hScalePixel;
		int index = GetChartIndex(x, m_leftVScaleWidth, pixel, m_firstVisibleIndex);
        if (index < 0)
        {
            index = 0;
        }
        if (index > m_lastVisibleIndex)
        {
            index = m_lastVisibleIndex;
        }
        return index;
	}

	int CChartMe::GetMaxVisibleCount(double hScalePixel, int pureH)
	{
		return (int)(pureH / hScalePixel);
	}

	CDivMe* CChartMe::GetMouseOverDiv()
	{
		POINT mp = GetMousePoint();
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *cDiv = *sIter;
			if (mp.y >= cDiv->GetTop() && mp.y <= cDiv->GetTop() + cDiv->GetHeight())
            {
                return cDiv;
            }
		}
		return 0;
	}

	int CChartMe::GetMouseOverIndex()
	{
	    POINT mp = GetMousePoint();
        if (m_reverseHScale)
        {
            mp.x = m_workingAreaWidth - (mp.x - m_leftVScaleWidth) + m_leftVScaleWidth;
        }
        double pixel = m_hScalePixel;
		return GetChartIndex(mp.x, m_leftVScaleWidth, pixel, m_firstVisibleIndex);
	}

	double CChartMe::GetNumberValue(CDivMe *div,const POINT& mp,AttachVScale attachVScale)
	{
		CVScaleMe *vScale = div->GetVScale(attachVScale);
		CVScaleMe *leftVScale = div->GetLeftVScale();
		CVScaleMe *rightVScale = div->GetRightVScale();
        int vHeight = div->GetWorkingAreaHeight() - vScale->GetPaddingTop() - vScale->GetPaddingBottom();
        int cY = mp.y - div->GetTop() - div->GetTitleBar()->GetHeight() - vScale->GetPaddingTop();
        if (vScale->IsReverse())
        {
            cY = vHeight - cY;
        }
        if (vHeight > 0)
        {
            double max = 0;
            double min = 0;
            bool isLog = false;
            if (attachVScale == AttachVScale_Left)
            {
                max = leftVScale->GetVisibleMax();
                min = leftVScale->GetVisibleMin();
                if (max == 0 && min == 0)
                {
                    max = rightVScale->GetVisibleMax();
                    min = rightVScale->GetVisibleMin();
                }
                isLog = leftVScale->GetSystem() == VScaleSystem_Logarithmic;
            }
            else if (attachVScale == AttachVScale_Right)
            {
                max = rightVScale->GetVisibleMax();
                min = rightVScale->GetVisibleMin();
                if (max == 0 && min == 0)
                {
                    max = leftVScale->GetVisibleMax();
                    min = leftVScale->GetVisibleMin();
                }
                isLog = rightVScale->GetSystem() == VScaleSystem_Logarithmic;
            }
            if (isLog)
            {
                if (max >= 0)
                {
                    max = log10(max);
                }
                else
                {
                    max = -log10(abs(max));
                }
                if (min >= 0)
                {
                    min = log10(min);
                }
                else
                {
                    min = -log10(abs(min));
                }
				double value  = GetVScaleValue(cY, max, min, (float)vHeight);
				return pow(10, value);
            }
            else
            {
				return GetVScaleValue(cY, max, min, (float)vHeight);
            }
        }
        return 0;
	}

	void CChartMe::GetProperty(const String& name, String *value, String *type)
	{
		if(name == L"autofillhscale")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(AutoFillHScale());
		}
		else if(name == L"blankspace")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetBlankSpace());
		}
		else if(name == L"canmoveshape")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanMoveShape());
		}
		else if(name == L"canresizeh")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanResizeH());
		}
		else if(name == L"canresizev")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanResizeV());
		}
		else if(name == L"canscroll")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanScroll());
		}
		else if(name == L"canzoom")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(CanZoom());
		}
		else if(name == L"crosslinemovemode")
		{
			*type = L"enum:CrossLineMoveMode";
			CrossLineMoveMode crossLineMoveMode = GetCrossLineMoveMode();
			if(crossLineMoveMode == CrossLineMoveMode_AfterClick)
			{
				*value = L"AfterClick";
			}
			else
			{
				*value = L"FollowMouse";
			}
		}
		else if(name == L"hscalefieldtext")
		{
			*type = L"text";
			*value = GetHScaleFieldText();
		}
		else if(name == L"hscalepixel")
		{
			*type = L"double";
			*value = CStrMe::ConvertDoubleToStr(GetHScalePixel());
		}
		else if(name == L"leftvscalewidth")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetLeftVScaleWidth());
		}
		else if(name == L"reversehscale")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(IsReverseHScale());
		}
		else if(name == L"rightvscalewidth")
		{
			*type = L"int";
			*value = CStrMe::ConvertIntToStr(GetRightVScaleWidth());
		}
		else if(name == L"scrolladdspeed")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(IsScrollAddSpeed());
		}
		else if(name == L"showcrossline")
		{
			*type = L"bool";
			*value = CStrMe::ConvertBoolToStr(IsShowCrossLine());
		}
		else
		{
			CControlMe::GetProperty(name, value, type);
		}
	}

	vector<String> CChartMe::GetPropertyNames()
	{
		vector<String> propertyNames = CControlMe::GetPropertyNames();
		propertyNames.push_back(L"AutoFillHScale");
		propertyNames.push_back(L"BlankSpace");
		propertyNames.push_back(L"CanMoveShape");
		propertyNames.push_back(L"CanResizeH");
		propertyNames.push_back(L"CanResizeV");
		propertyNames.push_back(L"CanScroll");
		propertyNames.push_back(L"CanZoom");
		propertyNames.push_back(L"CrossLineMoveMode");
		propertyNames.push_back(L"HScaleFieldText");
		propertyNames.push_back(L"HScalePixel");
		propertyNames.push_back(L"LeftVScaleWidth");
		propertyNames.push_back(L"ReverseHScale");
		propertyNames.push_back(L"RightVScaleWidth");
		propertyNames.push_back(L"ScrollAddSpeed");
		propertyNames.push_back(L"ShowCrossLine");
		return propertyNames;
	}

	int CChartMe::GetShapesCount(int field)
	{
		int count=0;
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
        {
			CDivMe *cDiv = *sIter;
			vector<CBaseShapeMe*> shapesCopy = cDiv->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *shape = *sIter2;
				int length = 0;
				int *fields = shape->GetFields(&length);
				for(int f = 0; f < length; f++)
				{
					if(fields[f] == field)
					{
						count++;
						break;
					}
				}
				if(fields)
				{
					delete[] fields;
					fields = 0;
				}
			}
		}
		return count;
	}

	float CChartMe::GetX(int index)
	{
	    float x = 0;
        x = (float)(m_leftVScaleWidth + (index - m_firstVisibleIndex) * m_hScalePixel + m_hScalePixel / 2 + 1);
        if (m_reverseHScale)
        {
            return m_workingAreaWidth - (x - m_leftVScaleWidth) + m_leftVScaleWidth + m_blankSpace;
        }
        else
        {
            return x;
        }
	}

	float CChartMe::GetY(CDivMe *div, double value, AttachVScale attach)
	{
		if (div)
        {
            CVScaleMe *scale = div->GetVScale(attach);
            double max = scale->GetVisibleMax();
            double min = scale->GetVisibleMin();
            if (scale->GetSystem() == VScaleSystem_Logarithmic)
            {
                if (value > 0)
                {
                    value = log10(value);
                }
                else if(value < 0)
                {
                    value = -log10(abs(value));
                }
                if (max > 0)
                {
                    max = log10(max);
                }
                else if(max < 0)
                {
                    max = -log10(abs(max));
                }
                if (min > 0)
                {
                    min = log10(min);
                }
                else if(min < 0)
                {
                    min = -log10(abs(min));
                }
            }
            if (max != min)
            {
                int wHeight = div->GetWorkingAreaHeight() - scale->GetPaddingTop() - scale->GetPaddingBottom();
				CTitleBarMe *titleBar = div->GetTitleBar();
                if (wHeight > 0)
                {
					float y = (float)((max - value) / (max - min) * wHeight);
                    if (scale->IsReverse())
                    {

						return titleBar->GetHeight() + div->GetWorkingAreaHeight() - scale->GetPaddingBottom() - y;
                    }
                    else
                    {
						return titleBar->GetHeight() + scale->GetPaddingTop() + y;
                    }
                }
            }
        }
        return 0;
	}

	int CChartMe::GetVScaleBaseField(CDivMe *div, CVScaleMe *vScale)
	{
		int baseField = vScale->GetBaseField();
		if (baseField == CTableMe::NULLFIELD() && vScale->GetForeColor2() == COLOR_EMPTY)
		{
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_DESC);
			vector<CBaseShapeMe*>::iterator sIter = shapesCopy.begin();
			for(; sIter != shapesCopy.end(); ++sIter)
			{
				CBaseShapeMe *shape = *sIter;
				baseField = shape->GetBaseField();
				break;
			}
		}
		return baseField;
	}

	double CChartMe::GetVScaleBaseValue(CDivMe *div, CVScaleMe *vScale, int i)
	{
		double baseValue = 0;
		int baseField = GetVScaleBaseField(div, vScale);
        if (baseField != CTableMe::NULLFIELD() && m_dataSource->RowsCount() > 0)
        {
            if (i >= m_firstVisibleIndex && i <= m_lastVisibleIndex)
            {
                double value = m_dataSource->Get2(i, baseField);
				if (!m_dataSource->IsNaN(value))
                {
                    baseValue = value;
                }
            }
        }
		else
		{
			baseValue = vScale->GetMidValue();
		}
        return baseValue;
	}

	bool CChartMe::IsOperating()
	{
	    if (m_movingPlot || m_movingShape
        || m_hResizeType != 0 || m_userResizeDiv)
        {
            return true;
        }
        return false;
	}

	void CChartMe::LocateCrossLine()
	{
		if (m_dataSource->RowsCount() > 0)
        {
            vector<CDivMe*> divsCopy = GetDivs();
			vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *div = *sIter;
                if (m_cross_y >= div->GetTop() && m_cross_y <= div->GetTop() + div->GetHeight())
                {
                    if (div->GetWorkingAreaHeight() > 0 && m_crossStopIndex >= 0 && m_crossStopIndex < m_dataSource->RowsCount())
                    {
						vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_DESC);
                        vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
						for(; sIter2 != shapesCopy.end(); ++sIter2)
						{
							CBaseShapeMe *tls = *sIter2;
                            if (tls->IsVisible())
                            {
                                double value = m_dataSource->Get2(m_crossStopIndex, tls->GetBaseField());
                                if (!m_dataSource->IsNaN(value))
                                {
                                    m_cross_y = (int)GetY(div, value, tls->GetAttachVScale()) + div->GetTop();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
	}

	void CChartMe::MoveShape(CDivMe* cDiv, CBaseShapeMe *shape)
	{
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
		{
			CDivMe *div = *sIter;
			div->RemoveShape(shape);
		}
		if(cDiv)
		{
			cDiv->AddShape(shape);
		}
	}

	double CChartMe::DivMaxOrMin(int index, CDivMe *div, int flag)
    {
		if (index < 0)
        {
            return 0;
        }
        if (div)
        {
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_NONE);
			vector<CBaseShapeMe*>::iterator sIter = shapesCopy.begin();
			double max = 0, min = 0;
			bool isEmpty = true;
			for(; sIter != shapesCopy.end(); ++sIter)
            {
				CBaseShapeMe *bs = *sIter;
                if (!bs->IsVisible())
                {
                    continue;
                }
				int fieldsLength = 0;
                int *fields = bs->GetFields(&fieldsLength);
                for (int i = 0; i < fieldsLength; i++)
                {
                    double value = m_dataSource->Get2(index, fields[i]);
                    if (!m_dataSource->IsNaN(value))
                    {
						if(isEmpty)
						{
							max = value;
							min = value;
							isEmpty = false;
						}
						else
						{
							if(flag == 0 && max < value)
							{
								max = value;
							}
							if(flag == 1 && min > value)
							{
								min = value;
							}
						}
                    }
                }
				if(fields)
				{
					delete fields;
					fields = 0;
				}
            }
            if (flag == 0)
            {
                return max;
            }
            else
            {
                return min;
            }
        }
        return 0;
    }

	int CChartMe::GetDateType(DateType dateType)
	{
		switch(dateType)
		{
		case DateType_Year:
			return 0;
		case DateType_Month:
			return 1;
		case DateType_Day:
			return 2;
		case DateType_Hour:
			return 3;
		case DateType_Minute:
			return 4;
		case DateType_Second:
			return 5;
		case DateType_Millisecond:
			return 6;
		}
		return 3;
	}

	DateType CChartMe::GetDateType(int dateType)
	{
		switch(dateType)
		{
		case 0:
			return DateType_Year;
		case 1:
			return DateType_Month;
		case 2:
			return DateType_Day;
		case 3:
			return DateType_Hour;
		case 4:
			return DateType_Minute;
		case 5:
			return DateType_Second;
		case 6:
			return DateType_Millisecond;
		}
		return DateType_Day;
	}

	vector<CDivMe*> CChartMe::GetDivs()
	{
		vector<CDivMe*> list;
		if(m_divs.size() > 0)
		{
			copy(m_divs.begin(), m_divs.end(), back_inserter(list));
		}
		return list;
	}

	void CChartMe::ResetCrossOverIndex()
    {
        if (m_showCrossLine)
        {
            m_crossStopIndex = ResetCrossOverIndex(m_dataSource->RowsCount(), m_maxVisibleRecord,
                m_crossStopIndex, m_firstVisibleIndex, m_lastVisibleIndex);
        }
        m_isScrollCross = true;
    }

	void CChartMe::RemoveAll()
	{
		Clear();
		ClearSelectedDiv();
        vector<CDivMe*>::iterator sIter = m_divs.begin();
		for(; sIter != m_divs.end(); ++sIter)
		{
			CDivMe *div = *sIter;
			delete div;
		}
		m_divs.clear();
        m_dataSource->Clear();
        m_cross_y = -1;
        m_showingToolTip = false;
	}

	bool CChartMe::ResizeDiv()
	{
		int width = GetWidth(), height = GetHeight();
        if (m_hResizeType > 0)
        {
            POINT mp = GetMousePoint();
            if (m_hResizeType == 1)
            {
                if (mp.x > 0 && mp.x < width - m_rightVScaleWidth - 50)
                {
                    m_leftVScaleWidth = mp.x;
                }
            }
            else if (m_hResizeType == 2)
            {
                if (mp.x > m_leftVScaleWidth + 50 && mp.x < width)
                {
                    m_rightVScaleWidth = width - mp.x;
                }
            }
            m_hResizeType = 0;
            Update();
            return true;
        }
        if (m_userResizeDiv)
        {
            POINT mp = GetMousePoint();
            CDivMe *nextCP = 0;
            bool rightP = false;
			vector<CDivMe*> divsCopy = GetDivs();
			vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *cDiv = *sIter;
                if (rightP)
                {
                    nextCP = cDiv;
                    break;
                }
                if (cDiv == m_userResizeDiv)
                {
                    rightP = true;
                }
            }
            int sumPercent = 0;
            sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *div = *sIter;
                sumPercent += div->GetVerticalPercent();
            }
            int originalVP = m_userResizeDiv->GetVerticalPercent();
			RECT uRect = m_userResizeDiv->GetBounds();
            if (mp.x >= uRect.left && mp.x <= uRect.right && mp.y >= uRect.top && mp.y <= uRect.bottom)
            {
                m_userResizeDiv->SetVerticalPercent(sumPercent * (mp.y - m_userResizeDiv->GetTop()) / height);
                if (m_userResizeDiv->GetVerticalPercent() < 1)
                {
                    m_userResizeDiv->SetVerticalPercent(1);
                }
                if (nextCP)
                {
					nextCP->SetVerticalPercent(nextCP->GetVerticalPercent()+originalVP - m_userResizeDiv->GetVerticalPercent());
                }
            }
            else
            {
				if(nextCP)
				{
					RECT nRect = nextCP->GetBounds();
					if (nextCP && mp.x >= nRect.left && mp.x <= nRect.right && mp.y >= nRect.top && mp.y <= nRect.bottom)
					{
						m_userResizeDiv->SetVerticalPercent(sumPercent * (mp.y - m_userResizeDiv->GetTop()) / height);
						if (m_userResizeDiv->GetVerticalPercent() >= originalVP + nextCP->GetVerticalPercent())
						{
							m_userResizeDiv->SetVerticalPercent(m_userResizeDiv->GetVerticalPercent()-1);
						}
						nextCP->SetVerticalPercent(originalVP + nextCP->GetVerticalPercent() - m_userResizeDiv->GetVerticalPercent());
					}
				}
            }
            m_userResizeDiv = 0;
            Update();
            return true;
        }
        return false;
	}

	void CChartMe::RemoveDiv(CDivMe *div)
    {
	    vector<CDivMe*>::iterator sIter = m_divs.begin();
		for(; sIter != m_divs.end(); ++sIter)
        {
			CDivMe *cDiv = *sIter;
			if(cDiv == div)
			{
				m_divs.erase(sIter);
				break;
			}
	    }
        Update();
    }

	void CChartMe::Reset()
	{
		if(IsVisible())
		{
			ResetVisibleRecord();
			Adjust();
			ResetCrossOverIndex();
		}
	}

	void CChartMe::ResetVisibleRecord()
    {
		vector<CDivMe*> divs = GetDivs();
        if (divs.size() > 0)
        {
			int rowsCount = m_dataSource->RowsCount();
            if (m_autoFillHScale)
            {
                if (m_workingAreaWidth > 0 && rowsCount > 0)
                {
                    m_hScalePixel = (double)m_workingAreaWidth / rowsCount;
                    m_maxVisibleRecord = rowsCount;
                    m_firstVisibleIndex = 0;
                    m_lastVisibleIndex = rowsCount - 1;
                }
            }
			else
			{
				m_maxVisibleRecord = GetMaxVisibleCount(m_hScalePixel, m_workingAreaWidth);
				if (rowsCount == 0)
				{
					m_firstVisibleIndex = -1;
					m_lastVisibleIndex = -1;
				}
				else
				{
					if (rowsCount < m_maxVisibleRecord)
					{
						m_lastVisibleIndex = rowsCount - 1;
						m_firstVisibleIndex = 0;
					}
					else
					{
						if (m_firstVisibleIndex != -1 && m_lastVisibleIndex != -1 && !m_lastRecordIsVisible)
						{
							int index = m_dataSource->GetRowIndex(m_lastVisibleKey);
							if (index != -1)
							{
								m_lastVisibleIndex = index;
							}
							m_firstVisibleIndex = m_lastVisibleIndex - m_maxVisibleRecord + 1;
							if (m_firstVisibleIndex < 0)
							{
								m_firstVisibleIndex = 0;
								m_lastVisibleIndex = m_firstVisibleIndex + m_maxVisibleRecord;
								CheckLastVisibleIndex();
							}
						}
						else
						{
							m_lastVisibleIndex = rowsCount - 1;
							m_firstVisibleIndex = m_lastVisibleIndex - m_maxVisibleRecord + 1;
							if (m_firstVisibleIndex > m_lastVisibleIndex)
							{
								m_firstVisibleIndex = m_lastVisibleIndex;
							}
						}
					}
				}
			}
        }
    }

	void CChartMe::ScrollLeft(int step)
	{
		if(!m_autoFillHScale)
		{
			ScrollLeft(step, m_dataSource->RowsCount(), m_hScalePixel, m_workingAreaWidth,
				&m_firstVisibleIndex, &m_lastVisibleIndex);
			CheckLastVisibleIndex();
		}
	}

	void CChartMe::ScrollLeftToBegin()
	{
		if (!m_autoFillHScale && m_dataSource->RowsCount() > 0)
        {
            m_firstVisibleIndex = 0;
            m_lastVisibleIndex = m_maxVisibleRecord - 1;
            CheckLastVisibleIndex();
            m_crossStopIndex = m_firstVisibleIndex;
        }
	}

	void CChartMe::ScrollRight(int step)
	{
		if(!m_autoFillHScale)
		{
			ScrollRight(step, m_dataSource->RowsCount(), m_hScalePixel, m_workingAreaWidth,
				&m_firstVisibleIndex, &m_lastVisibleIndex);
			CheckLastVisibleIndex();
		}
	}

	void CChartMe::ScrollRightToEnd()
	{
	    if (!m_autoFillHScale && m_dataSource->RowsCount() > 0)
        {
            m_lastVisibleIndex = m_dataSource->RowsCount() - 1;
            CheckLastVisibleIndex();
            m_firstVisibleIndex = m_lastVisibleIndex - m_maxVisibleRecord + 1;
            if (m_firstVisibleIndex < 0)
            {
                m_firstVisibleIndex = 0;
            }
            m_crossStopIndex = m_lastVisibleIndex;
        }
	}

	void CChartMe::ScrollCrossLineLeft(int step)
    {
        int currentIndex = m_crossStopIndex;
        m_crossStopIndex = currentIndex - step;
        if (m_crossStopIndex < 0)
        {
            m_crossStopIndex = 0;
        }
        if (currentIndex <= m_firstVisibleIndex)
        {
            ScrollLeft(step);
        }
    }

	void CChartMe::ScrollCrossLineRight(int step)
    {
        int currentIndex = m_crossStopIndex;
        m_crossStopIndex = currentIndex + step;
        if (m_dataSource->RowsCount() < m_maxVisibleRecord)
        {
            if (m_crossStopIndex >= m_maxVisibleRecord - 1)
            {
                m_crossStopIndex = m_maxVisibleRecord - 1;
            }
        }
        if (currentIndex >= m_lastVisibleIndex)
        {
            ScrollRight(step);
        }
    }

	CBaseShapeMe* CChartMe::SelectShape(int curIndex, int state)
    {
        CBaseShapeMe *selectObj = 0;
		POINT mp = GetMousePoint();
        vector<CDivMe*> divsCopy = GetDivs();
        vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
    	{
			CDivMe *div = *sIter;
			vector<CBaseShapeMe*> shapesCopy = div->GetShapes(SORTTYPE_DESC);
			vector<CBaseShapeMe*>::iterator sIter2 = shapesCopy.begin();
			for(; sIter2 != shapesCopy.end(); ++sIter2)
			{
				CBaseShapeMe *bShape = *sIter2;
				if(bShape->IsVisible())
				{
					if (selectObj)
					{
						if (state == 1)
						{
							bShape->SetSelected(false);
						}
					}
					else
					{
						if (m_firstVisibleIndex == -1 || m_lastVisibleIndex == -1)
						{
							if (state == 1)
							{
								bShape->SetSelected(false);
							}
							continue;
						}
						bool isSelect = false;
						CPolylineShapeMe *tls = dynamic_cast<CPolylineShapeMe*>(bShape);
						CCandleShapeMe *cs = dynamic_cast<CCandleShapeMe*>(bShape);
						CBarShapeMe *barS = dynamic_cast<CBarShapeMe*>(bShape);
						if (tls)
						{
							isSelect = SelectPolyline(div, mp, tls->GetBaseField(), tls->GetWidth(), tls->GetAttachVScale(), curIndex);
						}
						else if (cs)
						{
							if (cs->GetStyle() == CandleStyle_CloseLine)
							{
								isSelect = SelectPolyline(div, mp, cs->GetCloseField(), 1, cs->GetAttachVScale(), curIndex);
							}
							else
							{
								isSelect = SelectCandle(div, (float)mp.y, cs->GetHighField(), cs->GetLowField(), cs->GetStyleField(), cs->GetAttachVScale(), curIndex);
							}
						}
						else if (barS)
						{
							isSelect = SelectBar(div, (float)mp.y, barS->GetFieldName(), barS->GetFieldName2(), barS->GetStyleField(), barS->GetAttachVScale(), curIndex);
						}
						if (isSelect)
						{
							selectObj = bShape;
							if (state == 1)
							{
								bShape->SetSelected(true);
							}
						}
						else
						{
							if (state == 1)
							{
								bShape->SetSelected(false);
							}
						}
					}
				}
            }
        }
        return selectObj;
    }

	bool CChartMe::SelectBar(CDivMe *div, float mpY, int fieldName, int fieldName2, int styleField, AttachVScale attachVScale, int curIndex)
    {
		int style = 1;
		if (styleField != CTableMe::NULLFIELD())
        {
            double defineStyle = m_dataSource->Get2(curIndex, styleField);
            if (!m_dataSource->IsNaN(defineStyle))
            {
                style = (int)defineStyle;
            }
        }
        if (style == -10000 || curIndex < 0 || curIndex > m_lastVisibleIndex || m_dataSource->IsNaN(m_dataSource->Get2(curIndex, fieldName)))
        {
            return false;
        }
		double midValue = 0;
		if(fieldName2 != CTableMe::NULLFIELD())
		{
			midValue = m_dataSource->Get2(curIndex, fieldName2);
		}
        double volumn = m_dataSource->Get2(curIndex, fieldName);
        float y = GetY(div, volumn, attachVScale);
        float midY = GetY(div, midValue, attachVScale);
		int divTop = div->GetTop();
        float topY = y + divTop;
        float bottomY = midY + divTop;
        if (topY > bottomY)
        {
            topY = midY + divTop;
            bottomY = y + divTop;
        }
        topY -= 1;
        bottomY += 1;
        if (topY >= divTop && bottomY <= divTop + div->GetHeight()
            && mpY >= topY && mpY <= bottomY)
        {
            return true;
        }
        return false;
    }

	bool CChartMe::SelectCandle(CDivMe *div, float mpY, int highField, int lowField, int styleField, AttachVScale attachVScale, int curIndex)
    {
		int style = 1;
		if (styleField != CTableMe::NULLFIELD())
        {
            double defineStyle = m_dataSource->Get2(curIndex, styleField);
            if (!m_dataSource->IsNaN(defineStyle))
            {
                style = (int)defineStyle;
            }
        }
        double highValue = 0;
        double lowValue = 0;
        if (style == -10000 || curIndex < 0 || curIndex > m_lastVisibleIndex)
        {
            return false;
        }
        else
        {
            highValue = m_dataSource->Get2(curIndex, highField);
            lowValue = m_dataSource->Get2(curIndex, lowField);
            if (m_dataSource->IsNaN(highValue) || m_dataSource->IsNaN(lowValue))
            {
                return false;
            }
        }
        float highY = GetY(div, highValue, attachVScale);
        float lowY = GetY(div, lowValue, attachVScale);
		int divTop = div->GetTop();
        float topY = highY + divTop;
        float bottomY = lowY + divTop;
        if (topY > bottomY)
        {
            float temp = topY;
            topY = bottomY;
            bottomY = temp;
        }
        topY -= 1;
        bottomY += 1;
        if (topY >= divTop && bottomY <= divTop + div->GetHeight()
            && mpY >= topY && mpY <= bottomY)
        {
            return true;
        }
        return false;
    }

	bool CChartMe::SelectPolyline(CDivMe *div, const POINT& mp, int fieldName, float lineWidth, AttachVScale attachVScale, int curIndex)
    {
        if (curIndex < 0 || curIndex > m_lastVisibleIndex || (m_dataSource->IsNaN(m_dataSource->Get2(curIndex, fieldName))))
        {
            return false;
        }
        double lineValue = m_dataSource->Get2(curIndex, fieldName);
        float topY = GetY(div, lineValue, attachVScale) + div->GetTop();
        if (m_hScalePixel <= 1)
        {
            if (topY >= div->GetTop() && topY <= div->GetTop() + div->GetHeight()
            && mp.y >= topY - 8 && mp.y <= topY + 8)
            {
                return true;
            }
        }
        else
        {
            int index = curIndex;
			float scaleX = GetX(index);
            float judgeTop = 0;
            float judgeScaleX = scaleX;
            if (mp.x >= scaleX)
            {
                int leftIndex = curIndex + 1;
                if (curIndex < m_lastVisibleIndex && (!m_dataSource->IsNaN(m_dataSource->Get2(leftIndex, fieldName))))
                {
                    double rightValue = m_dataSource->Get2(leftIndex, fieldName);
                    judgeTop = GetY(div, rightValue, attachVScale) + div->GetTop();
                    if (judgeTop > div->GetTop() + div->GetHeight() - div->GetHScale()->GetHeight() || judgeTop < div->GetTop() + div->GetTitleBar()->GetHeight())
                    {
                        return false;
                    }
                }
                else
                {
                    judgeTop = topY;
                }
            }
            else
            {
                judgeScaleX = scaleX - (int)m_hScalePixel;
                int rightIndex = curIndex - 1;
                if (curIndex > 0 && (!m_dataSource->IsNaN(m_dataSource->Get2(rightIndex, fieldName))))
                {
                    double leftValue = m_dataSource->Get2(rightIndex, fieldName);
                    judgeTop = GetY(div, leftValue, attachVScale) + div->GetTop();
                    if (judgeTop > div->GetTop() + div->GetHeight() - div->GetHScale()->GetHeight() || judgeTop < div->GetTop() + div->GetTitleBar()->GetHeight())
                    {
                        return false;
                    }
                }
                else
                {
                    judgeTop = topY;
                }
            }
			float judgeX = 0, judgeY = 0, judgeW = 0, judgeH = 0;
            if (judgeTop >= topY)
            {
				judgeX = judgeScaleX;
				judgeY = topY - 2 - lineWidth;
				judgeW = (float)m_hScalePixel;
				judgeH = judgeTop - topY + lineWidth < 4 ? 4 : judgeTop - topY + 4 + lineWidth;
            }
            else
            {
				judgeX = judgeScaleX;
				judgeY = judgeTop - 2 - lineWidth / 2;
				judgeW = (float)m_hScalePixel;
				judgeH = topY - judgeTop + lineWidth < 4 ? 4 : topY - judgeTop + 4 + lineWidth;
            }
            if (mp.x >= judgeX && mp.x <= judgeX + judgeW && mp.y >= judgeY && mp.y <= judgeY + judgeH)
            {
                return true;
            }
        }
        return false;
    }

	void CChartMe::SetProperty(const String& name, const String& value)
	{
		if(name == L"autofillhscale")
		{
			SetAutoFillHScale(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"blankspace")
		{
			SetBlankSpace(CStrMe::ConvertStrToInt(value));
		}
		else if(name == L"canmoveshape")
		{
			SetCanMoveShape(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"canresizeh")
		{
			SetCanResizeH(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"canresizev")
		{
			SetCanResizeV(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"canscroll")
		{
			SetCanScroll(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"canzoom")
		{
			SetCanZoom(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"crosslinemovemode")
		{
			String lowerStr = CStrMe::ToLower(value);
			if(lowerStr == L"afterclick")
			{
				SetCrossLineMoveMode(CrossLineMoveMode_AfterClick);
			}
			else
			{
				SetCrossLineMoveMode(CrossLineMoveMode_FollowMouse);
			}
		}
		else if(name == L"hscalefieldtext")
		{
			SetHScaleFieldText(value);
		}
		else if(name == L"hscalepixel")
		{
			SetHScalePixel(CStrMe::ConvertStrToDouble(value));
		}
		else if(name == L"leftvscalewidth")
		{
			SetLeftVScaleWidth(CStrMe::ConvertStrToInt(value));
		}
		else if(name == L"reversehscale")
		{
			SetReverseHScale(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"rightvscalewidth")
		{
			SetRightVScaleWidth(CStrMe::ConvertStrToInt(value));
		}
		else if(name == L"scrolladdspeed")
		{
			SetScrollAddSpeed(CStrMe::ConvertStrToBool(value));
		}
		else if(name == L"showcrossline")
		{
			SetShowCrossLine(CStrMe::ConvertStrToBool(value));
		}
		else
		{
			CControlMe::SetProperty(name, value);
		}
	}
	
	void CChartMe::SetVisibleIndex(int firstVisibleIndex, int lastVisibleIndex)
	{
		double xScalePixel = m_workingAreaWidth / (m_lastVisibleIndex - m_firstVisibleIndex + 1);
        if (xScalePixel < 30)
        {
            m_firstVisibleIndex = firstVisibleIndex;
            m_lastVisibleIndex = lastVisibleIndex;
            if (m_lastVisibleIndex != m_dataSource->RowsCount() - 1)
            {
                m_lastRecordIsVisible = false;
            }
            else
            {
                m_lastRecordIsVisible = true;
            }
			SetHScalePixel(xScalePixel);
            m_maxVisibleRecord = GetMaxVisibleCount(m_hScalePixel, m_workingAreaWidth);
            CheckLastVisibleIndex();
        }
	}

	void CChartMe::ZoomIn()
	{
		if(!m_autoFillHScale)
		{
			double hp = m_hScalePixel;
			ZoomIn(m_workingAreaWidth, m_dataSource->RowsCount(), &m_firstVisibleIndex, &m_lastVisibleIndex, &hp);
			SetHScalePixel(hp);
			m_maxVisibleRecord = GetMaxVisibleCount(m_hScalePixel, m_workingAreaWidth);
			CheckLastVisibleIndex();
		}
	}

	void CChartMe::ZoomOut()
	{
		if(!m_autoFillHScale)
		{
			double hp = m_hScalePixel;
			ZoomOut(m_workingAreaWidth, m_dataSource->RowsCount(), &m_firstVisibleIndex, &m_lastVisibleIndex, &hp);
			SetHScalePixel(hp);
			m_maxVisibleRecord = GetMaxVisibleCount(m_hScalePixel, m_workingAreaWidth);
			CheckLastVisibleIndex();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CChartMe::DrawThinLine(CPaintMe *paint, _int64 dwPenColor, int width, int x1, int y1, int x2, int y2)
	{
		if(width > 1 || GetNative()->AllowScaleSize())
		{
			paint->DrawLine(dwPenColor, (float)width, 0, x1, y1, x2, y2);
		}
		else
		{
			int left = x1 < x2 ? x1 : x2;
			int top = y1 < y2 ? y1 : y2;
			int w = abs(x1 - x2);
			int h = abs(y1 - y2);
			if (w < 1) w = 1;
			if (h < 1) h = 1;
			if ((w > 1 && h == 1) || (w == 1 && h > 1))
            {
				RECT rect = {left, top, left + w, top + h};
				paint->FillRect(dwPenColor, rect);
            }
            else
            {
				paint->DrawLine(dwPenColor, (float)width, 0, x1, y1, x2, y2);
            }
		}
	}

	void CChartMe::DrawText(CPaintMe *paint, LPCWSTR strText, _int64 dwPenColor, FONT *font, int left, int top)
	{
		SIZE textSize = paint->TextSize(strText, font);
		RECT rect = {left, top, left + textSize.cx, top + textSize.cy};
		paint->DrawText(strText, dwPenColor, font, rect);
	}
	
	vector<double> CChartMe::GetVScaleStep(double max, double min, CDivMe *div, CVScaleMe *vScale)
    {
        vector<double> scaleStepList;
        if (vScale->GetType() == VScaleType_EqualDiff || vScale->GetType() == VScaleType_Percent)
        {
			double step = 0;
			int distance = div->GetVGrid()->GetDistance();
            int digit = 0, gN = div->GetWorkingAreaHeight() / distance;
            if (gN == 0)
            {
                gN = 1;
            }
			CMathLibMe::M012(min, max, div->GetWorkingAreaHeight(), distance, distance / 2, gN, &step, &digit);
            if (step > 0)
            {
                double start = 0;
                if (min >= 0)
                {
                    while (start + step < min)
                    {
                        start += step;
                    }
                }
                else
                {
                    while (start - step > min)
                    {
                        start -= step;
                    }
                }
                while (start <= max)
                {
                    scaleStepList.push_back(start);
                    start += step;
                }
            }
        }
        else if (vScale->GetType() == VScaleType_EqualRatio)
        {
            int baseField = GetVScaleBaseField(div, vScale);
            double bMax = 0;
            double bMin = 0;
			bool isNullBMax = true,isNullBMin = true;
            if (baseField != CTableMe::NULLFIELD())
            {
                for (int i = 0; i < m_dataSource->RowsCount(); i++)
                {
                    double value = m_dataSource->Get2(i, baseField);
                    if (!m_dataSource->IsNaN(value))
                    {
						 if(isNullBMax)
						{
							bMax = value;
							isNullBMax = false;
						}
                        else if (value > bMax)
                        {
                            bMax = value;
                        }
						if(isNullBMin)
						{
							bMin = value;
							isNullBMin = false;
						}
                        else if (value < bMin)
                        {
                            bMin = value;
                        }
                    }
                }
                if (!isNullBMax && !isNullBMin && bMin > 0 && bMax > 0 && bMin < bMax)
                {
                    double num = bMin;
                    while (num < bMax)
                    {
                        num = num * 1.1;
                        if (num >= min && num <= max)
                        {
                            scaleStepList.push_back(num);
                        }
                    }
                }
            }
        }
        else if (vScale->GetType() == VScaleType_Divide)
        {
            scaleStepList.push_back(min + (max - min) * 0.25);
            scaleStepList.push_back(min + (max - min) * 0.5);
            scaleStepList.push_back(min + (max - min) * 0.75);
        }
        else if (vScale->GetType() == VScaleType_GoldenRatio)
        {
            scaleStepList.push_back(min);
            scaleStepList.push_back(min + (max - min) * 0.191);
            scaleStepList.push_back(min + (max - min) * 0.382);
            scaleStepList.push_back(min + (max - min) * 0.5);
            scaleStepList.push_back(min + (max - min) * 0.618);
            scaleStepList.push_back(min + (max - min) * 0.809);
        }
        if ((max != min) && scaleStepList.size() == 0)
        {
	    if (!m_dataSource->IsNaN(min))
	    {
            	scaleStepList.push_back(min);
            }
        }
        return scaleStepList;
    }

	void CChartMe::OnPaintBar(CPaintMe *paint, CDivMe *div, CBarShapeMe *bs)
	{
		int ciFieldName1 = m_dataSource->GetColumnIndex(bs->GetFieldName());
		int ciFieldName2 = m_dataSource->GetColumnIndex(bs->GetFieldName2());
		int ciClr = m_dataSource->GetColumnIndex(bs->GetColorField());
		int ciStyle = m_dataSource->GetColumnIndex(bs->GetStyleField());
		int defaultLineWidth = 1;
        if (!IsOperating() && m_crossStopIndex != -1)
        {
            if (SelectBar(div, (float)GetMousePoint().y, bs->GetFieldName(), bs->GetFieldName2(), bs->GetStyleField(), bs->GetAttachVScale(), m_crossStopIndex))
            {
                defaultLineWidth = 2;
            }
        }
		for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
        {
			int thinLineWidth = 1;
			if(m_crossStopIndex == i)
			{
				thinLineWidth = defaultLineWidth;
			}
			int style = -10000;
			switch (bs->GetStyle())
			{
				case BarStyle_Line:
					style = 2;
					break;
				case BarStyle_Rect:
					style = 0;
					break;
			}
			if (ciStyle != -1)
			{
				double defineStyle = m_dataSource->Get3(i, ciStyle);
				if (!m_dataSource->IsNaN(defineStyle))
				{
					style = (int)defineStyle;
				}
			}
			if(style == -10000)
			{
				continue;
			}
			double value = m_dataSource->Get3(i, ciFieldName1); 
			int scaleX = (int)GetX(i);
			double midValue = 0;
			if(ciFieldName2 != -1)
			{
				midValue = m_dataSource->Get3(i, ciFieldName2); 
			}
			int midY = (int)GetY(div, midValue, bs->GetAttachVScale());
			if (!m_dataSource->IsNaN(value))
			{
				float barY = GetY(div, value, bs->GetAttachVScale());
				int startPX = scaleX;
				int startPY = (int)midY;
				int endPX = scaleX;
				int endPY = (int)barY;
				if (bs->GetStyle() == BarStyle_Rect)
				{
					if (startPY == div->GetHeight() - div->GetHScale()->GetHeight())
					{
						startPY = div->GetHeight() - div->GetHScale()->GetHeight() + 1;
					}
				}
				int x = 0, y = 0, width = 0, height = 0;
				width = (int)(m_hScalePixel * 2 / 3);
				if (width % 2 == 0)
				{
					width += 1;
				}
				if (width < 3)
				{
					width = 1;
				}
				x = scaleX - width / 2;
				if (startPY >= endPY)
				{
					y = endPY;
				}
				else
				{
					y = startPY;
				}
				height = abs(startPY - endPY);
				if (height < 1)
				{
					height = 1;
				}
				_int64 barColor = COLOR_EMPTY;
				if (ciClr != -1)
				{
					double defineColor = m_dataSource->Get3(i, ciClr);
					if(!m_dataSource->IsNaN(defineColor))
					{
						barColor = (_int64)defineColor;
					}
				}
				if(barColor == COLOR_EMPTY)
				{
					if (startPY >= endPY)
					{
						barColor = bs->GetUpColor();
					}
					else
					{
						barColor = bs->GetDownColor();
					}
				}
				switch (style)
				{
					case -1:
						if (m_hScalePixel <= 3)
						{
							DrawThinLine(paint, barColor, thinLineWidth, startPX, y, startPX, y + height);
						}
						else
						{
							RECT rect = {x, y, x + width,y + height};
							paint->FillRect(div->GetBackColor(), rect);
							paint->DrawRect(barColor, (float)thinLineWidth, 1, rect);
						}
						break;
					case 0:
						if (m_hScalePixel <= 3)
						{
							DrawThinLine(paint, barColor, thinLineWidth, startPX, y, startPX, y + height);
						}
						else
						{
							RECT rect = {x, y, x + width,y + height};
							paint->FillRect(barColor, rect);
							if (thinLineWidth > 1)
							{
								if (startPY >= endPY)
								{
									paint->DrawRect(bs->GetDownColor(), (float)thinLineWidth, 0, rect);
								}
								else
								{
									paint->DrawRect(bs->GetUpColor(), (float)thinLineWidth, 0, rect);
								}
							}
						}
						break;
					case 1:
						if (m_hScalePixel <= 3)
						{
							DrawThinLine(paint, barColor, thinLineWidth, startPX, y, startPX, y + height);
						}
						else
						{
							RECT rect = {x, y, x + width,y + height};
							paint->FillRect(div->GetBackColor(), rect);
							paint->DrawRect(barColor, (float)thinLineWidth, 0, rect);
						}
						break;
					case 2:
                        if (startPY <= 0)
                        {
                            startPY = 0;
                        }
                        if (startPY >= div->GetHeight())
                        {
                            startPY = div->GetHeight();
                        }
                        if (endPY <= 0)
                        {
                            endPY = 0;
                        }
                        if (endPY >= div->GetHeight())
                        {
                            endPY = div->GetHeight();
                        }
                        if (bs->GetLineWidth() <= 1)
                        {
                            DrawThinLine(paint, barColor, thinLineWidth, startPX, startPY, endPX, endPY);
                        }
                        else
                        {
                            float lineWidth = bs->GetLineWidth();
                            if (lineWidth > m_hScalePixel)
                            {
                                lineWidth = m_hScalePixel;
                            }
                            if (lineWidth < 1)
                            {
                                lineWidth = 1;
                            }
							paint->DrawLine(barColor, (float)(lineWidth + thinLineWidth - 1), 0, startPX, startPY, endPX, endPY);
                        }
						break;
				}
				if(bs->IsSelected())
				{
					int kPInterval = m_maxVisibleRecord / 30;
					if (kPInterval < 2)
					{
						kPInterval = 2;
					}
					if (i % kPInterval == 0)
					{
						if (barY >= div->GetTitleBar()->GetHeight()
							&& barY <= div->GetHeight() - div->GetHScale()->GetHeight())
						{
							RECT sRect = {scaleX - 3, (int)barY - 4, scaleX + 4, (int)barY + 3};
							paint->FillRect(bs->GetSelectedColor(), sRect);
						}
					}
				}
			}
			if (i == m_lastVisibleIndex && div->GetVScale(bs->GetAttachVScale())->GetVisibleMin() < 0)
			{
				if (m_reverseHScale)
                {
					int left = (int)(m_leftVScaleWidth + m_workingAreaWidth - (m_lastVisibleIndex - m_firstVisibleIndex + 1) * m_hScalePixel);
					paint->DrawLine(bs->GetDownColor(), 1, 0, m_leftVScaleWidth + m_workingAreaWidth, (int)midY, left, (int)midY);
				}
				else
				{
					int right = (int)(m_leftVScaleWidth + (m_lastVisibleIndex - m_firstVisibleIndex + 1) * m_hScalePixel);
					paint->DrawLine(bs->GetDownColor(), 1, 0, m_leftVScaleWidth, midY, right, midY);
				}
			}
		}
	}

	void CChartMe::OnPaintCandle(CPaintMe *paint, CDivMe *div, CCandleShapeMe *cs)
	{
		int x = 0, y = 0;
		vector<POINT> points;
		int visibleMaxIndex = 0, visibleMinIndex = 0;
		double visibleMax = 0, visibleMin = 0;
		int ciHigh = m_dataSource->GetColumnIndex(cs->GetHighField());
		int ciLow = m_dataSource->GetColumnIndex(cs->GetLowField());
		int ciOpen = m_dataSource->GetColumnIndex(cs->GetOpenField());
		int ciClose = m_dataSource->GetColumnIndex(cs->GetCloseField());
		int ciClr = m_dataSource->GetColumnIndex(cs->GetColorField());
		int ciStyle = m_dataSource->GetColumnIndex(cs->GetStyleField());
		int defaultLineWidth = 1;
        if (!IsOperating() && m_crossStopIndex != -1)
        {
            if (SelectCandle(div, (float)GetMousePoint().y, cs->GetHighField(), cs->GetLowField(), cs->GetStyleField(), cs->GetAttachVScale(), m_crossStopIndex))
            {
                defaultLineWidth = 2;
            }
        }
		for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
        {
			int thinLineWidth = 1;
			if(i == m_crossStopIndex)
			{
				thinLineWidth = defaultLineWidth;
			}
			int style = -10000;
			switch (cs->GetStyle())
			{
				case CandleStyle_Rect:
					style = 0;
					break;
				case CandleStyle_American:
					style = 3;
					break;
				case CandleStyle_CloseLine:
					style = 4;
					break;
				case CandleStyle_Tower:
					style = 5;
					break;
			}
			if (ciStyle != -1)
			{
				double defineStyle = m_dataSource->Get3(i, ciStyle);
				if (!m_dataSource->IsNaN(defineStyle))
				{
					style = (int)defineStyle;
				}
			}
			if (style == -10000)
			{
				continue;
			}
			double open = m_dataSource->Get3(i, ciOpen);
			double high = m_dataSource->Get3(i, ciHigh);
			double low = m_dataSource->Get3(i, ciLow);
			double close = m_dataSource->Get3(i, ciClose); 
			if (m_dataSource->IsNaN(open) || m_dataSource->IsNaN(high) || m_dataSource->IsNaN(low) || m_dataSource->IsNaN(close))
			{
                if (i != m_lastVisibleIndex || style != 4)
                {
                    continue;
                }
			}
			int scaleX = (int)GetX(i);
			if (cs->GetShowMaxMin())
			{
				if (i == m_firstVisibleIndex)
				{
					visibleMaxIndex = i;
					visibleMinIndex = i;
					visibleMax = high;
					visibleMin = low ;
				}
				else
				{
					if (high > visibleMax)
					{
						visibleMax = high;
						visibleMaxIndex = i;
					}
					if (low < visibleMin)
					{
						visibleMin = low;
						visibleMinIndex = i;
					}
				}
			}
			int highY = (int)GetY(div, high, cs->GetAttachVScale());
			int openY = (int)GetY(div, open, cs->GetAttachVScale());
			int lowY = (int)GetY(div, low, cs->GetAttachVScale());
			int closeY = (int)GetY(div, close, cs->GetAttachVScale());
			int cwidth = (int)(m_hScalePixel * 2 / 3);
			if (cwidth % 2 == 0)
			{
				cwidth += 1;
			}
			if (cwidth < 3) 
			{
				cwidth = 1;
			}
			int xsub = cwidth / 2;
			if(xsub < 1)
			{
				xsub = 1;
			}
			switch(style)
			{
			case 3:
				{
					_int64 color = cs->GetUpColor();
					if(open > close)
					{
						color = cs->GetDownColor();
					}
					if (ciClr != -1)
					{
						double defineColor = m_dataSource->Get3(i, ciClr);
						if(!m_dataSource->IsNaN(defineColor))
						{
							color = (_int64)defineColor;
						}
					}
					if ((int)highY != (int)lowY)
					{
						if (m_hScalePixel <= 3)
						{
							DrawThinLine(paint, color, thinLineWidth, scaleX, highY, scaleX, lowY);
						}
						else
						{
							DrawThinLine(paint, color, thinLineWidth, scaleX, highY, scaleX, lowY);
							DrawThinLine(paint, color, thinLineWidth, scaleX - xsub, openY, scaleX, openY);
							DrawThinLine(paint, color, thinLineWidth, scaleX, closeY, scaleX + xsub, closeY);
						}
					}
					else
					{
						DrawThinLine(paint, color, thinLineWidth, scaleX - xsub, closeY, scaleX + xsub, closeY);
					}
					break;
				}
			case 4:
				OnPaintPolyline(paint, div, cs->GetUpColor(), COLOR_EMPTY, ciClr, defaultLineWidth, PolylineStyle_SolidLine, close, cs->GetAttachVScale(), scaleX, (int)closeY, i, &points, &x, &y);
				break;
			default:
				if (open <= close)
				{
					float recth = GetUpCandleHeight(close, open, div->GetVScale(cs->GetAttachVScale())->GetVisibleMax(), div->GetVScale(cs->GetAttachVScale())->GetVisibleMin(), (float)div->GetWorkingAreaHeight());
					if (recth < 1)
					{
						recth = 1;
					}
					int rcUpX = scaleX - xsub, rcUpBottom = (int)openY, rcUpW = cwidth, rcUpH = (int)recth;
					if (openY < closeY)
					{
						rcUpBottom = (int)closeY;
					}
					_int64 upColor = COLOR_EMPTY;
					int colorField = cs->GetColorField();
					if (colorField != CTableMe::NULLFIELD())
					{
						double defineColor = m_dataSource->Get2(i, colorField);
						if(!m_dataSource->IsNaN(defineColor))
						{
							upColor = (_int64)defineColor;
						}
					}
					if(upColor == COLOR_EMPTY)
					{
						upColor = cs->GetUpColor();
					}
					switch (style)
					{
						case 0:
						case 1:
						case 2:
							if ((int)highY != (int)lowY)
							{
								DrawThinLine(paint, upColor, thinLineWidth, scaleX, highY, scaleX, lowY);
								if (m_hScalePixel > 3)
								{
									if ((int)openY == (int)closeY)
									{
										DrawThinLine(paint, upColor, thinLineWidth, rcUpX, rcUpBottom, rcUpX + rcUpW, rcUpBottom);
									}
									else
									{
										RECT rcUp = {rcUpX, rcUpBottom - rcUpH, rcUpX + rcUpW, rcUpBottom};
										if (style == 0 || style == 1)
										{
											if (rcUpW > 0 && rcUpH > 0 && m_hScalePixel > 3)
											{
												paint->FillRect(div->GetBackColor(), rcUp);
											}
											paint->DrawRect(upColor, (float)thinLineWidth, 0, rcUp);
										}
										else if (style == 2)
										{
											paint->FillRect(upColor, rcUp);
											if (thinLineWidth > 1)
                                            {
                                                paint->DrawRect(upColor, (float)thinLineWidth, 0, rcUp);
                                            }
										}
									}
								}
							}
							else
							{
								DrawThinLine(paint, upColor, thinLineWidth, scaleX - xsub, closeY, scaleX + xsub, closeY);
							}
							break;
						case 5:
							{
								double lOpen = m_dataSource->Get3(i - 1, ciOpen);
								double lClose = m_dataSource->Get3(i - 1, ciClose);
								double lHigh = m_dataSource->Get3(i - 1, ciHigh);
								double lLow = m_dataSource->Get3(i - 1, ciLow);
								int top = highY;
								int bottom = lowY;
								if ((int)highY > (int)lowY)
								{
									top = lowY;
									bottom = highY;
								}
								if (i == 0 || m_dataSource->IsNaN(lOpen) || m_dataSource->IsNaN(lClose) || m_dataSource->IsNaN(lHigh) || m_dataSource->IsNaN(lLow))
								{
									if (m_hScalePixel <= 3)
									{
										DrawThinLine(paint, upColor, thinLineWidth, rcUpX, top, rcUpX, bottom);
									}
									else
									{
										int rcUpHeight = (int)abs(bottom - top == 0 ? 1 : bottom - top);
										if (rcUpW > 0 && rcUpHeight > 0)
										{
											RECT rcUp = {rcUpX, top, rcUpX + rcUpW, top + rcUpHeight};
											paint->FillRect(upColor, rcUp);
											if (thinLineWidth > 1)
                                            {
                                                paint->DrawRect(upColor, (float)thinLineWidth, 0, rcUp);
                                            }
										}
									}
								}
								else
								{
									if (m_hScalePixel <= 3)
									{
										DrawThinLine(paint, upColor, thinLineWidth, rcUpX, top, rcUpX, bottom);
									}
									else
									{
										int rcUpHeight = (int)abs(bottom - top == 0 ? 1 : bottom - top);
										if (rcUpW > 0 && rcUpHeight> 0)
										{
											RECT rcUp = {rcUpX, top, rcUpX + rcUpW, top + rcUpHeight};
											paint->FillRect(upColor, rcUp);
											if (thinLineWidth > 1)
                                            {
                                                paint->DrawRect(upColor, (float)thinLineWidth, 0, rcUp);
                                            }
										}
									}
									if (lClose < lOpen && low < lHigh)
									{
										int tx = rcUpX;
										int ty = (int)GetY(div, lHigh, cs->GetAttachVScale());
										if (high < lHigh)
										{
											ty = (int)highY;
										}
										int width = rcUpW;
										int height = (int)lowY - ty;
										if (height > 0)
										{
											if (m_hScalePixel <= 3)
											{
												DrawThinLine(paint, cs->GetDownColor(), thinLineWidth, tx, ty, tx, ty + height);
											}
											else
											{
												if (width > 0 && height > 0)
												{
													RECT rect = {tx, ty, tx + width, ty + height};
													paint->FillRect(cs->GetDownColor(), rect);
													if (thinLineWidth > 1)
													{
														paint->DrawRect(cs->GetDownColor(), (float)thinLineWidth, 0, rect);
													}
												}
											}
										}
									}
								}
								break;
							}
					}
				}
				else
				{
					float recth = GetDownCandleHeight(close, open, div->GetVScale(cs->GetAttachVScale())->GetVisibleMax(), div->GetVScale(cs->GetAttachVScale())->GetVisibleMin(), (float)div->GetWorkingAreaHeight());
					if (recth < 1)
					{
						recth = 1;
					}
					int rcDownX = scaleX - xsub, rcDownBottom = (int)closeY, rcDownW = cwidth, rcDownH = (int)recth;
					if (closeY < openY)
					{
						rcDownBottom = (int)openY;
					}
					_int64 downColor = COLOR_EMPTY;
					if (ciClr != -1)
					{
						double defineColor = m_dataSource->Get3(i, ciClr);
						if(!m_dataSource->IsNaN(defineColor))
						{
							downColor = (_int64)defineColor;
						}
					}
					if(downColor == COLOR_EMPTY)
					{
						downColor = cs->GetDownColor();
					}
					switch (style)
					{
						case 0:
						case 1:
						case 2:
							if ((int)highY != (int)lowY)
							{
								DrawThinLine(paint, downColor, thinLineWidth, scaleX, highY, scaleX, lowY);
								if (m_hScalePixel > 3)
								{
									RECT rcDown = {rcDownX, rcDownBottom - rcDownH, rcDownX + rcDownW, rcDownBottom};
									if (style == 1)
									{
										if (rcDownW > 0 && rcDownH > 0 && m_hScalePixel > 3)
										{
											paint->FillRect(div->GetBackColor(), rcDown);
										}
										paint->DrawRect(downColor, (float)thinLineWidth, 0, rcDown);
									}
									else if (style == 0 || style == 1)
									{
										paint->FillRect(downColor, rcDown);
										if (thinLineWidth > 1)
										{
											paint->DrawRect(downColor, (float)thinLineWidth, 0, rcDown);
										}
									}
								}
							}
							else
							{
								DrawThinLine(paint, downColor, thinLineWidth, scaleX - xsub, closeY, scaleX + xsub, closeY);
							}
							break;
						case 5:
							double lOpen = m_dataSource->Get3(i - 1, ciOpen);
							double lClose = m_dataSource->Get3(i - 1, ciClose);
							double lHigh = m_dataSource->Get3(i - 1, ciHigh);
							double lLow = m_dataSource->Get3(i - 1, ciLow);
							int top = highY;
							int bottom = lowY;
							if ((int)highY > (int)lowY)
							{
								top = lowY;
								bottom = highY;
							}
							if (i == 0 || m_dataSource->IsNaN(lOpen) || m_dataSource->IsNaN(lClose) || m_dataSource->IsNaN(lHigh) || m_dataSource->IsNaN(lLow))
							{
								if (m_hScalePixel <= 3)
								{
									DrawThinLine(paint, downColor, thinLineWidth, rcDownX, top, rcDownX, bottom);
								}
								else
								{
									int rcDownHeight = (int)abs(bottom - top == 0 ? 1 : bottom - top);
									if (rcDownW > 0 && rcDownHeight > 0)
									{
										RECT rcDown = {rcDownX, top, rcDownX + rcDownW, rcDownBottom};
										paint->FillRect(downColor,rcDown);
										if (thinLineWidth > 1)
										{
											paint->DrawRect(downColor, (float)thinLineWidth, 0, rcDown);
										}
									}
								}
							}
							else
							{
								if (m_hScalePixel <= 3)
								{
									DrawThinLine(paint, downColor, thinLineWidth, rcDownX, top, rcDownX, bottom);
								}
								else
								{
									int rcDownHeight = (int)abs(bottom - top == 0 ? 1 : bottom - top);
									if (rcDownW > 0 && rcDownHeight > 0)
									{
										 RECT rcDown = {rcDownX, top, rcDownX + rcDownW, rcDownBottom};
										 paint->FillRect(downColor, rcDown);
										 if (thinLineWidth > 1)
										 {
											 paint->DrawRect(downColor, (float)thinLineWidth, 0, rcDown);
										 }
									}
								}
								if (lClose >= lOpen && high > lLow)
								{
									int tx = rcDownX;
									int ty = (int)highY;
									int width = rcDownW;
									int height = (int)abs(GetY(div, lLow, cs->GetAttachVScale()) - ty);
									if (low > lLow)
									{
										height = (int)lowY - ty;
									}
									if (height > 0)
									{
										if (m_hScalePixel <= 3)
										{
											DrawThinLine(paint, cs->GetUpColor(), thinLineWidth, tx, ty, tx, ty + height);
										}
										else
										{
											if (width > 0 && height > 0)
											{
												RECT rect = {tx, ty, tx + width, ty + height};
												paint->FillRect(cs->GetUpColor(), rect);
												if (thinLineWidth > 1)
												{
													paint->DrawRect(cs->GetUpColor(), (float)thinLineWidth, 0, rect);
												}
											}
										}
									}
								}
							}
							break;
					}
				}
				break;
			}
			if(cs->IsSelected())
			{
				int kPInterval = m_maxVisibleRecord / 30;
				if (kPInterval < 2)
				{
					kPInterval = 3;
				}
				if (i % kPInterval == 0)
				{
					if (!m_dataSource->IsNaN(open) && !m_dataSource->IsNaN(high) && !m_dataSource->IsNaN(low) && !m_dataSource->IsNaN(close))
					{
						if (closeY >= div->GetTitleBar()->GetHeight()
							&& closeY <= div->GetHeight() - div->GetHScale()->GetHeight())
						{
							RECT sRect = {scaleX - 3, closeY - 4, scaleX + 4, closeY + 3};
							paint->FillRect(cs->GetSelectedColor(), sRect);
						}
					}
				}
			}
		}
		OnPaintCandleEx(paint, div, cs, visibleMaxIndex, visibleMax, visibleMinIndex, visibleMin);
	}

	void CChartMe::OnPaintCandleEx(CPaintMe *paint, CDivMe *div, CCandleShapeMe *cs, int visibleMaxIndex, double visibleMax, int visibleMinIndex, double visibleMin)
	{
		if (m_dataSource->RowsCount() > 0)
        {
			if (visibleMaxIndex != -1 && visibleMinIndex != -1 && cs->GetShowMaxMin())
            {
                double max = visibleMax;
                double min = visibleMin;
                float scaleYMax = GetY(div, max, cs->GetAttachVScale());
                float scaleYMin = GetY(div, min, cs->GetAttachVScale());
                int scaleXMax = (int)GetX(visibleMaxIndex);
                int digit = div->GetVScale(cs->GetAttachVScale())->GetDigit();
				wchar_t maxStr[100] = {0};
				CStrMe::GetValueByDigit(max, digit, maxStr);
				FONT *font = div->GetFont();
				SIZE maxSize = paint->TextSize(maxStr, font);
				int width = GetWidth();
                float maxPX = 0, maxPY = 0;
                float strY = 0;
                if (scaleYMax > scaleYMin)
                {
					GetCandleMinStringPoint((float)scaleXMax, scaleYMax, (float)maxSize.cx, (float)maxSize.cy, width, m_leftVScaleWidth, m_rightVScaleWidth, &maxPX, &maxPY);
					strY = maxPY + maxSize.cy;
                }
                else
                {
					GetCandleMaxStringPoint((float)scaleXMax, scaleYMax, (float)maxSize.cx, (float)maxSize.cy, width, m_leftVScaleWidth, m_rightVScaleWidth,  &maxPX, &maxPY);
					strY = maxPY;
                }
				_int64 tagColor = cs->GetTagColor();
				DrawText(paint, maxStr, tagColor, font, (int)maxPX, (int)maxPY);
                paint->DrawLine(tagColor, 1, 0, scaleXMax, (int)scaleYMax, (int)(maxPX + maxSize.cx / 2), (int)strY);
				wchar_t minStr[100] = {0};
				CStrMe::GetValueByDigit(min, digit, minStr);
				SIZE minSize = paint->TextSize(minStr, font);
                int scaleXMin = (int)GetX(visibleMinIndex);
                float minPX = 0, minPY = 0;
                if (scaleYMax > scaleYMin)
                {
					GetCandleMaxStringPoint((float)scaleXMin, scaleYMin, (float)minSize.cx, (float)minSize.cy, width, m_leftVScaleWidth, m_rightVScaleWidth, &minPX, &minPY);
					strY = minPY;
                }
                else
                {
					GetCandleMinStringPoint((float)scaleXMin, scaleYMin, (float)minSize.cx, (float)minSize.cy, width, m_leftVScaleWidth, m_rightVScaleWidth, &minPX, &minPY);
					strY = minPY + minSize.cy;
                }
				DrawText(paint, minStr, tagColor, font, (int)minPX, (int)minPY);
                paint->DrawLine(tagColor, 1, 0, scaleXMin, (int)scaleYMin, (int)(minPX + minSize.cx / 2), (int)strY);
            }
        }
	}

	void CChartMe::OnPaintCrossLine(CPaintMe *paint, CDivMe *div)
    {
        POINT mousePoint = GetMousePoint();
        if (m_cross_y != -1)
        {
			int divWidth = div->GetWidth();
			int divHeight = div->GetHeight();
            int titleBarHeight = div->GetTitleBar()->GetHeight();
            int hScaleHeight = div->GetHScale()->GetHeight();
			int mpY = m_cross_y - div->GetTop();
            if (m_dataSource->RowsCount() > 0 && m_hResizeType == 0 && !m_userResizeDiv)
            {
                if (mpY >= titleBarHeight && mpY <= divHeight - hScaleHeight)
                {
					CVScaleMe *leftVScale = div->GetLeftVScale();
					CCrossLineTipMe *crossLineTip = leftVScale->GetCrossLineTip();
                    if (m_leftVScaleWidth != 0 && crossLineTip->IsVisible())
                    {
						if(crossLineTip->AllowUserPaint())
						{
							RECT clipRect = {0, 0, m_leftVScaleWidth, divHeight - hScaleHeight};
							crossLineTip->OnPaint(paint, div, clipRect);
						}
						else
						{
							double lValue = GetNumberValue(div, mousePoint, AttachVScale_Left);
							wchar_t leftValue[100] = {0};
							CStrMe::GetValueByDigit(lValue, leftVScale->GetDigit(), leftValue);
							SIZE leftYTipFontSize = paint->TextSize(leftValue, crossLineTip->GetFont());
							if (leftYTipFontSize.cx > 0 && leftYTipFontSize.cy > 0)
							{
								int lRtX = m_leftVScaleWidth - leftYTipFontSize.cx - 1;
								int lRtY = mpY - leftYTipFontSize.cy / 2;
								int lRtW = leftYTipFontSize.cx;
								int lRtH = leftYTipFontSize.cy;
								if (lRtW > 0 && lRtH > 0)
								{
									RECT lRtL = {lRtX, lRtY, lRtX + lRtW, lRtY + lRtH};
									paint->FillRect(crossLineTip->GetBackColor(),lRtL);
									paint->DrawRect(crossLineTip->GetForeColor(), 1, 0, lRtL);
								}
								DrawText(paint, leftValue, crossLineTip->GetForeColor(), crossLineTip->GetFont(), lRtX, lRtY);
							}
						}
                    }
					CVScaleMe *rightVScale = div->GetRightVScale();
					crossLineTip = rightVScale->GetCrossLineTip();
                    if (m_rightVScaleWidth != 0 && crossLineTip->IsVisible())
                    {
						if(crossLineTip->AllowUserPaint())
						{
							RECT clipRect = {divWidth - m_rightVScaleWidth, 0, divWidth, divHeight - hScaleHeight};
							crossLineTip->OnPaint(paint, div, clipRect);
						}
						else
						{
							double rValue = GetNumberValue(div, mousePoint, AttachVScale_Right);
							wchar_t rightValue[100] = {0};
							CStrMe::GetValueByDigit(rValue, rightVScale->GetDigit(), rightValue);
							SIZE rightYTipFontSize = paint->TextSize(rightValue, crossLineTip->GetFont());
							if (rightYTipFontSize.cx > 0 && rightYTipFontSize.cy > 0)
							{
								int rRtX = GetWidth() - m_rightVScaleWidth + 1;
								int rRtY = mpY - rightYTipFontSize.cy / 2;
								int rRtW = rightYTipFontSize.cx;
								int rRtH = rightYTipFontSize.cy;
								if (rRtW > 0 && rRtH > 0)
								{
									RECT rRtL = {rRtX, rRtY, rRtX + rRtW, rRtY + rRtH};
									paint->FillRect(crossLineTip->GetBackColor(), rRtL);
									paint->DrawRect(crossLineTip->GetForeColor(), 1, 0, rRtL);
								}
								DrawText(paint, rightValue, crossLineTip->GetForeColor(), crossLineTip->GetFont(), rRtX, rRtY);
							}
						}
                    }
                }
            }
            int verticalX = 0;
			if (m_crossStopIndex >= m_firstVisibleIndex && m_crossStopIndex <= m_lastVisibleIndex)
            {
                verticalX = (int)GetX(m_crossStopIndex);
            }
            if (!m_isScrollCross)
            {
                verticalX = mousePoint.x;
            }
			CCrossLineMe *crossLine = div->GetCrossLine();
            if (crossLine->AllowUserPaint())
            {
                RECT clRect = {0, 0, divWidth, divHeight};
                crossLine->OnPaint(paint, div, clRect);
            }
            else
            {
				if (m_showCrossLine)
				{
					if (mpY >= titleBarHeight && mpY <= divHeight - hScaleHeight)
					{
						paint->DrawLine(crossLine->GetLineColor(), 1, 0, m_leftVScaleWidth, mpY, GetWidth() - m_rightVScaleWidth, mpY);
					}
				}
				if (m_crossStopIndex == -1 || m_crossStopIndex < m_firstVisibleIndex || m_crossStopIndex > m_lastVisibleIndex)
				{
					if (m_showCrossLine)
					{
						int x = mousePoint.x;
						if (x > m_leftVScaleWidth && x < m_leftVScaleWidth + m_workingAreaWidth)
						{
							paint->DrawLine(crossLine->GetLineColor(), 1, 0, x, titleBarHeight, x, divHeight - hScaleHeight);
						}
					}
					return;
				}
				if (m_showCrossLine)
				{
					paint->DrawLine(crossLine->GetLineColor(), 1, 0, verticalX, titleBarHeight, verticalX, divHeight - hScaleHeight);
				}
			}
            if (m_hResizeType == 0 && !m_userResizeDiv)
            {
				CHScaleMe *hScale = div->GetHScale();
				CCrossLineTipMe *hScaleCrossLineTip = hScale->GetCrossLineTip();
				if (hScale->IsVisible() && hScaleCrossLineTip->IsVisible())
                {
					if(hScaleCrossLineTip->AllowUserPaint())
					{
						RECT clipRect = {0, divHeight - hScaleHeight, divWidth, divHeight};
						hScaleCrossLineTip->OnPaint(paint, div, clipRect);
					}
					else
					{
						wchar_t *tip = 0;
						wchar_t formatDate[100] = {0};
						wchar_t ctip[100] = {0};
						tip = L"";
						if (hScale->GetHScaleType() == HScaleType_Date)
						{
							CStrMe::GetFormatDate(m_dataSource->GetXValue(m_crossStopIndex), formatDate);
							tip = formatDate;
						}
						else if (hScale->GetHScaleType() == HScaleType_Number)
						{
							_stprintf_s(ctip, 99, L"%d", (int)m_dataSource->GetXValue(m_crossStopIndex));
							tip = ctip;
						}
						SIZE xTipFontSize = paint->TextSize(tip, hScaleCrossLineTip->GetFont());
						int xRtX = verticalX - xTipFontSize.cx / 2;
						int xRtY = divHeight - hScaleHeight + 2;
						int xRtW = xTipFontSize.cx + 2;
						int xRtH = xTipFontSize.cy;
						if (xRtX < m_leftVScaleWidth)
						{
							xRtX = m_leftVScaleWidth;
							xRtY = divHeight - hScaleHeight + 2;
						}
						if (xRtX + xRtW > divWidth - m_rightVScaleWidth)
						{
							xRtX = divWidth - m_rightVScaleWidth - xTipFontSize.cx - 1;
							xRtY = divHeight - hScaleHeight + 2;
						}                             
						if (xRtW > 0 && xRtH > 0)
						{
							RECT xRtL = {xRtX, xRtY, xRtX + xRtW, xRtY + xRtH};
							paint->FillRect(hScaleCrossLineTip->GetBackColor(), xRtL);
							paint->DrawRect(hScaleCrossLineTip->GetForeColor(),1 , 0, xRtL);
							DrawText(paint, tip, hScaleCrossLineTip->GetForeColor(), hScaleCrossLineTip->GetFont(), xRtX, xRtY);
						}
					}
                }
            }
        }
    }

	void CChartMe::OnPaintDivBackGround(CPaintMe *paint, CDivMe *div)
    {
        int width = div->GetWidth();
        int height = div->GetHeight();
        if (width < 1)
        {
            width = 1;
        }
        if (height < 1)
        {
            height = 1;
        }
        if (width > 0 && height > 0)
        {
			RECT rect = {0, 0, width, height};
			if(div->AllowUserPaint())
			{
				div->OnPaint(paint, rect);
			}
			else
			{
				if (div->GetBackColor() != GetBackColor())
				{
					paint->FillRect(div->GetBackColor(), rect);
				}
			}
        }
    }

	void CChartMe::OnPaintDivBorder(CPaintMe *paint, CDivMe *div)
    {
        int y = 0;
        int width = div->GetWidth();
        int height = div->GetHeight();
        if (width < 1)
        {
            width = 1;
        }
        if (height < 1)
        {
            height = 1;
        }
        if (width > 0 && height > 0)
        {
            CDivMe *lDiv = 0;
            vector<CDivMe*> divsCopy = GetDivs();
            vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *cDiv = *sIter;
                if (div != cDiv)
                {
                    lDiv = cDiv;
                }
                else
                {
                    break;
                }
            }
            if (lDiv)
            {
                if (!lDiv->GetHScale()->IsVisible())
                {
                    paint->DrawLine(div->GetHScale()->GetScaleColor(), 1, 0, m_leftVScaleWidth, y + 1, width - m_rightVScaleWidth, y + 1);
                }
                else
                {
                    paint->DrawLine(div->GetHScale()->GetScaleColor(), 1, 0, 0, y + 1, width, y + 1);
                }
            }
            if (div->IsShowSelect() && div->IsSelected())
            {
                if (m_leftVScaleWidth > 0)
                {
					int leftRectX = 1;
					int leftRectY = 0;
					int leftRectW = m_leftVScaleWidth - 1;
					int leftRectH = div->GetHeight() - div->GetHScale()->GetHeight();
                    if (leftRectW > 0 && leftRectH > 0)
                    {
						RECT leftRect = {leftRectX,leftRectY,leftRectX + leftRectW,leftRectY + leftRectH};
						paint->DrawRect(div->GetLeftVScale()->GetScaleColor(), 1, 0, leftRect);
                    }
                }
                if (m_rightVScaleWidth > 0)
                {
					int rightRectX = GetWidth() - m_rightVScaleWidth + 1;
					int rightRectY = 0;
					int rightRectW = m_rightVScaleWidth - 1;
					int rightRectH = div->GetHeight() - div->GetHScale()->GetHeight();
                    if (rightRectW > 0 && rightRectH> 0)
                    {
						RECT rightRect = {rightRectX,rightRectY,rightRectX + rightRectW,rightRectY + rightRectH};
                        paint->DrawRect(div->GetRightVScale()->GetScaleColor(),1 , 0, rightRect);
                    }
                }
            }
            if (div->GetBorderColor() != COLOR_EMPTY)
            {
            	if (width > 0 && height > 0)
            	{
					RECT rect = {0, y, width, height};
                	paint->DrawRect(div->GetBorderColor(), 1, 0, rect);
                }
			}
        }
    }
		
	void CChartMe::OnPaintHScale(CPaintMe *paint, CDivMe *div)
    {
		CHScaleMe *hScale = div->GetHScale();
		CScaleGridMe *vGrid = div->GetVGrid();
		int width = div->GetWidth(), height = div->GetHeight();
		int scaleHeight = hScale->GetHeight();
        if ((hScale->IsVisible() || vGrid->IsVisible()) && height >= scaleHeight)
        {
			RECT hRect = {0, height - scaleHeight, width, height};
			if(hScale->AllowUserPaint())
			{
				hScale->OnPaint(paint, div, hRect);
			}
			if(vGrid->AllowUserPaint())
			{
				vGrid->OnPaint(paint, div, hRect);
			}
			if(hScale->AllowUserPaint() && vGrid->AllowUserPaint())
			{
				return;
			}
            int divBottom = div->GetHeight();
            if (hScale->IsVisible() && !hScale->AllowUserPaint())
            {
                paint->DrawLine(hScale->GetScaleColor(), 1, 0, 0, divBottom - scaleHeight+ 1, width, divBottom - scaleHeight + 1);
            }
            if (m_firstVisibleIndex >= 0)
            {
                double xScaleWordRight = 0;
                int pureH = m_workingAreaWidth;
				vector<double> scaleSteps = hScale->GetScaleSteps();
				int scaleStepsSize = (int)scaleSteps.size();
                map<double, int> scaleStepsMap;
                for (int i = 0; i < scaleStepsSize; i++)
                {
                    scaleStepsMap[scaleSteps[i]] = 0;
                }
                if (hScale->GetHScaleType() == HScaleType_Number)
                {
                    for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
                    {
						double xValue = m_dataSource->GetXValue(i);
						if (scaleStepsSize > 0 && scaleStepsMap.find(xValue) == scaleStepsMap.end())
                        {
                            continue;
                        }
						wchar_t xValueStr[20] = {0};
						_stprintf_s(xValueStr, 19, L"%d",(int)m_dataSource->GetXValue(i));
                        int scaleX = (int)GetX(i);
                        SIZE xSize = paint->TextSize(xValueStr, hScale->GetFont());
                        if (scaleX - xSize.cx / 2 - hScale->GetInterval() > xScaleWordRight)
                        {
                            if (hScale->IsVisible() && !hScale->AllowUserPaint())
                            {
                                DrawThinLine(paint, hScale->GetScaleColor(), 1, scaleX, divBottom - scaleHeight + 1,
                                scaleX, divBottom - scaleHeight + 4);
                                DrawText(paint, xValueStr, hScale->GetForeColor(), hScale->GetFont(),
                                    scaleX - xSize.cx / 2, divBottom - scaleHeight + 6);
                            }
                            xScaleWordRight = scaleX + xSize.cx / 2;
                            if (vGrid->IsVisible() && !vGrid->AllowUserPaint())
                            {
								paint->DrawLine(vGrid->GetGridColor(), 1, vGrid->GetLineStyle(), scaleX, div->GetTitleBar()->GetHeight(),
                                    scaleX, div->GetHeight() - scaleHeight);
                            }
                        }
                    }
                }
                else
                {
					vector<int> xList;
                    for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
                    {
						if (scaleStepsSize > 0)
                        {
							map<double, int>::iterator sIter = scaleStepsMap.find(m_dataSource->GetXValue(i));
							if(sIter != scaleStepsMap.end())
							{
								scaleStepsMap.erase(sIter);
								scaleStepsSize = (int)scaleStepsMap.size();
							    xList.push_back(i);
                                if (scaleStepsSize == 0)
                                {
                                    break;
                                }
							}
							else
							{
								continue;
							}
                        }
                        xList.push_back(i);
                    }
                    int interval = hScale->GetInterval();
                    vector<int> lasts;
                    for (int p = 0; p < 7; p++)
                    {
                        int count = 0;
                        int xListSize = (int)xList.size();
                        for (int i = 0; i < xListSize; i++)
                        {
                            int pos = xList[i];
                            double date = m_dataSource->GetXValue(pos);
							DateType dateType = GetDateType(p);
                            double lDate = 0;
                            if (pos > 0)
                            {
                                lDate = m_dataSource->GetXValue(pos - 1);
                            }
							wchar_t xValueStr[20] = {0};
							xValueStr[0] = L'\0';
                            GetHScaleDateString(date, lDate, &dateType, xValueStr);
                            int scaleX = (int)GetX(pos);
                            if (GetDateType(dateType) == p)
                            {
                                count++;
                                bool show = true;
                                if (scaleStepsSize == 0)
                                {
									int lastsSize = (int)lasts.size();
									for (int j = 0; j < lastsSize; j++)
									{
										int index = lasts[j];
                                        int getX = (int)GetX(index);
                                        if (index > pos)
                                        {
                                            if (m_reverseHScale)
                                            {
                                                if (getX + interval * 2 > scaleX)
                                                {
                                                    show = false;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                if (getX - interval * 2 < scaleX)
                                                {
                                                    show = false;
                                                    break;
                                                }
                                            }
                                        }
                                        else if (index < pos)
                                        {
                                            if (m_reverseHScale)
                                            {
                                                if (getX - interval * 2 < scaleX)
                                                {
                                                    show = false;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                if (getX + interval * 2 > scaleX)
                                                {
                                                    show = false;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                if (show)
                                {
									lasts.push_back(pos);
									if (hScale->IsVisible() && !hScale->AllowUserPaint())
									{
										SIZE xSize = paint->TextSize(xValueStr, hScale->GetFont());
										DrawThinLine(paint, hScale->GetScaleColor(), 1, scaleX, divBottom - scaleHeight + 1,
										scaleX, divBottom - scaleHeight + 4);
										_int64 dateColor = hScale->GetDateColor(GetDateType(p));
										DrawText(paint, xValueStr, dateColor, hScale->GetFont(), scaleX - xSize.cx / 2, divBottom - scaleHeight + 6);
									}
									if (vGrid->IsVisible() && !vGrid->AllowUserPaint())
									{
										paint->DrawLine(vGrid->GetGridColor(), 1, vGrid->GetLineStyle(), scaleX, div->GetTitleBar()->GetHeight(),
											scaleX, div->GetHeight() - scaleHeight);
									}
                                    xList.erase(xList.begin() + i);
                                    i--;
                                    xListSize--;
                                }
                            }
                        }
                        if (count > pureH / 40)
                        {
                            break;
                        }
                    }
                    lasts.clear();
					xList.clear();
                }
            }
        }
        if (div->GetTitleBar()->ShowUnderLine())
        {
            SIZE sizeTitle = paint->TextSize(L" ", div->GetTitleBar()->GetFont());
            paint->DrawLine(div->GetTitleBar()->GetUnderLineColor(), 1, 2, m_leftVScaleWidth, 5 + sizeTitle.cy,
                width - m_rightVScaleWidth, 5 + sizeTitle.cy);
        }
    }

	void CChartMe::OnPaintIcon(CPaintMe *paint)
    {
        if (m_movingShape)
        {
            CDivMe *div = FindDiv(m_movingShape);
            if (div)
            {
				POINT actualPoint = GetMousePoint();
                int x = actualPoint.x;
                int y = actualPoint.y;
				if (m_lastMouseClickPoint.x != -1 && m_lastMouseClickPoint.y != -1 &&
                    abs(x - m_lastMouseClickPoint.x) > 5 && abs(y - m_lastMouseClickPoint.y) > 5)
                {
                    SIZE sizeK;
					sizeK.cx = 15;
					sizeK.cy = 16;
					int rectCsX = x - sizeK.cx;
					int rectCsY = y - sizeK.cy;
					int rectCsH = sizeK.cy;
					CBarShapeMe *bs = dynamic_cast<CBarShapeMe*>(m_movingShape);
					CCandleShapeMe *cs = dynamic_cast<CCandleShapeMe*>(m_movingShape);
					CPolylineShapeMe *tls = dynamic_cast<CPolylineShapeMe*>(m_movingShape);
                    if (bs)
                    {
						RECT bsRectA = {rectCsX + 1, rectCsY + 10, rectCsX + 4, rectCsY + rectCsH - 1};
                        paint->FillRect(bs->GetUpColor(), bsRectA);
						RECT bsRectB = {rectCsX + 6, rectCsY + 3, rectCsX + 9, rectCsY + rectCsH - 1};
                        paint->FillRect(bs->GetUpColor(), bsRectB);
						RECT bsRectC = {rectCsX + 11, rectCsY + 8, rectCsX + 14, rectCsY + rectCsH - 1};
                        paint->FillRect(bs->GetUpColor(), bsRectC);
                    }
                    else if (cs)
                    {
                        paint->DrawLine(cs->GetDownColor(), 1, 0, rectCsX + 4, rectCsY + 6, rectCsX + 4, rectCsY + rectCsH - 2);
                        paint->DrawLine(cs->GetUpColor(), 1, 0, rectCsX + 9, rectCsY + 2, rectCsX + 9, rectCsY + rectCsH - 4);
						RECT csRectA = {rectCsX + 3, rectCsY + 8, rectCsX + 6, rectCsY + 13};
                        paint->FillRect(cs->GetDownColor(), csRectA);
						RECT csRectB = {rectCsX + 8, rectCsY + 4, rectCsX + 11, rectCsY + 9};
                        paint->FillRect(cs->GetUpColor(), csRectB);
                    }
                    else if (tls)
                    {
                        paint->DrawLine(tls->GetColor(), 1, 0, rectCsX + 2, rectCsY + 5, rectCsX + 12, rectCsY + 1);
                        paint->DrawLine(tls->GetColor(), 1, 0, rectCsX + 2, rectCsY + 10, rectCsX + 12, rectCsY + 6);
                        paint->DrawLine(tls->GetColor(), 1, 0, rectCsX + 2, rectCsY + 15, rectCsX + 12, rectCsY + 11);
                    }
                }
            }
        }
    }

	void CChartMe::OnPaintPlots(CPaintMe *paint, CDivMe *div)
    {
        vector<CPlotMe*> plotsCopy = div->GetPlots(SORTTYPE_ASC);
        if (plotsCopy.size() > 0)
        {
            int wX = m_workingAreaWidth;
            int wY = div->GetWorkingAreaHeight();
            if (wX > 0 && wY > 0)
            {
				RECT clipRect = {0};
                clipRect.left = m_leftVScaleWidth;
                clipRect.top = div->GetTitleBar()->IsVisible() ? div->GetTitleBar()->GetHeight() : 0;
                clipRect.right = clipRect.left + wX;
                clipRect.bottom = clipRect.top + wY;
				vector<CPlotMe*>::iterator sIter = plotsCopy.begin();
				for(;sIter != plotsCopy.end();++sIter)
				{
					CPlotMe *pl = *sIter;
					if(pl->IsVisible())
					{
						paint->SetClip(clipRect);
						pl->Render(paint);
					}
				}
            }
        }
    }

	void CChartMe::OnPaintPolyline(CPaintMe *paint, CDivMe *div, CPolylineShapeMe *ls)
	{
		int x = 0, y = 0;
		vector<POINT> points;
		int ciFieldName = m_dataSource->GetColumnIndex(ls->GetBaseField());
		int ciClr = m_dataSource->GetColumnIndex(ls->GetColorField());
		int defaultLineWidth = ls->GetWidth();
        if (!IsOperating() && m_crossStopIndex != -1)
        {
            if (SelectPolyline(div, GetMousePoint(), ls->GetBaseField(), ls->GetWidth(), ls->GetAttachVScale(), m_crossStopIndex))
            {
                defaultLineWidth += 1;
            }
        }
		for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
        {
			int scaleX = (int)GetX(i);
			double value = m_dataSource->Get3(i, ciFieldName); 
			if (!m_dataSource->IsNaN(value))
			{
				int lY = (int)GetY(div, value, ls->GetAttachVScale());
				OnPaintPolyline(paint, div, ls->GetColor(), ls->GetFillColor(), ciClr, defaultLineWidth, ls->GetStyle(), value, ls->GetAttachVScale(), scaleX, lY, i, &points, &x, &y);
				if(ls->IsSelected())
				{
					int kPInterval = m_maxVisibleRecord / 30;
					if (kPInterval < 2)
					{
						kPInterval = 3;
					}
					if (i % kPInterval == 0)
					{
						if (lY >= div->GetTitleBar()->GetHeight()
						   && lY <= div->GetHeight() - div->GetHScale()->GetHeight())
						{
							int lineWidth = ls->GetWidth();
							int rl = scaleX - 3 - (lineWidth - 1);
							int rt = lY - 4 - (lineWidth - 1);
							RECT sRect = {rl, rt, rl + 7 + (lineWidth - 1) * 2, rt + 7 + (lineWidth - 1) * 2};
							paint->FillRect(ls->GetSelectedColor(), sRect);
						}
					}
				}
			}
			else
			{
				OnPaintPolyline(paint, div, ls->GetColor(), ls->GetFillColor(), ciClr, defaultLineWidth, ls->GetStyle(), value, ls->GetAttachVScale(), scaleX, 0, i, &points, &x, &y);
			}
		}
		points.clear();
	}


	void CChartMe::OnPaintPolyline(CPaintMe *paint, CDivMe *div, _int64 lineColor, _int64 fillColor, int ciClr,
            float lineWidth, PolylineStyle lineStyle, double value, AttachVScale attachVScale,
            int scaleX, int lY, int i, vector<POINT> *points, int*x, int *y)
	{
		if (!m_dataSource->IsNaN(value))
		{
			if (m_dataSource->RowsCount() == 1)
			{
				int cwidth = (int)(m_hScalePixel / 4);
				POINT startP = {scaleX - cwidth, lY};
				POINT endP = {scaleX - cwidth + cwidth * 2 + 1, lY};
				points->push_back(startP);
				points->push_back(endP);
			}
			else
			{
				int newX = 0;
				int newY = 0;
				if (i == m_firstVisibleIndex)
				{
					*x = scaleX;
					*y = lY;
				}
				newX = scaleX;
				newY = lY;
				if (*y <= div->GetHeight() - div->GetHScale()->GetHeight() + 1
				 && *y >= div->GetTitleBar()->GetHeight() - 1
				 && newY < div->GetHeight() - div->GetHScale()->GetHeight() + 1
				 && newY >= div->GetTitleBar()->GetHeight() - 1)
				{
					if (*x != newX || *y != newY)
					{
						if(points->size()==0)
						{
							POINT startP = {*x, *y};
							points->push_back(startP);
						}
						POINT endP = {newX, newY};
						points->push_back(endP);
					}
				}
				*x = newX;
				*y = newY;
			}
			if (ciClr != -1)
			{
				double defineColor = m_dataSource->Get3(i, ciClr);
				if(!m_dataSource->IsNaN(defineColor))
				{
					lineColor = (_int64)defineColor;
				}
			}
		}
		if (points->size() > 0)
        {
			_int64 lColor = lineColor;
			if (ciClr != -1 && i > 0)
			{
				double defineColor = m_dataSource->Get2(i - 1, ciClr);
				if(!m_dataSource->IsNaN(defineColor))
				{
					lColor = (_int64)defineColor;
				}
			}
            if (lineColor != lColor || i == m_lastVisibleIndex)
            {
				POINT *pts = new POINT[points->size()];
				int psize = (int)points->size();
				for(int j = 0;j < psize;j++)
				{
					pts[j] = points->at(j);
				}
				_int64 drawColor = lineColor;
				int width = (int)(m_hScalePixel / 2);
                if (lColor != lineColor)
                {
					drawColor = lColor;
                }
				switch (lineStyle)
                {
                    case PolylineStyle_Cycle:
						{
							int ew = (width - 1) > 0 ? (width - 1) : 1;
							int psize = (int)points->size();
							for (int j = 0; j < psize; j++)
							{
								POINT point = (*points)[j];
								RECT pRect = {point.x - ew / 2,
									point.y - ew / 2, point.x + ew / 2, point.y + ew / 2};
								paint->DrawEllipse(drawColor, 1, 0, pRect);
							}
							break;
						}
                    case PolylineStyle_DashLine:
                        {
							paint->DrawPolyline(lColor, (float)lineWidth, 1, pts, (int)points->size());
                            break;
                        }
                    case PolylineStyle_DotLine:
                        {
							paint->DrawPolyline(lColor, (float)lineWidth, 2, pts, (int)points->size());
                            break;
                        }
                    case PolylineStyle_SolidLine:
                        {
							paint->DrawPolyline(lColor, (float)lineWidth, 0, pts, (int)points->size());
                            break;
                        }
                }
				delete[] pts;
				pts = 0;
				if (fillColor != COLOR_EMPTY)
                {
                    int zy = (int)GetY(div, 0, attachVScale);
                    int th = div->GetTitleBar()->IsVisible() ? div->GetTitleBar()->GetHeight() : 0;
                    int hh = div->GetHScale()->IsVisible() ? div->GetHScale()->GetHeight() : 0;
                    if (zy < th) zy = th;
                    else if (zy > div->GetHeight() - hh) zy = div->GetHeight() - hh;
					POINT *ptsf = new POINT[points->size() + 2];
					POINT ps = {points->at(0).x, zy};
					POINT pe = {points->at(points->size() - 1).x, zy};
					ptsf[0] = ps;
					ptsf[1] = pe;
					int psize = (int)points->size();
					for(int j = 0; j < psize; j++)
					{
						ptsf[j + 1] = points->at(j);
					}
                    paint->FillPolygon(fillColor, ptsf, (int)points->size() + 2);
					delete[] ptsf;
					ptsf =  0;
                }
                points->clear();
            }
        }
	}

	void CChartMe::OnPaintResizeLine(CPaintMe *paint)
    {
        if (m_hResizeType > 0)
        {
            POINT mp = GetMousePoint();
            vector<CDivMe*> divsCopy = GetDivs();
            vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *div = *sIter;
                if (mp.x < 0) mp.x = 0;
                if (mp.x > GetWidth()) mp.x = GetWidth();
				paint->DrawLine(COLOR::Reverse(paint, div->GetBackColor()), 1, 2, mp.x, 0, mp.x, GetWidth());
            }
        }
        if (m_userResizeDiv)
        {
            POINT mp = GetMousePoint();
            CDivMe *nextCP = 0;
            bool rightP = false;
            vector<CDivMe*> divsCopy = GetDivs();
            vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(;sIter != divsCopy.end();++sIter)
			{
				CDivMe *cDiv = *sIter;
                if (rightP)
                {
                    nextCP = cDiv;
                    break;
                }
                if (cDiv == m_userResizeDiv)
                {
                    rightP = true;
                }
            }
            bool drawFlag = false;
			RECT uRect = m_userResizeDiv->GetBounds();
            if (mp.x >= uRect.left && mp.x <= uRect.right && mp.y >= uRect.top && mp.y <= uRect.bottom)
            {
                drawFlag = true;
            }
            else
            {
                if (nextCP)
                {
					RECT nRect = nextCP->GetBounds();
					if (mp.x >= nRect.left && mp.x <= nRect.right && mp.y >= nRect.top && mp.y <= nRect.bottom)
					{
                    	drawFlag = true;
					}
                }
            }
            if (drawFlag)
            {
                paint->DrawLine(COLOR::Reverse(paint, m_userResizeDiv->GetBackColor()), 1, 2, 0, mp.y, GetWidth(), mp.y);
            }
        }
    }

	void CChartMe::OnPaintSelectArea(CPaintMe *paint, CDivMe *div)
    {
		CSelectAreaMe *selectArea = div->GetSelectArea();
        if (selectArea->IsVisible())
        {
            RECT bounds = selectArea->GetBounds();
			if(selectArea->AllowUserPaint())
			{
				selectArea->OnPaint(paint, div, bounds);
			}
			else
			{
				if ((bounds.right - bounds.left) >= 5 && (bounds.bottom - bounds.top) >= 5)
				{
					paint->FillRect(selectArea->GetBackColor(), bounds);
					paint->DrawRect(selectArea->GetLineColor(), 1, 0, bounds);
				}
			}
        }
    }

	void CChartMe::OnPaintShapes(CPaintMe *paint, CDivMe *div)
    {
		vector<CBaseShapeMe*> sortedBs = div->GetShapes(SORTTYPE_ASC);
        vector<CBaseShapeMe*>::iterator sIter = sortedBs.begin();
		for(;sIter != sortedBs.end();++sIter)
        {
			CBaseShapeMe *bShape = *sIter;
			if (!bShape->IsVisible() || (div->GetVScale(bShape->GetAttachVScale())->GetVisibleMax() - div->GetVScale(bShape->GetAttachVScale())->GetVisibleMin()) == 0)
            {
                continue;
            }
			if(bShape->AllowUserPaint())
			{
				RECT rect = {0, 0, div->GetWidth(), div->GetHeight()};
				bShape->OnPaint(paint, div, rect);
			}
			else
			{
				CBarShapeMe *bs = dynamic_cast<CBarShapeMe*>(bShape);
				CCandleShapeMe *cs = dynamic_cast<CCandleShapeMe*>(bShape);
				CPolylineShapeMe *ls = dynamic_cast<CPolylineShapeMe*>(bShape);
				CTextShapeMe *ts = dynamic_cast<CTextShapeMe*>(bShape);
				if (ls)
				{
					OnPaintPolyline(paint, div, ls);
				}
				else if(ts)
				{
					OnPaintText(paint, div, ts);
				}
				else if(bs)
				{
					OnPaintBar(paint, div, bs);
				}
				else if (cs)
				{
					OnPaintCandle(paint, div, cs);
				}
			}
        }
    }

	void CChartMe::OnPaintText(CPaintMe *paint, CDivMe *div, CTextShapeMe *ts)
	{
		String drawText = ts->GetText();
		if (drawText.length() == 0)
        {
            return;
        }
		int ciFieldName = m_dataSource->GetColumnIndex(ts->GetFieldName());
		int ciClr = m_dataSource->GetColumnIndex(ts->GetColorField());
		int ciStyle = m_dataSource->GetColumnIndex(ts->GetStyleField());
		for (int i = m_firstVisibleIndex; i <= m_lastVisibleIndex; i++)
        {
			int style = 0;
			if (ciStyle != -1)
			{
				double defineStyle = m_dataSource->Get3(i, ciStyle);
				if (!m_dataSource->IsNaN(defineStyle))
				{
					style = (int)defineStyle;
				}
			}
			if (style == -10000)
			{
				continue;
			}
			double value = m_dataSource->Get3(i, ciFieldName);
			if (!m_dataSource->IsNaN(value))
			{
				int scaleX = (int)GetX(i);
				int y = (int)GetY(div, value, ts->GetAttachVScale());
				_int64 textColor = ts->GetForeColor();
				if (ciClr != -1)
				{
					double defineColor = m_dataSource->Get3(i, ciClr);
					if(!m_dataSource->IsNaN(defineColor))
					{
						textColor = (_int64)defineColor;
					}
				}
				SIZE tSize = paint->TextSize(drawText.c_str(), ts->GetFont());
				DrawText(paint, drawText.c_str(), textColor, ts->GetFont(), scaleX - tSize.cx / 2, y - tSize.cy / 2);
			}
		}
	}

	void CChartMe::OnPaintTitle(CPaintMe *paint, CDivMe *div)
    {
		CTitleBarMe *titleBar = div->GetTitleBar();
		int width = div->GetWidth(), height = div->GetHeight();
        if (titleBar->IsVisible())
        {
			RECT tbRect = {0, 0, width, height};
			if(titleBar->AllowUserPaint())
			{
				titleBar->OnPaint(paint, div, tbRect);
			}
			else
			{
				int titleLeftPadding = m_leftVScaleWidth;
				int rightPadding = width - m_rightVScaleWidth - 2;
				SIZE divNameSize = paint->TextSize(titleBar->GetText().c_str(), titleBar->GetFont());
				if (titleLeftPadding + divNameSize.cx <= width - m_rightVScaleWidth)
				{
					DrawText(paint, titleBar->GetText().c_str(), titleBar->GetForeColor(), titleBar->GetFont(), titleLeftPadding, 2);
				}
				titleLeftPadding += divNameSize.cx + 2;
				if (m_firstVisibleIndex >= 0 && m_lastVisibleIndex >= 0)
				{
					int displayIndex = m_lastVisibleIndex;
					if(displayIndex > m_lastUnEmptyIndex)
					{
						displayIndex = m_lastUnEmptyIndex;
					}
					if (m_showCrossLine)
					{
						if (m_crossStopIndex <= m_lastVisibleIndex)
						{
							displayIndex = m_crossStopIndex;
						}
						if (m_crossStopIndex < 0)
						{
							displayIndex = 0;
						}
						if (m_crossStopIndex >= m_lastVisibleIndex)
						{
							displayIndex = m_lastVisibleIndex;
						}
					}
					int curLength = 1;
					int tTop = 2;
					vector<CTitleMe*> titles = titleBar->Titles;
					vector<CTitleMe*>::iterator sIter = titles.begin();
					wchar_t *showTitle = 0;
					for(;sIter != titles.end();++sIter)
					{
						CTitleMe *title = *sIter;
						if (!title->IsVisible() || title->GetFieldTextMode() == TextMode_None)
						{
							continue;
						}
						showTitle = L"";
						wchar_t p[100] = {0};
						wchar_t digitStr[100] = {0};
						wchar_t p2[100] = {0};
						double value = m_dataSource->Get2(displayIndex, title->GetFieldName());
						if (m_dataSource->IsNaN(value))
						{
							value = 0;
						}
						if (title->GetFieldTextMode() != TextMode_Value)
						{
							CStrMe::Contact(p, title->GetFieldText().c_str(), title->GetFieldTextSeparator().c_str(), L"");
							showTitle = p;
						}
						if (title->GetFieldTextMode() != TextMode_Field)
						{
							if (!m_dataSource->IsNaN(value))
							{
								int digit = title->GetDigit();
								CStrMe::GetValueByDigit(value, digit, digitStr);
								CStrMe::Contact(p2, showTitle, digitStr, L"");
								showTitle = p2;
							}
						}
						SIZE conditionSize = paint->TextSize(showTitle, titleBar->GetFont());
						if (titleLeftPadding + conditionSize.cx + 8 > rightPadding)
						{
							curLength++;
							if (curLength <= titleBar->GetMaxLine())
							{
								tTop += conditionSize.cy + 2;
								titleLeftPadding = m_leftVScaleWidth;
								rightPadding = width - m_rightVScaleWidth;
							}
							else
							{
								break;
							}
							if (tTop + conditionSize.cy >= div->GetHeight() - div->GetHScale()->GetHeight())
							{
								break;
							}
						}
						if (titleLeftPadding <= rightPadding)
						{
							DrawText(paint, showTitle, title->GetTextColor(), titleBar->GetFont(), titleLeftPadding, tTop);
							titleLeftPadding += conditionSize.cx + 8;
						}
					}
				}
			}
        }
    }

    void CChartMe::OnPaintToolTip(CPaintMe *paint)
    {
        if (!m_showingToolTip)
        {
            return;
        }
		CBaseShapeMe *bs = SelectShape(GetMouseOverIndex(), 0);
        if (bs)
        {
            POINT mouseP = GetMousePoint();
            CDivMe *mouseOverDiv = GetMouseOverDiv();
            int digit = mouseOverDiv->GetVScale(bs->GetAttachVScale())->GetDigit();
            if (!mouseOverDiv) return;
            int index = GetIndex(mouseP);
            if (index < 0) return;
			CToolTipMe *toolTip = mouseOverDiv->GetToolTip();
			if(toolTip->AllowUserPaint())
			{
				RECT toolRect = {0, 0, GetWidth(), GetHeight()};
				toolTip->OnPaint(paint, mouseOverDiv, toolRect);
				return;
			}
            int pWidth = 0;
            int pHeight = 0;
			FONT *toolTipFont = toolTip->GetFont();
            double xValue = m_dataSource->GetXValue(index);
			int sLeft = mouseOverDiv->GetLeft(), sTop = mouseOverDiv->GetTop();
			for(int t = 0; t < 2; t++)
			{
				int x = mouseP.x + 10;
				int y = mouseP.y + 2;
				if(t == 0)
				{
					sLeft = x + 2;
					sTop = y;
				}
				SIZE xValueSize = {0};
				if (mouseOverDiv->GetHScale()->GetHScaleType() == HScaleType_Date)
				{
					wchar_t formatDate[100] = {0};
					CStrMe::GetFormatDate(xValue, formatDate);
					wchar_t p1[100] = {0};
					CStrMe::Contact(p1, m_hScaleFieldText.c_str(), L":", formatDate);
					xValueSize = paint->TextSize(p1, toolTipFont);
					pHeight = xValueSize.cy;
					if(t == 1)
					{
						DrawText(paint, p1, toolTip->GetForeColor(), toolTipFont, sLeft, sTop);
					}
				}
				else if (mouseOverDiv->GetHScale()->GetHScaleType() == HScaleType_Number)
				{
					wchar_t p2[100] = {0};
					wchar_t xValueStr[20] = {0};
					_stprintf_s(xValueStr, 19, L"%d", (int)xValue);
					CStrMe::Contact(p2,m_hScaleFieldText.c_str(), L":", xValueStr);
					xValueSize = paint->TextSize(p2, toolTipFont);
					pHeight = xValueSize.cy;
					if(t == 1)
					{
						DrawText(paint, p2, toolTip->GetForeColor(), toolTipFont, sLeft ,sTop);
					}
				}
				sTop += xValueSize.cy;
				int fieldsLength = 0;
				int *fields = bs->GetFields(&fieldsLength);
				if (fieldsLength > 0)
				{
					for (int i = 0; i < fieldsLength; i++)
					{
						String fieldText = bs->GetFieldText(fields[i]);
						double value = 0;
						if(index>=0)
						{
							value = m_dataSource->Get2(index, fields[i]);
						}
						wchar_t valueDigit[100] = {0};
						CStrMe::GetValueByDigit(value, digit, valueDigit);
						wchar_t p[100] = {0};
						CStrMe::Contact(p, fieldText.c_str(), L":", valueDigit);
						if(t == 1)
						{
							DrawText(paint, p, toolTip->GetForeColor(), toolTipFont, sLeft, sTop);
						}
						SIZE strSize = paint->TextSize(p, toolTipFont);
						if(i == 0)
						{
							pWidth = xValueSize.cx;
						}
						if(xValueSize.cx > pWidth)
						{
							pWidth = xValueSize.cx;
						}
						if(strSize.cx > pWidth)
						{
							pWidth = strSize.cx;
						}
						sTop += strSize.cy;
						pHeight += strSize.cy;
					}
				}
				if(fields)
				{
					delete[] fields;
					fields = 0;
				}
				if(t == 0)
				{
					int width = GetWidth(), height = GetHeight();
					pWidth += 4;
					pHeight += 1;
					if (x + pWidth > width)
					{
						x = width - pWidth;
						if (x < 0)
						{
							x = 0;
						}
					}
					if (y + pHeight > height)
					{
						y = height - pHeight;
						if (y < 0)
						{
							y = 0;
						}
					}
					sLeft = x;
					sTop = y;
					int rectPX = x, rectPY = y, rectPW = pWidth, rectPH = pHeight;
					if (rectPW > 0 && rectPH > 0)
					{
						RECT rectP = {rectPX, rectPY, rectPX + rectPW, rectPY + rectPH};
						paint->FillRect(toolTip->GetBackColor(), rectP);
						paint->DrawRect(toolTip->GetBorderColor(), 1, 0, rectP);
					}
				}
			}
        }
    }

	void CChartMe::OnPaintVScale(CPaintMe *paint, CDivMe *div)
	{
		int divBottom = div->GetHeight();
		vector<int> gridYList;
        bool leftGridIsShow = false;
		int width = GetWidth();
        if (m_leftVScaleWidth > 0)
        {
			CVScaleMe *leftVScale = div->GetLeftVScale();
			CScaleGridMe *hGrid = div->GetHGrid();
			bool paintV = true, paintG = true;
			if(leftVScale->AllowUserPaint())
			{
				RECT leftVRect = {0, 0, m_leftVScaleWidth, divBottom};
				leftVScale->OnPaint(paint, div, leftVRect);
				paintV = false;
			}
			if(hGrid->AllowUserPaint())
			{
				RECT hGridRect = {0, 0, width, divBottom};
				hGrid->OnPaint(paint, div, hGridRect);
				paintG = false;
			}
			if(paintV || paintG)
			{
				if (paintV && m_leftVScaleWidth <= width)
				{
					paint->DrawLine(leftVScale->GetScaleColor(), 1, 0, m_leftVScaleWidth, 0, m_leftVScaleWidth, divBottom - div->GetHScale()->GetHeight());
				}
				FONT *leftYFont = leftVScale->GetFont();
				SIZE leftYSize = paint->TextSize(L" ", leftYFont);
				double min = leftVScale->GetVisibleMin();
				double max = leftVScale->GetVisibleMax();
				if (min == 0 && max == 0)
				{
					CVScaleMe *rightVScale = div->GetRightVScale();
					if (rightVScale->GetVisibleMin() != 0 || rightVScale->GetVisibleMax() != 0)
					{
						min = rightVScale->GetVisibleMin();
						max = rightVScale->GetVisibleMax();
					}
				}
				vector<double> scaleStepList = leftVScale->GetScaleSteps();
				if(scaleStepList.size() == 0)
				{
					scaleStepList = GetVScaleStep(max, min, div, leftVScale);
				}
				float lY = -1;
				int stepSize = (int)scaleStepList.size();
				for (int i = 0; i < stepSize; i++)
				{
					double lValue = scaleStepList.at(i) / leftVScale->GetMagnitude();
					if (lValue != 0 && leftVScale->GetType() == VScaleType_Percent)
					{
						double baseValue = GetVScaleBaseValue(div, leftVScale, m_firstVisibleIndex) / leftVScale->GetMagnitude();
						lValue = 100 * (lValue - baseValue * leftVScale->GetMagnitude()) / lValue;
					}
					wchar_t *numberStr = 0;
					wchar_t number[100] = {0};
					CStrMe::GetValueByDigit(lValue, leftVScale->GetDigit(), number);
					numberStr = number;
					wchar_t p[100] = {0};
					if (leftVScale->GetType() == VScaleType_Percent)
					{
						CStrMe::Contact(p, numberStr, L"%", L"");
						numberStr = p;
					}
					int y = (int)GetY(div, scaleStepList.at(i), AttachVScale_Left);
					leftYSize = paint->TextSize(numberStr, leftYFont);
					if (y - leftYSize.cy / 2 < 0 || y + leftYSize.cy / 2 > divBottom)
					{
						continue;
					}
					if (hGrid->IsVisible() && paintG)
					{
						leftGridIsShow = true;
						if(find(gridYList.begin(), gridYList.end(), y) == gridYList.end())
						{
							gridYList.push_back(y);
							paint->DrawLine(hGrid->GetGridColor(), 1, hGrid->GetLineStyle(), m_leftVScaleWidth, y, width - m_rightVScaleWidth, y);
						}
					}
					if(paintV)
					{
						DrawThinLine(paint, leftVScale->GetScaleColor(), 1, m_leftVScaleWidth - 4, y, m_leftVScaleWidth, y);
						if (leftVScale->IsReverse())
						{
							if (lY != -1 && y - leftYSize.cy / 2 < lY)
							{
								continue;
							}
							lY = y + (float)leftYSize.cy / 2;
						}
						else
						{
							if (lY != -1 && y + leftYSize.cy / 2 > lY)
							{
								continue;
							}
							lY = y - (float)leftYSize.cy / 2;
						}
						_int64 scaleForeColor = leftVScale->GetForeColor();
						_int64 scaleForeColor2 = leftVScale->GetForeColor2();
						if (scaleForeColor2 != COLOR_EMPTY && scaleStepList[i] < leftVScale->GetMidValue())
						{
							scaleForeColor = scaleForeColor2;
						}
						if (leftVScale->GetType() != VScaleType_Percent && leftVScale->GetNumberStyle() == NumberStyle_Underline)
						{
							vector<String> splits = CStrMe::Split(numberStr, L".");
							if (splits.size() >= 1)
							{
								DrawText(paint, splits[0].c_str(), scaleForeColor, leftYFont, m_leftVScaleWidth - 10 - leftYSize.cx, y - leftYSize.cy / 2);
							}
							if (splits.size() >= 2)
							{
								SIZE decimalSize = paint->TextSize(splits[0].c_str(), leftYFont);
								SIZE size2 = paint->TextSize(splits[1].c_str(), leftYFont);
								DrawText(paint, splits[1].c_str(), scaleForeColor, leftYFont, m_leftVScaleWidth - 10 - leftYSize.cx
									+ decimalSize.cx, y - leftYSize.cy / 2);
								DrawThinLine(paint, scaleForeColor, 1, m_leftVScaleWidth - 10 - leftYSize.cx
								+ decimalSize.cx, y + leftYSize.cy / 2,
								m_leftVScaleWidth - 10 - leftYSize.cx + decimalSize.cx + size2.cx - 1, y + leftYSize.cy / 2);
							}
						}
						else
						{
							DrawText(paint, numberStr, scaleForeColor, leftYFont, m_leftVScaleWidth - 10 - leftYSize.cx, y - leftYSize.cy / 2);
						}
						if (leftVScale->GetType() == VScaleType_GoldenRatio)
						{
							String goldenRatio = L"";
							if (i == 1) goldenRatio = L"19.1%";
							else if (i == 2) goldenRatio = L"38.2%";
							else if (i == 4) goldenRatio = L"61.8%";
							else if (i == 5) goldenRatio = L"80.9%";
							if ((int)goldenRatio.length() > 0)
							{
								SIZE goldenRatioSize = paint->TextSize(goldenRatio.c_str(), leftYFont);
								DrawText(paint, goldenRatio.c_str(), scaleForeColor, leftYFont, m_leftVScaleWidth - 10 - goldenRatioSize.cx, y + leftYSize.cy / 2);
							}
						}
					}
				}
				if (leftVScale->GetMagnitude() != 1 && paintV)
				{
					wchar_t magnitude[100] = {0};
					_stprintf_s(magnitude, 99, L"%d", leftVScale->GetMagnitude());
					wchar_t str[100] = {0};
					CStrMe::Contact(str, L"X", magnitude, L"");
					SIZE sizeF = paint->TextSize(str, leftYFont);
					int x = m_leftVScaleWidth - sizeF.cx - 6;
					int y = div->GetHeight() - div->GetHScale()->GetHeight() - sizeF.cy - 2;
					RECT rectL = {x - 1, y - 1, x + sizeF.cx, y + sizeF.cy};
					paint->DrawRect(leftVScale->GetScaleColor(), 1, 0, rectL);
					DrawText(paint, str, leftVScale->GetForeColor(), leftYFont, x, y);
				}
			}
        }
        if (m_rightVScaleWidth > 0)
        {
			CVScaleMe *rightVScale = div->GetRightVScale();
			CScaleGridMe *hGrid = div->GetHGrid();
			bool paintV = true, paintG = true;
			if(rightVScale->AllowUserPaint())
			{
				RECT leftVRect = {width - m_rightVScaleWidth, 0, width, divBottom};
				rightVScale->OnPaint(paint, div, leftVRect);
				paintV = false;
			}
			if(hGrid->AllowUserPaint())
			{
				RECT hGridRect = {0, 0, width, divBottom};
				hGrid->OnPaint(paint, div, hGridRect);
				paintG = false;
			}
			if(paintV || paintG)
			{
				if (paintV && width - m_rightVScaleWidth >= m_leftVScaleWidth)
				{
					paint->DrawLine(rightVScale->GetScaleColor(), 1, 0, width - m_rightVScaleWidth, 0,width - m_rightVScaleWidth, divBottom - div->GetHScale()->GetHeight());
				}
				FONT *rightYFont = rightVScale->GetFont();
				SIZE rightYSize = paint->TextSize(L" ", rightYFont);
				double min = rightVScale->GetVisibleMin();
				double max = rightVScale->GetVisibleMax();
				if (min == 0 && max == 0)
				{
					CVScaleMe *leftVScale = div->GetLeftVScale();
					if (leftVScale->GetVisibleMin() != 0 || leftVScale->GetVisibleMax() != 0)
					{
						min = leftVScale->GetVisibleMin();
						max = leftVScale->GetVisibleMax();
					}
				}
				vector<double> scaleStepList = rightVScale->GetScaleSteps();
				if(scaleStepList.size() == 0)
				{
					scaleStepList = GetVScaleStep(max, min, div, rightVScale);
				}
				float lY = -1;
				int stepSize = (int)scaleStepList.size();
				for (int i = 0; i < stepSize; i++)
				{
					double rValue = scaleStepList.at(i) / rightVScale->GetMagnitude();
					if (rValue != 0 && rightVScale->GetType() == VScaleType_Percent)
					{
						double baseValue = GetVScaleBaseValue(div, rightVScale, m_lastVisibleIndex) / rightVScale->GetMagnitude();
						rValue = 100 * (rValue - baseValue * rightVScale->GetMagnitude()) / rValue;
					}
					wchar_t *numberStr = 0;
					wchar_t number[100] = {0};
					CStrMe::GetValueByDigit(rValue, rightVScale->GetDigit(), number);
					numberStr = number;
					wchar_t p[100] = {0};
					if (rightVScale->GetType() == VScaleType_Percent)
					{
						CStrMe::Contact(p, numberStr, L"%", L"");
						numberStr = p;
					}
					int y = (int)GetY(div, scaleStepList.at(i), AttachVScale_Right);
					rightYSize = paint->TextSize(numberStr, rightYFont);
					if (y - rightYSize.cy / 2 < 0 || y + rightYSize.cy / 2 > divBottom)
					{
						continue;
					}
					if (hGrid->IsVisible() && paintG && !leftGridIsShow)
					{
						if(find(gridYList.begin(), gridYList.end(), y) == gridYList.end())
						{
							gridYList.push_back(y);
							paint->DrawLine(hGrid->GetGridColor(), 1, hGrid->GetLineStyle(), m_leftVScaleWidth, y, width - m_rightVScaleWidth, y);
						}
					}
					if(paintV)
					{
						DrawThinLine(paint, rightVScale->GetScaleColor(), 1, width - m_rightVScaleWidth, y, width - m_rightVScaleWidth + 4, y);
						if (rightVScale->IsReverse())
						{
							if (lY != -1 && y - rightYSize.cy / 2 < lY)
							{
								continue;
							}
							lY = y + (float)rightYSize.cy / 2;
						}
						else
						{
							if (lY != -1 && y + rightYSize.cy / 2 > lY)
							{
								continue;
							}
							lY = y - (float)rightYSize.cy / 2;
						}
						_int64 scaleForeColor = rightVScale->GetForeColor();
						_int64 scaleForeColor2 = rightVScale->GetForeColor2();
						if (scaleForeColor2 != COLOR_EMPTY && scaleStepList[i] < rightVScale->GetMidValue())
						{
							scaleForeColor = scaleForeColor2;
						}
						if (rightVScale->GetType() != VScaleType_Percent && rightVScale->GetNumberStyle() == NumberStyle_Underline)
						{
							vector<String> splits = CStrMe::Split(numberStr, L".");
							if (splits.size() >= 1)
							{
								DrawText(paint, splits[0].c_str(), scaleForeColor, rightYFont, width - m_rightVScaleWidth + 10,
								y - rightYSize.cy / 2);
							}
							if (splits.size() >= 2)
							{
								SIZE decimalSize = paint->TextSize(splits[0].c_str(), rightYFont);
								SIZE size2 = paint->TextSize(splits[1].c_str(), rightYFont);
								DrawText(paint, splits[1].c_str(), scaleForeColor, rightYFont, width - m_rightVScaleWidth + 10
									+ decimalSize.cx, y - rightYSize.cy / 2);
								DrawThinLine(paint, scaleForeColor, 1, width - m_rightVScaleWidth + 10
								+ decimalSize.cx, y + rightYSize.cy / 2,
								width - m_rightVScaleWidth + 10 + decimalSize.cx + size2.cx - 1, y + rightYSize.cy / 2);
							}
						}
						else
						{
							DrawText(paint, numberStr, scaleForeColor, rightYFont, width - m_rightVScaleWidth + 10,
							y - rightYSize.cy / 2);
						}
						if (rightVScale->GetType() == VScaleType_GoldenRatio)
						{
							String goldenRatio = L"";
							if (i == 1) goldenRatio = L"19.1%";
							else if (i == 2) goldenRatio = L"38.2%";
							else if (i == 4) goldenRatio = L"61.8%";
							else if (i == 5) goldenRatio = L"80.9%";
							if ((int)goldenRatio.length() > 0)
							{
								DrawText(paint, goldenRatio.c_str(), scaleForeColor, rightYFont, width - m_rightVScaleWidth + 10,
								y + rightYSize.cy / 2);
							}
						}
					}
				}
				if (rightVScale->GetMagnitude() != 1 && paintV)
				{
					wchar_t magnitude[100] = {0};
					_stprintf_s(magnitude, 99, L"%d", rightVScale->GetMagnitude());
					wchar_t str[100] = {0};
					CStrMe::Contact(str, L"X", magnitude, L"");
					SIZE sizeF = paint->TextSize(str, rightYFont);
					int x = width - m_rightVScaleWidth + 6;
					int y = div->GetHeight() - div->GetHScale()->GetHeight() - sizeF.cy - 2;
					RECT rectR = {x - 1, y - 1, x + sizeF.cx, y + sizeF.cy};
					paint->DrawRect(rightVScale->GetScaleColor(), 1, 0, rectR);
					DrawText(paint, str, rightVScale->GetForeColor(), rightYFont, x, y);
				}
			}
        }
    }

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	void CChartMe::CorrectVisibleRecord(int dataCount, int *first, int *last)
	{
		if (dataCount > 0)
		{
			if (*first == -1)
			{
				*first = 0;
			}
			if (*last == -1)
			{
				*last = 0;
			}
			if (*first > *last)
			{
				*first = *last;
			}
			if (*last < *first)
			{
				*last = *first;
			}
		}
		else
		{
			*first = -1;
			*last = -1;
		}
	}

	void CChartMe::GetCandleMaxStringPoint(float scaleX, float scaleY, float stringWidth, float stringHeight, int actualWidth,
		int leftVScaleWidth, int rightVScaleWidth, float *x, float *y)
	{
		if(scaleX < leftVScaleWidth + stringWidth)
		{
			*x = scaleX;
		}
		else if(scaleX > actualWidth - rightVScaleWidth - stringWidth)
		{
			*x = scaleX - stringWidth;
		}
		else
		{
			if(scaleX < actualWidth / 2)
			{
				*x = scaleX - stringWidth;
			}
			else
			{
				*x = scaleX;
			}
		}
		*y = scaleY + stringHeight / 2;
	}


	void CChartMe::GetCandleMinStringPoint(float scaleX, float scaleY, float stringWidth, float stringHeight, int actualWidth,
		int leftVScaleWidth, int rightVScaleWidth, float *x, float *y)
	{
		if(scaleX < leftVScaleWidth + stringWidth)
		{
			*x = scaleX;
		}
		else if(scaleX > actualWidth - rightVScaleWidth - stringWidth)
		{
			*x = scaleX - stringWidth;
		}
		else
		{
			if(scaleX < actualWidth / 2)
			{
				*x = scaleX - stringWidth;
			}
			else
			{
				*x = scaleX;
			}
		}
		*y = scaleY - stringHeight * 3 / 2;
	}

	int CChartMe::GetChartIndex(int x, int leftScaleWidth, double hScalePixel, int firstVisibleIndex)
	{
		return (int)((x - leftScaleWidth) / hScalePixel + firstVisibleIndex);
	}

	float CChartMe::GetUpCandleHeight(double close, double open, double max, double min, float divPureV)
	{
		if(close-open == 0)
		{
			return 1;
		}
		else
		{
			return (float)((close - open) / (max - min) * divPureV);
		}
	}

	float CChartMe::GetDownCandleHeight(double close, double open, double max, double min, float divPureV)
	{
		if(close - open == 0)
		{
			return 1;
		}
		else
		{
			return (float)((open - close) / (max - min) * divPureV);
		}
	}

	void CChartMe::ScrollLeft(int step, int dateCount, double hScalePixel, int pureH, int *fIndex, int *lIndex)
	{
		int max = GetMaxVisibleCount(hScalePixel, pureH);
		int right = -1;
		if(dateCount > max)
		{
			right = max - (*lIndex - *fIndex);
			if(right > 1)
			{
				*fIndex = *lIndex - max + 1;
				if(*fIndex > *lIndex)
				{
					*fIndex = *lIndex;
				}
			}
			else
			{
				if(*fIndex-step >= 0)
				{
					*fIndex = *fIndex - step;
					*lIndex = *lIndex - step;
				}
				else
				{
					if(*fIndex != 0)
					{
						*lIndex = *lIndex - *fIndex;
						*fIndex = 0;
					}
				}
			}
		}
	}

	void CChartMe::ScrollRight(int step, int dataCount, double hScalePixel, int pureH, int *fIndex, int *lIndex)
	{
		int max = GetMaxVisibleCount(hScalePixel, pureH);
		if(dataCount > max)
		{
			if(*lIndex < dataCount-1)
			{
				if(*lIndex + step>dataCount-1)
				{
					*fIndex = *fIndex + dataCount - *lIndex;
					*lIndex = dataCount-1;
				}
				else
				{
					*fIndex = *fIndex + step;
					*lIndex = *lIndex + step;
				}
			}
			else
			{
				*fIndex = *lIndex - (int)(max * 0.9);
				if(*fIndex > *lIndex)
				{
					*fIndex = *lIndex;
				}
			}
		}
	}

	double CChartMe::GetVScaleValue(int y, double max, double min, float vHeight)
	{
		double every = (max - min) / vHeight;
		return max - y * every;
	}

	int CChartMe::ResetCrossOverIndex(int dataCount, int maxVisibleRecord, int crossStopIndex, int firstL, int lastL)
	{
		if(dataCount > 0 && dataCount >= maxVisibleRecord)
		{
			if(crossStopIndex < firstL)
			{
				crossStopIndex = firstL;
			}
			if(crossStopIndex > lastL)
			{
				crossStopIndex = lastL;
			}
		}
		return crossStopIndex;
	}

	void CChartMe::Update()
	{
		if(!GetNative())
		{
			return;
		}
		RECT bounds = GetBounds();
		int width = bounds.right - bounds.left;
		int height = bounds.bottom - bounds.top;
		m_workingAreaWidth = width - m_leftVScaleWidth - m_rightVScaleWidth - m_blankSpace - 1;
		if(m_workingAreaWidth < 0)
		{
			m_workingAreaWidth = 0;
		}
        int locationY = 0;
        float sumPercent = 0;
        vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(;sIter != divsCopy.end();++sIter)
		{
			CDivMe *div = *sIter;
            sumPercent += div->GetVerticalPercent();
        }
        if (sumPercent > 0)
        {
            sIter = divsCopy.begin();
			for(; sIter != divsCopy.end(); ++sIter)
			{
				CDivMe *cDiv = *sIter;
				RECT rect = {0, locationY, width, locationY + (int)(height * cDiv->GetVerticalPercent() / sumPercent)};
				cDiv->SetBounds(rect);
                cDiv->SetWorkingAreaHeight(cDiv->GetHeight() - cDiv->GetHScale()->GetHeight() - cDiv->GetTitleBar()->GetHeight() - 1);
				cDiv->SetPx(GetLeft());
				cDiv->SetPy(locationY);
                locationY += (int)(height * cDiv->GetVerticalPercent() / sumPercent);
            }
        }
		Reset();
	}


	void CChartMe::ZoomIn(int pureH, int dataCount, int *findex, int *lindex, double *hScalePixel)
	{
		int max = -1;
		if(*hScalePixel > 1)
		{
			*hScalePixel -=2 ;
		}
		else
		{
			*hScalePixel = *hScalePixel * 2 / 3;
		}
		max = GetMaxVisibleCount(*hScalePixel, pureH);
		if(max >= dataCount)
		{
			if(*hScalePixel < 1)
			{
				*hScalePixel = (double)pureH / dataCount;
			}
			*findex = 0;
			*lindex = dataCount - 1;
		}
		else
		{
			*findex = *lindex - max + 1;
			if(*findex < 0)
			{
				*findex = 0;
			}
		}
	}

	void CChartMe::ZoomOut(int pureH, int dataCount, int *findex, int *lindex, double *hScalePixel)
	{
		int oriMax = -1, max = -1, deal = 0;
		if(*hScalePixel < 30)
		{
			oriMax = GetMaxVisibleCount(*hScalePixel,  pureH);
			if(dataCount < oriMax)
			{
				deal = 1;
			}
			if(*hScalePixel >= 1)
			{
				*hScalePixel += 2;
			}
			else
			{
				*hScalePixel = *hScalePixel * 1.5;
				if(*hScalePixel > 1)
				{
					*hScalePixel = 1;
				}
			}
			max = GetMaxVisibleCount(*hScalePixel, pureH);
			if(dataCount >= max)
			{
				if(deal == 1)
				{
					*lindex = dataCount - 1;
				}
				*findex = *lindex - max + 1;
				if(*findex < 0)
				{
					*findex = 0;
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void CChartMe::OnKeyDown(char key)
	{
		CControlMe::OnKeyDown(key);
		CControlHostMe *host = GetNative()->GetHost();
		if(!host->IsKeyPress(VK_CONTROL)
		&& !host->IsKeyPress(VK_MENU)
		&& !host->IsKeyPress(VK_SHIFT))
		{
			m_isMouseMove = false;
			m_showingToolTip = false;
			ScrollType operatorType = ScrollType_None;
			switch (key)
			{
				case 37:
					if(m_reverseHScale)
						operatorType = ScrollType_Right;
					else
						operatorType = ScrollType_Left;
					break;
				case 39:
					if(m_reverseHScale)
						operatorType = ScrollType_Left;
					else
						operatorType = ScrollType_Right;
					break;
				case 38:
					operatorType = ScrollType_ZoomOut;
					break;
				case 40:
					operatorType = ScrollType_ZoomIn;
					break;
				case 27:
					vector<CDivMe*> divsCopy = GetDivs();
					if (divsCopy.size() > 0)
					{
						ClearSelectedDiv();
						Invalidate();
					}
					break;
			}
			if (operatorType != ScrollType_None)
			{
				ChangeChart(operatorType, 1);
				return;
			}
		}
	}

	void CChartMe::OnLoad()
	{
		CControlMe::OnLoad();
		StartTimer(m_timerID, 50);
		if(!m_dataSource)
		{
			m_dataSource = new CTableMe();
		}
	}

	void CChartMe::OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CControlMe::OnMouseDown(mp, button, clicks, delta); 
		if(button == MouseButtonsMe_Left && clicks == 2)
		{
			ClearSelectedShape();
			m_showCrossLine = !m_showCrossLine;
			Invalidate();
			return;
		}
		int width = GetWidth();
        m_userResizeDiv = 0;
        int shapeCount = !GetSelectedShape() ? 0 : 1;
		vector<CDivMe*> divsCopy = GetDivs();
        m_hResizeType = 0;
        if (button == MouseButtonsMe_Left)
        {
            ClearSelectedPlot();
            vector<CDivMe*>::iterator sIter = divsCopy.begin();
			CDivMe *mouseOverDiv = GetMouseOverDiv();
			for(; sIter != divsCopy.end(); ++sIter)
			{
				CDivMe *div = *sIter;
                if (div == mouseOverDiv)
                {
                    div->SetSelected(true);
                }
                else
                {
                    div->SetSelected(false);
                }
            }
			if (clicks == 1)
            {
                CloseSelectArea();
                m_crossStopIndex = GetMouseOverIndex();
                m_cross_y = mp.y;
				if (m_showCrossLine && m_crossLineMoveMode == CrossLineMoveMode_AfterClick)
                {
                    m_crossStopIndex = GetMouseOverIndex();
                    m_cross_y = mp.y;
                    m_isScrollCross = false;
                }
                if (m_canResizeH)
                {
                    if (mp.x >= m_leftVScaleWidth - 4 && mp.x <= m_leftVScaleWidth + 4)
                    {
                        m_hResizeType = 1;
                        goto OutLoop;
                    }
                    else if (mp.x >= width - m_rightVScaleWidth - 4 && mp.x <= width - m_rightVScaleWidth + 4)
                    {
                        m_hResizeType = 2;
                        goto OutLoop;
                    }
                }
                if (m_canResizeV)
                {
                    int pIndex = 0;
                    sIter = divsCopy.begin();
					for(; sIter != divsCopy.end(); ++sIter)
					{
						CDivMe *cDiv = *sIter;
                        pIndex++;
                        if (pIndex == (int)divsCopy.size())
                        {
                            break;
                        }
						RECT resizeRect = {0, cDiv->GetBottom() - 4, cDiv->GetWidth(), cDiv->GetBottom() + 4};
                        if (mp.x >= resizeRect.left && mp.x <= resizeRect.right
                            && mp.y >= resizeRect.top && mp.y <= resizeRect.bottom)
                        {
                            m_userResizeDiv = cDiv;
                            goto OutLoop;
                        }
                    }
                }
                if ((mp.x >= m_leftVScaleWidth && mp.x <= width - m_rightVScaleWidth))
                {
                    if (mouseOverDiv)
                    {
						vector<CPlotMe*> plotsCopy = mouseOverDiv->GetPlots(SORTTYPE_DESC);
                        vector<CPlotMe*>::iterator sIter = plotsCopy.begin();
						for(; sIter != plotsCopy.end(); ++sIter)
						{
							CPlotMe *lsb = *sIter;
                            if (lsb->IsEnabled() && lsb->IsVisible() && lsb->OnSelect())
                            {
                                m_movingPlot = lsb;
								lsb->OnMoveStart();
								double *zorders = new double[plotsCopy.size()];
								vector<CPlotMe*> plots = mouseOverDiv->GetPlots(SORTTYPE_DESC);
								vector<CPlotMe*>::iterator sIter2 = plots.begin();
								int lstSize = (int)plotsCopy.size();
								for (int j = 0;j < lstSize; j++, sIter2++)
								{
									CPlotMe *plot = *sIter2;
									zorders[j] = plot->GetZOrder();
								}
								lsb->SetZOrder((int)CMathLibMe::GetMax(zorders, (int)plotsCopy.size()) + 1);
								delete[] zorders;
								zorders = 0;
                            }
                        }
                    }
                    if (m_movingPlot)
                    {
                        m_movingPlot->SetSelected(true);
                        if (shapeCount != 0)
                        {
                            ClearSelectedShape();
                        }
                        goto OutLoop;
                    }
                    else
                    {
                        CBaseShapeMe *bs = SelectShape(m_crossStopIndex, 1);
                        CDivMe *div = 0;
                        if (!bs)
                        {
                            div = mouseOverDiv;
                            if (div && div->GetSelectArea()->IsEnabled())
                            {
                                if (mp.y >= div->GetTop() + 2 && mp.y <= div->GetBottom() - div->GetHScale()->GetHeight() - 2)
                                {
									m_showingSelectArea = true;
                                }
                            }
                        }
                    }
                }
            OutLoop: ;
            }
        }
        else
        {
            m_isMouseMove=true;
            m_showingToolTip = false;
        }
        m_lastMouseClickPoint = mp;
        if (GetSelectedShape())
        {
            m_movingShape = GetSelectedShape();
        }
		Invalidate();
	}

	void CChartMe::OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CControlMe::OnMouseMove(mp, button, clicks, delta); 
		if (mp.x != m_lastMouseMovePoint.x || mp.y != m_lastMouseMovePoint.y)
        {
			int width = GetWidth();
            m_isMouseMove = true;
            m_showingToolTip = false;
			vector<CDivMe*> divsCopy = GetDivs();
			vector<CDivMe*>::iterator sIter = divsCopy.begin();
			for(; sIter != divsCopy.end(); ++sIter)
			{
				CDivMe *div = *sIter;
                bool resize = false;
                if (div->GetSelectArea()->IsVisible() && div->GetSelectArea()->CanResize())
                {
                    resize = true;
                }
                else
                {
                    if (m_showingSelectArea)
                    {
                        if (button == MouseButtonsMe_Left)
                        {
                            int subX = m_lastMouseClickPoint.x - m_lastMouseMovePoint.x;
                            int subY = m_lastMouseMovePoint.y - m_lastMouseClickPoint.y;
                            if (abs(subX) > m_hScalePixel * 2 || abs(subY) > m_hScalePixel * 2)
                            {
                                m_showingSelectArea = false;
                                div->GetSelectArea()->SetVisible(true);
                                div->GetSelectArea()->SetCanResize(true);
                                resize = true;
                            }
                        }
                    }
                }
                if (resize && button == MouseButtonsMe_Left)
                {
                    int x1 = m_lastMouseClickPoint.x;
                    int y1 = m_lastMouseClickPoint.y;
                    int x2 = mp.x;
                    int y2 = mp.y;
                    if (x2 < m_leftVScaleWidth)
					{
                        x2 = m_leftVScaleWidth;
					}
                    else if (x2 > width - m_rightVScaleWidth)
					{
                        x2 = width - m_rightVScaleWidth;
					}
                    if (y2 > div->GetBottom() - div->GetHScale()->GetHeight())
					{
                        y2 = div->GetBottom() - div->GetHScale()->GetHeight();
					}
                    else if (y2 < div->GetTop() + div->GetTitleBar()->GetHeight())
					{
                        y2 = div->GetTop() + div->GetTitleBar()->GetHeight();
					}
					int bx = 0, by = 0, bwidth = 0, bheight = 0;
					CMathLibMe::M105(x1, y1 - div->GetTop(), x2, y2 - div->GetTop(), &bx, &by, &bwidth, &bheight);
					RECT bounds = {bx, by, bx + bwidth, by + bheight};
					div->GetSelectArea()->SetBounds(bounds);
                    Invalidate();
                    m_lastMouseMovePoint = mp;
                    return;
                }
                if (div->GetSelectArea()->IsVisible())
                {
                    return;
                }
            }
			SYSTEMTIME t; 
			GetLocalTime(&t); 
			m_lastMouseMoveTime = CMathLibMe::M129(t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,t.wMilliseconds);
            if (m_movingPlot && button == MouseButtonsMe_Left)
            {
                m_movingPlot->OnMoving();
            }
            else
            {
				if (m_canResizeH)
                {
                    if (m_hResizeType == 0)
                    {
                        if ((mp.x >= m_leftVScaleWidth - 4 && mp.x <= m_leftVScaleWidth + 4) ||
                        (mp.x >= width - m_rightVScaleWidth - 4 && mp.x <= width - m_rightVScaleWidth + 4))
                        {
							SetCursor(CursorsMe_SizeWE);
                            goto OutLoop;
                        }
                    }
                    else
                    {
                        SetCursor(CursorsMe_SizeWE);
                        goto OutLoop;
                    }
                }
                if (m_canResizeV)
                {
                    int pIndex = 0;
                    vector<CDivMe*> divsCopy = GetDivs();
					vector<CDivMe*>::iterator sIter = divsCopy.begin();
					for(; sIter != divsCopy.end(); ++sIter)
					{
						CDivMe *cDiv = *sIter;
                        pIndex++;
                        if (pIndex == (int)divsCopy.size())
                        {
                            break;
                        }
						RECT resizeRect = {0, cDiv->GetBottom() - 4, width, cDiv->GetBottom() + 4};
                        if (mp.x >= resizeRect.left && mp.x <= resizeRect.right && mp.y >= resizeRect.top && mp.y <= resizeRect.bottom)
                        {
							SetCursor(CursorsMe_SizeNS);
                            goto OutLoop;
						}
                    }
                }
				SetCursor(CursorsMe_Arrow);
				OutLoop: ;
            }
            m_crossStopIndex = GetMouseOverIndex();
            m_cross_y = mp.y;
            if (m_showCrossLine && m_crossLineMoveMode == CrossLineMoveMode_FollowMouse)
            {
                m_isScrollCross = false;
            }
            Invalidate();
        }
        m_lastMouseMovePoint = mp;
	}

	void CChartMe::OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CControlMe::OnMouseUp(mp, button, clicks, delta); 
		bool needUpdate = false;
        if (m_movingShape)
        {
            m_movingShape = 0;
        }
        vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
		{
			CDivMe *div = *sIter;
            if (div->GetSelectArea()->IsVisible())
            {
                div->GetSelectArea()->SetCanResize(false);
                Invalidate();
                return;
            }
        }
        SetCursor(CursorsMe_Arrow);
		CBaseShapeMe *selectedShape = GetSelectedShape();
		if (m_hResizeType == 0 && m_userResizeDiv == 0 && button == MouseButtonsMe_Left && m_canMoveShape && selectedShape)
        {
            CDivMe *curDiv = FindDiv(selectedShape);
            sIter = divsCopy.begin();
			for(; sIter != divsCopy.end(); ++sIter)
			{
				CDivMe *cDiv = *sIter;
                if (mp.y >= cDiv->GetTop() && mp.y <= cDiv->GetBottom())
                {
                    if (cDiv == curDiv)
                    {
                        break;
                    }
					if(!cDiv->ContainsShape(selectedShape))
                    {
						vector<CDivMe*>::iterator sIter2  = divsCopy.begin();
						int dsize = (int)divsCopy.size();
                        for (int j = 0; j < dsize; j++, sIter2++)
						{
							CDivMe *div = *sIter2;
							if(div->ContainsShape(selectedShape))
                            {
                                div->RemoveShape(selectedShape);
                                break;
                            }
                        }
                        cDiv->AddShape(selectedShape);
                        needUpdate = true;
                    }
                }
            }
        }
        if (m_movingPlot)
        {
            m_movingPlot = 0;
        }
        if (ResizeDiv())
        {
            needUpdate = true;
        }
        if (needUpdate)
        {
            Update();
        }
		Invalidate();
	}

	void CChartMe::OnMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
	{
		CControlMe::OnMouseWheel(mp, button, clicks, delta); 
        if (delta > 0)
		{
            ChangeChart(ScrollType_ZoomOut, 1);
        }
        else
        {
            ChangeChart(ScrollType_ZoomIn, 1);
        }
	}

	void CChartMe::OnKeyUp(char key)
	{
		CControlMe::OnKeyUp(key);
		if (m_scrollStep != 1)
        {
            bool redraw = false;
            if (m_scrollStep > 6)
            {
                redraw = true;
            }
            m_scrollStep = 1;
            if (redraw)
            {
                Update();
				Invalidate();
            }
        }
	}

	void CChartMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
	{
		POINT offset = paint->GetOffset();
		vector<CDivMe*> divsCopy = GetDivs();
		vector<CDivMe*>::iterator sIter = divsCopy.begin();
		for(; sIter != divsCopy.end(); ++sIter)
		{
			CDivMe *div = *sIter;
			int offsetX = offset.x + div->GetLeft();
            int offsetY = offset.y + div->GetTop();
			POINT newOffset = {offsetX, offsetY};
			paint->SetOffset(newOffset);
			RECT divClipRect = {0, 0, div->GetWidth(), div->GetHeight()};
			paint->SetClip(divClipRect);
			OnPaintDivBackGround(paint, div);
			OnPaintHScale(paint, div);
			OnPaintVScale(paint, div);
			OnPaintShapes(paint, div);
			OnPaintDivBorder(paint, div);
			OnPaintCrossLine(paint, div);
			OnPaintTitle(paint, div);
			OnPaintSelectArea(paint, div);
			OnPaintPlots(paint, div);
		}
		paint->SetOffset(offset);
		paint->SetClip(clipRect);
		OnPaintResizeLine(paint);
		OnPaintToolTip(paint);
		OnPaintIcon(paint);
	}

	void CChartMe::OnTimer(int timerID)
	{
		CControlMe::OnTimer(timerID);
		if(IsVisible() && this == GetNative()->GetHoveredControl() && timerID == m_timerID)
		{
			CheckToolTip();
		}
	}
}