#include "..\\stdafx.h"
#include "..\\include\\Base\\CStr.h"
#include "..\\include\\Chart\\CPExtend.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
P001::P001()
{
	SetPlotType(L"ANDREWSPITCHFORK");
}

ActionType P001::GetAction()
{
	ActionType nO = ActionType_NO;
	int size = (int)CPlotBaseMe::m_marks.size();
	if (size > 0)
	{
		map<String,int>::iterator sIter = CPlotBaseMe::m_sourceFields.find(L"CLOSE");
		if(sIter == CPlotBaseMe::m_sourceFields.end())
		{
			return nO;
		}
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		map<int,CPlotMarkMe*>::iterator sIter3 = CPlotBaseMe::m_marks.find(3);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		int dIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter3->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float x2 = CPlotBaseMe::PX(bIndex);
		float x3 = CPlotBaseMe::PX(cIndex);
		float x4 = CPlotBaseMe::PX(dIndex);
		float y1 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(aIndex, sIter->second));
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(cIndex, sIter->second));
		float y4 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(dIndex, sIter->second));
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x3, y3))
		{
			return ActionType_AT3;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x4, y4))
		{
			return ActionType_AT4;
		}
		float k = 0;
		float b = 0;
		if (CPlotBaseMe::SelectRay(mouseOverPoint, x1, y1, x2, y2, &k, &b))
		{
			return ActionType_MOVE;
		}
		int workingAreaWidth = CPlotBaseMe::GetWorkingAreaWidth();
		if (k != 0 || b != 0)
		{
			float x3_newx = (float)workingAreaWidth;
			if (bIndex < aIndex)
			{
				x3_newx = 0;
			}
			b = y3 - (x3 * k);
			float x3_newy = (k * x3_newx) + b;
			if (!CPlotBaseMe::SelectRay(mouseOverPoint, x3, y3, x3_newx, x3_newy))
			{
				float x4_newx = (float)workingAreaWidth;
				if (bIndex < aIndex)
				{
					x4_newx = 0;
				}
				b = y4 - (x4 * k);
				float x4_newy = (k * x4_newx) + b;
				if (!CPlotBaseMe::SelectRay(mouseOverPoint, x4, y4, x4_newx, x4_newy))
				{
					return nO;
				}
			}
			return ActionType_MOVE;
		}
		if (y1 >= y2)
		{
			if (!CPlotBaseMe::SelectRay(mouseOverPoint, x3, y3, x3, 0) && !CPlotBaseMe::SelectRay(mouseOverPoint, x4, y4, x4, 0))
			{
				return nO;
			}
			return ActionType_MOVE;
		}
		int workingAreaHeight = CPlotBaseMe::GetWorkingAreaHeight();
		if (CPlotBaseMe::SelectRay(mouseOverPoint, x3, y3, x3, (float) workingAreaHeight))
		{
			return ActionType_MOVE;
		}
		if (CPlotBaseMe::SelectRay(mouseOverPoint, x4, y4, x4, (float) workingAreaHeight))
		{
			return ActionType_MOVE;
		}
	}
	return nO;
}

bool P001::OnCreate(const POINT& mp)
{
	bool flag = CPlotBaseMe::Create4CandlePoints(mp);
	if (flag)
	{
		map<int,CPlotMarkMe*>::iterator sIter = CPlotBaseMe::m_marks.find(1);
		CPlotMarkMe* mark = sIter->second;
		CPlotMarkMe* newMark = new CPlotMarkMe(mark->Index, mark->Key, CPlotBaseMe::GetNumberValue(mp));
		delete mark;
		mark = 0;
		sIter->second = newMark;
	}
	return flag;
}

void P001::OnMoveStart()
{
	m_action = CPlotBaseMe::GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotMarkMe *mark = new CPlotMarkMe(sIterPlot->second->Index, sIterPlot->second->Key, sIterPlot->second->Value);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, mark));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		mark = new CPlotMarkMe(sIterPlot->second->Index, sIterPlot->second->Key, sIterPlot->second->Value);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, mark));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		mark = new CPlotMarkMe(sIterPlot->second->Index, sIterPlot->second->Key, sIterPlot->second->Value);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, mark));
		sIterPlot = CPlotBaseMe::m_marks.find(3);
		mark = new CPlotMarkMe(sIterPlot->second->Index, sIterPlot->second->Key, sIterPlot->second->Value);
		CPlotBaseMe::m_startMarks.insert(make_pair(3, mark));
	}
}

void P001::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	int size = (int)pList->size();
	if (size > 0)
	{
		map<String,int>::iterator sIterClose = CPlotBaseMe::m_sourceFields.find(L"CLOSE");
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		map<int,CPlotMarkMe*>::iterator sIter3 = CPlotBaseMe::m_marks.find(3);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		int dIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter3->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float x2 = CPlotBaseMe::PX(bIndex);
		float x3 = CPlotBaseMe::PX(cIndex);
		float x4 = CPlotBaseMe::PX(dIndex);
		float y1 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(aIndex, sIterClose->second));
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(cIndex, sIterClose->second));
		float y4 = CPlotBaseMe::PY(CPlotBaseMe::m_dataSource->Get2(dIndex, sIterClose->second));
		float k = 0;
		float b = 0;
		CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
		CPlotBaseMe::DrawRay(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2, k, b);
		if (k != 0 || b != 0)
		{
			float x3_newx = (float)CPlotBaseMe::GetWorkingAreaWidth();
			if (bIndex < aIndex)
			{
				x3_newx = 0;
			}
			b = y3 - (x3 * k);
			float x3_newy = (k * x3_newx) + b;
			CPlotBaseMe::DrawRay(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x3, y3, x3_newx, x3_newy, k, b);
			float x4_newx = (float)CPlotBaseMe::GetWorkingAreaWidth();
			if (bIndex < aIndex)
			{
				x4_newx = 0;
			}
			b = y4 - (x4 * k);
			float x4_newy = (k * x4_newx) + b;
			CPlotBaseMe::DrawRay(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x4, y4, x4_newx, x4_newy, k, b);
		}
		else if (y1 >= y2)
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x3, y3, x3, (float)0);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x4, y4, x4, (float)0);
		}
		else
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x3, y3, x3, (float) CPlotBaseMe::GetWorkingAreaHeight());
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x4, y4, x4, (float) CPlotBaseMe::GetWorkingAreaHeight());
		}
		if (CPlotBaseMe::IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
			CPlotBaseMe::DrawSelect(paint, lineColor, x4, y4);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P002::P002()
{
	SetPlotType(L"ANGLELINE");
}

ActionType P002::GetAction()
{
	ActionType nO = ActionType_NO;
	int size = (int)CPlotBaseMe::m_marks.size();
	if (size > 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		vector<CPlotMarkMe**> list;
		CPlotMarkMe** arry1 = new CPlotMarkMe*[2]; 
		arry1[0] = sIter0->second;
		arry1[1] = sIter1->second;
		CPlotMarkMe** arry2 = new CPlotMarkMe*[2];
		arry2[0] = sIter0->second;
		arry2[1] = sIter2->second; 
		list.push_back(arry1);
		list.push_back(arry2);
		int count = (int)list.size();
		for (int i = 0; i < count; i++)
		{
			CPlotMarkMe *markA = list[i][0];
			CPlotMarkMe *markB = list[i][1];
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(markA->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(markB->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			float y1 = CPlotBaseMe::PY(markA->Value);
			float y2 = CPlotBaseMe::PY(markB->Value);
			if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1))
			{
				return ActionType_AT1;
			}
			if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
			{
				if (i == 0)
				{
					return ActionType_AT2;
				}
				return ActionType_AT3;
			}
			float k = 0;
			float b = 0;
			CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
			if ((k != 0) || (b != 0))
			{
				if (((((float) mouseOverPoint.y) / ((mouseOverPoint.x * k) + b)) >= 0.9) 
					&& ((((float) mouseOverPoint.y) / ((mouseOverPoint.x * k) + b)) <= 1.1))
				{
					if (x1 >= x2)
					{
						if (mouseOverPoint.x > (x1 + 5))
						{
							return ActionType_NO;
						}
					}
					else if ((x1 < x2) && (mouseOverPoint.x < (x1 - 5)))
					{
						return ActionType_NO;
					}
					return ActionType_MOVE;
				}
			}
			else if ((mouseOverPoint.x >= (x1 - (m_lineWidth * 5))) && (mouseOverPoint.x <= (x1 + (m_lineWidth * 5))))
			{
				if (y1 >= y2)
				{
					if (mouseOverPoint.y <= (y1 - 5))
					{
						return ActionType_MOVE;
					}
				}
				else if (mouseOverPoint.y >= (y1 - 5))
				{
					return ActionType_MOVE;
				}
			}
		}
	}
	return nO;
}

bool P002::OnCreate(const POINT& mp)
{
	return Create3Points(mp);
}

void P002::OnMoveStart()
{
	m_action = CPlotBaseMe::GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (m_action != ActionType_NO)
	{
		if (m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P002::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	int size = (int)pList->size();
	if (size > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		vector<CPlotMarkMe**> marks;
		CPlotMarkMe** arry1 = new CPlotMarkMe*[2]; 
		arry1[0] = sIter0->second;
		arry1[1] = sIter1->second;
		CPlotMarkMe** arry2 = new CPlotMarkMe*[2];
		arry2[0] = sIter0->second;
		arry2[1] = sIter2->second; 
		marks.push_back(arry1);
		marks.push_back(arry2);

		int count = (int)marks.size();
		for (int i = 0; i < count; i++)
		{
			CPlotMarkMe *markA = marks[i][0];
			CPlotMarkMe *markB = marks[i][1];
			float y1 = CPlotBaseMe::PY(markA->Value);
			float y2 = CPlotBaseMe::PY(markB->Value);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(markA->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(markB->Key);
			int length = 0;
			float *lineParams = CPlotBaseMe::GetLineParams(markA, markB, &length);
			float a = 0;
			float b = 0;
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			if (lineParams && length >= 2)
			{
				a = lineParams[0];
				b = lineParams[1];
				float leftX = 0;
				float leftY = (leftX * a) + b;
				float rightX = (float)CPlotBaseMe::GetWorkingAreaWidth();
				float rightY = (rightX * a) + b;
				if (x1 >= x2)
				{
					CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, leftX, leftY, x2, y2);
				}
				else
				{
					CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x1, y1, rightX, rightY);
				}
				CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x1, y1, x2, y2);
			}
			else if (y1 >= y2)
			{
				CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x1, y1, x2, (float)0);
			}
			else
			{
				CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x1, y1, x2, (float) CPlotBaseMe::GetWorkingAreaHeight());
			}
			if (CPlotBaseMe::IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
P003::P003()
{
	SetPlotType(L"CIRCUMCIRCLE");
}

ActionType P003::GetAction()
{
	ActionType nO = ActionType_NO;
	int size = (int)CPlotBaseMe::m_marks.size();
	if (size == 0)
	{
		return nO;
	}
	POINT mp = CPlotBaseMe::GetMouseOverPoint();
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
	float y1 = PY(sIter0->second->Value);
	float y2 = PY(sIter1->second->Value);
	float y3 = PY(sIter2->second->Value);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float x2 = CPlotBaseMe::PX(eIndex);
	float x3 = CPlotBaseMe::PX(pIndex);
	float oX = 0;
	float oY = 0;
	float r = 0;
	CMathLibMe::M110(x1, y1, x2, y2, x3, y3, &oX, &oY, &r);
	float clickX = mp.x - oX;
	float clickY = mp.y - oY;
	double ellipseValue = (clickX * clickX) + (clickY * clickY);
	if ((ellipseValue < ((r * r) * 0.8)) || (ellipseValue > ((r * r) * 1.2)))
	{
		return nO;
	}
	if (CPlotBaseMe::SelectPoint(mp, x1, y1))
	{
		return ActionType_AT1;
	}
	if (CPlotBaseMe::SelectPoint(mp, x2, y2))
	{
		return ActionType_AT2;
	}
	if (CPlotBaseMe::SelectPoint(mp, x3, y3))
	{
		return ActionType_AT3;
	}
	return ActionType_MOVE;
}

bool P003::OnCreate(const POINT& mp)
{
	return Create3Points(mp);
}

void P003::OnMoveStart()
{
	m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (m_action != ActionType_NO)
	{
		if (m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P003::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	int size = (int)pList->size();
	if (size > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		float oX = 0;
		float oY = 0;
		float r = 0;
		CMathLibMe::M110(x1, y1, x2, y2, x3, y3, &oX, &oY, &r);
		CPlotBaseMe::DrawEllipse(paint, lineColor, m_lineWidth, m_lineStyle, oX - r, oY - r, oX + r, oY + r);
		if (CPlotBaseMe::IsSelected())
		{
			CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x1, y1, x2, y2);
			CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x2, y2, x3, y3);
			CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, x3, y3, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P004::P004()
{
	SetPlotType(L"ARROWSEGMENT");
}

ActionType P004::GetAction()
{
	ActionType nO = ActionType_NO;
	int size = (int)CPlotBaseMe::m_marks.size();
	if (size > 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		if (CPlotBaseMe::GetLineParams(sIter0->second, sIter1->second, &length) && length > 0)
		{
			if ((mp.x >= (x1 - (m_lineWidth * 2.5))) && (mp.x <= (x1 + (m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.x >= (x2 - (m_lineWidth * 2.5))) && (mp.x <= (x2 + (m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		else
		{
			if ((mp.y >= (y1 - (m_lineWidth * 5))) && (mp.y <= (y1 + (m_lineWidth * 5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (m_lineWidth * 5))) && (mp.y <= (y2 + (m_lineWidth * 5))))
			{
				return ActionType_AT2;
			}
		}
		if (CPlotBaseMe::SelectSegment(mp, x1, y1, x2, y2))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P004::OnCreate(const POINT& mp)
{
	return Create2PointsB(mp);
}

void P004::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (m_action != ActionType_NO)
	{
		if (m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P004::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	int size = (int)pList->size();
	if (size > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int y1 = (int)CPlotBaseMe::PY(sIter0->second->Value);
		int y2 = (int)CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int x1 = (int)CPlotBaseMe::PX(bIndex);
		int x2 = (int)CPlotBaseMe::PX(eIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, m_lineWidth, m_lineStyle, (float)x1, (float)y1, (float)x1, (float)y2);
		double slopy = 0.0;
		double cosy = 0.0;
		double siny = 0.0;
		slopy = atan2((double)(y1 - y2), (double)(x1 - x2));
		cosy = cos(slopy);
		siny = sin(slopy);
		POINT point = { x2, y2 };
		POINT point2 = { point.x + ((int) (((10.0 * cosy) - (5.0 * siny)) + 0.5)),
			point.y + ((int) (((10.0 * siny) + (5.0 * cosy)) + 0.5))};
		POINT point3 = { point.x + ((int) (((10.0 * cosy) + (5.0 * siny)) + 0.5)), 
			point.y - ((int) (((5.0 * cosy) - (10.0 * siny)) + 0.5))};
		POINT *points = new POINT[3];
		points[0] = point;
		points[1] = point2;
		points[2] = point3;
		CPlotBaseMe::FillPolygon(paint, lineColor, points, 3);
		if (CPlotBaseMe::IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float)x1, (float)y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float)x2, (float)y2);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RECT P005::GetDownArrowRect(float x, float y, float width)
{
	RECT rect = {(LONG)x, (LONG)y, (LONG)(x + width), (LONG)(y + width)};
	return rect;
}


P005::P005()
{
	SetPlotType(L"DOWNARROW");
}

ActionType P005::GetAction()
{
	ActionType nO = ActionType_NO;
	int size = (int)CPlotBaseMe::m_marks.size();
	if (size != 0)
	{
		map<int, CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		double num = sIter0->second->Value;
		int rowIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(rowIndex);
		float bottom = CPlotBaseMe::PY(num);
		int width = 10;
		RECT rect = { (LONG)(x1 - (width / 2)), (LONG)(bottom - ((width * 3) / 2)), (LONG)(x1 + (width / 2)), (LONG)bottom };
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		if (((mouseOverPoint.x >= rect.left) && (mouseOverPoint.x <= rect.right)) 
			&& ((mouseOverPoint.y >= rect.top) && (mouseOverPoint.y <= rect.bottom)))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P005::OnCreate(const POINT& mp)
{
	return CreatePoint(mp);
}

void P005::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P005::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	int size = (int)pList->size();
	if (size > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		double num = sIter0->second->Value;
		int rowIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int x = (int) CPlotBaseMe::PX(rowIndex);
		int y = (int) CPlotBaseMe::PY(num);
		int width = 10;
		POINT point = {x, y};
		POINT point2 = {x + (width / 2), y - width};
		POINT point3 = {x + (width / 4), y - width};
		POINT point4 = {x + (width / 4), y - ((width * 3) / 2)};
		POINT point5 = {x - (width / 4), y - ((width * 3) / 2)};
		POINT point6 = {x - (width / 4), y - width};
		POINT point7 = {x - (width / 2), y - width};
		POINT *points = new POINT[7];
		points[0] = point;
		points[1] = point2;
		points[2] = point3;
		points[3] = point4;
		points[4] = point5;
		points[5] = point6;
		points[6] = point7;
		CPlotBaseMe::FillPolygon(paint, lineColor, points, 7);
		if (CPlotBaseMe::IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) (x - (width / 2)), (float) (y - ((width * 3) / 2)));
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float* P006::GetDropLineParams(map<int, CPlotMarkMe*> *pList)
{
	if ((int)pList->size() == 0)
	{
		return 0;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	float num = CPlotBaseMe::PY(sIter0->second->Value);
	int rowIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	float x1 = CPlotBaseMe::PX(rowIndex);
	float a = 1;
	float b = num - x1;
	float *retArray = new float[2];
	retArray[0] = a;
	retArray[1] = b;
	return retArray;
}


P006::P006()
{
	SetPlotType(L"DROPLINE");
}

ActionType P006::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		float* dropLineParams = GetDropLineParams(&m_marks);
		if (((dropLineParams) && (((mouseOverPoint.y - (dropLineParams[0] * mouseOverPoint.x)) - dropLineParams[1]) >= (CPlotBaseMe::m_lineWidth * -5))) 
			&& (((mouseOverPoint.y - (dropLineParams[0] * mouseOverPoint.x)) - dropLineParams[1]) <= (CPlotBaseMe::m_lineWidth * 5)))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P006::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P006::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P006::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float* dropLineParams = GetDropLineParams(pList);
		float a = dropLineParams[0];
		float b = dropLineParams[1];
		float leftX = 0;
		float leftY = (leftX * a) + b;
		float rightX = (float)CPlotBaseMe::GetWorkingAreaWidth();
		float rightY = (rightX * a) + b;
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P009::P009()
{
	SetPlotType(L"ELLIPSE");
}

ActionType P009::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		double fValue = sIter0->second->Value;
		double eValue = sIter1->second->Value;
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(fValue);
		float y2 = CPlotBaseMe::PY(eValue);
		float x = 0;
		float y = 0;
		if (x1 >= x2)
		{
			x = x2;
		}
		else
		{
			x = x2 - ((x2 - x1) * 2);
		}
		if (y1 >= y2)
		{
			y = y1 - ((y1 - y2) * 2);
		}
		else
		{
			y = y1;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
		{
			return ActionType_AT2;
		}
		float width = abs((float) ((x1 - x2) * 2));
		float height = abs((float) ((y1 - y2) * 2));
		float oX = x + (width / 2);
		float oY = y + (height / 2);
		float a = 0;
		float b = 0;
		CMathLibMe::M108(width, height, &a, &b);
		if ((a != 0) && (b != 0))
		{
			float clickX = mouseOverPoint.x - oX;
			float clickY = mouseOverPoint.y - oY;
			double ellipseValue = ((clickX * clickX) / (a * a)) + ((clickY * clickY) / (b * b));
			if ((ellipseValue >= 0.8) && (ellipseValue <= 1.2))
			{
				nO = ActionType_MOVE;
			}
		}
	}
	return nO;
}

bool P009::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P009::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_AT1)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		else if (CPlotBaseMe::m_action == ActionType_AT2)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P009::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		double fValue = sIter0->second->Value;
		double eValue = sIter1->second->Value;
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(fValue);
		float y2 = CPlotBaseMe::PY(eValue);
		float x = x1 - (x1 - x2);
		float y = 0;
		float width = (x1 - x2) * 2;
		float height = 0;
		if (y1 >= y2)
		{
			height = (y1 - y2) * 2;
		}
		else
		{
			height = (y2 - y1) * 2;
		}
		y = y2 - (height / 2);
		if (width == 0)
		{
			width = 1;
		}
		if (height == 0)
		{
			height = 1;
		}
		if ((width == 1) && (height == 1))
		{
			CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x - 2, y - 2, x + 2, y + 2);
		}
		else
		{
			CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x, y, x + width, y + height);
		}
		if (CPlotBaseMe::IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P010::FibonacciEllipseParam(map<int, CPlotMarkMe*> *pList, int *length)
{
	if ((int)pList->size() == 0)
	{
		return 0;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float x2 = CPlotBaseMe::PX(eIndex);
	float y1 = CPlotBaseMe::PY(sIter0->second->Value);
	float y2 = CPlotBaseMe::PY(sIter1->second->Value);
	float r1 = (float)sqrt((double)(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
	float r2 = (float)(r1 * 0.236);
	float r3 = (float)(r1 * 0.382);
	float r4 = (float)(r1 * 0.5);
	float r5 = (float)(r1 * 0.618);
	*length = 9;
	float* retArray = new float[9];
	retArray[0] = x1;
	retArray[1] = y1;
	retArray[2] = x2;
	retArray[3] = y2;
	retArray[4] = r1;
	retArray[5] = r2;
	retArray[6] = r3;
	retArray[7] = r4;
	retArray[8] = r5;
	return retArray;
}


P010::P010()
{
	SetPlotType(L"FIBOELLIPSE");
}

ActionType P010::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		int length = 0;
		float* numArray = FibonacciEllipseParam(&m_marks, &length);
		float x1 = numArray[0];
		float y1 = numArray[1];
		float x2 = numArray[2];
		float y2 = numArray[3];
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectSegment(mouseOverPoint, x1, y1, x2, y2))
		{
			return ActionType_MOVE;
		}
		POINT point2 = {mouseOverPoint.x - x1, mouseOverPoint.y - y1};
		float round = (point2.x * point2.x) + (point2.y * point2.y);
		for (int i = 4; i < 9; i++)
		{
			float r = numArray[i];
			if (((round / (r * r)) >= 0.9) && ((round / (r * r)) <= 1.1))
			{
				return ActionType_MOVE;
			}
		}
	}
	return nO;
}

bool P010::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P010::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P010::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P010::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() > 0)
	{
		int length = 0;
		float* numArray = FibonacciEllipseParam(pList, &length);
		float x1 = numArray[0];
		float y1 = numArray[1];
		float x2 = numArray[2];
		float y2 = numArray[3];
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x1, y1, x2, y2);
		float r1 = (numArray[4] >= 4) ? numArray[4] : 4;
		float r2 = (numArray[5] >= 4) ? numArray[5] : 4;
		float r3 = (numArray[6] >= 4) ? numArray[6] : 4;
		float r4 = (numArray[7] >= 4) ? numArray[7] : 4;
		float r5 = (numArray[8] >= 4) ? numArray[8] : 4;
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r1, y1 - r1, x1 + r1, y1 + r1);
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r2, y1 - r2, x1 + r2, y1 + r2);
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r3, y1 - r3, x1 + r3, y1 + r3);
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r4, y1 - r4, x1 + r4, y1 + r4);
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r5, y1 - r5, x1 + r5, y1 + r5);
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
		if (r5 > 20)
		{
			SIZE size = CPlotBaseMe::TextSize(paint, L"23.6%", CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, L"23.6%", lineColor, CPlotBaseMe::m_font, (float) (x1 - (size.cx / 2)), (float) ((y1 - r1) - size.cy));
			size = CPlotBaseMe::TextSize(paint, L"38.2%", CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, L"38.2%", lineColor, CPlotBaseMe::m_font, (float) (x1 - (size.cx / 2)), (float) ((y1 - r2) - size.cy));
			size = CPlotBaseMe::TextSize(paint, L"50.0%", CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, L"50.0%", lineColor, CPlotBaseMe::m_font, (float) (x1 - (size.cx / 2)), (float) ((y1 - r3) - size.cy));
			size = CPlotBaseMe::TextSize(paint, L"61.8%", CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, L"61.8%", lineColor, CPlotBaseMe::m_font, (float) (x1 - (size.cx / 2)), (float) ((y1 - r4) - size.cy));
			size = CPlotBaseMe::TextSize(paint, L"100%", CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, L"100%", lineColor, CPlotBaseMe::m_font, (float) (x1 - (size.cx / 2)), (float) ((y1 - r5) - size.cy));
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P011::P011()
{
	SetPlotType(L"FIBOFANLINE");
}

ActionType P011::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() == 0)
	{
		return nO;
	}
	POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	float y1 = CPlotBaseMe::PY(sIter0->second->Value);
	float y2 = CPlotBaseMe::PY(sIter1->second->Value);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float x2 = CPlotBaseMe::PX(eIndex);
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
	{
		return ActionType_AT1;
	}
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
	{
		return ActionType_AT2;
	}
	POINTF firstP = { x2, y2 - ((y2 - y1) * 0.382) };
	POINTF secondP = { x2, y2 - ((y2 - y1) * 0.5)};
	POINTF thirdP = { x2, y2 - ((y2 - y1) * 0.618)};
	POINTF startP = { x1, y1};
	if (!CPlotBaseMe::SelectSegment(mouseOverPoint, x1, y1, x2, y2))
	{
		if (((x2 <= x1) || (mouseOverPoint.x < (x1 - 2))) && ((mouseOverPoint.x > (x1 + 2)) || (x2 >= x1)))
		{
			return nO;
		}
		if ((!CPlotBaseMe::SelectRay(mouseOverPoint, startP.x, startP.y, firstP.x, firstP.y) 
			&& !CPlotBaseMe::SelectRay(mouseOverPoint, startP.x, startP.y, secondP.x, secondP.y)) 
			&& !CPlotBaseMe::SelectRay(mouseOverPoint, startP.x, startP.y, thirdP.x, thirdP.y))
		{
			return nO;
		}
	}
	return ActionType_MOVE;
}

bool P011::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P011::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P011::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P011::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x1, y1, x2, y2);
		if (IsSelected() || (x1 == x2))
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
		if ((x1 != x2) && (y1 != y2))
		{
			POINTF firstP = {x2, y2 - ((y2 - y1) * 0.382)};
			POINTF secondP = {x2, y2 - ((y2 - y1) * 0.5)};
			POINTF thirdP = {x2, y2 - ((y2 - y1) * 0.618)};
			POINTF startP = {x1, y1};
			vector<POINTF> listP;
			POINTF *collection = new POINTF[3];
			collection[0] = firstP;
			listP.push_back(firstP);
			collection[1] = secondP;
			listP.push_back(secondP);
			collection[2] = thirdP;
			listP.push_back(thirdP);
			int count = (int)listP.size();
			for (int i = 0; i < count; i++)
			{
				float k = 0;
				float b = 0;
				CMathLibMe::M107(startP.x, startP.y, listP[i].x, listP[i].y, 0, 0, &k, &b);
				float newX = 0;
				float newY = 0;
				if (x2 > x1)
				{
					newY = (k * CPlotBaseMe::GetWorkingAreaWidth()) + b;
					newX = CPlotBaseMe::GetWorkingAreaWidth();
				}
				else
				{
					newY = b;
					newX = 0;
				}
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, startP.x, startP.y, newX, newY);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

vector<int> P012::GetFibonacciTimeZonesParam(map<int,CPlotMarkMe*> *pList)
{
	vector<int> fValueList;
	if ((int)pList->size() == 0)
	{
		return fValueList;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	double fValue = sIter0->second->Value;
	int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int pos = 1;
	int fibonacciValue = 1;
	fValueList.push_back(aIndex);
	CChartMe *chart = CPlotBaseMe::GetChart();
	while ((aIndex + fibonacciValue) <= chart->GetLastVisibleIndex())
	{
		fibonacciValue = CMathLibMe::M112(pos);
		fValueList.push_back(aIndex + fibonacciValue);
		pos++;
	}
	return fValueList;
}


P012::P012()
{
	SetPlotType(L"FIBOTIMEZONE");
}

ActionType P012::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		vector<int> params = GetFibonacciTimeZonesParam(&m_marks);
		vector<int>::iterator sIter = params.begin();
		for(; sIter != params.end(); ++sIter)
		{
			int rI = *sIter;
			CChartMe *chart = CPlotBaseMe::GetChart();
			if ((rI >= chart->GetFirstVisibleIndex()) && (rI <= chart->GetLastVisibleIndex()))
			{
				float x1 = CPlotBaseMe::PX(rI);
				if ((mouseOverPoint.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mouseOverPoint.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
				{
					return ActionType_MOVE;
				}
			}
		}
	}
	return nO;
}

bool P012::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P012::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P012::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		vector<int> fibonacciTimeZonesParam = GetFibonacciTimeZonesParam(pList);
		CChartMe *chart = CPlotBaseMe::GetChart();
		int length = (int)fibonacciTimeZonesParam.size();
		for (int i = 0; i < length; i++)
		{
			int rI = fibonacciTimeZonesParam[i];
			if ((rI >= chart->GetFirstVisibleIndex()) && (rI <= chart->GetLastVisibleIndex()))
			{
				float x1 = CPlotBaseMe::PX(rI);
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
				if ((i == 0) && IsSelected())
				{
					CPlotBaseMe::DrawSelect(paint, lineColor, x1, (float) (CPlotBaseMe::GetWorkingAreaHeight() / 2));
				}
				CPlotBaseMe::DrawText(paint, CStrMe::ConvertIntToStr(CMathLibMe::M112(i)).c_str(), lineColor, CPlotBaseMe::m_font, x1, 0);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P014::P014()
{
	SetPlotType(L"GANNBOX");
}

ActionType P014::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() == 0)
	{
		return nO;
	}
	return GetClickStatus();
}

ActionType P014::GetClickStatus()
{
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);

	POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
	RECT rectangle = CPlotBaseMe::GetRectangle(sIter0->second, sIter1->second);
	int x1 = rectangle.left;
	int y1 = rectangle.top;
	int x2 = rectangle.right;
	int y2 = rectangle.top;
	int x3 = rectangle.left;
	int y3 = rectangle.bottom;
	int x4 = rectangle.right;
	int y4 = rectangle.bottom;
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, (float) x1, (float) y1))
	{
		return ActionType_AT1;
	}
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, (float) x2, (float) y2))
	{
		return ActionType_AT2;
	}
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, (float) x3, (float) y3))
	{
		return ActionType_AT3;
	}
	if (CPlotBaseMe::SelectPoint(mouseOverPoint, (float) x4, (float) y4))
	{
		return ActionType_AT4;
	}
	int sub = (int)(CPlotBaseMe::m_lineWidth * 2.5);
	RECT bigRect = {rectangle.left - sub, rectangle.top - sub, rectangle.right + sub, rectangle.bottom + sub};
	if (((mouseOverPoint.x >= bigRect.left) && (mouseOverPoint.x <= bigRect.right)) && ((mouseOverPoint.y >= bigRect.top) && (mouseOverPoint.y <= bigRect.bottom)))
	{
		if (((rectangle.right - rectangle.left) <= 4) || ((rectangle.bottom - rectangle.top) <= 4))
		{
			return ActionType_MOVE;
		}
		RECT smallRect = {rectangle.left + sub, rectangle.top + sub, rectangle.right - sub, rectangle.bottom - sub};
		if (((mouseOverPoint.x < smallRect.left) || (mouseOverPoint.x > smallRect.right)) || ((mouseOverPoint.y < smallRect.top) || (mouseOverPoint.y > smallRect.bottom)))
		{
			return ActionType_MOVE;
		}
		x1 = rectangle.left;
		y1 = rectangle.bottom;
		x2 = rectangle.right;
		y2 = rectangle.top;
		POINT startP = {x1, y1};
		int length = 0;
		POINT* listP = GetGannBoxPoints((float)x1, (float)y1, (float)x2, (float)y2, &length);
		for (int i = 0; i < length; i++)
		{
			if (CPlotBaseMe::SelectLine(mouseOverPoint, (float)startP.x, (float)startP.y, (float)listP[i].x, (float)listP[i].y))
			{
				return ActionType_MOVE;
			}
		}
		if (CPlotBaseMe::SelectLine(mouseOverPoint, (float) startP.x, (float) startP.y, (float) x2, (float) y2))
		{
			return ActionType_MOVE;
		}
		x1 = rectangle.left;
		y1 = rectangle.top;
		x2 = rectangle.right;
		y2 = rectangle.bottom;
		length = 0;
		listP = GetGannBoxPoints((float)x1, (float)y1, (float)x2, (float)y2, &length);
		for (int j = 0; j < length; j++)
		{
			if (CPlotBaseMe::SelectLine(mouseOverPoint, (float)startP.x, (float)startP.y, (float)listP[j].x, (float)listP[j].y))
			{
				return ActionType_MOVE;
			}
		}
		POINT point = {x1, y1};
		startP = point;
		if (CPlotBaseMe::SelectLine(mouseOverPoint, (float) startP.x, (float) startP.y, (float) x2, (float) y2))
		{
			return ActionType_MOVE;
		}
	}
	return ActionType_NO;
}

POINT* P014::GetGannBoxPoints(float x1, float y1, float x2, float y2, int *length)
{
	POINT firstP = {x2, y2 - ((y2 - y1) * 0.875)};
	POINT secondP = {x2, y2 - ((y2 - y1) * 0.75)};
	POINT thirdP = {x2, y2 - ((y2 - y1) * 0.67)};
	POINT forthP = {x2, y2 - ((y2 - y1) * 0.5)};
	POINT fifthP = {x2 - ((x2 - x1) * 0.875), y2};
	POINT sixthP = {x2 - ((x2 - x1) * 0.75), y2};
	POINT seventhP = {x2 - ((x2 - x1) * 0.67), y2};
	POINT eighthP = {x2 - ((x2 - x1) * 0.5), y2};
	*length = 8;
	POINT* points = new POINT[8];
	points[0] = firstP;
	points[1] = secondP;
	points[2] = thirdP;
	points[3] = forthP;
	points[4] = fifthP;
	points[5] = sixthP;
	points[6] = seventhP;
	points[7] = eighthP;
	return points;
}

bool P014::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P014::OnMoveStart()
{

	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	RECT rectangle = CPlotBaseMe::GetRectangle(CPlotBaseMe::m_marks[0], CPlotBaseMe::m_marks[1]);
	int x1 = rectangle.left;
	int y1 = rectangle.top;
	int x2 = rectangle.right;
	int y2 = rectangle.top;
	int x3 = rectangle.left;
	int y3 = rectangle.bottom;
	int x4 = rectangle.right;
	int y4 = rectangle.bottom;
	POINT point = {0, 0};
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_AT1:
		point.x = x4;
		point.y = y4;
		m_oppositePoint = point;
		break;

	case ActionType_AT2:
		point.x = x3;
		point.y = y3;
		m_oppositePoint = point;
		break;

	case ActionType_AT3:
		point.x = x2;
		point.y = y2;
		m_oppositePoint = point;
		break;

	case ActionType_AT4:
		point.x = x1;
		point.y = y1;
		m_oppositePoint = point;
		break;
	}
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P014::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(movingPoint);
		return;
	case ActionType_AT1:
	case ActionType_AT2:
	case ActionType_AT3:
	case ActionType_AT4:
		CPlotBaseMe::Resize(movingPoint, m_oppositePoint);
		return;
	}
}

void P014::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P014::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		RECT rect = CPlotBaseMe::GetRectangle(sIter0->second, sIter1->second);
		int leftVScaleWidth = CPlotBaseMe::GetChart()->GetLeftVScaleWidth();
		int titleHeight = CPlotBaseMe::GetDiv()->GetTitleBar()->GetHeight();
		RECT clipRect = {rect.left + leftVScaleWidth, rect.top + titleHeight, rect.right + leftVScaleWidth, rect.bottom + titleHeight};
		paint->SetClip(clipRect);
		if (((rect.right - rect.left) > 0) && ((rect.bottom - rect.top) > 0))
		{
			CPlotBaseMe::DrawRect(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, rect.left, rect.top, rect.right, rect.bottom);
		}
		int x1 = rect.left;
		int y1 = rect.bottom;
		int x2 = rect.right;
		int y2 = rect.top;
		if ((x1 != x2) && (y1 != y2))
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) x1, (float) y1, (float) x2, (float) y2);
			POINT startP = {x1, y1};
			int length = 0;
			POINT* listP = GetGannBoxPoints((float)x1, (float)y1, (float)x2, (float)y2, &length);
			float k = 0;
			float b = 0;
			for (int i = 0; i < length; i++)
			{
				CMathLibMe::M107((float)startP.x, (float)startP.y, (float)listP[i].x, (float)listP[i].y, 0, 0, &k, &b);
				float newX = 0;
				float newY = 0;
				if (x2 > x1)
				{
					newY = (k * x2) + b;
					newX = x2;
				}
				else
				{
					newY = b;
					newX = x1;
				}
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) startP.x, (float) startP.y, newX, newY);
			}
			x1 = rect.left;
			y1 = rect.top;
			x2 = rect.right;
			y2 = rect.bottom;
			length = 0;
			listP = GetGannBoxPoints((float)x1, (float)y1, (float)x2, (float)y2, &length);
			POINT point = {x1, y1};
			startP = point;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) x1, (float) y1, (float) x2, (float) y2);
			for (int j = 0; j < length; j++)
			{
				CMathLibMe::M107((float)startP.x, (float)startP.y, (float)listP[j].x, (float)listP[j].y, 0, 0, &k, &b);
				float newX = 0;
				float newY = 0;
				if (x2 > x1)
				{
					newY = (k * x2) + b;
					newX = x2;
				}
				else
				{
					newY = b;
					newX = x1;
				}
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) startP.x, (float) startP.y, newX, newY);
			}
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rect.left, (float) rect.top);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rect.right, (float) rect.top);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rect.left, (float) rect.bottom);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rect.right, (float) rect.bottom);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P016::P016()
{
	SetPlotType(L"GANNLINE");
}

ActionType P016::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectSegment(mp, x1, y1, x2, y2))
		{
			return ActionType_MOVE;
		}
		POINTF firstP = {x2, y2 - ((y2 - y1) * 0.875)};
		POINTF secondP = {x2, y2 - ((y2 - y1) * 0.75)};
		POINTF thirdP = {x2, y2 - ((y2 - y1) * 0.67)};
		POINTF forthP = {x2, y2 - ((y2 - y1) * 0.5)};
		POINTF fifthP = {x2 - ((x2 - x1) * 0.875), y2};
		POINTF sixthP = {x2 - ((x2 - x1) * 0.75), y2};
		POINTF seventhP = {x2 - ((x2 - x1) * 0.67), y2};
		POINTF eighthP = {x2 - ((x2 - x1) * 0.5), y2};
		POINTF startP = {x1, y1};
		vector<POINTF> listP;
		POINTF *collection = new POINTF[8];
		collection[0] = firstP;
		listP.push_back(firstP);
		collection[1] = secondP;
		listP.push_back(secondP);
		collection[2] = thirdP;
		listP.push_back(thirdP);
		collection[3] = forthP;
		listP.push_back(forthP);
		collection[4] = fifthP;
		listP.push_back(fifthP);
		collection[5] = sixthP;
		listP.push_back(sixthP);
		collection[6] = seventhP;
		listP.push_back(seventhP);
		collection[7] = eighthP;
		listP.push_back(eighthP);
		if (((x2 <= x1) || (mp.x < (x1 - 2))) && ((mp.x > (x1 + 2)) || (x2 >= x1)))
		{
			return nO;
		}
		int listSize = (int)listP.size();
		for (int i = 0; i < listSize; i++)
		{
			if (CPlotBaseMe::SelectLine(mp, startP.x, startP.y, listP[i].x, listP[i].y))
			{
				return ActionType_MOVE;
			}
		}
	}
	return nO;
}

bool P016::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P016::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_AT1)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		else if (CPlotBaseMe::m_action == ActionType_AT2)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P016::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P016::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x1, y1, x2, y2);
		if (IsSelected() || (x1 == x2))
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
		if ((x1 != x2) && (y1 != y2))
		{
			POINTF firstP = {x2, y2 - ((y2 - y1) * 0.875)};
			POINTF secondP = {x2, y2 - ((y2 - y1) * 0.75f)};
			POINTF thirdP = {x2, y2 - ((y2 - y1) * 0.67f)};
			POINTF forthP = {x2, y2 - ((y2 - y1) * 0.5f)};
			POINTF fifthP = {x2 - ((x2 - x1) * 0.875f), y2};
			POINTF sixthP = {x2 - ((x2 - x1) * 0.75f), y2};
			POINTF seventhP = {x2 - ((x2 - x1) * 0.67f), y2};
			POINTF eighthP = {x2 - ((x2 - x1) * 0.5f), y2};
			POINTF startP = {x1, y1};
			vector<POINTF> listP;
			POINTF *collection = new POINTF[8];
			collection[0] = firstP;
			listP.push_back(firstP);
			collection[1] = secondP;
			listP.push_back(secondP);
			collection[2] = thirdP;
			listP.push_back(thirdP);
			collection[3] = forthP;
			listP.push_back(forthP);
			collection[4] = fifthP;
			listP.push_back(fifthP);
			collection[5] = sixthP;
			listP.push_back(sixthP);
			collection[6] = seventhP;
			listP.push_back(seventhP);
			collection[7] = eighthP;
			listP.push_back(eighthP);
			int listSize = (int)listP.size();
			for (int i = 0; i < listSize; i++)
			{
				float k = 0;
				float b = 0;
				CMathLibMe::M107(startP.x, startP.y, listP[i].x, listP[i].y, 0, 0, &k, &b);
				float newX = 0;
				float newY = 0;
				if (x2 > x1)
				{
					newY = (k * CPlotBaseMe::GetWorkingAreaWidth()) + b;
					newX = CPlotBaseMe::GetWorkingAreaWidth();
				}
				else
				{
					newY = b;
					newX = 0;
				}
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, startP.x, startP.y, newX, newY);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P017::P017()
{
	SetPlotType(L"GOLDENRATIO");
}

ActionType P017::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		if (CPlotBaseMe::m_moveTimes == 1)
		{
			return ActionType_AT1;
		}
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		int length = 0;
		float* lineParam = CPlotBaseMe::GoldenRatioParams(sIter0->second->Value, sIter1->second->Value, &length);
		if (CPlotBaseMe::HLinesSelect(lineParam, length))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P017::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P017::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P017::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_startMarks.find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_startMarks.find(1);
			double num = movingPoint.y - m_startPoint.y;
			double visibleMax = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMax();
			double visibleMin = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMin();
			double num4 = (num / ((double) CPlotBaseMe::GetWorkingAreaHeight())) * (visibleMin - visibleMax);
			CPlotBaseMe::m_marks[0] = new CPlotMarkMe(0, sIter0->second->Key, sIter0->second->Value + num4);
			CPlotBaseMe::m_marks[1] = new CPlotMarkMe(1, sIter1->second->Key, sIter1->second->Value + num4);
			return;
		}
	case ActionType_AT1:
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		CPlotBaseMe::Resize(1);
		return;
	}
}

void P017::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P017::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x = CPlotBaseMe::PX(bIndex);
		int length = 0;
		float* lineParam = CPlotBaseMe::GoldenRatioParams(sIter0->second->Value, sIter1->second->Value, &length);
		String strArray[6] = { L"0.00%", L"23.60%", L"38.20%", L"50.00%", L"61.80%", L"100.00%" };
		for (int i = 0; i < length; i++)
		{
			SIZE size = CPlotBaseMe::TextSize(paint, strArray[i].c_str(), CPlotBaseMe::m_font);
			float yP = lineParam[i];
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, (float)yP, (float) CPlotBaseMe::GetWorkingAreaWidth(), (float)yP);
			CPlotBaseMe::DrawText(paint, strArray[i].c_str(), lineColor, CPlotBaseMe::m_font, (float) (CPlotBaseMe::GetWorkingAreaWidth() - size.cx), yP - size.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x, y2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P018::P018()
{
	SetPlotType(L"HLINE");
}

ActionType P018::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		float num = CPlotBaseMe::PY(sIter0->second->Value);
		if ((mouseOverPoint.y >= (num - (CPlotBaseMe::m_lineWidth * 2.5))) && (mouseOverPoint.y <= (num + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P018::OnCreate(const POINT& mp)
{
	if (CPlotBaseMe::m_dataSource->RowsCount() > 0)
	{
		CPlotBaseMe::ClearMarks(&m_marks);
		double numberValue = CPlotBaseMe::GetNumberValue(mp);
		CPlotBaseMe::m_marks[0] = new CPlotMarkMe(0, 0.0, numberValue);
		return true;
	}
	return false;
}

void P018::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, CPlotBaseMe::m_marks[0]));
	}
}

void P018::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, 0.0, CPlotBaseMe::GetNumberValue(movingPoint))));
}

void P018::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, (float)y1, (float) CPlotBaseMe::GetWorkingAreaWidth(), (float)y1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P019::LevelGradingParams(double value1, double value2, int *length)
{
	float y1 = CPlotBaseMe::PY(value1);
	float y2 = CPlotBaseMe::PY(value2);
	float yA = 0;
	float yB = 0;
	float yC = 0;
	float yD = 0;
	float yE = 0;
	yA = y1;
	yB = y2;
	yC = (y1 <= y2) ? (y2 + ((y2 - y1) * 0.382)) : (y2 - ((y1 - y2) * 0.382));
	yD = (y1 <= y2) ? (y2 + ((y2 - y1) * 0.618)) : (y2 - ((y1 - y2) * 0.618));
	yE = (y1 <= y2) ? (y2 + (y2 - y1)) : (y2 - (y1 - y2));
	*length = 5;
	float* retArray = new float[5];
	retArray[0] = yA;
	retArray[1] = yB;
	retArray[2] = yC;
	retArray[3] = yD;
	retArray[4] = yE;
	return retArray;
}


P019::P019()
{
	SetPlotType(L"LEVELGRADING");
}

ActionType P019::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() > 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		if (CPlotBaseMe::m_moveTimes == 1)
		{
			return ActionType_AT1;
		}
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		int length = 0;
		float *lineParam = LevelGradingParams(sIter0->second->Value, sIter1->second->Value, &length);
		if (CPlotBaseMe::HLinesSelect(lineParam, length))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P019::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P019::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P019::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
			double num = movingPoint.y - m_startPoint.y;
			double visibleMax = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMax();
			double visibleMin = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMin();
			double num4 = (num / ((double) CPlotBaseMe::GetWorkingAreaHeight())) * (visibleMin - visibleMax);
			CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, sIter0->second->Key, sIter0->second->Value + num4)));
			CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(1, sIter1->second->Key, sIter1->second->Value + num4)));
			return;
		}
	case ActionType_AT1:
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		CPlotBaseMe::Resize(1);
		return;
	}
}

void P019::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P019::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		int length = 0;
		float *lineParam = LevelGradingParams(sIter0->second->Value, sIter1->second->Value, &length);
		String *str = new String[length];
		if (y1 >= y2)
		{
			str[0] = L"-100%";
			str[1] = L"0.00%";
			str[2] = L"38.20%";
			str[3] = L"61.80%";
			str[4] = L"100%";
		}
		else
		{
			str[0] = L"100%";
			str[1] = L"0.00%";
			str[2] = L"-38.20%";
			str[3] = L"-61.80%";
			str[4] = L"-100%";
		}
		for (int i = 0; i < length; i++)
		{
			SIZE size = CPlotBaseMe::TextSize(paint, str[i].c_str(), CPlotBaseMe::m_font);
			float yP = lineParam[i];
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, (float)yP, (float) CPlotBaseMe::GetWorkingAreaWidth(), (float)yP);
			CPlotBaseMe::DrawText(paint, str[i].c_str(), lineColor, CPlotBaseMe::m_font, (float) (CPlotBaseMe::GetWorkingAreaWidth() - size.cx), yP - size.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P020::P020()
{
	SetPlotType(L"LINE");
}

ActionType P020::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectLine(mp, x1, y1, x2, y2))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P020::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsA(mp);
}

void P020::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P020::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int length = 0;
		float *lineParams = CPlotBaseMe::GetLineParams(sIter0->second, sIter1->second, &length);
		float a = 0;
		float b = 0;
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (lineParams && length >= 2)
		{
			a = lineParams[0];
			b = lineParams[1];
			float leftX = 0;
			float leftY = (leftX * a) + b;
			float rightX = CPlotBaseMe::GetWorkingAreaWidth();
			float rightY = (rightX * a) + b;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)leftX, (float)leftY, (float)rightX, (float)rightY);
		}
		else
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P021::P021()
{
	SetPlotType(L"LRBAND");
}

ActionType P021::GetAction()
{

	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *param = CPlotBaseMe::GetLRParams(&m_marks);
		if (!param)
		{
			return nO;
		}
		float a = param[0];
		float b = param[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		int mouseIndex = CPlotBaseMe::GetChart()->GetMouseOverIndex();
		if ((mouseIndex < bIndex) || (mouseIndex > eIndex))
		{
			return nO;
		}
		double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
		float y = CPlotBaseMe::PY(yValue);
		float x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
		double *parallel = CPlotBaseMe::GetLRBandRange(&m_marks, param);
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) + parallel[0];
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) - parallel[1];
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
	}
	return nO;
}

bool P021::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P021::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P021::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P021::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *param = CPlotBaseMe::GetLRParams(pList);
		if (param)
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			float a = param[0];
			float b = param[1];
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)y1, (float)x2, (float)y2);
			double *parallel = CPlotBaseMe::GetLRBandRange(pList, param);
			double leftTop = leftValue + parallel[0];
			double rightTop = rightValue + parallel[0];
			double leftBottom = leftValue - parallel[1];
			double rightBottom = rightValue - parallel[1];
			float leftTopY = CPlotBaseMe::PY(leftTop);
			float rightTopY = CPlotBaseMe::PY(rightTop);
			float leftBottomY = CPlotBaseMe::PY(leftBottom);
			float rightBottomY = CPlotBaseMe::PY(rightBottom);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)leftTopY, (float)x2, (float)rightTopY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)leftBottomY, (float)x2, (float)rightBottomY);
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P022::P022()
{
	SetPlotType(L"LRCHANNEL");
}

ActionType P022::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *param = CPlotBaseMe::GetLRParams(&m_marks);
		if (!param)
		{
			return nO;
		}
		float a = param[0];
		float b = param[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		CChartMe *chart = CPlotBaseMe::GetChart();
		int mouseIndex = chart->GetMouseOverIndex();
		if ((mouseIndex < bIndex) || (mouseIndex > chart->GetLastVisibleIndex()))
		{
			return nO;
		}
		double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
		float y = CPlotBaseMe::PY(yValue);
		float x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
		double *parallel = CPlotBaseMe::GetLRBandRange(&m_marks, param);
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) + parallel[0];
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) - parallel[1];
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
	}
	return nO;
}

bool P022::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P022::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P022::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}

}

void P022::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *param = CPlotBaseMe::GetLRParams(pList);
		if (param)
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			float a = param[0];
			float b = param[1];
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)y1, (float)x2, (float)y2);
			double *parallel = CPlotBaseMe::GetLRBandRange(pList, param);
			double leftTop = leftValue + parallel[0];
			double rightTop = rightValue + parallel[0];
			double leftBottom = leftValue - parallel[1];
			double rightBottom = rightValue - parallel[1];
			float leftTopY = CPlotBaseMe::PY(leftTop);
			float rightTopY = CPlotBaseMe::PY(rightTop);
			float leftBottomY = CPlotBaseMe::PY(leftBottom);
			float rightBottomY = CPlotBaseMe::PY(rightBottom);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, leftTopY, x2, rightTopY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, leftBottomY, x2, rightBottomY);
			CChartMe *chart = CPlotBaseMe::GetChart();
			rightValue = (((chart->GetLastVisibleIndex() + 1) - bIndex) * a) + b;
			float x3 = (float)((((chart->GetLastVisibleIndex() - chart->GetFirstVisibleIndex()) + 1) * chart->GetHScalePixel()) + (chart->GetHScalePixel() / 2.0));
			double dashTop = rightValue + parallel[0];
			double dashBottom = rightValue - parallel[1];
			float mValueY = CPlotBaseMe::PY(rightValue);
			float dashTopY = CPlotBaseMe::PY(dashTop);
			float dashBottomY = CPlotBaseMe::PY(dashBottom);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, rightTopY, x3, dashTopY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, rightBottomY, x3, dashBottomY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, y2, x3, mValueY);
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P023::P023()
{
	SetPlotType(L"LRLINE");
}

ActionType P023::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *param = CPlotBaseMe::GetLRParams(&m_marks);
		if (!param)
		{
			return nO;
		}
		float a = param[0];
		float b = param[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		int mouseIndex = CPlotBaseMe::GetChart()->GetMouseOverIndex();
		if ((mouseIndex >= bIndex) && (mouseIndex <= eIndex))
		{
			double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
			float y = CPlotBaseMe::PY(yValue);
			float x = CPlotBaseMe::PX(mouseIndex);
			if (CPlotBaseMe::SelectPoint(mp, x, y))
			{
				return ActionType_MOVE;
			}
		}
	}
	return nO;
}

bool P023::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P023::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P023::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P023::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *param = CPlotBaseMe::GetLRParams(pList);
		if (param)
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			float a = param[0];
			float b = param[1];
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)y1, (float)x2, (float)y2);
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void P024::NullPoint(float x1, float y1, float x2, float y2, float *nullX, float *nullY)
{
	float k1 = 0;
	float k2 = 0;
	float b1 = 0;
	float b2 = 0;
	if (y1 >= y2)
	{
		k1 = -((float) tan(45.0));
		k2 = -((float) tan(60.0));
		b1 = y1 - (k1 * x1);
		b2 = y2 - (k2 * x2);
	}
	else
	{
		k1 = (float) tan(45.0);
		k2 = (float) tan(60.0);
		b1 = y1 - (k1 * x1);
		b2 = y2 - (k2 * x2);
	}
	*nullX = (b2 - b1) / (k1 - k2);
	*nullY = (*nullX * k1) + b1;
}

double* P024::GetNullPointParams(map<int,CPlotMarkMe*> *pList)
{
	if ((int)pList->size() == 0
		|| (int)CPlotBaseMe::m_sourceFields.size() == 0
		|| CPlotBaseMe::m_sourceFields.find(L"CLOSE") == CPlotBaseMe::m_sourceFields.end())
	{
		return 0;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	map<String,int>::iterator sIterClose = CPlotBaseMe::m_sourceFields.find(L"CLOSE");
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	double leftClose = 0.0;
	double rightClose = 0.0;
	CPlotBaseMe::m_dataSource->Get2(bIndex, sIterClose->second);
	CPlotBaseMe::m_dataSource->Get2(eIndex, sIterClose->second);
	if (eIndex >= bIndex)
	{
		leftClose = CPlotBaseMe::m_dataSource->Get2(bIndex, sIterClose->second);
		rightClose = CPlotBaseMe::m_dataSource->Get2(eIndex, sIterClose->second);
	}
	else
	{
		leftClose = CPlotBaseMe::m_dataSource->Get2(eIndex, sIterClose->second);
		rightClose = CPlotBaseMe::m_dataSource->Get2(bIndex, sIterClose->second);
	}
	double *ret = new double[2];
	ret[0] = leftClose;
	ret[1] = rightClose;
	return ret;
}


P024::P024()
{
	SetPlotType(L"NULLPOINT");
}

ActionType P024::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		double *closeParam = GetNullPointParams(&m_marks);
		double leftClose = closeParam[1];
		double rightClose = closeParam[0];
		float y1 = CPlotBaseMe::PY(leftClose);
		float y2 = CPlotBaseMe::PY(rightClose);
		float x1 = CPlotBaseMe::PX((bIndex >= eIndex) ? bIndex : eIndex);
		float x2 = CPlotBaseMe::PX((bIndex >= eIndex) ? eIndex : bIndex);
		int length = 0;
		CPlotBaseMe::GetLineParams(sIter0->second, sIter1->second, &length);
		if (length > 0)
		{
			if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		else
		{
			if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT2;
			}
		}
		float nullX = 0;
		float nullY = 0;
		if (y1 != y2)
		{
			NullPoint(x1, y1, x2, y2, &nullX, &nullY);
		}
		if (CPlotBaseMe::SelectTriangle(mp, x1, y1, x2, y2, nullX, nullY))
		{
			return ActionType_MOVE;
		}
	}
	return nO;
}

bool P024::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P024::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P024::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		double *closeParam = GetNullPointParams(pList);
		double leftClose = closeParam[1];
		double rightClose = closeParam[0];
		float y1 = CPlotBaseMe::PY(leftClose);
		float y2 = CPlotBaseMe::PY(rightClose);
		float x1 = CPlotBaseMe::PX((bIndex >= aIndex) ? bIndex : aIndex);
		float x2 = CPlotBaseMe::PX((bIndex >= aIndex) ? aIndex : bIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
		float nullX = 0;
		float nullY = 0;
		if (y1 != y2)
		{
			NullPoint(x1, y1, x2, y2, &nullX, &nullY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, nullX, nullY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x2, y2, nullX, nullY);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P025::GetParallelParams(map<int,CPlotMarkMe*> *pList, int *length)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		float a = 0;
		if ((x2 - x1) != 0)
		{
			a = (y2 - y1) / (x2 - x1);
			float num11 = y1 - (a * x1);
			float num12 = y3 - (a * x3);
			*length = 3;
			float *ret = new float[3];
			ret[0] = a;
			ret[1] = num11;
			ret[2] = num12;
			return ret;
		}
	}
	return 0;
}


P025::P025()
{
	SetPlotType(L"PARALLEL");
}

ActionType P025::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		int length = 0;
		float *parallelParams = GetParallelParams(&m_marks, &length);
		if (parallelParams)
		{
			if (CPlotBaseMe::SelectPoint(mp, x1, y1))
			{
				return ActionType_AT1;
			}
			if (CPlotBaseMe::SelectPoint(mp, x2, y2))
			{
				return ActionType_AT2;
			}
			if (CPlotBaseMe::SelectPoint(mp, x3, y3))
			{
				return ActionType_AT3;
			}
			if (((((mp.y - (parallelParams[0] * mp.x)) - parallelParams[1]) < (CPlotBaseMe::m_lineWidth * -5)) 
				|| (((mp.y - (parallelParams[0] * mp.x)) - parallelParams[1]) > (CPlotBaseMe::m_lineWidth * 5)))
				&& ((((mp.y - (parallelParams[0] * mp.x)) - parallelParams[2]) < (CPlotBaseMe::m_lineWidth * -5))
				|| (((mp.y - (parallelParams[0] * mp.x)) - parallelParams[2]) > (CPlotBaseMe::m_lineWidth * 5))))
			{
				return nO;
			}
			return ActionType_MOVE;
		}
		if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT1;
		}
		if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT2;
		}
		if ((mp.y >= (y3 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y3 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT3;
		}
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_MOVE;
		}
		if ((mp.x >= (x3 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.x <= (x3 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_MOVE;
		}
	}
	return nO;
}

bool P025::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create3Points(mp);
}

void P025::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P025::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		int length = 0;
		float *parallelParams = GetParallelParams(pList, &length);
		float a = 0;
		float b = 0;
		float c = 0;
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		if (parallelParams)
		{
			a = parallelParams[0];
			b = parallelParams[1];
			c = parallelParams[2];
			float leftX = 0;
			float leftY = (leftX * a) + b;
			float rightX = CPlotBaseMe::GetWorkingAreaWidth();
			float rightY = (rightX * a) + b;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
			leftY = (leftX * a) + c;
			rightY = (rightX * a) + c;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
		}
		else
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x3, (float)0, (float)x3, (float) CPlotBaseMe::GetWorkingAreaHeight());
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P026::GetPercentParams(double value1, double value2, int *length)
{
	float y1 = CPlotBaseMe::PY(value1);
	float y2 = CPlotBaseMe::PY(value2);
	float y0 = 0;
	float y25 = 0;
	float y50 = 0;
	float y75 = 0;
	float y100 = 0;
	y0 = y1;
	y25 = (y1 <= y2) ? (y1 + ((y2 - y1) / 4)) : (y2 + (((y1 - y2) * 3) / 4));
	y50 = (y1 <= y2) ? (y1 + ((y2 - y1) / 2)) : (y2 + ((y1 - y2) / 2));
	y75 = (y1 <= y2) ? (y1 + (((y2 - y1) * 3) / 4)) : (y2 + ((y1 - y2) / 4));
	y100 = y2;
	*length = 5;
	float *ret = new float[5];
	ret[0] = y0;
	ret[1] = y25;
	ret[2] = y50;
	ret[3] = y75;
	ret[4] = y100;
	return ret;
}


P026::P026()
{
	SetPlotType(L"PERCENT");
}

ActionType P026::GetAction()
{
	ActionType nO = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		if (CPlotBaseMe::m_moveTimes == 1)
		{
			return ActionType_AT1;
		}
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		int length = 0;
		float *percentParams = GetPercentParams(sIter0->second->Value,sIter1->second->Value, &length);
		if (CPlotBaseMe::HLinesSelect(percentParams, length))
		{
			nO = ActionType_MOVE;
		}
	}
	return nO;
}

bool P026::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P026::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}

		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P026::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_startMarks.find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_startMarks.find(1);
			double subY = mp.y - m_startPoint.y;
			double maxValue = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMax();
			double minValue = CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMin();
			double yAddValue = (subY / ((double)CPlotBaseMe::GetWorkingAreaHeight())) * (minValue - maxValue);
			CPlotBaseMe::m_marks[0] = new CPlotMarkMe(0, sIter0->second->Key, sIter0->second->Value + yAddValue);
			CPlotBaseMe::m_marks[1] = new CPlotMarkMe(1, sIter1->second->Key, sIter1->second->Value + yAddValue);
			return;
		}
	case ActionType_AT1:
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		CPlotBaseMe::Resize(1);
		return;
	}
}

void P026::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P026::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		int length = 0;
		float *lineParam = GetPercentParams(sIter0->second->Value, sIter1->second->Value, &length);
		String str[5] = { L"0.00%", L"25.00%", L"50.00%", L"75.00%", L"100.00%" };
		for (int i = 0; i < length; i++)
		{
			SIZE sizeF = CPlotBaseMe::TextSize(paint, str[i].c_str(), CPlotBaseMe::m_font);
			float yP = lineParam[i];
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, (float)yP, (float) CPlotBaseMe::GetWorkingAreaWidth(), (float)yP);
			CPlotBaseMe::DrawText(paint, str[i].c_str(), lineColor, CPlotBaseMe::m_font, (float) (CPlotBaseMe::GetWorkingAreaWidth() - sizeF.cx), yP - sizeF.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y2);
		}
		delete[] lineParam;
		lineParam = 0;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P027::P027()
{
	m_beginPeriod = 1;
	m_period = 5;
	SetPlotType(L"PERIODIC");
}

ActionType P027::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		vector<double> param = GetPLParams(&m_marks);
		float y = CPlotBaseMe::GetWorkingAreaHeight() / 2;
		int length = (int)param.size();
		for (int i = 0; i < length; i++)
		{
			int rI = (int)param[i];
			float x1 = CPlotBaseMe::PX(rI);
			if (CPlotBaseMe::SelectPoint(mp, x1, y))
			{
				action = ActionType_AT1;
				CPlotBaseMe::m_marks[0] = new CPlotMarkMe(0, CPlotBaseMe::m_dataSource->GetXValue(rI), 0.0);
				m_beginPeriod = m_period;
				return action;
			}
			if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

vector<double> P027::GetPLParams(map<int,CPlotMarkMe*> *pList)
{
	vector<double> fValueList;
	if ((int)pList->size() == 0)
	{
		return fValueList;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	double fValue = sIter0->second->Value;
	int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	CChartMe *chart = CPlotBaseMe::GetChart();
	for (int i = chart->GetFirstVisibleIndex(); i < chart->GetLastVisibleIndex(); i++)
	{
		if ((abs((int) (i - aIndex)) % m_period) == 0)
		{
			fValueList.push_back((double) i);
		}
	}
	return fValueList;
}

bool P027::OnCreate(const POINT& mp)
{
	if (CPlotBaseMe::m_dataSource->RowsCount() <= 0)
	{
		return false;
	}
	int currentIndex = CPlotBaseMe::GetIndex(mp);
	double y = CPlotBaseMe::GetNumberValue(mp);
	double date = CPlotBaseMe::m_dataSource->GetXValue(currentIndex);
	CPlotBaseMe::ClearMarks(&m_marks);
	CPlotBaseMe::m_marks[0] = new CPlotMarkMe(0, date, y);
	CChartMe *chart = CPlotBaseMe::GetChart();
	m_period = chart->GetMaxVisibleRecord() / 10;
	if (m_period < 1)
	{
		m_period = 1;
	}
	return true;
}

void P027::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_AT1)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P027::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	int bI = CPlotBaseMe::GetIndex(CPlotBaseMe::m_startPoint);
	int eI = CPlotBaseMe::GetIndex(mp);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		m_period = m_beginPeriod + (eI - bI);
		if (m_period < 1)
		{
			m_period = 1;
		}
		return;
	}
}

void P027::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		vector<double> vet = GetPLParams(pList);
		int size = (int)vet.size();
		for(int i = 0; i < size; i++)
		{
			int rI = (int)vet[i];
			float x1 = CPlotBaseMe::PX(rI);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, (float) (CPlotBaseMe::GetWorkingAreaHeight() / 2));
			}		
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P028::P028()
{
	SetPlotType(L"PRICE");
}

ActionType P028::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		double fValue = sIter0->second->Value;
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float y1 = CPlotBaseMe::PY(fValue);
		RECT rect = {x1, y1, x1 + m_textSize.cx, y1 + m_textSize.cy};
		if (((mp.x >= rect.left) && (mp.x <= rect.right)) && ((mp.y >= rect.top) && (mp.y <= rect.bottom)))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P028::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P028::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		CPlotBaseMe::m_startMarks[0] = CPlotBaseMe::m_marks[0];
	}
}

void P028::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		int workingAreaWidth = CPlotBaseMe::GetWorkingAreaWidth();
		int workingAreaHeight = CPlotBaseMe::GetWorkingAreaHeight();
		if ((workingAreaWidth > 0) && (workingAreaHeight > 0))
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
			double fValue = sIter0->second->Value;
			int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			float x1 = CPlotBaseMe::PX(aIndex);
			float y1 = CPlotBaseMe::PY(fValue);
			CChartMe *chart = CPlotBaseMe::GetChart();
			wchar_t wordChars[100] = {0};
			CStrMe::GetValueByDigit(fValue, 
				(chart->GetLeftVScaleWidth() > 0) ? CPlotBaseMe::m_div->GetLeftVScale()->GetDigit() : CPlotBaseMe::m_div->GetRightVScale()->GetDigit(), wordChars);
			String word(wordChars);
			CPlotBaseMe::DrawText(paint, word.c_str(), lineColor, CPlotBaseMe::m_font, x1, y1);
			m_textSize = CPlotBaseMe::TextSize(paint, word.c_str(), CPlotBaseMe::m_font);
			if ((IsSelected() && (m_textSize.cx > 0)) && (m_textSize.cy > 0))
			{
				CPlotBaseMe::DrawRect(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (int) x1, (int) y1, ((int) x1) + m_textSize.cx, ((int) y1) + m_textSize.cy);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P029::P029()
{
	SetPlotType(L"RANGERULER");
}

ActionType P029::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		CPlotBaseMe::PY(sIter0->second->Value);
		CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		double *candleRange = CPlotBaseMe::GetCandleRange(&m_marks, &length);
		double nHigh = candleRange[0];
		double nLow = candleRange[1];
		float highY = CPlotBaseMe::PY(nHigh);
		float lowY = CPlotBaseMe::PY(nLow);
		float smallX = (x1 > x2) ? x2 : x1;
		float bigX = (x1 > x2) ? x1 : x2;
		if (((mp.y >= (highY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (highY + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			|| ((mp.y >= (lowY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (lowY + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		if ((mp.y >= (highY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (highY + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			if ((mp.x >= (smallX - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (bigX + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
		else if (((mp.y >= (lowY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (lowY + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.x >= (smallX - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (bigX + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			return ActionType_MOVE;
		}
		float mid = (x1 >= x2) ? (x2 + ((x1 - x2) / 2)) : (x1 + ((x2 - x1) / 2));
		if (((mp.x >= (mid - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (mid + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.y >= (highY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (lowY + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			return ActionType_MOVE;
		}
	}
	return action;
}

bool P029::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P029::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P029::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		CPlotBaseMe::PY(sIter0->second->Value);
		CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float smallX = (x1 > x2) ? x2 : x1;
		float bigX = (x1 > x2) ? x1 : x2;
		int length = 0;
		double *candleRange = CPlotBaseMe::GetCandleRange(pList, &length);
		double nHigh = candleRange[0];
		double nLow = candleRange[1];
		float highY = CPlotBaseMe::PY(nHigh);
		float lowY = CPlotBaseMe::PY(nLow);
		float mid = (x1 >= x2) ? (x2 + ((x1 - x2) / 2)) : (x1 + ((x2 - x1) / 2));
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, highY, x2, highY);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, lowY, x2, lowY);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, mid, lowY, mid, highY);
		if (nHigh != nLow)
		{
			double diff = abs((double)(nLow - nHigh));
			double range = 0.0;
			if (nHigh != 0.0)
			{
				range = diff / nHigh;
			}
			CChartMe *chart = CPlotBaseMe::GetChart();
			wchar_t wordChars[100] = {0};
			CStrMe::GetValueByDigit(diff, CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetDigit(), wordChars);
			String diffString(wordChars);
			wchar_t wordCharsRange[100] = {0};
			CStrMe::GetValueByDigit(range, 2, wordCharsRange);
			String rangeString(wordCharsRange);
			rangeString = rangeString + L"%";
			SIZE diffSize = CPlotBaseMe::TextSize(paint, diffString.c_str(), CPlotBaseMe::m_font);
			SIZE rangeSize = CPlotBaseMe::TextSize(paint, rangeString.c_str(), CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, diffString.c_str(), lineColor, CPlotBaseMe::m_font, (float) (bigX - diffSize.cx), (float) (highY + 2));
			CPlotBaseMe::DrawText(paint, rangeString.c_str(), lineColor, CPlotBaseMe::m_font, (float) (bigX - rangeSize.cx), (float) (lowY - rangeSize.cy));
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, smallX, highY);
			CPlotBaseMe::DrawSelect(paint, lineColor, smallX, lowY);
			CPlotBaseMe::DrawSelect(paint, lineColor, bigX, highY);
			CPlotBaseMe::DrawSelect(paint, lineColor, bigX, lowY);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P030::P030()
{
	SetPlotType(L"RASELINE");
}

float* P030::GetRaseLineParams(map<int,CPlotMarkMe*> *pList)
{
	if ((int)pList->size() != 0)
	{
		return 0;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	float y1 = CPlotBaseMe::PY(sIter0->second->Value);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float a = -1;
	float b = y1 + x1;
	float *ret = new float[2];
	ret[0] = a;
	ret[1] = b;
	return ret;
}

ActionType P030::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float *raseLineParams = GetRaseLineParams(&m_marks);
		if (((raseLineParams != 0) && (((mp.y - (raseLineParams[0] * mp.x)) - raseLineParams[1]) >= (CPlotBaseMe::m_lineWidth * - 5)))
			&& (((mp.y - (raseLineParams[0] * mp.x)) - raseLineParams[1]) <= (CPlotBaseMe::m_lineWidth * 5)))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P030::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P030::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P030::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *raseLineParams = GetRaseLineParams(pList);
		float a = raseLineParams[0];
		float b = raseLineParams[1];
		float leftX = 0;
		float leftY = (leftX * a) + b;
		float rightX = CPlotBaseMe::GetWorkingAreaWidth();
		float rightY = (rightX * a) + b;
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P031::P031()
{
	SetPlotType(L"RAY");
}

ActionType P031::GetAction()
{

	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int length = 0;
		CPlotBaseMe::GetLineParams(sIter0->second, sIter1->second, &length);
		if ( length > 0)
		{
			if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		else
		{
			if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT1;
			}
			if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT2;
			}
		}
		if (CPlotBaseMe::SelectRay(mp, x1, y1, x2, y2))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P031::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsA(mp);
}

void P031::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P031::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float k = 0;
		float b = 0;
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &k, &b);
		CPlotBaseMe::DrawRay(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2, k, b);
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P032::P032()
{
	m_oppositePoint.x = 0;
	m_oppositePoint.y = 0;
	SetPlotType(L"RECT");
}

ActionType P032::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() == 0)
	{
		return action;
	}
	POINT mp = CPlotBaseMe::GetMouseOverPoint();
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	return CPlotBaseMe::SelectRect(mp, sIter0->second, sIter1->second);
}

bool P032::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P032::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	if ((CPlotBaseMe::m_action != ActionType_MOVE) && (CPlotBaseMe::m_action != ActionType_NO))
	{
		RECT rect = CPlotBaseMe::GetRectangle(CPlotBaseMe::m_marks[0], CPlotBaseMe::m_marks[1]);
		int x1 = rect.left;
		int y1 = rect.top;
		int x2 = rect.right;
		int y2 = rect.top;
		int x3 = rect.left;
		int y3 = rect.bottom;
		int x4 = rect.right;
		int y4 = rect.bottom;
		switch (CPlotBaseMe::m_action)
		{
		case ActionType_AT1:
			m_oppositePoint.x = x4;
			m_oppositePoint.y = y4;
			break;

		case ActionType_AT2:
			m_oppositePoint.x = x3;
			m_oppositePoint.y = y3;
			break;

		case ActionType_AT3:
			m_oppositePoint.x = x2;
			m_oppositePoint.y = y2;
			break;

		case ActionType_AT4:
			m_oppositePoint.x = x1;
			m_oppositePoint.y = y1;
			break;
		}
	}
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P032::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(movingPoint);
		return;

	case ActionType_AT1:
	case ActionType_AT2:
	case ActionType_AT3:
	case ActionType_AT4:
		CPlotBaseMe::Resize(movingPoint, m_oppositePoint);
		return;
	}
}

void P032::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P032::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		RECT rectangle = CPlotBaseMe::GetRectangle(sIter0->second, sIter1->second);
		if (((rectangle.right - rectangle.left) > 0) && ((rectangle.bottom - rectangle.top) > 0))
		{
			CPlotBaseMe::DrawRect(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, rectangle.left, rectangle.top, rectangle.right, rectangle.bottom);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rectangle.left, (float) rectangle.top);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rectangle.right, (float) rectangle.top);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rectangle.left, (float) rectangle.bottom);
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) rectangle.right, (float) rectangle.bottom);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P033::P033()
{
	SetPlotType(L"SEGMENT");
}

ActionType P033::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		float *params = CPlotBaseMe::GetLineParams(sIter0->second, sIter1->second, &length);
		if ( length > 0)
		{
			if ((mouseOverPoint.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mouseOverPoint.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mouseOverPoint.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mouseOverPoint.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		else
		{
			if ((mouseOverPoint.y >= (y1 - (CPlotBaseMe::m_lineWidth * 5))) && (mouseOverPoint.y <= (y1 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT1;
			}
			if ((mouseOverPoint.y >= (y2 - (CPlotBaseMe::m_lineWidth * 5))) && (mouseOverPoint.y <= (y2 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				return ActionType_AT2;
			}
		}
		if (CPlotBaseMe::SelectSegment(mouseOverPoint, x1, y1, x2, y2))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P033::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P033::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P033::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)y1, (float)x2, (float)y2);
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P034::P034()
{
	SetPlotType(L"SINE");
}

ActionType P034::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectSine(mp, x1, y1, x2, y2))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P034::OnCreate(const POINT& mp)
{
	if (CPlotBaseMe::m_dataSource->RowsCount() > 0)
	{
		CChartMe *chart = CPlotBaseMe::GetChart();
		int mouseIndex = chart->GetMouseOverIndex();
		if ((mouseIndex >= 0) && (mouseIndex <= chart->GetLastVisibleIndex()))
		{
			int eIndex = mouseIndex;
			int bIndex = eIndex - (chart->GetMaxVisibleRecord() / 10);
			if ((bIndex >= 0) && (eIndex != bIndex))
			{
				double fDate = CPlotBaseMe::m_dataSource->GetXValue(bIndex);
				double sDate = CPlotBaseMe::m_dataSource->GetXValue(eIndex);
				CPlotBaseMe::ClearMarks(&m_marks);
				double numberValue = CPlotBaseMe::GetNumberValue(mp);
				CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, fDate,
					numberValue + ((CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMax() 
					- CPlotBaseMe::m_div->GetVScale(CPlotBaseMe::m_attachVScale)->GetVisibleMin()) / 4.0))));
				CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(1, sDate, numberValue)));
				return true;
			}
		}
	}
	return false;
}

void P034::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_AT1)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		else if (CPlotBaseMe::m_action == ActionType_AT2)
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P034::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P034::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		double fValue = sIter0->second->Value;
		double eValue = sIter1->second->Value;
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int x1 = (int) CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(fValue);
		float y2 = CPlotBaseMe::PY(eValue);
		double f = 6.2831853071795862 / ((double)((x2 - x1) * 4));
		if (x1 != x2)
		{
			int len = CPlotBaseMe::GetWorkingAreaWidth();
			if (len > 0)
			{
				POINT *pf = new POINT[len];
				for (int i = 0; i < len; i++)
				{
					int x = -x1 + i;
					float y = (float)(((0.5 * (y2 - y1)) * sin(x * f)) * 2.0);
					POINT point = { x + x1, (int)(y + y1) };
					pf[i] = point;
				}
				CPlotBaseMe::DrawPolyline(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, pf, len);
				delete pf;
			}
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float)x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P035::P035()
{
	SetPlotType(L"SPEEDRESIST");
}

ActionType P035::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		POINTF firstP = {x2, y2 - ((y2 - y1) / 3)};
		POINTF secondP = {x2, y2 - (((y2 - y1) * 2) / 3)};
		POINTF startP = {x1, y1};
		float oK = 0;
		float oB = 0;
		float fK = 0;
		float fB = 0;
		float sK = 0;
		float sB = 0;
		CMathLibMe::M107(x1, y1, x2, y2, 0, 0, &oK, &oB);
		CMathLibMe::M107(startP.x, startP.y, firstP.x, firstP.y, 0, 0, &fK, &fB);
		CMathLibMe::M107(startP.x, startP.y, secondP.x, secondP.y, 0, 0, &sK, &sB);
		float smallX = (x1 <= x2) ? x1 : x2;
		float smallY = (y1 <= y2) ? y1 : y2;
		float bigX = (x1 > x2) ? x1 : x2;
		float bigY = (y1 > y2) ? y1 : y2;
		if (((mp.x >= (smallX - 2)) && (mp.x <= (bigX + 2))) && ((mp.y >= (smallY - 2)) && (mp.y <= (bigY + 2))))
		{
			if ((oK == 0) && (oB == 0))
			{
				return ActionType_MOVE;
			}
			if (((((float) mp.y) / ((mp.x * oK) + oB)) >= 0.9) && ((((float) mp.y) / ((mp.x * oK) + oB)) <= 1.1))
			{
				return ActionType_MOVE;
			}
		}
		if (((x2 > x1) && (mp.x >= (x1 - 2))) || ((mp.x <= (x1 + 2)) && (x2 < x1)))
		{
			if (((fK != 0) || (fB != 0)) && (((((float) mp.y) / ((mp.x * fK) + fB)) >= 0.9) && ((((float) mp.y) / ((mp.x * fK) + fB)) <= 1.1)))
			{
				return ActionType_MOVE;
			}
			if ((sK == 0) && (sB == 0))
			{
				return action;
			}
			if (((((float) mp.y) / ((mp.x * sK) + sB)) >= 0.9) && ((((float) mp.y) / ((mp.x * sK) + sB)) <= 1.1))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P035::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsA(mp);
}

void P035::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P035::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P035::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{

	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x1, y1, x2, y2);
		if (IsSelected() || (x1 == x2))
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
		if ((x1 != x2) && (y1 != y2))
		{
			POINT firstP = {x2, y2 - ((y2 - y1) / 3)};
			POINT secondP = {x2, y2 - (((y2 - y1) * 2) / 3)};
			POINT startP = {x1, y1};
			float fK = 0;
			float fB = 0;
			float sK = 0;
			float sB = 0;
			CMathLibMe::M107((float) startP.x, (float) startP.y, (float) firstP.x, (float) firstP.y, 0, 0, &fK, &fB);
			CMathLibMe::M107((float) startP.x, (float) startP.y, (float) secondP.x, (float) secondP.y, 0, 0, &sK, &sB);
			float newYF = 0;
			float newYS = 0;
			float newX = 0;
			if (x2 > x1)
			{
				newYF = (fK * CPlotBaseMe::GetWorkingAreaWidth()) + fB;
				newYS = (sK * CPlotBaseMe::GetWorkingAreaWidth()) + sB;
				newX = CPlotBaseMe::GetWorkingAreaWidth();
			}
			else
			{
				newYF = fB;
				newYS = sB;
				newX = 0;
			}
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) startP.x, (float) startP.y, (float) newX, (float) newYF);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float) startP.x, (float) startP.y, (float) newX, (float) newYS);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double P036::GetSEChannelSD(map<int,CPlotMarkMe*> *pList)
{
	map<String,int>::iterator sIter = CPlotBaseMe::m_sourceFields.find(L"CLOSE");
	if (sIter != CPlotBaseMe::m_sourceFields.end())
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = (CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key) - bIndex) + 1;
		if (eIndex > 0)
		{
			double *ary = new double[eIndex];
			for (int i = 0; i < eIndex; i++)
			{
				double close = CPlotBaseMe::m_dataSource->Get2(i + bIndex, sIter->second);
				if (!CPlotBaseMe::m_dataSource->IsNaN(close))
				{
					ary[i] = close;
				}
			}
			double avg = CMathLibMe::M010(ary, eIndex);
			return CMathLibMe::M007(ary, eIndex, avg, 2.0);
		}
	}
	return 0.0;
}


P036::P036()
{
	SetPlotType(L"SECHANNEL");
}

ActionType P036::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *lRParams = CPlotBaseMe::GetLRParams(&m_marks);
		if (lRParams == NULL)
		{
			return action;
		}
		float a = lRParams[0];
		float b = lRParams[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		CChartMe *chart = CPlotBaseMe::GetChart();
		int mouseIndex = chart->GetMouseOverIndex();
		if ((mouseIndex < bIndex) || (mouseIndex > chart->GetLastVisibleIndex()))
		{
			return action;
		}
		double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
		float y = CPlotBaseMe::PY(yValue);
		float x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
		double sEChannelSD = GetSEChannelSD(&m_marks);
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) + sEChannelSD;
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) - sEChannelSD;
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (CPlotBaseMe::SelectPoint(mp, x, y))
		{
			return ActionType_MOVE;
		}
	}
	return action;
}

bool P036::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P036::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}

		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P036::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P036::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		CChartMe *chart = CPlotBaseMe::GetChart();
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(chart->GetX(bIndex));
		float x2 = CPlotBaseMe::PX(chart->GetX(eIndex));
		float *lRParams = CPlotBaseMe::GetLRParams(pList);
		if (lRParams != NULL)
		{
			float a = lRParams[0];
			float b = lRParams[1];
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
			double sd = GetSEChannelSD(pList);
			double leftTop = leftValue + sd;
			double rightTop = rightValue + sd;
			double leftBottom = leftValue - sd;
			double rightBottom = rightValue - sd;
			float leftTopY = CPlotBaseMe::PY(leftTop);
			float rightTopY = CPlotBaseMe::PY(rightTop);
			float leftBottomY = CPlotBaseMe::PY(leftBottom);
			float rightBottomY = CPlotBaseMe::PY(rightBottom);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, leftTopY, x2, rightTopY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, leftBottomY, x2, rightBottomY);
			rightValue = (((chart->GetLastVisibleIndex() + 1) - bIndex) * a) + b;
			float x3 = (float)(((chart->GetLastVisibleIndex() - chart->GetFirstVisibleIndex()) * chart->GetHScalePixel()) + (chart->GetHScalePixel() / 2.0));
			double dashTop = rightValue + sd;
			double dashBottom = rightValue - sd;
			float mValueY = CPlotBaseMe::PY(rightValue);
			float dashTopY = CPlotBaseMe::PY(dashTop);
			float dashBottomY = CPlotBaseMe::PY(dashBottom);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, rightTopY, x3, dashTopY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, rightBottomY, x3, dashBottomY);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x2, y2, x3, mValueY);
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P037::P037()
{
	SetPlotType(L"SYMMETRICLINE");
}

ActionType P037::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() == 0)
	{
		return action;
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	POINT mp = CPlotBaseMe::GetMouseOverPoint();
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float x2 = CPlotBaseMe::PX(eIndex);
	float y1 = CPlotBaseMe::PY(sIter0->second->Value);
	float y2 = CPlotBaseMe::PY(sIter1->second->Value);
	if (CPlotBaseMe::SelectPoint(mp, x1, y1))
	{
		return ActionType_AT1;
	}
	if (CPlotBaseMe::SelectPoint(mp, x2, y2))
	{
		return ActionType_AT2;
	}
	int cIndex = 0;
	if (x2 >= x1)
	{
		cIndex = bIndex - (eIndex - bIndex);
	}
	else
	{
		cIndex = bIndex + (bIndex - eIndex);
	}
	if (cIndex > (CPlotBaseMe::m_dataSource->RowsCount() - 1))
	{
		cIndex = CPlotBaseMe::m_dataSource->RowsCount() - 1;
	}
	else if (cIndex < 0)
	{
		cIndex = 0;
	}
	float num8 = CPlotBaseMe::PX(cIndex);
	if ((((mp.x < (x1 - (CPlotBaseMe::m_lineWidth * 5))) || (mp.x > (x1 + (CPlotBaseMe::m_lineWidth * 5)))) && ((mp.x < (x2 - (CPlotBaseMe::m_lineWidth * 5))) 
		|| (mp.x > (x2 + (CPlotBaseMe::m_lineWidth * 5))))) && ((mp.x < (num8 - (CPlotBaseMe::m_lineWidth * 5))) || (mp.x > (num8 + (CPlotBaseMe::m_lineWidth * 5)))))
	{
		return action;
	}
	return ActionType_MOVE;
}

bool P037::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsA(mp);
}

void P037::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P037::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int cIndex = -1;
		if (x2 >= x1)
		{
			cIndex = bIndex - (eIndex - bIndex);
		}
		else
		{
			cIndex = bIndex + (bIndex - eIndex);
		}
		if (cIndex > (CPlotBaseMe::m_dataSource->RowsCount() - 1))
		{
			cIndex = CPlotBaseMe::m_dataSource->RowsCount() - 1;
		}
		else if (cIndex < 0)
		{
			cIndex = 0;
		}
		float x3 = CPlotBaseMe::PX(cIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x2, (float)0, (float)x2, (float) CPlotBaseMe::GetWorkingAreaHeight());
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x3, (float)0, (float)x3, (float) CPlotBaseMe::GetWorkingAreaHeight());
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P038::GetSymmetricTriangleParams(map<int,CPlotMarkMe*> *pList)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		float a = 0;
		if ((x2 - x1) != 0)
		{
			a = (y2 - y1) / (x2 - x1);
			float b = y1 - (a * x1);
			float c = -a;
			float d = y3 - (c * x3);
			float *retArray = new float[4];
			retArray[0] = a;
			retArray[1] = b;
			retArray[2] = c;
			retArray[3] = d;
			return retArray;
		}
	}
	return NULL;
}


P038::P038()
{
	SetPlotType(L"SYMMETRICTRIANGLE");
}

ActionType P038::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		float *symmetricTriangleParams = GetSymmetricTriangleParams(&m_marks);
		if (symmetricTriangleParams != NULL)
		{
			if (CPlotBaseMe::SelectPoint(mp, x1, y1))
			{
				return ActionType_AT1;
			}
			if (CPlotBaseMe::SelectPoint(mp, x2, y2))
			{
				return ActionType_AT2;
			}
			if (CPlotBaseMe::SelectPoint(mp, x3, y3))
			{
				return ActionType_AT3;
			}
			if (((((mp.y - (symmetricTriangleParams[0] * mp.x)) - symmetricTriangleParams[1]) < (CPlotBaseMe::m_lineWidth * -5))
				|| (((mp.y - (symmetricTriangleParams[0] * mp.x)) - symmetricTriangleParams[1]) > (CPlotBaseMe::m_lineWidth * 5))) 
				&& ((((mp.y - (symmetricTriangleParams[2] * mp.x)) - symmetricTriangleParams[3]) < (CPlotBaseMe::m_lineWidth * -5)) 
				|| (((mp.y - (symmetricTriangleParams[2] * mp.x)) - symmetricTriangleParams[3]) > (CPlotBaseMe::m_lineWidth * 5))))
			{
				return action;
			}
			return ActionType_MOVE;
		}
		if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT1;
		}
		if ((mp.y >= (y2 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y2 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT2;
		}
		if ((mp.y >= (y3 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.y <= (y3 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_AT3;
		}
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_MOVE;
		}
		if ((mp.x >= (x3 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.x <= (x3 + (CPlotBaseMe::m_lineWidth * 5))))
		{
			return ActionType_MOVE;
		}
	}
	return action;
}

bool P038::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create3Points(mp);
}

void P038::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P038::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float *symmetricTriangleParams = GetSymmetricTriangleParams(pList);
		float a = 0;
		float b = 0;
		float c = 0;
		float d = 0;
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float x3 = CPlotBaseMe::PX(pIndex);
		if (symmetricTriangleParams != NULL)
		{
			a = symmetricTriangleParams[0];
			b = symmetricTriangleParams[1];
			c = symmetricTriangleParams[2];
			d = symmetricTriangleParams[3];
			float leftX = 0;
			float leftY = (leftX * a) + b;
			float rightX = CPlotBaseMe::GetWorkingAreaWidth();
			float rightY = (rightX * a) + b;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
			leftY = (leftX * c) + d;
			rightY = (rightX * c) + d;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
		}
		else
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaWidth());
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x3, (float)0, (float)x3, (float) CPlotBaseMe::GetWorkingAreaWidth());
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double* P041::GetTimeRulerParams(map<int,CPlotMarkMe*> *pList, int *length)
{

	if ((int)pList->size() == 0)
	{
		return NULL;
	}
	CChartMe *chart = CPlotBaseMe::GetChart();
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	double bHigh = chart->DivMaxOrMin(bIndex, CPlotBaseMe::m_div, 0);
	double bLow = chart->DivMaxOrMin(bIndex, CPlotBaseMe::m_div, 1);
	double eHigh = chart->DivMaxOrMin(eIndex, CPlotBaseMe::m_div, 0);
	double eLow = chart->DivMaxOrMin(eIndex, CPlotBaseMe::m_div, 1);
	double *retArray = new double[4];
	retArray[0] = bHigh;
	retArray[1] = bLow;
	retArray[2] = eHigh;
	retArray[3] = eLow;
	*length = 4;
	return retArray;
}


P041::P041()
{
	SetPlotType(L"TIMERULER");
}

ActionType P041::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		int length = 0;
		double *timeRulerParams = GetTimeRulerParams(&m_marks, &length);
		float yBHigh = CPlotBaseMe::PY(timeRulerParams[0]);
		float yBLow = CPlotBaseMe::PY(timeRulerParams[1]);
		float yEHigh = CPlotBaseMe::PY(timeRulerParams[2]);
		float yELow = CPlotBaseMe::PY(timeRulerParams[3]);
		if (y1 < yBHigh)
		{
			yBHigh = y1;
		}
		if (y1 > yBLow)
		{
			yBLow = y1;
		}
		if (y2 < yEHigh)
		{
			yEHigh = y2;
		}
		if (y2 > yELow)
		{
			yELow = y2;
		}
		if (((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5)))
			&& (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.y >= (yBHigh - 2)) && (mp.y <= (yBLow + 2))))
		{
			return ActionType_MOVE;
		}
		if (((mp.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) 
			&& (mp.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.y >= (yEHigh - (CPlotBaseMe::m_lineWidth * 2.5)))
			&& (mp.y <= (yELow + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			return ActionType_MOVE;
		}
		if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 2.5))) 
			&& (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			float num11 = (x1 >= x2) ? x1 : x2;
			float num12 = (x1 < x2) ? x1 : x2;
			if ((mp.x >= (num12 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (num11 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P041::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P041::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P041::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	double y = CPlotBaseMe::GetNumberValue(movingPoint);
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(movingPoint);
		return;

	case ActionType_AT1:
		CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, CPlotBaseMe::m_dataSource->GetXValue(mouseIndex), y)));
		CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(1, sIter1->second->Key, y)));
		return;

	case ActionType_AT2:
		CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(0, CPlotBaseMe::m_dataSource->GetXValue(mouseIndex), y)));
		CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, sIter0->second->Key, y)));
		return;
	}
}

void P041::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		double *timeRulerParams = GetTimeRulerParams(pList, &length);
		float yBHigh = CPlotBaseMe::PY(timeRulerParams[0]);
		float yBLow = CPlotBaseMe::PY(timeRulerParams[1]);
		float yEHigh = CPlotBaseMe::PY(timeRulerParams[2]);
		float yELow = CPlotBaseMe::PY(timeRulerParams[3]);
		if (y1 < yBHigh)
		{
			yBHigh = y1;
		}
		if (y1 > yBLow)
		{
			yBLow = y1;
		}
		if (y2 < yEHigh)
		{
			yEHigh = y2;
		}
		if (y2 > yELow)
		{
			yELow = y2;
		}
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, yBHigh, x1, yBLow);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x2, yEHigh, x2, yELow);
		String record = CStrMe::ConvertIntToStr((abs((int)(eIndex - bIndex)) + 1));
		String recordStr = record + L"(T)";
		SIZE size = CPlotBaseMe::TextSize(paint, recordStr.c_str(), CPlotBaseMe::m_font);
		CPlotBaseMe::DrawText(paint, recordStr.c_str(), lineColor, CPlotBaseMe::m_font, (float)(((x2 + x1) / 2) - (size.cx / 2)), (float)(y1 - (size.cy / 2)));
		if (abs((float) (x1 - x2)) > size.cx)
		{
			if (x2 >= x1)
			{
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)y1, (float)((x2 + x1) / 2) - (size.cx / 2), (float)y1);
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)((x2 + x1) / 2) + (size.cx / 2), (float)y1, (float)x2, (float)y1);
			}
			else
			{
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x2, (float)y1, (float)((x2 + x1) / 2) - (size.cx / 2), (float)y1);
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)((x2 + x1) / 2) + (size.cx / 2), (float)y1, (float)x1, (float)y1);
			}
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P042::P042()
{
	SetPlotType(L"TRIANGLE");
}

ActionType P042::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float x2 = CPlotBaseMe::PX(bIndex);
		float x3 = CPlotBaseMe::PX(cIndex);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		if (CPlotBaseMe::m_moveTimes == 1)
		{
			return ActionType_AT3;
		}
		if (CPlotBaseMe::SelectPoint(mp, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectPoint(mp, x3, y3))
		{
			return ActionType_AT3;
		}
		if (CPlotBaseMe::SelectTriangle(mp, x1, y1, x2, y2, x3, y3))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P042::OnCreate(const POINT& mp)
{
	if (CPlotBaseMe::m_dataSource->RowsCount() <= 0)
	{
		return false;
	}
	int currentIndex = CPlotBaseMe::GetIndex(mp);
	double y = CPlotBaseMe::GetNumberValue(mp);
	double date = CPlotBaseMe::m_dataSource->GetXValue(currentIndex);
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, date, y)));
	int si = currentIndex + 10;
	CChartMe *chart = CPlotBaseMe::GetChart();
	if (si > chart->GetLastVisibleIndex())
	{
		si = chart->GetLastVisibleIndex();
	}
	CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(1, CPlotBaseMe::m_dataSource->GetXValue(si), y)));
	CPlotBaseMe::m_marks.insert(make_pair(2, new CPlotMarkMe(2, date, y)));
	return true;
}

void P042::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P042::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P042::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float x2 = CPlotBaseMe::PX(bIndex);
		float x3 = CPlotBaseMe::PX(cIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x3, y3);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x2, y2, x3, y3);
		if (IsSelected() || (((x1 == x2) && (x2 == x3)) && ((y1 == y2) && (y2 == y3))))
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

RECT P043::GetUpArrowRect(float x, float y, float width)
{
	if(width>10)
	{
		width = 14;
	}
	int mleft = (int)(x - width / 2);
	int mtop = (int)y;
	RECT markRect = {(LONG)mleft, (LONG)mtop, (LONG)(mleft + width), (LONG)(mtop + width * 3 / 2)};
	return markRect;
}

P043::P043()
{
	SetPlotType(L"UPARROW");
}

ActionType P043::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		double fValue = sIter0->second->Value;
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float y1 = CPlotBaseMe::PY(fValue);
		int width = 10;
		RECT rect = {x1 - (width / 2), y1, x1 + (width / 2), y1 + ((width * 3) / 2)};
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		if (((mouseOverPoint.x > rect.left) && (mouseOverPoint.x <= rect.right)) && ((mouseOverPoint.y >= rect.top) && (mouseOverPoint.y <= rect.bottom)))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P043::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P043::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P043::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		double fValue = sIter0->second->Value;
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int x = (int) CPlotBaseMe::PX(aIndex);
		int y = (int) CPlotBaseMe::PY(fValue);
		int width = 10;
		POINT point = {x, y};
		POINT point2 = {x + (width / 2), y + width};
		POINT point3 = {x + (width / 4), y + width};
		POINT point4 = {x + (width / 4), y + ((width * 3) / 2)};
		POINT point5 = {x - (width / 4), y + ((width * 3) / 2)};
		POINT point6 = {x - (width / 4), y + width};
		POINT point7 = {x - (width / 2), y + width};
		POINT points[7];
		points[0] = point;
		points[1] = point2;
		points[2] = point3;
		points[3] = point4;
		points[4] = point5;
		points[5] = point6;
		points[6] = point7;
		CPlotBaseMe::FillPolygon(paint, lineColor, points, 7);
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, (float) (x - (width / 2)), (float) y);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P044::P044()
{
	SetPlotType(L"VLINE");
}

ActionType P044::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

bool P044::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P044::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P044::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)x1, (float)0, (float)x1, (float) CPlotBaseMe::GetWorkingAreaHeight());
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

float* P045::GetWaveRulerParams(double value1, double value2, int *length)
{
	float y1 = CPlotBaseMe::PY(value1);
	float y2 = CPlotBaseMe::PY(value2);
	float y0 = 0;
	float yA = 0;
	float yB = 0;
	float yC = 0;
	float yD = 0;
	float yE = 0;
	float yF = 0;
	float yG = 0;
	float yH = 0;
	float yI = 0;
	float yMax = 0;
	y0 = y1;
	yA = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.09014515)) : (y2 + ((y1 - y2) * 0.9098548));
	yB = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.1382735)) : (y2 + ((y1 - y2) * 0.8617265));
	yC = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.1909855)) : (y2 + ((y1 - y2) * 0.8090145));
	yD = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.236058)) : (y2 + ((y1 - y2) * 0.7639419));
	yE = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.381971)) : (y2 + ((y1 - y2) * 0.6180291));
	yF = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.5278839)) : (y2 + ((y1 - y2) * 0.4721161));
	yG = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.6180291)) : (y2 + ((y1 - y2) * 0.381971));
	yH = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.7639419)) : (y2 + ((y1 - y2) * 0.2360581));
	yI = (y1 <= y2) ? (y1 + ((y2 - y1) * 0.9098548)) : (y2 + ((y1 - y2) * 0.09014517));
	yMax = y2;
	float *retArray = new float[11];
	retArray[0] = y0;
	retArray[1] = yA;
	retArray[2] = yB;
	retArray[3] = yC;
	retArray[4] = yD;
	retArray[5] = yE;
	retArray[6] = yF;
	retArray[7] = yG;
	retArray[8] = yH;
	retArray[9] = yI;
	retArray[0] = yMax;
	*length = 11;
	return retArray;
}


P045::P045()
{
	SetPlotType(L"WAVERULER");
}

ActionType P045::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		int length = 0;
		float *waveRulerParams = GetWaveRulerParams(sIter0->second->Value, sIter1->second->Value, &length);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = waveRulerParams[length - 1];
		if (CPlotBaseMe::SelectPoint(mp, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		float smallY = (waveRulerParams[0] < waveRulerParams[length - 1]) ? waveRulerParams[0] : waveRulerParams[length - 1];
		float bigY = (waveRulerParams[0] >= waveRulerParams[length - 1]) ? waveRulerParams[0] : waveRulerParams[length - 1];
		float mid = (x1 >= x2) ? (x2 + ((x1 - x2) / 2)) : (x1 + ((x2 - x1) / 2));
		if (((mp.x >= (mid - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (mid + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.y >= (smallY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (bigY + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			return ActionType_MOVE;
		}
		float top = 0;
		float bottom = CPlotBaseMe::GetWorkingAreaWidth();
		if ((mp.y < top) || (mp.y > bottom))
		{
			return action;
		}
		for(int i = 0; i < length; i++)
		{
			float p = waveRulerParams[i];
			if (((mp.x >= 0) && (mp.x <= CPlotBaseMe::GetWorkingAreaWidth())) 
				&& ((mp.y >= (p - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (p + (CPlotBaseMe::m_lineWidth * 2.5)))))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P045::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsB(mp);
}

void P045::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeWE);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P045::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P045::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		float *waveRulerParams = GetWaveRulerParams(sIter0->second->Value, sIter1->second->Value, &length);
		String strArray[11] = { L"0.00%", L"23.60%", L"38.20%", L"50.00%", L"61.80%", L"100.00%", L"138.20%", L"161.80%", L"200%", L"238.20%", L"261.80%" };
		float mid = (x1 >= x2) ? (x2 + ((x1 - x2) / 2)) : (x1 + ((x2 - x1) / 2));
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, mid, waveRulerParams[0], mid, waveRulerParams[length - 1]);
		for (int i = 0; i < length; i++)
		{
			SIZE size = CPlotBaseMe::TextSize(paint, strArray[i].c_str(), CPlotBaseMe::m_font);
			float yP = waveRulerParams[i];
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, yP, x2, yP);
			CPlotBaseMe::DrawText(paint, strArray[i].c_str(), lineColor, CPlotBaseMe::m_font, mid, yP - size.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double* P046::GetTironelLevelsParams(map<int,CPlotMarkMe*> *pList, int *length)
{
	*length = 0;
	double *candleRange = CPlotBaseMe::GetCandleRange(pList, length);
	if (candleRange != NULL && *length > 0)
	{
		double nHigh = candleRange[0];
		double nLow = candleRange[1];
		*length = 5;
		double *retArray = new double[5];
		retArray[0] = nHigh;
		retArray[1] = (nHigh - ((nHigh - nLow) / 3.0));
		retArray[2] = (nHigh - ((nHigh - nLow) / 2.0));
		retArray[3] = (nHigh - ((2.0 * (nHigh - nLow)) / 3.0));
		retArray[4] = nLow;
	}
	return NULL;
}


P046::P046()
{
	SetPlotType(L"TIRONELEVELS");
}

ActionType P046::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		CPlotBaseMe::PY(sIter0->second->Value);
		CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		int length = 0;
		double *tironelLevelsParams = GetTironelLevelsParams(&m_marks, &length);
		double nHigh = tironelLevelsParams[0];
		double nLow = tironelLevelsParams[4];
		float highY = CPlotBaseMe::PY(nHigh);
		float lowY = CPlotBaseMe::PY(nLow);
		float smallX = (x1 > x2) ? x2 : x1;
		float bigX = (x1 > x2) ? x1 : x2;
		if (((mp.y >= (highY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (highY + (CPlotBaseMe::m_lineWidth * 2.5))))
			|| ((mp.y >= (lowY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (lowY + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			if ((mp.x >= (x1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x1 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT1;
			}
			if ((mp.x >= (x2 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (x2 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_AT2;
			}
		}
		if ((mp.y >= (highY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (highY + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			if ((mp.x >= (smallX - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (bigX + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
		else if (((mp.y >= (lowY - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (lowY + (CPlotBaseMe::m_lineWidth * 2.5)))) 
			&& ((mp.x >= (smallX - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.x <= (bigX + (CPlotBaseMe::m_lineWidth * 2.5)))))
		{
			return ActionType_MOVE;
		}
		for (int i = 1; i < (length - 1); i++)
		{
			float num12 = CPlotBaseMe::PY(tironelLevelsParams[i]);
			if ((mp.y >= (num12 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (num12 + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P046::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P046::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P046::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		CPlotBaseMe::PY(sIter0->second->Value);
		CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float smallX = (x1 > x2) ? x2 : x1;
		float bigX = (x1 > x2) ? x1 : x2;
		int length = 0;
		double *tironelLevelsParams = GetTironelLevelsParams(pList, &length);
		double nHigh = tironelLevelsParams[0];
		double nLow = tironelLevelsParams[4];
		float highY = CPlotBaseMe::PY(nHigh);
		float lowY = CPlotBaseMe::PY(nLow);
		float mid = (x1 >= x2) ? (x2 + ((x1 - x2) / 2)) : (x1 + ((x2 - x1) / 2));
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, highY, x2, highY);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, lowY, x2, lowY);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, mid, lowY, mid, highY);
		for (int i = 1; i < (length - 1); i++)
		{
			float y = CPlotBaseMe::PY(tironelLevelsParams[i]);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, (float) 1, (float) 0, (float) y, (float) CPlotBaseMe::GetWorkingAreaWidth(), y);
			String text = CStrMe::ConvertIntToStr(i) + L"/3";
			if (i == 2)
			{
				text = L"1/2";
			}
			SIZE size = CPlotBaseMe::TextSize(paint, text.c_str(), CPlotBaseMe::m_font);
			CPlotBaseMe::DrawText(paint, text.c_str(), lineColor, CPlotBaseMe::m_font, (float) (CPlotBaseMe::GetWorkingAreaWidth() - size.cx), y - size.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, smallX, highY);
			CPlotBaseMe::DrawSelect(paint, lineColor, smallX, lowY);
			CPlotBaseMe::DrawSelect(paint, lineColor, bigX, highY);
			CPlotBaseMe::DrawSelect(paint, lineColor, bigX, lowY);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double P047::GetRRCRange(map<int,CPlotMarkMe*> *pList, float *param)
{
	map<String,int>::iterator sIterHigh = CPlotBaseMe::m_sourceFields.find(L"HIGH");
	map<String,int>::iterator sIterLow = CPlotBaseMe::m_sourceFields.find(L"LOW");
	if (((param == NULL))
		|| (((CPlotBaseMe::m_sourceFields.size() == 0)
		|| sIterHigh == CPlotBaseMe::m_sourceFields.end()) 
		|| sIterLow == CPlotBaseMe::m_sourceFields.end()))
	{
		return 0.0;
	}
	float a = param[0];
	float b = param[1];
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	double upSubValue = 0.0;
	double downSubValue = 0.0;
	int pos = 0;
	for (int i = bIndex; i <= eIndex; i++)
	{
		double high = CPlotBaseMe::m_dataSource->Get2(i, sIterHigh->second);
		double low = CPlotBaseMe::m_dataSource->Get2(i, sIterLow->second);
		if (!CPlotBaseMe::m_dataSource->IsNaN(high) && !CPlotBaseMe::m_dataSource->IsNaN(low))
		{
			double midValue = (((i - bIndex) + 1) * a) + b;
			if (pos == 0)
			{
				upSubValue = high - midValue;
				downSubValue = midValue - low;
			}
			else
			{
				if ((high - midValue) > upSubValue)
				{
					upSubValue = high - midValue;
				}
				if ((midValue - low) > downSubValue)
				{
					downSubValue = midValue - low;
				}
			}
			pos++;
		}
	}
	if (upSubValue >= downSubValue)
	{
		return upSubValue;
	}
	return downSubValue;
}


P047::P047()
{
	SetPlotType(L"RAFFCHANNEL");
}

ActionType P047::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *lRParams = CPlotBaseMe::GetLRParams(&m_marks);
		if (lRParams == NULL)
		{
			return action;
		}
		float a = lRParams[0];
		float b = lRParams[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		CChartMe *chart = CPlotBaseMe::GetChart();
		int mouseIndex = chart->GetMouseOverIndex();
		if ((mouseIndex < chart->GetFirstVisibleIndex()) || (mouseIndex > chart->GetLastVisibleIndex()))
		{
			return action;
		}
		double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
		float y = CPlotBaseMe::PY(yValue);
		float x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
		double rRCRange = GetRRCRange(&m_marks, lRParams);
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) + rRCRange;
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
		yValue = ((a * ((mouseIndex - bIndex) + 1)) + b) - rRCRange;
		y = CPlotBaseMe::PY(yValue);
		x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
	}
	return action;
}

bool P047::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P047::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P047::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P047::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *lRParams = CPlotBaseMe::GetLRParams(pList);
		if (lRParams != NULL)
		{
			float a = lRParams[0];
			float b = lRParams[1];
			map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			int length = 0;
			float *lineParams = CPlotBaseMe::GetLineParams(new CPlotMarkMe(0, sIter0->second->Key, leftValue), new CPlotMarkMe(1, sIter1->second->Key, rightValue), &length);
			if (lineParams != NULL)
			{
				a = lineParams[0];
				b = lineParams[1];
				float leftX = 0;
				float leftY = (leftX * a) + b;
				float rightX = CPlotBaseMe::GetWorkingAreaWidth();
				float rightY = (rightX * a) + b;
				CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
				double parallel = GetRRCRange(pList, lRParams);
				double leftTop = leftValue + parallel;
				double rightTop = rightValue + parallel;
				length = 0;
				lineParams = CPlotBaseMe::GetLineParams(new CPlotMarkMe(0, sIter0->second->Key, leftTop), new CPlotMarkMe(1, sIter1->second->Key, rightTop), &length);
				if (lineParams != NULL)
				{
					a = lineParams[0];
					b = lineParams[1];
					leftX = 0;
					leftY = (leftX * a) + b;
					rightX = CPlotBaseMe::GetWorkingAreaWidth();
					rightY = (rightX * a) + b;
					CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
				}
				double leftBottom = leftValue - parallel;
				double rightBottom = rightValue - parallel;
				length = 0;
				lineParams = CPlotBaseMe::GetLineParams(new CPlotMarkMe(0, sIter0->second->Key, leftBottom), new CPlotMarkMe(1, sIter1->second->Key, rightBottom), &length);
				if (lineParams != NULL)
				{
					a = lineParams[0];
					b = lineParams[1];
					leftX = 0;
					leftY = (leftX * a) + b;
					rightX = CPlotBaseMe::GetWorkingAreaWidth();
					rightY = (rightX * a) + b;
					CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
				}
			}
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P048::P048()
{
	SetPlotType(L"QUADRANTLINES");
}

ActionType P048::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float *lRParams = CPlotBaseMe::GetLRParams(&m_marks);
		if (lRParams == NULL)
		{
			return action;
		}
		float a = lRParams[0];
		float b = lRParams[1];
		double leftValue = a + b;
		double rightValue = (((eIndex - bIndex) + 1) * a) + b;
		float y1 = CPlotBaseMe::PY(leftValue);
		float y2 = CPlotBaseMe::PY(rightValue);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		int mouseIndex = CPlotBaseMe::GetChart()->GetMouseOverIndex();
		if ((mouseIndex < bIndex) || (mouseIndex > eIndex))
		{
			return action;
		}
		double yValue = (a * ((mouseIndex - bIndex) + 1)) + b;
		float y = CPlotBaseMe::PY(yValue);
		float x = CPlotBaseMe::PX(mouseIndex);
		if (((mp.x >= (x - 5)) && (mp.x <= (x + 5))) && ((mp.y >= (y - 5)) && (mp.y <= (y + 5))))
		{
			return ActionType_MOVE;
		}
		int length = 0;
		double *candleRange = CPlotBaseMe::GetCandleRange(&m_marks, &length);
		if (candleRange == NULL || length == 0)
		{
			return action;
		}
		float *percentParams = P026::GetPercentParams(candleRange[0], candleRange[1], &length);
		for (int i = 0; i < length; i++)
		{
			if (CPlotBaseMe::SelectRay(mp, x1, percentParams[i], x2, percentParams[i]))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P048::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P048::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P048::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P048::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float *lRParams = CPlotBaseMe::GetLRParams(pList);
		if (lRParams != NULL)
		{
			map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
			map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
			int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
			int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
			float x1 = CPlotBaseMe::PX(bIndex);
			float x2 = CPlotBaseMe::PX(eIndex);
			float a = lRParams[0];
			float b = lRParams[1];
			double leftValue = a + b;
			double rightValue = (((eIndex - bIndex) + 1) * a) + b;
			float y1 = CPlotBaseMe::PY(leftValue);
			float y2 = CPlotBaseMe::PY(rightValue);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
			int length = 0;
			double *candleRange = CPlotBaseMe::GetCandleRange(pList, &length);
			if (candleRange != NULL)
			{
				length = 0;
				float *percentParams = P026::GetPercentParams(candleRange[0], candleRange[1], &length);
				for (int i = 0; i < length; i++)
				{
					float yp = percentParams[i];
					if (i == 2)
					{
						CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, x1, yp, x2, yp);
					}
					else
					{
						CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, yp, x2, yp);
					}
				}
			}
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
			}
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ActionType P049::GetAction(const POINT& mp)
{
	int length = 0;
	double *candleRange = CPlotBaseMe::GetCandleRange(&m_marks, &length);
	double nHigh = candleRange[0];
	double nLow = candleRange[1];
	if (candleRange != NULL)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		return CPlotBaseMe::SelectRect(mp, new CPlotMarkMe(0, sIter0->second->Key, nHigh), new CPlotMarkMe(1, sIter1->second->Key, nLow));
	}
	return ActionType_NO;
}


P049::P049()
{
	SetPlotType(L"BOXLINE");
}

ActionType P049::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		action = GetAction(mouseOverPoint);
		if (action == ActionType_AT4)
		{
			action = ActionType_AT2;
		}
	}
	return action;
}

bool P049::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2CandlePoints(mp);
}

void P049::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P049::OnMoving()
{
	POINT mp = CPlotBaseMe::GetMovingPoint();
	CChartMe *chart = CPlotBaseMe::GetChart();
	int mouseIndex = chart->GetMouseOverIndex();
	if (mouseIndex < 0)
	{
		mouseIndex = 0;
	}
	if (mouseIndex > chart->GetLastVisibleIndex())
	{
		mouseIndex = chart->GetLastVisibleIndex();
	}
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	switch (CPlotBaseMe::m_action)
	{
	case ActionType_MOVE:
		CPlotBaseMe::Move(mp);
		return;

	case ActionType_AT1:
		if (mouseIndex >= eIndex)
		{
			break;
		}
		CPlotBaseMe::Resize(0);
		return;

	case ActionType_AT2:
		if (mouseIndex > bIndex)
		{
			CPlotBaseMe::Resize(1);
		}
		break;

	default:
		return;
	}
}

void P049::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int length = 0;
		double *candleRange = CPlotBaseMe::GetCandleRange(pList, &length);
		double nHigh = candleRange[0];
		double nLow = candleRange[1];
		if (candleRange != NULL)
		{
			RECT rectangle = CPlotBaseMe::GetRectangle(new CPlotMarkMe(0, sIter0->second->Key, nHigh), new CPlotMarkMe(1, sIter1->second->Key, nLow));
			int x1 = rectangle.left;
			int y1 = rectangle.top;
			int x2 = rectangle.right;
			int y2 = rectangle.bottom;
			if (((rectangle.right - rectangle.left) > 0) && ((rectangle.bottom - rectangle.top) > 0))
			{
				int rwidth = rectangle.right - rectangle.left;
				int rheight = rectangle.bottom - rectangle.top;
				CPlotBaseMe::DrawRect(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x1 + rwidth, y1 + rheight);
				String text = L"COUNT:" + CStrMe::ConvertIntToStr((abs((int) (bIndex - eIndex)) + 1));
				CPlotBaseMe::DrawText(paint, text.c_str(), lineColor, CPlotBaseMe::m_font, (int) (x1 + 2), (int) (y1 + 2));
				double diff = nLow - nHigh;
				double range = 0.0;
				if (nHigh != 0.0)
				{
					range = diff / nHigh;
				}
				wchar_t diffChar[99] = {0};				
				CStrMe::GetValueByDigit(diff, 2, diffChar);
				String diffString = diffChar;
				wchar_t rangeChar[99] = {0};				
				CStrMe::GetValueByDigit(range, 2, rangeChar);
				String rangeString = rangeChar;
				rangeString = rangeString + L"%";
				SIZE size = CPlotBaseMe::TextSize(paint, rangeString.c_str(), CPlotBaseMe::m_font);
				CPlotBaseMe::DrawText(paint, diffString.c_str(), lineColor, CPlotBaseMe::m_font, (int) ((x1 + rwidth) + 2), (int) (y1 + 2));
				CPlotBaseMe::DrawText(paint, rangeString.c_str(), lineColor, CPlotBaseMe::m_font, (int) ((x1 + rwidth) + 2), (int) (((y1 + rheight) - size.cy) - 2));
				map<String,int>::iterator sIterClose= CPlotBaseMe::m_sourceFields.find(L"CLOSE");
				if (sIterClose != CPlotBaseMe::m_sourceFields.end())
				{
					int length = 0;
					double *array = CPlotBaseMe::m_dataSource->DATA_ARRAY(sIterClose->second, eIndex, (eIndex - bIndex) + 1, &length);
					double avg = CMathLibMe::M010(array, length);
					float yAvg = CPlotBaseMe::PY(avg);
					CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, (float) x1, yAvg, (float) x2, yAvg);
					wchar_t avgChar[99] = {0};	
					CStrMe::GetValueByDigit(avg, 2, avgChar);
					String avgString = L"AVG:" + String(avgChar);
					SIZE avgSize = CPlotBaseMe::TextSize(paint, avgString.c_str(), CPlotBaseMe::m_font);
					CPlotBaseMe::DrawText(paint, avgString.c_str(), lineColor, CPlotBaseMe::m_font, (float) (x1 + 2), (yAvg - avgSize.cy) - 2);
				}
			}
			if (IsSelected())
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, (float) x1, (float) y1);
				CPlotBaseMe::DrawSelect(paint, lineColor, (float) x2, (float) y2);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P050::P050()
{
	SetPlotType(L"PARALLELOGRAM");
}

ActionType P050::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		POINT mouseOverPoint = CPlotBaseMe::GetMouseOverPoint();
		if (CPlotBaseMe::m_moveTimes == 1)
		{
			return ActionType_AT3;
		}
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		float y3 = CPlotBaseMe::PY(sIter2->second->Value);
		int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
		float x1 = CPlotBaseMe::PX(aIndex);
		float x2 = CPlotBaseMe::PX(bIndex);
		float x3 = CPlotBaseMe::PX(cIndex);
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x1, y1) || (CPlotBaseMe::m_moveTimes == 1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x2, y2))
		{
			return ActionType_AT2;
		}
		if (CPlotBaseMe::SelectPoint(mouseOverPoint, x3, y3))
		{
			return ActionType_AT3;
		}
		int length = 0;
		POINT *pLPoints = GetPLPoints(&m_marks, &length);
		for (int i = 0; i < length; i++)
		{
			int start = i;
			int end = i + 1;
			if (start == 3)
			{
				end = 0;
			}
			if (CPlotBaseMe::SelectRay(mouseOverPoint, (float) pLPoints[start].x, (float) pLPoints[start].y, (float) pLPoints[end].x, (float) pLPoints[end].y))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

POINT* P050::GetPLPoints(map<int,CPlotMarkMe*> *pList, int *length)
{
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
	map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
	POINT point = {CPlotBaseMe::PX(CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key)), CPlotBaseMe::PY(sIter0->second->Value)};
	POINT point2 = {CPlotBaseMe::PX(CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key)), CPlotBaseMe::PY(sIter1->second->Value)};
	POINT point3 = {CPlotBaseMe::PX(CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key)), CPlotBaseMe::PY(sIter2->second->Value)};
	float x1 = 0;
	float y1 = 0;
	float x2 = 0;
	float y2 = 0;
	float x3 = 0;
	float y3 = 0;
	float x4 = 0;
	float y4 = 0;
	x1 = point.x;
	y1 = point.y;
	x2 = point2.x;
	y2 = point2.y;
	x3 = point3.x;
	y3 = point3.y;
	CMathLibMe::M124(x1, y1, x2, y2, x3, y3, &x4, &y4);
	POINT point4 = {x4, y4};
	POINT* points = new POINT[4];
	*length = 4;
	points[0] = point;
	points[1] = point2;
	points[2] = point3;
	points[3] = point4;
	return points;
}

bool P050::OnCreate(const POINT& mp)
{
	if (CPlotBaseMe::m_dataSource->RowsCount() <= 0)
	{
		return false;
	}
	int currentIndex = CPlotBaseMe::GetIndex(mp);
	double y = CPlotBaseMe::GetNumberValue(mp);
	double date = CPlotBaseMe::m_dataSource->GetXValue(currentIndex);
	CPlotBaseMe::ClearMarks(&m_marks);
	CPlotBaseMe::m_marks.insert(make_pair(0, new CPlotMarkMe(0, date, y)));
	int si = currentIndex + 10;
	CChartMe *chart = CPlotBaseMe::GetChart();
	if (si > chart->GetLastVisibleIndex())
	{
		si = chart->GetLastVisibleIndex();
	}
	CPlotBaseMe::m_marks.insert(make_pair(1, new CPlotMarkMe(1, CPlotBaseMe::m_dataSource->GetXValue(si), y)));
	CPlotBaseMe::m_marks.insert(make_pair(2, new CPlotMarkMe(2, date, y)));
	return true;
}

void P050::OnMoveStart()
{
	CPlotBaseMe::m_moveTimes++;
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P050::OnPaintGhost(CPaintMe *paint)
{
	if (CPlotBaseMe::m_moveTimes > 1)
	{
		Paint(paint, &m_startMarks, GetSelectedColor());
	}
}

void P050::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		int length = 0;
		POINT *pLPoints = GetPLPoints(pList, &length);
		for (int i = 0; i < length; i++)
		{
			int start = i;
			int end = i + 1;
			if (start == 3)
			{
				end = 0;
			}
			float x1 = pLPoints[start].x;
			float y1 = pLPoints[start].y;
			float x2 = pLPoints[end].x;
			float y2 = pLPoints[end].y;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
			if (IsSelected() && (i < 3))
			{
				CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P051::P051()
{
	SetPlotType(L"CIRCLE");
}

ActionType P051::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		if (CPlotBaseMe::SelectPoint(mp, x1, y1))
		{
			return ActionType_AT1;
		}
		if (CPlotBaseMe::SelectPoint(mp, x2, y2))
		{
			return ActionType_AT2;
		}
		float r = (float)sqrt((double)(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
		POINT p = {mp.x - x1, mp.y - y1};
		float round = (p.x * p.x) + (p.y * p.y);
		if ((round / (r * r) >= 0.9) && ((round / (r * r)) <= 1.1))
		{
			return ActionType_MOVE;
		}
	}
	return action;
}

bool P051::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::Create2PointsA(mp);
}

void P051::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	}
}

void P051::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		float y2 = CPlotBaseMe::PY(sIter1->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		int eIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		float x2 = CPlotBaseMe::PX(eIndex);
		float r = (float)sqrt((double)abs((float)(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)))));
		CPlotBaseMe::DrawEllipse(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1 - r, y1 - r, x1 + r, y1 + r);
		if (IsSelected())
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
			CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void P052::GetLine3Params(map<int,CPlotMarkMe*> *pList, float *k, float *d, float *x4)
{
	map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
	map<int,CPlotMarkMe*>::iterator sIter2 = CPlotBaseMe::m_marks.find(2);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int pIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
	float x1 = CPlotBaseMe::PX(bIndex);
	float x3 = CPlotBaseMe::PX(pIndex);
	int length = 0;
	float *parallelParams = P025::GetParallelParams(&m_marks, &length);
	if (parallelParams != NULL && length > 2)
	{
		*k = parallelParams[0];
		float b = parallelParams[1];
		float c = parallelParams[2];
		*d = (b >= c) ? (b + (b - c)) : (b - (c - b));
	}
	else
	{
		*x4 = 0;
		if (x3 > x1)
		{
			*x4 = x1 - (x3 - x1);
		}
		else
		{
			*x4 = x1 + (x1 - x3);
		}
	}
}

void P052::PaintEx(CPaintMe *paint, map<int,CPlotMarkMe*> *pList,_int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		float k = 0;
		float d = 0;
		float x4 = 0;
		GetLine3Params(&m_marks, &k, &d, &x4);
		if ((k == 0) && (d == 0))
		{
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x4, (float) 0, x4, (float) CPlotBaseMe::GetWorkingAreaHeight());
		}
		else
		{
			float leftX = 0;
			float leftY = (leftX * k) + d;
			float rightX = CPlotBaseMe::GetWorkingAreaWidth();
			float rightY = (rightX * k) + d;
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, leftX, leftY, rightX, rightY);
		}
	}
}


P052::P052()
{
	SetPlotType(L"PRICECHANNEL");
}

ActionType P052::GetAction()
{
	ActionType action = CPlotBaseMe::GetAction();
	if (action == ActionType_NO)
	{
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float k = 0;
		float d = 0;
		float x4 = 0;
		GetLine3Params(&m_marks, &k, &d, &x4);
		if ((k == 0) && (d == 0))
		{
			if ((mp.x >= (x4 - (CPlotBaseMe::m_lineWidth * 5))) && (mp.x <= (x4 + (CPlotBaseMe::m_lineWidth * 5))))
			{
				action = ActionType_MOVE;
			}
			return action;
		}
		if (CPlotBaseMe::SelectLine(mp, CPlotBaseMe::PX(mp.x), k, d))
		{
			action = ActionType_MOVE;
		}
	}
	return action;
}

void P052::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		CPlotBaseMe::SetCursor(CursorsMe_Hand);
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(1);
		CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
		sIterPlot = CPlotBaseMe::m_marks.find(2);
		CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
	}
}

void P052::OnPaint(CPaintMe *paint)
{
	PaintEx(paint, &m_marks, GetColor());
	CPlotBaseMe::OnPaint(paint);
}

void P052::OnPaintGhost(CPaintMe *paint)
{
	PaintEx(paint, &m_startMarks, GetSelectedColor());
	CPlotBaseMe::OnPaintGhost(paint);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P053::P053()
{
	SetPlotType(L"GP");
}

ActionType P053::GetAction()
{
	ActionType action = ActionType_NO;
	if ((int)CPlotBaseMe::m_marks.size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		POINT mp = CPlotBaseMe::GetMouseOverPoint();
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		if ((mp.y >= (y1 - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (y1 + (CPlotBaseMe::m_lineWidth * 2.5))))
		{
			return ActionType_MOVE;
		}
		double list[11] = { 0.236, 0.382, 0.5, 0.618, 0.819, 1.191, 1.382, 1.618, 2.0, 2.382, 2.618 };
		for (int i = 0; i < 11; i++)
		{
			float yP = CPlotBaseMe::PY((double)(list[i] * sIter0->second->Value));
			if ((mp.y >= (yP - (CPlotBaseMe::m_lineWidth * 2.5))) && (mp.y <= (yP + (CPlotBaseMe::m_lineWidth * 2.5))))
			{
				return ActionType_MOVE;
			}
		}
	}
	return action;
}

bool P053::OnCreate(const POINT& mp)
{
	return CPlotBaseMe::CreatePoint(mp);
}

void P053::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	if (CPlotBaseMe::m_action != ActionType_NO)
	{
		if (CPlotBaseMe::m_action == ActionType_MOVE)
		{
			CPlotBaseMe::SetCursor(CursorsMe_Hand);
		}
		else
		{
			CPlotBaseMe::SetCursor(CursorsMe_SizeNS);
		}
		map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
		CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	}
}

void P053::OnMoving()
{
	POINT movingPoint = CPlotBaseMe::GetMovingPoint();
	if (CPlotBaseMe::m_action == ActionType_MOVE)
	{
		CPlotBaseMe::Move(movingPoint);
	}
}

void P053::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	if ((int)pList->size() != 0)
	{
		map<int,CPlotMarkMe*>::iterator sIter0 = CPlotBaseMe::m_marks.find(0);
		map<int,CPlotMarkMe*>::iterator sIter1 = CPlotBaseMe::m_marks.find(1);
		float y1 = CPlotBaseMe::PY(sIter0->second->Value);
		int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
		float x1 = CPlotBaseMe::PX(bIndex);
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, y1, (float) CPlotBaseMe::GetWorkingAreaWidth(), y1);
		double list[11] = { 0.236, 0.382, 0.5, 0.618, 0.819, 1.191, 1.382, 1.618, 2.0, 2.382, 2.618 };
		for (int i = 0; i < 11; i++)
		{
			float yP = CPlotBaseMe::PY((double)(list[i] * sIter0->second->Value));
			String str = CStrMe::ConvertIntToStr(list[i] * 100.0) + L"%";
			SIZE size = CPlotBaseMe::TextSize(paint, str.c_str(), CPlotBaseMe::m_font);
			CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, 1, (float)0, yP, (float)CPlotBaseMe::GetWorkingAreaWidth(), yP);
			CPlotBaseMe::DrawText(paint, str.c_str(), lineColor, CPlotBaseMe::m_font, (float)(CPlotBaseMe::GetWorkingAreaWidth() - size.cx), yP - size.cy);
		}
		if (IsSelected())
		{
			CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float* P054::GetGoldenRatioAimParams(map<int,CPlotMarkMe*> *pList, int *length)
{
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
	double baseValue = sIter0->second->Value;
	if (sIter1->second->Value >= sIter2->second->Value)
	{
		return CPlotBaseMe::GoldenRatioParams(baseValue, (baseValue + sIter1->second->Value) - sIter2->second->Value, length);
	}
	return CPlotBaseMe::GoldenRatioParams((baseValue + sIter1->second->Value) - sIter2->second->Value, baseValue, length);
}


P054::P054()
{
	SetPlotType(L"GA");
}

ActionType P054::GetAction()
{
	ActionType action = CPlotBaseMe::GetAction();
	int length = 0;
	float *goldenRatioAimParams = GetGoldenRatioAimParams(&m_marks, &length);
	if ((action == ActionType_NO) && CPlotBaseMe::HLinesSelect(goldenRatioAimParams, length))
	{
		action = ActionType_MOVE;
	}
	return action;
}

void P054::OnMoveStart()
{
	CPlotBaseMe::m_action = GetAction();
	CPlotBaseMe::ClearMarks(&m_startMarks);
	CPlotBaseMe::m_startPoint = CPlotBaseMe::GetMouseOverPoint();
	CPlotBaseMe::SetCursor(CursorsMe_Hand);
	map<int,CPlotMarkMe*>::iterator sIterPlot = CPlotBaseMe::m_marks.find(0);
	CPlotBaseMe::m_startMarks.insert(make_pair(0, sIterPlot->second));
	sIterPlot = CPlotBaseMe::m_marks.find(1);
	CPlotBaseMe::m_startMarks.insert(make_pair(1, sIterPlot->second));
	sIterPlot = CPlotBaseMe::m_marks.find(2);
	CPlotBaseMe::m_startMarks.insert(make_pair(2, sIterPlot->second));
}

void P054::Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor)
{
	map<int,CPlotMarkMe*>::iterator sIter0 = pList->find(0);
	map<int,CPlotMarkMe*>::iterator sIter1 = pList->find(1);
	map<int,CPlotMarkMe*>::iterator sIter2 = pList->find(2);
	float y1 = CPlotBaseMe::PY(sIter0->second->Value);
	float y2 = CPlotBaseMe::PY(sIter1->second->Value);
	float y3 = CPlotBaseMe::PY(sIter2->second->Value);
	int aIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter0->second->Key);
	int bIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter1->second->Key);
	int cIndex = CPlotBaseMe::m_dataSource->GetRowIndex(sIter2->second->Key);
	float x1 = CPlotBaseMe::PX(aIndex);
	float x2 = CPlotBaseMe::PX(bIndex);
	float x3 = CPlotBaseMe::PX(cIndex);
	CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x1, y1, x2, y2);
	CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, x2, y2, x3, y3);
	int length = 0;
	float *goldenRatioAimParams = GetGoldenRatioAimParams(pList, &length);
	String strArray[6] = { L"0.00%", L"23.60%", L"38.20%", L"50.00%", L"61.80%", L"100.00%" };
	for (int i = 0; i < length; i++)
	{
		SIZE size = CPlotBaseMe::TextSize(paint, strArray[i].c_str(), CPlotBaseMe::m_font);
		float yP = goldenRatioAimParams[i];
		CPlotBaseMe::DrawLine(paint, lineColor, CPlotBaseMe::m_lineWidth, CPlotBaseMe::m_lineStyle, (float)0, yP, (float) CPlotBaseMe::GetWorkingAreaWidth(), yP);
		CPlotBaseMe::DrawText(paint, strArray[i].c_str(), lineColor, CPlotBaseMe::m_font, (float) (CPlotBaseMe::GetWorkingAreaWidth() - size.cx), yP - size.cy);
	}
	if (IsSelected() || (((x1 == x2) && (x2 == x3)) && ((y1 == y2) && (y2 == y3))))
	{
		CPlotBaseMe::DrawSelect(paint, lineColor, x1, y1);
		CPlotBaseMe::DrawSelect(paint, lineColor, x2, y2);
		CPlotBaseMe::DrawSelect(paint, lineColor, x3, y3);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CPlotMe* PFactory::CreatePlot(const String& plotType)
{
	if(plotType == L"ANDREWSPITCHFORK")
	{
		return new P001();
	}
	else if(plotType == L"ANGLELINE")
	{
		return new P002();
	}
	else if(plotType == L"CIRCUMCIRCLE")
	{
		return new P003();
	}
	else if(plotType == L"ARROWSEGMENT")
	{
		return new P004();
	}
	else if(plotType == L"DOWNARROW")
	{
		return new P005();
	}
	else if(plotType == L"DROPLINE")
	{
		return new P006();
	}
	else if(plotType == L"ELLIPSE")
	{
		return new P009();
	}
	else if(plotType == L"FIBOELLIPSE")
	{
		return new P010();
	}
	else if(plotType == L"FIBOFANLINE")
	{
		return new P011();
	}
	else if(plotType == L"FIBOTIMEZONE")
	{
		return new P012();
	}
	else if(plotType == L"GANNBOX")
	{
		return new P014();
	}
	else if(plotType == L"GANNLINE")
	{
		return new P016();
	}
	else if(plotType == L"GOLDENRATIO")
	{
		return new P017();
	}
	else if(plotType == L"HLINE")
	{
		return new P018();
	}
	else if(plotType == L"LEVELGRADING")
	{
		return new P019();
	}
	else if(plotType == L"LINE")
	{
		return new P020();
	}
	else if(plotType == L"LRBAND")
	{
		return new P021();
	}
	else if(plotType == L"LRCHANNEL")
	{
		return new P022();
	}
	else if(plotType == L"LRLINE")
	{
		return new P023();
	}
	else if(plotType == L"NULLPOINT")
	{
		return new P024();
	}
	else if(plotType == L"PARALLEL")
	{
		return new P025();
	}
	else if(plotType == L"PERCENT")
	{
		return new P026();
	}
	else if(plotType == L"PERIODIC")
	{
		return new P027();
	}
	else if(plotType == L"PRICE")
	{
		return new P028();
	}
	else if(plotType == L"RANGERULER")
	{
		return new P029();
	}
	else if(plotType == L"RASELINE")
	{
		return new P030();
	}
	else if(plotType == L"RAY")
	{
		return new P031();
	}
	else if(plotType == L"RECT")
	{
		return new P032();
	}
	else if(plotType == L"SEGMENT")
	{
		return new P033();
	}
	else if(plotType == L"SINE")
	{
		return new P034();
	}
	else if(plotType == L"SPEEDRESIST")
	{
		return new P035();
	}
	else if(plotType == L"SECHANNEL")
	{
		return new P036();
	}
	else if(plotType == L"SYMMETRICLINE")
	{
		return new P037();
	}
	else if(plotType == L"SYMMETRICTRIANGLE")
	{
		return new P038();
	}
	else if(plotType == L"TIMERULER")
	{
		return new P041();
	}
	else if(plotType == L"TRIANGLE")
	{
		return new P042();
	}
	else if(plotType == L"UPARROW")
	{
		return new P043();
	}
	else if(plotType == L"VLINE")
	{
		return new P044();
	}
	else if(plotType == L"WAVERULER")
	{
		return new P045();
	}
	else if(plotType == L"TIRONELEVELS")
	{
		return new P046();
	}
	else if(plotType == L"RAFFCHANNEL")
	{
		return new P047();
	}
	else if(plotType == L"QUADRANTLINES")
	{
		return new P048();
	}
	else if(plotType == L"BOXLINE")
	{
		return new P049();
	}
	else if(plotType == L"PARALLELOGRAM")
	{
		return new P050();
	}
	else if(plotType == L"CIRCLE")
	{
		return new P051();
	}
	else if(plotType == L"PRICECHANNEL")
	{
		return new P052();
	}
	else if(plotType == L"GP")
	{
		return new P053();
	}
	else if(plotType == L"GA")
	{
		return new P054();
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

