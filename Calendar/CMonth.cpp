#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CMonth.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CMonthMe::CreateDays()
{
	int daysInMonth = GetDaysInMonth();
	for (int i = 1; i <= daysInMonth; i++)
	{
		Days.insert(make_pair(i, new CDayMe(m_year, m_month, i)));
	}
}

CMonthMe::CMonthMe(int year, int month)
{
	m_year = year;
	m_month = month;
	CreateDays();
}

CMonthMe::~CMonthMe()
{
	map<int,CDayMe*>::iterator sIter = Days.begin();
	for(; sIter != Days.end(); ++sIter)
	{
		delete sIter->second;
		sIter->second = 0;
	}
	Days.clear();
}

int CMonthMe::GetDaysInMonth()
{
	int days = 0;
	int dayArray[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (2 == m_month)
	{
		days = (((0 == m_year % 4) && (0 != m_year % 100) || (0 == m_year % 400)) ? 29 : 28);
	}
	else
	{
		days = dayArray[m_month - 1];
	}
	return days;
}

CDayMe* CMonthMe:: GetFirstDay()
{
	map<int,CDayMe*>::iterator sIter = Days.find(1);
	if(sIter != Days.end())
	{
		return sIter->second;
	}
	return 0;
}

CDayMe* CMonthMe::GetLastDay()
{
	int size = (int)Days.size();
	map<int,CDayMe*>::iterator sIter = Days.find(size);
	if(sIter != Days.end())
	{
		return sIter->second;
	}
	return 0;
}

int CMonthMe::GetMonth()
{
	return m_month;
}

int CMonthMe::GetYear()
{
	return m_year;
}