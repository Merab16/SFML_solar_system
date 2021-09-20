#include "GameState.h"

GameState::GameState(sf::RenderWindow* window) 
	: State(window)
{

}

GameState::~GameState()
{
}

void GameState::endState()
{
	std::cout << "Ending states\n";
}

void GameState::update(const float& dt)
{
	this->checkQuit();
}

void GameState::render(sf::RenderTarget* target)
{
}
