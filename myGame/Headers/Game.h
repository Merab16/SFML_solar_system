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

	sf::Text mousePos;
	int mPosX;
	int mPosY;

	std::stack<State*> states;
	std::vector<Planet*> planets;
	
	// Variables for background
	sf::Font font;
	sf::Image img;
	sf::Texture tex;
	sf::Sprite spr;

	// Temp planet info 
	Planet* pPlanet;
	sf::Text pName;
	sf::Text pDiameter;
	sf::Text pDistance;
	sf::Text pAroundSun;


	bool isShowInf;
	bool isMousePressed;


public:
	// Constr&Destr
	Game();
	virtual ~Game();

	// Functions 

	void endApllication();

	// Run
	void run();

	// Update
	void update();
	void updateSFMLEvents();
	void updateDt();
	void updatepInfo();
	void updateMousePos();

	// render
	void render();
	//void renderMousePos();

	// Init functions
	void initWindow();
	void initStates();
	void initPlanets();
	void initHeatBoxes();
	void initFont();
	void initBackground();

	void initpInfo();
	//void initCircle();



	void showPlanetInfo(Planet planet);
	


};


#endif // GAME_H
