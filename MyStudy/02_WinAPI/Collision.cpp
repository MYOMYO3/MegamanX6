#include "stdafx.h"
#include "Collision.h"
#include "CollisionMgr.h"
#include "Actor.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}


void Collision::PushColMgr()
{
	CollisionMgr::Inst().PushCol(this);
}

bool Collision::Init(const wchar_t* _GroupName, Actor* _Actor, Size _Size)
{
	actor		= _Actor;
	groupName	= _GroupName;
	pivot = CENTER;
	subRect.size = _Size;
	PushColMgr();

	return true;
}

void Collision::ColCheck(Collision* _Other)
{

	if (this == _Other)
	{
		assert(false);
	}
	//ó�� �浹�ΰ�
	//�浹���ΰ�
	//�浹���ΰ�

	//������� ��� ������ ������ΰ�?

	//�������� �浹�� ������
	if (true == IsCol(_Other))
	{
		//ó���浹�ߴ�.
		//collEnter
		// ����浹���̴�.
		//collstay

		FindIter = otherColSet.find(_Other);

		if (FindIter == otherColSet.end())
		{
			otherColSet.insert(_Other);
			actor->ColEnter(this, _Other);
		}
		else
		{
			actor->ColStay(this, _Other);
		}
	}
	else
	{
		//�ٷ� ���������ӱ��� �浹�ߴ�.
		//colExit
		//��������
		FindIter = otherColSet.find(_Other);
		//�̳༮�� ���� ���� �浹������ ����????

		if (FindIter != otherColSet.end())
		{
			otherColSet.erase(_Other);
			actor->ColExit(this, _Other);
		}
	}
}