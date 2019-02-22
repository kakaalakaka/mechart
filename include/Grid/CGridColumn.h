/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CGRIDCOLUMNME_H__
#define __CGRIDCOLUMNME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CGridEnums.h"
#include "CGrid.h"
#include "..\\Button\\CButton.h"

namespace MeLib
{
	class  CGridMe;

	class  CGridColumnMe : public CButtonMe
	{
	protected:
		bool m_allowSort;
		bool m_allowResize;
		HorizontalAlignMe m_cellAlign;
		wstring m_columnType;
		bool m_frozen;
		CGridMe *m_grid;
		RECT m_headerRect;
		int m_index;
		GridColumnSortMode m_sortMode;
	protected:
		int m_beginWidth;
        POINT m_mouseDownPoint;
		int m_resizeState;
	public:
		CGridColumnMe();
		CGridColumnMe(const wstring& text);
		virtual ~CGridColumnMe();
		virtual bool AllowResize();
		virtual void SetAllowResize(bool allowResize);
		virtual bool AllowSort();
		virtual void SetAllowSort(bool allowSort);
		virtual HorizontalAlignMe GetCellAlign();
		virtual void SetCellAlign(HorizontalAlignMe cellAlign);
		virtual wstring GetColumnType();
		virtual void SetColumnType(wstring columnType);
		virtual bool IsFrozen();
		virtual void SetFrozen(bool frozen);
		virtual CGridMe* GetGrid();
		virtual void SetGrid(CGridMe *grid);
		virtual RECT GetHeaderRect();
		virtual void SetHeaderRect(RECT headerRect);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual GridColumnSortMode GetSortMode();
		virtual void SetSortMode(GridColumnSortMode sortMode);
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual bool OnDragBegin();
		virtual void OnDragging();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif