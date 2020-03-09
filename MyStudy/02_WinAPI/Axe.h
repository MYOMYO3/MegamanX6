#pragma once
#include "Statue.h"


class Axe : public Statue
{

private:
	bool startAni;

	bool isEndAni;

public:
	bool Init() override;
	void Update() override;
public:
	Axe();
	~Axe();
};

