/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGRIDCELLME_H__
#define __CGRIDCELLME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CProperty.h"
#include "CGridColumn.h"
#include "CGridRow.h"
#include "CGrid.h"

namespace MeLib
{
	class  CGridColumnMe;
	class  CGridRowMe;
	class  CGridMe;

	class  GridCellStyle
	{
	protected:
		HorizontalAlignMe m_align;
		bool m_autoEllipsis;
		_int64 m_backColor;
		FONT *m_font;
		_int64 m_foreColor;
	public:
		GridCellStyle();
		virtual ~GridCellStyle();
		virtual HorizontalAlignMe GetAlign();
		virtual void SetAlign(HorizontalAlignMe align);
		virtual bool AutoEllipsis();
		virtual void SetAutoEllipsis(bool autoEllipsis);
		virtual _int64 GetBackColor();
		virtual void SetBackColor(_int64 backColor);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
	public:
		void Copy(GridCellStyle *style);
	};

	class  CGridCellMe : public CPropertyMe
	{
	protected:
		bool m_allowEdit;
		int m_colSpan;
		CGridColumnMe *m_column;
		CGridMe *m_grid;
		wstring m_name;
		CGridRowMe *m_row;
		int m_rowSpan;
		GridCellStyle *m_style;
		void *m_tag;
	public:
		CGridCellMe();
		virtual ~CGridCellMe();
		virtual bool AllowEdit();
		virtual void SetAllowEdit(bool allowEdit);
		virtual int GetColSpan();
		virtual void SetColSpan(int colSpan);
		virtual CGridColumnMe* GetColumn();
		virtual void SetColumn(CGridColumnMe *column);
		virtual CGridMe* GetGrid();
		virtual void SetGrid(CGridMe *grid);
		virtual wstring GetName();
		virtual void SetName(const wstring& name);
		virtual CGridRowMe* GetRow();
		virtual void SetRow(CGridRowMe *row);
		virtual int GetRowSpan();
		virtual void SetRowSpan(int rowSpan);
		virtual GridCellStyle* GetStyle();
		virtual void SetStyle(GridCellStyle *style);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual wstring GetText();
		virtual void SetText(const wstring& text);
	public:
		virtual int CompareTo(CGridCellMe *cell);
		virtual bool GetBool();
		virtual double GetDouble();
		virtual float GetFloat();
		virtual int GetInt();
		virtual _int64 GetLong();
		virtual wstring GetPaintText();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual wstring GetString();
		virtual void OnAdd();
		virtual void OnPaint(CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnRemove();
        virtual void SetBool(bool value);
        virtual void SetDouble(double value);
        virtual void SetFloat(float value);
        virtual void SetInt(int value);
        virtual void SetLong(_int64 value);
		virtual void SetProperty(const wstring& name, const wstring& value);
        virtual void SetString(const wstring& value);
	};

	class  CGridControlCellMe : public CGridCellMe
	{
	protected:
		CControlMe *m_control;
		ControlMouseEvent m_mouseDownEvent;
		ControlMouseEvent m_mouseMoveEvent;
		ControlMouseEvent m_mouseUpEvent;
		ControlMouseEvent m_mouseWheelEvent;
	protected:
		static void ControlMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ControlMouseMove(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ControlMouseUp(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
		static void ControlMouseWheel(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke);
	public:
		CGridControlCellMe();
		virtual ~CGridControlCellMe();
		CControlMe* GetControl();
		void SetControl(CControlMe *control);
		virtual wstring GetString();
		virtual wstring GetPaintText();
		virtual void OnAdd();
		virtual void OnControlMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnControlMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnControlMouseUp(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnControlMouseWheel(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaint(CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnPaintControl(CPaintMe *paint, const RECT& rect, const RECT& clipRect);
		virtual void OnRemove();
		virtual void SetString(const wstring& value);
	};
}

#endif