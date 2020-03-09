#pragma once

enum PIVOT
{
	LT, T, RT, R, RB, B ,LB, L, CENTER, CUSTOM
};

typedef class Pos
{
public:
	static Pos ZERO;

public:
	typedef class _tagIPos
	{
	public:
		int iX;
		int iY;		
	}IPos;

	union 
	{
		struct 
		{
			float x;
			float y;
		};
		IPos iPos;
		__int64 i64;

	};
#pragma region POS OPERATOR
public:
	Pos operator*(const float _Value)
	{
		return { x * _Value, y * _Value };
	}

	Pos operator/(const float _Value)
	{
		return { x / _Value, y / _Value };
	}

	Pos operator+(const Pos& _Other)
	{
		return { x + _Other.x, y + _Other.y };
	}

	Pos operator/(const Pos& _Other)
	{
		return { x / _Other.x, y / _Other.y };
	}

	Pos operator-(const Pos& _Other)
	{
		return { x - _Other.x, y - _Other.y };
	}

	bool operator==(const Pos& _Other)
	{
		return x == _Other.x && y == _Other.y;
	}

	Pos operator*(const Pos& _Other)
	{
		return { x * _Other.x, y * _Other.y};
	}

	Pos& operator+=(const Pos& _Other)
	{
		x += _Other.x;
		y += _Other.y;

		return *this;
	}

	Pos& operator-=(const Pos& _Other)
	{
		x -= _Other.x;
		y -= _Other.y;

		return *this;
	}

	Pos& operator*=(const Pos& _Other)
	{
		x *= _Other.x;
		y *= _Other.y;

		return *this;
	}

	//디폴트 대입연산자
	Pos& operator=(const Pos& _Other)
	{
		x = _Other.x;
		y = _Other.y;
		
		return *this;
	}

#pragma endregion

#pragma region POS INVERT
public:
	IPos ConvertInt()
	{
		IPos returnPos;
		returnPos.iX = (int)x;
		returnPos.iY = (int)y;

		return returnPos;
	}

	int HalfIY() const
	{
		return (int)HalfY();
	}

	int HalfIX() const
	{
		return (int)HalfX();
	}

	float HalfY() const
	{
		return y * 0.5f;
	}

	float HalfX() const
	{
		return x * 0.5f;
	}

	inline int IX() const
	{
		return (int)x;
	}

	inline int IY() const
	{
		return (int)y;
	}
#pragma endregion
	   
public:
	Pos() : x(0.0f), y(0.0f)
	{

	}

	Pos(float _X, float _Y) : x(_X), y(_Y)
	{

	}

	~Pos()
	{

	}

}Size;

class Rect
{
public:
	PIVOT pivot;
	Pos  pos;
	Size size;

public:
	int ICalPosX()		const	{	return (int)CalPosX();		}
	int ICalSizeX()		const	{	return (int)CalSizeX();		}
	int ICalPosY()		const	{	return (int)CalPosY();		}
	int ICalSizeY()		const	{	return (int)CalSizeY();		}

	float CalPosX()	const
	{
		switch (pivot)
		{
		case L:
		case LT:		
		case LB:
			return pos.x;

		case T:
		case B:
		case CENTER:
			return pos.x - size.HalfX();

		case R:
		case RT:
		case RB:
			return pos.x - size.x;

		//case CUSTOM:
		//	return;

		}
		return 0;
	}
	float CalSizeX()	const
	{
		switch (pivot)
		{
		case L:
		case LT:
		case LB:
			return pos.x + size.x;

		case T:
		case B:
		case CENTER:
			return pos.x + size.HalfX();

		case R:
		case RT:
		case RB:
			return pos.x;
		}
		return 0;
	}
	float CalPosY()		const
	{
		switch (pivot)
		{
		case LT:
		case RT:
		case T:
			return pos.y;

		case RB:
		case LB:
		case B:
			return pos.y - size.y;

		case L:
		case R:
		case CENTER:
			return pos.y - size.HalfY();

		}
		return 0;
	}
	float CalSizeY()		const
	{
		switch (pivot)
		{
		case LT:
		case RT:
		case T:
			return pos.y + size.y;
		case RB:
		case LB:
		case B:
			return pos.y;
		case L:
		case R:
		case CENTER:
			return pos.y + size.HalfY();
		}
		return 0;
	}

	Pos LeftTopPoint()	const { return { CalPosX(), CalPosY() };	}
	Pos RightTopPoint()	const { return { CalSizeX(), CalPosY() };	}
	Pos LeftBotPoint()	const { return { CalPosX(), CalSizeY() };	}
	Pos RightBotPoint()	const { return { CalSizeX(), CalSizeY() };	}

public:
	Rect& operator=(const Rect& _Other)
	{
		pivot	= _Other.pivot;
		size	= _Other.size;
		pos		= _Other.pos;

		return *this;
	}

public:
	Rect() : pivot(LT)
	{

	}
	Rect(PIVOT _Pivot) : pivot(_Pivot)
	{

	}
};

class Circle
{
public:
	PIVOT    pivot;
	Pos		 pos;
	float	 radius;

public:
	int ILeft()		const { return (int)Left(); }
	int IRight()	const { return (int)Right(); }
	int ITop()		const { return (int)Top(); }
	int IBot()		const { return (int)Bot(); }

	float Left()	const
	{
		switch (pivot)
		{
		case LT:
			return pos.x;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.x - radius;

		default:
			break;
		}
		return 0;
	}
	float Right()	const
	{
		switch (pivot)
		{
		case LT:
			return pos.x + radius *2.0f;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.x + radius;
		default:
			break;
		}
		return 0;
	}
	float Top()		const
	{
		switch (pivot)
		{
		case LT:
			return pos.y;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:

			return pos.y - radius;

		default:
			break;
		}
		return 0;
	}
	float Bot()		const
	{
		switch (pivot)
		{
		case LT:
			return pos.y + radius*2.0f;
		case T:
			break;
		case RT:
			break;
		case R:
			break;
		case RB:
			break;
		case B:
			break;
		case LB:
			break;
		case L:
			break;
		case CENTER:
			return pos.y + radius;

		default:
			break;
		}
		return 0;
	}

	Pos LeftTop()	const { return { Left(), Top() }; }
	Pos RightTop()	const { return { Right(), Top() }; }
	Pos LeftBot()	const { return { Left(), Bot() }; }
	Pos RightBot()	const { return { Right(), Bot() }; }

public:
	Circle& operator=(const Circle& _Other)
	{
		pivot = _Other.pivot;
		radius = _Other.radius;
		pos = _Other.pos;

		return *this;
	}

public:
	Circle() : pivot(LT)
	{

	}
	Circle(PIVOT _Pivot) : pivot(_Pivot)
	{

	}
};

class GeoMath
{
private:
	static Rect horizonRect;
	static Rect verticalRect;

public:
	static bool RectToPoint		(const Rect&	_Rect, const Pos& _Pos);
	static bool RectToRect		(const Rect&	_Rect,	const Rect& _OtherRect);
		
	static bool CircleToCircle	(const Circle&	_Circle, const Circle& _OtherCircle);
	static bool CircleToPoint	(const Circle&	_Circle, const Pos& _Pos);
	
	static bool RectToCircle	(const Rect&	_Rect,	const Circle& _Circle);

public:
	static float ABS			(const float _Value);
	static float PointDistacne	(const Pos& _Pos, const Pos& _OtherPos);
};