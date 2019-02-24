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
	shared_ptr<Entity> peach = make_shared<Entity>(600.f, 40.f, "Media/Textures/bowser.png");
	EntityManager::mPeach = peach;
	// Blocks
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
		{
			shared_ptr<Block> se = make_shared<Block>(100.f + 70.f * (i + 1), 110.f * (j + 1));
			EntityManager::mBlocks.push_back(se);
		}

	// peach
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			shared_ptr<Coin> se = make_shared<Coin>(130.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			if (!se->CollidesLadder(mLadders))
				EntityManager::mCoins.push_back(se);
		}
	}

	// Ladders
	for (int i = 0; i < 4; i++)
	{

		shared_ptr<Ladder> ladder = make_shared<Ladder>(170.f * (i + 1), 0.f + 110.f * (i + 1) + 33);
		EntityManager::mLadders.push_back(ladder);
	}
}
