#include "../Headers/Planet.h"


// Constr & Destr
Planet::Planet(std::string name, std::string diameter,
	std::string distance, std::string distanceFromSun, std::string daysAroundSun)
{
	this->name = name;
	this->imagePath = "assets/img/" + name + ".png";

	this->diameter = std::stoi(diameter);
	this->distance = std::stof(distance);

	this->posX = this->distance * 50;
	this->posY = this->distance * 50;

	this->posX_b = this->posX;
	this->posY_b = this->posY;

	this->daysAroundSun = std::stoi(daysAroundSun);

	this->distanceFromSun = std::stoi(distanceFromSun);

	this->velocity = float(this->diameter / this->daysAroundSun);
	this->dgrad = this->velocity * this->velocity / (this->diameter / 2);
	

	this->createObj();
	this->setSpriteScale();

	//this->initCircle();


}

Planet::~Planet()
{
}

Planet::Planet()
{

}


	// Functions

// Init

void Planet::initPlanets()
{

}

void Planet::initHeatBox()
{
	this->heatBox.setSize(sf::Vector2f(this->sfSprite.getGlobalBounds().width,
		this->sfSprite.getGlobalBounds().height));
	this->heatBox.setPosition(this->setNormalPos());
	this->heatBox.setFillColor(sf::Color::Transparent);
	this->heatBox.setOutlineThickness(1.f);
	this->heatBox.setOutlineColor(sf::Color::White);

}

void Planet::initCircle()
{
	this->circle.setRadius(float(sqrt(pow(this->posX_b - this->sfSprite.getGlobalBounds().width / 2, 2) +
		pow(this->posY_b - this->sfSprite.getGlobalBounds().height / 2, 2))));
	this->circle.setFillColor(sf::Color::Transparent);
	this->circle.setOutlineColor(sf::Color::White);
	this->circle.setOutlineThickness(1.f);
	this->circle.setPosition(-this->circle.getRadius(), -this->circle.getRadius());
}

// Getters

sf::Sprite& Planet::getSprite()
{
	return this->sfSprite;
}

sf::RectangleShape Planet::getHeatBox()
{
	return this->heatBox;
}

sf::CircleShape Planet::getCircle()
{
	return this->circle;
}

std::string& Planet::getName()
{
	return this->name;
}

int Planet::getDiameter()
{
	return this->diameter;
}

int Planet::getDistanceFromSun()
{
	return this->distanceFromSun;
}

int Planet::getAroundSun() {
	return this->daysAroundSun;
}

float Planet::getPosX()
{
	return this->posX;
}

float Planet::getPosY()
{
	return this->posY;
}


// Setters

void Planet::setImage()
{
	//std::cout << "Create sfImage\n";
	this->sfImage.loadFromFile(imagePath);
}

void Planet::setTexture()
{
	//std::cout << "Create sfTexture\n";
	this->sfTexture.loadFromImage(this->sfImage);
}

void Planet::setSprite()
{
	//std::cout << "Create sfSprite\n";
	this->sfSprite.setTexture(this->sfTexture);
}

void Planet::setSpriteScale()
{
	this->sfSprite.setScale(this->diameter / (NORMAL_PLANET * this->sfSprite.getGlobalBounds().width),
		this->diameter / (NORMAL_PLANET * this->sfSprite.getGlobalBounds().width));
}

sf::Vector2f Planet::setNormalPos()
{
	this->posX_n = this->posX - this->sfSprite.getGlobalBounds().width / 2;
	this->posY_n = this->posY - this->sfSprite.getGlobalBounds().height / 2;
	return sf::Vector2f(this->posX_n, this->posY_n);
}


// Actions with obj

void Planet::createObj()
{
	this->setImage();
	this->setTexture();
	this->setSprite();
}

void Planet::moveSprite()
{
	this->sfSprite.setPosition(this->setNormalPos());
}

void Planet::moveAround(const float& dt)
{
	this->grad += SPEED_RATIO * this->dgrad * dt;
	if (this->grad >= 360) this->grad -= 360;
	this->posX = this->posX_b * cos(this->grad * GRAD_TO_RAD);
	this->posY = this->posY_b * sin(this->grad * GRAD_TO_RAD);
}

sf::Sprite Planet::isClicked(const float& dt)
{
	//moveAround(dt);
	//sf::Sprite t_spr = this->sfSprite;
	//t_spr.setScale(0.5, 0.5);
	//t_spr.setPosition(1600 - t_spr.getGlobalBounds().width, 0);



	std::cout << this->name + " was clicked!\n";
	//return t_spr;
}

void Planet::copy(Planet* other)
{


	this->name = other->name;
	this->imagePath = other->imagePath;
	this->sfSprite = other->sfSprite;
	this->sfSprite.setScale(0.5, 0.5);
	this->sfSprite.setPosition(1600 - this->sfSprite.getGlobalBounds().width - 25, 25);

	this->diameter = other->diameter;
	this->distanceFromSun = other->distanceFromSun;
	this->daysAroundSun = other->daysAroundSun;



}

// Update
void Planet::update(const float& dt)
{
	this->moveSprite();
	//this->initHeatBox();
	this->moveAround(dt);
}


