/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCHARTME_H__
#define __CCHARTME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "..\\Base\\CMathLib.h"
#include "CTable.h"
#include "CDiv.h"
#include "CPlot.h"
#include "CBaseShape.h"
#include "CVScale.h"

namespace MeLib
{
	class  CDivMe;
	class  CPlotMe;
	class  CBaseShapeMe;
	class  CBarShapeMe;
	class  CPointShapeMe;
	class  CCandleShapeMe;
	class  CPolylineShapeMe;
	class  CTextShapeMe;
	class  CControlMe;
	class  CVScaleMe;

	class  CChartMe:public CControlMe
	{
	private:
		int m_timerID;
	protected:
		bool m_autoFillHScale;
		int m_blankSpace;
		bool m_canMoveShape;
		bool m_canResizeV;
		bool m_canResizeH;
		bool m_canScroll;
		bool m_canZoom;
		CrossLineMoveMode m_crossLineMoveMode;
		int m_crossStopIndex;
		int m_cross_y;
		CTableMe *m_dataSource;
		vector<CDivMe*> m_divs;
		int m_firstVisibleIndex;
		int m_hResizeType;
		wstring m_hScaleFieldText;
		double m_hScalePixel;
		bool m_isMouseMove;
		bool m_isScrollCross;
		POINT m_lastMouseMovePoint;
		POINT m_lastMouseClickPoint;
		double m_lastMouseMoveTime;
		bool m_lastRecordIsVisible;
		int m_lastUnEmptyIndex;
		double m_lastVisibleKey;
		int m_lastVisibleIndex;
		int m_leftVScaleWidth;
		int m_maxVisibleRecord;
		CPlotMe *m_movingPlot;
		CBaseShapeMe *m_movingShape;
		bool m_reverseHScale;
		int m_rightVScaleWidth;
		bool m_scrollAddSpeed;
		int m_scrollStep;
		bool m_showCrossLine;
		bool m_showingSelectArea;
		bool m_showingToolTip;
		int m_tooltip_dely;
		CDivMe *m_userResizeDiv;
		int m_workingAreaWidth;
	public:
		virtual void DrawThinLine(CPaintMe *paint, _int64 dwPenColor, int width, int x1, int y1, int x2, int y2);
		virtual void DrawText(CPaintMe *paint, LPCWSTR strText, _int64 dwPenColor,FONT *font, int left, int top);
		virtual vector<double> GetVScaleStep(double max, double min, CDivMe *div, CVScaleMe *vScale);
		virtual void OnPaintBar(CPaintMe *paint, CDivMe *div, CBarShapeMe *bs);
		virtual void OnPaintCandle(CPaintMe *paint, CDivMe *div, CCandleShapeMe *cs);
		virtual void OnPaintCandleEx(CPaintMe *paint, CDivMe *div, CCandleShapeMe *cs, int visibleMaxIndex, double visibleMax, int visibleMinIndex, double visibleMin);
		virtual void OnPaintCrossLine(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintDivBackGround(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintDivBorder(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintHScale(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintIcon(CPaintMe *paint);
		virtual void OnPaintPlots(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintPolyline(CPaintMe *paint, CDivMe *div, CPolylineShapeMe *ls);
		virtual void OnPaintPolyline(CPaintMe *paint, CDivMe *div, _int64 lineColor, _int64 fillColor, int ciClr,
				float lineWidth, PolylineStyle lineStyle, double value, AttachVScale attachVScale,
				int scaleX, int lY, int i, vector<POINT> *points, int *x, int *y);
		virtual void OnPaintResizeLine(CPaintMe *paint);
		virtual void OnPaintSelectArea(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintShapes(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintText(CPaintMe *paint, CDivMe *div, CTextShapeMe *ts);
		virtual void OnPaintTitle(CPaintMe *paint, CDivMe *div);
		virtual void OnPaintToolTip(CPaintMe *paint);
		virtual void OnPaintVScale(CPaintMe *paint, CDivMe *div);
	protected:
		virtual void CorrectVisibleRecord(int dataCount, int *first, int *last);
		virtual void GetCandleMaxStringPoint(float scaleX, float scaleY, float stringWidth, float stringHeight, int actualWidth,
		int leftVScaleWidth, int rightVScaleWidth, float *x, float *y);
		virtual void GetCandleMinStringPoint(float scaleX, float scaleY, float stringWidth, float stringHeight, int actualWidth,
		int leftVScaleWidth, int rightVScaleWidth, float *x, float *y);
		virtual int GetChartIndex(int x, int leftScaleWidth, double hScalePixel, int firstVisibleIndex);
		virtual float GetUpCandleHeight(double close, double open, double max, double min, float divPureV);
		virtual float GetDownCandleHeight(double close, double open, double max, double min, float divPureV);
		virtual void ScrollLeft(int step, int dateCount, double hScalePixel, int pureH, int *fIndex, int *lIndex);
		virtual void ScrollRight(int step, int dataCount, double hScalePixel, int pureH, int *fIndex, int *lIndex);
		virtual double GetVScaleValue(int y, double max, double min, float vHeight);
		virtual int ResetCrossOverIndex(int dataCount, int maxVisibleRecord, int crossStopIndex, int firstL, int lastL);
		virtual void ZoomIn(int pureH, int dataCount, int *findex, int *lindex, double *hScalePixel);
		virtual void ZoomOut(int pureH,int dataCount, int *findex, int *lindex, double *hScalePixel);
	public:
		CChartMe();
		virtual ~CChartMe();
		virtual bool AutoFillHScale();
		virtual void SetAutoFillHScale(bool autoFillHScale);
		virtual int GetBlankSpace();
		virtual void SetBlankSpace(int blankSpace);
		virtual bool CanMoveShape();
		virtual void SetCanMoveShape(bool canMoveShape);
		virtual bool CanResizeV();
		virtual void SetCanResizeV(bool canResizeV);
		virtual bool CanResizeH();
		virtual void SetCanResizeH(bool canResizeH);
		virtual bool CanScroll();
		virtual void SetCanScroll(bool canScroll);
		virtual bool CanZoom();
		virtual void SetCanZoom(bool canZoom);
		virtual CrossLineMoveMode GetCrossLineMoveMode();
		virtual void SetCrossLineMoveMode(CrossLineMoveMode crossLineMoveMode);
		virtual int GetCrossStopIndex();
		virtual void SetCrossStopIndex(int crossStopIndex);
		virtual CTableMe* GetDataSource();
		virtual void SetDataSource(CTableMe *dataSource);
		virtual int GetFirstVisibleIndex();
		virtual void SetFirstVisibleIndex(int firstVisibleIndex);
		virtual wstring GetHScaleFieldText();
		virtual void SetHScaleFieldText(const wstring& hScaleFieldText);
		virtual double GetHScalePixel();
		virtual void SetHScalePixel(double hScalePixel);
		virtual int GetLastVisibleIndex();
		virtual void SetLastVisibleIndex(int lastVisibleIndex);
		virtual int GetLeftVScaleWidth();
		virtual void SetLeftVScaleWidth(int leftVScaleWidth);
		virtual int GetMaxVisibleRecord();
		virtual void SetMaxVisibleRecord(int maxVisibleRecord);
		virtual CPlotMe* GetMovingPlot();
		virtual CBaseShapeMe* GetMovingShape();
		virtual bool IsReverseHScale();
		virtual void SetReverseHScale(bool reverseHScale);
		virtual int GetRightVScaleWidth();
		virtual void SetRightVScaleWidth(int rightVScaleWidth);
		virtual bool IsScrollAddSpeed();
		virtual void SetScrollAddSpeed(bool scrollAddSpeed);
		virtual CBaseShapeMe* GetSelectedShape();
		virtual void SetSelectedShape(CBaseShapeMe *baseShape);
		virtual CPlotMe* GetSelectedPlot();
		virtual void SetSelectedPlot(CPlotMe *selectedPlot);
		virtual CDivMe* GetSelectedDiv();
		virtual void SetSelectedDiv(CDivMe *selectedDiv);
		virtual bool IsShowCrossLine();
		virtual void SetShowCrossLine(bool showCrossLine);
		virtual int GetWorkingAreaWidth();
	public:
		virtual CDivMe* AddDiv(int vPercent);
		virtual CDivMe* AddDiv();
		virtual void Adjust();
		virtual void AddPlot(CPlotMe *bpl, const POINT& mp, CDivMe *div);
		virtual void Clear();
		virtual void ChangeChart(ScrollType scrollType, int limitStep);
		virtual void CheckLastVisibleIndex();
		virtual void CheckToolTip();
		virtual void ClearSelectedShape();
		virtual void ClearSelectedPlot();
		virtual void ClearSelectedDiv();
		virtual void CloseSelectArea();
		virtual double DivMaxOrMin(int index, CDivMe *div, int flag);
		virtual CDivMe* FindDiv(const POINT& mp);
		virtual CDivMe* FindDiv(CBaseShapeMe *shape);
		virtual wstring GetControlType();
		virtual int GetDateType(DateType dateType);
		virtual DateType GetDateType(int dateType);
		virtual vector<CDivMe*> GetDivs();
		virtual void GetHScaleDateString(double date, double lDate, DateType *dateType, wchar_t *str);
		virtual int GetIndex(const POINT& mp);
		virtual int GetMaxVisibleCount(double hScalePixel, int pureH);
		virtual CDivMe* GetMouseOverDiv();
		virtual int GetMouseOverIndex();
		double GetNumberValue(CDivMe *div, const POINT& mp, AttachVScale attachVScale);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual int GetShapesCount(int field);
		virtual float GetX(int index);
		virtual float GetY(CDivMe *div,double value,AttachVScale attach);
		virtual int GetVScaleBaseField(CDivMe *div, CVScaleMe *vScale);
		virtual double GetVScaleBaseValue(CDivMe *div, CVScaleMe *vScale, int i);
		virtual bool IsOperating();
		virtual void LocateCrossLine();
		virtual void MoveShape(CDivMe *div, CBaseShapeMe *shape);
		virtual void ResetCrossOverIndex();
		virtual void RemoveAll();
		virtual bool ResizeDiv();
		virtual void RemoveDiv(CDivMe *div);
		virtual void Reset();
		virtual void ResetVisibleRecord();
		virtual void ScrollLeft(int step);
		virtual void ScrollLeftToBegin();
		virtual void ScrollRight(int step);
		virtual void ScrollRightToEnd();
		virtual void ScrollCrossLineLeft(int step);
		virtual void ScrollCrossLineRight(int step);
		virtual CBaseShapeMe* SelectShape(int curIndex, int state);
		virtual bool SelectBar(CDivMe *div, float mpY, int fieldName, int fieldName2, int styleField, AttachVScale attachVScale, int curIndex);
		virtual bool SelectCandle(CDivMe *div, float mpY, int highField, int lowField, int styleField, AttachVScale attachVScale, int curIndex);
		virtual bool SelectPolyline(CDivMe *div, const POINT& mp, int fieldName, float lineWidth, AttachVScale attachVScale, int curIndex);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void SetVisibleIndex(int firstVisibleIndex, int lastVisibleIndex);
		virtual void Update();
		virtual void ZoomIn();
		virtual void ZoomOut();
	public:
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnKeyUp(char key);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnTimer(int timerID);
	};
}
#endif