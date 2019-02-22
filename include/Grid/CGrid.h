/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGRIDME_H__
#define __CGRIDME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CGridColumn.h"
#include "CGridRow.h"
#include "CGridCell.h"
#include "..\\ScrollBar\\CHScrollBar.h"
#include "..\\ScrollBar\\CVScrollBar.h"
#include "..\\Layout\\Div.h"
#include "..\\TextBox\\CTextBox.h"

namespace MeLib
{
	class  CGridCellMe;
	class  CGridColumnMe;
	class  CGridRowMe;
	class  CGridRowStyleMe;
	
	typedef  void (*GridCellEvent) (void*, CGridCellMe*, void*);

	typedef  void (*GridCellMouseEvent)(void*, CGridCellMe*, const POINT&, MouseButtonsMe, int, int, void*);

	class  CGridRowCompareMe
	{
	public:
		int m_columnIndex;
		int m_type;
	public:
		CGridRowCompareMe();
		virtual ~CGridRowCompareMe();
		bool operator()(CGridRowMe *x, CGridRowMe *y);
	};

	class  CGridMe;

	class  CGridSortMe
	{
	public:
		CGridSortMe();
		virtual ~CGridSortMe();
	public:
		virtual void SortColumn(CGridMe *grid, CGridColumnMe *column, GridColumnSortMode sortMode);
	};

	class  CGridMe:public DivMe
	{
	private:
		int m_timerID;
	protected:
		ControlEvent m_editTextBoxLostFocusEvent;
		ControlKeyEvent m_editTextBoxKeyDownEvent;
	protected:
		bool m_allowDragRow;
		bool m_allowHoveredRow;
		CGridRowStyleMe *m_alternateRowStyle;
		GridCellEditMode m_cellEditMode;
		CGridCellMe *m_editingCell;
		CTextBoxMe *m_editTextBox;
		_int64 m_gridLineColor;
		bool m_hasUnVisibleRow;
		bool m_headerVisible;
		int m_headerHeight;
		int m_horizontalOffset;
		CGridCellMe *m_hoveredCell;
		CGridRowMe *m_hoveredRow;
		POINT m_mouseDownPoint;
		bool m_multiSelect;
		CGridRowStyleMe *m_rowStyle;
		GridSelectionMode m_selectionMode;
		CGridSortMe *m_sort;
		bool m_useAnimation;
		int m_verticalOffset;
		void CallCellEvents(int eventID, CGridCellMe *cell);
		void CallCellMouseEvents(int eventID, CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void MouseEvent(const POINT& mp, MouseButtonsMe button, int clicks, int delta, int state);
		static void EditTextBoxLostFocus(void *sender, void *pInvoke);
		static void EditTextBoxKeyDown(void *sender, char key, void *pInvoke);
	public:
		bool m_lockUpdate;
		vector<CGridCellMe*> m_selectedCells;
		vector<CGridColumnMe*> m_selectedColumns;
		vector<CGridRowMe*> m_selectedRows;
		int GetAllVisibleColumnsWidth();
		int GetAllVisibleRowsHeight();
	public:
		vector<CGridRowMe*> m_animateAddRows;
		vector<CGridRowMe*> m_animateRemoveRows;
		vector<CGridColumnMe*> m_columns;
		CGridRowMe *m_editingRow;
		vector<CGridRowMe*> m_rows;
		CGridMe();
		virtual ~CGridMe();
		virtual bool AllowDragRow();
		virtual void SetAllowDragRow(bool allowDragRow);
		virtual bool AllowHoveredRow();
		virtual void SetAllowHoveredRow(bool allowHoveredRow);
		virtual CGridRowStyleMe* GetAlternateRowStyle();
		virtual void SetAlternateRowStyle(CGridRowStyleMe *alternateRowStyle);
		virtual GridCellEditMode GetCellEditMode();
		virtual void SetCellEditMode(GridCellEditMode cellEditMode);
		virtual CTextBoxMe* GetEditTextBox();
		virtual _int64 GetGridLineColor();
		virtual void SetGridLineColor(_int64 gridLineColor);
		virtual bool IsHeaderVisible();
		virtual void SetHeaderVisible(bool headerVisible);
		virtual int GetHeaderHeight();
		virtual void SetHeaderHeight(int headerHeight);
		virtual int GetHorizontalOffset();
		virtual void SetHorizontalOffset(int horizontalOffset);
		virtual CGridCellMe* GetHoveredCell();
		virtual CGridRowMe* GetHoveredRow();
		virtual bool IsMultiSelect();
		virtual void SetMultiSelect(bool multiSelect);
		virtual CGridRowStyleMe* GetRowStyle();
		virtual void SetRowStyle(CGridRowStyleMe *rowStyle);
		virtual vector<CGridCellMe*> GetSelectedCells();
		virtual void SetSelectedCells(vector<CGridCellMe*> selectedCells);
		virtual vector<CGridColumnMe*> GetSelectedColumns();
		virtual void SetSelectedColumns(vector<CGridColumnMe*> selectedColumns);
		virtual vector<CGridRowMe*> GetSelectedRows();
		virtual void SetSelectedRows(vector<CGridRowMe*> selectedRows);
		virtual GridSelectionMode GetSelectionMode();
		virtual void SetSelectionMode(GridSelectionMode selectionMode);
		virtual CGridSortMe* GetSort();
		virtual void SetSort(CGridSortMe *sort);
		virtual bool UseAnimation();
		virtual void SetUseAnimation(bool useAnimation);
		virtual int GetVerticalOffset();
		virtual void SetVerticalOffset(int verticalOffset);
	public:
		virtual void AddColumn(CGridColumnMe *column);
		void AddRow(CGridRowMe *row);
		void AnimateAddRow(CGridRowMe *row);
		void AnimateRemoveRow(CGridRowMe *row);
		void BeginUpdate();
		void Clear();
		virtual void ClearColumns();
		void ClearRows();
		void EndUpdate();
		CGridColumnMe* GetColumn(int columnIndex);
		CGridColumnMe* GetColumn(const wstring& columnName);
		vector<CGridColumnMe*> GetColumns();
		virtual int GetContentHeight();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		virtual POINT GetDisplayOffset();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		CGridRowMe* GetRow(const POINT& mp);
		CGridRowMe* GetRow(int rowIndex);
		vector<CGridRowMe*> GetRows();
		void GetVisibleRowsIndex(double visiblePercent, int *firstVisibleRowIndex, int *lastVisibleRowIndex);
		void InsertRow(int index, CGridRowMe *row);
		bool IsRowVisible(CGridRowMe *row, double visiblePercent);
		void MoveRow(int oldIndex, int newIndex);
		virtual void OnCellClick(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellEditBegin(CGridCellMe *cell);
		virtual void OnCellEditEnd(CGridCellMe *cell);
		virtual void OnCellMouseDown(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseEnter(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseLeave(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseMove(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseUp(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnKeyDown(char key);
		virtual void OnLoad();
		virtual void OnLostFocus();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseLeave(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintEditTextBox(CGridCellMe *cell, CPaintMe *paint, const RECT& rect, const RECT& clipRect);
		virtual void OnRowEditBegin(CGridRowMe *row);
		virtual void OnRowEditEnd();
		virtual void OnSelectedCellsChanged();
		virtual void OnSelectedColumnsChanged();
		virtual void OnSelectedRowsChanged();
		virtual void OnSetEmptyClipRegion();
		virtual void OnTimer(int timerID);
		virtual void OnVisibleChanged();
		virtual void RemoveColumn(CGridColumnMe *column);
		void RemoveRow(CGridRowMe *row);
		virtual void ResetHeaderLayout();
		CGridRowMe* SelectFrontRow();
		CGridRowMe* SelectNextRow();
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void SortColumn(CGridMe *grid, CGridColumnMe *column, GridColumnSortMode sortMode);
		virtual void Update();
		void UpdateSortColumn();
	};
}

#endif