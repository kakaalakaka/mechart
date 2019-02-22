/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CSPLITLAYOUTDIVME_H__
#define __CSPLITLAYOUTDIVME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Button\\CButton.h"
#include "Div.h"
#include "CLayoutDiv.h"
#include "CTableLayoutDiv.h"

namespace MeLib
{
	class  CSplitLayoutDivMe : public CLayoutDivMe
	{
	protected:
		CControlMe *m_firstControl;
		CControlMe *m_secondControl;
		SizeTypeMe m_splitMode;
		float m_splitPercent;
		CButtonMe *m_splitter;
		ControlEvent m_splitterDraggingEvent;
		static void SplitterDragging(void *sender, void *pInvoke);
	public:
		CSplitLayoutDivMe();
		virtual ~CSplitLayoutDivMe();
		virtual CControlMe* GetFirstControl();
		virtual void SetFirstControl(CControlMe *firstControl);
		virtual CControlMe* GetSecondControl();
		virtual void SetSecondControl(CControlMe *secondControl);
		virtual SizeTypeMe GetSplitMode();
		virtual void SetSplitMode(SizeTypeMe splitMode);
		virtual CButtonMe* GetSplitter();
	public:
		virtual wstring GetControlType();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void CSplitLayoutDivMe::OnSplitterDragging();
		virtual void OnLoad();
		virtual bool OnResetLayout();
		virtual void Update();
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif