/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCTABLEME_H__
#define __CCTABLEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CList.h"

namespace MeLib
{
	class  CTableMe;

	class  CRowMe
	{
	protected:
		double NaN;
		CTableMe *m_table;
		CListMe<double> m_values;
	public:
		CRowMe(CTableMe *table);
		CRowMe(CTableMe *table, int capacity, int step);
		CRowMe(CTableMe *table, double *ary, int size);
		virtual ~CRowMe();
		void FillEmpty(int columns);
		double Get(int index);
		void Remove(int index);
		void Set(int index, double value);
	};

	class  CTableMe
	{
	protected:
		int m_autoField;
		int m_colsCapacity;
		int m_colsStep;
		CListMe<int*> m_columns;
		CListMe<double> m_keys;
		CListMe<CRowMe*> m_rows;
		CRowMe* AddKey(double num);
		void FillEmpty();
	public:
		double NaN;
		CTableMe();
		virtual ~CTableMe();
		int AUTOFIELD();
		static inline int NULLFIELD()
		{
			return -1;
		}
		void AddColumn(int colName);
		void AddRow(double pk, double *ary, int size);
		int ColumnsCount();
		void Clear();
		int GetColumnIndex(int colName);
		int GetRowIndex(double key);
		double GetXValue(int rowIndex);
		double Get(double pk, int colName);
		double Get2(int rowIndex, int colName);
		double Get3(int rowIndex, int colIndex);
		static inline bool IsNaN(double value)
		{
			return ((*(((long long*) &value)) & 0x7fffffffffffffffL) > 0x7ff0000000000000L);
		}
		void RemoveAt(int rowIndex);
		void RemoveColumn(int name);
		int RowsCount();
		void Set(double pk, int colName, double value);
		void Set2(int rowIndex, int colName, double value);
		void Set3(int rowIndex, int colIndex, double value);
		void SetColsCapacity(int capacity);
		void SetColsGrowStep(int step);
		void SetRowsCapacity(int capacity);
		void SetRowsGrowStep(int step);
		double* DATA_ARRAY(int colName, int rowIndex, int n, int *length);
	};
}
#endif