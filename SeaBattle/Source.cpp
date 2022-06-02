#include "Header.h"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(1600, 900), "Sea Battle");
	window.setFramerateLimit(165);

	sf::Image icon;
	icon.loadFromFile("Texture\\ship.png");
	window.setIcon(100, 82, icon.getPixelsPtr());

	sf::Music music;
	music.openFromFile("Music\\music.ogg");
	music.play();
	music.setLoop(true);
	music.setVolume(15);

	GameRunning(window);

	music.stop();
	window.close();
	return 0;
}
