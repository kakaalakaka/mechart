#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CYear.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CYearMe::CreateMonths()
{
	for (int i = 1; i <= 12; i++)
	{
		Months.insert(make_pair(i, new CMonthMe(m_year, i)));
	}
}

CYearMe::CYearMe(int year)
{
	m_year = year;
	CreateMonths();
}

CYearMe::~CYearMe()
{
	map<int,CMonthMe*>::iterator sIter = Months.begin();
	for(; sIter != Months.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Months.clear();
}