#include "../Headers/Game.h"



Game::Game()
{
	initWindow();
	initStates();
	initBackground();
	initFont();
	initPlanets();
	initpInfo();
	
	



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
	std::string distanceFromSun = "0";

	while (!ifs.eof()) {
		ifs >> tempName;
		ifs >> diameter;
		ifs >> distance;
		ifs >> distanceFromSun;
		ifs >> daysAroundSun;
		planets.push_back(new Planet(tempName, diameter, distance, distanceFromSun, daysAroundSun));
		
		// Init text settings
		planets.back()->initText(font);
	}

	ifs.close();

	this->pPlanet = new Planet();
	std::cout << "initPlanets()\n";

}

void Game::initFont()
{
	if (!(this->font.loadFromFile("assets/fonts/GOTHIC.TTF"))) {
		std::cout << "Font error!\n";
	}
}

void Game::initpInfo()
{

	pName.setFont(font);
	pName.setCharacterSize(26);
	pName.setFillColor(sf::Color::White);
	pName.setPosition(1600 - 250, 400);


	pDiameter.setFont(font);
	pDiameter.setCharacterSize(26);
	pDiameter.setFillColor(sf::Color::White);
	pDiameter.setPosition(1600 - 325, 425);

	pDistance.setFont(font);
	pDistance.setCharacterSize(26);
	pDistance.setFillColor(sf::Color::White);
	pDistance.setPosition(1600 - 325, 450);

	pAroundSun.setFont(font);
	pAroundSun.setCharacterSize(26);
	pAroundSun.setFillColor(sf::Color::White);
	pAroundSun.setPosition(1600 - 325, 475);


	mousePos.setFont(font);
	mousePos.setCharacterSize(14);
	mousePos.setFillColor(sf::Color::White);
}

void Game::initBackground()
{
	this->img.loadFromFile("assets/img/kosmos5.jpg");
	this->tex.loadFromImage(this->img);
	this->spr.setTexture(this->tex);
	this->spr.setScale(1600 / this->spr.getGlobalBounds().width, 900 / this->spr.getGlobalBounds().height);
}

void Game::updatepInfo()
{
	pName.setString(pPlanet->getName());
	pDiameter.setString("Diameter: " + std::to_string(pPlanet->getDiameter()) + " km.");
	pDistance.setString("Distance: " + std::to_string(pPlanet->getDistanceFromSun()) + " mil. km.");
	pAroundSun.setString("Around Sun: " + std::to_string(pPlanet->getAroundSun()) + " days");
}




// Functions 

void Game::endApllication()
{
	std::cout << "Endig application\n";
}

void Game::showPlanetInfo(Planet planet)
{
	updatepInfo();

	this->window->draw(pPlanet->getSprite());
	this->window->draw(pName);
	this->window->draw(pDiameter);
	this->window->draw(pDistance);
	this->window->draw(pAroundSun);

}


// Run
void Game::run()
{
	while (this->window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}

// Update

void Game::update()
{
	updateMousePos();
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

		if (sfEvent.type == sf::Event::MouseButtonPressed) {
			this->isMousePressed = true;
			for (size_t i = 0; i < this->planets.size(); i++) {
				if (sf::IntRect(
					int(this->planets[i]->getPosX() -
						this->planets[i]->getSprite().getGlobalBounds().width / 2),
					int(this->planets[i]->getPosY() -
						this->planets[i]->getSprite().getGlobalBounds().height / 2),
					(int)this->planets[i]->getSprite().getGlobalBounds().width,
					(int)this->planets[i]->getSprite().getGlobalBounds().height).
					contains(sf::Mouse::getPosition(*this->window)) && this->isMousePressed) {

					if (pPlanet->getName() == planets[i]->getName() && isShowInf) {
						isShowInf = false;
					}
					else {
						isShowInf = true;
						pPlanet->copy(planets[i]);
					}



				}
			}
		}
		else if (sfEvent.type == sf::Event::MouseButtonReleased)
			isMousePressed = false;





	}
}

void Game::updateDt() {
	this->dt = this->dtClock.restart().asSeconds();
	//std::cout << this->dt;
	//system("cls");
}

void Game::updateMousePos()
{
	mPosX = sf::Mouse::getPosition(*this->window).x;
	mPosY = sf::Mouse::getPosition(*this->window).y;
	mousePos.setString(std::to_string(mPosX) + ';' + std::to_string(mPosY));
	mousePos.setPosition(mPosX, mPosY - 20);
}


// Render

void Game::render()
{
	this->window->clear();
	this->window->draw(this->spr);
	
	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	for (int i = 0; i < planets.size(); i++) {
		this->window->draw(planets[i]->getSprite());
		//this->window->draw(planets.at(i)->getCircle());
		//this->window->draw(planets[i]->getHeatBox());
		this->window->draw(planets[i]->getPosPlanet());
	}
	if (isShowInf) this->showPlanetInfo(*pPlanet);


	this->window->draw(mousePos);
	this->window->display();
}
