/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGRIDENUMSME_H__
#define __CGRIDENUMSME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	typedef enum  GridColumnSortMode
	{
		GridColumnSortMode_Asc,
		GridColumnSortMode_Desc,
		GridColumnSortMode_None
	};

	typedef enum  GridSelectionMode
	{
		GridSelectionMode_SelectCell,
		GridSelectionMode_SelectFullColumn,
		GridSelectionMode_SelectFullRow,
		GridSelectionMode_SelectNone
	};

	typedef enum  GridCellEditMode
	{
        GridCellEditMode_DoubleClick,
        GridCellEditMode_None,
        GridCellEditMode_SingleClick
	};
}

#endif