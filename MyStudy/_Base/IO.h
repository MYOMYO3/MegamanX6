#pragma once
// io input output�� ����
// ��������� �Լ��� �ƴϸ� ������
// ��κ� io ��� 
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

