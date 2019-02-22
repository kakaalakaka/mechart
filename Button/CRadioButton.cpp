#include "..\\stdafx.h"
#include "..\\include\\Button\\CRadioButton.h"
using namespace MeLib;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CRadioButtonMe::CRadioButtonMe()
{
	 m_groupName = L"";
}

CRadioButtonMe::~CRadioButtonMe()
{
}

String CRadioButtonMe::GetGroupName()
{
	return m_groupName;
}

void CRadioButtonMe::SetGroupName(const String& groupName)
{
	m_groupName = groupName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CRadioButtonMe::GetControlType()
{
	return L"RadioButton";
}

void CRadioButtonMe::GetProperty(const String& name, String *value, String *type)
{
	if (name == L"groupname")
	{
		*type = L"text";
		*value = GetGroupName();
	}
	else
	{
		CCheckBoxMe::GetProperty(name, value, type);
	}
}

vector<String> CRadioButtonMe::GetPropertyNames()
{
	vector<String> propertyNames = CButtonMe::GetPropertyNames();
	propertyNames.push_back(L"GroupName");
	return propertyNames;
}

void CRadioButtonMe::OnClick(const POINT& mp, MouseButtonsMe button, int clicks, int delta)
{
	if (!IsChecked())
	{
		SetChecked(!IsChecked());
	}
	CCheckBoxMe::CallMouseEvents(EVENTID::CLICK, mp, button, clicks, delta);
	Invalidate();
}

void CRadioButtonMe::OnPaintCheckButton(CPaintMe *paint, const RECT& clipRect)
{
	String paintingBackImage = GetPaintingBackImage();
	if ((int)paintingBackImage.length() > 0)
	{
		paint->DrawImage(paintingBackImage.c_str(), clipRect);
	}
	else
	{
		if (IsChecked())
		{
			RECT rect = { clipRect.left + 2, clipRect.top + 2, clipRect.right - 3, clipRect.bottom - 3};
			if (clipRect.right - clipRect.left < 4 || clipRect.bottom - clipRect.top < 4)
			{
				rect = clipRect;
			}
			paint->FillEllipse(GetPaintingButtonBackColor(), rect);
		}
		paint->DrawEllipse(GetPaintingButtonBorderColor(), 1, 0, clipRect);
	}
}

void CRadioButtonMe::SetProperty(const String& name, const String& value)
{
	if (name == L"groupname")
	{
		SetGroupName(value);
	}
	else
	{
		CCheckBoxMe::SetProperty(name, value);
	}
}

void CRadioButtonMe::Update()
{
	if (IsChecked())
	{
		vector<CControlMe*> controls;
		if (GetParent())
		{
			controls = GetParent()->GetControls();
		}
		else
		{
			controls = GetNative()->GetControls();
		}
		int count = (int)controls.size();
		for (int i = 0; i < count; i++)
		{
			CRadioButtonMe *radioButton = dynamic_cast<CRadioButtonMe*>(controls[i]);
			if ((radioButton && radioButton != this) 
				&& (radioButton->GetGroupName() == GetGroupName() && radioButton->IsChecked()))
			{
				radioButton->SetChecked(false);
				radioButton->Invalidate();
			}
		}
	}
}