#include "pch.h"
#include "Mario.h"
#include "EntityManager.h"

const int JUMPING_FRAMES = 10;
const int FLYING_FRAMES = 15;

Mario::Mario(float x, float y) : Entity(x, y)
{
	m_speed = 150.f;

	UpdateTexture("Media/Textures/mario_right.png");
	mSprite.setPosition(x, y);
}

Mario::~Mario()
{
}

void Mario::Jump(sf::Time elapsedTime) {
	if (!this->IsOnLadder()) {
		GoesToTheRight ? UpdateTexture(mRightJumpTexturePath) : UpdateTexture(mLeftJumpTexturePath);

		sf::Vector2f movement(0.f, 0.f);
		movement.y -= m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
	}
}

void Mario::GravityHandle() {
	if (cptFall != JUMPING_FRAMES) {
		GoesToTheRight ? UpdateTexture(mRightJumpTexturePath) : UpdateTexture(mLeftJumpTexturePath);
	}
	if (cptFly > 0 && cptFly < FLYING_FRAMES) {
		cptFly++;
	}
	else {
		if (cptJump == JUMPING_FRAMES) {
			cptFly++;
			mIsJumping = false;
		}
		if (!mIsJumping)
			cptJump = 0;
		if (!mIsJumping && cptFall != JUMPING_FRAMES)
			cptFall++;
		if (mIsJumping) {
			cptJump++;
			cptFall--;
		}
		if (cptFly == FLYING_FRAMES)
			cptFly = 0;
	}
}

void Mario::TryToEatCoin()
{
	for (shared_ptr<Coin> entity : EntityManager::mCoins)
	{
		sf::FloatRect fr = entity->mSprite.getGlobalBounds();
		if (this->mSprite.getGlobalBounds().intersects(fr))
		{
			if(entity->mEnabled == true)
			entity->mEnabled = false;
			break;
		}
	}
}

bool Mario::HasEatenAllCoins()
{
	if (EntityManager::GetCoinsEaten() == EntityManager::mCoins.size())
	{
		return true;
	}
	return false;
}

void Mario::GoLeft(sf::Time elapsedTime)
{
	if (cptFall == JUMPING_FRAMES) {
		UpdateTexture(mleftTexturePath);
	}
	Entity::GoLeft(elapsedTime);
}

void Mario::GoRight(sf::Time elapsedTime)
{
	if (cptFall == JUMPING_FRAMES) {
		UpdateTexture(mRightTexturePath);
	}
	Entity::GoRight(elapsedTime);
}

bool Mario::GoUp(sf::Time elapsedTime)
{
	if(IsAboveOrOnLadder())
		UpdateTexture(mUpTexturePath);
	return Entity::GoUp(elapsedTime); 
}

bool Mario::GoDown(sf::Time elapsedTime)
{
	if (this->IsAboveOrOnLadder() || OnVoid())
	{
		if (IsOnLadder()) 
			UpdateTexture(mUpTexturePath);

		sf::Vector2f movement(0.f, 0.f);
		movement.y += m_speed;
		this->mSprite.move(movement * elapsedTime.asSeconds());
		return true;
	}
	return false;
}


