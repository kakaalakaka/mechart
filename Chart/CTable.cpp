#include "..\\stdafx.h"
#include "..\\include\\Chart\\CTable.h"

namespace MeLib
{
	CRowMe::CRowMe(CTableMe *table)
	{
		m_table = table;
		LONGLONG ForDouble = 0x7FF8000000000000L;
		NaN = *(double *)&ForDouble;
	}

	CRowMe::CRowMe(CTableMe *table, int capacity, int step)
	{
		m_table = table;
		m_values.set_capacity(capacity);
		m_values.set_step(step);
		LONGLONG ForDouble = 0x7FF8000000000000L;
		NaN = *(double *)&ForDouble;
	}

	CRowMe::CRowMe(CTableMe *table, double *ary, int size)
	{
		m_table = table;
		m_values.addranges(ary, size);
		LONGLONG ForDouble = 0x7FF8000000000000L;
		NaN = *(double *)&ForDouble;
	}

	CRowMe::~CRowMe()
	{
		m_values.clear();
	}
	
	void CRowMe::FillEmpty(int columns)
	{
        int num = m_values.size();
        if (num >= 0)
        {
            for (int i = num; i < columns; i++)
            {
				m_values.insert(i, NaN);
            }
        }
	}

	double CRowMe::Get(int index)
	{
		int num = m_values.size();		
	    if (index >= 0 && index < num)
        {
            return m_values.get(index);
        }
        return NaN;
	}

	void CRowMe::Remove(int index)
	{
	    if (index != -1)
        {
            m_values.remove_at(index);
        }
	}

	void CRowMe::Set(int index, double value)
	{
		int num = m_values.size();
		if (index >= 0 && index < num)
		{
			m_values.set(index, value);
		}
	}
	//////////////////////////////////////////////////////////////////////////////////

	CTableMe::CTableMe()
	{
		m_colsCapacity = 4;
		m_colsStep = 4;
		m_autoField = 10000;
		LONGLONG ForDouble = 0x7FF8000000000000L;
		NaN = *(double *)&ForDouble;
	}

	CTableMe::~CTableMe()
	{
		m_keys.clear();
		CListMe<int*> m_columns;
		int size = m_columns.size();
		for(int i = 0; i < size; i++)
		{
			delete m_columns.get(i);
			m_columns.set(i, 0);
		}
		m_columns.clear();
		m_rows.clear();
	}

	CRowMe* CTableMe::AddKey(double num)
	{
		CRowMe* newRow = 0;
		if (m_keys.size() == 0)
        {
            m_keys.push_back(num);
            newRow = new CRowMe(this, m_colsCapacity, m_colsStep);
            m_rows.push_back(newRow);
        }
        else
        {
            int index = 0;
            int end = m_keys.size() - 1;
            for (int i = end - index; i > 1; i = end - index)
            {
                int middle = index + (i / 2);
                double midKey = m_keys.get(middle);
                if (midKey > num)
                {
                    end = middle;
                }
                else if (midKey < num)
                {
                    index = middle;
                }
            }
            if (num < m_keys.get(index))
            {
                m_keys.insert(index, num);
                newRow = new CRowMe(this, m_colsCapacity, m_colsStep);
                m_rows.insert(index, newRow);
            }
            else if (num > m_keys.get(end))
            {
                m_keys.insert(end + 1, num);
                newRow = new CRowMe(this, m_colsCapacity, m_colsStep);
                m_rows.insert(end + 1, newRow);
            }
            else
            {
                m_keys.insert(index + 1, num);
                newRow = new CRowMe(this, m_colsCapacity, m_colsStep);
                m_rows.insert(index + 1, newRow);
            }
        }
		return newRow;
	}

	void CTableMe::FillEmpty()
	{
		int columns = m_columns.size();
        for (int i = 0; i < m_rows.size(); i++)
        {
            m_rows.get(i)->FillEmpty(columns);
        }
	}

	int CTableMe::AUTOFIELD()
	{
		return ++m_autoField;
	}

	void CTableMe::AddColumn(int colName)
	{
		int* numArray = new int[2];
		numArray[0] = colName;
		numArray[1] = m_columns.size();
        if (m_columns.size() == 0)
        {
            m_columns.push_back(numArray);
        }
        else
        {
            int index = 0;
            int end = m_columns.size() - 1;
            for (int i = end - index; i > 1; i = end - index)
            {
                int mid = index + (i / 2);
                int midColumn = m_columns.get(mid)[0];
                if (midColumn > colName)
                {
                    end = mid;
                }
                else if (midColumn < colName)
                {
                    index = mid;
                }
            }
            if (colName < m_columns.get(index)[0])
            {
                m_columns.insert(index, numArray);
                FillEmpty();
            }
            else if (colName > m_columns.get(end)[0])
            {
                m_columns.insert(end + 1, numArray);
                FillEmpty();
            }
            else
            {
                m_columns.insert(index + 1, numArray);
                FillEmpty();
            }
        }
	}

	void CTableMe::AddRow(double pk, double *ary, int size)
	{	
        m_keys.push_back(pk);
        CRowMe* row = new CRowMe(this, ary, size);
        m_rows.push_back(row);
	}

	int CTableMe::ColumnsCount()
	{
		return m_columns.size();
	}

	void CTableMe::Clear()
	{
		if (m_keys.size() != 0)
        {
            m_keys.clear();
        }
        if (m_rows.size() != 0)
        {
            for (int i = 0; i < m_rows.size(); i++)
            {
                CRowMe *row = m_rows.get(i);
                if (row)
                {
					delete row;
                }
				row = 0;
            }
            m_rows.clear();
        }
	}

	int CTableMe::GetColumnIndex(int colName)
	{
		if (colName == CTableMe::NULLFIELD() || m_columns.size() == 0)
        {
            return -1;
        }
        int index = 0;
        int end = m_columns.size() - 1;
        int length = end - index;
        while (length >= 0)
        {
            int mid = index + (length / 2);
            int* numArray = m_columns.get(mid);
            if (numArray[0] == colName)
            {
                return numArray[1];
            }
            if (mid == index || mid == end)
            {
                int* numArray2 = m_columns.get(end);
                if (numArray2[0] == colName)
                {
                    return numArray2[1];
                }
                int* numArray3 = m_columns.get(index);
                if (numArray3[0] == colName)
                {
                    return numArray3[1];
                }
                return -1;
            }
            if (numArray[0] > colName)
            {
                end = mid;
            }
            else if (numArray[0] < colName)
            {
                index = mid;
            }
            length = end - index;
        }
        return -1;
	}

	int CTableMe::GetRowIndex(double key)
	{
		if (m_keys.size() == 0)
        {
            return -1;
        }
        int index = 0;
        int emd = m_keys.size() - 1;
        int length = emd - index;
        int ret = -1;
        while (length >= 0)
        {
            int mid = index + (length / 2);
            double midKey = m_keys.get(mid);
            if (midKey == key)
            {
                return mid;
            }
            if (mid == index || mid == emd)
            {
                if (m_keys.get(emd) == key)
                {
                    return emd;
                }
                if (m_keys.get(index) == key)
                {
                    ret = index;
                }
                return ret;
            }
            if (midKey > key)
            {
                emd = mid;
            }
            else if (midKey < key)
            {
                index = mid;
            }
            length = emd - index;
        }
        return ret;
	}

	double CTableMe::GetXValue(int rowIndex)
	{
		return m_keys.get(rowIndex);
	}

	double CTableMe::Get(double pk, int colName)
	{
        int rowIndex = GetRowIndex(pk);
		if(rowIndex < 0 || rowIndex >= m_rows.size())
		{
			return CTableMe::NaN;
		}
        int columnIndex = GetColumnIndex(colName);
        return m_rows.get(rowIndex)->Get(columnIndex);
	}

	double CTableMe::Get2(int rowIndex, int colName)
	{
		if (rowIndex >= 0 && rowIndex < m_rows.size())
        {
            int columnIndex = GetColumnIndex(colName);
            return m_rows.get(rowIndex)->Get(columnIndex);
		}
		return CTableMe::NaN;
	}

	double CTableMe::Get3(int rowIndex, int colIndex)
	{
        if (rowIndex >= 0 && rowIndex < m_rows.size())
        {
            return m_rows.get(rowIndex)->Get(colIndex);
		}
		return CTableMe::NaN;
	}

	void CTableMe::RemoveAt(int rowIndex)
	{
        m_keys.remove_at(rowIndex);
		CRowMe* row = m_rows.get(rowIndex);
		if(row)
		{
			delete row;
			row = 0;
		}
        m_rows.remove_at(rowIndex);
	}

	void CTableMe::RemoveColumn(int name)
	{
		int columnIndex = GetColumnIndex(name);
        if (columnIndex != -1)
        {
            int size = m_columns.size();
            int removeIndex = -1;
			int* numArray = 0;
            for (int i = 0; i < size; i++)
            {
                numArray = m_columns.get(i);
                int first = numArray[0];
                int second = numArray[1];
                if (first == name)
                {
                    removeIndex = i;
                }
                else if (second > columnIndex)
                {
					int *arrayNew = new int[2];
					arrayNew[0] = first;
					arrayNew[1] = second - 1;
                    m_columns.set(i, arrayNew);
					delete numArray;
					numArray = 0;
                }
            }
			if(numArray)
			{
				delete numArray;
				numArray = 0;
			}
            m_columns.remove_at(removeIndex);
            for (int j = 0; j < m_rows.size(); j++)
            {
                m_rows.get(j)->Remove(columnIndex);
                m_rows.get(j)->FillEmpty(m_columns.size());
            }
        }
	}

	int CTableMe::RowsCount()
	{
		return m_keys.size();
	}

	void CTableMe::Set(double pk, int colName, double value)
	{
		CRowMe* newRow = 0;
        int rowIndex = GetRowIndex(pk);
        if (rowIndex == -1)
        {
            newRow = AddKey(pk);
            newRow->FillEmpty(m_columns.size());
        }
        else
        {
            newRow = m_rows.get(rowIndex);
        }
        int columnIndex = GetColumnIndex(colName);
        newRow->Set(columnIndex, value);
	}

	void CTableMe::Set2(int rowIndex, int colName, double value)
	{
        int columnIndex = GetColumnIndex(colName);
        m_rows.get(rowIndex)->Set(columnIndex, value);
	}

	void CTableMe::Set3(int rowIndex, int colIndex, double value)
	{
		m_rows.get(rowIndex)->Set(colIndex, value);
	}

	void CTableMe::SetColsCapacity(int capacity)
	{
		m_colsCapacity = capacity;
	}

	void CTableMe::SetColsGrowStep(int step)
	{
		m_colsStep = step;
	}

	void CTableMe::SetRowsCapacity(int capacity)
	{
		m_keys.set_capacity(capacity);
        m_rows.set_capacity(capacity);
	}

	void CTableMe::SetRowsGrowStep(int step)
	{
		m_keys.set_step(step);
		m_rows.set_step(step);
	}

	double* CTableMe::DATA_ARRAY(int field, int index, int n, int *length)
	{
		if (index < 0)
        {
            return new double[0];
        }
        int arraylength = n;
        int start = 0;
        if (index < n - 1)
        {
            arraylength = index + 1;
        }
        else
        {
            start = index - n + 1;
        }
        if (arraylength == -1)
        {
            return new double[0];
        }
        double* numArray = new double[arraylength];
        int columnIndex = GetColumnIndex(field);
        for (int i = start; i <= index; i++)
        {
            numArray[i - start] = Get3(i, columnIndex);
        }
		*length = arraylength;
        return numArray;
	}
}