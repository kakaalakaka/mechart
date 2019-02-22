#include "..\\stdafx.h"
#include "..\\include\\TextBox\\CTextBox.h"
#include "..\\include\\Base\\CMathLib.h"
using namespace MeLib;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CTextBoxMe::CursorDown()
{
	CControlHostMe *host = GetNative()->GetHost();
	int num = -1;
	int num2 = -1;
	int rangeSize = (int)m_ranges.size();
	int stopMovingIndex = (m_selectionStart + m_selectionLength < rangeSize - 1) ? m_selectionStart + m_selectionLength : rangeSize - 1;
	if (host->IsKeyPress(0x10))
	{
		stopMovingIndex = m_stopMovingIndex;
	}
	else if (m_selectionLength > 0)
	{
		m_selectionLength = 1;
	}
	int lineSize = (int)m_lines.size();
	bool flag = false;
	for (int i = 0; i < lineSize; i++)
	{
		WordLine wordLine = m_lines[i];
		for (int j = wordLine.m_start; j <= wordLine.m_end; j++)
		{
			if ((!flag && j == stopMovingIndex) && (j == wordLine.m_start && i > 0))
			{
				i = 0;
				stopMovingIndex--;
				flag = true;
				break;
			}
			if (j >= stopMovingIndex && j < rangeSize)
			{
				int num8 = i;
				int num9 = j - wordLine.m_start;
				if (j == stopMovingIndex)
				{
					num = num9;
					num2 = num8;
				}
				else if (num8 == (num2 + 1))
				{
					bool flag2 = false;
					if (j < (rangeSize - 1))
					{
						if (j == wordLine.m_end)
						{
							flag2 = true;
						}
					}
					else
					{
						flag2 = true;
					}
					if (!flag2 && (num9 >= num))
					{
						flag2 = true;
					}
					if (flag2)
					{
						if (host->IsKeyPress(0x10))
						{
							SetMovingIndex(m_startMovingIndex, j);
						}
						else
						{
							m_selectionStart = j;
							m_selectionLength = 0;
							m_startMovingIndex = m_selectionStart;
							m_stopMovingIndex = m_selectionStart;
						}
						m_showCursor = true;
						StartTimer(m_timerID, TICK);
						return;
					}
				}
			}
		}
	}
}

void CTextBoxMe::CursorEnd()
{
	CControlHostMe *host = GetNative()->GetHost();
	int rangeSize = (int)m_ranges.size();
	int stopMovingIndex = (m_selectionStart + m_selectionLength < rangeSize - 1) ? m_selectionStart + m_selectionLength : rangeSize - 1;
	if (host->IsKeyPress(0x10))
	{
		stopMovingIndex = m_stopMovingIndex;
	}
	int lineSize = (int)m_lines.size();
	for (int i = 0; i < lineSize; i++)
	{
		WordLine wordLine = m_lines[i];
		for (int j = wordLine.m_start; j <= wordLine.m_end; j++)
		{
			if (j == stopMovingIndex)
			{
				if ((j == wordLine.m_start) && (i > 0))
				{
					wordLine = m_lines[i - 1];
				}
				if (host->IsKeyPress(0x10))
				{
					SetMovingIndex(m_startMovingIndex, wordLine.m_end + 1);
				}
				else
				{
					m_selectionStart = wordLine.m_end + 1;
					m_selectionLength = 0;
					m_startMovingIndex = m_selectionStart;
					m_stopMovingIndex = m_selectionStart;
				}
				m_showCursor = true;
				StartTimer(m_timerID, TICK);
				return;
			}
		}
	}
}

void CTextBoxMe::CursorHome()
{
	CControlHostMe *host = GetNative()->GetHost();
	int count = (int)m_ranges.size();
	int stopMovingIndex = (m_selectionStart < (count - 1)) ? m_selectionStart : (count - 1);
	if (host->IsKeyPress(0x10))
	{
		stopMovingIndex = m_stopMovingIndex;
	}
	int lineSize = (int)m_lines.size();
	for (int i = 0; i < lineSize; i++)
	{
		WordLine ea = m_lines[i];
		for (int j = ea.m_start; j <= ea.m_end; j++)
		{
			if (j == stopMovingIndex)
			{
				if (j == ea.m_start && i > 0)
				{
					ea = m_lines[i - 1];
				}
				if (host->IsKeyPress(0x10))
				{
					SetMovingIndex(m_startMovingIndex, ea.m_start + 1);
				}
				else
				{
					m_selectionStart = ea.m_start + 1;
					m_selectionLength = 0;
					m_startMovingIndex = m_selectionStart;
					m_stopMovingIndex = m_selectionStart;
				}
				m_showCursor = true;
				StartTimer(m_timerID, TICK);
				return;
			}
		}
	}
}

void CTextBoxMe::CursorLeft()
{
	if (GetNative()->GetHost()->IsKeyPress(0x10))
	{
		SetMovingIndex(m_startMovingIndex, m_stopMovingIndex - 1);
	}
	else
	{
		if (m_selectionStart > 0)
		{
			m_selectionStart--;
		}
		m_selectionLength = 0;
		m_startMovingIndex = m_selectionStart;
		m_stopMovingIndex = m_selectionStart;
	}
}

void CTextBoxMe::CursorRight()
{
	if (GetNative()->GetHost()->IsKeyPress(0x10))
	{
		SetMovingIndex(m_startMovingIndex, m_stopMovingIndex + 1);
	}
	else
	{
		int count = (int)m_ranges.size();
		int num2 = ((m_selectionStart + m_selectionLength) < (count - 1)) ? (m_selectionStart + m_selectionLength) : (count - 1);
		if (num2 < count)
		{
			m_selectionStart = num2 + 1;
		}
		m_selectionLength = 0;
		m_startMovingIndex = m_selectionStart;
		m_stopMovingIndex = m_selectionStart;
	}
}

void CTextBoxMe::CursorUp()
{
	CControlHostMe *host = GetNative()->GetHost();
	int num = -1;
	int num2 = -1;
	int count = (int)m_ranges.size();
	int stopMovingIndex = (m_selectionStart < (count - 1)) ? m_selectionStart : (count - 1);
	if (host->IsKeyPress(0x10))
	{
		stopMovingIndex = m_stopMovingIndex;
	}
	else if (m_selectionLength > 0)
	{
		m_selectionLength = 1;
	}
	int lineSize = (int)m_lines.size();
	for (int i = lineSize - 1; i >= 0; i--)
	{
		WordLine ea = m_lines[i];
		for (int j = ea.m_end; j >= ea.m_start; j--)
		{
			if ((j >= 0) && (j <= stopMovingIndex))
			{
				int num8 = i;
				int num9 = j - ea.m_start;
				if (j == stopMovingIndex)
				{
					num = num9;
					num2 = num8;
				}
				else if ((num8 == (num2 - 1)) && (num9 <= num))
				{
					if (host->IsKeyPress(0x10))
					{
						SetMovingIndex(m_startMovingIndex, j);
					}
					else
					{
						m_selectionStart = j;
						m_selectionLength = 0;
						m_startMovingIndex = m_selectionStart;
						m_stopMovingIndex = m_selectionStart;
					}
					m_showCursor = true;
					StartTimer(m_timerID, TICK);
					return;
				}
			}
		}
	}
}

void CTextBoxMe::DeleteWord()
{
	String text = GetText();
	int textLength = (int)text.length();
	if (textLength > 0)
	{
		int oldLines = (int)m_lines.size();
		String left;
		String right;
		int startIndex = -1;
		if (m_selectionLength > 0)
		{
			left = (m_selectionStart > 0) ? text.substr(0, m_selectionStart) : L"";
			startIndex = m_selectionStart + m_selectionLength;
		}
		else
		{
			left = (m_selectionStart > 0) ? text.substr(0, m_selectionStart - 1) : L"";
			startIndex = m_selectionStart + m_selectionLength;
			if (m_selectionStart > 0)
			{
				m_selectionStart--;
			}
		}
		if (startIndex < textLength)
		{
			right = text.substr(startIndex);
		}
		String newText = left + right;
		m_text = newText;
		textLength = (int)newText.length();
		if (textLength == 0)
		{
			m_selectionStart = 0;
		}
		else if (m_selectionStart > textLength)
		{
			m_selectionStart = textLength;
		}
		m_selectionLength = 0;
	}
}

void CTextBoxMe::InsertWord( const String& str )
{
	String text = GetText();
	int textLength = (int)text.length();
	if (textLength == 0 || m_selectionStart == 0)
	{
		text = text + str;
		m_text = text;
		m_selectionStart = textLength;
	}
	else
	{
		int sIndex = m_selectionStart > textLength ? textLength : m_selectionStart;
		String left = sIndex > 0 ? text.substr(0, sIndex) : L"";
		String right;
		int rightIndex = m_selectionStart + (m_selectionLength == 0 ? 0 : m_selectionLength);
		if (rightIndex < textLength)
		{
			right = text.substr(rightIndex);
		}
		text = left + str + right;
		m_text = text;
		m_selectionStart += (int)str.length();
		if (m_selectionStart > textLength)
		{
			m_selectionStart = textLength;
		}
		m_selectionLength = 0;
	}
}

bool CTextBoxMe::IsLineVisible( int index, double visiblePercent )
{
	int rangeSize = (int)m_ranges.size();
	if ((rangeSize <= 0 || index < 0) || index >= rangeSize)
	{
		return false;
	}
	int top = 0;
	int scrollV = 0;
	int sch = 0;
	CHScrollBarMe *hScrollBar = GetHScrollBar();
	CVScrollBarMe *vScrollBar = GetVScrollBar();
	if (hScrollBar && hScrollBar->IsVisible())
	{
		sch = hScrollBar->GetHeight();
	}
	if (vScrollBar && vScrollBar->IsVisible())
	{
		scrollV = -vScrollBar->GetPos();
	}
	top = scrollV;
	int cell = 1;
	int floor = GetHeight() - cell - sch - 1;
	RECTF indexRect = m_ranges[index];
	int indexTop = ((int) indexRect.top) + top;
	int indexBottom = ((int) indexRect.bottom) + top;
	return CMathLibMe::IsLineVisible(indexTop, indexBottom, cell, floor, m_lineHeight, visiblePercent);
}

void CTextBoxMe::SetMovingIndex( int sIndex, int eIndex )
{
	int length = (int)GetText().length();
	if (length > 0)
	{
		if (sIndex < 0)
		{
			sIndex = 0;
		}
		if (sIndex > length)
		{
			sIndex = length;
		}
		if (eIndex < 0)
		{
			eIndex = 0;
		}
		if (eIndex > length)
		{
			eIndex = length;
		}
		m_startMovingIndex = sIndex;
		m_stopMovingIndex = eIndex;
		m_selectionStart = min(m_startMovingIndex, m_stopMovingIndex);
		m_selectionLength = abs((int) (m_startMovingIndex - m_stopMovingIndex));
	}
}

CTextBoxMe::CTextBoxMe()
{
	m_isKeyDown = false;
	m_isMouseDown = false;
	m_lineHeight = 20;
	m_multiline = false;
	m_offsetX = 0;
	m_readOnly = false;
	m_rightToLeft = false;
	m_selectionBackColor = COLOR::ARGB(10, 36, 106);
	m_selectionForeColor = COLOR::ARGB(255, 255, 255);
	m_selectionLength = 0;
	m_selectionStart = -1;
	m_showCursor = false;
	m_startMovingIndex = -1;
	m_stopMovingIndex = -1;
	m_tempTextForeColor = COLOR_DISABLEDCONTROLTEXT;
	m_textAlign = HorizontalAlignMe_Left;
	m_textChanged = false;
	m_wordWrap = false;
	TICK = 500;
	m_tick = 500;
	m_timerID = GetNewTimerID();
	m_passwordChar = L'\0';
	SetCursor(CursorsMe_IBeam);
	SIZE sz = {100, 20};
	SetSize(sz);
	SetTabStop(true);
}

CTextBoxMe::~CTextBoxMe()
{
	StopTimer(m_timerID);
	m_lines.clear();
	m_ranges.clear();
	m_wordsSize.clear();
	while(!m_redoStack.empty()){
		m_redoStack.pop();
	}
	while(!m_undoStack.empty()){
		m_undoStack.pop();
	}
}

int CTextBoxMe::GetLinesCount()
{
	return (int)m_lines.size();
}

int CTextBoxMe::GetLineHeight()
{
	return m_lineHeight;
}

void CTextBoxMe::SetLineHeight( int lineHeight )
{
	m_lineHeight = lineHeight;
}

vector<WordLine> CTextBoxMe::GetLines()
{
	return m_lines;
}

bool CTextBoxMe::IsMultiline()
{
	return m_multiline;
}

void CTextBoxMe::SetMultiline( bool multiline )
{
	if (m_multiline != multiline)
	{
		m_multiline = multiline;
		m_textChanged = true;
	}
	SetShowVScrollBar(m_multiline);
}

wchar_t CTextBoxMe::GetPasswordChar()
{
	return m_passwordChar;
}

void CTextBoxMe::SetPasswordChar( wchar_t passwordChar )
{
	m_passwordChar = passwordChar;
	m_textChanged = true;
}

bool CTextBoxMe::IsReadOnly()
{
	return m_readOnly;
}

void CTextBoxMe::SetReadOnly( bool readOnly )
{
	m_readOnly = readOnly;
}

bool CTextBoxMe::IsRightToLeft()
{
	return m_rightToLeft;
}

void CTextBoxMe::SetRightToLeft( bool rightToLeft )
{
	m_rightToLeft = rightToLeft;
	m_textChanged = true;
}

_int64 CTextBoxMe::GetSelectionBackColor()
{
	return m_selectionBackColor;
}

void CTextBoxMe::SetSelectionBackColor( _int64 selectionBackColor )
{
	m_selectionBackColor = selectionBackColor;
}

_int64 CTextBoxMe::GetSelectionForeColor()
{
	return m_selectionForeColor;
}

void CTextBoxMe::SetSelectionForeColor( _int64 selectionForeColor )
{
	m_selectionForeColor = selectionForeColor;
}

int CTextBoxMe::GetSelectionLength()
{
	return m_selectionLength;
}

void CTextBoxMe::SetSelectionLength( int selectionLength )
{
	m_selectionLength = selectionLength;
}

int CTextBoxMe::GetSelectionStart()
{
	return m_selectionStart;
}

void CTextBoxMe::SetSelectionStart( int selectionStart )
{
	m_selectionStart = selectionStart;
	if (m_selectionStart > (int)GetText().length())
	{
		m_selectionStart = (int)GetText().length();
	}
}

String CTextBoxMe::GetTempText()
{
	return m_tempText;
}

void CTextBoxMe::SetTempText( const String& tempText )
{
	m_tempText = tempText;
}

_int64 CTextBoxMe::GetTempTextForeColor()
{
	return m_tempTextForeColor;
}

void CTextBoxMe::SetTempTextForeColor( _int64 tempTextForeColor )
{
	m_tempTextForeColor = tempTextForeColor;
}

HorizontalAlignMe CTextBoxMe::GetTextAlign()
{
	return m_textAlign;
}

void CTextBoxMe::SetTextAlign( HorizontalAlignMe textAlign )
{
	m_textAlign = textAlign;
}

bool CTextBoxMe::IsWordWrap()
{
	return m_wordWrap;
}

void CTextBoxMe::SetWordWrap( bool wordWrap )
{
	if (m_wordWrap != wordWrap)
	{
		m_wordWrap = wordWrap;
		m_textChanged = true;
	}
	SetShowHScrollBar(m_wordWrap);
}

bool CTextBoxMe::CanRedo()
{
	return (int)m_redoStack.size() > 0;
}

bool CTextBoxMe::CanUndo()
{
	return (int)m_undoStack.size() > 0;
}

void CTextBoxMe::ClearRedoUndo()
{
	while (!m_undoStack.empty())
		m_undoStack.pop();

	while (!m_redoStack.empty())
		m_redoStack.pop();
}

int CTextBoxMe::GetContentHeight()
{
	int contentHeight = DivMe::GetContentHeight();
	int bottom = 0;
	int count = (int)m_ranges.size();
	for (int i = 0; i < count; i++)
	{
		if (bottom < m_ranges[i].bottom)
		{
			bottom = (int) m_ranges[i].bottom;
		}
	}
	if (contentHeight <= bottom)
	{
		return bottom;
	}
	return contentHeight;
}

int CTextBoxMe::GetContentWidth()
{
	int wmax = DivMe::GetContentWidth();
	int cwidth = 0;
	int rangeSize = (int)m_ranges.size();
	for (int i = 0; i < rangeSize; i++)
	{
		if (cwidth < ((RECTF)m_ranges.at(i)).right)
		{
			cwidth = (int)((RECTF)m_ranges.at(i)).right;
		}
	}
	return wmax > cwidth ? wmax : cwidth;
}

String CTextBoxMe::GetControlType()
{
	return L"TextBox";
}

void CTextBoxMe::GetProperty( const String& name, String *value, String *type )
{
	if (name == L"lineheight")
	{
		*type = L"int";
		*value = CStrMe::ConvertIntToStr(GetLineHeight());
	}
	else if (name == L"multiline")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsMultiline());
	}
	else if (name == L"passwordchar")
	{
		*type = L"text";
		value[0] = GetPasswordChar();
	}
	else if (name == L"readonly")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsReadOnly());
	}
	else if (name == L"righttoleft")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsRightToLeft());
	}
	else if (name == L"selectionbackcolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetSelectionBackColor());
	}
	else if (name == L"selectionforecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetSelectionForeColor());
	}
	else if (name == L"temptext")
	{
		*type = L"text";
		*value = GetTempText();
	}
	else if (name == L"temptextforecolor")
	{
		*type = L"color";
		*value = CStrMe::ConvertColorToStr(GetTempTextForeColor());
	}
	else if (name == L"textalign")
	{
		*type = L"enum:HorizontalAlignMe";
		*value = CStrMe::ConvertHorizontalAlignToStr(GetTextAlign());
	}
	else if (name == L"wordwrap")
	{
		*type = L"bool";
		*value = CStrMe::ConvertBoolToStr(IsWordWrap());
	}
	else
	{
		DivMe::GetProperty(name, value, type);
	}
}

vector<String> CTextBoxMe::GetPropertyNames()
{
	vector<String> propertyNames = DivMe::GetPropertyNames();
	propertyNames.push_back(L"LineHeight");
	propertyNames.push_back(L"Multiline");
	propertyNames.push_back(L"PasswordChar");
	propertyNames.push_back(L"ReadOnly");
	propertyNames.push_back(L"RightToLeft");
	propertyNames.push_back(L"SelectionBackColor");
	propertyNames.push_back(L"SelectionForeColor");
	propertyNames.push_back(L"TempText");
	propertyNames.push_back(L"TempTextForeColor");
	propertyNames.push_back(L"TextAlign");
	propertyNames.push_back(L"WordWrap");
	return propertyNames;
}

String CTextBoxMe::GetSelectionText()
{
	String text = GetText();
	int length = (int)text.length();
	if (length > 0 && m_selectionStart != length)
	{
		return text.substr(m_selectionStart, m_selectionLength);
	}
	return text;
}

void CTextBoxMe::OnChar( wchar_t ch )
{
	if (!m_readOnly)
	{
		DivMe::OnChar(ch);
		if (!GetNative()->GetHost()->IsKeyPress(0x11))
		{
			int count = (int)m_lines.size();
			if ((ch != L'\b') || (!m_multiline && (ch == L'\r')))
			{
				String text = GetText();
				String ss(1, ch);
				InsertWord(ss);
				OnTextChanged();
				if (m_textChanged)
				{
					m_undoStack.push(text);
				}
			}
			Invalidate();
			int newCount = (int)m_lines.size();
			if (newCount != count)
			{
				CVScrollBarMe *vScrollBar = GetVScrollBar();
				if (vScrollBar)
				{
					int pos = vScrollBar->GetPos();
					pos += m_lineHeight * (newCount - count);
					vScrollBar->SetPos(pos);
					Invalidate();
				}
			}
		}
	}
}

void CTextBoxMe::OnCopy()
{
	String selectionText = GetSelectionText();
	int length = (int)selectionText.length();
	if (length > 0)
	{
		string str;
		CStrMe::wstringTostring(str, selectionText);
		GetNative()->GetHost()->Copy(str);
		DivMe::OnCopy();
	}
}

void CTextBoxMe::OnCut()
{
	if (!m_readOnly)
	{
		OnCopy();
		int count = (int)m_lines.size();
		String text = GetText();
		DeleteWord();
		OnTextChanged();
		if (m_textChanged)
		{
			m_undoStack.push(text);
		}
		Invalidate();
		int newCount = (int)m_lines.size();
		if (newCount != count)
		{
			CVScrollBarMe *vScrollBar = GetVScrollBar();
			if (vScrollBar)
			{
				int pos = vScrollBar->GetPos();
				pos += m_lineHeight * (newCount - count);
				vScrollBar->SetPos(pos);
				Invalidate();
			}
		}
		CControlMe::OnCut();
	}
}

void CTextBoxMe::OnGotFocus()
{
	CControlMe::OnGotFocus();
	m_showCursor = true;
	Invalidate();
	StartTimer(m_timerID, TICK);
}

void CTextBoxMe::OnKeyDown( char key )
{
	m_isKeyDown = true;
	if (GetNative()->GetHost()->IsKeyPress(0x11))
	{
		DivMe::OnKeyDown(key);
		if (key == 'A')
		{
			SelectAll();
		}
		else if (key == 'Y')
		{
			Redo();
		}
		else if (key == 'Z')
		{
			Undo();
		}
	}
	else if (key >= '#' && key <= '(')
	{
		if (key == '&' || key == '(')
		{
			DivMe::CallKeyEvents(0x12, key);
			if ((int)m_lines.size() > 1)
			{
				int lineHeight = 0;
				if (key == '&')
				{
					CursorUp();
					if (!IsLineVisible(m_stopMovingIndex, 0.6))
					{
						lineHeight = -m_lineHeight;
					}
				}
				else if (key == '(')
				{
					CursorDown();
					if (!IsLineVisible(m_stopMovingIndex, 0.6))
					{
						lineHeight = m_lineHeight;
					}
				}
				CVScrollBarMe *vScrollBar = GetVScrollBar();
				if (vScrollBar && vScrollBar->IsVisible())
				{
					int pos = vScrollBar->GetPos();
					pos += lineHeight;
					vScrollBar->SetPos(pos);
					vScrollBar->Update();
				}
			}
		}
		else
		{
			DivMe::OnKeyDown(key);
			if (key == '#')
			{
				CursorEnd();
			}
			else if (key == '$')
			{
				CursorHome();
			}
			else if (key == '%')
			{
				CursorLeft();
			}
			else if (key == '\'')
			{
				CursorRight();
			}
		}
	}
	else
	{
		DivMe::OnKeyDown(key);
		if (key == '\x001b')
		{
			SetFocused(false);
		}
		else if ((key == '\b' || key == '.') && !m_readOnly)
		{
			int count = (int)m_lines.size();
			String text = GetText();
			DeleteWord();
			OnTextChanged();
			if (m_textChanged)
			{
				m_undoStack.push(text);
			}
			Invalidate();
			int newCount = (int)m_lines.size();
			if (newCount != count)
			{
				CVScrollBarMe *vScrollBar = GetVScrollBar();
				if (vScrollBar)
				{
					int pos = vScrollBar->GetPos();
					pos += m_lineHeight * (newCount - count);
					vScrollBar->SetPos(pos);
					Invalidate();
				}
			}
		}
	}
	Invalidate();
}

void CTextBoxMe::OnKeyUp( char key )
{
	CControlMe::OnKeyUp(key);
	if (!GetNative()->GetHost()->IsKeyPress(0x10) && !m_isMouseDown)
	{
		m_startMovingIndex = m_selectionStart;
		m_stopMovingIndex = m_selectionStart;
	}
	m_isKeyDown = false;
}

void CTextBoxMe::OnLostFocus()
{
	CControlMe::OnLostFocus();
	StopTimer(m_timerID);
	m_isKeyDown = false;
	m_showCursor = false;
	m_selectionLength = 0;
	Invalidate();
}

void CTextBoxMe::OnMouseDown( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	DivMe::OnMouseDown(mp, button, clicks, delta);
	if (button == MouseButtonsMe_Left)
	{
		if (clicks != 1)
		{
			if (clicks == 2 && !m_multiline)
			{
				SelectAll();
			}
		}
		else
		{
			int sIndex = -1;
			int linesCount = (int)m_lines.size();
			m_selectionLength = 0;
			m_startMovingIndex = -1;
			m_stopMovingIndex = -1;
			if (linesCount > 0)
			{
				CHScrollBarMe *hScrollBar = GetHScrollBar();
				CVScrollBarMe *vScrollBar = GetVScrollBar();
				int scrollH = hScrollBar && hScrollBar->IsVisible() ? hScrollBar->GetPos() : 0;
				int scrollV = vScrollBar && vScrollBar->IsVisible() ? vScrollBar->GetPos() : 0;
				scrollH += m_offsetX;
				int x = mp.x + scrollH;
				int y = mp.y + scrollV;
				RECTF lastRange = {0};
				int rangeSize = (int)m_ranges.size();
				if (rangeSize > 0)
				{
					lastRange = m_ranges[rangeSize - 1];
				}
				for (int i = 0; i < linesCount; i++)
				{
					WordLine line = m_lines[i];
					for (int j = line.m_start; j <= line.m_end; j++)
					{
						RECTF rect = m_ranges[j];
						if (i == linesCount - 1)
						{
							rect.bottom += 3.0f;
						}
						if ((y >= rect.top) && (y <= rect.bottom))
						{
							float sub = (rect.right - rect.left) / 2.0f;
							if ((((x >= (rect.left - sub)) && 
								(x <= (rect.right - sub))) 
								|| ((j == line.m_start)
									&& (x <= (rect.left + sub)))) 
								|| ((j == line.m_end) 
									&& (x >= (rect.right - sub))))
							{
								if ((j == line.m_end) && (x >= (rect.right - sub)))
								{
									sIndex = j + 1;
								}
								else
								{
									sIndex = j;
								}
								break;
							}
						}
					}
					if (sIndex != -1)
					{
						break;
					}
				}
				if ((sIndex == -1) && ((((y >= lastRange.top) && (y <= lastRange.bottom)) 
					&& (x > lastRange.right)) || (y >= lastRange.bottom)))
				{
					sIndex = rangeSize;
				}
			}
			if (sIndex != -1)
			{
				m_selectionStart = sIndex;
			}
			else
			{
				m_selectionStart = 0;
			}
			m_startMovingIndex = m_selectionStart;
			m_stopMovingIndex = m_selectionStart;
		}
	}
	m_isMouseDown = true;
	m_showCursor = true;
	StartTimer(m_timerID, TICK);
	Invalidate();
}

void CTextBoxMe::OnMouseMove( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	DivMe::OnMouseMove(mp, button, clicks, delta);
	if (m_isMouseDown)
	{
		int count = (int)m_lines.size();
		if (count > 0)
		{
			int eIndex = -1;
			CHScrollBarMe *hScrollBar = GetHScrollBar();
			CVScrollBarMe *vScrollBar = GetVScrollBar();
			int scrollH = hScrollBar && hScrollBar->IsVisible() ? hScrollBar->GetPos() : 0;
			int scrollV = vScrollBar && vScrollBar->IsVisible() ? vScrollBar->GetPos() : 0;
			scrollH += m_offsetX;
			POINT point = mp;
			if (point.x < 0)
			{
				point.x = 0;
			}
			if (point.y < 0)
			{
				point.y = 0;
			}
			int x = point.x + scrollH;
			int y = point.y + scrollV;
			int rangeCount = (int)m_ranges.size();
			if (rangeCount > 0)
			{
				RECTF local1 = m_ranges[rangeCount - 1];
			}
			for (int i = 0; i < count; i++)
			{
				WordLine line = m_lines[i];
				for (int j = line.m_start; j <= line.m_end; j++)
				{
					RECTF rect = m_ranges[j];
					if (i == count - 1)
					{
						rect.bottom += 3.0f;
					}
					if (((eIndex == -1) && (y >= rect.top)) && (y <= rect.bottom))
					{
						float sub = (rect.right - rect.left) / 2.0f;
						if ((((x >= (rect.left - sub)) && (x <= (rect.right - sub))) 
							|| ((j == line.m_start) && (x <= (rect.left + sub)))) 
							|| ((j == line.m_end) && (x >= (rect.right - sub))))
						{
							if ((j == line.m_end) && (x >= (rect.right - sub)))
							{
								eIndex = j + 1;
							}
							else
							{
								eIndex = j;
							}
						}
					}
				}
				if (eIndex != -1)
				{
					break;
				}
			}
			if (eIndex != -1)
			{
				m_stopMovingIndex = eIndex;
			}
			if (m_startMovingIndex == m_stopMovingIndex)
			{
				m_selectionStart = m_startMovingIndex;
				m_selectionLength = 0;
			}
			else
			{
				m_selectionStart = (m_startMovingIndex < m_stopMovingIndex) ? m_startMovingIndex : m_stopMovingIndex;
				m_selectionLength = abs((int) (m_startMovingIndex - m_stopMovingIndex));
			}
			Invalidate();
		}
	}
}

void CTextBoxMe::OnMouseUp( const POINT& mp, MouseButtonsMe button, int clicks, int delta )
{
	m_isMouseDown = false;
	DivMe::OnMouseUp(mp, button, clicks, delta);
}

void CTextBoxMe::OnPaintForeground( CPaintMe *paint, const RECT& clipRect )
{
	String txtName = GetName();
	int width = GetWidth();
    int height = GetHeight();
    if ((width > 0) && (height > 0))
    {
        PADDING padding = GetPadding();
        CControlHostMe* host = GetNative()->GetHost();
		RECT rect = {0, 0, width, height};
        FONT* font = GetFont();
        SIZEF tSize = paint->TextSizeF(L" ", font);
        CHScrollBarMe* hScrollBar = GetHScrollBar();
        CVScrollBarMe* vScrollBar = GetVScrollBar();
        int vWidth = ((vScrollBar != 0) && vScrollBar->IsVisible()) ? ((vScrollBar->GetWidth() - padding.left) - padding.right) : 0;
        int scrollH = ((hScrollBar != 0) && hScrollBar->IsVisible()) ? hScrollBar->GetPos() : 0;
        int scrollV = ((vScrollBar != 0) && vScrollBar->IsVisible()) ? vScrollBar->GetPos() : 0;
        float strX = padding.left + 1;
        String text = GetText();
        if (text == L"")
        {
            text = L"";
        }
		int length = (int)text.length();
        SIZEF bSize = paint->TextSizeF(L"0", font);
        if (m_textChanged)
        {
            int line = 0;
            int count = 0;
            m_textChanged = !m_textChanged;
            m_lines.clear();
            m_ranges.clear();
            m_wordsSize.clear();
            for (int j = 0; j < length; j++)
            {
                if (j == 0)
                {
                    count = 0;
                    line++;
                    strX = padding.left + 1;
                    m_lines.push_back(WordLine(j, j));
                }
                wchar_t ch = text[j];
                String dch = L"";
				dch = ch;
                if (ch == L'\t')
                {
                    int addCount = 4 - (count % 4);
                    tSize.cx = bSize.cx * addCount;
                    tSize.cy = bSize.cy;
                    count += addCount;
                }
                else
                {
                    if (m_passwordChar != L'\0')
                    {
                        dch = m_passwordChar;
                    }
					tSize = paint->TextSizeF(dch.c_str(), font);
                    if (ch == L'\n')
                    {
                        tSize.cx = 0;
                    }
                    count++;
                }
                if (m_multiline)
                {
                    bool isNextLine = false;
                    if (ch == L'\r')
                    {
                        isNextLine = true;
                    }
                    else if (m_wordWrap && ((strX + tSize.cx) > (width - vWidth)))
                    {
                        isNextLine = true;
                    }
                    if (isNextLine)
                    {
                        count = 0;
                        line++;
                        strX = padding.left + 1;
                        m_lines.push_back(WordLine(j, j));
                        tSize.cx = 0;
                    }
                    else
                    {
                        m_lines[line - 1] = WordLine(m_lines[line - 1].m_start, j);
                    }
                }
                else
                {
                    m_lines[line - 1] = WordLine(m_lines[line - 1].m_start, j);
                }
				RECTF rangeRect = {strX, (float) (padding.top + (line - 1) * m_lineHeight),
					strX + tSize.cx + 2, (float) (padding.top + line * m_lineHeight)};
                m_ranges.push_back(rangeRect);
                m_wordsSize.push_back(tSize);
                strX += (int) ceil((double) tSize.cx+2);
            }
            if (m_rightToLeft)
            {
                int lcount = (int)m_lines.size();
                for (int k = 0; k < lcount; k++)
                {
                    WordLine ln = m_lines[k];
                    float lw = (width - vWidth - m_ranges[ln.m_end].right - m_ranges[ln.m_start].left) - 2;
                    if (lw > 0)
                    {
                        for (int m = ln.m_start; m <= ln.m_end; m++)
                        {
                            RECTF rangeRect = m_ranges[m];
                            rangeRect.left += lw;
                            rangeRect.right += lw;
                            m_ranges[m] = rangeRect;
                        }
                    }
                }
            }
            Update();
        }
        scrollH += m_offsetX;
		RECT tempRect = {0};
        int rangesSize = (int)m_ranges.size();
        if (!m_multiline)
        {
			RECTF firstRange = {0, 0, 0, 0};
            RECTF lastRange = {0, 0, 0, 0};
            if (rangesSize > 0)
            {
                firstRange = m_ranges[0];
                lastRange = m_ranges[rangesSize - 1];
            }
            int offsetX = m_offsetX;
            scrollH -= offsetX;
            if (m_textAlign == HorizontalAlignMe_Center)
            {
                offsetX = -((width - padding.right) - ((int) (lastRange.right - firstRange.left))) / 2;
            }
            else if (m_textAlign == HorizontalAlignMe_Right)
            {
                offsetX = -((int) (((width - padding.right) - (lastRange.right - firstRange.left)) - 3));
            }
            else if (lastRange.right > (width - padding.right))
            {
                int alwaysVisibleIndex = m_selectionStart + m_selectionLength;
                if (m_startMovingIndex != -1)
                {
                    alwaysVisibleIndex = m_startMovingIndex;
                }
                if (m_stopMovingIndex != -1)
                {
                    alwaysVisibleIndex = m_stopMovingIndex;
                }
                if (alwaysVisibleIndex > rangesSize - 1)
                {
                    alwaysVisibleIndex = rangesSize - 1;
                }
                if (alwaysVisibleIndex != -1)
                {
                    RECTF alwaysVisibleRange = m_ranges[alwaysVisibleIndex];
                    int cw = width - padding.left - padding.right;
                    if (alwaysVisibleRange.left - offsetX > cw - 10)
                    {
                        offsetX = (int) alwaysVisibleRange.right - cw + 3;
                        if (offsetX < 0)
                        {
                            offsetX = 0;
                        }
                    }
                    else if (alwaysVisibleRange.left - offsetX < 10)
                    {
                        offsetX -= ((int) bSize.cx) * 4;
                        if (offsetX < 0)
                        {
                            offsetX = 0;
                        }
                    }
                    if (offsetX > lastRange.right - cw)
                    {
                        offsetX = (int) lastRange.right - cw + 3;
                    }
                }
            }
            else if (m_textAlign == HorizontalAlignMe_Right)
            {
                offsetX = -((int) (width - padding.right - lastRange.right - firstRange.left - 3));
            }
            else
            {
                offsetX = 0;
            }
            m_offsetX = offsetX;
            scrollH += m_offsetX;
        }
        int lineCount = (int)m_lines.size();
        vector<RECTF> selectedRanges;
		vector<RECT> selectedWordsRanges;
        vector<wchar_t> selectedWords;
        for (int i = 0; i < lineCount; i++)
        {
            WordLine line = m_lines[i];
            for (int n = line.m_start; n <= line.m_end; n++)
            {
                wchar_t passwordChar = text[n];
                if ((passwordChar != L'\t') && (m_passwordChar > L'\0'))
                {
                    passwordChar = m_passwordChar;
                }
                RECTF rangeRect = m_ranges[n];
                rangeRect.left -= scrollH;
                rangeRect.top -= scrollV;
                rangeRect.right -= scrollH;
                rangeRect.bottom -= scrollV;
				RECT rRect = {rangeRect.left, rangeRect.top + ((m_lineHeight - m_wordsSize[n].cy) / 2), 
					rangeRect.right, rangeRect.top + ((m_lineHeight + m_wordsSize[n].cy) / 2)};
                if (rRect.right == rRect.left)
                {
                    rRect.right = rRect.left + 1;
                }
                if (host->GetIntersectRect(&tempRect, &rRect, &rect) > 0)
                {
                    if (((m_selectionLength > 0) && (n >= m_selectionStart)) && (n < (m_selectionStart + m_selectionLength)))
                    {
                        selectedWordsRanges.push_back(rRect);
                        selectedRanges.push_back(rangeRect);
                        selectedWords.push_back(passwordChar);
                    }
                    else
                    {
						String sss(1, passwordChar);
						paint->DrawText(sss.c_str(), GetPaintingForeColor(), font, rRect);
                    }
                }
            }
        }
        int selectedRangesSize = (int)selectedRanges.size();
        if (selectedRangesSize > 0)
        {
            int sIndex = 0;
            float right = 0;
            for (int i = 0; i < selectedRangesSize; i++)
            {
                RECTF rRect = selectedRanges[i];
                RECTF sRect = selectedRanges[i];
                bool newLine = !(rRect.top == sRect.top);
                if (newLine || i == selectedRangesSize - 1)
                {
                    int eIndex = i == selectedRangesSize - 1 ? i : i - 1;
                    RECTF eRect = selectedRanges[eIndex];
					RECT unionRect = {sRect.left, sRect.top, eRect.right + 1, sRect.bottom + 1};
                    if (newLine)
                    {
                        unionRect.right = (int) right;
                    }
                    paint->FillRect(m_selectionBackColor, unionRect);
                    for (int j = sIndex; j <= eIndex; j++)
                    {
						String sss(1, selectedWords[j]);
						paint->DrawText(sss.c_str(), m_selectionForeColor, font, selectedWordsRanges[j]);
					}
					sIndex = i;
                }
                right = rRect.right;
            }
            selectedRanges.clear();
            selectedWords.clear();
            selectedWordsRanges.clear();
        }
        if (((IsFocused() && !m_readOnly) && (m_selectionLength == 0)) && (m_isKeyDown || m_showCursor))
        {
            int selectionStart = m_selectionStart;
            if (selectionStart < 0)
            {
                selectionStart = 0;
            }
            if (selectionStart > length)
            {
                selectionStart = length;
            }
            int cursorX = 1;
            int cursorY = 0;
            if (length > 0)
            {
                if (selectionStart == 0)
                {
                    cursorX = (int) m_ranges[0].left;
                    cursorY = (int) m_ranges[0].top;
                }
                else
                {
                    cursorX = ((int) ceil((double) m_ranges[selectionStart - 1].right)) + 2;
                    cursorY = (int) ceil((double) m_ranges[selectionStart - 1].top);
                }
                cursorY += (m_lineHeight / 2) - (((int) tSize.cy) / 2);
            }
            else
            {
                cursorY = (m_lineHeight / 2) - (((int) tSize.cy) / 2);
            }
            if (m_isKeyDown || m_showCursor)
            {
				RECT cRect = {(float) (cursorX - scrollH - 1), (float) (cursorY - scrollV), 
					(float) (cursorX - scrollH + 1), cursorY + tSize.cy - scrollV};
                paint->FillRect(GetForeColor(), cRect);
            }
        }
		else if ((!IsFocused() && (int)text.length() == 0) 
			&& (m_tempText != L"" && (int)m_tempText.length() > 0))
        {
			RECT pRect = {0};
			SIZE pSize = paint->TextSize(m_tempText.c_str(), font);
            pRect.left = padding.left;
			pRect.top = (m_lineHeight - pSize.cy) / 2;
            pRect.right = pRect.left + pSize.cx;
            pRect.bottom = pRect.top + pSize.cy;
			paint->DrawText(m_tempText.c_str(), m_tempTextForeColor, font, pRect);
        }
    }
}

void CTextBoxMe::OnPaste()
{
	if (!m_readOnly)
	{
		string insert = GetNative()->GetHost()->Paste();
		String wstr;
		CStrMe::stringTowstring(wstr, insert);
		if ((int)wstr.length() > 0)
		{
			int oldLines = (int)m_lines.size();
			String text = GetText();
			InsertWord(wstr);
			OnTextChanged();
			if (m_textChanged)
			{
				m_undoStack.push(text);
			}
			Invalidate();
			int newLines = (int)m_lines.size();
			if (newLines != oldLines)
			{
				CVScrollBarMe *vScrollBar = GetVScrollBar();
				if (vScrollBar)
				{
					int pos = vScrollBar->GetPos();
					pos += m_lineHeight * (newLines - oldLines);
					vScrollBar->SetPos(pos);
					Invalidate();
				}
			}
			Update();
			CControlMe::OnPaste();
		}
	}
}

void CTextBoxMe::OnSizeChanged()
{
	CControlMe::OnSizeChanged();
	if (m_wordWrap)
	{
		m_textChanged = true;
		Invalidate();
	}
}

void CTextBoxMe::OnTabStop()
{
	CControlMe::OnTabStop();
	if (!m_multiline)
	{
		int length = (int)GetText().length();
		if (length > 0)
		{
			m_selectionStart = 0;
			m_selectionLength = length;
			OnTimer(m_timerID);
		}
	}
}

void CTextBoxMe::OnTextChanged()
{
	m_textChanged = true;
	CControlMe::OnTextChanged();
}

void CTextBoxMe::OnTimer( int timerID )
{
	CControlMe::OnTimer(timerID);
	if (m_timerID == timerID && IsVisible() && IsFocused() && !m_textChanged)
	{
		m_showCursor = !m_showCursor;
		Invalidate();
	}
}

void CTextBoxMe::Redo()
{
	if (CanRedo())
	{
		m_undoStack.push(GetText());
		SetText(m_redoStack.top());
		m_redoStack.pop();
	}
}

void CTextBoxMe::SelectAll()
{
	m_selectionStart = 0;
	m_selectionLength = (int)GetText().length();
}

void CTextBoxMe::SetProperty( const String& name, const String& value )
{
	if (name == L"lineheight")
	{
		SetLineHeight(CStrMe::ConvertStrToInt(value));
	}
	else if (name == L"multiline")
	{
		SetMultiline(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"passwordchar")
	{
		SetPasswordChar(value[0]);
	}
	else if (name == L"readonly")
	{
		SetReadOnly(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"righttoleft")
	{
		SetRightToLeft(CStrMe::ConvertStrToBool(value));
	}
	else if (name == L"selectionbackcolor")
	{
		SetSelectionBackColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"selectionforecolor")
	{
		SetSelectionForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"temptext")
	{
		SetTempText(value);
	}
	else if (name == L"temptextforecolor")
	{
		SetTempTextForeColor(CStrMe::ConvertStrToColor(value));
	}
	else if (name == L"textalign")
	{
		SetTextAlign(CStrMe::ConvertStrToHorizontalAlign(value));
	}
	else if (name == L"wordwrap")
	{
		SetWordWrap(CStrMe::ConvertStrToBool(value));
	}
	else
	{
		DivMe::SetProperty(name, value);
	}
}

void CTextBoxMe::Undo()
{
	if (CanUndo())
	{
		m_redoStack.push(GetText());
		SetText(m_undoStack.top());
		m_undoStack.pop();
	}
}

void CTextBoxMe::Update()
{
	DivMe::Update();
	if (GetNative())
	{
		CVScrollBarMe *vScrollBar = GetVScrollBar();
		if (vScrollBar)
		{
			vScrollBar->SetLineSize(m_lineHeight);
		}
	}
}