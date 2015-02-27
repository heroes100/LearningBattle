#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>


typedef float HealthUnit;
enum status { dead = -1, idle, searching, engaging, attacking, retreating };
sf::Texture bulletTexture;

/*
TODO:
+ Possibly implement a system inside/outside of bullet object that allows
   for selection of different bullets externally more easily
*/
class Bullet {
private:
	float locx, locy, rot, y, m, x, b, //Movement traits
		scale,
		speed, damage, lifeTime; //Combat traits

	sf::Texture texture;

public:

	sf::Sprite sprite;

	Bullet(float x, float y, char * imageFile){
		locx = 0;
		locy = 0;
		rot = 0;
		scale = 1;
		y = x = m = b = 0;
		speed = 0;
		damage = 2;
		lifeTime = 4;


		sprite.setPosition(locx, locy);
		bulletTexture.create(10, 5);

		if (!bulletTexture.loadFromFile(imageFile)){
			printf("Error image not loaded properly.");
		}

		sprite.scale(sf::Vector2f(scale, scale)); // factor relative to the current scale
		sprite.setTexture(bulletTexture);
	}

	void incPositionFromRot(){
		float moveX, moveY = 0;
		float rotation = (this->rot / 180)*PI;

		///printf("rotation: %f\n", rotation);
		moveX = cos(rotation);
		moveY = sin(rotation);
		///printf("rotation: %f    moveX: %f    moveY: %f\n",this->rot, moveX, moveY);


		this->setLocx(this->locx + (moveX*speed));
		this->setLocy(this->locy + (moveY*speed));
	}

};
