#include "..\\stdafx.h"
#include "..\\include\\TextBox\\CDateTimePicker.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDateTimePickerMe::DropDownButtonMouseDown( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CDateTimePickerMe *pThis = (CDateTimePickerMe*)sender;
	if(pThis)
	{
		pThis->OnDropDownOpening();
	}
}

void CDateTimePickerMe::SelectedTimeChanged( void *sender, void *pInvoke )
{
	CDateTimePickerMe *pThis = (CDateTimePickerMe*)sender;
	if(pThis)
	{
		pThis->OnSelectedTimeChanged();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CDateTimePickerMe::CDateTimePickerMe()
{
	m_calendar = 0;
	m_dropDownButton = 0;
	m_dropDownMenu = 0;
	m_customFormat = L"yyyy-MM-dd";
	m_dropDownButtonMouseDownEvent = &DropDownButtonMouseDown;
	m_selectedTimeChangedEvent = &SelectedTimeChanged;
}

CDateTimePickerMe::~CDateTimePickerMe()
{
	if (m_calendar)
	{
		if(m_selectedTimeChangedEvent)
		{
			m_calendar->UnRegisterEvent(m_selectedTimeChangedEvent, EVENTID::SELECTEDTIMECHANGED);
			m_selectedTimeChangedEvent = 0;
		}
		m_calendar = 0;
	}
	if (m_dropDownButton)
	{
		if(m_dropDownButtonMouseDownEvent)
		{
			m_dropDownButton->UnRegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_dropDownButtonMouseDownEvent = 0;
		}
		m_dropDownButton = 0;
	}
	if (m_dropDownMenu)
	{
		GetNative()->RemoveControl(m_dropDownMenu);
		delete m_dropDownMenu;
		m_dropDownMenu = 0;
	}
}

CCalendarMe* CDateTimePickerMe::GetCalendar()
{
	return m_calendar;
}

String CDateTimePickerMe::GetCustomFormat()
{
	return m_customFormat;
}

void CDateTimePickerMe::SetCustomFormat( const String& customFormat )
{
	m_customFormat = customFormat;
}

CButtonMe* CDateTimePickerMe::GetDropDownButton()
{
	return m_dropDownButton;
}

CMenuMe* CDateTimePickerMe::GetDropDownMenu()
{
	return m_dropDownMenu;
}

bool CDateTimePickerMe::ShowTime()
{
	return m_showTime;
}

void CDateTimePickerMe::SetShowTime(bool showTime)
{
	m_showTime = showTime;
}

String CDateTimePickerMe::GetControlType()
{
	return L"DateTimePicker";
}

void CDateTimePickerMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"customformat")
	{
		*type = L"string";
		*value = GetCustomFormat();
	}
	else if (name == L"showtime")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(m_showTime);
	}
	else
	{
		CTextBoxMe::GetProperty(name, value, type);
	}
}

vector<String> CDateTimePickerMe::GetPropertyNames()
{
	vector<String> propertyNames = CTextBoxMe::GetPropertyNames();
	propertyNames.push_back(L"CustomFormat");
	propertyNames.push_back(L"ShowTime");
	return propertyNames;
}

void CDateTimePickerMe::OnDropDownOpening()
{
	if (!m_dropDownMenu)
	{
		CControlHostMe *host = GetNative()->GetHost();
		m_dropDownMenu = (CMenuMe*)host->CreateInternalControl(this, L"dropdownmenu");
		GetNative()->AddControl(m_dropDownMenu);
		if (!m_calendar)
		{
			m_calendar = new CCalendarMe();
			m_calendar->SetDock(DockStyleMe_Fill);
			m_dropDownMenu->AddControl(m_calendar);
			m_calendar->SetSize(m_dropDownMenu->GetSize());
			m_calendar->RegisterEvent(m_selectedTimeChangedEvent, EVENTID::SELECTEDTIMECHANGED, this);
		}
	}
	m_dropDownMenu->SetNative(GetNative());
	POINT pt = {0, GetHeight()};
	POINT point = PointToNative(pt);
	m_dropDownMenu->SetLocation(point);
	m_dropDownMenu->SetVisible(true);
	if (m_calendar)
	{
		m_calendar->SetMode(CalendarMode_Day);
	}
	m_dropDownMenu->BringToFront();
	m_dropDownMenu->Invalidate();
}

void CDateTimePickerMe::OnLoad()
{
	CControlMe::OnLoad();
	if (!m_dropDownButton)
	{
		CControlHostMe *host = GetNative()->GetHost();
		m_dropDownButton = (CButtonMe*)host->CreateInternalControl(this, L"dropdownbutton");
		AddControl(m_dropDownButton);
		m_dropDownButton->RegisterEvent(m_dropDownButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
	}
	if (m_dropDownMenu)
	{
		m_dropDownMenu->SetNative(GetNative());
	}
}

void CDateTimePickerMe::OnSelectedTimeChanged()
{
	CallEvents(EVENTID::VALUECHANGED);
	if (m_calendar)
	{
		CDayMe *selectedDay = m_calendar->GetSelectedDay();
		if (selectedDay)
		{
			CTimeDivMe *dir = m_calendar->GetTimeDiv();
			String buff = CStrMe::GetFormatDate(m_customFormat.c_str(), selectedDay->GetYear(), 
				selectedDay->GetMonth(), selectedDay->GetDay(), dir->GetHour(), dir->GetMinute(), dir->GetSecond());
			SetText(buff);
			Invalidate();
		}
	}
}

void CDateTimePickerMe::SetProperty( const String& name, const String& value )
{
	if (name == L"customformat")
	{
		SetCustomFormat(value);
	}
	else if (name == L"showtime")
	{
		m_showTime = CStrMe::ConvertStrToBool(value);
	}
	else
	{
		CTextBoxMe::SetProperty(name, value);
	}
}

void CDateTimePickerMe::Update()
{
	CTextBoxMe::Update();
	int width = GetWidth();
	int height = GetHeight();
	if (m_dropDownButton)
	{
		int right = m_dropDownButton->GetWidth();
		POINT pt = {width - right, 0};
		m_dropDownButton->SetLocation(pt);
		SIZE sz = {right, height};
		m_dropDownButton->SetSize(sz);
		PADDING pd(0, 0, right, 0);
		SetPadding(pd);
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////