#include "..\\stdafx.h"
#include "..\\include\\Base\\CPaint.h"

_int64 COLOR::ARGB( int r, int g, int b )
{
    return r | g << 8 | b << 16;
}

_int64 COLOR::ARGB( int a, int r, int g, int b )
{
    if (a == 255) 
	{
      return ARGB(r, g, b);
    }
    if (a == 0) 
	{
      return COLOR_EMPTY;
    }
    _int64 rgb = (_int64)ARGB(r, g, b);
    _int64 argb = -(rgb * 1000 + a);
    return argb;
}

void COLOR::ToARGB( CPaintMe *paint, _int64 dwPenColor, int *a, int *r, int *g, int *b )
{
	if (paint != 0)
    {
        dwPenColor = paint->GetColor(dwPenColor);
    }
    *a = 255;
    if (dwPenColor < 0L)
    {
        dwPenColor = abs((double)dwPenColor);
		if(dwPenColor >= 1)
		{
			*a = dwPenColor % 1000;
		}
		else
		{
			*a = 255;
		}
        dwPenColor /= 1000;
    }
    *r = (int) (dwPenColor & 0xffL);
    *g = (int) ((dwPenColor >> 8) & 0xffL);
    *b = (int) ((dwPenColor >> 16) & 0xffL);
}

_int64 COLOR::RatioColor( CPaintMe *paint, _int64 originalColor, double ratio )
{
	int a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    ToARGB(paint, originalColor, &a, &r, &g, &b);
    r = (int) (r * ratio);
    g = (int) (g * ratio);
    b = (int) (b * ratio);
    if (r > 255)
    {
        r = 255;
    }
    if (g > 255)
    {
        g = 255;
    }
    if (b > 255)
    {
        b = 255;
    }
    return ARGB(a, r, g, b);
}

_int64 COLOR::Reverse( CPaintMe *paint, _int64 originalColor )
{
    int a = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    ToARGB(paint, originalColor, &a, &r, &g, &b);
    return ARGB(a, 255 - r, 255 - g, 255 - b);
}

CPaintMe::CPaintMe()
{

}

CPaintMe::~CPaintMe()
{

}

void CPaintMe::AddArc( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaintMe::AddBezier( POINT *apt, int cpt )
{

}

void CPaintMe::AddCurve( POINT *apt, int cpt )
{

}

void CPaintMe::AddEllipse( const RECT& rect )
{

}

void CPaintMe::AddLine( int x1, int y1, int x2, int y2 )
{

}

void CPaintMe::AddRect( const RECT& rect )
{

}

void CPaintMe::AddPie( const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaintMe::AddText( LPCWSTR strText, FONT *font, const RECT& rect )
{

}

void CPaintMe::BeginExport( const String& exportPath, const RECT& rect )
{

}

void CPaintMe::BeginPaint( HDC hDC, const RECT& wRect, const RECT& pRect )
{

}

void CPaintMe::BeginPath()
{

}

void CPaintMe::ClearCaches()
{

}

void CPaintMe::ClipPath()
{

}

void CPaintMe::CloseFigure()
{

}

void CPaintMe::ClosePath()
{

}

void CPaintMe::DrawArc( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaintMe::DrawBezier( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaintMe::DrawCurve( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, const RECT& rect )
{

}

void CPaintMe::DrawEllipse( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{

}

void CPaintMe::DrawImage( LPCWSTR imagePath, const RECT& rect )
{

}

void CPaintMe::DrawLine( _int64 dwPenColor, float width, int style, const POINT& x, const POINT& y )
{

}

void CPaintMe::DrawLine( _int64 dwPenColor, float width, int style, int x1, int y1, int x2, int y2 )
{

}

void CPaintMe::DrawPath( _int64 dwPenColor, float width, int style )
{

}

void CPaintMe::DrawPie( _int64 dwPenColor, float width, int style, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaintMe::DrawPolygon( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaintMe::DrawPolyline( _int64 dwPenColor, float width, int style, POINT *apt, int cpt )
{

}

void CPaintMe::DrawRect( _int64 dwPenColor, float width, int style, int left, int top, int right, int bottom )
{

}

void CPaintMe::DrawRect( _int64 dwPenColor, float width, int style, const RECT& rect )
{

}

void CPaintMe::DrawRoundRect( _int64 dwPenColor, float width, int style, const RECT& rect, int cornerRadius )
{

}

void CPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{

}

void CPaintMe::DrawText( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECTF& rect )
{

}

void CPaintMe::DrawTextAutoEllipsis( LPCWSTR strText, _int64 dwPenColor, FONT *font, const RECT& rect )
{

}

void CPaintMe::EndExport()
{

}

void CPaintMe::EndPaint()
{

}

void CPaintMe::ExcludeClipPath()
{

}

void CPaintMe::FillEllipse( _int64 dwPenColor, const RECT& rect )
{

}

void CPaintMe::FillGradientEllipse( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{

}

void CPaintMe::FillGradientPath( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int angle )
{

}

void CPaintMe::FillGradientPolygon( _int64 dwFirst, _int64 dwSecond, POINT *apt, int cpt, int angle )
{

}

void CPaintMe::FillGradientRect( _int64 dwFirst, _int64 dwSecond, const RECT& rect, int cornerRadius, int angle )
{

}

void CPaintMe::FillPath( _int64 dwPenColor )
{

}

void CPaintMe::FillPie( _int64 dwPenColor, const RECT& rect, float startAngle, float sweepAngle )
{

}

void CPaintMe::FillPolygon( _int64 dwPenColor, POINT *apt, int cpt )
{

}

void CPaintMe::FillRect( _int64 dwPenColor, const RECT& rect )
{

}

void CPaintMe::FillRect( _int64 dwPenColor, int left, int top, int right, int bottom )
{

}

void CPaintMe::FillRoundRect( _int64 dwPenColor, const RECT& rect, int cornerRadius )
{

}

_int64 CPaintMe::GetColor( _int64 dwPenColor )
{
	return 0;
}

_int64 CPaintMe::GetPaintColor( _int64 dwPenColor )
{
	return 0;
}

POINT CPaintMe::GetOffset()
{
	return POINT();
}

POINT CPaintMe::Rotate( const POINT& op, const POINT& mp, int angle )
{
	return POINT();
}

void CPaintMe::SetClip( const RECT& rect )
{

}

void CPaintMe::SetLineCap( int startLineCap, int endLineCap )
{

}

void CPaintMe::SetOffset( const POINT& offset )
{

}

void CPaintMe::SetOpacity( float opacity )
{

}

void CPaintMe::SetResourcePath( const String& resourcePath )
{

}

void CPaintMe::SetRotateAngle( int rotateAngle )
{

}

void CPaintMe::SetScaleFactor( double scaleFactorX, double scaleFactorY )
{

}

void CPaintMe::SetSmoothMode( int smoothMode )
{

}

void CPaintMe::SetTextQuality( int textQuality )
{

}

bool CPaintMe::SupportTransparent()
{
	return false;
}

SIZE CPaintMe::TextSize( LPCWSTR strText, FONT *font )
{
	return SIZE();
}

SIZEF CPaintMe::TextSizeF( LPCWSTR strText, FONT *font )
{
	SIZEF sz = {0, 0};
	return sz;
}
