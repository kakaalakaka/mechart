#include "..\\stdafx.h"
#include "..\\include\\Layout\\CLayoutDiv.h"
using namespace MeLib;

CLayoutDivMe::CLayoutDivMe()
{
	m_autoWrap = false;
	m_layoutStyle = LayoutStyleMe_LeftToRight;
}

CLayoutDivMe::~CLayoutDivMe()
{

}

bool CLayoutDivMe::AutoWrap()
{
	return m_autoWrap;
}

void CLayoutDivMe::SetAutoWrap( bool autoWrap )
{
	m_autoWrap = autoWrap;
}

LayoutStyleMe CLayoutDivMe::GetLayoutStyle()
{
	return m_layoutStyle;
}

void CLayoutDivMe::SetLayoutStyle( LayoutStyleMe layoutStyle )
{
	m_layoutStyle = layoutStyle;
}

String CLayoutDivMe::GetControlType()
{
	return L"LayoutDiv";
}

void CLayoutDivMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"autowrap")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AutoWrap());
	}
	else if (name == L"layoutstyle")
	{
		*type = L"enum:LayoutStyleMe";
		*value = CStrMe::ConvertLayoutStyleToStr(GetLayoutStyle());
	}
	else
	{
		DivMe::GetProperty(name, value, type);
	}
}

vector<String> CLayoutDivMe::GetPropertyNames()
{
	vector<String> propertyNames = DivMe::GetPropertyNames();
	propertyNames.push_back(L"AutoWrap");
	propertyNames.push_back(L"LayoutStyle");
	return propertyNames;
}

bool CLayoutDivMe::OnResetLayout()
{
	bool reset = false;
	if (GetNative())
	{
		PADDING padding = GetPadding();
		int left = padding.left;
		int top = padding.top;
		int width = GetWidth() - padding.left - padding.right;
		int height = GetHeight() - padding.top - padding.bottom;
		int count = (int)m_controls.size();
		for (int i = 0; i < count; i++)
		{
			CControlMe *control = m_controls[i];
			if (!control->IsVisible() || control == GetHScrollBar() || control == GetVScrollBar())
			{
				continue;
			}
			SIZE size = control->GetSize();
			int cLeft = control->GetLeft();
			int cTop = control->GetTop();
			int cx = size.cx;
			int cy = size.cy;
			int nLeft = cLeft;
			int nTop = cTop;
			int nWidth = cx;
			int nHeight = cy;
			PADDING margin = control->GetMargin();
			switch (m_layoutStyle)
			{
			case LayoutStyleMe_BottomToTop:
				{
					if (i == 0)
					{
						top = padding.top + height;
					}
					int lWidth = 0;
					if (m_autoWrap)
					{
						lWidth = size.cx;
						int lTop = top - margin.top - cy - margin.bottom;
						if (lTop < padding.top)
						{
							left += cx + margin.left;
							top = height - padding.top;
						}
					}
					else
					{
						lWidth = width - margin.left - margin.right;
					}
					top -= cy + margin.bottom;
					nLeft = left + margin.left;
					nWidth = lWidth;
					nTop = top;
					break;
				}
			case LayoutStyleMe_LeftToRight:
				{
					int lHeight = 0;
					if (m_autoWrap)
					{
						lHeight = size.cy;
						int lRight = left + margin.left + cx + margin.right;
						if (lRight > width)
						{
							left = padding.left;
							top += cy + margin.top;
						}
					}
					else
					{
						lHeight = height - margin.top - margin.bottom;
					}
					left += margin.left;
					nLeft = left;
					nTop = top + margin.top;
					nHeight = lHeight;
					left += cx + margin.right;
					break;
				}
			case LayoutStyleMe_RightToLeft:
				{

					if (i == 0)
					{
						left = width - padding.left;
					}
					int lHeight = 0;
					if (m_autoWrap)
					{
						lHeight = size.cy;
						int lLeft = left - margin.left - cx - margin.right;
						if (lLeft < padding.left)
						{
							left = width - padding.left;
							top += cy + margin.top;
						}
					}
					else
					{
						lHeight = height - margin.top - margin.bottom;
					}
					left -= cx + margin.left;
					nLeft = left;
					nTop = top + margin.top;
					nHeight = lHeight;
					break;
				}
			case LayoutStyleMe_TopToBottom:
				{

					int lWidth = 0;
					if (m_autoWrap)
					{
						lWidth = size.cx;
						int lBottom = top + margin.top + cy + margin.bottom;
						if (lBottom > height)
						{
							left += cx + margin.left + margin.right;
							top = padding.top;
						}
					}
					else
					{
						lWidth = width - margin.left - margin.right;
					}
					top += margin.top;
					nTop = top;
					nLeft = left + margin.left;
					nWidth = lWidth;
					top += cy + margin.bottom;
					break;
				}
			default:
				break;
			}
			if (cLeft != nLeft || cTop != nTop || cx != nWidth || cy != nHeight)
			{
				RECT rect = {nLeft, nTop, nLeft + nWidth, nTop + nHeight};
				control->SetBounds(rect);
				reset = true;
			}
		}
	}
	return reset;
}

void CLayoutDivMe::SetProperty( const String& name, const String& value )
{
	if (name == L"autowrap")
	{
		SetAutoWrap(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"layoutstyle")
	{
		SetLayoutStyle(CStrMe::ConvertStrToLayoutStyle(value));
	}
	else
	{
		DivMe::SetProperty(name, value);
	}
}

void CLayoutDivMe::Update()
{
	OnResetLayout();
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->Update();
	}
	UpdateScrollBar();
}