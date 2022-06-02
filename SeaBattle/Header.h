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

namespace TXT
{
	class Text
	{
	public:
		Text()
		{
			x = 0.0;
			y = 0.0;
			sizeTXT = 0;
			str = "";
			font.loadFromFile("");
			color = sf::Color::White;

			txt.setString(str);
			txt.setFont(font);
			txt.setCharacterSize(sizeTXT);

			txt.setFillColor(sf::Color(color));
			txt.setStyle(sf::Text::Bold);
			txt.setPosition(x, y);
		}
		Text(string str, sf::Font font, unsigned int sizeTXT, sf::Color color, float x, float y)
		{
			this->font = font;
			this->color = color;
			this->sizeTXT = sizeTXT;
			this->str = str;
			this->x = x;
			this->y = y;

			txt.setString(this->str);
			txt.setFont(this->font);
			txt.setCharacterSize(this->sizeTXT);

			txt.setFillColor(sf::Color(this->color));
			txt.setStyle(sf::Text::Bold);
			txt.setPosition(this->x, this->y);
		}

		void setString(string str)
		{
			txt.setString(str);
		}

		void draw(sf::RenderWindow& window)
		{
			window.draw(txt);
		}

	private:
		float x, y;
		unsigned int sizeTXT;
		string str;
		sf::Font font;
		sf::Color color;
		sf::Text txt;
	};
}


const int GUI_TEXT_MAX = 24;
const int GUI_TEXT_BACKSPACE = 8;
const int GUI_TEXT_ESCAPE = 27;
const sf::Color GUI_TEXT_GRAY = sf::Color(105, 105, 105);


class Ship
{
public:

	Ship()
	{
		texture.loadFromFile(this->fileName);
		ship.setTexture(texture);
		ship.setPosition(2000, 0);
	}

	static void setPATH()
	{
		fileName = "Texture\\ship_left.png";
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
	static string fileName;
	sf::Image image;
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


bool Menu(sf::RenderWindow& window, TextField& tf, TextField& tf2);
void Field(float x, float y, int& active_menu, sf::CircleShape square, bool activeField2, sf::RenderWindow& window);
void CreateShips(bool player2, int& active_menu, vector<Ship>& shipPlayer, int& qtyShips, vector<int>& arr);
void Attack(int* active_menu, vector<int>& arr, int& qtyCrossesGreen, int& qtyCrossesRed, Cross greenCross[], Cross redCross[], bool player2);
void GameRunning(sf::RenderWindow& window);
bool Game(sf::RenderWindow& window);
bool WinnerMenu(sf::RenderWindow& window, int qtyCrossesGreen, int qtyCrossesRed, int qtyCrossesRed2, int qtyCrossesGreen2, string nick, sf::Font f, float time);
