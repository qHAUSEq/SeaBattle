#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <vector>

using std::string;
using std::floor;
using std::vector;

const int GUI_TEXT_MAX = 24;
const int GUI_TEXT_BACKSPACE = 8;
const int GUI_TEXT_ESCAPE = 27;
const sf::Color GUI_TEXT_GRAY = sf::Color(105, 105, 105);

class Ship
{
public:
	Ship() { ship.setPosition(2000, 0); };

	void AddSprite(string fileName)
	{
		texture.loadFromFile(fileName);
		ship.setTexture(texture);
	}
	void Set_Pos(float x, float y)
	{
		ship.setPosition(x, y);
	}
	void Draw_Ship(sf::RenderWindow & window)
	{
		window.draw(ship);
	}

private:
	sf::Texture texture;
	sf::Sprite ship;
};

class Cross
{
public:
	Cross() { cross_sp.setPosition(2000, 0); };
	void AddSprite(string fileName)
	{
		cross_tex.loadFromFile(fileName);
		cross_sp.setTexture(cross_tex);
	}
	void Set_Pos(float x, float y)
	{
		cross_sp.setPosition(x, y);
	}
	void Draw_Cross(sf::RenderWindow& window)
	{
		window.draw(cross_sp);
	}

private:
	sf::Texture cross_tex;
	sf::Sprite cross_sp;
};

class TextField {
public:
	TextField();

	void setPosition(sf::Vector2f vec);
	void input(sf::Event ev);
	void setFont(sf::Font& f);
	const sf::String& getText();
	void setPlaceholder(std::string str);
	void render(sf::RenderWindow& window);
	void setLength(int arg);
	int getTextLength();
	bool isActive();
	void open();

private:
	sf::Text txt;
	sf::RectangleShape box;
	int size;
	int length;
	bool renderPlaceholder;
	void setActive(bool arg);
	bool active;
	sf::Vector2f pos;
	std::string placeholder;
};


bool Menu(sf::RenderWindow& window, TextField* tf, TextField* tf2);
void Field(float x, float y, int* active_menu, sf::CircleShape square, bool activeField2, sf::RenderWindow& window);
void CreateShips(bool player2, int* active_menu, Ship shipPlayer[], int* qtyShips, int arr[]);
void Attack(int* active_menu, int arr[], int* qtyCrossesGreen, int* qtyCrossesRed, Cross greenCross[], Cross redCross[], bool player2);
void GameRunning(sf::RenderWindow& window);
bool Game(sf::RenderWindow& window);
bool WinnerMenu(sf::RenderWindow& window, int qtyCrossesGreen, int qtyCrossesRed, int qtyCrossesRed2, int qtyCrossesGreen2, string nick, sf::Font f, float time);
