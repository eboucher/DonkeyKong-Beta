#pragma once
#include "pch.h"
#include "Entity.h"

using namespace std;

class Block : public Entity
{
public:
	Block();
	Block(sf::Vector2f position);
	~Block();

};

class Ladder : public Entity
{
public:
	Ladder();
	Ladder(sf::Vector2f position);
	~Ladder();


};

class Coin : public Entity
{
public:
	Coin();
	Coin(sf::Vector2f position);
	~Coin();

public:
	bool CollidesLadder(vector<shared_ptr<Ladder>> mLadders);
};