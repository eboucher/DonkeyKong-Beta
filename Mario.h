#pragma once
#include "pch.h"
#include "Entity.h"

using namespace std;

class Mario : public Entity
{
public:
	Mario(float x, float y);
	virtual ~Mario();
	

public:
	void TryToEatCoin();
	bool HasEatenAllCoins();
	bool GoDown(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime) override; 
	void GoRight(sf::Time elapsedTime) override; 
	bool GoUp(sf::Time elapsedTime) override;
	void Jump(sf::Time elapsedTime);
	void GravityHandle();

public:
	bool mIsJumping = false;
	int cptJump = 0;
	int cptFall = 10;
	int cptFly = 0;

protected:
	string mImagePath = "Media/Textures/mario_right.png";
	string mRightTexturePath = "Media/Textures/mario_right.png";
	string mleftTexturePath = "Media/Textures/mario_left.png";
	string mUpTexturePath = "Media/Textures/mario_back.png";
	string mRightJumpTexturePath = "Media/Textures/mario_jump_right.png";
	string mLeftJumpTexturePath = "Media/Textures/mario_jump_left.png";
};

