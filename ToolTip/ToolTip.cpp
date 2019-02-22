#include "..\\stdafx.h"
#include "..\\include\\ToolTip\\ToolTip.h"
using namespace MeLib;

ToolTipMe::ToolTipMe()
{
	m_timerID = GetNewTimerID();
	m_autoPopDelay = 0;
	m_initialDelay = 0;
	m_lastMousePoint.x = 0;
	m_lastMousePoint.y = 0;
	m_showAlways = false;
	m_useAnimation = false;
	m_remainAutoPopDelay = 0;
	m_remainInitialDelay = 0;
	SetAutoSize(true);
	SetBackColor(COLOR::ARGB(255, 255, 40));
	SetBorderColor(COLOR_CONTROLBORDER);
	SetTopMost(true);
	SetVisible(false);
}

ToolTipMe::~ToolTipMe()
{
	StopTimer(m_timerID);
}

int ToolTipMe::GetAutoPopDelay()
{
	return m_autoPopDelay;
}

void ToolTipMe::SetAutoPopDelay( int autoPopDelay )
{
	m_autoPopDelay = autoPopDelay;
}

int ToolTipMe::GetInitialDelay()
{
	return m_initialDelay;
}

void ToolTipMe::SetInitialDelay( int initialDelay )
{
	m_initialDelay = initialDelay;
}

bool ToolTipMe::ShowAlways()
{
	return m_showAlways;
}

void ToolTipMe::SetShowAlways( bool showAlways )
{
	m_showAlways = showAlways;
}

bool ToolTipMe::UseAnimation()
{
	return m_useAnimation;
}

void ToolTipMe::SetUseAnimation( bool useAnimation )
{
	m_useAnimation = useAnimation;
}

String ToolTipMe::GetControlType()
{
	return L"ToolTip";
}

void ToolTipMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"autopopupdelay")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetAutoPopDelay());
	}
	else if (name == L"initialdelay")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetInitialDelay());
	}
	else if (name == L"showalways")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(ShowAlways());
	}
	else if (name == L"useanimation")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(UseAnimation());
	}
	else
	{
		CLabelMe::GetProperty(name, value, type);
	}
}

vector<String> ToolTipMe::GetPropertyNames()
{
	vector<String> propertyNames = CLabelMe::GetPropertyNames();
	propertyNames.push_back(L"AutoPopupDelay");
	propertyNames.push_back(L"InitialDelay");
	propertyNames.push_back(L"ShowAlways");
	propertyNames.push_back(L"UseAnimation");
	return propertyNames;
}

void ToolTipMe::Hide()
{
	SetVisible(false);
}

void ToolTipMe::OnLoad()
{
	CControlMe::OnLoad();
	m_lastMousePoint = GetMousePoint();
	StartTimer(m_timerID, 10);
}

void ToolTipMe::OnTimer( int timerID )
{
	CControlMe::OnTimer(timerID);
	if (m_timerID == timerID)
	{
		POINT mousePoint = GetMousePoint();
		if (!m_showAlways && (m_lastMousePoint.x != mousePoint.x || m_lastMousePoint.y != mousePoint.y))
		{
			SetVisible(false);
		}
		m_lastMousePoint = mousePoint;
		if (m_remainAutoPopDelay > 0)
		{
			m_remainAutoPopDelay -= 10;
			if (m_remainAutoPopDelay <= 0)
			{
				SetVisible(false);
			}
		}
		if (m_remainInitialDelay > 0)
		{
			m_remainInitialDelay -= 10;
			if (m_remainInitialDelay <= 0)
			{
				SetVisible(true);
			}
		}
	}
}

void ToolTipMe::OnVisibleChanged()
{
	CControlMe::OnVisibleChanged();
	if (m_native)
	{
		if (IsVisible())
		{
			m_native->AddControl(this);
			m_remainAutoPopDelay = m_autoPopDelay;
			m_remainInitialDelay = 0;
		}
		else
		{
			m_native->RemoveControl(this);
			StartTimer(m_timerID, 10);
			m_remainAutoPopDelay = 0;
			m_remainInitialDelay = 0;
		}
		GetNative()->Invalidate();
	}
}

void ToolTipMe::Show()
{
	m_remainAutoPopDelay = 0;
	m_remainInitialDelay = m_initialDelay;
	SetVisible(m_initialDelay == 0);
	GetNative()->Invalidate();
}

void ToolTipMe::SetProperty( const String& name, const String& value )
{
	if (name == L"autopopupdelay")
	{
		SetAutoPopDelay(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"initialdelay")
	{
		SetInitialDelay(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"showalways")
	{
		SetShowAlways(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"useanimation")
	{
		SetUseAnimation(CStrMe::ConvertStrToBool(value));
	}
	else
	{
		CLabelMe::SetProperty(name, value);
	}
}