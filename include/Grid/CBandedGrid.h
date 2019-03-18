/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CBANDEDGRIDME_H__
#define __CBANDEDGRIDME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "CGridEnums.h"
#include "CBandedGridColumn.h"
#include "CGridBand.h"
#include "CGrid.h"

namespace MeLib
{
	class  CBandedGridColumnMe;
	class  CGridBandMe;

	class  CBandedGridMe : public CGridMe
	{
	protected:
		int GetAllVisibleBandsWidth();
	public:
		vector<CGridBandMe*> m_bands;
		CBandedGridMe();
		virtual ~CBandedGridMe();
	public:
		void AddBand(CGridBandMe *band);
		virtual void AddColumn(CGridColumnMe *column);
		void ClearBands();
		virtual void ClearColumns();
		vector<CGridBandMe*> GetBands();
		virtual int GetContentWidth();
		virtual wstring GetControlType();
		void InsertBand(int index, CGridBandMe *band);
		virtual void OnSetEmptyClipRegion();
		void RemoveBand(CGridBandMe *band);
		virtual void RemoveColumn(CGridColumnMe *column);
		virtual void ResetHeaderLayout();
		virtual void Update();
	};
}

#endif