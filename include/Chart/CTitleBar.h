/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CTITLEBARME_H__
#define __CTITLEBARME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CPaint.h"
#include "CTable.h"
#include "CEnums.h"
#include "CList.h"
#include "CDiv.h"

namespace MeLib
{
	class  CDivMe;

	class  CTitleMe : public CPropertyMe
	{
	protected:
		int m_digit;
		int m_fieldName;
		wstring m_fieldText;
		TextMode m_fieldTextMode;
		wstring m_fieldTextSeparator;
		_int64 m_textColor;
		bool m_visible;
	public:
		CTitleMe(int fieldName, const wstring& fieldText, _int64 color, int digit, bool visible);
		virtual int GetDigit();
		virtual void SetDigit(int digit);
		virtual int GetFieldName();
		virtual void SetFieldName(int fieldName);
		virtual wstring GetFieldText();
		virtual void SetFieldText(const wstring& fieldText);
		virtual TextMode GetFieldTextMode();
		virtual void SetFieldTextMode(TextMode fieldTextMode);
		virtual wstring GetFieldTextSeparator();
		virtual void SetFieldTextSeparator(const wstring& fieldTextSeparator);
		virtual _int64 GetTextColor();
		virtual void SetTextColor(_int64 textColor);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};

	class  CTitleBarMe : public CPropertyMe
	{
	protected:
		bool m_allowUserPaint;
		FONT *m_font;
		_int64 m_foreColor;
		int m_height;
		int m_maxLine;
		bool m_showUnderLine;
		wstring m_text;
		_int64 m_underLineColor;
		bool m_visible;
	public:
		CTitleBarMe();
		virtual ~CTitleBarMe();
		vector<CTitleMe*> Titles;
		virtual bool AllowUserPaint();
		virtual void SetAllowUserPaint(bool allowUserPaint);
		virtual FONT* GetFont();
		virtual void SetFont(FONT *font);
		virtual _int64 GetForeColor();
		virtual void SetForeColor(_int64 foreColor);
		virtual int GetHeight();
		virtual void SetHeight(int height);
		virtual int GetMaxLine();
		virtual void SetMaxLine(int maxLine);
		virtual bool ShowUnderLine();
		virtual void SetShowUnderLine(bool showUnderLine);
		virtual wstring GetText();
		virtual void SetText(const wstring& text);
		virtual _int64 GetUnderLineColor();
		virtual void SetUnderLineColor(_int64 underLineColor);
		virtual bool IsVisible();
		virtual void SetVisible(bool visible);
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnPaint(CPaintMe *paint, CDivMe *div, const RECT& rect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}
#endif