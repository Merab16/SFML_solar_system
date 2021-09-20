#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include <vector>
#include <fstream>


#ifndef STATE_H
#define STATE_H

class State
{
protected:
	sf::RenderWindow* window;
	bool quit;



public:
	// COnstr & destr
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;
	virtual void checkQuit();


	// Functions 
	virtual void endState() = 0;
	virtual void update(const float & dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;


};




#endif // !STATE_H





