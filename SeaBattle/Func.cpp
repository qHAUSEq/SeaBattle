#include "Header.h"

const int n = 20;
const int n2 = 80;
const int n3 = 100;
string Ship::fileName = "Texture\\ship.png"; // Инициализация кораблей первого игрока

void GameRunning(sf::RenderWindow& window)
{
	if (Game(window)) { GameRunning(window); }
}

bool Game(sf::RenderWindow& window)
{
	// вызов функции первого стартового меню

	TextField tf, tf2;
	bool exit2 = true;

	exit2 = Menu(window, tf, tf2);
	if (exit2 == false) return false;

	//Основные переменные

	int active_menu = 0, active_menu2 = 0, qtyShips = 0, qtyCrossesGreen = 0, qtyCrossesRed = 0, qtyCrossesGreen2 = 0, qtyCrossesRed2 = 0, count = 0;
	float x = 50.0, y = 60.0, x2 = 800.0;
	bool player2 = false, shipVisible = true, shipVisible2 = true, exit;
	string nickname, nickname2;
	std::ostringstream ss; ss << 0;
	sf::Clock clock;

	vector<int> arr(n3, 0);
	vector<int> arr2(n3, 0);

	// Кораблики

	vector<Ship> shipPlayer1(n);
	Ship::setPATH();
	vector<Ship> shipPlayer2(n);

	// Создание фона

	sf::Texture textureBackground;
	textureBackground.loadFromFile("Texture\\menu.png");
	sf::Sprite spriteBackground(textureBackground);
	spriteBackground.setPosition(0, 0);

	// Массивы крестиков, попал или промах
	
	Cross* greenCross = new Cross[n];
	Cross* redCross = new Cross[n2];
	Cross* greenCross2 = new Cross[n];
	Cross* redCross2 = new Cross[n2];
	for (int i = 0; i < n; i++)
	{
		greenCross[i].AddSprite("Texture\\GreenCross.png");
		greenCross2[i].AddSprite("Texture\\GreenCross.png");
	}
	for (int i = 0; i < n2; i++)
	{
		redCross[i].AddSprite("Texture\\RedCross.png");
		redCross2[i].AddSprite("Texture\\RedCross.png");
	}

	// Работа с текстом/добавление шрифта

	nickname = tf.getText(); 
	nickname2 = tf2.getText();

	sf::Font fontForText, fontForName;
	fontForText.loadFromFile("Font\\MoonlessSC-Regular.otf");
	fontForName.loadFromFile("Font\\Cavorting.otf");

	TXT::Text nick("First player: " + nickname, fontForName, 25, sf::Color::Red, 100, 30), 
			  nick2("Second player: " + nickname2, fontForName, 25, sf::Color::Red, 1200, 30),
			  move("Qty moves: " + ss.str(), fontForText, 30, sf::Color::Magenta, 610, 1),
			  whoIsMove("", fontForText, 30, sf::Color::Magenta, 500, 25), 
			  num("0\n1\n2\n3\n4\n5\n6\n7\n8\n9", fontForText, 50, sf::Color::Black, 733, 100), 
			  letter("A   B   C   D   E   F   G   H   I   J", fontForText, 55, sf::Color::Black, 25, 780), 
			  letter2("J   I   H   G   F   E   D   C   B   A", fontForText, 55, sf::Color::Black, 780, 780);

	//Работа с полем квадратов

	sf::CircleShape figure(45, 4), figure2(45, 4);
	figure.rotate(45);
	figure.setOutlineThickness(2);
	figure2.rotate(45);
	figure2.setOutlineThickness(2);

	// Цикл для вывода окна с игрой + все ивенты

	for (; window.isOpen(); )
	{
		sf::Event e;
		float time = clock.getElapsedTime().asSeconds();

		if (qtyShips == n && player2 == false)
		{
			qtyShips = 0;
			active_menu = 0;
			player2 = true;
		}
		if (player2 == true && qtyShips > 19 && count == 0)
		{
			count = 1;
			active_menu2 = 0;
			shipVisible2 = false;
		}

		if (shipVisible == false	&&	shipVisible2 == true)	player2 = false;
		if (shipVisible == true		&&	shipVisible2 == false)	player2 = true;

		window.clear(sf::Color::Black);

		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
			{
				shipPlayer1.clear();
				shipPlayer2.clear();
				delete[] greenCross;     greenCross = nullptr;
				delete[] redCross;       redCross = nullptr;
				delete[] greenCross2;    greenCross2 = nullptr;
				delete[] redCross2;      redCross2 = nullptr;
				arr.clear();
				arr2.clear();

				return false;
			}
			case sf::Event::KeyPressed:
			{
				switch (e.key.code)
				{
				case sf::Keyboard::Right:
				{
					if (player2 == false) active_menu++;
					else active_menu2++;
					break;
				}
				case sf::Keyboard::Left:
				{
					if (player2 == false) active_menu--;
					else active_menu2--;
					break;
				}
				case sf::Keyboard::Up:
				{
					if (player2 == false) active_menu -= 10;
					else active_menu2 -= 10;
					break;
				}
				case sf::Keyboard::Down:
				{
					if (player2 == false) active_menu += 10;
					else active_menu2 += 10;
					break;
				}
				case sf::Keyboard::Enter:
				{
					if (count < 1)
					{
						if (player2 == false) CreateShips(player2, active_menu, shipPlayer1, qtyShips, arr);
						else CreateShips(player2, active_menu2, shipPlayer2, qtyShips, arr2);
						break;
					}
					if (count == 1)
					{
						if (player2 == true)
						{
							Attack(&active_menu2, arr2, qtyCrossesGreen, qtyCrossesRed, greenCross, redCross, player2);
							player2 = false;
							shipVisible = false;
							shipVisible2 = true;
							ss.str("");
							ss << qtyCrossesGreen + qtyCrossesGreen2 + qtyCrossesRed + qtyCrossesRed2;
							move.setString("Qty moves: " + ss.str());
							break;
						}
						else
						{
							Attack(&active_menu, arr, qtyCrossesGreen2, qtyCrossesRed2, greenCross2, redCross2, player2);
							player2 = true;
							shipVisible = true;
							shipVisible2 = false;
							ss.str("");
							ss << qtyCrossesGreen + qtyCrossesGreen2 + qtyCrossesRed + qtyCrossesRed2;
							move.setString("Qty moves: " + ss.str());
							break;
						}
					}
				}
				}
			}
			}
		}
		x = 50, y = 60, x2 = 800;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			shipPlayer1.clear();
			shipPlayer2.clear();
			delete[] greenCross;     greenCross = nullptr;
			delete[] redCross;       redCross = nullptr;
			delete[] greenCross2;    greenCross2 = nullptr;
			delete[] redCross2;      redCross2 = nullptr;
			arr.clear();
			arr2.clear();

			return true;
		}

		window.draw(spriteBackground);
		Field(x, y, active_menu, figure2, false, window);
		Field(x2, y, active_menu2, figure, true, window);

		if (shipVisible) for (int i = 0; i < n; i++) shipPlayer1[i].Draw_Ship(window);
		if (shipVisible2) for (int i = 0; i < n; i++) shipPlayer2[i].Draw_Ship(window);

		for (int i = 0; i < n; i++) greenCross[i].Draw_Cross(window);
		for (int i = 0; i < n2; i++) redCross[i].Draw_Cross(window);
		for (int i = 0; i < n; i++) greenCross2[i].Draw_Cross(window);
		for (int i = 0; i < n2; i++) redCross2[i].Draw_Cross(window);

		nick.draw(window);
		nick2.draw(window);
		move.draw(window);

		if (player2 == true && shipVisible2 == true || player2 == false && shipVisible == false) whoIsMove.setString("The player's current turn is: " + nickname2);
		else whoIsMove.setString("The player's current turn is: " + nickname);

		whoIsMove.draw(window);
		num.draw(window);
		letter.draw(window);
		letter2.draw(window);

		if (qtyCrossesGreen == 20)
		{
			exit = WinnerMenu(window, qtyCrossesGreen, qtyCrossesRed, qtyCrossesRed2, qtyCrossesGreen2, nickname, fontForText, time);

			shipPlayer1.clear();
			shipPlayer2.clear();
			delete[] greenCross;     greenCross = nullptr;
			delete[] redCross;       redCross = nullptr;
			delete[] greenCross2;    greenCross2 = nullptr;
			delete[] redCross2;      redCross2 = nullptr;
			arr.clear();
			arr2.clear();

			return exit;
		}
		if (qtyCrossesGreen2 == 20)
		{
			exit = WinnerMenu(window, qtyCrossesGreen, qtyCrossesRed, qtyCrossesRed2, qtyCrossesGreen2, nickname2, fontForText, time);

			shipPlayer1.clear();
			shipPlayer2.clear();
			delete[] greenCross;     greenCross = nullptr;
			delete[] redCross;       redCross = nullptr;
			delete[] greenCross2;    greenCross2 = nullptr;
			delete[] redCross2;      redCross2 = nullptr;
			arr.clear();
			arr2.clear();

			return exit;
		}

		window.display();
	}

	return false;
}

bool Menu(sf::RenderWindow& window, TextField& tf, TextField& tf2)
{
	sf::Font fontForName;
	fontForName.loadFromFile("Font\\Cavorting.otf");

	tf.setFont(fontForName);
	tf.setLength(12);
	tf.setPlaceholder("PLAYER1");
	tf.setPosition(sf::Vector2f(560, 300));

	tf2.setFont(fontForName);
	tf2.setLength(12);
	tf2.setPlaceholder("PLAYER2");
	tf2.setPosition(sf::Vector2f(770, 300));

	sf::Texture menuTexture1, menuTexture2, menuBackground;
	menuBackground.loadFromFile("Texture\\menu.png");
	menuTexture1.loadFromFile("Texture\\start.png");
	menuTexture2.loadFromFile("Texture\\exit.png");

	sf::Sprite menuSprite1(menuTexture1), menuSprite2(menuTexture2), menuSpriteBackground(menuBackground);
	menuSprite1.setPosition(550, 290);
	menuSprite2.setPosition(500, 450);
	menuSpriteBackground.setPosition(0, 0);

	bool isMenu = true;
	int active_menu = 0;

	while (isMenu)
	{

		menuSprite1.setColor(sf::Color::White);
		menuSprite2.setColor(sf::Color::White);
		active_menu = 0;

		window.clear();
		
		sf::Event e;
		while (window.pollEvent(e))
		{
			tf.input(e);
			tf2.input(e);
			if (e.type == sf::Event::Closed) return false;
		}

		if (sf::IntRect(580, 330, 340, 150).contains(sf::Mouse::getPosition(window)))
		{
			menuSprite1.setColor(sf::Color::Green);
			active_menu = 1;
		}
		if (sf::IntRect(560, 480, 380, 140).contains(sf::Mouse::getPosition(window)))
		{
			menuSprite2.setColor(sf::Color::Green);
			active_menu = 2;
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (active_menu == 1)
			{
				isMenu = false;
				return true;
			}
			if (active_menu == 2)
			{
				isMenu = false;
				return false;
			}
		}

		window.draw(menuSpriteBackground);
		window.draw(menuSprite1);
		window.draw(menuSprite2);
		tf.render(window);
		tf2.render(window);

		window.display();
	}

	return false;
}

void Field(float x, float y, int& active_menu, sf::CircleShape square, bool activeField2, sf::RenderWindow & window)
{
	for (int i = 0; i < n3; i++)
	{
		if (active_menu == n3 || active_menu <= -1 || active_menu > n3)
		{
			i = 0;
			active_menu = 0;
		}
		if (i != active_menu)
		{
			square.setOutlineColor(sf::Color::Red);
		}
		if (i == active_menu)
		{
			square.setOutlineColor(sf::Color::Green);
		}

		square.setPosition(x, y);
		window.draw(square);
		x += 70;

		if (i == 9 || i == 19 || i == 29 || i == 39 || i == 49 || i == 59 || i == 69 || i == 79 || i == 89)
		{
			x = 50;
			y += 69;
			if (activeField2 == true) x = 800;
		}
	}
}

void CreateShips(bool player2, int& active_menu, vector<Ship>& shipPlayer, int& qtyShips, vector<int>& arr)
{
	float posXship, posYship;

	if (player2 == false)	 posXship = (float)10 + (float)70 * (active_menu % 10);
	else					 posXship = (float)740 + (float)70 * (active_menu % 10);

	posYship = 73 + 69 * floor(active_menu / static_cast<float>(10)); 

	shipPlayer[qtyShips].Set_Pos(posXship, posYship);

	for (int i = 0; i < n3; i++)
	{
		if (i == active_menu && arr[i] != 1)
		{
			qtyShips++;
			arr[i] = 1;
		}
	}
}

void Attack(int* active_menu, vector<int>& arr, int& qtyCrossesGreen, int& qtyCrossesRed, Cross greenCross[], Cross redCross[], bool player2)
{
	float posXcross, posYcross;
	for (int i = 0; i < n3; i++)
	{
		if (i == *active_menu)
		{
			if (arr[i] == 1)
			{
				if (player2 == true)	posXcross = (float)780 + (float)70 * (*active_menu % 10);
				else					posXcross = (float)25 + (float)70 * (*active_menu % 10);

				posYcross = 105 + 68 * floor(*active_menu / static_cast<float>(10));

				greenCross[qtyCrossesGreen].Set_Pos(posXcross, posYcross);

				arr[i] = 2; // попал
				(qtyCrossesGreen)++;
				break;
			}
			if (arr[i] == 0)
			{
				if (player2 == true)	posXcross = (float)780 + (float)70 * (*active_menu % 10);
				else					posXcross = (float)25 + (float)70 * (*active_menu % 10);

				posYcross = 105 + 68 * floor(*active_menu / static_cast<float>(10));

				redCross[qtyCrossesRed].Set_Pos(posXcross, posYcross);

				arr[i] = 3; // не попал
				(qtyCrossesRed)++;
				break;
			}
		}
	}
}

bool WinnerMenu(sf::RenderWindow& window, int qtyCrossesGreen, int qtyCrossesRed, int qtyCrossesRed2, int qtyCrossesGreen2, string nick, sf::Font f, float time)
{
	sf::Texture menuBackground;
	menuBackground.loadFromFile("Texture\\menu.png");

	sf::Sprite menuSpriteBackground(menuBackground);
	menuSpriteBackground.setPosition(0, 0);

	std::stringstream ssMin, ssSec, ss, ssMiss, ssHits;
	float min = 0;
	int qtyMoves = qtyCrossesGreen + qtyCrossesGreen2 + qtyCrossesRed + qtyCrossesRed2;
	float sec = time;

	min = sec / 60; 
	sec = fmod(sec, static_cast<float>(60));

	ssMin << floor(min); ssSec << floor(sec);

	ss << qtyMoves; ssMiss << qtyCrossesRed + qtyCrossesRed2; ssHits << qtyCrossesGreen + qtyCrossesGreen2;

	TXT::Text message("CONGRATULATIONS! " + nick + " winner!", f, 80, sf::Color::Red, 400, 350),
			  elapsedTime("The game lasted: " + ssMin.str() + " min " + ssSec.str() + " sec ", f, 40, sf::Color::Black, 400, 450),
			  moves("Number of moves: " + ss.str(), f, 40, sf::Color::Black, 400, 500),
			  miss("Number of misses: " + ssMiss.str(), f, 40, sf::Color::Black, 900, 450),
			  hits("Number of hits: " + ssHits.str(), f, 40, sf::Color::Black, 900, 500);

	bool isMenu = true;
	int active_menu = 0;

	while (isMenu)
	{
		window.clear();

		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) return false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return true;

		window.draw(menuSpriteBackground);
		message.draw(window);
		elapsedTime.draw(window);
		moves.draw(window);
		miss.draw(window);
		hits.draw(window);

		window.display();
	}

	return false;
}