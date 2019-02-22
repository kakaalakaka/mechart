#include "..\\stdafx.h"
#include "..\\include\\Tree\\CTreeNode.h"
using namespace MeLib;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTreeNodeMe::CheckChildNodes( vector<CTreeNodeMe*> nodes, bool isChecked )
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		CTreeNodeMe *ea = nodes[i];
		ea->SetChecked(isChecked);
		vector<CTreeNodeMe*> childNodes = ea->GetChildNodes();
		if (childNodes.size() > 0)
		{
			CheckChildNodes(childNodes, isChecked);
		}
	}
}

void CTreeNodeMe::CollapseChildNodes( vector<CTreeNodeMe*> nodes, bool collapseAll )
{
	int count = (int)nodes.size();
	for (int i = 0; i < count; i++)
	{
		CTreeNodeMe *ea = nodes[i];
		if (collapseAll)
		{
			ea->SetExpended(false);
		}
		ea->GetRow()->SetVisible(false);
		vector<CTreeNodeMe*> childNodes = ea->GetChildNodes();
		if (childNodes.size() > 0)
		{
			CollapseChildNodes(childNodes, collapseAll);
		}
	}
}

void CTreeNodeMe::ExpendChildNodes( vector<CTreeNodeMe*> nodes, bool parentExpened, bool expendAll )
{
	int count = (int)nodes.size();
	for (int i = 0; i < count; i++)
	{
		CTreeNodeMe *ea = nodes[i];
		bool flag = parentExpened;
		CGridRowMe *row = ea->GetRow();
		if (expendAll)
		{
			flag = true;
			row->SetVisible(true);
			ea->SetExpended(true);
		}
		else
		{
			if (parentExpened)
			{
				row->SetVisible(true);
			}
			else
			{
				row->SetVisible(false);
			}
			if (!ea->IsExpended())
			{
				flag = false;
			}
		}
		vector<CTreeNodeMe*> childNodes = ea->GetChildNodes();
		if (childNodes.size() > 0)
		{
			ExpendChildNodes(childNodes, flag, expendAll);
		}
	}
}

CTreeNodeMe* CTreeNodeMe::GetLastNode( vector<CTreeNodeMe*> nodes )
{
	int count = (int)nodes.size();
	if (count > 0)
	{
		for (int i = count - 1; i >= 0; i--)
		{
			CTreeNodeMe *ea = nodes[i];
			if (ea->GetRow())
			{
				vector<CTreeNodeMe*> childNodes = ea->GetChildNodes();
				CTreeNodeMe *lastNode = GetLastNode(childNodes);
				if (lastNode)
				{
					return lastNode;
				}
				return ea;
			}
		}
	}
	return 0;
}

CTreeNodeMe::CTreeNodeMe()
{
	m_allowDragIn = false;
	m_allowDragOut = false;
	m_checked = false;
	m_expended = true;
	m_indent = 0;
	m_parent = 0;
	m_targetColumn = 0;
	m_tree = 0;
}

CTreeNodeMe::~CTreeNodeMe()
{
	m_parent = 0;
	m_targetColumn = 0;
	m_tree = 0;
}

bool CTreeNodeMe::AllowDragIn()
{
	return m_allowDragIn;
}

void CTreeNodeMe::SetAllowDragIn( bool allowDragIn )
{
	m_allowDragIn = allowDragIn;
}

bool CTreeNodeMe::AllowDragOut()
{
	return m_allowDragOut;
}

void CTreeNodeMe::SetAllowDragOut( bool allowDragOut )
{
	m_allowDragOut = allowDragOut;
}

bool CTreeNodeMe::IsChecked()
{
	return m_checked;
}

void CTreeNodeMe::SetChecked( bool checked )
{
	if (m_checked != checked)
	{
		m_checked = checked;
		CheckChildNodes(m_nodes, m_checked);
	}
}

bool CTreeNodeMe::IsExpended()
{
	return m_expended;
}

void CTreeNodeMe::SetExpended( bool expended )
{
	m_expended = expended;
}

int CTreeNodeMe::GetIndent()
{
	return m_indent;
}

CTreeNodeMe* CTreeNodeMe::GetParent()
{
	return m_parent;
}

void CTreeNodeMe::SetParent( CTreeNodeMe *parent )
{
	m_parent = parent;
}

CGridColumnMe* CTreeNodeMe::GetTargetColumn()
{
	return m_targetColumn;
}

void CTreeNodeMe::SetTargetColumn( CGridColumnMe *targetColumn )
{
	m_targetColumn = targetColumn;
}

CTreeMe* CTreeNodeMe::GetTree()
{
	return m_tree;
}

void CTreeNodeMe::SetTree( CTreeMe *tree )
{
	m_tree = tree;
}

String CTreeNodeMe::GetValue()
{
	return m_value;
}

void CTreeNodeMe::SetValue( const String& value )
{
	m_value = value;
}

void CTreeNodeMe::AppendNode( CTreeNodeMe *node )
{
	node->SetParent(this);
	node->SetTree(m_tree);
	node->OnAddingNode(-1);
	m_nodes.push_back(node);
}

void CTreeNodeMe::ClearNodes()
{
	int count = (int)m_nodes.size();
	for (int i = 0; i < count; i++)
	{
		RemoveNode(m_nodes[i]);
	}
	m_nodes.clear();
}

void CTreeNodeMe::Collapse()
{
	if ((int)m_nodes.size() > 0)
	{
		m_expended = false;
		CollapseChildNodes(m_nodes, false);
	}
}

void CTreeNodeMe::CollapseAll()
{
	if ((int)m_nodes.size() > 0)
	{
		m_expended = false;
		CollapseChildNodes(m_nodes, true);
	}
}

void CTreeNodeMe::Expend()
{
	if ((int)m_nodes.size() > 0)
	{
		m_expended = true;
		ExpendChildNodes(m_nodes, true, false);
	}
}

void CTreeNodeMe::ExpendAll()
{
	if ((int)m_nodes.size() > 0)
	{
		m_expended = true;
		ExpendChildNodes(m_nodes, true, true);
	}
}

vector<CTreeNodeMe*> CTreeNodeMe::GetChildNodes()
{
	return m_nodes;
}

int CTreeNodeMe::GetNodeIndex( CTreeNodeMe *node )
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

String CTreeNodeMe::GetPaintText()
{
	return GetText();
}

void CTreeNodeMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"allowdragin")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowDragIn());
	}
	else if (name == L"allowdragout")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(AllowDragOut());
	}
	else if (name == L"checked")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsChecked());
	}
	else if (name == L"expended")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsExpended());
	}
	else if (name == L"value")
	{
		*type = L"String";
		*value = GetValue();
	}
	else
	{
		CGridCellMe::GetProperty(name, value, type);
	}
}

vector<String> CTreeNodeMe::GetPropertyNames()
{
	vector<String> propertyNames = CGridCellMe::GetPropertyNames();
	propertyNames.push_back(L"AllowDragIn");
	propertyNames.push_back(L"AllowDragOut");
	propertyNames.push_back(L"Checked");
	propertyNames.push_back(L"Expended");
	propertyNames.push_back(L"Value");
	return propertyNames;
}

String CTreeNodeMe::GetString()
{
	return m_text;
}

void CTreeNodeMe::InsertNode( int index, CTreeNodeMe *node )
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
	else if ((int)m_nodes.size() > 0)
	{
		num = m_nodes[index]->GetRow()->GetIndex();
	}
	node->SetTree(m_tree);
	node->SetParent(this);
	node->OnAddingNode(num);
	m_nodes.insert(m_nodes.begin() + index, node);
}

bool CTreeNodeMe::IsNodeVisible( CTreeNodeMe *node )
{
	CTreeNodeMe *parent = node->GetParent();
	if (!parent)
	{
		return true;
	}
	if (parent->IsExpended())
	{
		return IsNodeVisible(parent);
	}
	return false;
}

void CTreeNodeMe::OnAddingNode( int index )
{
	CGridRowMe *row = GetRow();
	if (!row)
	{
		row = new CGridRowMe();
		CTreeNodeMe *parent = m_parent;
		if (!parent)
		{
			if (index != -1)
			{
				m_tree->InsertRow(index, row);
				vector<CGridRowMe*> rows = m_tree->GetRows();
				int count = (int)rows.size();
				for (int i = 0; i < count; i++)
				{
					rows[i]->SetIndex(i);
				}
			}
			else
			{
				m_tree->AddRow(row);
				vector<CGridRowMe*> list2 = m_tree->GetRows();
				row->SetIndex((int)list2.size() - 1);
			}
			row->AddCell(0, this);
			m_targetColumn = m_tree->GetColumn(0);
		}
		else
		{
			int rowIndex = parent->GetRow()->GetIndex() + 1;
			if (index != -1)
			{
				rowIndex = index;
			}
			else
			{
				CTreeNodeMe *lastNode = GetLastNode(parent->GetChildNodes());
				if (lastNode)
				{
					if (lastNode->GetRow() == 0)
					{
						return;
					}
					rowIndex = lastNode->GetRow()->GetIndex() + 1;
				}
			}
			m_tree->InsertRow(rowIndex, row);
			vector<CGridRowMe*> list3 = m_tree->GetRows();
			int num4 = (int)list3.size();
			if (rowIndex == num4 - 1)
			{
				row->SetIndex(rowIndex);
			}
			else
			{
				for (int j = 0; j < num4; j++)
				{
					list3[j]->SetIndex(j);
				}
			}
			row->AddCell(0, this);
			m_targetColumn = m_tree->GetColumn((int) (parent->m_targetColumn->GetIndex() + 1));
		}
		SetColSpan((int)m_tree->GetColumns().size());
		if ((int)m_nodes.size() > 0)
		{
			int nodeSize = (int)m_nodes.size();
			for (int k = 0; k < nodeSize; k++)
			{
				m_nodes[k]->OnAddingNode(-1);
			}
		}
		row->SetVisible(IsNodeVisible(this));
	}
}

void CTreeNodeMe::OnPaintCheckBox( CPaintMe *paint, const RECT& rect )
{
	if (m_checked)
	{
		String checkedImg = m_tree->GetCheckedImage();
		if ((int)checkedImg.length() > 0)
		{
			paint->DrawImage(checkedImg.c_str(), rect);
		}
		else
		{
			paint->FillRect((_int64) COLOR::ARGB(0, 0, 0), rect);
		}
	}
	else
	{
		String unChecked = m_tree->GetUnCheckedImage();
		if ((int)unChecked.length() > 0)
		{
			paint->DrawImage(unChecked.c_str(), rect);
		}
		else
		{
			paint->DrawRect((_int64) COLOR::ARGB(0, 0, 0), 1.0f, 0, rect);
		}
	}
}

void CTreeNodeMe::OnPaintNode( CPaintMe *paint, const RECT& rect )
{
	String collapsedImg = m_tree->GetCollapsedNodeImage();
	if (m_expended)
	{
		String expendedImg = m_tree->GetExpendedNodeImage();
		if ((int)expendedImg.length() > 0)
		{
			paint->DrawImage(expendedImg.c_str(), rect);
			return;
		}
	}
	else if ((int)collapsedImg.length() > 0)
	{
		paint->DrawImage(collapsedImg.c_str(), rect);
		return;
	}
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	POINT points[3];
	if (m_expended)
	{
		points[0].x = rect.left;
		points[0].y = rect.top;
		points[1].x = rect.left + width;
		points[1].y = rect.top;
		points[2].x = rect.left + width / 2;
		points[2].y = rect.top + height;
	}
	else
	{
		points[0].x = rect.left;
		points[0].y = rect.top;
		points[1].x = rect.left;
		points[1].y = rect.top + height;
		points[2].x = rect.left + width;
		points[2].y = rect.top + height / 2;
	}
	CGridMe *grid = GetGrid();
	paint->FillPolygon(grid->GetForeColor(), points, 3);
}

void CTreeNodeMe::OnPaint( CPaintMe *paint, const RECT& rect, const RECT& clipRect, bool isAlternate )
{
	int clipW = clipRect.right - clipRect.left;
	int clipH = clipRect.bottom - clipRect.top;
	CGridMe *grid = GetGrid();
	CGridRowMe *row = GetRow();
	if (clipW > 0 && clipH > 0 && grid && GetColumn() && row && GetTargetColumn())
	{
		int height = rect.bottom - rect.top;
		FONT *font = 0;
		_int64 eMPTY = COLOR_EMPTY;
		_int64 dwPenColor = COLOR_EMPTY;
		bool autoEllipsis = m_tree->AutoEllipsis();
		GridCellStyle *style = GetStyle();
		if (style)
		{
			if (style->AutoEllipsis())
			{
				autoEllipsis = style->AutoEllipsis();
			}
			eMPTY = style->GetBackColor();
			if (style->GetFont())
			{
				font = style->GetFont();
			}
			dwPenColor = style->GetForeColor();
		}
		CGridRowStyleMe *rowStyle = grid->GetRowStyle();
		if (isAlternate)
		{
			CGridRowStyleMe *alternateRowStyle = grid->GetAlternateRowStyle();
			if (alternateRowStyle)
			{
				rowStyle = alternateRowStyle;
			}
		}
		if (rowStyle)
		{
			bool selected = false;
			vector<CGridRowMe*> selectedRows = grid->GetSelectedRows();
			int count = (int)selectedRows.size();
			for (int i = 0; i < count; i++)
			{
				if (selectedRows[i] == row)
				{
					selected = true;
					break;
				}
			}
			if (eMPTY == COLOR_EMPTY)
			{
				if (selected)
				{
					eMPTY = rowStyle->GetSelectedBackColor();
				}
				else if (GetRow() == GetGrid()->GetHoveredRow())
				{
					eMPTY = rowStyle->GetHoveredBackColor();
				}
				else
				{
					eMPTY = rowStyle->GetBackColor();
				}
			}
			if (font == 0)
			{
				font = rowStyle->GetFont();
			}
			if (dwPenColor == COLOR_EMPTY)
			{
				if (selected)
				{
					dwPenColor = rowStyle->GetSelectedForeColor();
				}
				else if (GetRow() == GetGrid()->GetHoveredRow())
				{
					dwPenColor = rowStyle->GetHoveredForeColor();
				}
				else
				{
					dwPenColor = rowStyle->GetForeColor();
				}
			}
		}
		paint->FillRect(eMPTY, rect);		
		int pos = 0;
		CHScrollBarMe *hScrollBar = grid->GetHScrollBar();
		if (hScrollBar && hScrollBar->IsVisible())
		{
			pos = hScrollBar->GetPos();
		}

		RECT bounds = GetTargetColumn()->GetBounds();
		bounds.left += GetGrid()->GetHorizontalOffset() - pos;
		bounds.top += GetGrid()->GetVerticalOffset() - pos;
		int left = bounds.left;
		if (m_tree->HasCheckBoxes())
		{
			int cw = m_tree->GetCheckBoxSize().cx;
			int ch = m_tree->GetCheckBoxSize().cy;
			RECT rect3 = {left, rect.top + ((height - ch) / 2), rect3.left + cw, rect3.top + ch};
			OnPaintCheckBox(paint, rect3);
			left += cw + 10;
		}
		int cx = m_tree->GetNodeSize().cx;
		int cy = m_tree->GetNodeSize().cy;
		if ((int)m_nodes.size() > 0)
		{
			RECT nodeRect = {left, rect.top + ((height - cy) / 2), nodeRect.left + cx, nodeRect.top + cy};
			OnPaintNode(paint, nodeRect);
		}
		left += cx + 10;
		m_indent = left;
		String paintText = GetPaintText();
		if ((int)paintText.length() > 0)
		{
			SIZE size = paint->TextSize(paintText.c_str(), font);
			RECT tRect = {left, rect.top + (row->GetHeight() - size.cy) / 2, tRect.left + size.cx, tRect.top + size.cy};
			if (autoEllipsis && (tRect.right < clipRect.right || tRect.bottom < clipRect.bottom))
			{
				if (tRect.right < clipRect.right)
				{
					tRect.right = clipRect.right;
				}
				if (tRect.bottom < clipRect.bottom)
				{
					tRect.bottom = clipRect.bottom;
				}
				paint->DrawTextAutoEllipsis(paintText.c_str(), dwPenColor, font, tRect);
			}
			else
			{
				paint->DrawText(paintText.c_str(), dwPenColor, font, tRect);
			}
		}
	}
	OnPaintControl(paint, rect, clipRect);
}

void CTreeNodeMe::OnRemovingNode()
{
	m_indent = 0;
	CGridRowMe *row = GetRow();
	if (row)
	{
		if ((int)m_nodes.size() > 0)
		{
			int num = (int)m_nodes.size();
			for (int j = 0; j < num; j++)
			{
				m_nodes[j]->OnRemovingNode();
			}
		}
		m_tree->RemoveRow(row);
		row->ClearCells();
		SetRow(0);
		vector<CGridRowMe*> rows = m_tree->GetRows();
		int count = (int)rows.size();
		for (int i = 0; i < count; i++)
		{
			rows[i]->SetIndex(i);
		}
		m_targetColumn = 0;
	}
}

void CTreeNodeMe::RemoveNode( CTreeNodeMe *node )
{
	for (vector<CTreeNodeMe*>::iterator it = m_nodes.begin(); it != m_nodes.end(); it++)
	{
		if (*it == node)
		{
			node->OnRemovingNode();
			m_nodes.erase(it);
			break;
		}
	}
}

void CTreeNodeMe::SetProperty( const String& name, const String& value )
{
	if (name == L"allowdragin")
	{
		SetAllowDragIn(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"allowdragout")
	{
		SetAllowDragOut(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"checked")
	{
		SetChecked(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"expended")
	{
		SetExpended(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"value")
	{
		SetValue(value);
	}
	else
	{
		CGridCellMe::SetProperty(name, value);
	}
}

void CTreeNodeMe::SetString( const String& value )
{
	m_text = value;
}
