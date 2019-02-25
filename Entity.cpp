#include "pch.h"
#include "Entity.h"
#include "EntityManager.h"

Entity::Entity()
{
}

Entity::Entity(sf::Vector2f position)
{
}

Entity::Entity(sf::Vector2f position, string texturePath)
{
	mSprite.setPosition(position);
	mSprite.setTexture(mTexture);
	mTexture.loadFromFile(texturePath);
}


void Entity::GoRight(sf::Time elapsedTime)
{
	if (!CollidesBlock())
	{
		GoesToTheRight = true;
		sf::Vector2f movement(0.f, 0.f);
		movement.x += m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Entity::GoLeft(sf::Time elapsedTime)
{
	if (!CollidesBlock())
	{
		GoesToTheRight = false;
		sf::Vector2f movement(0.f, 0.f);
		movement.x -= m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
	}
}

bool Entity::GoUp(sf::Time elapsedTime)
{
	if (this->IsOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder())
	{
		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}

bool Entity::IsOnLadder()
{
	for (shared_ptr<Entity> ladder : EntityManager::mLadders)
	{
		sf::FloatRect ladderBounds = ladder->mSprite.getGlobalBounds();
		// we add the height of the block texture so our entity can hike on it
		ladderBounds.top -= 33;
		ladderBounds.height += 33;
		// we adjust the weight of the block so entities cannot go up if they intersect with only 1 pixel
		ladderBounds.left += 13;
		ladderBounds.width -= 20;

		sf::FloatRect entityBounds = this->mSprite.getGlobalBounds();
		if (entityBounds.intersects(ladderBounds))
		{
			return true;
		}
	}
	return false;
}

bool Entity::IsAboveOrOnLadder()
{
	for (shared_ptr<Entity> entity : EntityManager::mLadders)
	{
		sf::FloatRect ladderBounds = entity->mSprite.getGlobalBounds();
		sf::FloatRect entityBounds = this->mSprite.getGlobalBounds();
		ladderBounds.top -= this->mSprite.getTexture()->getSize().y + 10;
		ladderBounds.height += 13;

		if (entityBounds.intersects(ladderBounds))
		{
			return true;
		}
	}
	return false;
}

bool Entity::CollidesBlock() {
	for (shared_ptr<Entity> block : EntityManager::mBlocks)
	{
		sf::FloatRect entityBounds = this->mSprite.getGlobalBounds();
		sf::FloatRect blockBounds = block->mSprite.getGlobalBounds();
		if (entityBounds.intersects(blockBounds))
		{
			return true;
		}
	}
	return false;
}

bool Entity::OnVoid()
{
	bool OnEdge = true;
	for (shared_ptr<Entity> block : EntityManager::mBlocks)
	{
		sf::FloatRect blockBounds = block->mSprite.getGlobalBounds();
		blockBounds.top -= 5;
		blockBounds.left += 5;
		blockBounds.width -= 10;
		if (mSprite.getGlobalBounds().intersects(blockBounds))
			OnEdge = false;
	}
	return !IsOnLadder() && OnEdge;
}

bool Entity::IsOutsideOfWindow()
{
	if (this->mSprite.getPosition().y > 600)
		return true;
	return false;
}

void Entity::UpdateTexture(string path)
{
	mTexture.loadFromFile(path);
	mSprite.setTexture(mTexture);
}
