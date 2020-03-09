
#include "FILE.h"
#include <assert.h>

///////////////////////////////// BASE FILE

// FPen
FileStream::FileStream(const char* _FileName, const char* _Mode) : pFile(nullptr)
{
	// W가 아니라면
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}
	fopen_s(&pFile, _FileName, _Mode);
}

FileStream::FileStream(const wchar_t* _FileName, const wchar_t* _Mode) : pFile(nullptr)
{
	//if (false == HIO::IsFile(_FileName))
	//{
	//	assert(false);
	//}

	_wfopen_s(&pFile, _FileName, _Mode);
}

FileStream::~FileStream()
{
	if (nullptr != pFile)
	{
		fclose(pFile);
	}
}

///////////////////////////////// WB
FileWBStream::FileWBStream(const char* _FileName)
	: FileStream(_FileName, "wb") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileWBStream::FileWBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"wb") {}

///////////////////////////////// RB
FileRBStream::FileRBStream(const char* _FileName)
	: FileStream(_FileName, "rb") {}
// : HFILESTREAM() // 이런식으로 부모님의 생성자를 
// 자식은 항상 호출해 주고 있었다.
FileRBStream::FileRBStream(const wchar_t* _FileName)
	: FileStream(_FileName, L"rb") {}