#pragma once
#include <string>

class ObjBase
{
private:
	std::wstring name; 

	bool active;
	bool death;

public:
	virtual inline bool IsActive()
	{
		return active && false == death;
	}

	// 헤더에 구현해 놓으면 자동으로 붙여넣는다.
	// inline 자동으로 삽입된다.
	// 함수 구조의 세부적인 
	// 함수 선언 함수 선언(Header)
	// 함수 선언 함수 체(Body)
	// 컴파일 과정에서 본다면
	// 명시해주는 것이 가독성이 좋다.
	// 컴파일러가 알아서 처리한다.
	// 너무 복잡한 함수들은 인라인화 되지 않을수 있다.
	virtual inline bool IsDeath()
	{
		return death;
	}

	virtual void On()
	{
		active = true;
	}

	virtual void Off()
	{
		active = false;
	}

	virtual void Die()
	{
		death = true;
	}

public:
	const wchar_t* PtrName() const
	{
		return name.c_str();
	}

	std::wstring Name()
	{
		return name;
	}

	void Name(const wchar_t* _Name)
	{
		name = _Name;
	}

public:
	ObjBase();
	virtual ~ObjBase() = 0;
};

