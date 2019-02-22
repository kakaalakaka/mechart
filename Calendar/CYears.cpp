#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CYears.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CYearsMe::CYearsMe()
{

}

CYearsMe::~CYearsMe()
{
	map<int,CYearMe*>::iterator sIter = Years.begin();
	for(; sIter != Years.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Years.clear();
}

CYearMe* CYearsMe::GetYear(int year)
{
	map<int, CYearMe*>::iterator sIter = Years.find(year);
	if(sIter != Years.end())
	{
		return sIter->second;
	}
	else
	{
		CYearMe* cYear = new CYearMe(year);
		Years.insert(make_pair(year, cYear));
		return cYear;
	}
}