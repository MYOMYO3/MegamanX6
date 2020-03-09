#include "stdafx.h"
#include "Render.h"
#include "RenderMgr.h"
#include "Actor.h"
#include <assert.h>


JRender::JRender() 
{
	BF.BlendOp = AC_SRC_OVER;
	BF.BlendFlags = 0;
	BF.SourceConstantAlpha = 255;
	BF.AlphaFormat = AC_SRC_ALPHA;

}


JRender::~JRender()
{
}

void JRender::Init(int _Value, Actor* _Actor)
{	
	actor = _Actor;
	order = _Value;
	PushRenderMgr();
}

void JRender::PushRenderMgr()
{
	RenderMgr::Inst().PushRender(this);
}

