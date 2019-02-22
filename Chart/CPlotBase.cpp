#include "..\\stdafx.h"
#include "..\\include\\Chart\\CPlotBase.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPlotBaseMe::CPlotBaseMe()
{
	 m_action = ActionType_NO;
	 m_attachVScale = AttachVScale_Left;
	 m_color = COLOR::ARGB(255, 255, 255);
	 m_dataSource = 0;
	 m_div = 0;
	 m_drawGhost = true;
	 m_enabled = true;
	 m_font = new FONT();
	 m_isPaintingGhost = false;
	 m_lineStyle = 0;
	 m_lineWidth = 1;
	 m_moveTimes = 0;
	 m_plotType = L"LINE";
	 m_selected = false;
	 m_selectedColor = COLOR::ARGB(255, 255, 255);
	 m_selectedPoint = SelectPoint_Rect;
	 m_startPoint.x = 0;
	 m_startPoint.y = 0;
	 m_text = L"";
	 m_visible = true;
	 m_zOrder = 0;
}

CPlotBaseMe::~CPlotBaseMe()
{
	if(m_font)
	{
		delete m_font;
	}
	m_font = 0;
	ClearMarks(&m_marks);
	ClearMarks(&m_startMarks);
	m_sourceFields.clear();
}

AttachVScale CPlotBaseMe::GetAttachVScale()
{
	return m_attachVScale;
}

void CPlotBaseMe::SetAttachVScale(AttachVScale attachVScale)
{
	m_attachVScale = attachVScale;
}

_int64 CPlotBaseMe::GetColor()
{
	return m_color;
}

void CPlotBaseMe::SetColor(_int64 color)
{
	m_color = color;
}

CursorsMe CPlotBaseMe::GetCursor()
{
	return m_div->GetChart()->GetCursor();
}

void CPlotBaseMe::SetCursor(CursorsMe cursor)
{
	m_div->GetChart()->SetCursor(cursor);
}

CDivMe* CPlotBaseMe::GetDiv()
{
	return m_div;
}

void CPlotBaseMe::SetDiv(CDivMe *div)
{
	m_div = div;
}

bool CPlotBaseMe::DrawGhost()
{
	return m_drawGhost;
}

void CPlotBaseMe::SetDrawGhost(bool drawGhost)
{
	m_drawGhost = drawGhost;
}

bool CPlotBaseMe::IsEnabled()
{
	return m_enabled;
}

void CPlotBaseMe::SetEnabled(bool enabled)
{
	if (!enabled)
	{
		m_selected = false;
	}
	m_enabled = enabled;
}

FONT* CPlotBaseMe::GetFont()
{
	return m_font;
}

void CPlotBaseMe::SetFont(FONT *font)
{
	m_font->Copy(font);
}

CChartMe* CPlotBaseMe::GetChart()
{
	return m_div->GetChart();
}

int CPlotBaseMe::GetLineStyle()
{
	return m_lineStyle;
}

void CPlotBaseMe::SetLineStyle(int lineStyle)
{
	m_lineStyle = lineStyle;
}

int CPlotBaseMe::GetLineWidth()
{
	return m_lineWidth;
}

void CPlotBaseMe::SetLineWidth(int lineWidth)
{
	m_lineWidth = lineWidth;
}

String CPlotBaseMe::GetPlotType()
{
	return m_plotType;
}

void CPlotBaseMe::SetPlotType(const String& plotType)
{
	m_plotType = plotType;
}

bool CPlotBaseMe::IsSelected()
{
	return m_selected;
}

void CPlotBaseMe::SetSelected(bool selected)
{
	m_selected = selected;
}

_int64 CPlotBaseMe::GetSelectedColor()
{
	return m_selectedColor;
}

void CPlotBaseMe::SetSelectedColor(_int64 selectedColor)
{
	m_selectedColor = selectedColor;
}

enum SelectPoint CPlotBaseMe::GetSelectedPoint()
{
	return m_selectedPoint;
}

void CPlotBaseMe::SetSelectedPoint(enum SelectPoint selectedPoint)
{
	m_selectedPoint = selectedPoint;
}

String CPlotBaseMe::GetText()
{
	return m_text;
}

void CPlotBaseMe::SetText(const String& text)
{
	m_text = text;
}

bool CPlotBaseMe::IsVisible()
{
	return m_visible;
}

void CPlotBaseMe::SetVisible(bool visible)
{
	m_visible = visible;
}

int CPlotBaseMe::GetWorkingAreaWidth()
{
	return GetChart()->GetWorkingAreaWidth();
}

int CPlotBaseMe::GetWorkingAreaHeight()
{
	return m_div->GetWorkingAreaHeight();
}

int CPlotBaseMe::GetZOrder()
{
	return m_zOrder;
}

void CPlotBaseMe::SetZOrder(int zOrder)
{
	m_zOrder = zOrder;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CPlotBaseMe::DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, const RECT& rect)
{
	DrawEllipse(paint, dwPenColor, width, style, rect.left, rect.top, rect.right, rect.bottom);
}

void CPlotBaseMe::DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, int left, int top, int right, int bottom)
{
	DrawEllipse(paint, dwPenColor, width, style, (float)left, (float)top, (float)right, (float)bottom);
}

void CPlotBaseMe::DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, float left, float top, float right, float bottom)
{
	int px = GetPx();
	int py = GetPy();
	left += px;
	top += py;
	right += px;
	bottom += py;
	RECT rect = { (LONG)left, (LONG)top, (LONG)right, (LONG)bottom };
	paint->DrawEllipse(dwPenColor, (float) width, style, rect);
	if (paint->SupportTransparent())
	{
		CChartMe *chart = GetChart();
		POINT mp = GetChart()->GetMousePoint();
		if(!m_isPaintingGhost)
		{
			if (chart->GetMovingPlot() == this || (mp.y >= m_div->GetTop() && mp.y <= m_div->GetBottom())
				&& (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect()))
			{
				int a = 0;
				int r = 0;
				int g = 0;
				int b = 0;
				COLOR::ToARGB(paint, dwPenColor, &a, &r, &g, &b);
				if (a == 255)
				{
					a = 50;
				}
				dwPenColor = COLOR::ARGB(a, r, g, b);
				width += 10;
				paint->DrawEllipse(dwPenColor, (float) width, 0, rect);
			}
		}
	}
}

void CPlotBaseMe::DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, const POINT& x, const POINT& y)
{
	DrawLine(paint, dwPenColor, width, style, x.x, x.y, y.x, y.y);
}

void CPlotBaseMe::DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, int x1, int y1, int x2, int y2)
{
	DrawLine(paint, dwPenColor, width, style, (float)x1, (float)y1, (float)x2, (float)y2);
}

void CPlotBaseMe::DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, float x1, float y1, float x2, float y2)
{
	int px = GetPx();
	int py = GetPy();
	x1 += px;
	y1 += py;
	x2 += px;
	y2 += py;
	paint->DrawLine(dwPenColor, (float) width, style, (int) x1, (int) y1, (int) x2, (int) y2);
	if (paint->SupportTransparent())
	{
		CChartMe *chart = GetChart();
		POINT mp = chart->GetMousePoint();
		if(!m_isPaintingGhost)
		{
			if (chart->GetMovingPlot() == this || (mp.y >= m_div->GetTop() && mp.y <= m_div->GetBottom())
				&& (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect()))
			{
				int a = 0;
				int r = 0;
				int g = 0;
				int b = 0;
				COLOR::ToARGB(paint, dwPenColor, &a, &r, &g, &b);
				if (a == 255)
				{
					a = 50;
				}
				dwPenColor = COLOR::ARGB(a, r, g, b);
				width += 10;
				paint->DrawLine(dwPenColor, (float) width, 0, (int) x1, (int) y1, (int) x2, (int) y2);
			}
		}
	}
}

void CPlotBaseMe::DrawPolygon(CPaintMe *paint, _int64 dwPenColor, int width, int style, POINT *apt, int cpt)
{
	int px = GetPx();
	int py = GetPy();
	for (int i = 0; i < cpt; i++)
	{
		POINT point = {px + apt[i].x, py + apt[i].y};
		apt[i] = point;
	}
	paint->DrawPolygon(dwPenColor, (float)width, style, apt, cpt);
	if (paint->SupportTransparent())
	{
		CChartMe *chart = GetChart();
		POINT mp = chart->GetMousePoint();
		if(!m_isPaintingGhost)
		{
			if (chart->GetMovingPlot() == this || (mp.y >= m_div->GetTop() && mp.y <= m_div->GetBottom())
				&& (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect()))
			{
				int a = 0;
				int r = 0;
				int g = 0;
				int b = 0;
				COLOR::ToARGB(paint, dwPenColor, &a, &r, &g, &b);
				if (a == 255)
				{
					a = 50;
				}
				dwPenColor = COLOR::ARGB(a, r, g, b);
				width += 10;
				paint->DrawPolygon(dwPenColor, (float) width, 0, apt, cpt);
			}
		}
	}
}

void CPlotBaseMe::DrawPolyline(CPaintMe *paint, _int64 dwPenColor, int width, int style, POINT *apt, int cpt)
{
	int px = GetPx();
	int py = GetPy();
	for (int i = 0; i <cpt; i++)
	{
		POINT point = {px + apt[i].x, py + apt[i].y};
		apt[i] = point;
	}
	paint->DrawPolyline(dwPenColor, (float) width, style, apt, cpt);
	if (paint->SupportTransparent())
	{
		CChartMe *chart = GetChart();
		POINT mp = chart->GetMousePoint();
		if(!m_isPaintingGhost)
		{
			if (chart->GetMovingPlot() == this || (mp.y >= m_div->GetTop() && mp.y <= m_div->GetBottom())
				&& (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect()))
			{
				{
					int a = 0;
					int r = 0;
					int g = 0;
					int b = 0;
					COLOR::ToARGB(paint, dwPenColor, &a, &r, &g, &b);
					if (a == 255)
					{
						a = 50;
					}
					dwPenColor = COLOR::ARGB(a, r, g, b);
					width += 10;
					paint->DrawPolyline(dwPenColor, (float) width, 0, apt, cpt);
				}
			}
		}
	}
}

void CPlotBaseMe::DrawRay(CPaintMe *paint, _int64 dwPenColor, int width, int style, float x1, float y1, float x2, float y2, float k, float b)
{
	if (k != 0 || b != 0)
	{
		float leftX = 0;
		float leftY = leftX * k + b;
		float rightX = (float)GetWorkingAreaWidth();
		float rightY = rightX * k + b;
		if (x1 >= x2)
		{
			DrawLine(paint, dwPenColor, width, style, leftX, leftY, x1, y1);
		}
		else
		{
			DrawLine(paint, dwPenColor, width, style, x1, y1, rightX, rightY);
		}
	}
	else
	{
		if (y1 >= y2)
		{
			DrawLine(paint, dwPenColor, width, style, (float)x1, (float)y1, (float)x1, (float)0);
		}
		else
		{
			DrawLine(paint, dwPenColor, width, style, x1, y1, x1, (float) GetWorkingAreaHeight());
		}
	}
}

void CPlotBaseMe::DrawRect(CPaintMe *paint, _int64 dwPenColor, int width, int style, int left, int top, int right, int bottom)
{
	int px = GetPx();
	int py = GetPy();
	left += px;
	top += py;
	right += px;
	bottom += py;
	RECT rect = { left, top, right, bottom };
	paint->DrawRect(dwPenColor, (float) width, style, rect);
	if (paint->SupportTransparent())
	{
		CChartMe *chart = GetChart();
		POINT mp = chart->GetMousePoint();
		if(!m_isPaintingGhost)
		{
			if (chart->GetMovingPlot() == this || (mp.y >= m_div->GetTop() && mp.y <= m_div->GetBottom())
				&& (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect()))
			{
				int a = 0;
				int r = 0;
				int g = 0;
				int b = 0;
				COLOR::ToARGB(paint, dwPenColor, &a, &r, &g, &b);
				if (a == 255)
				{
					a = 50;
				}
				dwPenColor = COLOR::ARGB(a, r, g, b);
				width += 10;
				paint->DrawRect(dwPenColor, (float) width, 0, rect);
			}
		}
	}
}

void CPlotBaseMe::DrawRect(CPaintMe *paint, _int64 dwPenColor, int width, int style, const RECT& rect)
{
	DrawRect(paint, dwPenColor, width, style, rect.left, rect.top, rect.right, rect.bottom);
}

void CPlotBaseMe::DrawSelect(CPaintMe *paint, _int64 dwPenColor, int x, int y)
{
	int px = GetPx();
	int py = GetPy();
	x += px;
	y += py;
	int sub = m_lineWidth * 3;
	RECT rect = { (LONG)(x - sub), (LONG)(y - sub), (LONG)(x + sub), (LONG)(y + sub) };
	if (GetSelectedPoint() == SelectPoint_Ellipse)
	{
		paint->FillEllipse(dwPenColor, rect);
	}
	else if (GetSelectedPoint() == SelectPoint_Rect)
	{
		paint->FillRect(dwPenColor, rect);
	}
}

void CPlotBaseMe::DrawSelect(CPaintMe *paint, _int64 dwPenColor, float x, float y)
{
	DrawSelect(paint, dwPenColor, (int)x, (int)y);
}

void CPlotBaseMe::DrawText(CPaintMe *paint, LPCWSTR strText, _int64 dwPenColor, FONT *font, int left, int top)
{
	int px = GetPx();
	int py = GetPy();
	left += px;
	top += py;
	SIZE size = paint->TextSize(strText, font);
	RECT rect = { left, top, left + size.cx, top + size.cy};
	paint->DrawText(strText, dwPenColor, font, rect);
}

void CPlotBaseMe::FillEllipse(CPaintMe *paint, _int64 dwPenColor, const RECT& rect)
{
	int px = GetPx();
	int py = GetPy();
	int left = rect.left;
	int top = rect.top;
	int right = rect.right;
	int bottom = rect.bottom;
	left += px;
	top += py;
	right += px;
	bottom += py;
	RECT newRect = { left, top, right, bottom };
	paint->FillEllipse(dwPenColor, newRect);
}

void CPlotBaseMe::FillPolygon(CPaintMe *paint, _int64 dwPenColor, POINT *apt, int cpt)
{
	int px = GetPx();
	int py = GetPy();
	for (int i = 0; i < cpt; i++)
	{
		POINT point = {px + apt[i].x, py + apt[i].y};
		apt[i] = point;
	}
	paint->FillPolygon(dwPenColor, apt, cpt);
}

void CPlotBaseMe::FillRect(CPaintMe *paint, _int64 dwPenColor, const RECT& rect)
{
	int px = GetPx();
	int py = GetPy();
	int left = rect.left;
	int top = rect.top;
	int right = rect.right;
	int bottom = rect.bottom;
	left += px;
	top += py;
	right += px;
	bottom += py;
	RECT newRect = { left, top, right, bottom };
	paint->FillRect(dwPenColor, newRect);
}

void CPlotBaseMe::UpdateSourceField(const String& fieldName, int fieldId)
{
	map<String,int>::iterator sIter = m_sourceFields.find(fieldName);
	if(sIter == m_sourceFields.end())
	{
		m_sourceFields.insert(make_pair(fieldName, fieldId));
	}
	else
	{
		sIter->second = fieldId;
	}
}

SIZE CPlotBaseMe::TextSize(CPaintMe *paint, LPCWSTR strText, FONT *font)
{
	return paint->TextSize(strText, font);
}

void CPlotBaseMe::MovePlot(float mouseY, float startY, int startIndex, int mouseBeginIndex, int mouseEndIndex, float pureV,
						double max, double min, int dataCount, double *yAddValue, int *newIndex)
{
	float subY = mouseY - startY;
	*yAddValue = (min - max) * subY / (double) pureV;
	*newIndex = startIndex + mouseEndIndex - mouseBeginIndex;
	if (*newIndex < 0)
	{
		*newIndex = 0;
	}
	else if (*newIndex > dataCount - 1)
	{
		*newIndex = dataCount - 1;
	}
}

CNativeBaseMe* CPlotBaseMe::GetNative()
{
	return m_div->GetChart()->GetNative();
}

int CPlotBaseMe::GetIndex(const POINT& mp)
{
	CChartMe *chart = GetChart();
	POINT newPoint;
	newPoint.x = mp.x + chart->GetLeftVScaleWidth();
	newPoint.y = mp.y + m_div->GetTop() + m_div->GetTitleBar()->GetHeight();
	return chart->GetIndex(newPoint);
}

POINT CPlotBaseMe::GetMouseOverPoint()
{
	CChartMe *chart = GetChart();
	POINT mp = chart->GetMousePoint();
	mp.x -= chart->GetLeftVScaleWidth();
	mp.y = mp.y - m_div->GetTop() - m_div->GetTitleBar()->GetHeight();
	return mp;
}

void CPlotBaseMe::ClearMarks(map<int,CPlotMarkMe*> *marks)
{
	map<int,CPlotMarkMe*>::iterator sIterPlot = marks->begin();
	for(; sIterPlot != marks->end(); ++sIterPlot)
	{
		delete sIterPlot->second;
		sIterPlot->second = 0;
	}
	marks->clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool CPlotBaseMe::CreatePoint(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		int mouseIndex = chart->GetIndex(mp);
		if (mouseIndex >= chart->GetFirstVisibleIndex() && mouseIndex <= chart->GetLastVisibleIndex())
		{
			double date = m_dataSource->GetXValue(mouseIndex);
			ClearMarks(&m_marks);
			double yValue = GetNumberValue(mp);
			m_marks.insert(make_pair(0, new CPlotMarkMe(0, date, yValue)));
			return true;
		}
	}
	return false;
}

bool CPlotBaseMe::Create2PointsA(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		int mouseIndex = chart->GetIndex(mp);
		if (mouseIndex >= chart->GetFirstVisibleIndex() && mouseIndex <= chart->GetLastVisibleIndex())
		{
			int eIndex = mouseIndex;
			int bIndex = eIndex - 1;
			if (bIndex >= 0)
			{
				double fDate = m_dataSource->GetXValue(bIndex);
				double sDate = m_dataSource->GetXValue(eIndex);
				ClearMarks(&m_marks);
				double numberValue = GetNumberValue(mp);
				m_marks.insert(make_pair(0, new CPlotMarkMe(0, fDate, numberValue)));
				m_marks.insert(make_pair(1, new CPlotMarkMe(1, sDate, numberValue)));
				return true;
			}
		}
	}
	return false;
}

bool CPlotBaseMe::Create2PointsB(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		int mouseIndex = chart->GetIndex(mp);
		if (mouseIndex >= chart->GetFirstVisibleIndex()
			&& mouseIndex <= chart->GetLastVisibleIndex())
		{
			double date = m_dataSource->GetXValue(mouseIndex);
			ClearMarks(&m_marks);
			double numberValue = GetNumberValue(mp);
			m_marks.insert(make_pair(0, new CPlotMarkMe(0, date, numberValue)));
			m_marks.insert(make_pair(1, new CPlotMarkMe(1, date, numberValue)));
			return true;
		}
	}
	return false;
}

bool CPlotBaseMe::Create2CandlePoints(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		vector<CBaseShapeMe*> shapes =  m_div->GetShapes(SORTTYPE_DESC);
		vector<CBaseShapeMe*>::iterator sIter = shapes.begin();
		for(; sIter != shapes.end(); ++sIter)
		{
			CBaseShapeMe *shape = (*sIter);
			if (shape->IsVisible())
			{
				CCandleShapeMe *cs = dynamic_cast<CCandleShapeMe*>(shape);
				if (cs)
				{
					int mouseIndex = chart->GetIndex(mp);
					if (mouseIndex >= chart->GetFirstVisibleIndex()
						&& mouseIndex <= chart->GetLastVisibleIndex())
					{
						int eIndex = mouseIndex;
						int bIndex = eIndex - 1;
						if (bIndex >= 0)
						{
							double fDate = m_dataSource->GetXValue(bIndex);
							double sDate = m_dataSource->GetXValue(eIndex);
							ClearMarks(&m_marks);
							double numberValue = GetNumberValue(mp);
							m_marks.insert(make_pair(0, new CPlotMarkMe(0, fDate, numberValue)));
							m_marks.insert(make_pair(1, new CPlotMarkMe(1, sDate, numberValue)));
							UpdateSourceField(L"CLOSE", cs->GetCloseField());
							UpdateSourceField(L"OPEN", cs->GetOpenField());
							UpdateSourceField(L"HIGH", cs->GetHighField());
							UpdateSourceField(L"LOW", cs->GetLowField());
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

bool CPlotBaseMe::Create3Points(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		int mouseIndex = chart->GetIndex(mp);
		if (mouseIndex >= chart->GetFirstVisibleIndex()
			&& mouseIndex <= chart->GetLastVisibleIndex())
		{
			int eIndex = mouseIndex;
			int bIndex = eIndex - 1;
			if (bIndex >= 0)
			{
				double fDate = m_dataSource->GetXValue(bIndex);
				double sDate = m_dataSource->GetXValue(eIndex);
				ClearMarks(&m_marks);
				double numberValue = GetNumberValue(mp);
				m_marks.insert(make_pair(0, new CPlotMarkMe(0, fDate, numberValue)));
				m_marks.insert(make_pair(1, new CPlotMarkMe(1, sDate, numberValue)));

				CVScaleMe *vscale = m_div->GetVScale(m_attachVScale);
				if (vscale && vscale->GetVisibleMax() != vscale->GetVisibleMin())
				{
					m_marks.insert(make_pair(2, new CPlotMarkMe(2, fDate, 
						numberValue + (vscale->GetVisibleMax() - vscale->GetVisibleMin()) / 4.0)));
				}
				else
				{
					m_marks.insert(make_pair(2, new CPlotMarkMe(2, fDate, numberValue)));
				}
				return true;
			}
		}
	}
	return false;
}

void CPlotBaseMe::CreateCandlePoint(int pos, int index, int close)
{
	if (index >= 0)
	{
		int rowCount = m_dataSource->RowsCount();
		if (index > rowCount - 1)
		{
			index = rowCount - 1;
		}
		double date = m_dataSource->GetXValue(index);
		double yValue = 0.0;
		if (!m_dataSource->IsNaN(m_dataSource->Get2(index, close)))
		{
			yValue = m_dataSource->Get2(index, close);
		}
		m_marks.insert(make_pair(pos, new CPlotMarkMe(pos, date, yValue)));
	}
}

bool CPlotBaseMe::Create4CandlePoints(const POINT& mp)
{
	if (m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = GetChart();
		vector<CBaseShapeMe*> shapes =  m_div->GetShapes(SORTTYPE_ASC);
		vector<CBaseShapeMe*>::iterator sIter = shapes.begin();
		for(; sIter != shapes.end(); ++sIter)
		{
			CBaseShapeMe *shape = (*sIter);
			CCandleShapeMe *cshape = dynamic_cast<CCandleShapeMe*>(shape);
			if (shape->IsVisible() && cshape)
			{
				int mouseIndex = chart->GetIndex(mp);
				if (mouseIndex >= chart->GetFirstVisibleIndex() 
					&& mouseIndex <= chart->GetLastVisibleIndex())
				{
					int closeField = cshape->GetCloseField();
					CreateCandlePoint(0, mouseIndex, closeField);
					CreateCandlePoint(1, mouseIndex + 1, closeField);
					CreateCandlePoint(2, mouseIndex + 2, closeField);
					CreateCandlePoint(3, mouseIndex + 3, closeField);

					UpdateSourceField(L"CLOSE", closeField);
					UpdateSourceField(L"OPEN", cshape->GetOpenField());
					UpdateSourceField(L"HIGH", cshape->GetHighField());
					UpdateSourceField(L"LOW", cshape->GetLowField());
					return true;
				}
			}
		}
	}
	return false;
}

double* CPlotBaseMe::GetCandleRange(map<int,CPlotMarkMe*> *pList, int *length)
{
	*length = 0;
	if ((int)pList->size() == 0 || (int)m_sourceFields.size() == 0)
	{
		return 0;
	}
	map<String, int>::iterator sIterHigh = m_sourceFields.find(L"HIGH");
	map<String, int>::iterator sIterLow = m_sourceFields.find(L"LOW");
	if (sIterHigh == m_sourceFields.end() || sIterLow == m_sourceFields.end())
	{
		return 0;
	}
	map<int,CPlotMarkMe*>::iterator pList0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator pList1 = pList->find(1);;
	int bRecord = m_dataSource->GetRowIndex(pList0->second->Key);
	int eRecord = m_dataSource->GetRowIndex(pList1->second->Key);
	double *highlist = 0;
	double *lowlist = 0;
	int hightLength = 0;
	int lowLength = 0;
	if (eRecord >= bRecord)
	{
		highlist = m_dataSource->DATA_ARRAY(sIterHigh->second, eRecord, eRecord - bRecord + 1, &hightLength);
		lowlist = m_dataSource->DATA_ARRAY(sIterLow->second, eRecord, eRecord - bRecord + 1, &lowLength);
	}
	else
	{
		highlist = m_dataSource->DATA_ARRAY(sIterHigh->second, bRecord, bRecord - eRecord + 1, &hightLength);
		lowlist = m_dataSource->DATA_ARRAY(sIterLow->second, bRecord, bRecord - eRecord + 1, &lowLength);
	}
	double nHigh = 0.0;
	double nLow = 0.0;
	nHigh = CMathLibMe::GetMax(highlist, hightLength);
	nLow = CMathLibMe::GetMin(lowlist, lowLength);
	if(highlist)
	{
		delete highlist;
	}
	highlist = 0;
	if(lowlist)
	{
		delete lowlist;
	}
	lowlist = 0;
	double *retArray = new double[2];
	retArray[0] = nHigh;
	retArray[1] = nLow;
	*length = 2;
	return retArray;
}

float* CPlotBaseMe::GetLineParams(CPlotMarkMe *markA, CPlotMarkMe *markB, int *length)
{
	float y1 = PY(markA->Value);
	float y2 = PY(markB->Value);
	int bIndex = m_dataSource->GetRowIndex(markA->Key);
	int eIndex = m_dataSource->GetRowIndex(markB->Key);
	float x1 = PX(bIndex);
	float x2 = PX(eIndex);
	if (x2 - x1 != 0)
	{
		float k = 0;
		float b = 0;
		CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
		float *retArray = new float[2];
		retArray[0] = k;
		retArray[1] = b;
		*length = 2;
		return retArray;
	}
	*length = 0;
	return NULL;
}

double* CPlotBaseMe::GetLRBandRange(map<int,CPlotMarkMe*> *marks, float *param)
{
	map<String, int>::iterator sIterHigh;
	map<String, int>::iterator sIterLow;
	if ((int)m_sourceFields.size() <= 0)
	{
		sIterHigh = m_sourceFields.find(L"HIGH");
		sIterLow = m_sourceFields.find(L"LOW");
		if (sIterHigh == m_sourceFields.end() || sIterLow == m_sourceFields.end())
		{
			return 0;
		}
	}
	float a = param[0];
	float b = param[1];
	vector<double> upList;
	vector<double> downList;
	map<int,CPlotMarkMe*>::iterator pList0 = marks->find(0);
	map<int,CPlotMarkMe*>::iterator pList1 = marks->find(1);;
	int bIndex = m_dataSource->GetRowIndex(pList0->second->Key);
	int eIndex = m_dataSource->GetRowIndex(pList1->second->Key);
	for (int i = bIndex; i <= eIndex; i++)
	{
		double high = m_dataSource->Get2(i, sIterHigh->second);
		double low = m_dataSource->Get2(i, sIterLow->second);
		if (!m_dataSource->IsNaN(high) && !m_dataSource->IsNaN(low))
		{
			double midValue = (i - bIndex + 1) * a + b;
			upList.push_back(high - midValue);
			downList.push_back(midValue - low);
		}
	}
	int upSize = (int)upList.size();
	int downSize = (int)downList.size();
	double *upArray = new double[upSize];
	double *downArray = new double[downSize];
	for(int i = 0; i < upSize; i++)
	{
		upArray[i] = upList[i];
	}
	for(int i = 0; i < downSize; i++)
	{
		downArray[i] = downList[i];
	}
	double upSubValue = CMathLibMe::GetMax(upArray, upSize);
	double downSubValue = CMathLibMe::GetMax(downArray, downSize);
	double *retArray = new double[2];
	retArray[0] = upSubValue;
	retArray[1] = downSubValue;
	return retArray;
}

float* CPlotBaseMe::GetLRParams(map<int,CPlotMarkMe*> *marks)
{
	map<String, int>::iterator sIterClose;
	if ((int)m_sourceFields.size() > 0)
	{
		sIterClose = m_sourceFields.find(L"CLOSE");
		if(sIterClose != m_sourceFields.end())
		{
			map<int,CPlotMarkMe*>::iterator pList0 = marks->find(0);
			map<int,CPlotMarkMe*>::iterator pList1 = marks->find(1);;
			int bIndex = m_dataSource->GetRowIndex(pList0->second->Key);
			int eIndex = m_dataSource->GetRowIndex(pList1->second->Key);
			if (bIndex != -1 && eIndex != -1)
			{
				vector<double> closeVList;
				for (int i = bIndex; i <= eIndex; i++)
				{
					double value = m_dataSource->Get2(i, sIterClose->second);
					if (!m_dataSource->IsNaN(value))
					{
						closeVList.push_back(value);
					}
				}
				if ((int)closeVList.size() > 0)
				{
					float a = 0;
					float b = 0;
					int closeSize = (int)closeVList.size();
					double *closeArray = new double[closeSize];
					for(int i = 0; i < closeSize; i++)
					{
						closeArray[i] = closeVList[i];
					}
					CMathLibMe::M014(closeArray, closeSize, &a, &b);
					if(closeArray)
					{
						delete closeArray;
						closeArray = 0;
					}
					float *retArray = new float[2];
					retArray[0] = a;
					retArray[1] = b;
					return retArray;
				}
			}
		}
	}
	return 0;
}

POINT CPlotBaseMe::GetMovingPoint()
{
	POINT mp = GetMouseOverPoint();
	if (mp.x < 0)
	{
		mp.x = 0;
	}
	else if (mp.x > GetWorkingAreaWidth())
	{
		mp.x = GetWorkingAreaWidth();
	}
	if (mp.y < 0)
	{
		mp.y = 0;
	}
	else if (mp.y > GetWorkingAreaWidth())
	{
		mp.y = GetWorkingAreaWidth();
	}
	return mp;
}

double CPlotBaseMe::GetNumberValue(const POINT& mp)
{
	CChartMe *chart = GetChart();
	POINT newPoint;
	newPoint.x = mp.x + chart->GetLeftVScaleWidth();
	newPoint.y = mp.y + m_div->GetTop() + m_div->GetTitleBar()->GetHeight();
	return chart->GetNumberValue(m_div, newPoint, m_attachVScale);
}

int CPlotBaseMe::GetPx()
{
	return GetChart()->GetLeftVScaleWidth();
}

int CPlotBaseMe::GetPy()
{
	return m_div->GetTitleBar()->GetHeight();
}

RECT CPlotBaseMe::GetRectangle(CPlotMarkMe *markA, CPlotMarkMe *markB)
{
	double aValue = markA->Value;
	double bValue = markB->Value;
	int aIndex = m_dataSource->GetRowIndex(markA->Key);
	int bIndex = m_dataSource->GetRowIndex(markB->Key);
	float x = PX(aIndex);
	float y = PY(aValue);
	float xS = PX(bIndex);
	float yS = PY(bValue);
	float width = abs((float)(xS - x));
	if (width < 4)
	{
		width = 4;
	}
	float height = abs((float)(yS - y));
	if (height < 4)
	{
		height = 4;
	}
	float left = x <= xS ? x : xS;
	float top = y <= yS ? y : yS;
	RECT rect = { (LONG)left, (LONG)top,  (LONG)(left + width),  (LONG)(top + height) };
	return rect;
}

float* CPlotBaseMe::GoldenRatioParams(double value1, double value2, int *length)
{
	float y1 = PY(value1);
	float y2 = PY(value2);
	float y0 = 0;
	float yA = 0;
	float yB = 0;
	float yC = 0;
	float yD = 0;
	float y100 = 0;
	y0 = y1;
	yA = (float)((y1 <= y2) ? (y1 + ((y2 - y1) * 0.236)) : (y2 + ((y1 - y2) * 0.764)));
	yB = (float)((y1 <= y2) ? (y1 + ((y2 - y1) * 0.382)) : (y2 + ((y1 - y2) * 0.618)));
	yC = (float)((y1 <= y2) ? (y1 + ((y2 - y1) * 0.5)) : (y2 + ((y1 - y2) * 0.5)));
	yD = (float)((y1 <= y2) ? (y1 + ((y2 - y1) * 0.618)) : (y2 + ((y1 - y2) * 0.382)));
	y100 = y2;
	*length = 6;
	float *retArray = new float[6];
	retArray[0] = y0;
	retArray[1] = yA;
	retArray[2] = yB;
	retArray[3] = yC;
	retArray[4] = yD;
	retArray[5] = y100;
	return retArray;
}

bool CPlotBaseMe::HLinesSelect(float *param, int length)
{
	POINT mp = GetMouseOverPoint();
	float top = 0;
	float bottom = (float)GetWorkingAreaHeight();
	if (mp.y >= top && mp.y <= bottom)
	{
		for(int i = 0; i < length; i++)
		{
			float p = param[i];
			if (mp.y >= (p - m_lineWidth * 2.5) && mp.y <= (p + m_lineWidth * 2.5))
			{
				return true;
			}
		}
	}
	return false;
}

void CPlotBaseMe::Move(const POINT& mp)
{
	CVScaleMe *vScale = m_div->GetVScale(m_attachVScale);
	ClearMarks(&m_marks);
	int startMarkSize = (int)m_startMarks.size();
	for (int i = 0; i < startMarkSize; i++)
	{
		int startIndex = m_dataSource->GetRowIndex(m_startMarks[i]->Key);
		int newIndex = 0;
		double yAddValue = 0.0;
		MovePlot((float) mp.y, (float) m_startPoint.y, startIndex,
			GetIndex(m_startPoint), GetIndex(mp), (float) GetWorkingAreaHeight(), vScale->GetVisibleMax(), 
			vScale->GetVisibleMin(), m_dataSource->RowsCount(), &yAddValue, &newIndex);
		if (vScale->IsReverse())
		{
			CPlotMarkMe *mark = new CPlotMarkMe(i, m_dataSource->GetXValue(newIndex), m_startMarks[i]->Value - yAddValue);
			map<int,CPlotMarkMe*>::iterator sIter = m_marks.find(i);
			if(sIter == m_marks.end())
			{
				m_marks.insert(make_pair(i, mark));
			}
			else
			{
				sIter->second = mark;
			}
		}
		else
		{
			CPlotMarkMe *mark = new CPlotMarkMe(i, m_dataSource->GetXValue(newIndex), m_startMarks[i]->Value + yAddValue);
			map<int,CPlotMarkMe*>::iterator sIter = m_marks.find(i);
			if(sIter == m_marks.end())
			{
				m_marks.insert(make_pair(i, mark));
			}
			else
			{
				sIter->second = mark;
			}
		}
	}
}

void CPlotBaseMe::OnPaint(CPaintMe *paint)
{
	CChartMe *chart = GetChart();
	POINT mousePoint = chart->GetMousePoint();
	if (mousePoint.y >= m_div->GetTop() && mousePoint.y <= m_div->GetBottom()
		&& (chart->GetMovingPlot() == this
			|| (chart == GetNative()->GetHoveredControl() && !chart->IsOperating() && OnSelect())))
	{
		Paint(paint, &m_marks, m_selectedColor);
	}
	else
	{
		Paint(paint, &m_marks, m_color);
	}
}

void CPlotBaseMe::OnPaintGhost(CPaintMe *paint)
{
	m_isPaintingGhost = true;
	Paint(paint, &m_startMarks, m_color);
	m_isPaintingGhost = false;
}

void CPlotBaseMe::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
}

float CPlotBaseMe::PX(int index)
{
	CChartMe *chart = GetChart();
	return chart->GetX(index) - chart->GetLeftVScaleWidth();
}

float CPlotBaseMe::PY(double value)
{
	CChartMe *chart = GetChart();
	return chart->GetY(m_div, value, m_attachVScale) - m_div->GetTitleBar()->GetHeight();
}

float CPlotBaseMe::PX(float x)
{
	CChartMe *chart = GetChart();
	return x - chart->GetLeftVScaleWidth();
}

float CPlotBaseMe::PY(float y)
{
	return y - m_div->GetTop() - m_div->GetTitleBar()->GetHeight();
}

void CPlotBaseMe::Resize(int index)
{
	CChartMe *chart = GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	double y = GetNumberValue(GetMovingPoint());
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	CPlotMarkMe *mark = new CPlotMarkMe(index, m_dataSource->GetXValue(mouseIndex), y);
	map<int,CPlotMarkMe*>::iterator sIter = m_marks.find(index);
	if(sIter == m_marks.end())
	{
		m_marks.insert(make_pair(index, mark));
	}
	else
	{
		sIter->second = mark;
	}
}

void CPlotBaseMe::Resize(const POINT& mp, POINT oppositePoint)
{
	POINT point = {oppositePoint.x, oppositePoint.y};
	double sValue = GetNumberValue(point);
	double eValue = GetNumberValue(mp);
	int indexS = GetIndex(point);
	int indexE = GetIndex(mp);
	double topValue = 0.0;
	double bottomValue = 0.0;
	CVScaleMe *vScale = m_div->GetVScale(m_attachVScale);
	if (sValue >= eValue)
	{
		if (vScale->IsReverse())
		{
			topValue = eValue;
			bottomValue = sValue;
		}
		else
		{
			topValue = sValue;
			bottomValue = eValue;
		}
	}
	else if (vScale->IsReverse())
	{
		topValue = sValue;
		bottomValue = eValue;
	}
	else
	{
		topValue = eValue;
		bottomValue = sValue;
	}
	double sDate = 0.0;
	double eDate = 0.0;
	if (indexS < 0)
	{
		indexS = 0;
	}
	else if (indexS > m_dataSource->RowsCount() - 1)
	{
		indexS = m_dataSource->RowsCount() - 1;
	}
	if (indexE < 0)
	{
		indexE = 0;
	}
	else if (indexE > m_dataSource->RowsCount() - 1)
	{
		indexE = m_dataSource->RowsCount() - 1;
	}
	if (indexS >= indexE)
	{
		sDate = m_dataSource->GetXValue(indexE);
		eDate = m_dataSource->GetXValue(indexS);
	}
	else
	{
		sDate = m_dataSource->GetXValue(indexS);
		eDate = m_dataSource->GetXValue(indexE);
	}
	ClearMarks(&m_marks);
	CPlotMarkMe *mark = new CPlotMarkMe(0, sDate, topValue);
	map<int,CPlotMarkMe*>::iterator sIter = m_marks.find(0);
	if(sIter == m_marks.end())
	{
		m_marks.insert(make_pair(0, mark));
	}
	else
	{
		sIter->second = mark;
	} 
	mark = new CPlotMarkMe(1, eDate, bottomValue);
	sIter = m_marks.find(1);
	if(sIter == m_marks.end())
	{
		m_marks.insert(make_pair(1, mark));
	}
	else
	{
		sIter->second = mark;
	}
}

bool CPlotBaseMe::SelectPoint(const POINT& mp, float x, float y)
{
	return mp.x >= (x - m_lineWidth * 6) 
			&& mp.x <= (x + m_lineWidth * 6)
			&& mp.y >= (y - m_lineWidth * 6) 
			&& mp.y <= (y + m_lineWidth * 6);
}

bool CPlotBaseMe::SelectLine(const POINT& mp, float x, float k, float b)
{
	if (k != 0 || b != 0)
	{
		if (((((float) mp.y) / (mp.x * k + b)) >= 0.95)
			&& ((((float) mp.y) / (mp.x * k + b)) <= 1.05))
		{
			return true;
		}
	}
	else if (mp.x >= x - (m_lineWidth * 5) && mp.x <= x + (m_lineWidth * 5))
	{
		return true;
	}
	return false;
}

bool CPlotBaseMe::SelectLine(const POINT& mp, float x1, float y1, float x2, float y2)
{
	float k = 0;
	float b = 0;
	CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
	return SelectLine(mp, x1, k, b);
}

bool CPlotBaseMe::SelectRay(const POINT& mp, float x1, float y1, float x2, float y2, float *pk, float *pb)
{
	CMathLibMe::M107(x1, y1, x2, y2, 0, 0, pk, pb);
	if (*pk != 0 || *pb != 0)
	{
		if ((((float) mp.y) / (mp.x * (*pk) + (*pb))) >= 0.95 && (((float) mp.y) / (mp.x * (*pk) + (*pb))) <= 1.05)
		{
			if (x1 >= x2)
			{
				if (mp.x > x1 + 5)
				{
					return false;
				}
			}
			else if (x1 < x2 && mp.x < x1 - 5)
			{
				return false;
			}
			return true;
		}
	}
	else if (mp.x >= x1 - (m_lineWidth * 5) && mp.x <= x1 + (m_lineWidth * 5))
	{
		if (y1 >= y2)
		{
			if (mp.y <= y1 - 5)
			{
				return true;
			}
		}
		else if (mp.y >= y1 - 5)
		{
			return true;
		}
	}
	return false;
}

bool CPlotBaseMe::SelectRay(const POINT& mp, float x1, float y1, float x2, float y2)
{
	float k = 0;
	float b = 0;
	return SelectRay(mp, x1, y1, x2, y2, &k, &b);
}

ActionType CPlotBaseMe::SelectRect(const POINT& mp, CPlotMarkMe *markA, CPlotMarkMe *markB)
{
	RECT rect = GetRectangle(markA, markB);
	int x1 = rect.left;
	int y1 = rect.top;
	int x2 = rect.right;
	int y2 = rect.top;
	int x3 = rect.left;
	int y3 = rect.bottom;
	int x4 = rect.right;
	int y4 = rect.bottom;
	if (SelectPoint(mp, (float) x1, (float) y1))
	{
		return ActionType_AT1;
	}
	if (SelectPoint(mp, (float) x2, (float) y2))
	{
		return ActionType_AT2;
	}
	if (SelectPoint(mp, (float) x3, (float) y3))
	{
		return ActionType_AT3;
	}
	if (SelectPoint(mp, (float) x4, (float) y4))
	{
		return ActionType_AT4;
	}
	int sub = (int)(m_lineWidth * 2.5);
	RECT bigRect = { rect.left - sub, rect.top - sub, rect.right + sub, rect.bottom + sub };
	if (mp.x >= bigRect.left && mp.x <= bigRect.right
		&& mp.y >= bigRect.top && mp.y <= bigRect.bottom)
	{
		if (rect.right - rect.left <= 4 || rect.bottom - rect.top <= 4)
		{
			return ActionType_MOVE;
		}
		RECT smallRect = { rect.left + sub, rect.top + sub, rect.right - sub, rect.bottom - sub };
		if (mp.x < smallRect.left || mp.x > smallRect.right 
			|| mp.y < smallRect.top || mp.y > smallRect.bottom)
		{
			return ActionType_MOVE;
		}
	}
	return ActionType_NO;
}

bool CPlotBaseMe::SelectSegment(const POINT& mp, float x1, float y1, float x2, float y2)
{
	float k = 0;
	float b = 0;
	CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
	float smallX = x1 <= x2 ? x1 : x2;
	float smallY = y1 <= y2 ? y1 : y2;
	float bigX = x1 > x2 ? x1 : x2;
	float bigY = x1 > y2 ? y1 : y2;
	if (mp.x >= (smallX - 2) && mp.x <= (bigX + 2)
		&& mp.y >= (smallY - 2) && mp.y <= (bigY + 2))
	{
		if (k != 0 || b != 0)
		{
			if ((((float) mp.y) / (mp.x * k + b)) >= 0.95 && (((float) mp.y) / (mp.x * k + b)) <= 1.05)
			{
				return true;
			}
		}
		else if (mp.x >= (x1 - m_lineWidth * 5) && mp.x <= (x1 + m_lineWidth * 5))
		{
			return true;
		}
	}
	return false;
}

bool CPlotBaseMe::SelectSine(const POINT& mp,float x1, float y1, float x2, float y2)
{
	double f = 6.28318 / ((double)((x2 - x1) * 4));
	int len = GetWorkingAreaWidth();
	if (len > 0)
	{
		float lastX = 0;
		float lastY = 0;
		for (int i = 0; i < len; i++)
		{
			float x = i - x1;
			float y = (float)(0.5 * (y2 - y1) * sin(x * f) * 2.0);
			float px = x + x1;
			float py = y + y1;
			if (i == 0)
			{
				if (SelectPoint(mp, px, py))
				{
					return true;
				}
			}
			else
			{
				float rectLeft = lastX - 2;
				float rectTop = lastY <= py ? lastY : py - 2;
				float rectRight = rectLeft + abs((float)(px - lastX)) + 4;
				float rectBottom = rectTop + abs((float)(py - lastY)) + 4;
				if (mp.x >= rectLeft && mp.x <= rectRight
					&& mp.y >= rectTop && mp.y <= rectBottom)
				{
					return true;
				}
			}
			lastX = px;
			lastY = py;
		}
	}
	return false;
}

bool CPlotBaseMe::SelectTriangle(const POINT& mp, float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (SelectSegment(mp, x1, y1, x2, y2) || (SelectSegment(mp, x1, y1, x3, y3) || SelectSegment(mp, x2, y2, x3, y3)));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ActionType CPlotBaseMe::GetAction()
{
	return ActionType_NO;
}

bool CPlotBaseMe::OnCreate(const POINT& mp)
{
	return false;
}

void CPlotBaseMe::OnMoveEnd()
{
}

void CPlotBaseMe::OnMoving()
{
	POINT movingPoint = GetMovingPoint();
	switch (m_action)
	{
	case ActionType_MOVE:
		Move(movingPoint);
		return;
	case ActionType_AT1:
		Resize(0);
		return;
	case ActionType_AT2:
		Resize(1);
		return;                    
	case ActionType_AT3:
		Resize(2);
		return;
	case ActionType_AT4:
		Resize(3);
		return;
	}
}

void CPlotBaseMe::OnMoveStart()
{
}

bool CPlotBaseMe::OnSelect()
{
	return GetAction() != ActionType_NO;
}

void CPlotBaseMe::Render(CPaintMe *paint)
{
	CChartMe *chart = GetChart();
	if (m_drawGhost && chart->GetMovingPlot() && chart->GetMovingPlot() == this)
	{
		OnPaintGhost(paint);
	}
	OnPaint(paint);
}