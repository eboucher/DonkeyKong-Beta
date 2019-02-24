#include "pch.h"
#include "InanimateEntities.h"
#include "EntityManager.h"

Block::Block()
{
}

Block::Block(float x, float y) : Entity(x, y)
{
	mTexture.loadFromFile("Media/Textures/Block.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(x, y);
}


Block::~Block()
{
}


Ladder::Ladder()
{
}

Ladder::Ladder(float x, float y) : Entity(x, y)
{
	UpdateTexture("Media/Textures/Echelle.png");
	mSprite.setPosition(x, y);
}


Ladder::~Ladder()
{
}


Coin::Coin()
{
}

Coin::Coin(float x, float y) : Entity(x, y)
{
	UpdateTexture("Media/Textures/coin.png");
	mSprite.setPosition(x, y);
}


Coin::~Coin()
{
}

bool Coin::CollidesLadder(vector<shared_ptr<Ladder>> mLadders)
{
	for (shared_ptr<Entity> entity : mLadders)
	{
		sf::FloatRect fr = entity->mSprite.getGlobalBounds();
		fr.top -= 30; // so Mario can continue to hike when he's on the block
		if (this->mSprite.getGlobalBounds().intersects(fr))
		{
			return true;
			break;
		}
	}
	return false;
}