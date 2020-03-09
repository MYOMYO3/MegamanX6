#include "stdafx.h"
#include "Player.h"
#include "AniRender.h"
#include <JTIME.h>
#include <Input.h>


#include "Map.h"
#include "GAMECORE.h"
#include <WINDOW.h>
#include "RenderMgr.h"
#include "TransRender.h"
#include "SceneMgr.h"
#include <Debug.h>
#include <ColorRGB.h>
#include <Windows.h>


//Pos gravityAcc = { 0.0f, 10.0f };
//Pos gPos = { 0.0f, 500.0f };

void Player::SetMap(Map* _Map)
{
	map = _Map;
}

#pragma region PIXELCOLLIDECHECK

void Player::GroundCheck()
{
	if (isPixelCheck == true)
	{
		return;
	}

	if (groundCheck == false)
	{
		return;
	}
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; // 검정색
	
	/*char* p = (char*)&mouseColor;	//마우스 포지션 색체크
	mouseColor = sprite->PosToColor({ pos.x - 640.0f + GameCore::MainWindow().MousePos().x,
										pos.y - 400.0f + GameCore::MainWindow().MousePos().y });*/

	posColor	= sprite->PosToColor(pos + Pos{ 0.0f, 1.0f  } -map->GetPos());;
	groundColor = sprite->PosToColor(pos + Pos{ 0.0f, 20.0f } -map->GetPos());;

	if (groundColor == ColorRGB::Blue)
	{
		hp = -100;
		//state = DEAD;
	}


	if (checkColor != posColor)
	{		
		pos		+= gravity		* Time::DeltaTime();
		gravity += gravityAcc	* Time::DeltaTime();
	}
	else
	{
		while (checkColor == sprite->PosToColor(pos - map->GetPos()))
		{
			CalDebugPos(pos);
			pos -= {0.0f, 1.0f};
		}			
		ResetGravity();	
		ResetJumpPwr();

		isGround = true;						///
	}
}

bool Player::IsColorCheck(CHECKDIR _eDir, int _Color)
{
	if (isPixelCheck == true)
	{
		return false;
	}

#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0;

	CalDebugPos(pos);
	int CheckColor = sprite->PosToColor((GetCheckPos(_eDir) + CHECKPOSSUB[_eDir]) - map->GetPos());

	return _Color == CheckColor;
}

bool Player::IsGroundColorCheck()
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; //검정색

	CalDebugPos(pos);
	int CheckColor = sprite->PosToColor((pos * Pos{ 1.0f, 1.1f }) - map->GetPos());
	int black = 0;
	


	return (black == CheckColor);
}

bool Player::IsCameraCheckX(Pos _Pos)
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; //검정색

	
	int CheckColor = sprite->PosToColor((_Pos + Pos{0.0f, 240.0f}) - map->GetPos());
	int red = ColorRGB::Red;

	if (red == CheckColor)
	{
		if (prevCheckX == false)
		{
			prevLPosX = pos.x;
			prevCheckX = true;
		}
		
		isCameraColArr[0] = true;
		return true;
	}


	int CheckColorR = sprite->PosToColor((_Pos + Pos{ 645.0f, 240.0f }) - map->GetPos());
	red = ColorRGB::Red;

	if (red == CheckColorR)
	{
		if (prevCheckX == false)
		{
			prevRPosX = pos.x;

			prevCheckX = true;
		}
		isCameraColArr[1] = true;
		return true;
	}

	return false;

}


bool Player::IsCameraCheckY(Pos _Pos)
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; //검정색

		int red = ColorRGB::Red;



	int CheckColorT = sprite->PosToColor((_Pos + Pos{ 322.5f, 0.0f }) - map->GetPos());
	if (red == CheckColorT)
	{
		if (prevCheckY == false)
		{
			prevTPosY = pos.y;
			prevCheckY = true;
		}
		isCameraColArr[2] = true;
		return true;
	}


	int CheckColorB = sprite->PosToColor((_Pos + Pos{ 322.5f, 480.0f }) - map->GetPos());
	if (red == CheckColorB)
	{


		return true;
	}

	return false;

}


void Player::DirCheck()
{

	if (isChangeDir == true)
	{
		DIRECTION tempDir;

		if (true == Input::Press(L"LEFT"))
		{
			tempDir = LEFT;
		}
		else if (true == Input::Press(L"RIGHT"))
		{
			tempDir = RIGHT;
		}
		else
		{
			return;
		}

		if (dir != tempDir)
		{
			std::wstring ChangeAniName = L"";

			switch (tempDir)
			{
			case DIRECTION::LEFT:
				ChangeAniName += L"L_";
				break;
			case DIRECTION::RIGHT:
				ChangeAniName += L"R_";
				break;
			default:
				break;
			}
			ChangeAniName += PlayerAniName[state];
			aniRender->PlayAnimation(ChangeAniName.c_str());			
		}
		dir = tempDir;
	}
	else
	{
		isChangeDir = true;
		return;
	}
}
void Player::ULDirCheck()
{

	if (isChangeDir == true)
	{
		DIRECTION tempDir;

		if (true == Input::Press(L"LEFT"))
		{
			tempDir = LEFT;
		}
		else if (true == Input::Press(L"RIGHT"))
		{
			tempDir = RIGHT;
		}
		else
		{
			return;
		}

		if (dir != tempDir)
		{
			std::wstring ChangeAniName = L"";

			switch (tempDir)
			{
			case DIRECTION::LEFT:
				ChangeAniName += L"L_UL";
				break;
			case DIRECTION::RIGHT:
				ChangeAniName += L"R_UL";
				break;
			default:
				break;
			}

			ChangeAniName += PlayerAniName[state];
			if (state != START)
			{
				aniRender->PlayAnimation(ChangeAniName.c_str(), true);
			}			
		}
		dir = tempDir;
	}
	else
	{
		isChangeDir = true;
		return;
	}
	//SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(645 * 0.5f, 480 * 0.7f));
}

void Player::MoveCheck(float _Speed)
{
	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
	{
		return;
	}

	if (true == Input::Press(L"LEFT"))
	{		
		if (pos.x > 160.0f)
		{
			pos.x -= _Speed * Time::DeltaTime();
		}		
	}
	else if (true == Input::Press(L"RIGHT"))
	{
		/*if (내가갈 곳에 검은색 벽이면)
		{
			return
		}*/
		
		pos.x += _Speed * Time::DeltaTime();		
	}
	
	
	//SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(645 * 0.5f, 480 * 0.7f));
}

void Player::DashMoveCheck(float _Speed)
{
	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
	{
		return;
	}

	if (dir == LEFT)
	{
		pos.x -= _Speed * Time::DeltaTime();
	}
	else if (dir == RIGHT)
	{
		pos.x += _Speed * Time::DeltaTime();
	}


	//SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(645 * 0.5f, 480 * 0.7f));
}

void Player::ChangeState(PlAYERSTATE _State)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		changeAniName += L"L_";
		break;
	case RIGHT:
		changeAniName += L"R_";
		break;
	default:
		break;
	}

	// 변신이 되어있다면
	// L_RIGHTANI

	changeAniName += PlayerAniName[_State];

	aniRender->PlayAnimation(changeAniName.c_str());

	state = _State;
}

void Player::ChangeULState(PlAYERSTATE _State)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		changeAniName += L"L_UL";
		break;
	case RIGHT:
		changeAniName += L"R_UL";
		break;
	default:
		break;
	}

	changeAniName += PlayerAniName[_State];

	aniRender->PlayAnimation(changeAniName.c_str());

	state = _State;
}

void Player::ChangeShootParitcle(const std::wstring _Shoot)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		shootRender->RenderPos({ -115, -130});
		changeAniName += L"L_";
		break;
	case RIGHT:
		shootRender->RenderPos({ -85, -130 });
		changeAniName += L"R_";
		break;
	}

	changeAniName += _Shoot;
	shootRender->PlayAnimation(changeAniName.c_str());
}

void Player::ChangeDashParticle(const std::wstring _Dash)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		dashRender->RenderPos({ -10, -70 });
		dashBooster->RenderPos({ 10, -70 });
		changeAniName += L"L_";
		break;
	case RIGHT:
		dashRender->RenderPos({-120, -70 });
		dashBooster->RenderPos({ -100, -70 });
		changeAniName += L"R_";
		break;
	}

	changeAniName += _Dash;
	dashRender->PlayAnimation(changeAniName.c_str());
	dashBooster->PlayAnimation(changeAniName.c_str());
}

void Player::RenderAfterImage(const std::wstring _AfterImage)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		changeAniName += L"L_";
		break;
	case RIGHT:
		changeAniName += L"R_";
		break;
	default:
		break;
	}
	
	changeAniName += _AfterImage;
	afterImageRender->PlayAnimation(changeAniName.c_str());
}

void Player::ChangeOption(PLAYEROPTION _Option)
{
	std::wstring changeOption = L"";

	changeOption += PlayerOption[_Option];

	chargeRender->PlayAnimation(changeOption.c_str());

	option = _Option;
}


void Player::DebugRender()
{
	//std::wstring DebugText;
	//wchar_t ArrText[256];
	//swprintf_s(ArrText, L"jumppower : %f  gravity : %f Acc : %f ", jumpPower, gravity.y, gravityAcc.y);
	//DebugText = ArrText;
	//TextOut(RenderMgr::BACKDC(), 10, 130, DebugText.c_str(), (int)DebugText.size());

}