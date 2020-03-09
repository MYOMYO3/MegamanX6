#include "GEOMETRY.h"
#include <math.h>

Pos Pos::ZERO = { 0.0f, 0.0f };


#pragma region COLLIDE
bool GeoMath::RectToPoint(const Rect&	_Rect, const Pos& _Pos)
{
	if (_Rect.CalSizeX() < _Pos.x)
	{
		return false;
	}
	if (_Rect.CalPosX() > _Pos.x)
	{
		return false;
	}
	if (_Rect.CalPosY() > _Pos.y)
	{
		return false;
	}
	if (_Rect.CalSizeY() < _Pos.y)
	{
		return false;
	}

	return true;
}

bool GeoMath::RectToRect(const Rect&	_Rect, const Rect& _OtherRect)
{
	if (_Rect.CalSizeX() < _OtherRect.CalPosX())
	{
		return false;
	}
	if (_Rect.CalPosX() > _OtherRect.CalSizeX())
	{
		return false;
	}
	if (_Rect.CalPosY() > _OtherRect.CalSizeY())
	{
		return false;
	}
	if (_Rect.CalSizeY() < _OtherRect.CalPosY())
	{
		return false;
	}


	return true;
}



bool GeoMath::CircleToCircle(const Circle& _Circle, const Circle& _Other)
{
	//원 충돌을 하고 충돌이 되었다면
	float distance = PointDistacne(_Circle.pos, _Other.pos);
	float radiusSum = _Circle.radius + _Other.radius;

	return distance < radiusSum;
}

bool GeoMath::CircleToPoint(const Circle& _Circle, const Pos& _Pos)
{
	float distance = PointDistacne(_Circle.pos, _Pos);
	float radius = _Circle.radius;

	return distance < radius;
}


Rect GeoMath::horizonRect;
Rect GeoMath::verticalRect;
bool GeoMath::RectToCircle(const Rect&	_Rect, const Circle& _Circle)
{
	horizonRect		= _Rect;
	verticalRect	= _Rect;

	horizonRect.size.x	+= _Circle.radius * 2.0f;
	verticalRect.size.y += _Circle.radius * 2.0f;

	if (true == RectToPoint(horizonRect, _Circle.pos) ||
		true == RectToPoint(verticalRect, _Circle.pos))
	{
		return true;
	}

	if (
		true == CircleToPoint(_Circle, _Rect.LeftTopPoint()) ||
		true == CircleToPoint(_Circle, _Rect.LeftBotPoint()) ||
		true == CircleToPoint(_Circle, _Rect.RightTopPoint()) ||
		true == CircleToPoint(_Circle, _Rect.RightBotPoint())
		)
	{
		return true;
	}

	return false;
}
#pragma endregion

#pragma region MATH
float GeoMath::ABS(float _Value)
{
	return _Value < 0 ? _Value * -1.0f : _Value;
}
float GeoMath::PointDistacne(const Pos& _Pos, const Pos& _OtherPos)
{
	float xDistance = ABS(_OtherPos.x - _Pos.x);
	float yDistance = ABS(_OtherPos.y - _Pos.y);	

	return sqrtf( (xDistance*xDistance) + (yDistance* yDistance) );
}
#pragma endregion

