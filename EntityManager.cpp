#pragma once
#include "pch.h"
#include "EntityManager.h"

using namespace std;

shared_ptr<Mario> EntityManager::mMario;
shared_ptr<Entity> EntityManager::mPeach;
vector<shared_ptr<Block>> EntityManager::mBlocks(0);
vector<shared_ptr<Ladder>> EntityManager::mLadders(0);
vector<shared_ptr<Coin>> EntityManager::mCoins(0);

EntityManager::EntityManager()
{
	InitializeEntities();
}


EntityManager::~EntityManager()
{
}

int EntityManager::GetCoinsEaten()
{
	int coins = 0;
	for (shared_ptr<Entity> entity : mCoins)
	{
		if (!entity->mEnabled)
		{
			coins += 1;
		}
	}
	return coins;
}

void EntityManager::InitializeEntities()
{

	shared_ptr<Mario> ptr = make_shared<Mario>(170.f, 470.f);
	EntityManager::mMario = ptr;
	shared_ptr<Entity> peach = make_shared<Entity>(600.f, 55.f, "Media/Textures/peach.png");
	EntityManager::mPeach = peach;
	// Blocks
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
		{
			if (!(j == 3 && (i == 3 || i == 4)))
			{
				shared_ptr<Block> se = make_shared<Block>(100.f + 70.f * (i + 1.f), 110.f * (j + 1.f));
				EntityManager::mBlocks.push_back(se);
			} 
		}

	
	// Ladders
	pair<float, float> laddersPositions[5]{ make_pair(540.f, 473.f), 
											make_pair(680.f, 363.f), 
											make_pair(280.f, 363.f), 
											make_pair(540.f, 253.f), 
											make_pair(280.f, 143.f) };
	for (const pair<float, float> ladderPosition : laddersPositions)
	{
		shared_ptr<Ladder> ladder = make_shared<Ladder>(ladderPosition.first, ladderPosition.second);
		EntityManager::mLadders.push_back(ladder);
	}
	// Coins
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			shared_ptr<Coin> se = make_shared<Coin>(100.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			if (!se->CollidesLadder(mLadders))
				EntityManager::mCoins.push_back(se);
		}
	}
}	
