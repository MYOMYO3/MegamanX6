#pragma once
// ref: http://www.iro.umontreal.ca/~panneton/WELLRNG.html
// ref: https://blog.naver.com/sorkelf/40188049396

/* ***************************************************************************** */
/* Copyright:      Francois Panneton and Pierre L'Ecuyer, University of Montreal */
/*                 Makoto Matsumoto, Hiroshima University                        */
/* Notice:         This code can be used freely for personal, academic,          */
/*                 or non-commercial purposes. For commercial purposes,          */
/*                 please contact P. L'Ecuyer at: lecuyer@iro.UMontreal.ca       */
/* ***************************************************************************** */

#include <time.h>

class Well512Random
{
public:
	static void Init()
	{
		//시드값 자동 생성
		unsigned int s = static_cast<unsigned int>(time(NULL));

		for (int i = 0; i < 16; i++)
		{
			state[i] = s;
			s += s + __tag::DIFFER_VALUE;
		}
	}

public:
	enum __tag
	{
		DIFFER_VALUE = 100,
	};

private:


	//explicit Well512Random(unsigned int nSeed)
	//	: state( )
	//	, index(0)
	//{
	//	//시드 값을 받아 초기화
	//	unsigned int s = nSeed;

	//	for ( int i = 0; i < 16; i++ )
	//	{
	//		state[i] = s;
	//		s += s + __tag::DIFFER_VALUE;
	//	}
	//}

	~Well512Random() = default;

public:
	static unsigned int GetValue()
	{
		unsigned int a, b, c, d;

		a = state[index];
		c = state[(index + 13) & 15];
		b = a ^ c ^ (a << 16) ^ (c << 15);
		c = state[(index + 9) & 15];
		c ^= (c >> 11);
		a = state[index] = b ^ c;
		d = a ^ ((a << 5) & 0xda442d24U);
		index = (index + 15) & 15;
		a = state[index];
		state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);

		return state[index];
	}

	static unsigned int GetValue(unsigned int nMinValue, unsigned int nMaxValue)
	{
		return nMinValue + (GetValue() % (nMaxValue - nMinValue));
	}

	static unsigned int GetValue(unsigned int nMaxValue)
	{
		return GetValue() % nMaxValue;
	}

	//Float Value
	static float GetFloatValue()
	{
		unsigned int nRandValue = GetValue();

		union
		{
			unsigned long ul; float f;
		} p;
		p.ul = (((nRandValue *= 16807) & 0x007fffff) - 1) | 0x3f800000;

		return p.f - 1.0f;
	}

	static float GetFloatValue(float fMinValue, float fMaxValue)
	{
		return fMinValue + GetFloatValue() * (fMaxValue - fMinValue);
	}

	static float GetFloatValue(float fMaxValue)
	{
		return GetFloatValue() * fMaxValue;
	}

protected:
	static unsigned long state[16];
	static unsigned int index;
};