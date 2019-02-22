#include "..\\stdafx.h"
#include "..\\include\\TextBox\\CDatePicker.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDatePickerMe::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{

}

void CDatePickerMe::SelectedDayChanged( void *sender, void *pInvoke )
{

}

CDatePickerMe::CDatePickerMe()
{
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_selectedDayChangedEvent = &SelectedDayChanged;
}

CDatePickerMe::~CDatePickerMe()
{
	if ((m_calendar) && (m_selectedDayChangedEvent))
	{
		m_calendar->UnRegisterEvent(m_selectedDayChangedEvent, 0x2e);
		m_selectedDayChangedEvent = 0;
	}
	if ((m_dropDownButton) && (m_dropDownButtonMouseDownEvent))
	{
		m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, 0x18);
		m_dropDownButtonMouseDownEvent = 0;
	}
	if (m_dropDownMenu)
	{
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

CCalendarMe* CDatePickerMe::GetCalendar()
{
	return m_calendar;
}

CButtonMe* CDatePickerMe::GetDropDownButton()
{
	return  m_dropDownButton;
}

CMenuMe* CDatePickerMe::GetDropDownMenu()
{
	return m_dropDownMenu;
}

String CDatePickerMe::GetControlType()
{
	return L"DatePicker";
}

void CDatePickerMe::OnDropDownOpening()
{

}

void CDatePickerMe::OnLoad()
{
	CTextBoxMe::OnLoad();
	if (m_dropDownButton == 0)
	{
		CControlHostMe *host = GetNative()->GetHost();
		m_dropDownButton = (CButtonMe*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, 0x18, this);
	}
	if (m_dropDownMenu != 0)
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void CDatePickerMe::OnValueChanged()
{
	CallEvents(0x2e);
	if (m_calendar != 0)
	{
		CDayMe *selectedDay = m_calendar->GetSelectedDay();
		if (selectedDay != 0)
		{
			CTimeDivMe *dir = m_calendar->GetTimeDiv();
			wchar_t buff[128] = {0};
			SetText(buff);
			Invalidate();
		}
	}
}

void CDatePickerMe::Update()
{
	CTextBoxMe::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton != 0)
	{
		int right = m_dropDownButton->GetWidth();
		PADDING pd(0, 0, right, 0);
		SetPadding(pd);
		POINT pt = {width - right, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {right, height};
		m_dropDownButton->SetSize(sz);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
