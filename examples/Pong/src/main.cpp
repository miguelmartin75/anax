#include <SFML/Graphics.hpp>
#include <anax/anax.hpp>

#include <RunGame.hpp>

#include "PongGame.hpp"

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;
const char* const TITLE = "Pong";

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
	PongGame game(window);
	game.init();

	return RunGame(window, game);
}