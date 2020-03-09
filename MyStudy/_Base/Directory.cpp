#include "Directory.h"
#include <Windows.h>
#include <assert.h>

Directory::Directory(const Directory& _Other) : fullPath(_Other.fullPath)
{

}

Directory::Directory()
{
	wchar_t Arr[1000];
	GetCurrentDirectoryW(1000, Arr);
	fullPath = Arr;
	
}


Directory::~Directory()
{
}

std::wstring Directory::FolderName()
{
	std::wstring folderName = fullPath;

	size_t curCount = folderName.find_last_of(L"\\", fullPath.size());
	folderName.replace(0, curCount + 1, L"");

	return folderName;
}

void Directory::ReplaceParentPath()
{
	size_t curCount = fullPath.find_last_of(L"\\", fullPath.size());
	fullPath.replace(curCount, fullPath.size(), L"");
}

bool Directory::Move(const wchar_t* _FolderName)
{
	std::wstring findPath = fullPath + L"\\" + _FolderName;

	if (false == IO::ExistFile(findPath.c_str()))
	{
		assert(false);
		return false;
	}
	fullPath = findPath;

	return true;
}

bool Directory::ExistFile(const wchar_t* _FileName)
{
	return IO::ExistFile( (fullPath + L"\\" +_FileName).c_str() );
}


std::vector<std::wstring> Directory::GetFilesinDirectory()
{
	std::vector<std::wstring> files;
	std::wstring search = fullPath + L"\\*.*";
	_wfinddata_t findData;
	LONG handle = (LONG)_wfindfirst(search.c_str(), &findData);
	
	if (handle == -1)
	{
		assert(false);
		return files;
	}
	int result = 0;
	
	do
	{
		if (0 == IO::ExistFile(findData.name))
		{			
			files.push_back(findData.name);			
		}
		result = _wfindnext(handle, &findData);
		
	} while (result != -1);

	
	
	return files;

	
}