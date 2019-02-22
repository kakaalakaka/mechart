#include "..\\stdafx.h"
#include "..\\include\\Base\\CFile.h"
#include "..\\include\\Base\\CStr.h"
using namespace MeLib;

bool CFile::Append(const char *file, const char *content)
{
	ofstream fs(file, ios::app);
	if(fs)
	{
		fs << content;
		fs.close();
		return true;
	}
	return false;
}

bool CFile::Append(const String &file, const String &content)
{
	string sFile, sContent;
	CStrMe::wstringTostring(sFile, file);
	CStrMe::wstringTostring(sContent, content);
	return Append(sFile.c_str(), sContent.c_str());
}

void CFile::CreateDirectory(const char *dir)
{
	_mkdir(dir);
}

void CFile::CreateDirectory(const String &dir)
{
	string sDir;
	CStrMe::wstringTostring(sDir, dir);
	return CreateDirectory(sDir.c_str());
}

bool CFile::IsDirectoryExist(const char *dir)
{
	if( (_access(dir, 0 )) != -1 )
	{
		return true;
	}
	return false;
}

bool CFile::IsDirectoryExist(const String &dir)
{
	string sDir;
	CStrMe::wstringTostring(sDir, dir);
	return IsDirectoryExist(sDir.c_str());
}

bool CFile::IsFileExist(const char *file)
{
	ifstream fs;
	fs.open(file, ios::in);
	if(fs)
	{
		fs.close();
		return true;
	}
	else
	{
		return false;
	}
}

bool CFile::IsFileExist(const String &file)
{
	string sFile;
	CStrMe::wstringTostring(sFile, file);
	return IsFileExist(sFile.c_str());
}

bool CFile::GetDirectories(const char *dir, vector<string> *dirs)
{
	long hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = (long)_findfirst(p.assign(dir).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			if(fileinfo.attrib &  _A_SUBDIR)  
			{  
				if(strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					dirs->push_back(p.assign(dir).append("\\").append(fileinfo.name));  
				}
			}  
		}
		while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
	} 
	return dirs->size() > 0;
}

bool CFile::GetDirectories(const String &file, vector<String> *dirs)
{
	vector<string> vectors;
	string sFile;
	String dir;
	CStrMe::wstringTostring(sFile, file);
	bool res = GetDirectories(sFile.c_str(), &vectors);
	int size=(int)vectors.size();
	for (int i = 0; i < size; i++)
	{
		CStrMe::stringTowstring(dir, vectors[i]);
		dirs->push_back(dir);
	}
	return res;
}

int CFile::GetFileLength(const char *file)
{
	FILE* fp = 0;
	int fileLen = 0;
	fp = fopen(file, "rb");
	if (!fp)
	{
		return 0;
	}
	fseek(fp, 0, SEEK_END);        
	fileLen = ftell(fp);
	fclose(fp);
	return fileLen;
}

int CFile::GetFileLength(const String &file)
{
	string sFile;
	CStrMe::wstringTostring(sFile, file);
	return GetFileLength(sFile.c_str());
}

bool CFile::GetFiles(const char *dir, vector<string> *files)
{
	long hFile = 0;  
	struct _finddata_t fileinfo;  
	string p;  
	if((hFile = (long)_findfirst(p.assign(dir).append("\\*").c_str(),&fileinfo)) !=  -1)  
	{  
		do  
		{  
			if(!(fileinfo.attrib &  _A_SUBDIR))  
			{  
				files->push_back(p.assign(dir).append("\\").append(fileinfo.name));  
			}  
		}
		while(_findnext(hFile, &fileinfo)  == 0);  
		_findclose(hFile); 
	} 
	return files->size() > 0;
}

bool CFile::GetFiles(const String &dir, vector<String> &files)
{
	string sDir;
	String file;
	vector<string> vectors;
	CStrMe::wstringTostring(sDir, dir);
	bool res = GetFiles(sDir.c_str(), &vectors);
	int size=(int)vectors.size();
	for (int i = 0; i < size; i++)
	{
		CStrMe::stringTowstring(file, vectors[i]);
		files.push_back(file);
	}
	return res;
}

int CFile::GetFileState(const char *file, struct stat *buf)
{
	return stat(file, buf);
}

int CFile::GetFileState(const String &file, struct stat *buf)
{
	string sFile;
	CStrMe::wstringTostring(sFile, file);
	return GetFileState(sFile.c_str(), buf);
}

bool CFile::Read(const char *file, string *content)
{
	if(CFile::IsFileExist(file))
	{
		int fileLength = GetFileLength(file);
		char *szContent = new char[fileLength + 1];
		memset(szContent, '\0', fileLength + 1);
		ifstream fs(file, ios::in); 
		if(fs)
		{
			if(fileLength > 0)
			{
				while(!fs.eof())
				{
					fs.read(szContent, fileLength); 
				}
			}
			fs.close();
		}
		*content = szContent;
		delete[] szContent;
		szContent = 0;
		return true;
	}
	return false;
}	

bool CFile::ReadLine(ifstream *fs, string *lineContent, int lineLength)
{
	char *szContent = new char[lineLength];
	memset(szContent, '\0', lineLength);
	if(fs)
	{
		if(!fs->eof())
		{
			fs->getline(szContent, lineLength); 
		}
	}
	*lineContent = szContent;
	delete[] szContent;
	szContent = 0;
	return true;
}

bool CFile::ReadLine(ifstream *fs, String *lineContent, int lineLength)
{
	char *szContent = new char[lineLength];
	memset(szContent, '\0', lineLength);
	if(fs)
	{
		if(!fs->eof())
		{
			fs->getline(szContent, lineLength); 
		}
	}
	string sContent(szContent);
	String wsContent;
	CStrMe::stringTowstring(wsContent, sContent);	
	*lineContent = wsContent;
	delete[] szContent;
	szContent = 0;
	return true;
}

bool CFile::Read( const String &file, String *content )
{
	string sFile;
	CStrMe::wstringTostring(sFile,file);
	string str;
	bool res = Read(sFile.c_str(), &str);
	String temp;
	CStrMe::stringTowstring(temp, str);
	*content = temp;
	return res;
}

void CFile::RemoveFile(const char *file)
{
	if(CFile::IsFileExist(file))
	{
		String wFile;
		CStrMe::stringTowstring(wFile, file);
		::DeleteFile(wFile.c_str());
	}
}

void CFile::RemoveFile(const String &file)
{
	string sFile;
	CStrMe::wstringTostring(sFile, file);
	return RemoveFile(sFile.c_str());
}

bool CFile::Write(const char *file, const char *content)
{
	ofstream fs(file, ios::out);
	if(fs)
	{
		fs << content;
		fs.close();
		return true;
	}
	return false;
}

bool CFile::Write(const String &file, const String &content)
{
	string sFile,sContent;
	CStrMe::wstringTostring(sFile, file);
	CStrMe::wstringTostring(sContent, content);
	return Write(sFile.c_str(), sContent.c_str());
}