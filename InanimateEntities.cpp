#include "pch.h"
#include "InanimateEntities.h"
#include "EntityManager.h"

/********* Block *********************************************/
Block::Block()
{
}

Block::Block(sf::Vector2f position) : Entity(position)
{
	mTexture.loadFromFile("Media/Textures/Block.png");
	mSprite.setTexture(mTexture);
	mSprite.setPosition(position);
}


Block::~Block()
{
}

/************************************************************/


/********* Ladder *******************************************/
Ladder::Ladder()
{
}

Ladder::Ladder(sf::Vector2f position) : Entity(position)
{
	UpdateTexture("Media/Textures/Echelle.png");
	mSprite.setPosition(position);
}


Ladder::~Ladder()
{
}

/************************************************************/

/********** Coin ********************************************/

Coin::Coin()
{
}

Coin::Coin(sf::Vector2f position) : Entity(position)
{
	UpdateTexture("Media/Textures/coin.png");
	mSprite.setPosition(position);
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

/************************************************************/