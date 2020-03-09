#pragma once
// io input output의 약자
// 파일입출력 함수나 아니면 헤더라면
// 대부분 io 라는 
// img Texture

#include <iostream>
#include <io.h>

class IO	//input output
{
public:
	static bool ExistFile(const char*    _FileName);
	static bool ExistFile(const wchar_t* _FileName);

private:
	IO() {}
	~IO() {}
};

