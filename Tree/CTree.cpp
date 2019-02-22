#include "..\\stdafx.h"
#include "..\\include\\Tree\\CTree.h"
using namespace MeLib;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CTreeMe::CTreeMe()
{
	m_checkBoxes = false;
	m_checkBoxSize.cx = 14;
	m_checkBoxSize.cy = 14;
	CGridMe::SetGridLineColor(COLOR_EMPTY);
	m_movingNode = 0;
	m_nodeSize.cx = 14;
	m_nodeSize.cy = 14;
}

CTreeMe::~CTreeMe()
{
	m_movingNode = 0;
}

bool CTreeMe::HasCheckBoxes()
{
	return m_checkBoxes;
}

void CTreeMe::SetCheckBoxes( bool checkBoxes )
{
	m_checkBoxes = checkBoxes;
}

SIZE CTreeMe::GetCheckBoxSize()
{
	return m_checkBoxSize;
}

void CTreeMe::SetCheckBoxSize( SIZE checkBoxSize )
{
	m_checkBoxSize = checkBoxSize;
}

String CTreeMe::GetCheckedImage()
{
	return m_checkedImage;
}

void CTreeMe::SetCheckedImage( const String& checkedImage )
{
	m_checkedImage = checkedImage;
}

String CTreeMe::GetCollapsedNodeImage()
{
	return m_collapsedNodeImage;
}

void CTreeMe::SetCollapsedNodeImage( const String& collapsedNodeImage )
{
	m_collapsedNodeImage = collapsedNodeImage;
}

String CTreeMe::GetExpendedNodeImage()
{
	return m_expendedNodeImage;
}

void CTreeMe::SetExpendedNodeImage( const String& expendedNodeImage )
{
	m_expendedNodeImage = expendedNodeImage;
}

SIZE CTreeMe::GetNodeSize()
{
	return m_nodeSize;
}

void CTreeMe::SetNodeSize( SIZE nodeSize )
{
	m_nodeSize = nodeSize;
}

vector<CTreeNodeMe*> CTreeMe::GetSelectedNodes()
{
	vector<CTreeNodeMe*> list;
	vector<CGridRowMe*> selectedRows = GetSelectedRows();
	int count = (int)selectedRows.size();
	for (int i = 0; i < count; i++)
	{
		vector<CGridCellMe*> cells = selectedRows[i]->m_cells;
		int num3 = (int)cells.size();
		for (int j = 0; j < num3; j++)
		{
			CTreeNodeMe *item = (CTreeNodeMe*)cells[j];
			if (item)
			{
				list.push_back(item);
				break;
			}
		}
	}
	return list;
}

void CTreeMe::SetSelectedNodes( vector<CTreeNodeMe*> selectedNodes )
{
	int count = (int)selectedNodes.size();
	vector<CGridRowMe*> list;
	for (int i = 0; i < count; i++)
	{
		list.push_back(selectedNodes[i]->GetRow());
	}
	SetSelectedRows(list);
}

String CTreeMe::GetUnCheckedImage()
{
	return m_unCheckedImage;
}

void CTreeMe::SetUnCheckedImage( const String& unCheckedImage )
{
	m_unCheckedImage = unCheckedImage;
}

void CTreeMe::AppendNode( CTreeNodeMe *node )
{
	node->SetTree(this);
	node->OnAddingNode(-1);
	m_nodes.push_back(node);
}

void CTreeMe::ClearNodes()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		RemoveNode(m_nodes[i]);
	}
	m_nodes.clear();
}

void CTreeMe::Collapse()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->Collapse();
	}
}

void CTreeMe::CollapseAll()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->CollapseAll();
	}
}

void CTreeMe::Expend()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->Expend();
	}
}

void CTreeMe::ExpendAll()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		m_nodes[i]->ExpendAll();
	}
}

vector<CTreeNodeMe*> CTreeMe::GetChildNodes()
{
	return m_nodes;
}

String CTreeMe::GetControlType()
{
	return L"Tree";
}

int CTreeMe::GetNodeIndex( CTreeNodeMe *node )
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		if (m_nodes[i] == node)
		{
			return i;
		}
	}
	return -1;
}

void CTreeMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"checkboxes")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(HasCheckBoxes());
	}
	else if (name == L"checkboxsize")
	{
		*type = L"size";
		*value = CStrMe::ConvertSizeToStr(GetCheckBoxSize());
	}
	else if (name == L"checkedimage")
	{
		*type = L"String";
		*value = GetCheckedImage();
	}
	else if (name == L"collapsednodeimage")
	{
		*type = L"String";
		*value = GetCollapsedNodeImage();
	}
	else if (name == L"expendednodeimage")
	{
		*type = L"String";
		*value = GetExpendedNodeImage();
	}
	else if (name == L"uncheckedimage")
	{
		*type = L"String";
		*value = GetUnCheckedImage();
	}
	else if (name == L"nodesize")
	{
		*type = L"size";
		*value = CStrMe::ConvertSizeToStr(GetNodeSize());
	}
	else
	{
		CGridMe::GetProperty(name, value, type);
	}
}

vector<String> CTreeMe::GetPropertyNames()
{
	vector<String> propertyNames = CGridMe::GetPropertyNames();
	propertyNames.push_back(L"CheckBoxes");
	propertyNames.push_back(L"CheckBoxSize");
	propertyNames.push_back(L"CheckedImage");
	propertyNames.push_back(L"CollapsedNodeImage");
	propertyNames.push_back(L"ExpendedNodeImage");
	propertyNames.push_back(L"UnCheckedImage");
	propertyNames.push_back(L"NodeSize");
	return propertyNames;
}

void CTreeMe::InsertNode( int index, CTreeNodeMe *node )
{
	int num = -1;
	if (index == 0)
	{
		if (node->GetParent())
		{
			num = node->GetParent()->GetRow()->GetIndex() + 1;
		}
		else
		{
			num = 0;
		}
	}
	else if (!m_nodes.empty())
	{
		num = m_nodes[index]->GetRow()->GetIndex();
	}
	node->SetTree(this);
	node->OnAddingNode(num);
	m_nodes.insert(m_nodes.begin() + index, node);
}

void CTreeMe::OnCellMouseDown( CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CGridMe::OnCellMouseDown(cell, mp, button, clicks, delta);
	CTreeNodeMe *ea = (CTreeNodeMe*)cell;
	if (ea)
	{
		int pos = 0;
		CHScrollBarMe *hScrollBar = GetHScrollBar();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			pos = hScrollBar->GetPos();
		}
		RECT bounds = ea->GetTargetColumn()->GetBounds();
		bounds.left += GetHorizontalOffset() - pos;
		bounds.top += GetVerticalOffset() - pos;
		int left = bounds.left;
		if (m_checkBoxes)
		{
			int cx = m_checkBoxSize.cx;
			if ((mp.x >= left) && (mp.x <= (left + cx)))
			{
				ea->SetChecked(!ea->IsChecked());
				return;
			}
			left += cx + 10;
		}
		vector<CTreeNodeMe*> childNodes = ea->GetChildNodes();
		if (!childNodes.empty())
		{
			int num4 = m_nodeSize.cx;
			if ((mp.x >= left) && (mp.x <= (left + num4)))
			{
				if (ea->IsExpended())
				{
					ea->Collapse();
				}
				else
				{
					ea->Expend();
				}
				Update();
				return;
			}
		}
		if (ea->AllowDragOut())
		{
			m_movingNode = ea;
		}
	}
}

void CTreeMe::OnCellMouseMove( CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CGridMe::OnCellMouseMove(cell, mp, button, clicks, delta);
	if (m_movingNode)
	{
		Invalidate();
	}
}

void CTreeMe::OnCellMouseUp( CGridCellMe *cell, const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	CGridMe::OnCellMouseUp(cell, mp, button, clicks, delta);
	if (m_movingNode)
	{
		CGridRowMe *row = GetRow(mp);
		if (row)
		{
			CTreeNodeMe *node = (CTreeNodeMe*)(row->GetCell(0));
			if (node->AllowDragIn() && (m_movingNode != node))
			{
				CTreeNodeMe *parent = node->GetParent();
				CTreeNodeMe *ea3 = m_movingNode->GetParent();
				if (ea3)
				{
					ea3->RemoveNode(m_movingNode);
				}
				else
				{
					RemoveNode(m_movingNode);
				}
				if (parent)
				{
					if (ea3 == parent)
					{
						parent->InsertNode(parent->GetNodeIndex(node), m_movingNode);
					}
					else
					{
						node->AppendNode(m_movingNode);
					}
				}
				else if (ea3 == parent)
				{
					InsertNode(GetNodeIndex(node), m_movingNode);
				}
				else
				{
					node->AppendNode(m_movingNode);
				}
				node->Expend();
			}
		}
		m_movingNode = 0;
		Update();
	}
}

void CTreeMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	CGridMe::OnPaintForeground(paint, clipRect);
	if (m_movingNode)
	{
		FONT *font = GetFont();
		POINT mousePoint = GetMousePoint();
		SIZE size = paint->TextSize(m_movingNode->GetText().c_str(), font);
		RECT rect = {mousePoint.x, mousePoint.y, mousePoint.x + size.cx, mousePoint.y + size.cy};
		paint->DrawText(m_movingNode->GetText().c_str(), GetForeColor(), font, rect);
	}
}

void CTreeMe::OnPaintEditTextBox( CGridCellMe *cell, CPaintMe *paint, const RECT& rc, const RECT& clipRect )
{
	RECT rect = rc;
	CTextBoxMe *editTextBox = GetEditTextBox();
	if (editTextBox)
	{
		CTreeNodeMe *ea = (CTreeNodeMe*)cell;
		if (ea)
		{
			int indent = ea->GetIndent();
			rect.left += indent;
			if (rect.right < rect.left)
			{
				rect.right = rect.left;
			}
			editTextBox->SetBounds(rect);
			editTextBox->SetDisplayOffset(false);
			editTextBox->BringToFront();
		}
		else
		{
			CGridMe::OnPaintEditTextBox(cell, paint, rect, clipRect);
		}
	}
}

void CTreeMe::RemoveNode( CTreeNodeMe *node )
{
	node->OnRemovingNode();
	for (vector<CTreeNodeMe*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		if (*it == node)
		{
			m_nodes.erase(it);
			break;
		}
	}
}

void CTreeMe::SetProperty( const String& name, const String& value )
{
	if (name == L"checkboxes")
	{
		SetCheckBoxes(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"checkboxsize")
	{
		SetCheckBoxSize(CStrMe::ConvertStrToSize(value));
	}
	else if (name == L"checkedimage")
	{
		SetCheckedImage(value);
	}
	else if (name == L"collapsednodeimage")
	{
		SetCollapsedNodeImage(value);
	}
	else if (name == L"expendednodeimage")
	{
		SetExpendedNodeImage(value);
	}
	else if (name == L"uncheckedimage")
	{
		SetUnCheckedImage(value);
	}
	else if (name == L"nodesize")
	{
		SetNodeSize(CStrMe::ConvertStrToSize(value));
	}
	else
	{
		CGridMe::SetProperty(name, value);
	}
}
