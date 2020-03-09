#pragma once
#include "Directory.h"
#include <map>


//sprite, D:\project\Arr22\AR22api\Sprite
class Path
{
private:
	static std::map<std::wstring, Directory> pathMap;
	static Directory root;

public:
	static inline void SetRootDir(const Directory& _Dir)
	{
		root = _Dir;
	}

	static inline Directory GetRootDir()
	{
		return root;
	}

	//루트를 기준으로 경로를 만들어 주는 함수
	static void CreatePath(const wchar_t* _Path);
	static void CreatePath(const wchar_t* _Name ,const wchar_t* _Path);

	static Directory FindPathDir(const wchar_t* _Name);
	static std::wstring FindPathToString(const wchar_t* _Name);
	static std::wstring ExtractFileName(const wchar_t* _Path);

private:
	Path();
	~Path();
};

