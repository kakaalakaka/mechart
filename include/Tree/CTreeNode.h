/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __TREENODE_H__
#define __TREENODE_H__
#pragma once

#include "..\\..\\stdafx.h"
#include "..\\Grid\\CGrid.h"
#include "..\\Grid\\CGridRow.h"
#include "..\\Grid\\CGridCell.h"
#include "..\\Button\\CCheckBox.h"
#include "CTree.h"

namespace MeLib
{
	class  CTreeMe;

	class  CTreeNodeMe : public CGridControlCellMe
	{
	protected:
		bool m_allowDragIn;
		bool m_allowDragOut;
		bool m_checked;
		vector<CTreeNodeMe*> m_nodes;
		bool m_expended;
		int m_indent;
		CTreeNodeMe *m_parent;
		CGridColumnMe *m_targetColumn;
		wstring m_text;
		CTreeMe *m_tree;
		wstring m_value;
		void CheckChildNodes(vector<CTreeNodeMe*> nodes, bool isChecked);
		void CollapseChildNodes(vector<CTreeNodeMe*> nodes, bool collapseAll);
		void ExpendChildNodes(vector<CTreeNodeMe*> nodes, bool parentExpened, bool expendAll);
		CTreeNodeMe* GetLastNode(vector<CTreeNodeMe*> nodes);
	public:
		CTreeNodeMe();
		virtual ~CTreeNodeMe();
		virtual bool AllowDragIn();
		virtual void SetAllowDragIn(bool allowDragIn);
		virtual bool AllowDragOut();
		virtual void SetAllowDragOut(bool allowDragOut);
		virtual bool IsChecked();
		virtual void SetChecked(bool checked);
		virtual bool IsExpended();
		virtual void SetExpended(bool expended);
		virtual int GetIndent();
		virtual CTreeNodeMe* GetParent();
		virtual void SetParent(CTreeNodeMe *parent);
		virtual CGridColumnMe* GetTargetColumn();
		virtual void SetTargetColumn(CGridColumnMe *targetColumn);
		virtual CTreeMe* GetTree();
		virtual void SetTree(CTreeMe *tree);
		virtual wstring GetValue();
		virtual void SetValue(const wstring& value);
	public:
		void AppendNode(CTreeNodeMe *node);
		void ClearNodes();
		void Collapse();
		void CollapseAll();
		void Expend();
		void ExpendAll();
		vector<CTreeNodeMe*> GetChildNodes();
		int GetNodeIndex(CTreeNodeMe *node);
		virtual wstring GetPaintText();
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type);
		virtual vector<wstring> GetPropertyNames();
		virtual wstring GetString();
		void InsertNode(int index, CTreeNodeMe *node);
		bool IsNodeVisible(CTreeNodeMe *node);
		virtual void OnAddingNode(int index);
		virtual void OnPaintCheckBox(CPaintMe *paint, const RECT& rect);
		virtual void OnPaintNode(CPaintMe *paint, const RECT& rect);
		virtual void OnPaint(CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate);
		virtual void OnRemovingNode();
		void RemoveNode(CTreeNodeMe *node);
		virtual void SetProperty(const wstring& name, const wstring& value);
		virtual void SetString(const wstring& value);
	};
}

#endif