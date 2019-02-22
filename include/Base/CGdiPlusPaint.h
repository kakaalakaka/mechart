/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CGDIPLUSPAINTME_H__
#define __CGDIPLUSPAINTME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include <comdef.h>
#include "gdiplus.h"
#pragma comment(lib, "gdiplus.lib")
using namespace Gdiplus;
#include "CPaint.h"

namespace MeLib
{
	class  CGdiPlusPaintMe : public CPaintMe 
	{
	protected:
		Bitmap *m_bitmap;
		SolidBrush *m_brush;
		_int64 m_brushColor;
		StringFormat *m_emptyStringFormat;
		int m_endLineCap;
		wstring m_exportPath;
		Graphics *m_g;
		HDC m_hDC;
		map<wstring, Bitmap*> m_images;
		int m_offsetX;
		int m_offsetY;
		float m_opacity;
		GraphicsPath *m_path;
		Pen *m_pen;
		RECT m_pRect;
		_int64 m_penColor;
		float m_penWidth;
		int m_penStyle;
		wstring m_resourcePath;
		int m_rotateAngle;
		double m_scaleFactorX;
		double m_scaleFactorY;
		int m_smoothMode;
		int m_startLineCap;
		int m_textQuality;
		RECT m_wRect;
	protected:
		void AffectScaleFactor(Rect *gdiplusRect);
		void AffectScaleFactor(RectF *gdiplusRect);
		SolidBrush* GetBrush(_int64 dwPenColor);
		Color GetGdiPlusColor(_int64 dwPenColor);
		int GetEncoderClsid(const WCHAR *format, CLSID *pClsid);
		Gdiplus::Font* GetFont(FONT *font);
		Pen* GetPen(_int64 dwPenColor, float width, int style);
		GraphicsPath* GetRoundRectPath(Rect gdiPlusRect, int cornerRadius);
	public:
		CGdiPlusPaintMe();
		virtual ~CGdiPlusPaintMe();
	public:
		virtual void AddArc(const RECT& rect, float startAngle, float sweepAngle);
		virtual void AddBezier(POINT *apt, int cpt);
		virtual void AddCurve(POINT *apt, int cpt);
		virtual void AddEllipse(const RECT& rect);
		virtual void AddLine(int x1, int y1, int x2, int y2);
		virtual void AddRect(const RECT& rect);
		virtual void AddPie(const RECT& rect, float startAngle, float sweepAngle);
		virtual void AddText(LPCWSTR strText, FONT *font, const RECT& rect);
		virtual void BeginExport(const wstring& exportPath, const RECT& rect);
		virtual void BeginPaint(HDC hDC, const RECT& wRect, const RECT& pRect);
		virtual void BeginPath();
		virtual void ClipPath();
		virtual void ClearCaches();
		virtual void CloseFigure();
		virtual void ClosePath();
		virtual void DrawArc(_int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle);
		virtual void DrawBezier(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawCurve(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawEllipse(_int64 dwPenColor, float width, int style, const RECT& rect);
		virtual void DrawEllipse(_int64 dwPenColor, float width, int style, int left, int top, int right, int bottom);
		virtual void DrawImage(LPCWSTR imagePath, const RECT& rect);
		virtual void DrawLine(_int64 dwPenColor, float width, int style, const POINT& x, const POINT& y);
		virtual void DrawLine(_int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2);
		virtual void DrawPath(_int64 dwPenColor, float width, int style);
		virtual void DrawPie(_int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle);
		virtual void DrawPolygon(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawPolyline(_int64 dwPenColor, float width, int style, POINT *apt, int cpt);
		virtual void DrawRect(_int64 dwPenColor, float width, int style, int left, int top, int right, int bottom);
		virtual void DrawRect(_int64 dwPenColor, float width, int style, const RECT& rect);
		virtual void DrawRoundRect(_int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius);
		virtual void DrawText(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect);
		virtual void DrawText(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect);
		virtual void DrawTextAutoEllipsis(LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect);
		virtual void EndExport();
		virtual void EndPaint();
		virtual void ExcludeClipPath();
		virtual void FillEllipse(_int64 dwPenColor, const RECT& rect);
		virtual void FillGradientEllipse(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle);
		virtual void FillGradientPath(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle);
		virtual void FillGradientPolygon(_int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle);
		virtual void FillGradientRect(_int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle);
		virtual void FillPath(_int64 dwPenColor);
		virtual void FillPie(_int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle);
		virtual void FillPolygon(_int64 dwPenColor, POINT *apt, int cpt);
		virtual void FillRect(_int64 dwPenColor, const RECT& rect);
		virtual void FillRect(_int64 dwPenColor, int left, int top, int right, int bottom);
		virtual void FillRoundRect(_int64 dwPenColor, const RECT& rect, int cornerRadius);
		virtual _int64 GetColor(_int64 dwPenColor);
		virtual _int64 GetPaintColor(_int64 dwPenColor);
		virtual POINT GetOffset();
		virtual POINT Rotate(const POINT& op, const POINT& mp, int angle);
		virtual void SetClip(const RECT& rect);
		virtual void SetLineCap(int startLineCap, int endLineCap);
		virtual void SetOffset(const POINT& offset);
		virtual void SetOpacity(float opacity);
        virtual void SetResourcePath(const wstring& resourcePath);
		virtual void SetRotateAngle(int rotateAngle);
		virtual void SetScaleFactor(double scaleFactorX, double scaleFactorY);
		virtual void SetSmoothMode(int smoothMode);
		virtual void SetTextQuality(int textQuality);
		virtual bool SupportTransparent();
		virtual SIZE TextSize(LPCWSTR strText, FONT *font);
		virtual SIZEF TextSizeF(LPCWSTR strText, FONT *font);
	};
}

#endif