/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CMONTHME_H__
#define __CMONTHME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CDay.h"

namespace MeLib
{
	class  CMonthMe
	{
	protected:
		int m_month;
		int m_year;
		void CreateDays();
	public:
		CMonthMe(int year, int month);
		virtual ~CMonthMe();
		map<int,CDayMe*> Days;
		int GetDaysInMonth();
		CDayMe* GetFirstDay();
		CDayMe* GetLastDay();
		int GetMonth();
		int GetYear();
	};
}
#endif