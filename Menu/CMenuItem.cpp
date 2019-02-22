#include "..\\stdafx.h"
#include "..\\include\\Menu\\CMenuItem.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CMenuItemMe::CMenuItemMe()
{
	m_checked = false;
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
	m_text = L"";
	FONT font(L"ËÎÌו", 12, false, false, false);
	SetFont(&font);
	SIZE size = { 200, 25 };
	SetSize(size);
}

CMenuItemMe::CMenuItemMe(const String& text)
{
	m_checked = false;
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
	m_text = text;

	FONT font(L"ËÎÌו", 12, false, false, false);
	SetFont(&font);
	SIZE size = { 200, 25 };
	SetSize(size);
}

CMenuItemMe::~CMenuItemMe()
{
	ClearItems();
	m_dropDownMenu = 0;
	m_parentItem = 0;
	m_parentMenu = 0;
}

bool CMenuItemMe::IsChecked()
{
	return m_checked;
}

void CMenuItemMe::SetChecked(bool checked)
{
	m_checked = checked;
}

CMenuMe* CMenuItemMe::GetDropDownMenu()
{
	return m_dropDownMenu;
}

void CMenuItemMe::SetDropDownMenu(CMenuMe *dropDownMenu)
{
	m_dropDownMenu = dropDownMenu;
}

CMenuItemMe* CMenuItemMe::GetParentItem()
{
	return m_parentItem;
}

void CMenuItemMe::SetParentItem(CMenuItemMe *parentItem)
{
	m_parentItem = parentItem;
}

CMenuMe* CMenuItemMe::GetParentMenu()
{
	return m_parentMenu;
}

void CMenuItemMe::SetParentMenu(CMenuMe *parentMenu)
{
	m_parentMenu = parentMenu;
}

String CMenuItemMe::GetValue()
{
	return m_value;
}

void CMenuItemMe::SetValue(const String& value)
{
	m_value = value;
}

void CMenuItemMe::AddItem(CMenuItemMe *item)
{
	item->SetParentItem(this);
	item->SetParentMenu(GetParentMenu());
	item->OnAddingItem(-1);
	m_items.push_back(item);
}

void CMenuItemMe::ClearItems()
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

String CMenuItemMe::GetControlType()
{
	return L"MenuItem";
}

vector<CMenuItemMe*> CMenuItemMe::GetItems()
{
	return m_items;
}

void CMenuItemMe::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"checked")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsChecked());
	}
	else if (name == L"value")
	{
		*type = L"String";
		*value = GetValue();
	}
	else
	{
		CButtonMe::GetProperty(name, value, type);
	}
}

vector<String> CMenuItemMe::GetPropertyNames()
{
	vector<String> propertyNames = CButtonMe::GetPropertyNames();
	propertyNames.push_back(L"Checked");
	propertyNames.push_back(L"Value");
	return propertyNames;
}

void CMenuItemMe::InsertItem(int index, CMenuItemMe *item)
{
	item->SetParentItem(this);
	item->SetParentMenu(GetParentMenu());
	item->OnAddingItem(index);
	m_items.insert(m_items.begin() + index, item);
}

void CMenuItemMe::OnAddingItem(int index)
{
	CMenuMe *dropDownMenu = 0;
	if (m_parentItem)
	{
		dropDownMenu = m_parentItem->GetDropDownMenu();
		if (!dropDownMenu)
		{
			dropDownMenu = m_parentMenu->CreateDropDownMenu();
			dropDownMenu->SetVisible(false);
			m_parentItem->SetDropDownMenu(dropDownMenu);
			dropDownMenu->SetParentItem(m_parentItem);
			m_parentMenu->GetNative()->AddControl(dropDownMenu);
		}
	}
	else
	{
		dropDownMenu = m_parentMenu;
	}
	if (dropDownMenu)
	{
		if (index != -1)
		{
			dropDownMenu->InsertControl(index, this);
		}
		else
		{
			dropDownMenu->AddControl(this);
		}
		int itemSize = (int)m_items.size();
		for (int i = 0; i < itemSize; i++)
		{
			m_items[i]->OnAddingItem(-1);
		}
	}
}

void CMenuItemMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CButtonMe::OnClick(mp, button, clicks, delta);
	if (m_parentMenu)
	{
		m_parentMenu->OnMenuItemClick(this, mp, button, clicks, delta);
	}
}

void CMenuItemMe::OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	CButtonMe::OnMouseMove(mp, button, clicks, delta);
	if (m_parentMenu)
	{
		m_parentMenu->OnMenuItemMouseMove(this, mp, button, clicks, delta);
	}
}

void CMenuItemMe::OnPaintForeground(CPaintMe *paint, const RECT& clipRect)
{
	int width = GetWidth();
	int height = GetHeight();
	if (width > 0 && height > 0)
	{
		int right = width;
		int midY = height / 2;
		String text = GetText();
		int tRight = 0;
		_int64 foreColor = GetPaintingForeColor();
		if ((int)text.length() > 0)
		{
			FONT *font = GetFont();
			SIZE tSize = paint->TextSize(text.c_str(), font);
			RECT tRect;
			tRect.left = 10;
			tRect.top = (midY - tSize.cy / 2) + 2;
			tRect.right = tRect.left + tSize.cx;
			tRect.bottom = tRect.top + tSize.cy;
			paint->DrawText(text.c_str(), foreColor, font, tRect);
			tRight = tRect.right + 4;
		}
		if (m_checked)
		{
			RECT eRect = { tRight, height / 2 - 4, tRight + 8, height / 2 + 4 };
			paint->FillEllipse(foreColor, eRect);
		}
		int count = (int)m_items.size();
		if (count > 0)
		{
			POINT point = {0, 0};
			POINT point2 = {0, 0};
			POINT point3 = {0, 0};
			CMenuMe *parentMenu = m_parentMenu;
			if (m_parentItem)
			{
				parentMenu = m_parentItem->GetDropDownMenu();
			}
			switch (parentMenu->GetLayoutStyle())
			{
			case LayoutStyleMe_LeftToRight:
			case LayoutStyleMe_RightToLeft:
				point.x = right - 25;
				point.y = midY - 2;
				point2.x = right - 14;
				point2.y = midY - 2;
				point3.x = right - 20;
				point3.y = midY + 4;
				break;

			default:
				point.x = right - 15;
				point.y = midY;
				point2.x = right - 25;
				point2.y = midY - 5;
				point3.x = right - 25;
				point3.y = midY + 5;
				break;
			}
			POINT points[3] = { point, point2, point3 };
			paint->FillPolygon(foreColor, points, 3);
		}
	}
}

void CMenuItemMe::OnRemovingItem()
{
	CMenuMe *dropDownMenu;
	if (m_parentItem)
	{
		dropDownMenu = m_parentItem->GetDropDownMenu();
	}
	else
	{
		dropDownMenu = m_parentMenu;
	}
	if (dropDownMenu)
	{
		int count = (int)m_items.size();
		if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				m_items[i]->OnRemovingItem();
			}
		}
		dropDownMenu->RemoveControl(this);
	}
	if (m_dropDownMenu)
	{
		m_parentMenu->GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

void CMenuItemMe::RemoveItem(CMenuItemMe *item)
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

void CMenuItemMe::SetProperty(const String& name, const String& value)
{
	if (name == L"checked")
	{
		SetChecked(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"value")
	{
		SetValue(value);
	}
	else
	{
		CButtonMe::SetProperty(name, value);
	}
}