#include "..\\stdafx.h"
#include "..\\include\\Base\\CGdiPlusPaint.h"
#include "..\\include\\Base\\CFile.h"
#include "..\\include\\Base\\CStr.h"
using namespace MeLib;

HBITMAP create_hbitmap_from_gdiplus_bitmap_ex(Bitmap* bitmap_ptr, Gdiplus::Rect rect)
{
	Gdiplus::Rect newRect(0, 0, bitmap_ptr->GetWidth(), bitmap_ptr->GetHeight());
	rect.Intersect(newRect);
	if(rect.Width > 0 && rect.Height > 0)
	{
		BITMAP bm;
		Gdiplus::BitmapData bmpdata;
		HBITMAP hBitmap;
		if (bitmap_ptr->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppPARGB, &bmpdata) != Gdiplus::Ok)
		{
			return 0;
		}
		bm.bmType = 0;
		bm.bmWidth = bmpdata.Width;
		bm.bmHeight = bmpdata.Height;
		bm.bmWidthBytes = bmpdata.Stride;
		bm.bmPlanes = 1;
		bm.bmBitsPixel = 32;
		bm.bmBits = bmpdata.Scan0;
		hBitmap = CreateBitmapIndirect(&bm);
		bitmap_ptr->UnlockBits(&bmpdata);
		return hBitmap;
	}
	else
	{
		return 0;
	}
}

void CGdiPlusPaintMe::AffectScaleFactor( Rect *gdiplusRect )
{
	if ((m_scaleFactorX != 1.0) || (m_scaleFactorY != 1.0))
	{
		gdiplusRect->X = (int) (gdiplusRect->X * m_scaleFactorX);
		gdiplusRect->Y = (int) (gdiplusRect->Y * m_scaleFactorY);
		gdiplusRect->Width = (int) (gdiplusRect->Width * m_scaleFactorX);
		gdiplusRect->Height = (int) (gdiplusRect->Height * m_scaleFactorY);
	}
}

void CGdiPlusPaintMe::AffectScaleFactor( RectF *gdiplusRect )
{
	if ((m_scaleFactorX != -1.0) || (m_scaleFactorY != -1.0))
    {
        gdiplusRect->X = (float) (gdiplusRect->X * m_scaleFactorX);
		gdiplusRect->Y = (float) (gdiplusRect->Y * m_scaleFactorY);
        gdiplusRect->Width = (float) (gdiplusRect->Width * m_scaleFactorX);
        gdiplusRect->Height = (float) (gdiplusRect->Height * m_scaleFactorY);
    }
}

SolidBrush* CGdiPlusPaintMe::GetBrush( _int64 dwPenColor )
{
	Color gdiColor = GetGdiPlusColor(dwPenColor);
    if (!m_brush)
    {
        m_brush = new SolidBrush(gdiColor);
        if (m_opacity == 1)
        {
            m_brushColor = dwPenColor;
        }
        else
        {
            m_brushColor = COLOR_EMPTY;
        }
    }
    else
    {
        if (m_brushColor == COLOR_EMPTY || m_brushColor != dwPenColor)
        {
			m_brush->SetColor(gdiColor);
            m_brushColor = dwPenColor;
        }
        if (m_opacity != 1)
        {
            m_brushColor = COLOR_EMPTY;
        }
    }
    return m_brush;
}

Color CGdiPlusPaintMe::GetGdiPlusColor( _int64 dwPenColor )
{
	dwPenColor = GetPaintColor(dwPenColor);
	int a = 255;
	if(dwPenColor < 0)
	{
		dwPenColor = -dwPenColor;
		if(dwPenColor < 1)
		{
			a = 255;
		}
		else
		{
			a = (int)(dwPenColor - dwPenColor / 1000 * 1000);
		}
		dwPenColor /= 1000;
	}
	int r = (int)(dwPenColor & 255);
	int g = (int)((dwPenColor >> 8) & 255);
	int b = (int)((dwPenColor >> 16) & 255);
	Color gdiColor(a, r, g, b);
	if(m_opacity < 1)
	{
		Color opacityColor((BYTE)(a * m_opacity), r, g, b);
		return opacityColor;
	}
	return gdiColor;
}

int CGdiPlusPaintMe::GetEncoderClsid( const WCHAR *format, CLSID *pClsid )
{
	UINT  num = 0;          
	UINT  size = 0;         
	ImageCodecInfo *pImageCodecInfo = 0;
	GetImageEncodersSize(&num, &size);
	if(size == 0){
		return -1;  
	}
	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == 0){
		return -1; 
	}
	GetImageEncoders(num, size, pImageCodecInfo);
	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  
		}    
	}
	free(pImageCodecInfo);
	return -1;  
}

Gdiplus::Font* CGdiPlusPaintMe::GetFont( FONT *font )
{
	if(font->m_strikeout)
	{
		if (font->m_bold && font->m_underline && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleUnderline | FontStyleItalic | FontStyleStrikeout, UnitPixel);
		}
		else if (font->m_bold && font->m_underline)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleUnderline | FontStyleStrikeout, UnitPixel);
		}
		else if (font->m_bold && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleItalic | FontStyleStrikeout, UnitPixel);
		}
		else if (font->m_underline && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleUnderline | FontStyleItalic | FontStyleStrikeout, UnitPixel);
		}
		else if (font->m_bold)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleStrikeout, UnitPixel);
		}
		else if(font->m_underline)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleUnderline | FontStyleStrikeout, UnitPixel);
		}
		else if (font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleItalic| FontStyleStrikeout, UnitPixel);
		}
		else
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleRegular| FontStyleStrikeout, UnitPixel);
		}
	}
	else
	{
		if (font->m_bold && font->m_underline && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleUnderline | FontStyleItalic, UnitPixel);
		}
		else if (font->m_bold && font->m_underline)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleUnderline, UnitPixel);
		}
		else if (font->m_bold && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold | FontStyleItalic, UnitPixel);
		}
		else if (font->m_underline && font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleUnderline | FontStyleItalic, UnitPixel);
		}
		else if (font->m_bold)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleBold, UnitPixel);
		}
		else if(font->m_underline)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleUnderline, UnitPixel);
		}
		else if (font->m_italic)
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleItalic, UnitPixel);
		}
		else
		{
			return new Gdiplus::Font(font->m_fontFamily.c_str(), (REAL)font->m_fontSize, FontStyleRegular, UnitPixel);
		}
	}
}

Pen* CGdiPlusPaintMe::GetPen( _int64 dwPenColor, float width, int style )
{
	Color gdiColor = GetGdiPlusColor(dwPenColor);
	if (!m_pen )
	{
		m_pen = new Pen(gdiColor, (REAL)width);
		if (style == 0)
		{
			m_pen->SetDashStyle(DashStyleSolid);
		}
		else if (style == 1)
		{
			m_pen->SetDashStyle(DashStyleDash);
		}
		else if (style == 2)
		{
			m_pen->SetDashStyle(::DashStyleDot);
		}
		m_penWidth = width;
		m_penStyle = style;
		if (m_opacity == 1)
		{
			m_penColor = dwPenColor;
		}
		else
		{
			m_penColor = COLOR_EMPTY;
		}
		switch(m_startLineCap)
		{
		case 0:
			m_pen->SetStartCap(LineCapFlat);
			break;
		case 1:
			m_pen->SetStartCap(LineCapSquare);
			break;
		case 2:
			m_pen->SetStartCap(LineCapRound);
			break;
		case 3:
			m_pen->SetStartCap(LineCapTriangle);
			break;
		case 4:
			m_pen->SetStartCap(LineCapNoAnchor);
			break;
		case 5:
			m_pen->SetStartCap(LineCapSquareAnchor);
			break;
		case 6:
			m_pen->SetStartCap(LineCapRoundAnchor);
			break;
		case 7:
			m_pen->SetStartCap(LineCapDiamondAnchor);
			break;
		case 8:
			m_pen->SetStartCap(LineCapArrowAnchor);
			break;
		case 9:
			m_pen->SetStartCap(LineCapAnchorMask);
			break;
		case 10:
			m_pen->SetStartCap(LineCapCustom);
			break;
		}
		switch(m_endLineCap)
		{
		case 0:
			m_pen->SetEndCap(LineCapFlat);
			break;
		case 1:
			m_pen->SetEndCap(LineCapSquare);
			break;
		case 2:
			m_pen->SetEndCap(LineCapRound);
			break;
		case 3:
			m_pen->SetEndCap(LineCapTriangle);
			break;
		case 4:
			m_pen->SetEndCap(LineCapNoAnchor);
			break;
		case 5:
			m_pen->SetEndCap(LineCapSquareAnchor);
			break;
		case 6:
			m_pen->SetEndCap(LineCapRoundAnchor);
			break;
		case 7:
			m_pen->SetEndCap(LineCapDiamondAnchor);
			break;
		case 8:
			m_pen->SetEndCap(LineCapArrowAnchor);
			break;
		case 9:
			m_pen->SetEndCap(LineCapAnchorMask);
			break;
		case 10:
			m_pen->SetEndCap(LineCapCustom);
			break;
		}
	}
	else
	{
		if (m_penColor == COLOR_EMPTY || m_penColor != dwPenColor)
		{
			m_pen->SetColor(gdiColor);
			m_penColor = dwPenColor;
		}
		if(m_opacity != 1)
		{
			m_penColor = COLOR_EMPTY;
		}
		if (m_penWidth != width)
		{
			m_pen->SetWidth((REAL)width);
			m_penWidth = width;
		}
		if (m_penStyle != style)
		{
			if (style == 0)
			{
				m_pen->SetDashStyle(DashStyleSolid);
			}
			else if (style == 1)
			{
				m_pen->SetDashStyle(DashStyleDash);
			}
			else if (style == 2)
			{
				m_pen->SetDashStyle(DashStyleDot);
			}
			m_penStyle = style;
		}
	}
	return m_pen;
}

GraphicsPath* CGdiPlusPaintMe::GetRoundRectPath( Rect gdiPlusRect, int cornerRadius )
{
	GraphicsPath *gdiPlusPath = new GraphicsPath;
	gdiPlusPath->AddArc(gdiPlusRect.X, gdiPlusRect.Y, cornerRadius * 2, cornerRadius * 2, 180, 90);
	gdiPlusPath->AddLine(gdiPlusRect.X + cornerRadius, gdiPlusRect.Y, gdiPlusRect.GetRight() - cornerRadius * 2, gdiPlusRect.Y);
	gdiPlusPath->AddArc(gdiPlusRect.X + gdiPlusRect.Width - cornerRadius * 2, gdiPlusRect.Y, cornerRadius * 2, cornerRadius * 2, 270, 90);
	gdiPlusPath->AddLine(gdiPlusRect.GetRight(), gdiPlusRect.Y + cornerRadius * 2, gdiPlusRect.GetRight(), gdiPlusRect.Y + gdiPlusRect.Height - cornerRadius * 2);
	gdiPlusPath->AddArc(gdiPlusRect.X + gdiPlusRect.Width - cornerRadius * 2, gdiPlusRect.Y + gdiPlusRect.Height - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 0, 90);
	gdiPlusPath->AddLine(gdiPlusRect.GetRight() - cornerRadius * 2, gdiPlusRect.GetBottom(), gdiPlusRect.X + cornerRadius * 2, gdiPlusRect.GetBottom());
	gdiPlusPath->AddArc(gdiPlusRect.X, gdiPlusRect.GetBottom() - cornerRadius * 2, cornerRadius * 2, cornerRadius * 2, 90, 90);
	gdiPlusPath->AddLine(gdiPlusRect.X, gdiPlusRect.GetBottom() - cornerRadius * 2, gdiPlusRect.X, gdiPlusRect.Y + cornerRadius * 2);
	gdiPlusPath->CloseFigure();
	return gdiPlusPath;
}

CGdiPlusPaintMe::CGdiPlusPaintMe()
{
	m_bitmap = 0;
	m_brush = 0;
	m_brushColor = 0;
	m_emptyStringFormat = 0;
	m_endLineCap = 0;
	m_exportPath = L"";
	m_g = 0;
	m_hDC = 0;
	m_offsetX = 0;
	m_offsetY = 0;
	m_opacity = 1;
	m_path = 0;
	m_pen = 0;
	m_penColor = 0;
	m_penWidth = 0;
	m_penStyle = 0;
	m_pRect.left = 0;
	m_pRect.top = 0;
	m_pRect.right = 0;
	m_pRect.bottom = 0;
	m_resourcePath = L"";
	m_rotateAngle = 0;
	m_scaleFactorX = 0;
	m_scaleFactorY = 0;
	m_smoothMode = 2;
	m_startLineCap = 0;
	m_textQuality = 3;
	m_wRect.left = 0;
	m_wRect.top = 0;
	m_wRect.right = 0;
	m_wRect.bottom = 0;
}

CGdiPlusPaintMe::~CGdiPlusPaintMe()
{
	if(m_g)
	{
		delete m_g;
		m_g = 0;
	}
	if(m_bitmap)
	{
		delete m_bitmap;
		m_bitmap = 0;
	}
	ClearCaches();
}

void CGdiPlusPaintMe::AddArc( const RECT& rect, float startAngle, float sweepAngle )
{
	int rw = rect.right - rect.left - 1;
    if (rw < 1)
    {
        rw = 1;
    }
    int rh = rect.bottom - rect.top - 1;
    if (rh < 1)
    {
        rh = 1;
    }
	Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
    AffectScaleFactor(&gdiplusRect);
    m_path->AddArc(gdiplusRect, startAngle, sweepAngle);
}

void CGdiPlusPaintMe::AddBezier( POINT *apt, int cpt )
{
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_path->AddBezier(points[0], points[1], points[2], points[3]);
	delete[] points;
	points = 0;

}

void CGdiPlusPaintMe::AddCurve( POINT *apt, int cpt )
{
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_path->AddCurve(points, cpt);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::AddEllipse( const RECT& rect )
{
	int rw = rect.right - rect.left - 1;
    if (rw < 1)
    {
        rw = 1;
    }
    int rh = rect.bottom - rect.top - 1;
    if (rh < 1)
    {
        rh = 1;
    }
    Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiplusRect);
    m_path->AddEllipse(gdiplusRect);
}

void CGdiPlusPaintMe::AddLine( int x1, int y1, int x2, int y2 )
{
	int lx1 = x1 + m_offsetX;
	int ly1 = y1 + m_offsetY;
	int lx2 = x2 + m_offsetX;
	int ly2 = y2 + m_offsetY;
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		lx1 = (int)(m_scaleFactorX * lx1);
		ly1 = (int)(m_scaleFactorY * ly1);
		lx2 = (int)(m_scaleFactorX * lx2);
		ly2 = (int)(m_scaleFactorY * ly2);
	}
	m_path->AddLine(lx1, ly1, lx2, ly2);
}

void CGdiPlusPaintMe::AddRect( const RECT& rect )
{
    int rw = rect.right - rect.left - 1;
    if (rw < 1)
    {
        rw = 1;
    }
    int rh = rect.bottom - rect.top - 1;
    if (rh < 1)
    {
        rh = 1;
    }
    Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
    AffectScaleFactor(&gdiplusRect);
    m_path->AddRectangle(gdiplusRect);
}

void CGdiPlusPaintMe::AddPie( const RECT& rect, float startAngle, float sweepAngle )
{
	int rw = (rect.right - rect.left) - 1;
    if (rw < 1)
    {
        rw = 1;
    }
    int rh = (rect.bottom - rect.top) - 1;
    if (rh < 1)
    {
        rh = 1;
    }
    Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiplusRect);
    m_path->AddPie(gdiplusRect, startAngle, sweepAngle);
}

void CGdiPlusPaintMe::AddText( LPCWSTR strText, FONT *font, const RECT& rect )
{
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericTypographic();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		int strX = (int)(m_scaleFactorX * (rect.left + m_offsetX));
		int strY = (int)(m_scaleFactorY * (rect.top + m_offsetY));
		PointF gdiPlusPoint((REAL)strX, (REAL)strY);
		float fontSize = (float)(font->m_fontSize * (m_scaleFactorX + m_scaleFactorY) / 2);
		FONT scaleFont(font->m_fontFamily, fontSize, font->m_bold, font->m_underline, font->m_italic);
		Gdiplus::Font *gdiFont = GetFont(&scaleFont);
		FontFamily fontFamily;
		gdiFont->GetFamily(&fontFamily);
		m_path->AddString(strText, -1, &fontFamily, gdiFont->GetStyle(), gdiFont->GetSize(), gdiPlusPoint, m_emptyStringFormat);
		delete gdiFont;
		gdiFont = 0;
	}
	else
	{
		PointF gdiPlusPoint((REAL)(rect.left + m_offsetX), (REAL)(rect.top + m_offsetY));
		Gdiplus::Font *gdiFont = GetFont(font);
		FontFamily fontFamily;
		gdiFont->GetFamily(&fontFamily);
		m_path->AddString(strText, -1, &fontFamily, gdiFont->GetStyle(), gdiFont->GetSize(), gdiPlusPoint, m_emptyStringFormat);
		delete gdiFont;
		gdiFont = 0;
	}
}

void CGdiPlusPaintMe::BeginExport( const String& exportPath, const RECT& rect )
{
	m_exportPath = exportPath;
    int rw = rect.right - rect.left;
    int rh = rect.bottom - rect.top;
    if (rw == 0)
    {
        rw = 1;
    }
    if (rh == 0)
    {
        rh = 1;
	}
	if (m_bitmap)
	{
		delete m_bitmap;
		m_bitmap = 0;
	}
    if (m_g)
    {
		delete m_g;
		m_g = 0;
    }
    m_bitmap = new Bitmap(rw, rh);
	m_g = Graphics::FromImage(m_bitmap);
	SetSmoothMode(m_smoothMode);
    SetTextQuality(m_textQuality);
    m_opacity = 1;
    m_resourcePath = L"";
}

void CGdiPlusPaintMe::BeginPaint( HDC hDC, const RECT& wRect, const RECT& pRect )
{	
	m_pRect = pRect;
	m_wRect = wRect;
	int width = m_wRect.right - m_wRect.left;
	int height = m_wRect.bottom - m_wRect.top;
	if(!m_bitmap || width > (int)m_bitmap->GetWidth() || height > (int)m_bitmap->GetHeight())
	{
		int oldWidth = 0, oldHeight = 0;
		if(m_bitmap)
		{
			oldWidth = (int)m_bitmap->GetWidth();
			oldHeight = (int)m_bitmap->GetHeight();
			delete m_bitmap;
		}
		if(m_g)
		{
			delete m_g;
		}
		m_bitmap = new Bitmap(max(width, oldWidth), max(height, oldHeight));
		m_g = Graphics::FromImage(m_bitmap);
	}
	m_hDC = hDC;
	m_smoothMode = 0;
	m_textQuality = 0;
    SetSmoothMode(m_smoothMode);
    SetTextQuality(m_textQuality);
	m_opacity = 1;
	m_resourcePath = L"";
}

void CGdiPlusPaintMe::BeginPath()
{
    m_path = new GraphicsPath();
}

void CGdiPlusPaintMe::ClearCaches()
{
	if(m_brush)
	{
		delete m_brush;
		m_brush = 0;
	}
	if(m_emptyStringFormat)
	{
		delete m_emptyStringFormat;
		m_emptyStringFormat = 0;
	}
	std::map<wstring, Bitmap*>::iterator sIter = m_images.begin(); 
	for(;sIter != m_images.end(); ++sIter)
	{
		delete sIter->second;
	}
	m_images.clear();
	if(m_pen)
	{
		delete m_pen;
		m_pen = 0;
	}
	if(m_path)
	{
		delete m_path;
		m_path = 0;
	}
}

void CGdiPlusPaintMe::ClipPath()
{
    m_g->SetClip(m_path);
}

void CGdiPlusPaintMe::CloseFigure()
{
	m_path->CloseFigure();
}

void CGdiPlusPaintMe::ClosePath()
{
    delete m_path;
    m_path = 0;
}

void CGdiPlusPaintMe::DrawArc( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{
	if (dwPenColor = COLOR_EMPTY)
	{
		return;
	}
    int rw = (rect.right - rect.left) - 1;
    if (rw < 1)
    {
        rw = 1;
    }
    int rh = (rect.bottom - rect.top) - 1;
    if (rh < 1)
    {
        rh = 1;
    }
	Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
    AffectScaleFactor(&gdiplusRect);
    m_g->DrawArc(GetPen(dwPenColor, width, style), gdiplusRect, startAngle, sweepAngle);
}

void CGdiPlusPaintMe::DrawBezier( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if(dwPenColor == COLOR_EMPTY){
		return;
	}
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->DrawBezier(GetPen(dwPenColor, width, style), points[0], points[1], points[2], points[3]);
	m_g->SetSmoothingMode(SmoothingModeNone);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::DrawCurve( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if(dwPenColor == COLOR_EMPTY) 
	{
		return;
	}
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->DrawCurve(GetPen(dwPenColor, width, style), points, cpt);
	m_g->SetSmoothingMode(SmoothingModeNone);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, const RECT& rect )
{
	if (dwPenColor == COLOR_EMPTY)
	{
		return;
	}
	int rw = rect.right - rect.left - 1;
	if (rw < 1)
	{
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if (rh < 1)
	{
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->DrawEllipse(GetPen(dwPenColor, width, style), gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{
	RECT rect = {left, top, right, bottom};
	DrawEllipse(dwPenColor, width, style, rect);
}

void CGdiPlusPaintMe::DrawImage( LPCWSTR imagePath, const RECT& rect )
{
	m_g->SetSmoothingMode(SmoothingModeNone);
	wstring imageKey = m_resourcePath + imagePath;
	Bitmap *drawImage = 0;
	int rw = rect.right - rect.left;
	if(rw < 1) {
		rw = 1;
	}
	int rh = rect.bottom - rect.top;
	if(rh < 1){
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	if (m_images.find(imageKey) != m_images.end())
	{
		drawImage = m_images[imageKey];
	}
	else
	{
		wstring attributes[5];
		attributes[0] = L"file";
		attributes[1] = L"corner";
		attributes[2] = L"source";
		attributes[3] = L"highcolor";
		attributes[4] = L"lowcolor";
		wstring values[5];
		values[0] = imagePath;
		values[1] = L"";
		values[2] = L"";
		values[3] = L"";
		values[4] = L"";
		wstring wPath = imagePath;
		if (wPath.find(L"=") >= 0)
		{
			for (int i = 0; i < 5; i++)
			{
				wstring attribute = attributes[i];
				int alength = (int)attribute.length() + 2;
				int pos = (int)wPath.find(attribute + L"=\'");
				if (pos >= 0)
				{
					int rpos = (int)wPath.find(L"\'", pos + alength);
					values[i] = wPath.substr(pos + alength, rpos - pos - alength);
				}
			}
		}
		wstring file = values[0];
		string strFile;
		CStrMe::wstringTostring(strFile, file);
		if(_access(strFile.c_str(), 0) == -1)
		{
			if(m_resourcePath.length() > 0)
			{
				if(m_resourcePath.find(L"\\") == (int)m_resourcePath.length() - 1)
				{
					file = m_resourcePath + file;
				}
				else
				{
					file = m_resourcePath + L"\\" + file;
				}
			}
		}
		Bitmap *image = 0;
		if(values[2].length() > 0)
		{
			int source[4];
			vector<wstring> strs = CStrMe::Split(values[2], L",");
			int size = (int)strs.size();
			for (int i = 0; i < size; i++)
			{
				int pos = CStrMe::ConvertStrToInt(strs[i].c_str());
				source[i] = pos;
			}
			Rect gdiPlusSourceRect(source[0], source[1], source[2] - source[0], source[3] - source[1]);
			Bitmap *sourceImage = (Bitmap*)Bitmap::FromFile(file.c_str());
			if (sourceImage)
			{
				image = new Bitmap(gdiPlusSourceRect.Width, gdiPlusSourceRect.Height);
				Graphics *sg = Graphics::FromImage(image);
				Rect srcRect(0, 0, gdiPlusSourceRect.Width, gdiPlusSourceRect.Height);
				sg->DrawImage(sourceImage, srcRect, gdiPlusSourceRect.GetLeft(), gdiPlusSourceRect.GetTop(), gdiPlusSourceRect.Width, gdiPlusSourceRect.Height, UnitPixel);
				delete sg;
				delete sourceImage;
			}
		}
		else
		{
			image = (Bitmap*)Bitmap::FromFile(file.c_str());
		}
		if(image)
		{
			Gdiplus::ImageAttributes imageAttr;
			_int64 highColor = COLOR_EMPTY, lowColor = COLOR_EMPTY;
			if (values[3].length() != 0 && values[4].length() != 0)
			{
				highColor = CStrMe::ConvertStrToColor(values[3]);
				lowColor = CStrMe::ConvertStrToColor(values[4]);
			}
			if (highColor != COLOR_EMPTY && lowColor != COLOR_EMPTY)
			{
				int A = 0, R = 0, G = 0, B = 0;
				COLOR::ToARGB(this, highColor, &A, &R, &G, &B);
				Color gdiPlusHighColor((BYTE)A, (BYTE)R, (BYTE)G, (BYTE)B);
				COLOR::ToARGB(this, highColor, &A, &R, &G, &B);
				Color gdiPlusLowColor((BYTE)A, (BYTE)R, (BYTE)G, (BYTE)B);
				imageAttr.SetColorKey(gdiPlusLowColor, gdiPlusHighColor);
			}
			int iw = image->GetWidth();
			int ih = image->GetHeight();
			drawImage = new Bitmap(iw, ih);
			Graphics *g = Graphics::FromImage(drawImage);
			if (values[1].length() == 0)
			{
				Rect drawImageRect(0, 0, iw, ih);
				g->DrawImage(image, drawImageRect, 0, 0, iw, ih, UnitPixel, &imageAttr);
			}
			else
			{
				int corners[4];
				vector<wstring> strs = CStrMe::Split(values[1], L",");
				int size = (int)strs.size();
				for (int i = 0; i < size; i++)
				{
					int corner = CStrMe::ConvertStrToInt(strs[i].c_str());
					corners[i] = corner;
				}
				int left = 0;
				int top = 0;
				int right = iw;
				int bottom = ih;
				if (corners[0] > 0)
				{
					Rect destRect(left, top, corners[0], ih);
					g->DrawImage(image, destRect, 0, 0, corners[0], ih, UnitPixel, &imageAttr);
				}
				if (corners[1] > 0)
				{
					Rect destRect(left, top, iw, corners[1]);
					g->DrawImage(image, destRect, 0, 0, iw, corners[1], UnitPixel, &imageAttr);
				}
				if (corners[2] > 0)
				{
					Rect destRect(right - corners[2], top, corners[2], ih);
					g->DrawImage(image, destRect, iw - corners[2], 0, corners[2], ih, UnitPixel, &imageAttr);
				}
				if (corners[3] > 0)
				{
					Rect destRect(left, bottom - corners[3], iw, corners[3]);
					g->DrawImage(image, destRect, 0, ih - corners[3], iw, corners[3], UnitPixel, &imageAttr);
				}
				int cwdest = iw - corners[0] - corners[2];
				int chdest = ih - corners[1] - corners[3];
				int cwsrc = iw - corners[0] - corners[2];
				int chsrc = ih - corners[1] - corners[3];
				if (cwdest > 0 && chdest > 0 && cwsrc > 0 && chsrc > 0)
				{
					Rect destRect(left + corners[0], top + corners[1], cwdest, chdest);
					g->DrawImage(image, destRect, corners[0], corners[1], cwsrc, chsrc, UnitPixel, &imageAttr);
				}
			}
			delete image;
			delete g;
			m_images[imageKey] = drawImage;
		}
	}
	if(drawImage)
	{
		AffectScaleFactor(&gdiPlusRect);
		if(m_opacity < 1)
		{
			Gdiplus::ColorMatrix colorMatrix = 
			{
				1, 0, 0, 0, 0,
				0, 1, 0, 0, 0,
				0, 0, 1, 0, 0,
				0, 0, 0, m_opacity, 0,
				0, 0, 0, 0, 1
			};
			Gdiplus::ImageAttributes imageAtt;
			imageAtt.SetColorMatrix(&colorMatrix);
			m_g->DrawImage(drawImage, gdiPlusRect, 0, 0, drawImage->GetWidth(), drawImage->GetHeight(), UnitPixel, &imageAtt);
		}
		else
		{
			m_g->DrawImage(drawImage, gdiPlusRect, 0, 0, drawImage->GetWidth(), drawImage->GetHeight(), UnitPixel);
		}
	}
}

void CGdiPlusPaintMe::DrawLine( _int64 dwPenColor, float width, int style, const POINT& x, const POINT& y )
{
	DrawLine(dwPenColor, width, style, x.x, x.y, y.x, y.y);
}

void CGdiPlusPaintMe::DrawLine( _int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2 )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	int lx1 = x1 + m_offsetX;
	int ly1 = y1 + m_offsetY;
	int lx2 = x2 + m_offsetX;
	int ly2 = y2 + m_offsetY;
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		lx1 = (int)(m_scaleFactorX * (x1 + m_offsetX));
		ly1 = (int)(m_scaleFactorY * (y1 + m_offsetY));
		lx2 = (int)(m_scaleFactorX * (x2 + m_offsetX));
		ly2 = (int)(m_scaleFactorY * (y2 + m_offsetY));
	}
	if(style == 2)
	{
		if(dwPenColor == COLOR_EMPTY){
			return;
		}
		SolidBrush *brush = GetBrush(dwPenColor);
		m_g->SetSmoothingMode(SmoothingModeNone);
		vector<Rect> vecRect;
		int x = lx1, y = ly1, dx = lx2 - lx1, dy = -ly2 - ly1, p = 2 * dy - dx;
		int c = 4 * (dy - dx);
		int j = 4 * dy;
		for(; x < lx2; x += 6)
		{
			Rect rect(x, y, 1, 1);
			vecRect.push_back(rect);
			if(p >= 0)
			{
				y += 2;
				p += c;
			}
			else
			{
				p += j;
			}
		}
		int recSize = (int)vecRect.size();
		if(recSize > 0)
		{
			Rect* rects = new Rect[recSize];
			for(int i = 0; i < recSize; i++)
			{
				rects[i] = vecRect[i];
			}
			m_g->FillRectangles(brush, rects, recSize);
			delete [] rects;
			rects = 0;
		}
		vecRect.clear();
	}
	else
	{
		m_g->DrawLine(GetPen(dwPenColor, width, style), lx1, ly1, lx2, ly2);
	}
}

void CGdiPlusPaintMe::DrawPath( _int64 dwPenColor, float width, int style )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	m_g->DrawPath(GetPen(dwPenColor, width, style), m_path);
}

void CGdiPlusPaintMe::DrawPie( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}

	int rw = rect.right - rect.left - 1;
	if (rw < 1)
	{
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if (rh < 1)
	{
		rh = 1;
	}
	Gdiplus::Rect gdiplusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiplusRect);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->DrawPie(GetPen(dwPenColor, width, style), gdiplusRect, startAngle, sweepAngle);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::DrawPolygon( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_g->DrawPolygon(GetPen(dwPenColor, width, style), points, cpt);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::DrawPolyline( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_g->DrawLines(GetPen(dwPenColor, width, style), points, cpt);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::DrawRect( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{
	RECT rect = {left, top, right, bottom};
	DrawRect(dwPenColor, width, style, rect);
}

void CGdiPlusPaintMe::DrawRect( _int64 dwPenColor, float width, int style, const RECT& rect )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	int rw = rect.right - rect.left - 1;
	if(rw < 1){
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeNone);
	m_g->DrawRectangle(GetPen(dwPenColor, width, style), gdiPlusRect);
}

void CGdiPlusPaintMe::DrawRoundRect( _int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	int rw = rect.right - rect.left - 1;
	if(rw < 1) {
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	if(cornerRadius != 0)
	{
		GraphicsPath *gdiPlusPath = GetRoundRectPath(gdiPlusRect, cornerRadius);
		m_g->SetSmoothingMode(SmoothingModeAntiAlias);
		m_g->DrawPath(GetPen(dwPenColor, width, style), gdiPlusPath);
		m_g->SetSmoothingMode(SmoothingModeNone);
		delete gdiPlusPath;
	}
	else
	{
		m_g->SetSmoothingMode(SmoothingModeNone);
		m_g->DrawRectangle(GetPen(dwPenColor, width, style), gdiPlusRect);
	}
}

void CGdiPlusPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	m_g->SetSmoothingMode(SmoothingModeNone);
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericDefault();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		int strX = (int)(m_scaleFactorX * (rect.left + m_offsetX));
		int strY = (int)(m_scaleFactorY * (rect.top + m_offsetY));
		PointF gdiPlusPoint((REAL)strX, (REAL)strY);
		float fontSize = (float)(font->m_fontSize * (m_scaleFactorX + m_scaleFactorY) / 2);
		FONT scaleFont(font->m_fontFamily, fontSize, font->m_bold, font->m_underline, font->m_italic);
		Gdiplus::Font *gdiFont = GetFont(&scaleFont);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, GetBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
	else
	{
		PointF gdiPlusPoint((REAL)(rect.left + m_offsetX), (REAL)(rect.top + m_offsetY));
		Gdiplus::Font *gdiFont = GetFont(font);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, GetBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
}

void CGdiPlusPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	m_g->SetSmoothingMode(SmoothingModeNone);
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericDefault();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		float strX = (float)(m_scaleFactorX * (rect.left + m_offsetX));
		float strY = (float)(m_scaleFactorY * (rect.top + m_offsetY));
		PointF gdiPlusPoint((REAL)strX, (REAL)strY);
		float fontSize = (float)(font->m_fontSize * (m_scaleFactorX + m_scaleFactorY) / 2);
		FONT scaleFont(font->m_fontFamily, fontSize, font->m_bold, font->m_underline, font->m_italic);
		Gdiplus::Font *gdiFont = GetFont(&scaleFont);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, GetBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
	else
	{
		PointF gdiPlusPoint((REAL)(rect.left + m_offsetX), (REAL)(rect.top + m_offsetY));
		Gdiplus::Font *gdiFont = GetFont(font);
		m_g->DrawString(strText, -1, gdiFont, gdiPlusPoint, m_emptyStringFormat, GetBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
}

void CGdiPlusPaintMe::DrawTextAutoEllipsis( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	m_g->SetSmoothingMode(SmoothingModeNone);
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericDefault();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	int rw = rect.right - rect.left - 1;
	if(rw < 1){
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	m_emptyStringFormat->SetTrimming(::StringTrimmingEllipsisCharacter);
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		AffectScaleFactor(&gdiPlusRect);
		float fontSize = (float)(font->m_fontSize * (m_scaleFactorX + m_scaleFactorY) / 2);
		FONT scaleFont(font->m_fontFamily, fontSize, font->m_bold, font->m_underline, font->m_italic);
		Gdiplus::Font *gdiFont = GetFont(&scaleFont);
		RectF fRect((REAL)gdiPlusRect.X, (REAL)gdiPlusRect.Y, (REAL)gdiPlusRect.Width, (REAL)gdiPlusRect.Height);
		m_g->DrawString(strText, -1, gdiFont, fRect, m_emptyStringFormat, GetBrush(dwPenColor));
		delete gdiFont;
		gdiFont = 0;
	}
	else
	{
		RectF fRect((REAL)gdiPlusRect.X, (REAL)gdiPlusRect.Y, (REAL)gdiPlusRect.Width, (REAL)gdiPlusRect.Height);
		m_g->DrawString(strText, -1, GetFont(font), fRect, m_emptyStringFormat, GetBrush(dwPenColor));
	}
	m_emptyStringFormat->SetTrimming(::StringTrimmingNone);
}

void CGdiPlusPaintMe::EndExport()
{
	if (m_bitmap)
	{
		CLSID encoder;
		if (GetEncoderClsid(L"image/jpeg", &encoder))
		{
			m_bitmap->Save(m_exportPath.c_str(), &encoder, 0);
		}
	}
	if (m_g)
	{
		delete m_g;
		m_g = 0;
	}
	if (m_bitmap)
	{
		delete m_bitmap;
		m_bitmap = 0;
	}
	m_offsetX = 0;
	m_offsetY = 0;
	m_opacity = 1;
	m_resourcePath = L"";
}

void CGdiPlusPaintMe::EndPaint()
{
	Rect clipRect(m_pRect.left, m_pRect.top, m_pRect.right - m_pRect.left, m_pRect.bottom - m_pRect.top);
	AffectScaleFactor(&clipRect);
	int width = m_wRect.right - m_wRect.left;
	int height = m_wRect.bottom - m_wRect.top;
	if(clipRect.Width < width || clipRect.Height < height)
	{
		if(clipRect.X < m_wRect.left)
		{
			clipRect.Width += clipRect.X;
			clipRect.X = m_wRect.left;
		}
		if(clipRect.Y < m_wRect.top)
		{
			clipRect.Height += clipRect.Y;
			clipRect.Y = m_wRect.top;
		}
		if(clipRect.GetRight() > m_wRect.right)
		{
			clipRect.Width -= abs(clipRect.GetRight() - m_wRect.right);
		}
		if(clipRect.GetBottom() > m_wRect.bottom)
		{
			clipRect.Height -= abs(clipRect.GetBottom() - m_wRect.bottom);
		}
		if (clipRect.Width > 0 && clipRect.Height > 0)
		{
			HBITMAP bitmap = create_hbitmap_from_gdiplus_bitmap_ex(m_bitmap, clipRect);
			if(bitmap)
			{
				HDC hdcsource = CreateCompatibleDC(m_hDC);
				SelectObject(hdcsource, bitmap);
				StretchBlt(m_hDC, clipRect.X, clipRect.Y, clipRect.Width, clipRect.Height, hdcsource, 0, 0, clipRect.Width, clipRect.Height, 13369376);
				DeleteObject(bitmap);
				DeleteObject(hdcsource);
			}
		}
	}
	else
	{
		if (clipRect.Width > 0 && clipRect.Height > 0)
		{
			HBITMAP bitmap = create_hbitmap_from_gdiplus_bitmap_ex(m_bitmap, clipRect);
			if(bitmap)
			{
				HDC hdcsource = CreateCompatibleDC(m_hDC);
				SelectObject(hdcsource, bitmap);
				StretchBlt(m_hDC, clipRect.X, clipRect.Y, clipRect.Width, clipRect.Height, hdcsource, 0, 0, width, height, 13369376);
				DeleteObject(bitmap);
				DeleteObject(hdcsource);
			}
		}
	}
	m_hDC = 0;
	m_offsetX = 0;
	m_offsetY = 0;
	m_opacity = 1;
	m_resourcePath = L"";
}

void CGdiPlusPaintMe::ExcludeClipPath()
{
	Gdiplus::Region region(m_path);
	m_g->ExcludeClip(&region);
}

void CGdiPlusPaintMe::FillEllipse( _int64 dwPenColor, const RECT& rect )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rect.right - rect.left, rect.bottom - rect.top);
	AffectScaleFactor(&gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->FillEllipse(GetBrush(dwPenColor), gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::FillGradientEllipse( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{
	int rw = rect.right - rect.left - 1;
	if(rw < 1){
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	LinearGradientBrush lgb(gdiPlusRect, GetGdiPlusColor(dwFirst), GetGdiPlusColor(dwSecond), (REAL)angle, true);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->FillEllipse(&lgb, gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::FillGradientPath( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{
	int rw = rect.right - rect.left - 1;
	if(rw < 1) {
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	LinearGradientBrush lgb(gdiPlusRect, GetGdiPlusColor(dwFirst), GetGdiPlusColor(dwSecond), (REAL)angle, true);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);       
	m_g->FillPath(&lgb, m_path);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::FillGradientPolygon( _int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle )
{
	int left = 0, top = 0, right = 0, bottom = 0;
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		if (i == 0)
		{
			left = x;
			top = y;
			right = x;
			bottom = y;
		}
		else
		{
			if (x < left)
			{
				left = x;
			}
			if (y < top)
			{
				top = y;
			}
			if (x > right)
			{
				right = x;
			}
			if (y > bottom)
			{
				bottom = y;
			}
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	Rect gdiPlusRect(left, top, right - left, bottom - top);
	if(gdiPlusRect.Height > 0)
	{
		LinearGradientBrush lgb(gdiPlusRect, GetGdiPlusColor(dwFirst), GetGdiPlusColor(dwSecond), (REAL)angle, true);
		m_g->SetSmoothingMode(SmoothingModeAntiAlias);
		m_g->FillPolygon(&lgb, points, cpt);
		m_g->SetSmoothingMode(SmoothingModeNone);
	}
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::FillGradientRect( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle )
{
	int rw = rect.right - rect.left - 1;
	if(rw < 1) {
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if(rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	LinearGradientBrush lgb(gdiPlusRect, GetGdiPlusColor(dwFirst), GetGdiPlusColor(dwSecond), (REAL)angle, true);
	if(cornerRadius != 0)
	{
		GraphicsPath *gdiPlusPath = GetRoundRectPath(gdiPlusRect, cornerRadius);
		m_g->SetSmoothingMode(SmoothingModeAntiAlias);
		m_g->FillPath(&lgb, gdiPlusPath);
		m_g->SetSmoothingMode(SmoothingModeNone);
		delete gdiPlusPath;
	}
	else
	{
		m_g->FillRectangle(&lgb, gdiPlusRect);
	}
}

void CGdiPlusPaintMe::FillPath( _int64 dwPenColor )
{
	if(dwPenColor == COLOR_EMPTY){
		return;
	}
	m_g->FillPath(GetBrush(dwPenColor), m_path);
}

void CGdiPlusPaintMe::FillPie( _int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle )
{
	if(dwPenColor == COLOR_EMPTY){
		return;
	}
	int rw = rect.right - rect.left - 1;
	if (rw < 1) {
		rw = 1;
	}
	int rh = rect.bottom - rect.top - 1;
	if (rh < 1) {
		rh = 1;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rw, rh);
	AffectScaleFactor(&gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeAntiAlias);
	m_g->FillPie(GetBrush(dwPenColor), gdiPlusRect, startAngle, sweepAngle);
	m_g->SetSmoothingMode(SmoothingModeNone);
}

void CGdiPlusPaintMe::FillPolygon( _int64 dwPenColor, POINT *apt, int cpt )
{
	if(dwPenColor == COLOR_EMPTY){
		return;
	}
	Point *points = new Point[cpt];
	for(int i = 0; i < cpt; i++)
	{
		int x = apt[i].x + m_offsetX;
		int y = apt[i].y + m_offsetY;
		if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
		{
			x = (int)(m_scaleFactorX * x);
			y = (int)(m_scaleFactorY * y);
		}
		Point newPoint(x, y);
		points[i] = newPoint;
	}
	m_g->FillPolygon(GetBrush(dwPenColor), points, cpt);
	delete[] points;
	points = 0;
}

void CGdiPlusPaintMe::FillRect( _int64 dwPenColor, const RECT& rect )
{
	FillRect(dwPenColor, rect.left, rect.top, rect.right, rect.bottom);
}

void CGdiPlusPaintMe::FillRect( _int64 dwPenColor, int left, int top, int right, int bottom )
{
	if(dwPenColor == COLOR_EMPTY){
		return;
	}
	Rect gdiPlusRect(left + m_offsetX, top + m_offsetY, right - left, bottom - top);
	AffectScaleFactor(&gdiPlusRect);
	m_g->SetSmoothingMode(SmoothingModeNone);
	m_g->FillRectangle(GetBrush(dwPenColor), gdiPlusRect);
}

void CGdiPlusPaintMe::FillRoundRect( _int64 dwPenColor, const RECT& rect, int cornerRadius )
{
	if(dwPenColor == COLOR_EMPTY) {
		return;
	}
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rect.right - rect.left, rect.bottom - rect.top);
	AffectScaleFactor(&gdiPlusRect);
	if(cornerRadius != 0)
	{
		GraphicsPath *gdiPlusPath = GetRoundRectPath(gdiPlusRect, cornerRadius);
		m_g->SetSmoothingMode(SmoothingModeAntiAlias);
		m_g->FillPath(GetBrush(dwPenColor), gdiPlusPath);
		m_g->SetSmoothingMode(SmoothingModeNone);
		delete gdiPlusPath;
	}
	else
	{
		m_g->SetSmoothingMode(SmoothingModeNone);
		m_g->FillRectangle(GetBrush(dwPenColor), gdiPlusRect);
	}
}

_int64 CGdiPlusPaintMe::GetColor( _int64 dwPenColor )
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
		}
	}
	return dwPenColor;
}

_int64 CGdiPlusPaintMe::GetPaintColor( _int64 dwPenColor )
{   
	return GetColor(dwPenColor);
}

POINT CGdiPlusPaintMe::GetOffset()
{
	POINT offset = {m_offsetX, m_offsetY};
	return offset;
}

POINT CGdiPlusPaintMe::Rotate( const POINT& op, const POINT& mp, int angle )
{
	float PI = 3.14159265f;
	POINT pt = {0};
	pt.x = (int)((mp.x - op.x) * cos(angle * PI / 180) - (mp.y - op.y) * sin(angle * PI / 180) + op.x);
	pt.y = (int)((mp.x - op.x) * sin(angle * PI / 180) + (mp.y - op.y) * cos(angle * PI / 180) + op.y);
	return pt;
}

void CGdiPlusPaintMe::SetClip( const RECT& rect )
{
	Rect gdiPlusRect(rect.left + m_offsetX, rect.top + m_offsetY, rect.right - rect.left, rect.bottom - rect.top);
	if (m_scaleFactorX != 1 || m_scaleFactorY != 1)
	{
		gdiPlusRect.X = (int)floor(gdiPlusRect.X * m_scaleFactorX);
		gdiPlusRect.Y = (int)floor(gdiPlusRect.Y * m_scaleFactorY);
		gdiPlusRect.Width = (int)ceil(gdiPlusRect.Width * m_scaleFactorX);
		gdiPlusRect.Height = (int)ceil(gdiPlusRect.Height * m_scaleFactorY);
	}
	m_g->SetClip(gdiPlusRect);
}

void CGdiPlusPaintMe::SetLineCap( int startLineCap, int endLineCap )
{
	m_startLineCap = startLineCap;
	m_endLineCap = endLineCap;
	if (m_pen)
	{
		switch(m_startLineCap)
		{
		case 0:
			m_pen->SetStartCap(LineCapFlat);
			break;
		case 1:
			m_pen->SetStartCap(LineCapSquare);
			break;
		case 2:
			m_pen->SetStartCap(LineCapRound);
			break;
		case 3:
			m_pen->SetStartCap(LineCapTriangle);
			break;
		case 4:
			m_pen->SetStartCap(LineCapNoAnchor);
			break;
		case 5:
			m_pen->SetStartCap(LineCapSquareAnchor);
			break;
		case 6:
			m_pen->SetStartCap(LineCapRoundAnchor);
			break;
		case 7:
			m_pen->SetStartCap(LineCapDiamondAnchor);
			break;
		case 8:
			m_pen->SetStartCap(LineCapArrowAnchor);
			break;
		case 9:
			m_pen->SetStartCap(LineCapAnchorMask);
			break;
		case 10:
			m_pen->SetStartCap(LineCapCustom);
			break;
		}
		switch(m_endLineCap)
		{
		case 0:
			m_pen->SetEndCap(LineCapFlat);
			break;
		case 1:
			m_pen->SetEndCap(LineCapSquare);
			break;
		case 2:
			m_pen->SetEndCap(LineCapRound);
			break;
		case 3:
			m_pen->SetEndCap(LineCapTriangle);
			break;
		case 4:
			m_pen->SetEndCap(LineCapNoAnchor);
			break;
		case 5:
			m_pen->SetEndCap(LineCapSquareAnchor);
			break;
		case 6:
			m_pen->SetEndCap(LineCapRoundAnchor);
			break;
		case 7:
			m_pen->SetEndCap(LineCapDiamondAnchor);
			break;
		case 8:
			m_pen->SetEndCap(LineCapArrowAnchor);
			break;
		case 9:
			m_pen->SetEndCap(LineCapAnchorMask);
			break;
		case 10:
			m_pen->SetEndCap(LineCapCustom);
			break;
		}
	}
}

void CGdiPlusPaintMe::SetOffset( const POINT& offset )
{
	m_offsetX = offset.x;
	m_offsetY = offset.y;
}

void CGdiPlusPaintMe::SetOpacity( float opacity )
{
    m_opacity = opacity;
}

void CGdiPlusPaintMe::SetResourcePath( const String& resourcePath )
{
    m_resourcePath = resourcePath;
}

void CGdiPlusPaintMe::SetRotateAngle( int rotateAngle )
{
    m_rotateAngle = rotateAngle;
}

void CGdiPlusPaintMe::SetScaleFactor( double scaleFactorX, double scaleFactorY )
{
    m_scaleFactorX = scaleFactorX;
    m_scaleFactorY = scaleFactorY;
}

void CGdiPlusPaintMe::SetSmoothMode( int smoothMode )
{
	m_smoothMode = smoothMode;
	if (m_g)
	{
		switch (m_smoothMode)
		{
		case 0:
			m_g->SetSmoothingMode(SmoothingModeNone);
			break;
		case 1:
			m_g->SetSmoothingMode(SmoothingModeAntiAlias);
			break;
		case 2:
			m_g->SetSmoothingMode(SmoothingModeHighQuality);
			break;
		case 3:
			m_g->SetSmoothingMode(SmoothingModeHighSpeed);
			break;
		}
	}
}

void CGdiPlusPaintMe::SetTextQuality( int textQuality )
{
	m_textQuality = textQuality;
	if (m_g)
	{
		switch (m_textQuality)
		{
		case 0:
			m_g->SetTextRenderingHint(TextRenderingHintSystemDefault);
			break;
		case 1:
			m_g->SetTextRenderingHint(TextRenderingHintAntiAlias);
			break;
		case 2:
			m_g->SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
			break;
		case 3:
			m_g->SetTextRenderingHint(TextRenderingHintClearTypeGridFit);
			break;
		case 4:
			m_g->SetTextRenderingHint(TextRenderingHintSingleBitPerPixel);
			break;
		case 5:
			m_g->SetTextRenderingHint(TextRenderingHintSingleBitPerPixelGridFit);
			break;
		}
	}
}

bool CGdiPlusPaintMe::SupportTransparent()
{
	return true;
}

SIZE CGdiPlusPaintMe::TextSize( LPCWSTR strText, FONT *font )
{
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericDefault();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	SizeF layoutSize(0, 0);
	SizeF gdiPlusSize;
	Gdiplus::Font *gdiFont = GetFont(font);
	m_g->MeasureString(strText, -1, gdiFont, layoutSize, m_emptyStringFormat, &gdiPlusSize);
	SIZE size = {(long)gdiPlusSize.Width, (long)gdiPlusSize.Height};
	delete gdiFont;
	gdiFont = 0;
	return size;
}

SIZEF CGdiPlusPaintMe::TextSizeF( LPCWSTR strText, FONT *font )
{
	if(!m_emptyStringFormat)
	{
		m_emptyStringFormat = (StringFormat*)StringFormat::GenericDefault();
		m_emptyStringFormat->SetFormatFlags(::StringFormatFlagsMeasureTrailingSpaces);
	}
	SizeF layoutSize(0, 0);
	SizeF gdiPlusSize;
	Gdiplus::Font *gdiFont = GetFont(font);
	m_g->MeasureString(strText, -1, gdiFont, layoutSize, m_emptyStringFormat, &gdiPlusSize);
	if (wcslen(strText) == 1)
	{
		gdiPlusSize.Width = (float)floor(gdiPlusSize.Width * 2 / 3);
	}
	SIZEF size = {gdiPlusSize.Width, gdiPlusSize.Height};
	delete gdiFont;
	gdiFont = 0;
	return size;
}