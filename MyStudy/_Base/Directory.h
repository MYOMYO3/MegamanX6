#pragma once
#include "IO.h"
#include <vector>
#include <string>

class Directory
{
private:
	std::wstring fullPath;
	std::vector<std::wstring> allFilesName;

public:
	std::wstring FolderName();

	const wchar_t* FullPath()
	{
		return fullPath.c_str();
	}

	std::wstring FullPathString()
	{
		return fullPath;
	}

	int FullPathSize()
	{
		return (int)fullPath.size();
	}

	void ReplaceParentPath();

	bool Move(const wchar_t* _FolderName);
	bool ExistFile(const wchar_t* _FileName);

public:	
	std::vector<std::wstring> GetFilesinDirectory();

public:
	Directory(const Directory& _Other); // �����α׷��� ����� ��ġ�� �ڽ��� ��η� ����
	Directory();						// ��ΰ� �����Ȱ� Directory(const wchar_t* _Name);
	~Directory();
};

