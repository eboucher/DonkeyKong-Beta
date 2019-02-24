#pragma once
#include "pch.h"
#include "Entity.h"

using namespace std;

class Block : public Entity
{
public:
	Block();
	Block(float x, float y);
	~Block();

};

class Ladder : public Entity
{
public:
	Ladder();
	Ladder(float x, float y);
	~Ladder();


};

class Coin : public Entity
{
public:
	Coin();
	Coin(float x, float y);
	~Coin();

public:
	bool CollidesLadder(vector<shared_ptr<Ladder>> mLadders);
};