#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

const float NORMAL_PLANET = 700;
const float GRAD_TO_RAD = 3.14f / 180.f;
const float NORMAL_GRAD =  365.f / 1000000.f;
const float SPEED_RATIO = 90.f;


#ifndef PLANET_H
#define PLANET_H


class Planet
{
private:
	std::string name;
	std::string imagePath;

	sf::Image sfImage;
	sf::Texture sfTexture;
	sf::Sprite sfSprite;
	sf::RectangleShape heatBox;
	sf::CircleShape circle;
	sf::Text posPlanet;


	float scale;
	float posX;
	float posY;
	float posX_b;
	float posY_b;
	float posX_n;
	float posY_n;
	int diameter;	
	float distance;
	float grad = 30;
	float velocity;
	float dgrad;
	int daysAroundSun;
	int distanceFromSun;


public:
	Planet(std::string name,std::string diameter, std::string distance,
		std::string daysAroundSun, std::string distanceFromSun);
	Planet();
	virtual ~Planet();

	


	// Init functions
	void initPlanets();
	void initHeatBox();
	void initCircle();
	void initText(sf::Font& font);

	// Functions

	// Getters
	std::string &getName();
	int getDiameter();
	int getDistanceFromSun();
	int getAroundSun();

	float getPosX();
	float getPosY();

	sf::Sprite &getSprite();
	sf::RectangleShape getHeatBox();
	sf::Text getPosPlanet();
	sf::CircleShape getCircle();

	// Setters
	void setImage();
	void setTexture();
	void setSprite();

	void setSpriteScale();
	sf::Vector2f setNormalPos();

	// Actions with obj
	void createObj();
	void moveSprite();
	void moveAround(const float& dt);

	void copy( Planet* other);

	sf::Sprite isClicked(const float& dt);
	
	// Update
	void update(const float &dt);
	
};


#endif // PLANET_H





