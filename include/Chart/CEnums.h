/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CENUMSME_H__
#define __CENUMSME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	typedef enum  ActionType
	{
		ActionType_AT1 = 1,
		ActionType_AT2 = 2,
		ActionType_AT3 = 3,
		ActionType_AT4 = 4,
		ActionType_MOVE = 0,
		ActionType_NO = -1
	};

	typedef enum  AttachVScale
	{
		AttachVScale_Left,
		AttachVScale_Right
	};

	typedef enum  BarStyle
	{
		BarStyle_Line,
		BarStyle_Rect
	};

	typedef enum  CandleStyle
	{
		CandleStyle_American,
		CandleStyle_CloseLine,
		CandleStyle_Rect,
		CandleStyle_Tower
	};

	typedef enum  CrossLineMoveMode
	{
		CrossLineMoveMode_AfterClick,
		CrossLineMoveMode_FollowMouse
	};

	typedef enum  DateType
	{
		DateType_Day = 2,
		DateType_Hour = 3,
		DateType_Millisecond = 6,
		DateType_Minute = 4,
		DateType_Month = 1,
		DateType_Second = 5,
		DateType_Year = 0
	};

	typedef enum  HScaleType
	{
		HScaleType_Date,
		HScaleType_Number
	};

	typedef enum  NumberStyle
	{
		NumberStyle_Standard,
		NumberStyle_Underline
	};

	typedef enum  PolylineStyle
	{
		PolylineStyle_Cycle,
		PolylineStyle_DashLine,
		PolylineStyle_DotLine,
		PolylineStyle_SolidLine
	};

	typedef enum  ScrollType
	{
		ScrollType_None,
		ScrollType_Left,
		ScrollType_Right,
		ScrollType_ZoomIn,
		ScrollType_ZoomOut
	};

	typedef enum  SelectPoint
	{
		SelectPoint_Ellipse,
		SelectPoint_Rect
	};

	typedef enum  TextMode
	{
		TextMode_Field,
		TextMode_Full,
		TextMode_None,
		TextMode_Value
	};

	typedef enum  VScaleSystem
	{
		VScaleSystem_Logarithmic,
		VScaleSystem_Standard
	};

	typedef enum  VScaleType
	{
		VScaleType_Divide,
		VScaleType_EqualDiff,
		VScaleType_EqualRatio,
		VScaleType_GoldenRatio,
		VScaleType_Percent
	};
}
#endif