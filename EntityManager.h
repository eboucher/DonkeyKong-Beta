#pragma once
#include "Mario.h"
#include "InanimateEntities.h"


using namespace std;

class EntityManager
{
public:
	EntityManager();
	virtual ~EntityManager();

public:
	static int GetCoinsEaten();

public:
	bool IsWon = false;
	static shared_ptr<Mario> mMario;
	static shared_ptr<Entity> mPeach;
	static vector<shared_ptr<Block>> mBlocks;
	static vector<shared_ptr<Ladder>> mLadders;
	static vector<shared_ptr<Coin>> mCoins;

private:
	static void InitializeEntities();

public:
	void HandleCoinProximity();
};

