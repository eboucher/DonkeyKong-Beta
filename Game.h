#pragma once

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
	void Over(int state);

private:
	static const sf::Time	TimePerFrame;
	EntityManager	mEntityManager;

	sf::RenderWindow		mWindow;
	sf::Font	mFont;
	sf::Text	mStatisticsText;
	sf::Time	mStatisticsUpdateTime;
	sf::Text	mGameOver;
	sf::Sprite	mPeach;

	size_t	mStatisticsNumFrames;

	bool mIsMovingUpOnLadder;
	bool mIsMovingDownOnLadder;
	bool mIsMovingRight;
	bool mIsJumping;
	bool mIsMovingLeft;
};
