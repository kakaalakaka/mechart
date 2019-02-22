#include "..\\stdafx.h"
#include "..\\include\\ScrollBar\\CVScrollBar.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CVScrollBarMe::BackButtonMouseDown( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CVScrollBarMe *pThis = (CVScrollBarMe*)sender;
	if(pThis)
	{
		pThis->OnBackButtonMouseDown(mp, button, clicks, delta);
	}
}

void CVScrollBarMe::BackButtonMouseUp( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CVScrollBarMe *pThis = (CVScrollBarMe*)sender;
	if(pThis)
	{
		pThis->OnBackButtonMouseUp(mp, button, clicks, delta);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CVScrollBarMe::CVScrollBarMe()
{
	m_backButtonMouseDownEvent = &BackButtonMouseDown;
	m_backButtonMouseUpEvent = &BackButtonMouseUp;
}

CVScrollBarMe::~CVScrollBarMe()
{
	if (m_backButton)
	{
		if (m_backButtonMouseDownEvent)
		{
			m_backButton->UnRegisterEvent(m_backButtonMouseDownEvent, EVENTID::MOUSEDOWN);
			m_backButtonMouseDownEvent = 0;
		}
		if (m_backButtonMouseUpEvent)
		{
			m_backButton->UnRegisterEvent(m_backButtonMouseUpEvent, EVENTID::MOUSEUP);
			m_backButtonMouseUpEvent = 0;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String CVScrollBarMe::GetControlType()
{
	return L"VScrollBar";
}

void CVScrollBarMe::OnBackButtonMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CButtonMe *scrollButton = GetScrollButton();
	if (mp.y < scrollButton->GetTop())
	{
		PageReduce();
		SetIsReducing(true);
	}
	else if (mp.y > scrollButton->GetBottom())
	{
		PageAdd();
		SetIsAdding(true);
	}
}

void CVScrollBarMe::OnBackButtonMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	SetIsAdding(false);
	SetIsReducing(false);
}

void CVScrollBarMe::OnDragScroll()
{
	bool flag = false;
	CButtonMe *backButton = GetBackButton();
	CButtonMe *scrollButton = GetScrollButton();
	int height = backButton->GetHeight();
	int contentSize = GetContentSize();
	if (scrollButton->GetBottom() > height)
	{
		flag = true;
	}
	CScrollBarMe::OnDragScroll();
	if (flag)
	{
		SetPos(contentSize);
	}
	else
	{
		SetPos((int) (contentSize * scrollButton->GetTop() / (_int64) height));
	}
	OnScrolled();
}

void CVScrollBarMe::OnLoad()
{
	bool flag = false;
	if (GetBackButton() != 0)
	{
		flag = true;
	}
	CScrollBarMe::OnLoad();
	if (!flag)
	{
		CButtonMe *backButton = GetBackButton();
		backButton->RegisterEvent(m_backButtonMouseDownEvent, EVENTID::MOUSEDOWN, this);
		backButton->RegisterEvent(m_backButtonMouseUpEvent, EVENTID::MOUSEUP, this);
	}
}

void CVScrollBarMe::Update()
{
	if (GetNative())
	{
		CButtonMe *addButton = GetAddButton();
		CButtonMe *backButton = GetBackButton();
		CButtonMe *reduceButton = GetReduceButton();
		CButtonMe *scrollButton = GetScrollButton();
		int width = GetWidth();
		int height = GetHeight();
		int contentSize = GetContentSize();
		if (contentSize > 0 && addButton && backButton && reduceButton && scrollButton)
		{
			int pos = GetPos();
			int pageSize = GetPageSize();
			if (pos > (contentSize - pageSize))
			{
				pos = contentSize - pageSize;
			}
			if (pos < 0)
			{
				pos = 0;
			}
			int abWidth = addButton->IsVisible() ? addButton->GetHeight() : 0;
			SIZE abSize = {width, abWidth};
			addButton->SetSize(abSize);
			POINT abPoint = {0, height - abWidth};
			addButton->SetLocation(abPoint);
			int rbWidth = reduceButton->IsVisible() ? reduceButton->GetHeight() : 0;
			SIZE rbSize = {width, rbWidth};
			reduceButton->SetSize(rbSize);
			POINT rbPoint = {0, 0};
			reduceButton->SetLocation(rbPoint);
			int backWidth = height - abWidth - rbWidth;
			SIZE backSize = {width, backWidth};
			backButton->SetSize(backSize);
			POINT backPoint = {0, rbWidth};
			backButton->SetLocation(backPoint);
			int scrollWidth = backWidth * pageSize / contentSize;
			int scrollPos = backWidth * pos / contentSize;
			if (scrollWidth < 10)
			{
				scrollWidth = 10;
				if (scrollPos + scrollWidth > backWidth)
				{
					scrollPos = backWidth - scrollWidth;
				}
			}
			SIZE scrollSize = {width, scrollWidth};
			scrollButton->SetSize(scrollSize);
			POINT scrollPoint = {0, scrollPos};
			scrollButton->SetLocation(scrollPoint);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////