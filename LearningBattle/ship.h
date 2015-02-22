#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265


typedef float HealthUnit;
enum status { dead = -1,idle, searching, engaging, attacking, retreating };
sf::Texture shipTexture;


class Ship {

	//Add proper data variables for ship (i.e locations, rotation, health, status etc)
private:
	bool alive;
	int status, id;
	float rot, speed, maxSpeed, accel, deccel, locx, locy, scale, //Movement traits
		  health, fireRange, fireDmg, accuracy, rof, ammo, bulletSpeed; //Combat traits
	sf::Texture texture;
	//sf::Sprite sprite;

public:
	sf::Sprite sprite;

	//The construstor
	Ship(char * imageFile){
		alive = true;
		status = 0;
		id = 0;
		scale = 0.5f;
		rot = 0;
		speed = 1;
		maxSpeed = 5;
		accel = 0.1f;
		deccel = 0.3f;
		locx = 50;
		locy = 50;

		health = 100;
		fireRange = 100;
		fireDmg = 10;
		accuracy = 60;
		rof = 2;
		ammo = 5;
		bulletSpeed = 2;
		

		sprite.setPosition(locx, locy);
		shipTexture.create(10, 10);

		if (!shipTexture.loadFromFile(imageFile)){
			printf("Error image not loaded properly.");
		}

		sprite.scale(sf::Vector2f(scale, scale)); // factor relative to the current scale
		sprite.setTexture(shipTexture);
	}


	void incPositionFromRot(){
		float moveX, moveY = 0;
		float rotation = (this->rot/180)*PI;

		///printf("rotation: %f\n", rotation);
		moveX = cos(rotation);
		moveY = sin(rotation);
		///printf("rotation: %f    moveX: %f    moveY: %f\n",this->rot, moveX, moveY);
		

		this->setLocx(this->locx + (moveX*speed));
		this->setLocy(this->locy + (moveY*speed));

		/*
		while (rotation < 0){
		rotation += 360;
		}
		
		if (rotation == 0){
			moveY = -1;
		}
		else if (rotation == 90){
			moveX = 1;
		}
		else if (rotation == 180){
			moveY = 1;
		}
		else if (rotation == 270){
			moveX = -1;
		}else if (90 > rotation && rotation > 0){
			//In top right quadrent
			///printf("1\n");
			moveX = sin(rotation); //is Negative (to move left)
			moveY = -cos(rotation); //make Negative (to move up)
		}else if (180 > rotation && rotation > 90){
			//Bottom right quadrent
			///printf("2\n");
			moveX = sin(rotation); //is Positive (to move right)
			moveY = -cos(rotation); //make Negative to Positive (positive move down)
		}else if (270 > rotation && rotation > 180){
			//Bottom left quadrent
			///printf("3\n");
			moveX = sin(rotation); //is negative (positive move left)
			moveY = -cos(rotation); //make Negative Positive (positive to move down)
		}else if (360 > rotation && rotation > 270){
			//Should be in the top left quadrent
			printf("4\n");
			moveX = sin(rotation); //is Negative (to move right)
			moveY = -cos(rotation); //make Negative (to move up)
		}else{
			///printf("Error calculating movement.\n");
		}
		
		///printf("moveX: %f\nmoveY: %f\n",moveX, moveY);
		this->locx += (moveX*speed);
		this->locy += (moveY*speed);
		this->sprite.setPosition(this->locx, this->locy);
		*/
	}


	void incSpeed(){
		this->speed += this->speed*(1+this->accel);
		if (this->speed > this->maxSpeed){
			this->speed = this->maxSpeed;
		}
	}


	void decSpeed(){
		this->speed -= this->speed*(1+this->deccel);
		if (this->speed < 0){
			this->speed = 0;
		}
	}

	void setRotFromXY(float x, float y){

		float deltaY = y - this->getLocy();
		float deltaX = x - this->getLocx();

		float angleInDegrees = (float)((atan2(deltaY, deltaX) * 180 / PI)); //-90 is from image origin pointing up

		this->setRot(angleInDegrees);
	}

	int getRotFromXY(float x, float y){

		float deltaY = y - this->locy;
		float deltaX = x - this->locx;

		float angleInDegrees = (float)( (atan2(deltaY, deltaX) * 180 / PI)); //-270 is from image origin pointing up

		return (int)angleInDegrees;
	}


	/*
	* Getters And Setters
	*/
	bool getAlive(){
		return this->alive;
	}

	float getLocx(){
		return this->locx;
	}

	float getLocy(){
		return this->locy;
	}

	float getHealth(){
		return this->health;
	}

	int getStatus(){
		return this->status;
	}

	int getId(){
		return this->id;
	}

	float getRot(){
		return this->rot;
	}

	float getSpeed(){
		return this->speed;
	}

	float getMaxSpeed(){
		return this->maxSpeed;
	}

	float getAccel(){
		return this->accel;
	}

	float getDeccel(){
		return this->deccel;
	}

	float getScale(){
		return this->scale;
	}

	sf::Texture getTexture(){
		return this->texture;
	}

	sf::Sprite getSprite(){
		return this->sprite;
	}


	void setAlive(bool alive){
		this->alive = alive;
	}

	void setLocx(float locx){
		this->sprite.setPosition(locx, this->locy);
		this->locx = locx;
	}

	void setLocy(float locy){
		this->sprite.setPosition(this->locx, locy);
		this->locy = locy;
	}

	void setHealth(float health){
		this->health = health;
	}

	void setStatus(int status){
		this->status = status;
	}

	void setId(int id){
		this->id = id;
	}

	void setRot(float rot){
		float rotation = (rot * PI / 180);
		//rot = ((int)rotation%360); //Makes degrees positive (loses up to 1 degree of accuracy)
		rot = rotation;
		if (rot < 0){
			rot += 360;
		}
		rot = (rot * 180 / PI);
		this->sprite.setRotation(rot+90);
		this->rot = rot;
	}

	void setSpeed(float speed){
		this->speed = speed;
	}

	void setMaxSpeed(float maxSpeed){
		this->maxSpeed = maxSpeed;
	}

	void setAccel(float accel){
		this->accel = accel;
	}

	void setDeccel(float deccel){
		this->deccel = deccel;
	}

	void setScale(float scale){
		this->scale = scale;
	}

	void setTexture(sf::Texture texture){
		this->texture = texture;
	}

	void setSprite(sf::Sprite sprite){
		this->sprite = sprite;
	}

};

/*
* IMPORTANT: This function might have a problem declaring the ship. The memory used for 
* declaring the ship might not be accessable after the function call causing major issues.
*/
int addShipToList(std::vector<Ship> shipArray, char * image){

	Ship * ship = new Ship(image);

	printf("array size: %d\n",shipArray.capacity());
	if (shipArray._Unused_capacity() != shipArray.capacity()){
		//printf("Array is not full. There is space to add another ship\n");
		shipArray[shipArray._Unused_capacity()] = *ship;
		ship->setId(shipArray._Unused_capacity());

	}
	
    return 0;
}

/*

*/
void drawShips(std::vector<Ship> shipArray, sf::RenderWindow window){
	for (int i = 0; i < shipArray._Unused_capacity(); i++){
		window.draw(shipArray[i].getSprite());
	}

}