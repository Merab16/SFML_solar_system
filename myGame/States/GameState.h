#pragma once
#include "State.h"
#ifndef GAMESTATE_H
#define GAMESTATE_H


class GameState: public State
{
private:



public:
	GameState(sf::RenderWindow* window);
	virtual ~GameState();

	void endState();
	void update(const float &dt);
	void render(sf::RenderTarget* target);

};

#endif

