/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CDAYME_H__
#define __CDAYME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	class  CDayMe
	{
	protected:
		int m_day;
		int m_month;
		int m_year;
	public:
		CDayMe(int year, int month, int day);
		virtual ~CDayMe();
		int GetDay();
		int GetMonth();
		int GetYear();
	};
}
#endif