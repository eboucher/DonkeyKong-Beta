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
	, mIsMovingUp(false)
	, mIsMovingDown(false)
	, mIsMovingRight(false)
	, mIsMovingLeft(false)
{
	mWindow.setFramerateLimit(60);

	// Draw Statistic Font
	mFont.loadFromFile("Media/Sansation.ttf");
	mStatisticsText.setString("Welcome to Donkey Kong 1981");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(20);

	// Draw end game text
	mEndGameText.setFont(mFont);
	mEndGameText.setPosition(280.f, 10.f);
	mEndGameText.setFillColor(sf::Color::Red);
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

		if (mGameState != GameState::End) {
			std::shared_ptr<Mario> mario = mEntityManager.mMario;

			if (mario->HasEatenAllCoins())
			{
				this->IsOver(1);
			}
			if ((mario->OnVoid() && !mario->mIsJumping && mario->cptFly == 0) || (mario->IsOnLadder() && !mario->mIsJumping && mario->cptFall != 10))
				mario->GoDown(sf::microseconds(10000));
			if (mario->IsOutsideOfWindow())
				IsOver(0);
			mario->GravityHandle();
		}
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
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && mEntityManager.mMario->cptFall == 10) {
		mWindow.setKeyRepeatEnabled(false);
		if(mEntityManager.mMario->cptFall == 10)
			mEntityManager.mMario->mIsJumping = true;
	}
	else if (key == sf::Keyboard::Return)
		mEnterIsPressed = isPressed;
}

void Game::update(sf::Time elapsedTime)
{
	switch(mGameState)
	{

	case GameState::Running:
		if (mIsMovingUp)
			mEntityManager.mMario->GoUp(elapsedTime);
		
		if (mIsMovingDown)
			mEntityManager.mMario->GoDown(elapsedTime);

		if (mIsMovingLeft)
			mEntityManager.mMario->GoLeft(elapsedTime);

		if (mIsMovingRight)
			mEntityManager.mMario->GoRight(elapsedTime);

		if (mEntityManager.mMario->mIsJumping)
			mEntityManager.mMario->Jump(elapsedTime);

		mEntityManager.mMario->TryToEatCoin();

		break;

	case GameState::End:

		if (mEnterIsPressed)
		{

			mEndGameText.setString("");
			mGameState = GameState::Running;
		}

		break;
	}
}

void Game::render()
{
	mWindow.clear();

	for (std::shared_ptr<Entity> entity : mEntityManager.mBlocks)
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
	mWindow.draw(mEndGameText);

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
			toString(mEntityManager.GetCoinsEaten()) + "/" + toString(mEntityManager.mCoins.size()) + " coins"
		);

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}


	if (mStatisticsUpdateTime >= sf::seconds(0.050f))
	{

	}
}

void Game::IsOver(int state)
{
	mGameState = GameState::End;
	if (state == 0)
	{
		mEndGameText.setString("GAME OVER !\nRetry?");
	}
	else
	{
		mEntityManager.IsWon = true;
		mEndGameText.setString("YOU WON !\n");
	}
}