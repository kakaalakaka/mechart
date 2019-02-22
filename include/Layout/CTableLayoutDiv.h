/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CTABLELAYOUTDIVME_H__
#define __CTABLELAYOUTDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "Div.h"

namespace MeLib
{	
	typedef enum  SizeTypeMe
	{
		SizeTypeMe_AbsoluteSize,
		SizeTypeMe_AutoFill,
		SizeTypeMe_PercentSize
	};

	class  CColumnStyleMe : public CPropertyMe
	{
	protected:
		SizeTypeMe m_sizeType;
		float m_width;
	public:
		CColumnStyleMe(SizeTypeMe sizeType, float width);
		virtual ~CColumnStyleMe();
		virtual SizeTypeMe GetSizeType();
		virtual void SetSizeTypeMe(SizeTypeMe  sizeType);
		virtual float GetWidth();
		virtual void SetWidth(float width);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};

	class  CRowStyleMe : public CPropertyMe
	{
	protected:
		float m_height;
		SizeTypeMe m_sizeType;
	public:
		CRowStyleMe(SizeTypeMe sizeType, float height);
		virtual ~CRowStyleMe();
		virtual float GetHeight();
		virtual void SetHeight(float height);
		virtual SizeTypeMe GetSizeType();
		virtual void SetSizeTypeMe(SizeTypeMe  sizeType);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};

	class  CTableLayoutDivMe : public DivMe
	{
	protected:
		vector<int> m_columns;
		int m_columnsCount;
		vector<int> m_rows;
		int m_rowsCount;
		vector<CControlMe*> m_tableControls;
	public:
		vector<CColumnStyleMe> m_columnStyles;
		vector<CRowStyleMe> m_rowStyles;
		CTableLayoutDivMe();
		virtual ~CTableLayoutDivMe();
		virtual int GetColumnsCount();
		virtual void SetColumnsCount(int columnsCount);
		virtual int GetRowsCount();
		virtual void SetRowsCount(int rowsCount);
	public:
		virtual void AddControl(CControlMe *control);
		virtual void AddControl(CControlMe *control, int column, int row);
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual bool OnResetLayout();
		virtual void RemoveControl(CControlMe *control);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void Update();
	};
}

#endif