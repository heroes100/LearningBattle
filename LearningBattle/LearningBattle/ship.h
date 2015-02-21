#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>


typedef float HealthUnit;
enum status { dead = -1,idle, searching, engaging, attacking, retreating };
sf::Texture shipTexture;


class Ship {

	//Add proper data variables for ship (i.e locations, rotation, health, status etc)
private:
	bool alive;
	int status, id;
	float rot, speed, maxSpeed, accel, deccel, health, locx, locy, scale;
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
		speed = 10;
		maxSpeed = 5;
		accel = 0.1f;
		deccel = 0.3f;
		health = 0;
		locx = 50;
		locy = 50;

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
		float rotation = ((int)this->rot % 360);
		
		moveX = cos(rotation);
		moveY = sin(rotation);
		/*if (rotation == 0){
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
			moveX = sin(this->rot); //is Negative (to move left)
			moveY = -cos(this->rot); //make Negative (to move up)
		}else if (180 > rotation && rotation > 90){
			//Bottom right quadrent
			moveX = sin(this->rot); //is Positive (to move right)
			moveY = -cos(this->rot); //make Negative to Positive (positive move down)
		}else if (270 > rotation && rotation > 180){
			//Bottom left quadrent
			moveX = sin(this->rot); //is negative (positive move left)
			moveY = -cos(this->rot); //make Negative Positive (positive to move down)
		}else if (360 > rotation && rotation > 270){
			//Should be in the top left quadrent
			moveX = sin(this->rot); //is Negative (to move right)
			moveY = cos(this->rot); //is Negative (to move up)
		}
		*/

		this->setLocx(this->locx+(moveX*speed));
		this->setLocy(this->locy+(moveY*speed));
		/*this->locx += (moveX*speed);
		this->locy += (moveY*speed);
		this->sprite.setPosition(this->locx, this->locy);*/
	}


	void setRotFromXY(float x, float y){

		float deltaY = y - this->getLocy();
		float deltaX = x - this->getLocx();

		float angleInDegrees = (float)(-270 + (atan2(deltaY, deltaX) * 180 / 3.14159265)); //-90 is from image origin pointing up

		this->setRot(angleInDegrees);
	}

	int getRotFromXY(float x, float y){

		float deltaY = y - this->locy;
		float deltaX = x - this->locx;

		float angleInDegrees = (float)(-270 + (atan2(deltaY, deltaX) * 180 / 3.14159265)); //-270 is from image origin pointing up

		return (int)angleInDegrees;
	}


	/*
	* Getters And Setters
	*/
	bool getAlive(){
		return alive;
	}

	float getLocx(){
		return locx;
	}

	float getLocy(){
		return locy;
	}

	float getHealth(){
		return health;
	}

	int getStatus(){
		return status;
	}

	int getId(){
		return id;
	}

	float getRot(){
		return rot;
	}

	float getSpeed(){
		return speed;
	}

	float getMaxSpeed(){
		return maxSpeed;
	}

	float getAccel(){
		return accel;
	}

	float getDeccel(){
		return deccel;
	}

	float getScale(){
		return scale;
	}

	sf::Texture getTexture(){
		return texture;
	}

	sf::Sprite getSprite(){
		return sprite;
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
		this->sprite.setRotation(rot);
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