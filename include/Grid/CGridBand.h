/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGRIDBANDME_H__
#define __CGRIDBANDME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CGridEnums.h"
#include "CBandedGrid.h"
#include "CBandedGridColumn.h"
#include "..\\Button\\CButton.h"

namespace MeLib
{
	class  CBandedGridMe;
	class  CBandedGridColumnMe;

	class  CGridBandMe : public CButtonMe
	{
	protected:
		bool m_allowResize;
		CBandedGridMe *m_grid;
		int m_index;
		CGridBandMe *m_parentBand;
	protected:
		int m_beginWidth;
        POINT m_mouseDownPoint;
		int m_resizeState;
	public:
		vector<CGridBandMe*> m_bands;
		vector<CBandedGridColumnMe*> m_columns;
		CGridBandMe();
		virtual ~CGridBandMe();
		virtual bool AllowResize();
		virtual void SetAllowResize(bool allowResize);
		virtual CBandedGridMe* GetGrid();
		virtual void SetGrid(CBandedGridMe *grid);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual CGridBandMe* GetParentBand();
		virtual void SetParentBand(CGridBandMe *parentBand);
	public:
		void AddBand(CGridBandMe *band);
		void AddColumn(CBandedGridColumnMe *column);
		void ClearBands();
		void ClearColumns();
		vector<CBandedGridColumnMe*> GetAllChildColumns();
		vector<CGridBandMe*> GetBands();
		vector<CBandedGridColumnMe*> GetColumns();
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertBand(int index, CGridBandMe *band);
		void InsertColumn(int index, CBandedGridColumnMe *column);
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void RemoveBand(CGridBandMe *band);
		void RemoveColumn(CBandedGridColumnMe *column);
		virtual void ResetHeaderLayout();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif