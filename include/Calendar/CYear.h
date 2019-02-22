/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CYEARME_H__
#define __CYEARME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CMonth.h"

namespace MeLib
{
	class  CYearMe
	{
	protected:
		int m_year;
		void CreateMonths();
	public:
		CYearMe(int year);
		virtual ~CYearMe();
		map<int,CMonthMe*> Months;
	};
}

#endif