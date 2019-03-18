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

	class P001:public CPlotBaseMe
	{
	public:
		P001();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P002:public CPlotBaseMe
	{
	public:
		P002();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P003:public CPlotBaseMe
	{
	public:
		P003();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P004:public CPlotBaseMe
	{
	public:
		P004();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class P005:public CPlotBaseMe
	{
	protected:
		RECT GetDownArrowRect(float x, float y, float width);
	public:
		P005();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class P006:public CPlotBaseMe
	{
	protected:
		float* GetDropLineParams(map<int, CPlotMarkMe*> *pList);
	public:
		P006();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P009:public CPlotBaseMe
	{
	public:
		P009();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P010:public CPlotBaseMe
	{
	protected:
		float* FibonacciEllipseParam(map<int, CPlotMarkMe*> *pList, int *length);
	public:
		P010();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P011:public CPlotBaseMe
	{
	public:
		P011();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P012:public CPlotBaseMe
	{
	protected:
		vector<int> GetFibonacciTimeZonesParam(map<int,CPlotMarkMe*> *pList);
	public:
		P012();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P014:public CPlotBaseMe
	{
	protected:
		POINT m_oppositePoint;
	public:
		P014();
		virtual ActionType GetAction();
		ActionType GetClickStatus();
		POINT* GetGannBoxPoints(float x1, float y1, float x2, float y2, int *length);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P016:public CPlotBaseMe
	{
	public:
		P016();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P017:public CPlotBaseMe
	{
	public:
		P017();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P018:public CPlotBaseMe
	{
	public:
		P018();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P019:public CPlotBaseMe
	{
	protected:
		float* LevelGradingParams(double value1, double value2, int *length);
	public:
		P019();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P020:public CPlotBaseMe
	{
	public:
		P020();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P021:public CPlotBaseMe
	{
	public:
		P021();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P022:public CPlotBaseMe
	{
	public:
		P022();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P023:public CPlotBaseMe
	{
	public:
		P023();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P024:public CPlotBaseMe
	{
	protected:
		void NullPoint(float x1, float y1, float x2, float y2, float *nullX, float *nullY);
		double* GetNullPointParams(map<int,CPlotMarkMe*> *pList);
	public:
		P024();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P025:public CPlotBaseMe
	{
	protected:
		float* GetParallelParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		P025();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P026:public CPlotBaseMe
	{
	protected:
		float* GetPercentParams(double value1, double value2, int *length);
	public:
		P026();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P027:public CPlotBaseMe
	{
	protected:
		int m_period;
		int m_beginPeriod;
	public:
		P027();
		virtual ActionType GetAction();
		vector<double> GetPLParams(map<int,CPlotMarkMe*> *pList);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P028:public CPlotBaseMe
	{
	protected:
		SIZE m_textSize;
	public:
		P028();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P029:public CPlotBaseMe
	{
	public:
		P029();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P030:public CPlotBaseMe
	{
	public:
		P030();
		float* GetRaseLineParams(map<int,CPlotMarkMe*> *pList);
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P031:public CPlotBaseMe
	{
	public:
		P031();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P032:public CPlotBaseMe
	{
	protected:
		POINT m_oppositePoint;
	public:
		P032();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P033:public CPlotBaseMe
	{
	public:
		P033();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P034:public CPlotBaseMe
	{
	public:
		P034();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P035:public CPlotBaseMe
	{
	public:
		P035();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P036:public CPlotBaseMe
	{
	protected:
		double GetSEChannelSD(map<int,CPlotMarkMe*> *pList);
	public:
		P036();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P037:public CPlotBaseMe
	{
	public:
		P037();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P038:public CPlotBaseMe
	{
	protected:
		float* GetSymmetricTriangleParams(map<int,CPlotMarkMe*> *pList);
	public:
		P038();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P041:public CPlotBaseMe
	{
	protected:
		double* GetTimeRulerParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		P041();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart(); 
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P042:public CPlotBaseMe
	{
	public:
		P042();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};
	class P043:public CPlotBaseMe
	{
	protected:
		RECT GetUpArrowRect(float x, float y, float width);
	public:
		P043();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P044:public CPlotBaseMe
	{
	public:
		P044();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P045:public CPlotBaseMe
	{
	protected:
		float* GetWaveRulerParams(double value1, double value2, int *length);
	public:
		P045();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P046:public CPlotBaseMe
	{
	protected:
		double* GetTironelLevelsParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		P046();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P047:public CPlotBaseMe
	{
	protected:
		double GetRRCRange(map<int,CPlotMarkMe*> *pList, float *param);
	public:
		P047();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P048:public P026
	{
	public: 
		P048();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P049:public P032
	{
	protected:
		ActionType GetAction(const POINT& mp);
	public:
		P049();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P050:public CPlotBaseMe
	{
	public:
		P050();
		virtual ActionType GetAction();
		POINT* GetPLPoints(map<int,CPlotMarkMe*> *pList, int *length);
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnPaintGhost(CPaintMe *paint);
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P051:public CPlotBaseMe
	{
	public:
		P051();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P052:public P025
	{
	protected:
		void GetLine3Params(map<int,CPlotMarkMe*> *pList, float *k, float *d, float *x4);
		void PaintEx(CPaintMe *paint, map<int,CPlotMarkMe*> *pList,_int64 lineColor);
	public:
		P052();
		virtual ActionType GetAction();
		virtual void OnMoveStart();
		virtual void OnPaint(CPaintMe *paint);
        virtual void OnPaintGhost(CPaintMe *paint);
	};

	class P053:public CPlotBaseMe
	{
	public:
		P053();
		virtual ActionType GetAction();
		virtual bool OnCreate(const POINT& mp);
		virtual void OnMoveStart();
		virtual void OnMoving();
		virtual void Paint(CPaintMe *paint, map<int,CPlotMarkMe*> *pList, _int64 lineColor);
	};

	class P054:public P042
	{
	protected:
		float* GetGoldenRatioAimParams(map<int,CPlotMarkMe*> *pList, int *length);
	public:
		P054();
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