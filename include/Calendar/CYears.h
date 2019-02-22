/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CYEARSME_H__
#define __CYEARSME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CYear.h"

namespace MeLib
{
	class  CYearsMe
	{
	public:
		CYearsMe();
		virtual ~CYearsMe();
		map<int,CYearMe*> Years;
		CYearMe* GetYear(int year);
	};
}

#endif