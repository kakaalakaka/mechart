/*****************************************************************************\
*                                                                             *
* GSEnum.h -    GannSquare types                                              *
*                                                                             *
*               Version 4.00 ¡ï¡ï¡ï                                           *
*                                                                             *
*               Copyright (c) 2016-2016, Lord's square. All rights reserved.  *
*                                                                             *
*******************************************************************************/

#ifndef __GSENUMS_H__
#define __GSENUMS_H__
#pragma once
#include "..\\..\\stdafx.h"

namespace OwLib
{
	typedef enum BolsterOrStress
	{
		BolsterOrStress_Bolster,
		BolsterOrStress_Stress
	};

	typedef enum SquareCellStyle
	{
		SquareCellStyle_Major,
		SquareCellStyle_Minor,
		SquareCellStyle_Normal
	};

	typedef enum SquareStyle
	{
		SquareStyle_Normal,
		SquareStyle_Spiral
	};
}
#endif