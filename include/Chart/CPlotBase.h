/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CPLOTBASEME_H__
#define __CPLOTBASEME_H__
#pragma once
#include "..\\stdafx.h"
#include "..\\include\\Base\\CStr.h"
#include "..\\include\\Base\\CNativeBase.h"
#include "..\\include\\Base\\CPaint.h"
#include "..\\include\\Base\\CMathLib.h"
#include "CDiv.h"
#include "CChart.h"
#include "CTable.h"
#include "CPlot.h"

namespace MeLib
{
	class CDivMe;
	class CTable;
	class CChartMe;
	class CNativeBaseMe;
	class CMathLibMe;
	class CPlotMe;
	class CPlotMarkMe
	{
	public:
		CPlotMarkMe(int index, double key, double value)
		{
			Index = index;
			Key = key;
			Value = value;
		}
		int Index;
		double Key;
		double Value;
		CPlotMarkMe* Copy()
		{
			CPlotMarkMe *plotMark = new CPlotMarkMe(Index, Key, Value);
			return plotMark;
		}
	};

	class CPlotBaseMe : public CPlotMe
	{
	protected:
		ActionType m_action;
		AttachVScale m_attachVScale;
		_int64 m_color;
		CTableMe *m_dataSource;
		CDivMe *m_div;
		bool m_drawGhost;
		bool m_enabled;
		FONT *m_font;
		bool m_isPaintingGhost;
		int m_lineStyle;
		int m_lineWidth;
		map<int,CPlotMarkMe*> m_marks;
		int m_moveTimes;
		String m_plotType;
		map<String,int> m_sourceFields;
		map<int,CPlotMarkMe*> m_startMarks;
		bool m_selected;
		_int64 m_selectedColor;
		SelectPoint m_selectedPoint;
		POINT m_startPoint;
		String m_text;
		bool m_visible;
		int m_zOrder;
	protected:
		void DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, const RECT& rect);
		void DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, int left, int top, int right, int bottom);
		void DrawEllipse(CPaintMe *paint, _int64 dwPenColor, int width, int style, float left, float top, float right, float bottom);
		void DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, const POINT& x, const POINT& y);
		void DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, int x1, int y1, int x2, int y2);
		void DrawLine(CPaintMe *paint, _int64 dwPenColor, int width, int style, float x1, float y1, float x2, float y2);
		void DrawPolygon(CPaintMe *paint, _int64 dwPenColor, int width, int style, POINT *apt, int cpt);
		void DrawPolyline(CPaintMe *paint, _int64 dwPenColor, int width, int style, POINT *apt, int cpt);
		void DrawRay(CPaintMe *paint, _int64 dwPenColor, int width, int style, float x1, float y1, float x2, float y2, float k, float b);
		void DrawRect(CPaintMe *paint, _int64 dwPenColor, int width, int style, int left, int top, int right, int bottom);
		void DrawRect(CPaintMe *paint, _int64 dwPenColor, int width, int style, const RECT& rect);
		void DrawSelect(CPaintMe *paint, _int64 dwPenColor, int x, int y);
		void DrawSelect(CPaintMe *paint, _int64 dwPenColor, float x, float y);
		void DrawText(CPaintMe *paint, LPCWSTR strText, _int64 dwPenColor, FONT *font, int left, int top);
		void FillEllipse(CPaintMe *paint, _int64 dwPenColor, const RECT& rect);
		void FillPolygon(CPaintMe *paint, _int64 dwPenColor, POINT *apt, int cpt);
		void FillRect(CPaintMe *paint, _int64 dwPenColor, const RECT& rect);
		void UpdateSourceField(const String& fieldName, int fieldId);
		SIZE TextSize(CPaintMe *paint, LPCWSTR strText, FONT *font);
	protected:
		void MovePlot(float mouseY, float startY, int startIndex, int mouseBeginIndex, int mouseEndIndex, float pureV,
		double max, double min, int dataCount, double *yAddValue, int *newIndex);
	protected:
		void ClearMarks(map<int,CPlotMarkMe*> *marks);
		CNativeBaseMe* GetNative();
		bool CreatePoint(const POINT& mp);
		bool Create2PointsA(const POINT& mp);
		bool Create2PointsB(const POINT& mp);
		bool Create2CandlePoints(const POINT& mp);
		bool Create3Points(const POINT& mp);
		void CreateCandlePoint(int pos, int index, int close);
		bool Create4CandlePoints(const POINT& mp);	
		double* GetCandleRange(map<int,CPlotMarkMe*> *pList, int *length);
		POINT GetMouseOverPoint();
		int GetIndex(const POINT& mp);
		float* GetLineParams(CPlotMarkMe *markA, CPlotMarkMe *markB, int *length);
		double* GetLRBandRange(map<int,CPlotMarkMe*> *marks, float *param);
		float* GetLRParams(map<int,CPlotMarkMe*> *marks);
		POINT GetMovingPoint();
		double GetNumberValue(const POINT& mp);
		int GetPx();
		int GetPy();
		RECT GetRectangle(CPlotMarkMe *markA, CPlotMarkMe *markB);
		float* GoldenRatioParams(double value1, double value2, int *length);
		bool HLinesSelect(float *param, int length);
		void Move(const POINT& mp);
		virtual void OnPaint(CPaintMe *paint);
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
		float PX(int index);
		float PY(double value);
		float PX(float x);
		float PY(float y);
		void Resize(int index);
		void Resize(const POINT& mp, POINT oppositePoint);
		bool SelectPoint(const POINT& mp, float x, float y);
		bool SelectLine(const POINT& mp, float x, float k, float b);
		bool SelectLine(const POINT& mp, float x1, float y1, float x2, float y2);
		bool SelectRay(const POINT& mp, float x1, float y1, float x2, float y2, float *pk, float *pb);
		bool SelectRay(const POINT& mp, float x1, float y1, float x2, float y2);
		ActionType SelectRect(const POINT& mp, CPlotMarkMe *markA, CPlotMarkMe *markB);
		bool SelectSegment(const POINT& mp, float x1, float y1, float x2, float y2);
		bool SelectSine(const POINT& mp,float x1, float y1, float x2, float y2);
		bool SelectTriangle(const POINT& mp, float x1, float y1, float x2, float y2, float x3, float y3);
	public:
		CPlotBaseMe();
		virtual ~CPlotBaseMe();
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual _int64 GetColor();
		virtual void SetColor(_int64 color);
		CursorsMe GetCursor();
		void SetCursor(CursorsMe cursor);
		virtual CDivMe* GetDiv();
		virtual void SetDiv(CDivMe *div);
		virtual bool DrawGhost();
		virtual void SetDrawGhost(bool drawGhost);
		virtual bool IsEnabled();
		virtual void SetEnabled(bool enabled);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual CChartMe* GetChart();
		virtual int GetLineStyle();
		virtual void SetLineStyle(int lineStyle);
		virtual int GetLineWidth();
		virtual void SetLineWidth(int lineWidth);
		virtual String GetPlotType();
		virtual void SetPlotType(const String& plotType);
		virtual bool IsSelected();
		virtual void SetSelected(bool selected);
		virtual _int64 GetSelectedColor();
		virtual void SetSelectedColor(_int64 selectedColor);
		virtual enum SelectPoint GetSelectedPoint();
		virtual void SetSelectedPoint(enum SelectPoint selectedPoint);
		virtual String GetText();
		virtual void SetText(const String& text);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetWorkingAreaWidth();
		virtual int GetWorkingAreaHeight();
		virtual int GetZOrder();
		virtual void SetZOrder(int zOrder);
	public:
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveEnd();
		virtual void OnMoving();
		virtual void OnMoveStart();
		virtual bool OnSelect();
		virtual void Render(CPaintMe *paint);
	};
}
#endif