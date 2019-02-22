#include "..\\stdafx.h"
#include "..\\include\\Calendar\\CDay.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CDayMe::CDayMe(int year, int month, int day)
{
	m_year = year;
	m_month = month;
	m_day = day;
}

CDayMe::~CDayMe()
{
}

int CDayMe::GetDay()
{
	return m_day;
}

int CDayMe::GetMonth()
{
	return m_month;
}

int CDayMe::GetYear()
{
	return m_year;
}