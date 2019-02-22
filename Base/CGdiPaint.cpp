#include "..\\stdafx.h"
#include "..\\include\\Base\\CGdiPaint.h"
#include "..\\include\\Base\\CStr.h"
#include "..\\include\\Base\\CFile.h"
#include <stdlib.h>
using namespace MeLib;

void CGdiPaintMe::AffectScaleFactor( RECT *rect )
{
	if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
    {
        rect->left = (int) (rect->left * m_scaleFactorX);
        rect->top = (int) (rect->top * m_scaleFactorY);
        rect->right = (int) (rect->right * m_scaleFactorX);
        rect->bottom = (int) (rect->bottom * m_scaleFactorY);
    }
}

CGdiPaintMe::CGdiPaintMe()
{

}

CGdiPaintMe::~CGdiPaintMe()
{
	if (m_hDC)
	{
		DeleteDC(m_hDC);
		m_hDC = 0;
	}
	if (m_wndHDC)
	{
		DeleteDC(m_wndHDC);
		m_wndHDC = 0;
	}
	if (m_g)
	{
		delete m_g;
		m_g = 0;
	}
	if (m_memBM)
	{
		DeleteObject(m_memBM);
		m_memBM = 0;
	}
	ClearCaches();
}

void CGdiPaintMe::AddArc( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CGdiPaintMe::AddBezier( POINT *apt, int cpt )
{

}

void CGdiPaintMe::AddCurve( POINT *apt, int cpt )
{

}

void CGdiPaintMe::AddEllipse( const RECT& rect )
{

}

void CGdiPaintMe::AddLine( int x1, int y1, int x2, int y2 )
{

}

void CGdiPaintMe::AddRect( const RECT& rect )
{

}

void CGdiPaintMe::AddPie( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CGdiPaintMe::AddText( LPCWSTR strText, FONT *font, const RECT& rect )
{

}

void CGdiPaintMe::BeginExport( const String& exportPath, const RECT& rect )
{

}

void CGdiPaintMe::BeginPaint( HDC hDC, const RECT& wRect, const RECT& pRect )
{
}

void CGdiPaintMe::BeginPath()
{

}

void CGdiPaintMe::ClearCaches()
{
	for (map<String, Bitmap*>::iterator it = m_images.begin(); it != m_images.end(); it++)
	{
		delete it->second;
		it->second = 0;
	}
	m_images.clear();
}

void CGdiPaintMe::ClipPath()
{

}

void CGdiPaintMe::CloseFigure()
{

}

void CGdiPaintMe::ClosePath()
{

}

void CGdiPaintMe::DrawArc( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CGdiPaintMe::DrawBezier( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CGdiPaintMe::DrawCurve( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CGdiPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, const RECT& rect )
{
	DrawEllipse(dwPenColor, width, style, rect.left, rect.top, rect.right, rect.bottom);
}

void CGdiPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{
	if (dwPenColor != COLOR_EMPTY)
	{
		dwPenColor = GetPaintColor(dwPenColor);
		if (dwPenColor < 0L)
		{
			dwPenColor = abs((long double)dwPenColor) / 0x3e8;
		}
		HPEN hObject= CreatePen((int) dwPenColor, (int) width, style);
		HPEN *ptr2 = (HPEN*)SelectObject(m_hDC, hObject);
		SelectObject(m_hDC, GetStockObject(5));
		RECT rect = {left + m_offsetX, top + m_offsetY, right + m_offsetX, bottom + m_offsetY};
		AffectScaleFactor(&rect);
		Ellipse(m_hDC, rect.left, rect.top, rect.right, rect.bottom);
		SelectObject(m_hDC, ptr2);
		DeleteObject(hObject);
	}
}

void CGdiPaintMe::DrawImage( LPCWSTR imagePath, const RECT& rect )
{
	String key = m_resourcePath + imagePath;
	Bitmap *image = 0;
	int width = rect.right - rect.left;
	if (width < 1)
	{
		width = 1;
	}
	int height = rect.bottom - rect.top;
	if (height < 1)
	{
		height = 1;
	}
	Gdiplus::RectF rectangle(rect.left + m_offsetX, rect.top + m_offsetY, width, height);
	if (m_images.find(key) != m_images.end())
	{
		image = m_images[key];
	}
	else
	{
		String strArray[] = { L"file", L"corner", L"source", L"highcolor", L"lowcolor" };
		String strArray2[5];
		strArray2[0] = imagePath;
		String temp(imagePath);
		if (temp.find(L"=") != -1)
		{
			for (int i = 0; i < _countof(strArray); i++)
			{
				String str2 = strArray[i];
				int num4 = (int)str2.length() + 2;
				int index = (int)temp.find(str2 + L"='");
				if (index >= 0)
				{
					int num6 = (int)temp.find(L"'", (int) (index + num4));
					strArray2[i] = temp.substr(index + num4, (num6 - index) - num4);
				}
			}
		}
		String path = strArray2[0];
		if ((!CFile::IsDirectoryExist(path)) && ((int)m_resourcePath.length() > 0))
		{
			if ((int)m_resourcePath.find_last_of(L"\\") == (int)m_resourcePath.size() - 1)
			{
				path = m_resourcePath + path;
			}
			else
			{
				path = m_resourcePath + L"\\" + path;
			}
		}
		if (CFile::IsDirectoryExist(path))
		{
			Bitmap* bitmap2 = NULL;
			if (strArray2[2].size() > 0)
			{
				int numArray[4];
				vector<String> strArray3 = CStrMe::Split(strArray2[2], L",");
				for (int j = 0; j < (int)strArray3.size(); j++)
				{
					numArray[j] = CStrMe::ConvertStrToInt(strArray3[j]);
				}
				
				Gdiplus::RectF srcRect(numArray[0], numArray[1], numArray[2] - numArray[0], numArray[3] - numArray[1]);
				Bitmap* bitmap3 = (Bitmap*) Image::FromFile(path.c_str());
				if (bitmap3 != NULL)
				{
					bitmap2 = new Bitmap(srcRect.Width, srcRect.Height);
					Graphics* graphics = Graphics::FromImage(bitmap2);
					Gdiplus::RectF rectDraw(0, 0, srcRect.Width, srcRect.Height);
					graphics->DrawImage(bitmap3,  srcRect);
				}
			}
			else
			{
				bitmap2 = (Bitmap*) Image::FromFile(path.c_str());
			}
			if (bitmap2 != NULL)
			{
				_int64 eMPTY = COLOR_EMPTY;
				_int64 num9 = COLOR_EMPTY;
				if ((strArray2[3].size() > 0) && (strArray2[4].size() > 0))
				{
					eMPTY = CStrMe::ConvertStrToColor(strArray2[3]);
					num9 = CStrMe::ConvertStrToColor(strArray2[4]);
				}
				ImageAttributes* imageAttr = new ImageAttributes();
				if ((eMPTY != COLOR_EMPTY) && (num9 != COLOR_EMPTY))
				{
					int a = 0;
					int r = 0;
					int g = 0;
					int b = 0;
					COLOR::ToARGB(this, eMPTY, &a, &r, &g, &b);
					_int64 colorHigh = COLOR::ARGB(a, r, g, b);
					COLOR::ToARGB(this, num9, &a, &r, &g, &b);
					_int64 colorLow = COLOR::ARGB(a, r, g, b);
					imageAttr->SetColorKey(colorLow, colorHigh);
				}
				int num14 = bitmap2->GetWidth();
				int num15 = bitmap2->GetHeight();
				image = new Bitmap(num14, num15);
				Graphics* graphics2 = Graphics::FromImage(image);
				if (strArray2[1].size() == 0)
				{
					Rect destRect(0, 0, num14, num15);
					graphics2->DrawImage(bitmap2, destRect, 0, 0, num14, num15, UnitPixel);
				}
				else
				{
					int numArray2[4];
					vector<String> strArray4 = CStrMe::Split(strArray2[1], L",");
					for (int k = 0; k < strArray4.size(); k++)
					{
						numArray2[k] = CStrMe::ConvertStrToInt(strArray4[k]);
					}
					int x = 0;
					int y = 0;
					int num19 = rectangle.Width;
					int num20 = rectangle.Height;
					if (numArray2[0] > 0)
					{
						Rect destRect(x, y, numArray2[0], num15);
						graphics2->DrawImage(bitmap2, destRect, 0, 0, numArray2[0], num15, UnitPixel);					
					}
					if (numArray2[1] > 0)
					{
						Rect destRect(x, y, num14, numArray2[1]);
						graphics2->DrawImage(bitmap2, destRect, 0, 0, num14, numArray2[1], UnitPixel);
					}
					if (numArray2[2] > 0)
					{
						Rect destRect(num19 - numArray2[2], y, numArray2[2], num15);
						graphics2->DrawImage(bitmap2, destRect, num14 - numArray2[2], 0, numArray2[2], num15, UnitPixel);						
					}
					if (numArray2[3] > 0)
					{
						Rect destRect(x, num20 - numArray2[3], num14, numArray2[3]);
						graphics2->DrawImage(bitmap2, destRect, 0, num15 - numArray2[3], num14, numArray2[3], UnitPixel);
					}
					int num21 = (num14 - numArray2[0]) - numArray2[2];
					int num22 = (num15 - numArray2[1]) - numArray2[3];
					int srcWidth = (num14 - numArray2[0]) - numArray2[2];
					int srcHeight = (num15 - numArray2[1]) - numArray2[3];
					if (((num21 > 0) && (num22 > 0)) && ((srcWidth > 0) && (srcHeight > 0)))
					{
						Rect destRect(x + numArray2[0], y + numArray2[1], num21, num22);
						graphics2->DrawImage(bitmap2, destRect, numArray2[0], numArray2[1], srcWidth, srcHeight, UnitPixel);
					}
				}
				delete imageAttr;
                delete graphics2;
                delete bitmap2;
				m_images[key] = image;
			}
		}
	}
	if (image != NULL)
	{
		HBITMAP hbitmap;
		image->GetHBITMAP(RGB(0, 0, 0), &hbitmap);
		HDC hdc = CreateCompatibleDC(m_hDC);
		SelectObject(hdc, hbitmap);
		int nXDest = rect.left + m_offsetX;
		int nYDest = rect.top + m_offsetY;
		int nWidth = width;
		int nHeight = height;
		if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
		{
			nXDest = (int) (m_scaleFactorX * nXDest);
			nYDest = (int) (m_scaleFactorY * nYDest);
			nWidth = (int) (m_scaleFactorX * nWidth);
			nHeight = (int) (m_scaleFactorY * nHeight);
		}
        BitBlt(m_hDC, nXDest, nYDest, nWidth, nHeight, hdc, 0, 0, 13369376);
		DeleteObject(hbitmap);
		DeleteObject(hdc);
	}
}

void CGdiPaintMe::DrawLine( _int64 dwPenColor, float width, int style, const POINT& x, const POINT& y )
{
	DrawLine(dwPenColor, width, style, x.x, x.y, y.x, y.y);
}

void CGdiPaintMe::DrawLine( _int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2 )
{
	if (dwPenColor != COLOR_EMPTY)
	{
		dwPenColor = GetPaintColor(dwPenColor);
		if (dwPenColor < 0L)
		{
			dwPenColor = abs((long double)dwPenColor) / 0x3e8;
		}
		HPEN hObject = CreatePen(style, (int) width, (int) dwPenColor);
		HPEN *ptr2 = (HPEN*)SelectObject(m_hDC, hObject);
		int x = x1 + m_offsetX;
		int y = y1 + m_offsetY;
		int num3 = x2 + m_offsetX;
		int num4 = y2 + m_offsetY;
		if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
		{
			x = (int) (m_scaleFactorX * x);
			y = (int) (m_scaleFactorY * y);
			num3 = (int) (m_scaleFactorX * num3);
			num4 = (int) (m_scaleFactorY * num4);
		}
		MoveToEx(m_hDC, x, y, 0);
		LineTo(m_hDC, num3, num4);
		SelectObject(m_hDC, ptr2);
		DeleteObject(hObject);
	}
}

void CGdiPaintMe::DrawPath( _int64 dwPenColor, float width, int style )
{

}

void CGdiPaintMe::DrawPie( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CGdiPaintMe::DrawPolygon( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		POINT*  points= new POINT[cpt];
        for (int i = 0; i < cpt; i++)
        {
			POINT pSrc = *(apt + i);
            int x = pSrc.x + m_offsetX;
            int y = pSrc.y + m_offsetY;
            if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
            {
                x = (int) (m_scaleFactorX * x);
                y = (int) (m_scaleFactorY * y);
            }
			POINT p;
			p.x = x;
			p.y = y;
            points[i] = p;
        }
        HPEN hObject = CreatePen(style, (int) width, (int) dwPenColor);
        HGDIOBJ ptr2 = SelectObject(m_hDC, hObject);
		Polygon(m_hDC, points, cpt);		
        SelectObject(m_hDC, ptr2);
        DeleteObject(hObject);
		delete[] points;
    }
}

void CGdiPaintMe::DrawPolyline( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		POINT*  points= new POINT[cpt];
        for (int i = 0; i < cpt; i++)
        {
            POINT pSrc = *(apt + i);
            int x = pSrc.x + m_offsetX;
            int y = pSrc.y + m_offsetY;
            if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
            {
                x = (int) (m_scaleFactorX * x);
                y = (int) (m_scaleFactorY * y);
            }
			POINT p;
			p.x = x;
			p.y = y;
            points[i] = p;
        }
		HPEN hObject = ::CreatePen(style, (int) width, (int) dwPenColor);
		HGDIOBJ ptr2 = ::SelectObject(m_hDC, hObject);
		::Polyline(m_hDC, points, cpt);
		delete[]points;
		::SelectObject(m_hDC, ptr2);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::DrawRect( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		HPEN hObject = ::CreatePen(style, (int) width, (int) dwPenColor);
		HGDIOBJ ptr2 = ::SelectObject(m_hDC, hObject);
		::SelectObject(m_hDC, GetStockObject(5));
        RECT rect;
		rect.left = left + m_offsetX;
		rect.top = top + m_offsetY;
		rect.right = right + m_offsetX;
		rect.bottom = bottom + m_offsetY;
        AffectScaleFactor(&rect);
		::Rectangle(m_hDC, rect.left, rect.top, rect.right, rect.bottom);
		::SelectObject(m_hDC, ptr2);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::DrawRect( _int64 dwPenColor, float width, int style, const RECT& rect )
{
	DrawRect(dwPenColor, width, style, rect.left, rect.top, rect.right, rect.bottom);
}

void CGdiPaintMe::DrawRoundRect( _int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		HPEN hObject = ::CreatePen(style, (int) width, (int) dwPenColor);
		HGDIOBJ ptr2 = ::SelectObject(m_hDC, hObject);
		::SelectObject(m_hDC, GetStockObject(5));
        RECT rect2;
		rect2.left = rect.left + m_offsetX;
		rect2.top = rect.top + m_offsetY;
		rect2.right = rect.right + m_offsetX;
		rect2.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rect2);
        if (cornerRadius != 0)
        {
			::RoundRect(m_hDC, rect2.left, rect2.top, rect2.right, rect2.bottom, cornerRadius, cornerRadius);
        }
        else
        {
			::Rectangle(m_hDC, rect2.left, rect2.top, rect2.right, rect2.bottom);
        }
		::SelectObject(m_hDC, ptr2);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
        int fontSize = (int) font->m_fontSize;
        if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
        {
            fontSize = (int) ((fontSize * (m_scaleFactorX + m_scaleFactorY)) / 2.0);
        }
		HFONT hObject = ::CreateFont(fontSize, 0, 0, 0, font->m_bold ? 700 : 400, font->m_italic ? 1 : 0, font->m_underline ? 1 : 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, font->m_fontFamily.c_str());
        RECT rect2;
		rect2.left = rect.left + m_offsetX;
		rect2.top = rect.top + m_offsetY;
		rect2.right = rect.right + m_offsetX;
		rect2.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rect2);
		::SetBkMode(m_hDC, 1);
		::SetTextColor(m_hDC, (int) dwPenColor);
		HGDIOBJ ptr2 = ::SelectObject(m_hDC, hObject);
		::DrawText(m_hDC, strText, -1, &rect2, 0x800);
		::SelectObject(m_hDC, ptr2);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect )
{
	RECT rect1;
	rect1.left = rect.left;
	rect1.right = rect.right;
	rect1.top = rect.top;
	rect1.bottom =rect.bottom;
	DrawText(strText, dwPenColor, font, rect1);
}

void CGdiPaintMe::DrawTextAutoEllipsis( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{
 if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
        int fontSize = (int) font->m_fontSize;
        if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
        {
            fontSize = (int) ((fontSize * (m_scaleFactorX + m_scaleFactorY)) / 2.0);
        }
		HFONT hObject = ::CreateFont(fontSize, 0, 0, 0, font->m_bold ? 700 : 400, font->m_italic ? 1 : 0, font->m_underline ? 1 : 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, font->m_fontFamily.c_str());
        RECT rect2;
		rect2.left = rect.left + m_offsetX;
		rect2.top = rect.top + m_offsetY;
		rect2.right = rect.right + m_offsetX;
		rect2.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rect2);
		::SetBkMode(m_hDC, 1);
		::SetTextColor(m_hDC, (int) dwPenColor);
		HGDIOBJ ptr2 = ::SelectObject(m_hDC, hObject);
		::DrawText(m_hDC, strText, -1, &rect2, 0x40800);
		::SelectObject(m_hDC, ptr2);
		::DeleteObject(hObject);
    }

}

void CGdiPaintMe::EndExport()
{

}

void CGdiPaintMe::EndPaint()
{
	int left = m_pRect.left;
	int top = m_pRect.top;
	int nWidth = m_pRect.right - m_pRect.left;
	int nHeight = m_pRect.bottom - m_pRect.top;
	if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
	{
		left = (int) (m_scaleFactorX * left);
		top = (int) (m_scaleFactorY * top);
		nWidth = (int) (m_scaleFactorX * nWidth);
		nHeight = (int) (m_scaleFactorY * nHeight);
	}
	BitBlt(m_wndHDC, left, top, nWidth, nHeight, m_hDC, left, top, 0xcc0020);
	if (m_hDC != 0)
	{
		DeleteDC(m_hDC);
		m_hDC = 0;
	}
	if (m_hRgn != 0)
	{
		DeleteObject(m_hRgn);
		m_hRgn = 0;
	}
	if (m_wndHDC != 0)
	{
		DeleteObject(m_wndHDC);
		m_wndHDC = 0;
	}
	if (m_g != 0)
	{
		m_g = 0;
	}
	m_offsetX = 0;
	m_offsetY = 0;
	m_resourcePath = L"";
}

void CGdiPaintMe::ExcludeClipPath()
{

}

void CGdiPaintMe::FillEllipse( _int64 dwPenColor, const RECT& rect )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		HBRUSH hObject = ::CreateSolidBrush((int) dwPenColor);
		::SelectObject(m_hDC, hObject);
        RECT rectAfter;
		rectAfter.left = rect.left + m_offsetX;
		rectAfter.top = rect.top + m_offsetY;
		rectAfter.right = rect.right + m_offsetX;
		rectAfter.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rectAfter);
		::Ellipse(m_hDC, rectAfter.left, rectAfter.top, rectAfter.right, rectAfter.bottom);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::FillGradientEllipse( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{
	if (dwFirst != COLOR_EMPTY)
    {
        dwFirst = GetPaintColor(dwFirst);
        if (dwFirst < 0L)
        {
            dwFirst = abs((long double)dwFirst) / 0x3e8L;
        }
		HBRUSH hObject = ::CreateSolidBrush((int) dwFirst);
		::SelectObject(m_hDC, hObject);
        RECT rectAfter;
		rectAfter.left = rect.left + m_offsetX;
		rectAfter.top = rect.top + m_offsetY;
		rectAfter.right = rect.right + m_offsetX;
		rectAfter.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rectAfter);
		::Ellipse(m_hDC, rectAfter.left, rectAfter.top, rectAfter.right, rectAfter.bottom);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::FillGradientPath( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{

}

void CGdiPaintMe::FillGradientPolygon( _int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle )
{
	FillPolygon(dwFirst, apt, cpt);
}

void CGdiPaintMe::FillGradientRect( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle )
{
    if (cornerRadius != 0)
    {
        FillRoundRect(dwFirst, rect, cornerRadius);
    }
    else
    {
        FillRect(dwFirst, rect);
    }
}

void CGdiPaintMe::FillPath( _int64 dwPenColor )
{

}

void CGdiPaintMe::FillPie( _int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CGdiPaintMe::FillPolygon( _int64 dwPenColor, POINT *apt, int cpt )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
		POINT*  points= new POINT[cpt];
        for (int i = 0; i < cpt; i++)
        {
			POINT pSrc = *(apt + i);
            int x = pSrc.x + m_offsetX;
            int y = pSrc.y + m_offsetY;
            if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
            {
                x = (int) (m_scaleFactorX * x);
                y = (int) (m_scaleFactorY * y);
            }
			POINT p;
			p.x = x;
			p.y = y;
            points[i] = p;
        }

		HBRUSH hObject = ::CreateSolidBrush((int) dwPenColor);
		::SelectObject(m_hDC, hObject);
		::Polygon(m_hDC, points, cpt);
		delete[]points;
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::FillRect( _int64 dwPenColor, const RECT& rect )
{
	if (dwPenColor != COLOR_EMPTY)
    {
        dwPenColor = GetPaintColor(dwPenColor);
        if (dwPenColor < 0L)
        {
            dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
        }
        RECT rect2;
		rect2.left = rect.left + m_offsetX;
		rect2.top = rect.top + m_offsetY;
		rect2.right = rect.right + m_offsetX;
		rect2.bottom = rect.bottom + m_offsetY;
        AffectScaleFactor(&rect2);
		HBRUSH hObject = ::CreateSolidBrush((int) dwPenColor);
		::SelectObject(m_hDC, hObject);
		::FillRect(m_hDC, &rect2, hObject);
		::DeleteObject(hObject);
    }
}

void CGdiPaintMe::FillRect( _int64 dwPenColor, int left, int top, int right, int bottom )
{
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
	FillRect(dwPenColor, rect);
}

void CGdiPaintMe::FillRoundRect( _int64 dwPenColor, const RECT& rect, int cornerRadius )
{
	if (dwPenColor != COLOR_EMPTY)
	{
		dwPenColor = GetPaintColor(dwPenColor);
		if (dwPenColor < 0L)
		{
			dwPenColor = abs((long double)dwPenColor) / 0x3e8L;
		}
		RECT rect2;
		rect2.left = rect.left + m_offsetX;
		rect2.top = rect.top + m_offsetY;
		rect2.right = rect.right + m_offsetX;
		rect2.bottom = rect.bottom + m_offsetY;
		AffectScaleFactor(&rect2);
		HBRUSH hObject = ::CreateSolidBrush((int) dwPenColor);
		::SelectObject(m_hDC, hObject);
		if (cornerRadius != 0)
		{
			RoundRect(m_hDC, rect2.left, rect2.top, rect2.right, rect2.bottom, cornerRadius, cornerRadius);
		}
		else
		{
			::FillRect(m_hDC, &rect2, hObject);
		}
		::DeleteObject(hObject);
	}
}

_int64 CGdiPaintMe::GetColor( _int64 dwPenColor )
{
	if (dwPenColor < COLOR_EMPTY)
	{
		if (dwPenColor == COLOR_CONTROL)
		{
			dwPenColor = 0xffffffL;
			return dwPenColor;
		}
		if (dwPenColor == COLOR_CONTROLBORDER)
		{
			dwPenColor = 0x323232L;
			return dwPenColor;
		}
		if (dwPenColor == COLOR_CONTROLTEXT)
		{
			dwPenColor = 0L;
			return dwPenColor;
		}
		if (dwPenColor == COLOR_DISABLEDCONTROL)
		{
			dwPenColor = 0xc8c8c8L;
			return dwPenColor;
		}
		if (dwPenColor == COLOR_DISABLEDCONTROLTEXT)
		{
			dwPenColor = 0x323232L;
			return dwPenColor;
		}
		if (dwPenColor == COLOR_HOVEREDCONTROL)
		{
			dwPenColor = COLOR::ARGB(255, 0, 0);
			return dwPenColor;
		}
		if (dwPenColor == COLOR_PUSHEDCONTROL)
		{
			dwPenColor = COLOR::ARGB(0, 255, 0);
			return dwPenColor;
		}
	}
	return dwPenColor;
}

_int64 CGdiPaintMe::GetPaintColor( _int64 dwPenColor )
{
    return GetColor(dwPenColor);
}

POINT CGdiPaintMe::GetOffset()
{
	POINT point = {m_offsetX, m_offsetY};
	return point;
}

POINT CGdiPaintMe::Rotate( const POINT& op, const POINT& mp, int angle )
{
    float num = 3.141593f;
	POINT point = {0, 0};
	float cosNum = cos((double) ((angle * num) / 180));
	float sinNum = sin((double) ((angle * num) / 180));
    point.x = (int) (((mp.x - op.x) * cosNum) - ((mp.y - op.y) * sinNum)) + op.x;
    point.y = (int) (((mp.x - op.x) * sinNum) + ((mp.y - op.y) * cosNum)) + op.y;
    return point;
}

void CGdiPaintMe::SetClip( const RECT& rect )
{
	if (m_hRgn != 0)
    {
        DeleteObject(m_hRgn);
    }
	RECT rect2;
	rect2.left = rect.left + m_offsetX;
	rect2.top = rect.top + m_offsetY;
	rect2.right = rect.right + m_offsetX;
	rect2.bottom = rect.bottom + m_offsetY;
    if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
    {
        rect2.left = (int) floor((double) (rect2.left * m_scaleFactorX));
        rect2.top = (int) floor((double) (rect2.top * m_scaleFactorY));
        rect2.right = (int) ceil((double) (rect2.right * m_scaleFactorX));
        rect2.bottom = (int) ceil((double) (rect2.bottom * m_scaleFactorY));
    }
    m_hRgn = CreateRectRgnIndirect(&rect2);
    SelectClipRgn(m_hDC, m_hRgn);
}

void CGdiPaintMe::SetLineCap( int startLineCap, int endLineCap )
{
   
}

void CGdiPaintMe::SetOffset( const POINT& offset )
{
    m_offsetX = offset.x;
    m_offsetY = offset.y;
}

void CGdiPaintMe::SetOpacity( float opacity )
{

}

void CGdiPaintMe::SetResourcePath( const String& resourcePath )
{
	m_resourcePath = resourcePath;
}

void CGdiPaintMe::SetRotateAngle( int rotateAngle )
{
	m_rotateAngle = rotateAngle;
}

void CGdiPaintMe::SetScaleFactor( double scaleFactorX, double scaleFactorY )
{
    m_scaleFactorX = scaleFactorX;
    m_scaleFactorY = scaleFactorY;
}

void CGdiPaintMe::SetSmoothMode( int smoothMode )
{

}

void CGdiPaintMe::SetTextQuality( int textQuality )
{

}

bool CGdiPaintMe::SupportTransparent()
{
	return false;
}

SIZE CGdiPaintMe::TextSize( LPCWSTR strText, FONT *font )
{
	SIZE size;
	String text(strText);
	if (text.size() > 0)
    {
        HFONT hObject = CreateFont((int) font->m_fontSize, 0, 0, 0, font->m_bold ? 700 : 400, font->m_italic ? 1 : 0,
			font->m_underline ? 1 : 0, 0, GB2312_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, font->m_fontFamily.c_str());
        HGDIOBJ ptr2 = SelectObject(m_hDC, hObject);
        GetTextExtentPoint32(m_hDC, strText, (int)text.size(), &size);
        SelectObject(m_hDC, ptr2);
        DeleteObject(hObject);
    }
    return size;

}

SIZEF CGdiPaintMe::TextSizeF( LPCWSTR strText, FONT *font )
{
	SIZE size = TextSize(strText, font);
	SIZEF sizeF;
	sizeF.cx = (float) size.cx;
	sizeF.cy = (float) size.cy;
    return sizeF ;
}
