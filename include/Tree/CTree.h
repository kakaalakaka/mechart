/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CTREEME_H__
#define __CTREEME_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Grid\\CGrid.h"
#include "..\\Grid\\CGridColumn.h"
#include "..\\Grid\\CGridRow.h"
#include "..\\Grid\\CGridCell.h"
#include "..\\Grid\\CGridCellExtends.h"
#include "CTreeNode.h"

namespace MeLib
{
	class  CTreeNodeMe;

	class  CTreeMe:public CGridMe
	{
	protected:
		bool m_checkBoxes;
		SIZE m_checkBoxSize;
		wstring m_checkedImage;
		wstring m_collapsedNodeImage;
		wstring m_expendedNodeImage;
		CTreeNodeMe *m_movingNode;
		SIZE m_nodeSize;
		wstring m_unCheckedImage;
	public:
		vector<CTreeNodeMe*> m_nodes;
		CTreeMe();
		virtual ~CTreeMe();
		virtual bool HasCheckBoxes();
		virtual void SetCheckBoxes(bool checkBoxes);
		virtual SIZE GetCheckBoxSize();
		virtual void SetCheckBoxSize(SIZE checkBoxSize);
		virtual wstring GetCheckedImage();
		virtual void SetCheckedImage(const wstring& checkedImage);
		virtual wstring GetCollapsedNodeImage();
		virtual void SetCollapsedNodeImage(const wstring& collapsedNodeImage);
		virtual wstring GetExpendedNodeImage();
		virtual void SetExpendedNodeImage(const wstring& expendedNodeImage);
		virtual SIZE GetNodeSize();
		virtual void SetNodeSize(SIZE nodeSize);
		virtual vector<CTreeNodeMe*> GetSelectedNodes();
		virtual void SetSelectedNodes(vector<CTreeNodeMe*> selectedNodes);
		virtual wstring GetUnCheckedImage();
		virtual void SetUnCheckedImage(const wstring& unCheckedImage);
	public:
		void AppendNode(CTreeNodeMe *node);
		void ClearNodes();
		void Collapse();
		void CollapseAll();
		void Expend();
		void ExpendAll();
		vector<CTreeNodeMe*> GetChildNodes();
		virtual wstring GetControlType();
		int GetNodeIndex(CTreeNodeMe *node);
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		void InsertNode(int index, CTreeNodeMe *node);
		virtual void OnCellMouseDown(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseMove(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnCellMouseUp(CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta);
		virtual void OnPaintForeground(CPaintMe *paint, const RECT& clipRect);
		virtual void OnPaintEditTextBox(CGridCellMe *cell, CPaintMe *paint, const RECT& rect, const RECT& clipRect);
		void RemoveNode(CTreeNodeMe *node);
		virtual void SetProperty(const wstring& name, const wstring& value);
	};
}

#endif