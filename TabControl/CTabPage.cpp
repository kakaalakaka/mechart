#include "..\\stdafx.h"
#include "..\\include\\TabControl\\CTabPage.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTabPageMe::DragHeaderBegin(void *sender, void *pInvoke)
{
	CTabPageMe *page = (CTabPageMe*)pInvoke;
	if(page)
	{
		CTabControlMe *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDragTabHeaderBegin(page);
		}
	}
}

void CTabPageMe::DragHeaderEnd(void *sender, void *pInvoke)
{
	CTabPageMe *page = (CTabPageMe*)pInvoke;
	if(page)
	{
		CTabControlMe *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDragTabHeaderEnd(page);
		}
	}
}

void CTabPageMe::DraggingHeader(void *sender, void *pInvoke)
{
	CTabPageMe *page = (CTabPageMe*)pInvoke;
	if(page)
	{
		CTabControlMe *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->OnDraggingTabHeader(page);
		}
	}
}

void CTabPageMe::HeaderMouseDown(void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke)
{
	CTabPageMe *page = (CTabPageMe*)pInvoke;
	if(page)
	{
		CTabControlMe *tabControl = page->GetTabControl();
		if(tabControl)
		{
			tabControl->SetSelectedTabPage(page);
			tabControl->Invalidate();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTabPageMe::CTabPageMe()
{
	m_headerButton = 0;
	m_headerLocation.x = 0;
	m_headerLocation.y = 0;
	m_tabControl = 0;

	m_dragHeaderBeginEvent = &DragHeaderBegin;
	m_dragHeaderEndEvent = &DragHeaderEnd;
	m_draggingHeaderEvent = &DraggingHeader;
	m_headerMouseDownEvent = &HeaderMouseDown;
}

CTabPageMe::~CTabPageMe()
{

	if (m_dragHeaderBeginEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_dragHeaderBeginEvent, EVENTID::DRAGBEGIN);
		}
		m_dragHeaderBeginEvent = 0;
	}
	if (m_dragHeaderEndEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_dragHeaderEndEvent, EVENTID::DRAGEND);
		}
		m_dragHeaderEndEvent = 0;
	}
	if (m_draggingHeaderEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_draggingHeaderEvent, EVENTID::DRAGGING);
		}
		m_draggingHeaderEvent = 0;
	}
	if (m_headerMouseDownEvent)
	{
		if (m_headerButton)
		{
			m_headerButton->UnRegisterEvent(m_headerMouseDownEvent, EVENTID::MOUSEDOWN);
		}
		m_headerMouseDownEvent = 0;
	}
	m_headerButton = 0;
	m_tabControl = 0;
}

CButtonMe* CTabPageMe::GetHeaderButton()
{
	return m_headerButton;
}

void CTabPageMe::SetHeaderButton(CButtonMe *headerButton)
{
	m_headerButton = headerButton;
}

POINT CTabPageMe::GetHeaderLocation()
{
	return m_headerLocation;
}

void CTabPageMe::SetHeaderLocation(POINT headerLocation)
{
	m_headerLocation = headerLocation;
}

bool CTabPageMe::IsHeaderVisible()
{
	return (m_headerButton && m_headerButton->IsVisible());
}

void CTabPageMe::SetHeaderVisible(bool visible)
{
	if (m_headerButton)
	{
		m_headerButton->SetVisible(visible);
	}
}

CTabControlMe* CTabPageMe::GetTabControl()
{
	return m_tabControl;
}

void CTabPageMe::SetTabControl(CTabControlMe *tabControl)
{
	m_tabControl = tabControl;
}

String CTabPageMe::GetControlType()
{
	return L"TabPage";
}

void CTabPageMe::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"headersize")
	{
		*type = L"size";
		if (m_headerButton)
		{
			*value = CStrMe::ConvertSizeToStr(m_headerButton->GetSize());
		}
		else
		{
			*value = L"0,0";
		}
	}
	else if (name == L"headervisible")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsHeaderVisible());
	}
	else if(name.find(L"header-") != -1)
	{
		if (m_headerButton)
		{
			m_headerButton->GetProperty(name.substr(7), value, type);
		}
	}
	else
	{
		DivMe::GetProperty(name, value, type);
	}
}

vector<String> CTabPageMe::GetPropertyNames()
{
	vector<String> propertyNames = DivMe::GetPropertyNames();
	propertyNames.push_back(L"Header");
	propertyNames.push_back(L"HeaderSize");
	propertyNames.push_back(L"HeaderVisible");
	return propertyNames;
}

void CTabPageMe::OnLoad()
{
	DivMe::OnLoad();
	if (m_tabControl)
	{
		if (!m_headerButton)
		{
			CControlHostMe *host = GetNative()->GetHost();
			m_headerButton = dynamic_cast<CButtonMe*>(host->CreateInternalControl(this, L"headerbutton"));
			m_headerButton->RegisterEvent(m_dragHeaderBeginEvent, EVENTID::DRAGBEGIN, this);
			m_headerButton->RegisterEvent(m_dragHeaderEndEvent, EVENTID::DRAGEND, this);
			m_headerButton->RegisterEvent(m_draggingHeaderEvent, EVENTID::DRAGGING, this);
			m_headerButton->RegisterEvent(m_headerMouseDownEvent, EVENTID::MOUSEDOWN, this);
		}
		if (!m_tabControl->ContainsControl(m_headerButton))
		{
			m_tabControl->AddControl(m_headerButton);
		}
	}
}

void CTabPageMe::OnTextChanged()
{
	DivMe::OnTextChanged();
	if (m_headerButton)
	{
		m_headerButton->SetText(GetText());
	}
}

void CTabPageMe::SetProperty(const String& name, const String& value)
{
	if (name == L"headersize")
	{
		if (m_headerButton)
		{
			m_headerButton->SetSize(CStrMe::ConvertStrToSize(value));
		}
	}
	else if (name == L"headervisible")
	{
		SetHeaderVisible(CStrMe::ConvertStrToBool(value));
	}
	else if(name.find(L"header-") != -1)
	{
		if (m_headerButton) 
		{
			m_headerButton->SetProperty(name.substr(7), value);
		}
	}
	else
	{
		DivMe::SetProperty(name, value);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////