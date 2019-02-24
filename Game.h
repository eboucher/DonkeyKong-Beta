#pragma once

#define BLOCK_SPACE 110.f
#define COIN_SPACE 100.f
#include "EntityManager.h"

class Game
{
public:
	Game();
	~Game() { };
	void run();

private:
	void processEvents();
	void update(sf::Time elapsedTime);
	void render();

	void updateStatistics(sf::Time elapsedTime);
	void handleMarioInput(sf::Keyboard::Key key, bool isPressed);
	void IsOver(int state);

private:
	static const sf::Time	TimePerFrame;
	bool mRunning = true;
	EntityManager	mEntityManager;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	sf::Text	mEndGameText;
	sf::Sprite	mPeach;
	sf::Texture mPeachTexture;

	size_t	mStatisticsNumFrames;

	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingRight;
	bool mIsMovingLeft;
	bool mEnterIsPressed;
};
