#include "..\\stdafx.h"
#include "..\\include\\Layout\\CSplitLayoutDiv.h"
using namespace MeLib;

void CSplitLayoutDivMe::SplitterDragging( void *sender, void *pInvoke )
{
	CSplitLayoutDivMe* div = (CSplitLayoutDivMe*)pInvoke;
	if(div)
	{
		div->OnSplitterDragging();
	}
}

CSplitLayoutDivMe::CSplitLayoutDivMe()
{
	m_oldSize.cx = 0;
	m_oldSize.cy = 0;
	m_firstControl = 0;
	m_secondControl = 0;
	m_splitMode = SizeTypeMe_AbsoluteSize;
	m_splitPercent = -1.0f;
	m_splitter = 0;
	m_splitterDraggingEvent = &SplitterDragging;
}

CSplitLayoutDivMe::~CSplitLayoutDivMe()
{
	m_firstControl = 0;
	m_secondControl = 0;
	if (m_splitter && m_splitterDraggingEvent)
	{
		m_splitter->UnRegisterEvent(m_splitterDraggingEvent, EVENTID::DRAGGING);
		m_splitterDraggingEvent = 0;
	}
	m_splitter = 0;
}

CControlMe* CSplitLayoutDivMe::GetFirstControl()
{
	return m_firstControl;
}

void CSplitLayoutDivMe::SetFirstControl( CControlMe *firstControl )
{
	m_firstControl = firstControl;
}

CControlMe* CSplitLayoutDivMe::GetSecondControl()
{
	return m_secondControl;
}

void CSplitLayoutDivMe::SetSecondControl( CControlMe *secondControl )
{
	m_secondControl = secondControl;
}

SizeTypeMe CSplitLayoutDivMe::GetSplitMode()
{
	return m_splitMode;
}

void CSplitLayoutDivMe::SetSplitMode( SizeTypeMe splitMode )
{
	m_splitMode = splitMode;
}

CButtonMe* CSplitLayoutDivMe::GetSplitter()
{
	return m_splitter;
}

String CSplitLayoutDivMe::GetControlType()
{
	return L"SplitLayoutDiv";
}

void CSplitLayoutDivMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"candragsplitter")
	{
		*type = L"bool";
		if (m_splitter)
		{
			*value = CStrMe::ConvertBoolToStr(m_splitter->AllowDrag());
		}
		else
		{
			*value = L"False";
		}
	}
	else if (name == L"splitmode")
	{
		*type = L"enum:SizeTypeMe";
		if (GetSplitMode() == SizeTypeMe_AbsoluteSize)
		{
			*value = L"AbsoluteSize";
		}
		else
		{
			*value = L"PercentSize";
		}
	}
	else if (name.find(L"splitter-") != -1)
	{
		if (m_splitter)
		{
			m_splitter->GetProperty(name.substr(9), value, type);
		}
	}
	else if (name == L"splitterposition")
	{
		*type = L"rect";
		if (m_splitter)
		{
			*value = CStrMe::ConvertRectToStr(m_splitter->GetBounds());
		}
		*value = L"0,0,0,0";
	}
	else if (name == L"splittervisible")
	{
		*type = L"bool";
		if (m_splitter)
		{
			*value = CStrMe::ConvertBoolToStr(m_splitter->IsVisible());
		}
		else
		{
			*value = L"False";
		}
	}
	else
	{
		CLayoutDivMe::GetProperty(name, value, type);
	}
}

vector<String> CSplitLayoutDivMe::GetPropertyNames()
{
	vector<String> propertyNames = CLayoutDivMe::GetPropertyNames();
	propertyNames.push_back(L"CanDragSplitter");
	propertyNames.push_back(L"SplitMode");
	propertyNames.push_back(L"Splitter");
	propertyNames.push_back(L"SplitterPosition");
	propertyNames.push_back(L"SplitterVisible");
	return propertyNames;
}

void CSplitLayoutDivMe::OnLoad()
{
	CControlMe::OnLoad();
	if (!m_splitter)
	{
		CControlHostMe *host = GetNative()->GetHost();
		m_splitter = (CButtonMe*)host->CreateInternalControl(this, L"splitter");
		m_splitter->RegisterEvent(m_splitterDraggingEvent, EVENTID::DRAGGING, this);
		AddControl(m_splitter);
	}
	m_oldSize = GetSize();
}

bool CSplitLayoutDivMe::OnResetLayout()
{
	bool flag = false;
	if (!GetNative() || !m_splitter || !m_firstControl|| !m_secondControl)
	{
		m_oldSize = GetSize();
		return flag;
	}
	RECT rect = {0, 0, 0, 0};
	int width = GetWidth();
	int height = GetHeight();
	RECT fRect = {0, 0, 0, 0};
	RECT sRect = {0, 0, 0, 0};
	SIZE size = {0, 0};
	if (m_splitter->IsVisible())
	{
		size.cx = m_splitter->GetWidth();
		size.cy = m_splitter->GetHeight();
	}
	LayoutStyleMe layoutStyle = GetLayoutStyle();
	switch (layoutStyle)
	{
	case LayoutStyleMe_BottomToTop:
		
		if ((m_splitMode != SizeTypeMe_AbsoluteSize) && (m_oldSize.cy != 0))
		{
			if (m_splitMode == SizeTypeMe_PercentSize)
			{
				rect.left = 0;
				if (CStrMe::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = (m_splitter->GetTop() / m_oldSize.cy);
				}
				rect.top = ((int)(height * m_splitPercent));
				rect.right = width;
				rect.bottom = rect.top + size.cy;
			}
		}
		else
		{
			rect.left = 0;
			rect.top = (height - (m_oldSize.cy - m_splitter->GetTop()));
			rect.right = width;
			rect.bottom = rect.top + size.cy;
		}
		fRect.left = 0;
		fRect.top = rect.bottom;
		fRect.right = width;
		fRect.bottom = height;
		sRect.left = 0;
		sRect.top = 0;
		sRect.right = width;
		sRect.bottom = rect.top;
		break;

	case LayoutStyleMe_LeftToRight:
		if ((m_splitMode != SizeTypeMe_AbsoluteSize) && (m_oldSize.cx != 0))
		{
			if (m_splitMode == SizeTypeMe_PercentSize)
			{
				if (CStrMe::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetLeft()) / ((float) m_oldSize.cx);
				}
				rect.left = (int) (width * m_splitPercent);
				rect.top = 0;
				rect.right = rect.left + size.cx;
				rect.bottom = height;
			}
		}
		else
		{
			rect.left = m_splitter->GetLeft();
			rect.top = 0;
			rect.right = rect.left + size.cx;
			rect.bottom = height;
		}
		fRect.left = 0;
		fRect.top = 0;
		fRect.right = rect.left;
		fRect.bottom = height;
		sRect.left = rect.right;
		sRect.top = 0;
		sRect.right = width;
		sRect.bottom = height;
        break;

	case LayoutStyleMe_RightToLeft:
		if ((m_splitMode != SizeTypeMe_AbsoluteSize) && (m_oldSize.cx != 0))
		{
			if (m_splitMode == SizeTypeMe_PercentSize)
			{
				if (CStrMe::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetLeft()) / ((float) m_oldSize.cx);
				}
				rect.left = (int) (width * m_splitPercent);
				rect.top = 0;
				rect.right = rect.left + size.cx;
				rect.bottom = height;
			}
		}
		else
		{
			rect.left = width - (m_oldSize.cx - m_splitter->GetLeft());
			rect.top = 0;
			rect.right = rect.left + size.cx;
			rect.bottom = height;
		}
		fRect.left = rect.right;
		fRect.top = 0;
		fRect.right = width;
		fRect.bottom = height;
		sRect.left = 0;
		sRect.top = 0;
		sRect.right = rect.left;
		sRect.bottom = height;
        break;

	case LayoutStyleMe_TopToBottom:
		if ((m_splitMode != SizeTypeMe_AbsoluteSize) && (m_oldSize.cy != 0))
		{
			if (m_splitMode == SizeTypeMe_PercentSize)
			{
				rect.left = 0;
				if (CStrMe::ValueEqual(m_splitPercent, -1.0f))
				{
					m_splitPercent = ((float) m_splitter->GetTop()) / ((float) m_oldSize.cy);
				}
				rect.top = (int) (height * m_splitPercent);
				rect.right = width;
				rect.bottom = rect.top + size.cy;
			}
		}
		else
		{
			rect.left = 0;
			rect.top = m_splitter->GetTop();
			rect.right = width;
			rect.bottom = rect.top + size.cy;
		}
		fRect.left = 0;
		fRect.top = 0;
		fRect.right = width;
		fRect.bottom = rect.top;
		sRect.left = 0;
		sRect.top = rect.bottom;
		sRect.right = width;
		sRect.bottom = height;
        break;

	default:
        break;
	}
	if (m_splitter->IsVisible())
	{
		RECT spRect = m_splitter->GetBounds();
		if ((spRect.left != rect.left || spRect.top != rect.top) || (spRect.right != rect.right || spRect.bottom != rect.bottom))
		{
			m_splitter->SetBounds(rect);
			flag = true;
		}
		if (m_splitter->AllowDrag())
		{
			switch (layoutStyle)
			{
			case LayoutStyleMe_LeftToRight:
			case LayoutStyleMe_RightToLeft:
				m_splitter->SetCursor(CursorsMe_SizeWE);
				break;

			default:
				m_splitter->SetCursor(CursorsMe_SizeNS);
				break;
			}
			m_splitter->BringToFront();
		}
	}
	RECT bounds = m_firstControl->GetBounds();
	if ((bounds.left != fRect.left || bounds.top != fRect.top) || (bounds.right != fRect.right || bounds.bottom != fRect.bottom))
	{
		flag = true;
		m_firstControl->SetBounds(fRect);
		m_firstControl->Update();
	}
	RECT scRect = m_secondControl->GetBounds();
	if ((scRect.left != sRect.left || scRect.top != sRect.top) || (scRect.right != sRect.right || scRect.bottom != sRect.bottom))
	{
		flag = true;
		m_secondControl->SetBounds(sRect);
		m_secondControl->Update();
	}
	m_oldSize = GetSize();
	return flag;
}

void CSplitLayoutDivMe::OnSplitterDragging()
{
	m_splitPercent = -1.0f;
	Update();
	Invalidate();
}

void CSplitLayoutDivMe::SetProperty( const String& name, const String& value )
{
	if (name == L"candragsplitter")
	{
		if (m_splitter)
		{
			m_splitter->SetAllowDrag(CStrMe::ConvertStrToBool(value));
		}
	}
	else if (name == L"splitmode")
	{
		String temp = CStrMe::ToLower(value);
		if (temp == L"absolutesize")
		{
			SetSplitMode(SizeTypeMe_AbsoluteSize);
		}
		else
		{
			SetSplitMode(SizeTypeMe_PercentSize);
		}
	}
	else if (name.find(L"splitter-") != -1)
	{
		if (m_splitter)
		{
			m_splitter->SetProperty(name.substr(9), value);
		}
	}
	else if (name == L"splitterposition")
	{
		if (m_splitter)
		{
			m_splitter->SetBounds(CStrMe::ConvertStrToRect(value));
		}
	}
	else if (name == L"splittervisible")
	{
		if (m_splitter)
		{
			m_splitter->SetVisible(CStrMe::ConvertStrToBool(value));
		}
	}
	else
	{
		CLayoutDivMe::SetProperty(name, value);
	}
}

void CSplitLayoutDivMe::Update()
{
	OnResetLayout();
	int count = (int)m_controls.size();
	for (int i = 0; i < count; i++)
	{
		m_controls[i]->Update();
	}
}