#include "..\\stdafx.h"
#include "..\\include\\Window\\CWindowFrame.h"
using namespace MeLib;

CWindowFrameMe::CWindowFrameMe()
{
	SetBackColor(COLOR_EMPTY);
	SetBorderColor(COLOR_EMPTY);
	SetDock(DockStyleMe_Fill);
}

CWindowFrameMe::~CWindowFrameMe()
{
}

bool CWindowFrameMe::ContainsPoint( const POINT& point )
{
	vector<CControlMe*> controls = GetControls();
	int count = (int)controls.size();
	for (int i = 0; i < count; i++)
	{
		CWindowMe *window = dynamic_cast<CWindowMe*>(controls[i]);
		if (window && window->GetFrame() == this)
		{
			return (window->IsDialog() || window->ContainsPoint(point));
		}
	}
	return false;
}

String CWindowFrameMe::GetControlType()
{
	return L"WindowFrame";
}

void CWindowFrameMe::Invalidate()
{
	if (m_native)
	{
		vector<CControlMe*> controls = GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			CWindowMe *wa = dynamic_cast<CWindowMe*>(controls[i]);
			if (wa)
			{
				m_native->Invalidate(wa->GetDynamicPaintRect());
				return;
			}
		}
	}
}

void CWindowFrameMe::OnPaintBackground( CPaintMe *paint, const RECT& clipRect )
{
	CControlMe::OnPaintBackground(paint, clipRect);
	if (paint->SupportTransparent())
	{
		vector<CControlMe*> controls = GetControls();
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			CWindowMe *wa = dynamic_cast<CWindowMe*>(controls[i]);
			if (wa)
			{
				_int64 shadowColor = wa->GetShadowColor();
				int shadowSize = wa->GetShadowSize();
				if (shadowColor != COLOR_EMPTY && shadowSize > 0 && wa->IsDialog() && wa->GetFrame() == this)
				{
					RECT bounds = wa->GetBounds();
					RECT rect;
					rect.left = bounds.left - shadowSize;
					rect.top = bounds.top - shadowSize;
					rect.right = bounds.left;
					rect.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect);

					RECT rect3;
					rect3.left = bounds.right;
					rect3.top = bounds.top - shadowSize;
					rect3.right = bounds.right + shadowSize;
					rect3.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect3);

					RECT rect4;
					rect4.left = bounds.left;
					rect4.top = bounds.top - shadowSize;
					rect4.right = bounds.right;
					rect4.bottom = bounds.top;
					paint->FillRect(shadowColor, rect4);

					RECT rect5;
					rect5.left = bounds.left;
					rect5.top = bounds.bottom;
					rect5.right = bounds.right;
					rect5.bottom = bounds.bottom + shadowSize;
					paint->FillRect(shadowColor, rect5);
					return;
				}
			}
		}
	}
}
