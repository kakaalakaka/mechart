/**
 *  @file
 *  @copyright defined in mechart/LICENSE
 */

#ifndef __CFILEME_H__
#define __CFILEME_H__
#pragma once
#include "..\\..\\stdafx.h"
#include <io.h>
#include <direct.h>
#include <fstream>
#include <sys/stat.h>

class CFile
{
public:
	static bool Append(const char *file, const char *content);
	static bool Append(const String &file, const String &content);
	static void CreateDirectory(const char *dir);
	static void CreateDirectory(const String &dir);
	static bool IsDirectoryExist(const char *dir);
	static bool IsDirectoryExist(const String &dir);
	static bool IsFileExist(const char *file);
	static bool IsFileExist(const String &file);
	static bool GetDirectories(const char *dir, vector<string> *dirs);
	static bool GetDirectories(const String &file, vector<String> *dirs);
	static int GetFileLength(const char *file);
	static int GetFileLength(const String &file);
	static bool GetFiles(const char *dir, vector<string> *files);
	static bool GetFiles(const String &dir, vector<String> &files);
	static int GetFileState(const char *file, struct stat *buf);
	static int GetFileState(const String &file, struct stat *buf);
	static bool Read(const char *file, string *content);
	static bool ReadLine(ifstream *fs, string *lineContent, int lineLength);
	static bool ReadLine(ifstream *fs, String *lineContent, int lineLength);
	static bool Read(const String &file, String *content);
	static void RemoveFile(const char *file);
	static void RemoveFile(const String &file);
	static bool Write(const char *file, const char *content);
	static bool Write(const String &file, const String &content);
};
#endif