#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
using namespace sf;
using namespace std;
enum states
{
	alive,
	escaped,
	drown,
	eaten,
	starved
};
states state = alive;
void Intialize(RenderWindow &window, RectangleShape &shape, Text &text, Font &font, RectangleShape &water, RectangleShape &bridge, RectangleShape cat[], RectangleShape &mouse, Texture &tom, Texture &jerry)
{
	window.create(VideoMode(800, 800), "Tom & Jerry");
	shape.setSize(Vector2f(600, 600));
	shape.setPosition(100, 100);
	shape.setFillColor(Color::Yellow);
	bridge.setSize(Vector2f(100, 100));
	bridge.setPosition(700, 350);
	bridge.setFillColor(Color::Yellow);
	tom.loadFromFile("tom.png");
	jerry.loadFromFile("jerry.png");
	for (int i = 0; i < 4; i++)
	{
		cat[i].setSize(Vector2f(60, 60));
		cat[i].setPosition(float((100 * i) + 300 - ((rand() % 2) * 100)), float((100 * i) + 200 - ((rand() % 2) * 100)));
		cat[i].setTexture(&tom);
	}
	mouse.setSize(Vector2f(35, 35));
	mouse.setPosition(100, 100);
	mouse.setTexture(&jerry);
	if (font.loadFromFile("lunchds.ttf"))
	{
		text.setFont(font);
		text.setFillColor(Color::White);
		text.setCharacterSize(50);
		text.setStyle(Text::Bold);
	}
}
void handleEvent(RenderWindow &window, RectangleShape &shape, int &count, RectangleShape &mouse, RectangleShape cat[], RectangleShape &bridge, states &state)
{
	Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
			window.close();
			break;
		case Event::KeyPressed:
			if (state == alive)
			{
				switch (event.key.code)
				{
				case Keyboard::Down:
					mouse.move(0, 20);
					count++;
					break;
				case Keyboard::Up:
					mouse.move(0, -20);
					count++;
					break;
				case Keyboard::Right:
					mouse.move(20, 0);
					count++;
					break;
				case Keyboard::Left:
					mouse.move(-20, 0);
					count++;
					break;
				case Keyboard::Escape:
					window.close();
					break;
				}
			}
			break;
		}
		if (!shape.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y) && !bridge.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
			state = drown;
		for (int i = 0; i < 4; i++)
		{
			if (cat[i].getGlobalBounds().intersects(mouse.getGlobalBounds()))
				state = eaten;
		}
		if (count > 100)
			state = starved;
		if (bridge.getGlobalBounds().contains(mouse.getPosition().x, mouse.getPosition().y))
			state = escaped;
	}
}
void movecat(RectangleShape &shape, RectangleShape cat[], Clock &clock, states state)
{
	if (clock.getElapsedTime().asMilliseconds() == 600)
	{
		for (int i = 0; i < 4 && state == alive; i++)
		{
			int k = (rand() % 4) + 1;
			switch (k)
			{
			case (1):
				if (!shape.getGlobalBounds().contains(cat[i].getPosition().x + 20, cat[i].getPosition().y))
					cat[i].move(-20, 0);
				else
					cat[i].move(20, 0);
				break;
			case (2):
				if (!shape.getGlobalBounds().contains(cat[i].getPosition().x - 20, cat[i].getPosition().y))
					cat[i].move(20, 0);
				else
					cat[i].move(-20, 0);
				break;
			case (3):
				if (!shape.getGlobalBounds().contains(cat[i].getPosition().x, cat[i].getPosition().y - 20))
					cat[i].move(0, 20);
				else
					cat[i].move(0, -20);
				break;
			case (4):
				if (!shape.getGlobalBounds().contains(cat[i].getPosition().x, cat[i].getPosition().y + 20))
					cat[i].move(0, -20);
				else
					cat[i].move(0, 20);
				break;
			}
		}
		clock.restart();
	}
}
void render(RenderWindow &window, RectangleShape &shape, RectangleShape cat[], RectangleShape mouse, RectangleShape &bridge, Text &text, Font &font)
{
	window.clear(Color::Cyan);
	window.draw(text);
	window.draw(shape);
	window.draw(bridge);
	for (int i = 0; i < 4; i++)
		window.draw(cat[i]);
	window.draw(mouse);
	window.display();
}
int main()
{
	RenderWindow window;
	RectangleShape cat[4], mouse, water, island, bridge;
	Texture tom, jerry;
	Text text;
	Font font;
	Clock clock;
	srand(time(NULL));
	int count = 0;
	Intialize(window, island, text, font, water, bridge, cat, mouse, tom, jerry);
	while (window.isOpen())
	{
		handleEvent(window, island, count, mouse, cat, bridge, state);
		render(window, island, cat, mouse, bridge, text, font);
		movecat(island, cat, clock, state);
		if (state == alive)
			text.setString("Tom & Jerry" + std::to_string(count) + " /100");
		else if (state == starved)
		{
			text.setString("Jerry starved");
			jerry.loadFromFile("dead.png");
			mouse.setTexture(&jerry);
		}
		else if (state == eaten)
			text.setString("Jerry was eaten");
		else if (state == drown)
			text.setString("Jerry drown");
		else
			text.setString("Jerry escaped");
	}
	return 0;
}
