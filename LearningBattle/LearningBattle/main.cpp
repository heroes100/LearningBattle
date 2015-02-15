#include <SFML/Graphics.hpp>
#include <stdio.h>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	sf::Texture texture;
	texture.create(10,10);
	if (!texture.loadFromFile("ship.png")){
		printf("Error");
	}

	sf::Sprite sprite;
	sprite.scale(sf::Vector2f(0.5f, 0.5f)); // factor relative to the current scale
	sprite.setTexture(texture);

	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(sprite);
		//window.draw(shape);
		window.display();
	}

	return 0;
}