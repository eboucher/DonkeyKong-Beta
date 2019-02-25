#include "pch.h"
#include "StringHelpers.h"
#include "Entity.h"
#include "Game.h"
#include "Mario.h"
#include "InanimateEntities.h"

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game()
	: mWindow(sf::VideoMode(840, 600), "Donkey Kong 1981", sf::Style::Close)
	, mFont()
	, mStatisticsText()
	, mStatisticsUpdateTime()
	, mStatisticsNumFrames(0)
	, mIsMovingUpOnLadder(false)
	, mIsMovingDownOnLadder(false)
	, mIsMovingRight(false)
	, mIsJumping(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(60);

	// Draw Statistic Font
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();

			shared_ptr<Mario> mario = mEntityManager.mMario;

			if (mEntityManager.NoMoreCoinsLeft())
			{
				this->Over(1);
			}
			if ((mario->OnVoid() && !mario->mIsJumping && mario->cptFly == 0)) {
				mario->GoDown(sf::microseconds(10000));
			}			
			if (mario->IsOutsideOfWindow())
				Over(0);
			mario->GravityHandle();
	}
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleMarioInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handleMarioInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::handleMarioInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::Up)
		mIsMovingUpOnLadder = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDownOnLadder = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
	if (key == sf::Keyboard::Space) {
		mIsJumping = isPressed;
	}
}

void Game::update(sf::Time elapsedTime)
{
		if (mIsMovingUpOnLadder)
			mEntityManager.mMario->GoUp(elapsedTime);

		if (mIsMovingDownOnLadder)
			mEntityManager.mMario->GoDown(elapsedTime);

		if (mIsMovingLeft)
			mEntityManager.mMario->GoLeft(elapsedTime);

		if (mIsMovingRight)
			mEntityManager.mMario->GoRight(elapsedTime);

		if (mIsJumping)
			mEntityManager.mMario->Jump(elapsedTime);

		mEntityManager.HandleCoinProximity();

		if(mEntityManager.mMario->TouchBowser())
		{
			Over(1);
		}
}

void Game::render()
{
	mWindow.clear();

	for (shared_ptr<Entity> entity : mEntityManager.mBlocks)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : mEntityManager.mLadders)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	for (shared_ptr<Entity> entity : mEntityManager.mCoins)
	{
		if (entity->mEnabled)
			mWindow.draw(entity->mSprite);
	}

	mWindow.draw(mEntityManager.mMario->mSprite);
	mWindow.draw(mEntityManager.mPeach->mSprite);

	mWindow.draw(mStatisticsText);
	mWindow.draw(mGameOver);

	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us\n" +
			toString(mEntityManager.EatenCoins()) + "/" + toString(mEntityManager.mCoins.size()) + " peachs"
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::Over(int state)
{
	mGameOver.setFont(mFont);
	mGameOver.setPosition(300.f, 300.f);
	if (state == 0)
	{
		mGameOver.setString("OOOOOOOOOOOh Mamamia !");
	}
	else
	{
		mEntityManager.IsWon = true;
		mGameOver.setString("Sub Zero Win !");
	}
}