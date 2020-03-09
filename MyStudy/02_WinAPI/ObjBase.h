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

	// ����� ������ ������ �ڵ����� �ٿ��ִ´�.
	// inline �ڵ����� ���Եȴ�.
	// �Լ� ������ �������� 
	// �Լ� ���� �Լ� ����(Header)
	// �Լ� ���� �Լ� ü(Body)
	// ������ �������� ���ٸ�
	// ������ִ� ���� �������� ����.
	// �����Ϸ��� �˾Ƽ� ó���Ѵ�.
	// �ʹ� ������ �Լ����� �ζ���ȭ ���� ������ �ִ�.
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

