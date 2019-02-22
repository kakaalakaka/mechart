#include "..\\stdafx.h"
#include "..\\include\\Grid\\CGridCellExtends.h"
#include "..\\include\\Button\\CCheckBox.h"
#include "..\\include\\Button\\CRadioButton.h"
#include "..\\include\\TextBox\\CComboBox.h"
#include "..\\include\\TextBox\\CDateTimePicker.h"
#include "..\\include\\Label\\CLabel.h"

namespace MeLib
{
	CGridBoolCellMe::CGridBoolCellMe()
	{
		m_value = false;		
	}

	CGridBoolCellMe::CGridBoolCellMe(bool value)
	{
		m_value = value;
	}

	CGridBoolCellMe::~CGridBoolCellMe()
	{
		
	}
		
	int CGridBoolCellMe::CompareTo(CGridCellMe *cell)
	{
		bool value = this->GetBool();
		bool target = cell->GetBool();
		if(value && !target)
		{
			return 1;
		}
		if(!value && target)
		{
			return -1;
		}
		return 0;
	}
	
	bool CGridBoolCellMe::GetBool()
	{
		return m_value;
	}
	
	double CGridBoolCellMe::GetDouble()
	{
		return (double)(m_value ? 1 : 0);
	}
	
	float CGridBoolCellMe::GetFloat()
	{
		return (float)(m_value ? 1 : 0);
	}
	
	int CGridBoolCellMe::GetInt()
	{
		return m_value ? 1 : 0;
	}
	
	_int64 CGridBoolCellMe::GetLong()
	{
		return m_value ? 1 : 0;
	}
	
	String CGridBoolCellMe::GetString()
	{
		return m_value ? L"true" : L"false";
	}
	
	void CGridBoolCellMe::SetBool(bool value)
	{
		m_value = value;
	}
	
	void CGridBoolCellMe::SetDouble(double value)
	{
		m_value = value > 0.0;
	}
	
	void CGridBoolCellMe::SetFloat(float value)
	{
		m_value = value > 0.0;
	}
	
	void CGridBoolCellMe::SetInt(int value)
	{
		m_value = value > 0;
	}
	
	void CGridBoolCellMe::SetLong(_int64 value)
	{
		m_value = value > 0;
	}
	
	void CGridBoolCellMe::SetString(const String& value)
	{
		m_value = value == L"true";
	}
	////////////////////////////////////////////////////////////////////////////

	CGridButtonCellMe::CGridButtonCellMe()
	{
		CButtonMe* buttonA = new CButtonMe();
		buttonA->SetBorderColor(COLOR_EMPTY);
		buttonA->SetDisplayOffset(false);
		SetControl(buttonA);
	}

	CGridButtonCellMe:: ~CGridButtonCellMe()
	{
	}

	CButtonMe* CGridButtonCellMe::GetButton()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CButtonMe*>(control);
		}
        return 0;
	}
	//////////////////////////////////////////////////////////////////////////////////////////

	CGridCheckBoxCellMe::CGridCheckBoxCellMe()
	{
		CCheckBoxMe* checkBoxA = new CCheckBoxMe();
		checkBoxA->SetDisplayOffset(false);
		checkBoxA->SetButtonAlign(HorizontalAlignMe_Center);
		SetControl(checkBoxA);
	}
	
	CGridCheckBoxCellMe:: ~CGridCheckBoxCellMe()
	{
	 
	}
	
	CCheckBoxMe* CGridCheckBoxCellMe::GetCheckBox()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CCheckBoxMe*>(control);
		}
		return NULL;
	}

	 bool CGridCheckBoxCellMe::GetBool()
	 {
		 CCheckBoxMe* checkBox = GetCheckBox();
		 if(checkBox)
		 {
			 return checkBox->IsChecked();
		 }
		 else
		 {
			 return false;
		 }
	 }

	 double CGridCheckBoxCellMe::GetDouble()
	 {
		 CCheckBoxMe* checkBox = GetCheckBox();
		 if(checkBox)
		 {
			 return (double)(checkBox->IsChecked() ? 1 : 0);
		 }
		 return 0;
	 }
	 
	 float CGridCheckBoxCellMe::GetFloat()
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (float)(checkBox->IsChecked() ? 1 : 0);
		}
		return 0;
	 }

	 int CGridCheckBoxCellMe::GetInt()
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (checkBox->IsChecked()) ? 1 : 0;
		}
		return 0;		 
	 }
	 
	 _int64 CGridCheckBoxCellMe::GetLong()
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			return (checkBox->IsChecked()) ? 1 : 0;
		}
		return 0;			 
	 }
	 
	 String CGridCheckBoxCellMe::GetString()
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (!checkBox)
		{
			return L"false";
		}
		if (!checkBox->IsChecked())
		{
			return L"false";
		}
		return L"true";		 
	 }
	 
	 void CGridCheckBoxCellMe::SetBool(bool value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value);
		}		 
	 }
	 
	 void CGridCheckBoxCellMe::SetDouble(double value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void CGridCheckBoxCellMe::SetFloat(float value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void CGridCheckBoxCellMe::SetInt(int value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }
	 
	 void CGridCheckBoxCellMe::SetLong(_int64 value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value > 0);
		}		 
	 }

	 void CGridCheckBoxCellMe::SetString(const String& value)
	 {
		CCheckBoxMe* checkBox = GetCheckBox();
		if (checkBox)
		{
			checkBox->SetChecked(value == L"true");
		}		 
	 }
	 ///////////////////////////////////////////////////////////////////////////////////////////
	 

	CGridComboBoxCellMe::CGridComboBoxCellMe()
	{
        CComboBoxMe* comboBoxA = new CComboBoxMe();
		comboBoxA->SetBorderColor(COLOR_EMPTY);
		comboBoxA->SetDisplayOffset(false);
		SetControl(comboBoxA);		
	}
	 
	CGridComboBoxCellMe::~CGridComboBoxCellMe()
	{
		
	}

	CComboBoxMe* CGridComboBoxCellMe::GetComboBox()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CComboBoxMe*>(control);
		}
		return 0;		
	}
	
	bool CGridComboBoxCellMe::GetBool()
	{
		CComboBoxMe* comboBox = GetComboBox();
		return (comboBox && (comboBox->GetSelectedIndex() > 0));		
	}

	double CGridComboBoxCellMe::GetDouble()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0.0;
	}
	
	float CGridComboBoxCellMe::GetFloat()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0.0;		
	}
	
	int CGridComboBoxCellMe::GetInt()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0;		
	}
	
	_int64 CGridComboBoxCellMe::GetLong()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedIndex();
		}
		return 0;		
	}
	
	String CGridComboBoxCellMe::GetString()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox)
		{
			return comboBox->GetSelectedValue();
		}
		return L"";			
	}

	void CGridComboBoxCellMe::OnAdd()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox  && comboBox->GetDropDownButton())
		{
			comboBox->RegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN, this);
			comboBox->RegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE, this);
			comboBox->RegisterEvent(m_mouseUpEvent,  EVENTID::MOUSEUP, this);
			comboBox->RegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL, this);
		}
		CGridControlCellMe::OnAdd();
	}

	void CGridComboBoxCellMe::OnRemove()
	{
		CComboBoxMe* comboBox = GetComboBox();
		if(comboBox  && comboBox->GetDropDownButton())
		{
			comboBox->UnRegisterEvent(m_mouseDownEvent, EVENTID::MOUSEDOWN);
			comboBox->UnRegisterEvent(m_mouseMoveEvent, EVENTID::MOUSEMOVE);
			comboBox->UnRegisterEvent(m_mouseUpEvent,  EVENTID::MOUSEUP);
			comboBox->UnRegisterEvent(m_mouseWheelEvent, EVENTID::MOUSEWHEEL);
		}
		CGridControlCellMe::OnRemove();
	}

	void CGridComboBoxCellMe::SetBool(bool value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex(value ? 1 : 0);
		}
	}
	
	void CGridComboBoxCellMe::SetDouble(double value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}		
	}
	
	void CGridComboBoxCellMe::SetFloat(float value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}	
	}
	
	void CGridComboBoxCellMe::SetInt(int value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}			
	}
	
	void CGridComboBoxCellMe::SetLong(_int64 value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedIndex((int)value);
		}			
	}
	
	void CGridComboBoxCellMe::SetString(const String& value)
	{
		CComboBoxMe* comboBox = GetComboBox();
		if (comboBox)
		{
			comboBox->SetSelectedValue(value);
		}		
	}
	///////////////////////////////////////////////////////////////////////////////

	CGridDateTimePickerCellMe::CGridDateTimePickerCellMe()
	{
		CDateTimePickerMe* dateTimePickerA = new CDateTimePickerMe();
		dateTimePickerA->SetBorderColor(COLOR_EMPTY);
		dateTimePickerA->SetDisplayOffset(false);
		SetControl(dateTimePickerA);
	}
	
	CGridDateTimePickerCellMe::~CGridDateTimePickerCellMe()
	{
	}
	
	CDateTimePickerMe* CGridDateTimePickerCellMe::GetDatePicker()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CDateTimePickerMe*>(control);
		}
		return 0;		
	}
	/////////////////////////////////////////////////////////////////////////////
	
	CGridDivCellMe::CGridDivCellMe()
	{
		DivMe* divA = new DivMe();
		divA->SetBorderColor(COLOR_EMPTY);
		divA->SetDisplayOffset(false);
		SetControl(divA);		
	}
	
	CGridDivCellMe::~CGridDivCellMe()
	{
		
	}
	
	DivMe* CGridDivCellMe::GetDiv()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<DivMe*>(control);
		}
		return 0;		
	}
	/////////////////////////////////////////////////////////////////////////////

	CGridDoubleCellMe::CGridDoubleCellMe()
	{
		m_value = 0;
	}
	
	CGridDoubleCellMe::CGridDoubleCellMe(double value)
	{
		m_value = value;
	}
	
	CGridDoubleCellMe::~CGridDoubleCellMe()
	{

	}

	int CGridDoubleCellMe::CompareTo(CGridCellMe *cell)
	{
		double value = GetDouble();
		double target = cell->GetDouble();
		if(value > target)
		{
			return 1;
		}
		if(value < target)
		{
			return -1;
		}
		return 0;
	}
	
	bool CGridDoubleCellMe::GetBool()
	{
		return m_value != 0;
	}
	
	double CGridDoubleCellMe::GetDouble()
	{
		return m_value;
	}
	
	float CGridDoubleCellMe::GetFloat()
	{
		return (float)m_value;
	}

	int CGridDoubleCellMe::GetInt()
	{
		return (int)m_value;
	}

	_int64 CGridDoubleCellMe::GetLong()
	{
		return (_int64)m_value;
	}

	String CGridDoubleCellMe::GetString()
	{
		return CStrMe::ConvertDoubleToStr(m_value);
	}
	
	void CGridDoubleCellMe::SetBool(bool value)
	{
		m_value = value ? ((double) 1) : ((double) 0);
	}
	
	void CGridDoubleCellMe::SetDouble(double value)
	{
		m_value = value;
	}
	
	void CGridDoubleCellMe::SetFloat(float value)
	{
		m_value = value;
	}
	
	void CGridDoubleCellMe::SetInt(int value)
	{
		m_value = (double)value;
	}
	
	void CGridDoubleCellMe::SetLong(_int64 value)
	{
		m_value = (double)value;
	}
	
	void CGridDoubleCellMe::SetString(const String& value)
	{
		m_value = CStrMe::ConvertStrToDouble(value);
	}
	///////////////////////////////////////////////////////////////////////////
	
	CGridFloatCellMe::CGridFloatCellMe()
	{
		m_value = 0;
	}

	CGridFloatCellMe::CGridFloatCellMe(float value)
	{
		m_value = value;
	}
	
	CGridFloatCellMe::~CGridFloatCellMe()
	{
		
	}
	
	int CGridFloatCellMe::CompareTo(CGridCellMe *cell)
	{
		float value = GetFloat();
		float target = cell->GetFloat();
		if (value > target)
		{
			return 1;
		}
		if (value < target)
		{
			return -1;
		}
		return 0;		
	}
	
	bool CGridFloatCellMe::GetBool()
	{
		return m_value != 0;
	}
	
	double CGridFloatCellMe::GetDouble()
	{
		return (double)m_value;
	}
	
	float CGridFloatCellMe::GetFloat()
	{
		return m_value;
	}
	
	int CGridFloatCellMe::GetInt()
	{
		return (int)m_value;
	}
	
	_int64 CGridFloatCellMe::GetLong()
	{
		return(_int64)m_value;
	}
	
	String CGridFloatCellMe::GetString()
	{
		return CStrMe::ConvertFloatToStr(m_value);
	}

	void CGridFloatCellMe::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}
	
	void CGridFloatCellMe::SetDouble(double value)
	{
		m_value = (float)value;
	}
	
	void CGridFloatCellMe::SetFloat(float value)
	{
		m_value = value;
	}
	
	void CGridFloatCellMe::SetInt(int value)
	{
		m_value = (float)value;
	}
	
	void CGridFloatCellMe::SetLong(_int64 value)
	{
		m_value = (float)value;
	}
	
	void CGridFloatCellMe::SetString(const String& value)
	{
		m_value = CStrMe::ConvertStrToFloat(value);
	}

	////////////////////////////////////////////////////////////////////////////////////
	CGridIntCellMe::CGridIntCellMe()
	{
		m_value = 0;
	}
	CGridIntCellMe::CGridIntCellMe(int value)
	{
		m_value = value;
	}
	
	CGridIntCellMe::~CGridIntCellMe()
	{
		
	}

	int CGridIntCellMe::CompareTo(CGridCellMe *cell)
	{
		int value = GetInt();
		int target = cell->GetInt();
		if(value > target)
		{
			return 1;
		}
		if(value < target)
		{
			return -1;
		}
		return 0;
	}
	
	bool CGridIntCellMe::GetBool()
	{
		return m_value != 0;
	}
	
	double CGridIntCellMe::GetDouble()
	{
		return (double)m_value;
	}
	
	float CGridIntCellMe::GetFloat()
	{
		return (float)m_value;
	}
	
	int CGridIntCellMe::GetInt()
	{
		return m_value;
	}
	
	_int64 CGridIntCellMe::GetLong()
	{
		return (_int64)m_value;
	}
	
	String CGridIntCellMe::GetString()
	{
		return CStrMe::ConvertIntToStr(m_value);
	}

	void CGridIntCellMe::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}

	void CGridIntCellMe::SetDouble(double value)
	{
		m_value = (int)value;
	}

	void CGridIntCellMe::SetFloat(float value)
	{
		m_value = (int)value;
	}
	void CGridIntCellMe::SetInt(int value)
	{
		m_value = (int)value;
	}
	void CGridIntCellMe::SetLong(_int64 value)
	{
		m_value = (int)value;
	}
	void CGridIntCellMe::SetString(const String& value)
	{
		m_value = CStrMe::ConvertStrToInt(value);
	}
	////////////////////////////////////////////////////////////////////////////////////

	CGridLabelCellMe::CGridLabelCellMe()
	{
		CLabelMe* labelA = new CLabelMe();
		labelA->SetBorderColor(COLOR_EMPTY);
		labelA->SetDisplayOffset(false);
		SetControl(labelA);
	}

	CGridLabelCellMe:: ~CGridLabelCellMe()
	{
	}

	CLabelMe* CGridLabelCellMe::GetLabel()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CLabelMe*>(control);
		}
		return 0;
	}
	
	////////////////////////////////////////////////////////////////////////////////////

	CGridLongCellMe::CGridLongCellMe()
	{
		m_value = 0;
	}
	
	CGridLongCellMe::CGridLongCellMe(_int64 value)
	{
		m_value = value;
	}

	CGridLongCellMe::~CGridLongCellMe()
	{
	}

	int CGridLongCellMe::CompareTo(CGridCellMe *cell)
	{
	    _int64 value = GetLong();
        _int64 target = cell->GetLong();
        if (value > target)
        {
            return 1;
        }
        if (value < target)
        {
            return -1;
        }
        return 0;
	}
	
	bool CGridLongCellMe::GetBool()
	{
		return m_value != 0;
	}
	
	double CGridLongCellMe::GetDouble()
	{
		return (double)m_value;
	}
	
	float CGridLongCellMe::GetFloat()
	{
		return (float)m_value;
	}
	
	int CGridLongCellMe::GetInt()
	{
		return (int)m_value;
	}
	
	_int64 CGridLongCellMe::GetLong()
	{
		return m_value;
	}

	String CGridLongCellMe::GetString()
	{
		return CStrMe::ConvertLongToStr(m_value);
	}
	
	void CGridLongCellMe::SetBool(bool value)
	{
		m_value = value ? 1 : 0;
	}
	
	void CGridLongCellMe::SetDouble(double value)
	{
		m_value = (_int64)value;
	}
	
	void CGridLongCellMe::SetFloat(float value)
	{
		m_value = (_int64)value;
	}
	
	void CGridLongCellMe::SetInt(int value)
	{
		m_value = (_int64)value;
	}
	
	void CGridLongCellMe::SetLong(_int64 value)
	{
		m_value = (_int64)value;
	}
	
	void CGridLongCellMe::SetString(const String& value)
	{
		m_value = CStrMe::ConvertStrToLong(value);
	}
	///////////////////////////////////////////////////////////////////////////////////

	CGridRadioButtonCellMe::CGridRadioButtonCellMe()
	{
		CRadioButtonMe* radioButtonA = new CRadioButtonMe();
		radioButtonA->SetBorderColor(COLOR_EMPTY);
		radioButtonA->SetDisplayOffset(false);
		SetControl(radioButtonA);		
	}
	
	CGridRadioButtonCellMe::~CGridRadioButtonCellMe()
	{
		
	}
	
	CRadioButtonMe* CGridRadioButtonCellMe::GetRadioButton()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CRadioButtonMe*>(control);
		}
		return NULL;		
	}

	bool CGridRadioButtonCellMe::GetBool()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		return (radioButton && radioButton->IsChecked());
	}
	
	double CGridRadioButtonCellMe::GetDouble()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	float CGridRadioButtonCellMe::GetFloat()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	int CGridRadioButtonCellMe::GetInt()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;
	}
	
	_int64 CGridRadioButtonCellMe::GetLong()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			return radioButton->IsChecked() ? 1 : 0;
		}
		return 0;		
	}
	
	String CGridRadioButtonCellMe::GetString()
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if (!radioButton)
		{
			return L"false";
		}
		if (!radioButton->IsChecked())
		{
			return L"false";
		}
		return L"true";		
	}
	
	void CGridRadioButtonCellMe::SetBool(bool value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value);
		}
	}

	void CGridRadioButtonCellMe::SetDouble(double value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void CGridRadioButtonCellMe::SetFloat(float value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void CGridRadioButtonCellMe::SetInt(int value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void CGridRadioButtonCellMe::SetLong(_int64 value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value > 0);
		}
	}

	void CGridRadioButtonCellMe::SetString(const String& value)
	{
		CRadioButtonMe* radioButton = GetRadioButton();
		if(radioButton)
		{
			radioButton->SetChecked(value == L"true");
		}
	}
	////////////////////////////////////////////////////////////////////

	CGridSpinCellMe::CGridSpinCellMe()
	{
		CSpinMe* spinA = new CSpinMe();
		spinA->SetBorderColor(COLOR_EMPTY);
		spinA->SetDisplayOffset(false);
		SetControl(spinA);
	}
	
	CGridSpinCellMe::~CGridSpinCellMe()
	{
	
	}
	
	CSpinMe* CGridSpinCellMe::GetSpin()
	{
		CControlMe* control = GetControl();
		if (control)
        {
			return dynamic_cast<CSpinMe*>(control);
        }
        return 0;	
	}
	
	bool CGridSpinCellMe::GetBool()
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			return spin->GetValue() > 0;
		}
		return false;
	}
	
	double CGridSpinCellMe::GetDouble()
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			return spin->GetValue();
		}		
		return 0;
	}
	
	float CGridSpinCellMe::GetFloat()
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			return (float)spin->GetValue();
		}		
		return 0;		
	}
	
	int CGridSpinCellMe::GetInt()
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			return (int)spin->GetValue();
		}		
		return 0;		
	}
	
	_int64 CGridSpinCellMe::GetLong()
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			return (_int64)spin->GetValue();
		}		
		return 0;			
	}
	
	void CGridSpinCellMe::SetBool(bool value)
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value ? 1 : 0);
		}			
	}
	
	void CGridSpinCellMe::SetDouble(double value)
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}			
	}
	
	void CGridSpinCellMe::SetFloat(float value)
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	
	void CGridSpinCellMe::SetInt(int value)
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	
	void CGridSpinCellMe::SetLong(_int64 value)
	{
		CSpinMe* spin = GetSpin();
		if(spin)
		{
			spin->SetValue(value);
		}
	}
	///////////////////////////////////////////////////////////////

	CGridStringCellMe::CGridStringCellMe()
	{
		m_value = L"";
	}
	
	CGridStringCellMe::CGridStringCellMe(const String& value)
	{
		m_value = value;
	}
	
	CGridStringCellMe::~CGridStringCellMe()
	{

	}

	int CGridStringCellMe::CompareTo(CGridCellMe *cell)
	{
		String value = cell->GetString();
		String target = GetString();
		if (target.size() > 0)
		{
			return target.compare(value);
		}
		return -1;
	}

	bool CGridStringCellMe::GetBool()
	{
		return false;
	}

	double CGridStringCellMe::GetDouble()
	{
		return 0;
	}

	float CGridStringCellMe::GetFloat()
	{
		return 0;
	}

	int CGridStringCellMe::GetInt()
	{
		return 0;
	}

	_int64 CGridStringCellMe::GetLong()
	{
		return 0;
	}

	String CGridStringCellMe::GetString()
	{
		return m_value;
	}

	void CGridStringCellMe::SetString(const String& value)
	{
		m_value = value;
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGridPasswordCellMe::CGridPasswordCellMe()
	{
	}

	CGridPasswordCellMe:: ~CGridPasswordCellMe()
	{
	}

	String CGridPasswordCellMe::GetPaintText()
	{
		return L"******";
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CGridTextBoxCellMe::CGridTextBoxCellMe()
	{
        CTextBoxMe* textBoxA = new CTextBoxMe();
        textBoxA->SetBorderColor(COLOR_EMPTY);
        textBoxA->SetDisplayOffset(false);
        SetControl(textBoxA);		
	}
	
	CGridTextBoxCellMe:: ~CGridTextBoxCellMe()
	{
		
	}
	
	CTextBoxMe* CGridTextBoxCellMe::GetTextBox()
	{
		CControlMe *control = GetControl();
		if (control)
		{
			return dynamic_cast<CTextBoxMe*>(control);
		}
		return 0;	
	}
}