/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CCHECKBOXME_H__
#define __CCHECKBOXME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "CButton.h"

namespace MeLib
{
	class  CCheckBoxMe : public CButtonMe
	{
	protected:
		HorizontalAlignMe m_buttonAlign;
		_int64 m_buttonBackColor;
		_int64 m_buttonBorderColor;
		SIZE m_buttonSize;
		bool m_checked;
		wstring m_checkedBackImage;
		wstring m_checkHoveredBackImage;
		wstring m_checkPushedBackImage;
		wstring m_disableCheckedBackImage;
	protected:
		virtual _int64 GetPaintingBackColor();
		virtual _int64 GetPaintingButtonBackColor();
		virtual _int64 GetPaintingButtonBorderColor();
		virtual wstring GetPaintingBackImage();
	public:
		CCheckBoxMe();
		virtual ~CCheckBoxMe();
		virtual HorizontalAlignMe GetButtonAlign();
		virtual void SetButtonAlign(HorizontalAlignMe buttonAlign);
		virtual _int64 GetButtonBackColor();
		virtual void SetButtonBackColor(_int64 buttonBackColor);
		virtual _int64 GetButtonBorderColor();
		virtual void SetButtonBorderColor(_int64 buttonBorderColor);
		virtual SIZE GetButtonSize();
		virtual void SetButtonSize(SIZE buttonSize);
		virtual bool IsChecked();
		virtual void SetChecked(bool checked);
		virtual wstring GetCheckedBackImage();
		virtual void SetCheckedBackImage(const wstring& checkedBackImage);
		virtual wstring GetCheckHoveredBackImage();
		virtual void SetCheckHoveredBackImage(const wstring& checkHoveredBackImage);
		virtual wstring GetCheckPushedBackImage();
		virtual void SetCheckPushedBackImage(const wstring& checkPushedBackImage);
		virtual wstring GetDisableCheckedBackImage();
		virtual void SetDisableCheckedBackImage(const wstring& disableCheckedBackImage);
	public:
		virtual wstring GetControlType();
		virtual vector<wstring> GetEventNames();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual void OnCheckedChanged();
		virtual void OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintBackground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintCheckButton(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif