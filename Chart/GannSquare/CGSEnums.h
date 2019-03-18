/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGSENUMSME_H__
#define __CGSENUMSME_H__
#pragma once
#include "..\\..\\stdafx.h"

namespace MeLib
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