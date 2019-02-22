/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CWINFORMCONTROLHOSTME_H__
#define __CWINFORMCONTROLHOSTME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "CControl.h"
#include "CStr.h"
#include "CPaint.h"
#include "CMathLib.h"
#include "CGdiPaint.h"
#include "CGdiPlusPaint.h"
#include "CNativeBase.h"
#include "CControlHost.h"

namespace MeLib
{
	class CNativeBaseMe;

	class WinformControlHost : public CControlHostMe
	{
	private:
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
	private:
		SIZE GetClientSize();
	public:
		WinformControlHost();
		virtual ~WinformControlHost();
		HWND GetHWnd();
		void SetHWnd(HWND hWnd);
		virtual CNativeBaseMe* GetNative();
		virtual void SetNative(CNativeBaseMe *native);
		int GetPInvokeMsgID();
		void SetPInvokeMsgID(int pInvokeMsgID);
	public:
		virtual void ActiveMirror();
		virtual bool AllowOperate();
		virtual bool AllowPartialPaint();
		virtual void BeginInvoke(CControlMe *control, void *args);
		virtual void Copy(string text);
		virtual CControlMe* CreateInternalControl(CControlMe *parent, const String& clsid);
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
        virtual void StartTimer(int timerID, int interval);
        virtual void StopTimer(int timerID);
		void UnLock();
	};
}
#endif