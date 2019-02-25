#pragma once
#include "pch.h"
#include "EntityManager.h"

using namespace std;

shared_ptr<Mario> EntityManager::mMario;
shared_ptr<Entity> EntityManager::mPeach;
vector<shared_ptr<Block>> EntityManager::mBlocks;
vector<shared_ptr<Ladder>> EntityManager::mLadders;
vector<shared_ptr<Coin>> EntityManager::mCoins;

EntityManager::EntityManager()
{
	InitializeEntities();
}


EntityManager::~EntityManager()
{
}

int EntityManager::EatenCoins()
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

bool EntityManager::NoMoreCoinsLeft()
{
	if (EntityManager::EatenCoins() == EntityManager::mCoins.size())
	{
		return true;
	}
	return false;
}

void EntityManager::InitializeEntities()
{
	sf::Vector2f MarioPosition = sf::Vector2f(170.f, 470.f);
	sf::Vector2f PeachPosition = sf::Vector2f(600.f, 40.f);

	shared_ptr<Mario> ptr = make_shared<Mario>(MarioPosition);
	EntityManager::mMario = ptr;
	shared_ptr<Entity> peach = make_shared<Entity>(PeachPosition, "Media/Textures/bowser_.png");
	EntityManager::mPeach = peach;

	// Blocks
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 5; j++)
		{
			sf::Vector2f BlockPosition = sf::Vector2f(100.f + 70.f * (i + 1), 110.f * (j + 1));
			shared_ptr<Block> block = make_shared<Block>(BlockPosition);
			EntityManager::mBlocks.push_back(block);
		}

	// Coins drawn as peaches
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sf::Vector2f CoinPosition = sf::Vector2f(130.f + 130.f * (j + 1), 110.f * (i + 1) + 50.f);
			shared_ptr<Coin> coin = make_shared<Coin>(CoinPosition);
			if (!coin->CollidesLadder(mLadders))
				EntityManager::mCoins.push_back(coin);
		}
	}

	// Ladders
	for (int i = 0; i < 4; i++)
	{
		sf::Vector2f LadderPosition = sf::Vector2f(170.f * (i + 1), 0.f + 110.f * (i + 1) + 33);
		shared_ptr<Ladder> ladder = make_shared<Ladder>(LadderPosition);
		EntityManager::mLadders.push_back(ladder);
	}
}

void EntityManager::HandleCoinProximity()
{
	for (shared_ptr<Coin> entity : EntityManager::mCoins)
	{
		sf::FloatRect coinArea = entity->mSprite.getGlobalBounds();
		sf::FloatRect MarioArea = EntityManager::mMario->mSprite.getGlobalBounds();

		if (MarioArea.intersects(coinArea))
		{
			if (entity->mEnabled == true) {
				entity->mEnabled = false;
			}
			break;
		}
	}
}
