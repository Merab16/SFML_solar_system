#pragma once

#include "../States/GameState.h"
#include "Planet.h"


#ifndef GAME_H
#define GAME_H




class Game
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;
	std::vector<Planet*> planets;
	
	sf::Font font;
	sf::Image img;
	sf::Texture tex;
	sf::Sprite spr;

//	sf::Sprite t_spr;
	Planet* pPlanet;
	bool isShowInf;
	



public:
	// Constr&Destr
	Game();
	virtual ~Game();

	// Functions 

	void endApllication();

	void run();
	void update();
	void updateSFMLEvents();
	void updateDt();
	void render();

	// Init functions
	void initWindow();
	void initStates();
	void initPlanets();
	void initHeatBoxes();
	void initFont();

	//void initCircle();
	void showPlanetInfo(Planet planet);
	
};


#endif // GAME_H
