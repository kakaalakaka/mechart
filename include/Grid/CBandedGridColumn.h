/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CBANDEDGRIDCOLUMNME_H__
#define __CBANDEDGRIDCOLUMNME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CGridEnums.h"
#include "CBandedGrid.h"
#include "CGridColumn.h"
#include "CGridBand.h"

namespace MeLib
{
	class  CBandedGridMe;
	class  CGridColumnMe;
	class  CGridBandMe;

	class  CBandedGridColumnMe : public CGridColumnMe
	{
	protected:
		CGridBandMe *m_band;
	public:
		CBandedGridColumnMe();
		virtual ~CBandedGridColumnMe();
		virtual CGridBandMe* GetBand();
		virtual void SetBand(CGridBandMe *band);
	public:
		virtual wstring GetControlType();
		virtual bool OnDragBegin();
		virtual void OnMouseDown(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnMouseMove(const POINT& mp, MouseButtonsMe button, int clicks, int delta);
	};
}

#endif