#include <SFML/Graphics.hpp>

//#include "RunGame.hpp"
//#include "Game.hpp"

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const char* const TITLE = "Example 4 - Collision";

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);

	Game game(window);
	game.init();

	return RunGame(window, game);
}
