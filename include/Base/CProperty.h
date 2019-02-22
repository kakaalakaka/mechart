/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CPROPERTYME_H__
#define __CPROPERTYME_H__
#pragma once

#include "..\\..\\stdafx.h"

namespace MeLib
{
	class  CPropertyMe
	{
	public:
		virtual void GetProperty(const wstring& name, wstring *value, wstring *type)
		{
		}
		virtual vector<wstring> GetPropertyNames()
		{
			vector<wstring> propertyNames;
			return propertyNames;
		}
		virtual void SetProperty(const wstring& name, const wstring& value)
		{
		}
	};
}
#endif