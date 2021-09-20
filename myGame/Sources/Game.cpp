#include "../Headers/Game.h"



Game::Game()
{
	initWindow();
	initStates();
	initPlanets();
	initFont();

	this->img.loadFromFile("assets/img/kosmos.jpg");
	this->tex.loadFromImage(this->img);
	this->spr.setTexture(this->tex);
	this->spr.setScale(1600 / this->spr.getGlobalBounds().width, 900 / this->spr.getGlobalBounds().height);

	std::cout << "Конструктор Game" << std::endl;
}

Game::~Game()
{
	std::cout << "Деструктор Game" << std::endl;
	delete window;
	for (size_t i = 0; i < planets.size(); i++)
		delete planets.at(i);
	delete pPlanet;
}




// Init functions

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1600, 900), "myGame");
	this->window->setFramerateLimit(120);
	this->window->setVerticalSyncEnabled(false);
}

void Game::initStates()
{
	this->states.push(new GameState(this->window));
}

void Game::initPlanets()
{
	std::ifstream ifs("assets/config/configPlanets.ini");
	std::string tempName = "Name";
	std::string diameter = "0";
	std::string distance = "0";
	std::string daysAroundSun = "0";

	while (!ifs.eof()) {
		ifs >> tempName;
		ifs >> diameter;
		ifs >> distance;
		ifs >> daysAroundSun;
		planets.push_back(new Planet(tempName, diameter, distance, daysAroundSun));
	}

	ifs.close();

	std::cout << "initPlanets()\n";

}

void Game::initFont()
{
	if (!(this->font.loadFromFile("assets/fonts/GOTHIC.TTF"))) {
		std::cout << "Font error!\n";
	}
}

void Game::showPlanetInfo(Planet planet)
{

	planet.getSprite().setScale(0.5, 0.5);
	planet.getSprite().setPosition(1600 - planet.getSprite().getGlobalBounds().width, 0);

	sf::Text pName;
	pName.setFont(this->font);
	pName.setString(planet.getName());
	pName.setCharacterSize(20);
	pName.setFillColor(sf::Color::White);
	pName.setPosition(1600 - 250, planet.getSprite().getGlobalBounds().height + 20);

	sf::Text pDiameter;
	pDiameter.setFont(this->font);
	pDiameter.setString("Diameter: " + std::to_string(int(planet.getDiameter())) + " km.");
	pDiameter.setCharacterSize(20);
	pDiameter.setFillColor(sf::Color::White);
	pDiameter.setPosition(1600 - 250, planet.getSprite().getGlobalBounds().height + 40);


	sf::Text pDistance;
	pDistance.setFont(this->font);
	pDistance.setString("Distance: " + std::to_string(int(planet.getDistance())) + " km.");
	pDistance.setCharacterSize(20);
	pDistance.setFillColor(sf::Color::White);
	pDistance.setPosition(1600 - 250, planet.getSprite().getGlobalBounds().height + 60);



	this->window->draw(planet.getSprite());
	this->window->draw(pName);
	this->window->draw(pDiameter);
	this->window->draw(pDistance);

}





// Functions 

void Game::endApllication()
{
	std::cout << "Endig application\n";
}


void Game::run()
{
	while (this->window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

void Game::update()
{
	updateSFMLEvents();
	for (size_t i = 0; i < this->planets.size(); i++) {
		this->planets.at(i)->update(this->dt);
	}

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else {
		this->endApllication();
		this->window->close();
	}
}


void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

			for (size_t i = 0; i < this->planets.size(); i++) {
				if (sf::IntRect(
					this->planets[i]->getPosX() -
					this->planets[i]->getSprite().getGlobalBounds().width / 2,
					this->planets[i]->getPosY() -
					this->planets[i]->getSprite().getGlobalBounds().height / 2,
					this->planets[i]->getSprite().getGlobalBounds().width,
					this->planets[i]->getSprite().getGlobalBounds().height).
					contains(sf::Mouse::getPosition(*this->window))) {
					//this->planets[i]->isClicked(this->dt);
					this->isShowInf = true;
					this->pPlanet = this->planets[i];
				}
			}
		}


	}
}



void Game::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
	//std::cout << this->dt;
	//system("cls");
}

void Game::render()
{
	this->window->clear();
	this->window->draw(this->spr);

	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	for (int i = 0; i < planets.size(); i++) {
		this->window->draw(planets.at(i)->getSprite());
		this->window->draw(planets.at(i)->getCircle());
		//this->window->draw(planets.at(i)->getHeatBox());
	}
	if (isShowInf) this->showPlanetInfo(*pPlanet);



	this->window->display();
}
