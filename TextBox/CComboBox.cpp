#include "..\\stdafx.h"
#include "..\\include\\TextBox\\CComboBox.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CComboBoxMenuMe::CComboBoxMenuMe()
{
	m_comboBox = 0;
}

CComboBoxMenuMe::~CComboBoxMenuMe()
{
	m_comboBox = 0;
}

CComboBoxMe* CComboBoxMenuMe::GetComboBox()
{
	return m_comboBox;
}

void CComboBoxMenuMe::SetComboBox( CComboBoxMe *comboBox )
{
	m_comboBox = comboBox;
}

bool CComboBoxMenuMe::OnAutoHide()
{
	if (m_comboBox && m_comboBox->IsFocused())
	{
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CComboBoxMe::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CComboBoxMe *pThis = (CComboBoxMe*)pInvoke;
	if(pThis)
	{
		pThis->OnDropDownOpening();
	}
}

void CComboBoxMe::MenuItemClick( void *sender, CMenuItemMe *item, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CComboBoxMe *pThis = (CComboBoxMe *)pInvoke;
	if(pThis)
	{
		pThis->SetText(item->GetText());
		vector<CMenuItemMe*> items = pThis->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			if (items[i] == item)
			{
				pThis->SetSelectedIndex(i);
				break;
			}
		}
		pThis->SetSelectionStart((int)pThis->GetText().length());
		pThis->Invalidate();
	}
}

void CComboBoxMe::MenuKeyDown( void *sender, char key, void *pInvoke )
{
	if (key == '\r')
	{
		CComboBoxMe *pThis = (CComboBoxMe*)sender;
		if(pThis)
		{
			pThis->OnSelectedIndexChanged();
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CComboBoxMe::CComboBoxMe()
{
	m_dropDownButton = 0;
	m_dropDownMenu = 0;
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_menuItemClickEvent = &MenuItemClick;
	m_menuKeyDownEvent = &MenuKeyDown;
}

CComboBoxMe::~CComboBoxMe()
{
	if (m_dropDownButton && m_dropDownButtonMouseDownEvent)
	{
		m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN);
		m_dropDownButtonMouseDownEvent = 0;
	}
	if (m_dropDownMenu)
	{
		if (m_menuItemClickEvent)
		{
			m_dropDownMenu->UnRegisterEvent(m_menuItemClickEvent, EVENTID::MENUITEMCLICK);
			m_menuItemClickEvent = 0;
		}
		if (m_menuKeyDownEvent)
		{
			m_dropDownMenu->UnRegisterEvent(m_menuKeyDownEvent, EVENTID::KEYDOWN);
			m_menuKeyDownEvent = 0;
		}
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

CButtonMe* CComboBoxMe::GetDropDownButton()
{
	return m_dropDownButton;
}

CComboBoxMenuMe* CComboBoxMe::GetDropDownMenu()
{
	return m_dropDownMenu;
}

int CComboBoxMe::GetSelectedIndex()
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return i;
			}
		}
	}
	return -1;
}

void CComboBoxMe::SetSelectedIndex( int selectedIndex )
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (i == selectedIndex)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

String CComboBoxMe::GetSelectedText()
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return menuItemA->GetText();
			}
		}
	}
	return L"";
}

void CComboBoxMe::SetSelectedText( const String& selectedText )
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (menuItemA->GetText() == selectedText)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

String CComboBoxMe::GetSelectedValue()
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (menuItemA->IsChecked())
			{
				return menuItemA->GetValue();
			}
		}
	}
	return L"";
}

void CComboBoxMe::SetSelectedValue( const String& selectedValue )
{
	if (m_dropDownMenu)
	{
		vector<CMenuItemMe*> items = m_dropDownMenu->GetItems();
		int count = (int)items.size();
		bool flag = false;
		for (int i = 0; i < count; i++)
		{
			CMenuItemMe *menuItemA = items[i];
			if (menuItemA->GetValue() == selectedValue)
			{
				if (!menuItemA->IsChecked())
				{
					flag = true;
					menuItemA->SetChecked(true);
				}
				SetText(menuItemA->GetText());
			}
			else
			{
				menuItemA->SetChecked(false);
			}
		}
		if (flag)
		{
			OnSelectedIndexChanged();
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CComboBoxMe::AddItem( CMenuItemMe *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->AddItem(item);
	}
}

void CComboBoxMe::ClearItems()
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->ClearItems();
	}
}

String CComboBoxMe::GetControlType()
{
	return L"ComboBox";
}

vector<wstring> CComboBoxMe::GetEventNames()
{
	vector<wstring> ws;
	ws.push_back(L"SelectedIndexChanged");
	return ws;
}

vector<CMenuItemMe*> CComboBoxMe::GetItems()
{
	if (m_dropDownMenu)
	{
		return m_dropDownMenu->GetItems();
	}
	return vector<CMenuItemMe*>();
}

void CComboBoxMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"selectedindex")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetSelectedIndex());
	}
	else if (name == L"selectedtext")
	{
		*type = L"text";
		*value = GetSelectedText();
	}
	else if (name == L"selectedvalue")
	{
		*type = L"text";
		*value = GetSelectedValue();
	}
	else
	{
		CTextBoxMe::GetProperty(name, value, type);
	}
}

vector<String> CComboBoxMe::GetPropertyNames()
{
	vector<String> propertyNames = CTextBoxMe::GetPropertyNames();
	propertyNames.push_back(L"SelectedIndex");
	propertyNames.push_back(L"SelectedText");
	propertyNames.push_back(L"SelectedValue");
	return propertyNames;
}

void CComboBoxMe::InsertItem( int index, CMenuItemMe *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->InsertItem(index, item);
	}
}

void CComboBoxMe::OnDropDownOpening()
{
	m_dropDownMenu->SetNative(GetNative());
	POINT pp = {0, GetHeight()};
	POINT point = PointToNative(pp);
	m_dropDownMenu->SetLocation(point);
	SIZE sz = {GetWidth(), m_dropDownMenu->GetContentHeight()};
	m_dropDownMenu->SetSize(sz);
	m_dropDownMenu->SetVisible(true);
	m_dropDownMenu->BringToFront();
	m_dropDownMenu->Invalidate();
}

void CComboBoxMe::OnKeyDown( char key )
{
	CTextBoxMe::OnKeyDown(key);
	CControlHostMe *host = GetNative()->GetHost();
	if ((((!host->IsKeyPress(0x10) 
		&& !host->IsKeyPress(0x11)) 
		&& (!host->IsKeyPress(0x12) 
		&& GetLinesCount() <= 1)) 
		&& (((key == '\r') || (key == '&')) || (key == '(')))
		&& m_dropDownMenu)
	{
		m_dropDownMenu->OnKeyDown(key);
	}
}

void CComboBoxMe::OnLoad()
{
	CTextBoxMe::OnLoad();
	CControlHostMe *host = GetNative()->GetHost();
	if (!m_dropDownButton)
	{
		m_dropDownButton = (CButtonMe*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
	}
	if (!m_dropDownMenu)
	{
		m_dropDownMenu = (CComboBoxMenuMe*)host->CreateInternalControl(this, L"dropdownmenu");
		GetNative()->AddControl(m_dropDownMenu);
		m_dropDownMenu->SetVisible(false);
		m_dropDownMenu->RegisterEvent(m_menuItemClickEvent, EVENTID::MENUITEMCLICK, this);
		m_dropDownMenu->RegisterEvent(m_menuKeyDownEvent, EVENTID::KEYDOWN, this);
	}
	else
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void CComboBoxMe::OnSelectedIndexChanged()
{
	CallEvents(EVENTID::SELECTEDINDEXCHANGED);
}

void CComboBoxMe::OnMouseWheel( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CTextBoxMe::OnMouseWheel(mp, button, clicks, delta);
	if (GetLinesCount() <= 1 && m_dropDownMenu)
	{
		m_dropDownMenu->OnMouseWheel(m_dropDownMenu->GetMousePoint(), button, clicks, delta);
	}
}

void CComboBoxMe::RemoveItem( CMenuItemMe *item )
{
	if (m_dropDownMenu)
	{
		m_dropDownMenu->RemoveItem(item);
	}
}

void CComboBoxMe::SetProperty( const String& name, const String& value )
{
	if (name == L"selectedindex")
	{
		SetSelectedIndex(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"selectedtext")
	{
		SetSelectedText(value);
	}
	else if (name == L"selectedvalue")
	{
		SetSelectedValue(value);
	}
	else
	{
		CTextBoxMe::SetProperty(name, value);
	}
}

void CComboBoxMe::Update()
{
	CTextBoxMe::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton)
	{
		int dWidth = m_dropDownButton->GetWidth();
		POINT pt = {width - dWidth, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {dWidth, height};
		m_dropDownButton->SetSize(sz);
		PADDING pd(0, 0, dWidth, 0);
		SetPadding(pd);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////