/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CPEXTENDME_H__
#define __CPEXTENDME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "CPlot.h"
#include "CPlotBase.h"

namespace MeLib
{
	class CPlotBase;

	class PlotAndrewsPitchFork:public CPlotBaseMe
	{
	public:
		PlotAndrewsPitchFork();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotAngleLine:public CPlotBaseMe
	{
	public:
		PlotAngleLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotCircumCircle:public CPlotBaseMe
	{
	public:
		PlotCircumCircle();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotArrowSegment:public CPlotBaseMe
	{
	public:
		PlotArrowSegment();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class PlotDownArrow:public CPlotBaseMe
	{
	protected:
		RECT GetDownArrowRect(float x, float y, float width);
	public:
		PlotDownArrow();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class PlotDropLine:public CPlotBaseMe
	{
	protected:
		float* GetDropLineParams(map<int, CPlotMarkMe*> *pList);
	public:
		PlotDropLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotEllipse:public CPlotBaseMe
	{
	public:
		PlotEllipse();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotFiboEllipse:public CPlotBaseMe
	{
	protected:
		float* FibonacciEllipseParam(map<int, CPlotMarkMe*> *pList, int *length);
	public:
		PlotFiboEllipse();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotFibofanLine:public CPlotBaseMe
	{
	public:
		PlotFibofanLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotFiboTimeZone:public CPlotBaseMe
	{
	protected:
		vector<int> GetFibonacciTimeZonesParam(map<int,CPlotMarkMe*> *pList);
	public:
		PlotFiboTimeZone();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotGannbox:public CPlotBaseMe
	{
	protected:
		POINT m_oppositePoint;
	public:
		PlotGannbox();
		virtual ActionType GetAction();
		ActionType GetClickStatus();
		POINT* GetGannBoxPoints(float x1, float y1, float x2, float y2, int *length);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotGannLine:public CPlotBaseMe
	{
	public:
		PlotGannLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotGoldenRatio:public CPlotBaseMe
	{
	public:
		PlotGoldenRatio();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotHline:public CPlotBaseMe
	{
	public:
		PlotHline();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotLevelGrading:public CPlotBaseMe
	{
	protected:
		float* LevelGradingParams(double value1, double value2, int *length);
	public:
		PlotLevelGrading();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotLine:public CPlotBaseMe
	{
	public:
		PlotLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotLrBand:public CPlotBaseMe
	{
	public:
		PlotLrBand();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotLrChannel:public CPlotBaseMe
	{
	public:
		PlotLrChannel();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotLrLine:public CPlotBaseMe
	{
	public:
		PlotLrLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotNullPoint:public CPlotBaseMe
	{
	protected:
		void NullPoint(float x1, float y1, float x2, float y2, float *nullX, float *nullY);
		double* GetNullPointParams(map<int,CPlotMarkMe*> *pList);
	public:
		PlotNullPoint();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotParallel:public CPlotBaseMe
	{
	protected:
		float* GetParallelParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		PlotParallel();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotPercent:public CPlotBaseMe
	{
	protected:
		float* GetPercentParams(double value1, double value2, int *length);
	public:
		PlotPercent();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotPeriodic:public CPlotBaseMe
	{
	protected:
		int m_period;
		int m_beginPeriod;
	public:
		PlotPeriodic();
		virtual ActionType GetAction();
		vector<double> GetPLParams(map<int,CPlotMarkMe*> *pList);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotPrice:public CPlotBaseMe
	{
	protected:
		SIZE m_textSize;
	public:
		PlotPrice();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotRangeruler:public CPlotBaseMe
	{
	public:
		PlotRangeruler();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotRaseline:public CPlotBaseMe
	{
	public:
		PlotRaseline();
		float* GetRaseLineParams(map<int,CPlotMarkMe*> *pList);
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotRay:public CPlotBaseMe
	{
	public:
		PlotRay();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotRect:public CPlotBaseMe
	{
	protected:
		POINT m_oppositePoint;
	public:
		PlotRect();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSegement:public CPlotBaseMe
	{
	public:
		PlotSegement();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSine:public CPlotBaseMe
	{
	public:
		PlotSine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSpeedresist:public CPlotBaseMe
	{
	public:
		PlotSpeedresist();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSechannel:public CPlotBaseMe
	{
	protected:
		double GetSEChannelSD(map<int,CPlotMarkMe*> *pList);
	public:
		PlotSechannel();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSymmetricLine:public CPlotBaseMe
	{
	public:
		PlotSymmetricLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotSymmetricTriangle:public CPlotBaseMe
	{
	protected:
		float* GetSymmetricTriangleParams(map<int,CPlotMarkMe*> *pList);
	public:
		PlotSymmetricTriangle();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotTimeRuler:public CPlotBaseMe
	{
	protected:
		double* GetTimeRulerParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		PlotTimeRuler();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart(); 
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotTriangle:public CPlotBaseMe
	{
	public:
		PlotTriangle();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class PlotUpArrow:public CPlotBaseMe
	{
	protected:
		RECT GetUpArrowRect(float x, float y, float width);
	public:
		PlotUpArrow();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotVLine:public CPlotBaseMe
	{
	public:
		PlotVLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotWavRuler:public CPlotBaseMe
	{
	protected:
		float* GetWaveRulerParams(double value1, double value2, int *length);
	public:
		PlotWavRuler();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotTironelevels:public CPlotBaseMe
	{
	protected:
		double* GetTironelLevelsParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		PlotTironelevels();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotRaffchannel:public CPlotBaseMe
	{
	protected:
		double GetRRCRange(map<int,CPlotMarkMe*> *pList, float *param);
	public:
		PlotRaffchannel();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotQuadrantLines:public PlotPercent
	{
	public: 
		PlotQuadrantLines();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotBoxLine:public PlotRect
	{
	protected:
		ActionType GetAction(const POINT& mp);
	public:
		PlotBoxLine();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotParallelogram:public CPlotBaseMe
	{
	public:
		PlotParallelogram();
		virtual ActionType GetAction();
		POINT* GetPLPoints(map<int,CPlotMarkMe*> *pList, int *length);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotCircle:public CPlotBaseMe
	{
	public:
		PlotCircle();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotPriceChannel:public PlotParallel
	{
	protected:
		void GetLine3Params(map<int,CPlotMarkMe*> *pList, float *k, float *d, float *x4);
		void PaintEx(CPaintMe *paint, map<int,CPlotMarkMe*> *pList,_int64 lineColor);
	public:
		PlotPriceChannel();
		virtual ActionType GetAction();
		virtual void OnMoveStart();
		virtual void OnPaint(CPaintMe *paint);
        virtual void OnPaintGhost(CPaintMe *paint);
	};

	class PlotGP:public CPlotBaseMe
	{
	public:
		PlotGP();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PlotGA:public PlotTriangle
	{
	protected:
		float* GetGoldenRatioAimParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		PlotGA();
		virtual ActionType GetAction();
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class PFactory
	{
	public:
		static CPlotMe* CreatePlot(const String& plotType);
	};
}
#endif