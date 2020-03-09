#pragma once
#include "Statue.h"

class Zero : public Statue
{
private:
	bool startAni;

public:
	bool Init() override;
	void Update() override;
public:
	Zero();
	~Zero();
};

