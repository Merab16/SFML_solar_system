#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>

const float NORMAL_PLANET = 700;
const float GRAD_TO_RAD = 3.1415 / 180;
const float NORMAL_GRAD =  365.f / 1000000.f;


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

	float scale;
	float posX;
	float posY;
	float posX_b;
	float posY_b;
	float posX_n;
	float posY_n;
	float diameter;	
	float distance;
	float grad = 30;
	float velocity;
	float dgrad;
	float daysAroundSun;


public:
	Planet(std::string name,std::string diameter, std::string distance, std::string daysAroundSun);
	virtual ~Planet();

	// Init functions
	void initPlanets();
	void initHeatBox();
	void initCircle();

	// Functions
	std::string &getName();
	float getDiameter();
	float getDistance();

	sf::Sprite &getSprite();
	sf::RectangleShape getHeatBox();
	sf::CircleShape getCircle();

	float getPosX();
	float getPosY();
	

	void setImage();
	void setTexture();
	void setSprite();

	void setSpriteScale();
	sf::Vector2f setNormalPos();

	void createObj();
	void moveSprite();
	void moveAround(const float& dt);

	sf::Sprite isClicked(const float& dt);
	
	void update(const float &dt);
	
};


#endif // PLANET_H





