#pragma once
#include <iostream>
#include "IO.h"
// � ��� �־��ָ� ������ �����ϴ���
// �������� �ʴ��� �˷��ִ� �Լ��� ������?
// ������? 

class FileStream
{
protected:
	FILE* pFile;

public:
	bool IsOpen() 
	{
		return nullptr != pFile;
	}

public:
	FileStream(const char* _FileName, const char* _Mode);
	FileStream(const wchar_t* _FileName, const wchar_t* _Mode);
	virtual ~FileStream();
};


class FileWBStream : public FileStream
{
public:
	template<typename T>
	void operator <<(const T& _Data)
	{
		fwrite(&_Data, sizeof(T), 1, pFile);
	}

public:
	FileWBStream(const char* _FileName);
	FileWBStream(const wchar_t* _FileName);
	~FileWBStream() {}
};

class FileRBStream : public FileStream
{
public:
	template<typename T>
	void operator >>(T& _Data)
	{
		fread_s(&_Data, sizeof(T), sizeof(T), 1, pFile);
	}

public:
	FileRBStream(const char* _FileName);
	FileRBStream(const wchar_t* _FileName);
	~FileRBStream() {}
};