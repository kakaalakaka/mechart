#include "..\\stdafx.h"
#include "..\\include\\Menu\\CMenu.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMenuMe::Adjust(CMenuMe *menu)
{
	CNativeBaseMe *native = GetNative();
	if (AutoSize())
	{
		int contentHeight = menu->GetContentHeight();
		int cy = GetMaximumSize().cy;
		menu->SetHeight(min(contentHeight, cy));
	}
	POINT location = menu->GetLocation();
	SIZE size = menu->GetSize();
	SIZE displaySize = native->GetDisplaySize();
	if (location.x < 0)
	{
		location.x = 0;
	}
	if (location.y < 0)
	{
		location.y = 0;
	}
	if (location.x + size.cx > displaySize.cx)
	{
		location.x = displaySize.cx - size.cx;
	}
	if (location.y + size.cy > displaySize.cy)
	{
		location.y = displaySize.cy - size.cy;
	}
	menu->SetLocation(location);
	menu->Update();
}

bool CMenuMe::CheckDivFocused(vector<CMenuItemMe*> items)
{
	int count = (int)items.size();
	for (int i = 0; i < count; i++)
	{
		CMenuItemMe *ma = items[i];
		CMenuMe *dropDownMenu = ma->GetDropDownMenu();
		if (dropDownMenu && CheckFocused(dropDownMenu))
		{
			return true;
		}
		vector<CMenuItemMe*> list = ma->GetItems();
		if (CheckDivFocused(list))
		{
			return true;
		}
	}
	return false;
}

bool CMenuMe::CheckFocused(CControlMe *control)
{
	if (control->IsFocused())
	{
		return true;
	}
	vector<CControlMe*> controls = control->GetControls();
	int count = (int)controls.size();
	if (count)
	{
		for (int i = 0; i < count; i++)
		{
			if (CheckFocused(controls[i]))
			{
				return true;
			}
		}
	}
	return false;
}

bool CMenuMe::CloseMenus(vector<CMenuItemMe*> items)
{
	int itemSize = (int)items.size();
	bool close = false;
	for (int i = 0; i < itemSize; i++)
	{
		CMenuItemMe *item = items[i];
		vector<CMenuItemMe*> list = item->GetItems();
		if (CloseMenus(list))
		{
			close = true;
		}
		CMenuMe *dropDownMenu = item->GetDropDownMenu();
		if ((dropDownMenu) && dropDownMenu->IsVisible())
		{
			dropDownMenu->Hide();
			close = true;
		}
	}
	return close;
}

void CMenuMe::CallMenuItemMouseEvent(int eventID, CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	map<int, vector<void*>*>::iterator sIter = CControlMe::m_events.find(eventID);
	map<int, vector<void*>*>::iterator sIterInvoker = CControlMe::m_invokes.find(eventID);
	if(sIter != CControlMe::m_events.end() && sIterInvoker != CControlMe::m_invokes.end())
	{
		vector<void*>* list = sIter->second;
		vector<void*>* invokerList = sIterInvoker->second;
 		int count = (int)list->size();
		int count2 = (int)invokerList->size();
		for(int i = 0; i < count; i++)
		{
			MenuItemMouseEvent event2 = (MenuItemMouseEvent)(*list)[i];
			if(event2)
			{
				(event2)(this, item, mp, button, clicks, delta, (*invokerList)[i]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMenuMe::CMenuMe()
{
	m_autoHide = true;
	m_parentItem = 0;
	m_popup = false;
	m_timerID = CControlMe::GetNewTimerID();
	SetAutoSize(true);
	SetLayoutStyle(LayoutStyleMe_TopToBottom);
	SIZE maxSize = { 2000, 500 };
	SetMaximumSize(maxSize);
	SetShowHScrollBar(true);
	SetShowVScrollBar(true);
	SetTopMost(true);
	SIZE size = { 200, 200 };
	SetSize(size);
}

CMenuMe::~CMenuMe()
{
	m_parentItem = 0;
	StopTimer(m_timerID);
	ClearItems();
}

bool CMenuMe::AutoHide()
{
	return m_autoHide;
}

void CMenuMe::SetAutoHide(bool autoHide)
{
	m_autoHide = autoHide;
}

CMenuItemMe* CMenuMe::GetParentItem()
{
	return m_parentItem;
}

void CMenuMe::SetParentItem(CMenuItemMe *parentItem)
{
	m_parentItem = parentItem;
}

bool CMenuMe::IsPopup()
{
	return m_popup;
}

void CMenuMe::SetPopup(bool popup)
{
	m_popup = popup;
	if(m_popup)
	{
		SetVisible(false);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMenuMe::AddItem(CMenuItemMe *item)
{
	item->SetParentMenu(this);
	item->OnAddingItem(-1);
	m_items.push_back(item);
}

void CMenuMe::ClearItems()
{
	vector<CMenuItemMe*> itemsCopy;
	int itemSize = (int)m_items.size();
	for (int i = 0; i < itemSize; i++)
	{
		itemsCopy.push_back(m_items[i]);
	}
	vector<CMenuItemMe*>::iterator sIter = itemsCopy.begin();
	for(; sIter != itemsCopy.end(); ++sIter)
	{
		(*sIter)->OnRemovingItem();
		delete *sIter;
		*sIter = 0;
	}
	itemsCopy.clear();
	m_items.clear();
}

CMenuMe* CMenuMe::CreateDropDownMenu()
{
	CMenuMe *menuA = new CMenuMe();
	menuA->SetPopup(true);
	menuA->SetShowHScrollBar(true);
	menuA->SetShowVScrollBar(true);
	return menuA;
}

String CMenuMe::GetControlType()
{
	return L"Menu";
}

vector<wstring> CMenuMe::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"MenuItemClick");
	return ws;
}

vector<CMenuItemMe*> CMenuMe::GetItems()
{
	return m_items;
}

void CMenuMe::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"popup")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsPopup());
	}
	else
	{
		CLayoutDivMe::GetProperty(name, value, type);
	}
}

vector<String> CMenuMe::GetPropertyNames()
{
	vector<String> propertyNames = CLayoutDivMe::GetPropertyNames();
	propertyNames.push_back(L"Popup");
	return propertyNames;
}

void CMenuMe::InsertItem(int index, CMenuItemMe *item)
{
	item->SetParentMenu(this);
	item->OnAddingItem(index);
	m_items.insert(m_items.begin() + index, item);
}

bool CMenuMe::OnAutoHide()
{
	return true;
}

void CMenuMe::OnLoad()
{
	CControlMe::OnLoad();
}

void CMenuMe::OnMenuItemClick(CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	if ((int)item->GetItems().size() == 0)
	{
		CallMenuItemMouseEvent(EVENTID::MENUITEMCLICK, item, mp, button, clicks, delta);
		CloseMenus(m_items);
		if (m_popup)
		{
			Hide();
		}
		else
		{
			GetNative()->Invalidate();
		}
	}
	else
	{
		OnMenuItemMouseMove(item, mp, button, clicks, delta);
	}
}

void CMenuMe::OnMenuItemMouseMove(CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CNativeBaseMe *native = GetNative();
	vector<CMenuItemMe*> items;
	CMenuItemMe *parentItem = item->GetParentItem();
	if (parentItem)
	{
		items = parentItem->GetItems();
	}
	else
	{
		items = m_items;
	}
	CloseMenus(items);
	if ((int)item->GetItems().size() > 0)
	{
		CMenuMe *dropDownMenu = item->GetDropDownMenu();
		if (dropDownMenu)
		{
			dropDownMenu->SetNative(native);
			LayoutStyleMe layoutStyle = GetLayoutStyle();
			POINT point = { native->ClientX(item) + item->GetWidth(), native->ClientY(item) };
			switch (layoutStyle)
			{
			case LayoutStyleMe_LeftToRight:
			case LayoutStyleMe_RightToLeft:
				point.x = native->ClientX(item);
				point.y = native->ClientY(item) + item->GetHeight();
				break;
			}
			dropDownMenu->SetOpacity(GetOpacity());
			dropDownMenu->SetLocation(point);
			dropDownMenu->BringToFront();
			dropDownMenu->Focus();
			dropDownMenu->Show();
			Adjust(dropDownMenu);
		}
	}
	native->Invalidate();
}

void CMenuMe::OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CLayoutDivMe::OnMouseDown(mp, button, clicks, delta);
	CloseMenus(m_items);
	GetNative()->Invalidate();
}

void CMenuMe::OnTimer(int timerID)
{
	CLayoutDivMe::OnTimer(timerID);
	if ((m_timerID == timerID && !m_parentItem
		&& IsVisible() && !CheckFocused(this))
		&& (!CheckDivFocused(m_items) && OnAutoHide()))
	{
		CloseMenus(m_items);
		if (m_popup)
		{
			Hide();
		}
		else
		{
			GetNative()->Invalidate();
		}
	}
}

void CMenuMe::OnVisibleChanged()
{
	CLayoutDivMe::OnVisibleChanged();
	if (IsVisible())
	{
		if (m_popup)
		{
			CHScrollBarMe *hScrollBar = GetHScrollBar();
			CVScrollBarMe *vScrollBar = GetVScrollBar();
			if (hScrollBar)
			{
				hScrollBar->SetPos(0);
			}
			if (vScrollBar)
			{
				vScrollBar->SetPos(0);
			}
			Focus();
			Adjust(this);
		}
		StartTimer(m_timerID, 10);
	}
	else
	{
		StopTimer(m_timerID);
		CloseMenus(m_items);
		CNativeBaseMe *native = GetNative();
		if (native)
		{
			native->Invalidate();
		}
	}
}

void CMenuMe::RemoveItem(CMenuItemMe *item)
{
	item->OnRemovingItem();
	vector<CMenuItemMe*>::iterator sIter = m_items.begin();
	for(; sIter != m_items.end(); ++sIter)
	{
		if(item = *sIter)
		{
			m_items.erase(sIter);
			delete *sIter;
			*sIter = 0;  
		}
	}
}

void CMenuMe::SetProperty(const String& name, const String& value)
{
	if (name == L"popup")
	{
		SetPopup(CStrMe::ConvertStrToBool(value));
	}
	else
	{
		CLayoutDivMe::SetProperty(name, value);
	}
}