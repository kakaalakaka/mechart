/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CLISTME_H__
#define __CLISTME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	template <class numtype>
	class  CListMe
	{
	public:
		numtype *m_ary;
		int m_size;
		int m_capacity;
		int m_step;
	public:
		CListMe()
		{
			m_size = 0;
			m_ary = 0;
			m_capacity = 4;
			m_step = 4;
		}

		CListMe(int capacity)
		{
			m_size = 0;
            m_ary = 0;
            m_capacity = capacity;
            m_step = 4;
		}

		void addranges(numtype *ary, int size)
		{
            m_ary = ary;
			m_size = size;
            m_capacity = m_size;
            m_step = 4;
		}

		int capacity()
		{
			return m_capacity;
		}

		void clear()
		{
			if(m_ary)
			{
				VirtualFree(m_ary, 0, MEM_RELEASE);
				m_ary = 0;
			}
			m_size = 0;
		}

		numtype get(int index)
		{
			return m_ary[index];
		}

		void insert(int index, numtype value)
		{
			m_size += 1;
			if(m_size == 1537)
			{
				int a = 0;
				int b = 0;
			}
			if(!m_ary)
			{
				m_ary = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE); 
			}
			else
			{
				if(m_size > m_capacity)
				{
					m_capacity += m_step;
					numtype *newAry = (numtype*)VirtualAlloc(m_ary, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
					if(newAry)
					{
						m_ary = newAry;
					}
					else
					{
						newAry = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
						MoveMemory(newAry, m_ary, sizeof(numtype) * (m_size - 1));
						VirtualFree(m_ary, 0, MEM_RELEASE);
						m_ary = newAry;
					}
				}
				numtype last = 0;
				for(int i = index; i < m_size; i++)
				{
					if(i == index)
					{
						last = m_ary[i];
					}
					else if(i > index)
					{
						numtype temp = m_ary[i];
						m_ary[i] = last;
						last = temp;
					}
				}
			}
			m_ary[index] = value;
		}

		void push_back(numtype value)
		{
			m_size += 1;
			if(!m_ary)
			{
				m_ary = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE); 
			}
			else
			{
				if(m_size > m_capacity)
				{
					m_capacity += m_step;
					numtype *newAry = (numtype*)VirtualAlloc(m_ary, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
					if(newAry)
					{
						m_ary = newAry;
					}
					else
					{
						newAry = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
						MoveMemory(newAry, m_ary, sizeof(numtype) * (m_size - 1));
						VirtualFree(m_ary, 0, MEM_RELEASE);
						m_ary = newAry;
					}
				}
			}
			m_ary[m_size - 1] = value;
		}

		void remove_at(int index)
		{
			m_size -= 1;
			for(int i = index;i < m_size; i++)
			{
				m_ary[i] = m_ary[i + 1];
			}
			if(m_capacity - m_size > m_step)
			{
				m_capacity -= m_step;
				if(m_capacity > 0)
				{
					numtype *newAry = (numtype*)VirtualAlloc(m_ary, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
					if(newAry)
					{
						m_ary = newAry;
					}
					else
					{
						newAry = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
						MoveMemory(newAry, m_ary, sizeof(numtype) * m_size);
						VirtualFree(m_ary, 0, MEM_RELEASE);
						m_ary = newAry;
					}
				}
				else
				{
					if(m_ary)
					{
						VirtualFree(m_ary, 0, MEM_RELEASE);
						m_ary = 0;
					}
				}
			}
		}

		void set(int index,numtype value)
		{
			m_ary[index] = value;
		}

		void set_capacity(int capacity)
		{
			m_capacity = capacity;
			if(m_ary)
			{
				numtype *newAry = (numtype*)VirtualAlloc(m_ary, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
				if(newAry)
				{
					m_ary = newAry;
				}
				else
				{
					newAry = (numtype*)VirtualAlloc(0, sizeof(numtype) * m_capacity, MEM_COMMIT, PAGE_READWRITE);
					MoveMemory(newAry, m_ary, sizeof(numtype) * (m_size - 1));
					VirtualFree(m_ary, 0, MEM_RELEASE);
					m_ary = newAry;
				}
			}
		}

		void set_step(int step)
		{
			m_step = step;
		}

		int size()
		{
			return m_size;
		}

		virtual ~CListMe()
		{
			clear();
		}
	};
}
#endif