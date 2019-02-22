#include "..\\stdafx.h"
#include "..\\include\\ScrollBar\\CHScrollBar.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CHScrollBarMe::BackButtonMouseDown( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CHScrollBarMe *pThis = (CHScrollBarMe*)pInvoke;
	if(pThis)
	{
		pThis->OnBackButtonMouseDown(mp, button, clicks, delta);
	}
}

void CHScrollBarMe::BackButtonMouseUp( void *sender, const POINT& mp, MouseButtonsMe button, int clicks, int delta, void *pInvoke )
{
	CHScrollBarMe *pThis = (CHScrollBarMe*)pInvoke;
	if(pThis)
	{
		pThis->OnBackButtonMouseUp(mp, button, clicks, delta);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CHScrollBarMe::CHScrollBarMe()
{
	m_backButtonMouseDownEvent = &BackButtonMouseDown;
	m_backButtonMouseUpEvent = &BackButtonMouseUp;
}

CHScrollBarMe::~CHScrollBarMe()
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
String CHScrollBarMe::GetControlType()
{
	return L"HScrollBar";
}

void CHScrollBarMe::OnBackButtonMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CButtonMe *scrollButton = GetScrollButton();
	if (mp.x < scrollButton->GetLeft())
	{
		PageReduce();
		SetIsReducing(true);
	}
	else if (mp.x > scrollButton->GetRight())
	{
		PageAdd();
		SetIsAdding(true);
	}
}

void CHScrollBarMe::OnBackButtonMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	SetIsAdding(false);
	SetIsReducing(false);
}

void CHScrollBarMe::OnDragScroll()
{
	bool flag = false;
	CButtonMe *backButton = GetBackButton();
	CButtonMe *scrollButton = GetScrollButton();
	int width = backButton->GetWidth();
	int contentSize = GetContentSize();
	if (scrollButton->GetRight() > width)
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
		SetPos((int) (contentSize * scrollButton->GetLeft() / (_int64) width));
	}
	OnScrolled();
}

void CHScrollBarMe::OnLoad()
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

void CHScrollBarMe::Update()
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
			if (pos > contentSize - pageSize)
			{
				pos = contentSize - pageSize;
			}
			if (pos < 0)
			{
				pos = 0;
			}
			int abWidth = addButton->IsVisible() ? addButton->GetWidth() : 0;
			SIZE abSize = {abWidth, height};
			addButton->SetSize(abSize);
			POINT abPoint = {width - abWidth, 0};
			addButton->SetLocation(abPoint);
			int rbWidth = reduceButton->IsVisible() ? reduceButton->GetWidth() : 0;
			SIZE rbSize = {rbWidth, height};
			reduceButton->SetSize(rbSize);
			POINT rbPoint = {0, 0};
			reduceButton->SetLocation(rbPoint);
			int backWidth = width - abWidth - rbWidth;
			SIZE backSize = {backWidth, height};
			backButton->SetSize(backSize);
			POINT backPoint = {rbWidth, 0};
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
			SIZE scrollSize = {scrollWidth, height};
			scrollButton->SetSize(scrollSize);
			POINT scrollPoint = {scrollPos, 0};
			scrollButton->SetLocation(scrollPoint);
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////