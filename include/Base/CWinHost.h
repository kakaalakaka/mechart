/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CWINHOSTME_H__
#define __CWINHOSTME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CControl.h"
#include "CStr.h"
#include "CPaint.h"
#include "CGdiPaint.h"
#include "CGdiPlusPaint.h"
#include "CNativeBase.h"
#include "CControlHost.h"

namespace MeLib
{
	class  CControlMe;
	class  CNativeBaseMe;

	class  CWinHostMe : public CControlHostMe
	{
	protected:
		CRITICAL_SECTION _csLock;
		bool m_allowOperate;
		bool m_allowPartialPaint;
		HIMC m_hImc;
		HWND m_hWnd;
		int m_invokeSerialID;
		map<int, void*> m_invokeArgs;
		map<int, CControlMe*> m_invokeControls;
		CNativeBaseMe *m_native;
		int m_pInvokeMsgID;
		CControlMe *m_toolTip;
	protected:
		SIZE GetClientSize();
	public:
		CWinHostMe();
		virtual ~CWinHostMe();
		HWND GetHWnd();
		void SetHWnd(HWND hWnd);
		virtual CNativeBaseMe* GetNative();
		virtual void SetNative(CNativeBaseMe *native);
		int GetPInvokeMsgID();
		void SetPInvokeMsgID(int pInvokeMsgID);
		CControlMe* GetToolTip();
		void SetToolTip(CControlMe *toolTip);
	public:
		virtual void ActiveMirror();
		virtual bool AllowOperate();
		virtual bool AllowPartialPaint();
		virtual void BeginInvoke(CControlMe *control, void *args);
		virtual void Copy(string text);
		virtual CControlMe* CreateInternalControl(CControlMe *parent, const wstring& clsid);
		static string GetAppPath();
		virtual CursorsMe GetCursor();
		virtual int GetIntersectRect(LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect);
        virtual POINT GetMousePoint();
        virtual SIZE GetSize();
		virtual int GetUnionRect(LPRECT lpDestRect, const RECT *lpSrc1Rect, const RECT *lpSrc2Rect);
		void Lock();
		virtual void Invalidate();
        virtual void Invalidate(const RECT& rect);
		virtual void Invoke(CControlMe *control, void *args);
		virtual bool IsKeyPress(char key);
		void OnInvoke(int invokeSerialID);
		int OnMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		void OnPaint(HDC hDC, const RECT& rect);
		virtual string Paste();
		virtual void SetAllowOperate(bool allowOperate);
		virtual void SetAllowPartialPaint(bool allowPartialPaint);
        virtual void SetCursor(CursorsMe cursor);
		virtual void ShowToolTip(void *sender, const wstring& text, const POINT& mp);
        virtual void StartTimer(int timerID, int interval);
        virtual void StopTimer(int timerID);
		void UnLock();
	};
}
#endif