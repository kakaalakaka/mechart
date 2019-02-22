/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGRIDROWME_H__
#define __CGRIDROWME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CProperty.h"
#include "CGridCell.h"
#include "CGrid.h"

namespace MeLib
{
	class  CGridCellMe;
	class  CGridMe;

	class  CGridRowStyleMe
	{
	protected:
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
		_int64 m_hoveredBackColor;
		_int64 m_hoveredForeColor;
		_int64 m_selectedBackColor;
		_int64 m_selectedForeColor;
	public:
		CGridRowStyleMe();
		virtual ~CGridRowStyleMe();
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual _int64 GetHoveredBackColor();
		virtual void SetHoveredBackColor(_int64 hoveredBackColor);
		virtual _int64 GetHoveredForeColor();
		virtual void SetHoveredForeColor(_int64 hoveredForeColor);
		virtual _int64 GetSelectedBackColor();
		virtual void SetSelectedBackColor(_int64 selectedBackColor);
		virtual _int64 GetSelectedForeColor();
		virtual void SetSelectedForeColor(_int64 selectedForeColor);
	public:
		void Copy(CGridRowStyleMe *style);
	};

	class  CGridRowMe : public CPropertyMe
	{
	protected:
		bool m_allowEdit;
		RECT m_bounds;
		CControlMe *m_editButton;
		CGridMe *m_grid;
		int m_height;
		int m_horizontalOffset;
		int m_index;
		void *m_tag;
		bool m_visible;
		int m_visibleIndex;
	public:
		vector<CGridCellMe*> m_cells;
		int m_editState;
		CGridRowMe();
		virtual ~CGridRowMe();
		virtual bool AllowEdit();
		virtual void SetAllowEdit(bool allowEdit);
		virtual RECT GetBounds();
		virtual void SetBounds(RECT bounds);
		virtual CControlMe* GetEditButton();
		virtual void SetEditButton(CControlMe *editButton);
		virtual CGridMe* GetGrid();
		virtual void SetGrid(CGridMe *grid);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual int GetHorizontalOffset();
		virtual void SetHorizontalOffset(int horizontalOffset);
		virtual int GetIndex();
		virtual void SetIndex(int index);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
		virtual int GetVisibleIndex();
		virtual void SetVisibleIndex(int visibleIndex);
	public:
		void AddCell(int columnIndex, CGridCellMe *cell);
		void AddCell(const wstring& columnName, CGridCellMe *cell);
		void ClearCells();
		vector<CGridCellMe*> GetCells();
		CGridCellMe* GetCell(int columnIndex);
		CGridCellMe* GetCell(wstring columnName);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnAdd();
		virtual void OnPaint(CPaintMe *paint, const RECT& clipRect, bool isAlternate);
		virtual void OnPaintBorder(CPaintMe *paint, const RECT& clipRect, bool isAlternate);
		virtual void OnRemove();
		void RemoveCell(int columnIndex);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif