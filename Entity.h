#pragma once

using namespace std;

class Entity
{

protected:
	Entity();
	Entity(float x, float y);
public:
	Entity(float x, float y, string path);

public:
	~Entity() { };

public:
	void GoRight(sf::Time elapsedTime);
	void GoLeft(sf::Time elapsedTime);
	bool GoUp(sf::Time elapsedTime);
	void UpdateTexture(string path);
	bool GoDown(sf::Time elapsedTime);
	bool IsOnLadder();		
	bool IsAboveOrOnLadder();
	bool CollidesBlock();
	bool OnVoid();
	bool IsOutsideOfWindow();

public:
	bool GoesToTheRight = true;
	sf::Sprite mSprite;
	bool mEnabled = true;
	int mTimes = 0;

protected:
	sf::Texture mTexture;

public:
	float	m_speed;
};