/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */
#ifndef __CINDICATORME_H__
#define __CINDICATORME_H__
#pragma once

#define FUNCTIONID_CHUNK 40
#define FUNCTIONID_FUNCVAR 10
#define FUNCTIONID_FUNCTION 9
#define FUNCTIONID_VAR 10

#include "..\\..\\stdafx.h"
#include "..\\Base\\CStr.h"
#include "..\\Base\\CMathLib.h"
#include "CEnums.h"
#include "CTable.h"
#include "CDiv.h"
#include "CList.h"
#include "CBaseShape.h"

namespace MeLib
{
	class  CIndicatorMe;
	class  CMathElementMe;

	class  CVariableMe
	{
	public:
		CVariableMe();
		virtual ~CVariableMe();
		CBarShapeMe *m_barShape;
		CCandleShapeMe *m_candleShape;
		wstring m_expression;
		int m_field;
		int m_fieldIndex;
		wstring m_fieldText;
		int m_functionID;
		wstring m_funcName;
		CIndicatorMe *m_indicator;
		int m_line;
		CPointShapeMe *m_pointShape;
		CPolylineShapeMe *m_polylineShape;
		wstring m_name;
		CVariableMe **m_parameters;
		int m_parametersLength;
		CMathElementMe **m_splitExpression;
		int m_splitExpressionLength;
		int *m_tempFields;
		int m_tempFieldsLength;
		int *m_tempFieldsIndex;
		int m_tempFieldsIndexLength;
		CTextShapeMe *m_textShape;
		int m_type;
		double m_value;
		void CreateTempFields(int count);
	};

	class  CMathElementMe
	{
	public:
		CMathElementMe();
		CMathElementMe(int type, double value);
		virtual ~CMathElementMe();
		int m_type;
		double m_value;
		CVariableMe *m_var;
	};

	class   CMathElementMeEx : public CMathElementMe
	{
	public:
		CMathElementMeEx *m_next;
		CMathElementMeEx(int type, double value):CMathElementMe(type, value)
		{
			m_next = 0;
		}
		virtual ~CMathElementMeEx()
		{
			if(m_next)
			{
				delete m_next;
				m_next = 0;
			}
		}
	};

	class  CFunctionMe
	{
	public:
		CFunctionMe();
		virtual ~CFunctionMe();
		int m_ID;
		wstring m_name;
		int m_type;
	public:
		virtual double OnCalculate(CVariableMe *var);
	};

	class  CVarMe
    {
	public:
        vector<wstring> *m_list;
        map<wstring, wstring> *m_map;
        double m_num;
        wstring m_str;
        int m_type;
        CVarMe *m_parent;
	public:
        CVarMe()
        {
			m_list = 0;
			m_map = 0;
			m_parent = 0;
        }
        virtual ~CVarMe()
        {
			if (m_list)
            {
                delete m_list;
				m_list = 0;
            }
            if (m_map)
            {
                delete m_map;
				m_map = 0;
            }
            m_parent = 0;
        }
	public:
        virtual wstring GetText(CIndicatorMe *indicator, CVariableMe *name);
		virtual double GetValue(CIndicatorMe *indicator, CVariableMe *name);
		virtual double OnCreate(CIndicatorMe *indicator, CVariableMe *name, CVariableMe *value);
		virtual void SetValue(CIndicatorMe *indicator, CVariableMe *name, CVariableMe *value);
    };

	class  CVarFactoryMe
	{
	public:
		virtual CVarMe* CreateVar()
		{
			return new CVarMe;
		}
	};

	class  CIndicatorMe
	{
	protected:
		CRITICAL_SECTION _csLock;
		map<wstring,double> m_defineParams;
		map<wstring,CFunctionMe*> m_functions;
		map<int, CFunctionMe*> m_functionsMap;
		int m_index;
		vector<CVariableMe*> m_lines;
		vector<_int64> m_systemColors;
		void *m_tag;
		map<wstring, CVariableMe*> m_tempFunctions;
        map<wstring, CVariableMe*> m_tempVariables;
		vector<CVariableMe*> m_variables;
		CVarFactoryMe *m_varFactory;
	protected:
		AttachVScale m_attachVScale;
		int m_break;
		CTableMe *m_dataSource;
		CDivMe *m_div;
		wstring m_name;
		double m_result;
		CVarMe m_resultVar;
	protected:
		void AnalysisVariables(wstring *sentence, int line, wstring funcName, wstring fieldText, bool isFunction);
		void AnalysisScriptLine(wstring line);
		double Calculate(CMathElementMe **expr, int exprLength);
		double CallFunction(CVariableMe *var);
		void DeleteTempVars();
		void DeleteTempVars(CVariableMe *var);
		_int64 GetColor(const wstring& strColor);
		LPDATA GetDatas(int fieldIndex, int mafieldIndex, int index, int n);
		float GetLineWidth(const wstring& strLine);
		int GetMiddleScript(const wstring& script, vector<wstring> *lines);
		String wchartToString(wchar_t c);
		int GetOperator(const wstring& op);
		bool IsNumeric(const wstring& str);
		wstring Replace(const wstring& parameter);
		CMathElementMe** SplitExpression(const wstring& expression, int *sLength);
		wstring* SplitExpression2(const wstring& expression, int *sLength);
	public:
		CIndicatorMe();
		virtual ~CIndicatorMe();
		map<wstring ,int> m_mainVariables;
		map<int, CVarMe*> m_tempVars;
		virtual AttachVScale GetAttachVScale();
		virtual void SetAttachVScale(AttachVScale attachVScale);
		virtual CTableMe* GetDataSource();
		virtual void SetDataSource(CTableMe *dataSource);
		virtual CDivMe* GetDiv();
		virtual void SetDiv(CDivMe *div);
		virtual int GetIndex();
		virtual wstring GetName();
		virtual void SetName(const wstring& name);
		virtual double GetResult();
		virtual void SetScript(const wstring& script);
		virtual vector<_int64> GetSystemColors();
		virtual void SetSystemColors(vector<_int64> systemColors);
		virtual void* GetTag();
		virtual void SetTag(void *tag);
		virtual CVarFactoryMe* GetVarFactory();
		virtual void SetVarFactory(CVarFactoryMe *varFactory);
	public:
		void AddFunction(CFunctionMe *function);
		double CallFunction(wstring funcName);
		void Clear();
		vector<CFunctionMe*> GetFunctions();
		vector<CBaseShapeMe*> GetShapes();
		wstring GetText(CVariableMe *var);
		double GetValue(CVariableMe *var);
		CVariableMe* GetVariable(const wstring& name);
		void Lock();
		void OnCalculate(int index);
		void RemoveFunction(CFunctionMe *function);
		void SetSourceField(const wstring& key, int value);
		void SetSourceValue(int index, const wstring& key, double value);
		void SetVariable(CVariableMe *variable, CVariableMe *parameter);
		void UnLock();
	protected:
		double ABS2(CVariableMe *var);
		double AMA(CVariableMe *var);
		double ACOS(CVariableMe *var);
		double ASIN(CVariableMe *var);
		double ATAN(CVariableMe *var);
		double AVEDEV(CVariableMe *var);
		int BARSCOUNT(CVariableMe *var);
		int BARSLAST(CVariableMe *var);
		int BETWEEN(CVariableMe *var);
		int BREAK(CVariableMe *var);
		double CEILING(CVariableMe *var);
		double CHUNK(CVariableMe *var);
		int CONTINUE(CVariableMe *var);
		double COS(CVariableMe *var);
		int COUNT(CVariableMe *var);
		int CROSS(CVariableMe *var);
		int CURRBARSCOUNT(CVariableMe *var);
		int DATE(CVariableMe *var);
		int DAY(CVariableMe *var);
		int DELETE2(CVariableMe *var);
		double DMA(CVariableMe *var);
		int DOTIMES(CVariableMe *var);
		int DOWHILE(CVariableMe *var);
		int DOWNNDAY(CVariableMe *var);
		double DRAWICON(CVariableMe *var);
		double DRAWKLINE(CVariableMe *var);
		double DRAWNULL(CVariableMe *var);
		double DRAWTEXT(CVariableMe *var);
		int EXIST(CVariableMe *var);
		double EMA(CVariableMe *var);
		int EVERY(CVariableMe *var);
		double EXPMEMA(CVariableMe *var);
		double EXP(CVariableMe *var);
		double FLOOR(CVariableMe *var);
		int FOR(CVariableMe *var);
		double FUNCTION(CVariableMe *var);
		double FUNCVAR(CVariableMe *var);
		double GET(CVariableMe *var);
		double HHV(CVariableMe *var);
		double HHVBARS(CVariableMe *var);
		int HOUR(CVariableMe *var);
		double IF(CVariableMe *var);
		double IFN(CVariableMe *var);
		double INTPART(CVariableMe *var);
		int LAST(CVariableMe *var);
		double LLV(CVariableMe *var);
		double LLVBARS(CVariableMe *var);
		double LOG(CVariableMe *var);
		double MA(CVariableMe *var);
		double MAX2(CVariableMe *var);
		double MEMA(CVariableMe *var);
		double MIN2(CVariableMe *var);
		int MINUTE(CVariableMe *var);
		double MOD(CVariableMe *var);
		int MONTH(CVariableMe *var);
		int NDAY(CVariableMe *var);
		int NOT(CVariableMe *var);
		double POLYLINE(CVariableMe *var);
		double POW(CVariableMe *var);
		int RAND(CVariableMe *var);
		double REF(CVariableMe *var);
		double RETURN(CVariableMe *var);
		double REVERSE(CVariableMe *var);
		double ROUND(CVariableMe *var);
		double SAR(CVariableMe *var);
		double SET(CVariableMe *var);
		int SIGN(CVariableMe *var);
		double SIN(CVariableMe *var);
		double SMA(CVariableMe *var);
		double SQRT(CVariableMe *var);
		double SQUARE(CVariableMe *var);
		double STD(CVariableMe *var);
		double STICKLINE(CVariableMe *var);
		double SUM(CVariableMe *var);
		double TAN(CVariableMe *var);
		int TIME(CVariableMe *var);
		int TIME2(CVariableMe *var);
		double TMA(CVariableMe *var);
		int UPNDAY(CVariableMe *var);
		double VALUEWHEN(CVariableMe *var);
		double VAR(CVariableMe *var);
		int WHILE(CVariableMe *var);
		double WMA(CVariableMe *var);
		int YEAR(CVariableMe *var);
		double ZIG(CVariableMe *var);
	public:
		int STR_CONTACT(CVariableMe *var);
		int STR_EQUALS(CVariableMe *var);
		int STR_FIND(CVariableMe *var);
		int STR_FINDLAST(CVariableMe *var);
		int STR_LENGTH(CVariableMe *var);
		int STR_SUBSTR(CVariableMe *var);
		int STR_REPLACE(CVariableMe *var);
		int STR_SPLIT(CVariableMe *var);
		int STR_TOLOWER(CVariableMe *var);
		int STR_TOUPPER(CVariableMe *var);
		int LIST_ADD(CVariableMe *var);
		int LIST_CLEAR(CVariableMe *var);
		int LIST_GET(CVariableMe *var);
		int LIST_INSERT(CVariableMe *var);
		int LIST_REMOVE(CVariableMe *var);
		int LIST_SIZE(CVariableMe *var);
		int MAP_CLEAR(CVariableMe *var);
		int MAP_CONTAINSKEY(CVariableMe *var);
		int MAP_GET(CVariableMe *var);
		int MAP_GETKEYS(CVariableMe *var);
		int MAP_REMOVE(CVariableMe *var);
		int MAP_SET(CVariableMe *var);
		int MAP_SIZE(CVariableMe *var);
	};
}
#endif