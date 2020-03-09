#include "Path.h"
#include <assert.h>


std::map<std::wstring, Directory> Path::pathMap;
Directory Path::root = Directory();

Path::Path()
{
}


Path::~Path()
{
}


void Path::CreatePath(const wchar_t* _Path)
{
	CreatePath(_Path, _Path);
}

void Path::CreatePath(const wchar_t* _Name, const wchar_t* _Path)
{
	Directory newPath = root;

	if (false == newPath.Move(_Path))
	{
		return;
	}

	pathMap.insert(std::map<std::wstring, Directory>::value_type(_Name, newPath));
	return;
}

Directory Path::FindPathDir(const wchar_t* _Name)
{
	std::map<std::wstring, Directory>::iterator iter = pathMap.find(_Name);

	if (iter == pathMap.end())
	{
		assert(false);
		return Directory();
	}

	return iter->second;
}

std::wstring Path::FindPathToString(const wchar_t* _Name)
{
	return FindPathDir(_Name).FullPath();
}

std::wstring Path::ExtractFileName(const wchar_t* _Path)
{
	std::wstring fileName = _Path;
	size_t cutCount		  = fileName.find_last_of(L"\\", fileName.size());

	return fileName.replace(0, cutCount + 1, L"");
}

