/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CNATIVEBASEME_H__
#define __CNATIVEBASEME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include "CControl.h"
#include "CStr.h"
#include "CPaint.h"
#include "CGdiPaint.h"
#include "CGdiPlusPaint.h"
#include "CControlHost.h"
#include "CWinHost.h"

namespace MeLib
{
	typedef enum  SORTTYPE
	{
		SORTTYPE_NONE,
		SORTTYPE_ASC,
		SORTTYPE_DESC
	};

	class  CControlMe;
	class  CControlHostMe;
	class  CWinHostMe;
	class  CNativeBaseMe
	{
	protected:
		bool m_allowScaleSize;
		SIZE m_displaySize;
		POINT m_drawBeginPoint;
		RECT m_dragBeginRect;
		POINT m_dragStartOffset;
		CControlMe *m_exportingControl;
		CControlHostMe *m_host;
		CNativeBaseMe *m_mirrorHost;
		MirrorMode m_mirrorMode;
		float m_opacity;
		CPaintMe *m_paint;
		POINT m_mouseDownPoint;
		wstring m_resourcePath;
		int m_rotateAngle;
		SIZE m_scaleSize;
		map<int, CControlMe*> m_timers;
		CControlMe* FindControl(const POINT& mp, vector<CControlMe*> *controls);
		CControlMe* FindControl(const wstring& name, vector<CControlMe*> *controls);
		CControlMe* FindPreviewsControl(CControlMe *control);
		CControlMe* FindWindow(CControlMe *control);
		float GetPaintingOpacity(CControlMe *control);
		wstring GetPaintingResourcePath(CControlMe *control);
		bool GetSortedControls(CControlMe *parent, vector<CControlMe*> *sortedControls);
		void GetTabStopControls(CControlMe *control, vector<CControlMe*> *tabStopControls);
		bool IsPaintEnabled(CControlMe *control);
		void RenderControls(const RECT& rect, vector<CControlMe*> *controls, wstring resourcePath, float opacity);
		void SetCursor(CControlMe *control);
		void SetPaint(int offsetX, int offsetY, const RECT& clipRect, wstring resourcePath, float opacity);
	public:
		CControlMe *m_draggingControl;
		CControlMe *m_focusedControl;
		CControlMe *m_mouseDownControl;
		CControlMe *m_mouseMoveControl;
	public:
		vector<CControlMe*> m_controls;
		vector<CNativeBaseMe*> m_mirrors;
		CNativeBaseMe();
		virtual ~CNativeBaseMe();
		bool AllowScaleSize();
		void SetAllowScaleSize(bool allowScaleSize);
		CursorsMe GetCursor();
		void SetCursor(CursorsMe cursor);
		SIZE GetDisplaySize();
		void SetDisplaySize(SIZE displaySize);
		CControlMe* GetFocusedControl();
		void SetFocusedControl(CControlMe *focusedControl);
		CControlHostMe* GetHost();
		void SetHost(CControlHostMe *host);
		CControlMe* GetHoveredControl();
		CNativeBaseMe* GetMirrorHost();
		MirrorMode GetMirrorMode();
		void SetMirrorMode(MirrorMode mirrorMode);
		POINT GetMousePoint();
		float GetOpacity();
		void SetOpacity(float opacity);
		CPaintMe* GetPaint();
		void SetPaint(CPaintMe *paint);
		CControlMe* GetPushedControl();
		wstring GetResourcePath();
		void SetResourcePath(const wstring& resourcePath);
		int GetRotateAngle();
		void SetRotateAngle(int rotateAngle);
		SIZE GetScaleSize();
		void SetScaleSize(SIZE scaleSize);
	public:
		void AddControl(CControlMe *control);
		void AddMirror(CNativeBaseMe *mirrorHost, CControlMe *control);
		void BringToFront(CControlMe *control);
		void CancelDragging();
		void ClearControls();
		int ClientX(CControlMe *control);
		int ClientY(CControlMe *control);
		bool ContainsControl(CControlMe *control);
        void ExportToImage(const wstring& exportPath);
        void ExportToImage(const wstring& exportPath, CControlMe *control);
		CControlMe* FindControl(const POINT& mp);
		CControlMe* FindControl(const POINT& mp, CControlMe *parent);
		CControlMe* FindControl(const wstring& name);
		vector<CControlMe*> GetControls();
		void InsertControl(int index, CControlMe *control);
		void Invalidate();
		void Invalidate(CControlMe *control);
		void Invalidate(const RECT& rect);
		bool OnChar(wchar_t key);
		void OnDoubleClick(MouseButtonsMe button, int clicks, int delta);
		void OnKeyDown(char key);
		void OnKeyUp(char key);
		void OnMouseDown(MouseButtonsMe button, int clicks, int delta);
		void OnMouseLeave(MouseButtonsMe button, int clicks, int delta);
		void OnMouseMove(MouseButtonsMe button, int clicks, int delta);
		void OnMouseUp(MouseButtonsMe button, int clicks, int delta);
		void OnMouseWheel(MouseButtonsMe button, int clicks, int delta);
		void OnPaint(const RECT& rect);
		bool OnPreviewsKeyEvent(int eventID, char key);
		bool OnPreviewsMouseEvent(int eventID, CControlMe *control, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		void OnResize();
		void OnTimer(int timerID);
		void RemoveControl(CControlMe *control);
		void RemoveMirror(CControlMe *control);
		void SendToBack(CControlMe *control);
		void SetAlign(vector<CControlMe*> *controls);
		void SetAnchor(vector<CControlMe*> *controls, SIZE oldSize);
		void SetDock(vector<CControlMe*> *controls);
		void StartTimer(CControlMe *control, int timerID, int interval);
		void StopTimer(int timerID);
		void Update();
	};
}
#endif