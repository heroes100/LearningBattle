#include <SFML/Graphics.hpp>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265


typedef float HealthUnit;
enum status { dead = -1, idle, searching, engaging, attacking, retreating };
float minRotSpeed = 0.1;
sf::Texture shipTexture;


class Ship {

	//Add proper data variables for ship (i.e locations, rotation, health, status etc)
private:
	bool alive;
	int status, id;
	float rot, rotSpeed, speed, maxSpeed, accel, deccel, locx, locy, scale, //Movement traits
		health, fireRange, fireDmg, accuracy, rof, ammo, bulletSpeed; //Combat traits
<<<<<<< HEAD
	//sf::Texture texture;
=======
	sf::Texture texture;
>>>>>>> origin/master
	//sf::Sprite sprite;

public:
	sf::Texture texture;
	sf::Sprite sprite;

	//The construstor
	Ship(char * imageFile){
		alive = true;
		status = 0;
		id = 0;
		scale = 0.5f;
		rot = 0;
<<<<<<< HEAD
		rotSpeed = 2;
		speed = 5;
=======
		rotSpeed = 5;
		speed = 2;
>>>>>>> origin/master
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

	/*
	This function will calculate the X and Y movement based on the Ships current angle and speed
	*/
	void incPositionFromRot(){
		float moveX, moveY = 0;
		float rotation = (this->rot / 180)*PI; //Convert to radians for trig

		moveX = cos(rotation);
		moveY = sin(rotation);
		///printf("rotation: %f    moveX: %f    moveY: %f\n",this->rot, moveX, moveY);
<<<<<<< HEAD
=======

>>>>>>> origin/master

		this->setLocx(this->locx + (moveX*speed));
		this->setLocy(this->locy + (moveY*speed));

	}

	bool checkPointInTurn(float curX, float curY, float curRot, float radius, float targetX, float targetY){

		//My radius value isnt correct, needs to be calculated for
		//TODO: Capture case of 0 rotation speed
		radius = this->speed / (this->rotSpeed/360);
		curRot += 90;

		float centerX = -1;
		float centerY = -1;
		if (curRot > 180 + 90 && curRot < 360 + 90){
			//Left half of circle
			centerX = curX + (sin(curRot)*radius);
		}
<<<<<<< HEAD
		else{
			//Right half of circle
			centerX = curX - (sin(curRot)*radius);
		}

		if (curRot > 270+90 || curRot < 90+90){
			//Top half of circle
			centerY = curY + (cos(curRot)*radius);
		}
		else{
			//Bottom half of circle
			centerY = curY - (cos(curRot)*radius);
		}
		//float centerX = (sin(curRot)*radius) +curX;
		//float centerY = (cos(curRot)*radius) +curY; //TODO: Double check that up/down is correctly calculated

		printf("X: %f\tY: %f\nCenterX: %f     CenterY: %f\n",curX, curY, centerX,centerY);

		if ((centerX + radius) > targetX && (centerX - radius) < targetX && (centerY + radius) > targetY && (centerY - radius) < targetY){
			return true;
		}
		else{
			return false;
		}

	}

	/*
	This function will find the shortest rotation path (CW/CCW) to reach the target Rotation
	Note: This function deals with rotation in degrees only
	Note: This function favours Clockwise when both options are equal
	*/
	float rotateTo(float targetRot){
		bool adjCurRot = false;
		float finalRotation = 0;
		float curRot = this->rot;
		///printf("currently rotated at: %f\trot To: %f\trot rem: %f degrees\n",this->rot, targetRot, abs(targetRot - this->rot));

		if (targetRot < 0){
			//Adjust to make sure angle is positive
			targetRot += 360;
			//Need to track this since ship can deal with negatives
			//Need to add 360 back if it was subtracted
		}
		if (this->rot < 0){
			//Adjust to make sure angle is positive for logic
			adjCurRot = true;
			curRot += 360;
			//Need to track this since ship deals with negative degrees
		}

		
		//Compare the distances for CW vs CCW
		if ((targetRot - curRot) >= 0 || targetRot + 180 < curRot){
			//Clockwise is shorter rotation increase rotation
			if (targetRot + 180 < curRot){ //Shorter to turn more than 360 (350->20 case)
				if (targetRot + 360 > (curRot + this->rotSpeed)){
					finalRotation = curRot + this->rotSpeed;
				}
				else{
					finalRotation = targetRot;
				}
			}
			else if (targetRot > (curRot + this->rotSpeed)){
				//Target rotation is out of range, move by max rotation speed
				finalRotation = curRot + this->rotSpeed;
			}
			else{
				//Target rotation is in range, move precisely to that angle
				finalRotation = targetRot;
			}
		}
		else{ //Counter clockwise is shorter rotation
			if (targetRot + 180 > curRot){ //Shorter to turn negative degrees (20->350 case)
				//Shorter to rotate Coutner clockwise
				if (targetRot - 360 < (curRot - this->rotSpeed)){
					//Target rotation is out of range, move by max rotation speed
					finalRotation = curRot - this->rotSpeed;
				}
				else{
					//Target rotation is in range, move precisely to that angle
					finalRotation = targetRot;
				}
			}
			else if ((curRot - this->rotSpeed) > targetRot){
				//Rotation is out of range, move by max rotation speed
				finalRotation = curRot - this->rotSpeed;
			}
			else{
				//Rotation is in range, move precisely to that angle
				finalRotation = targetRot;
			}
		}

		if (adjCurRot){
			//Revert back to origonal negative value if adjusted earlier
			finalRotation -= 360;
		}

		return finalRotation;
	}


	void rotateClockwise(float targetRot){
		if (abs(this->rot - targetRot) > this->rotSpeed){
			this->setRot(this->rot + rotSpeed);
		}
		else{
			this->setRot(this->rot = targetRot);
		}
	}


	void rotateCounterClockwise(float targetRot){
		if (abs(this->rot - targetRot) > this->rotSpeed){
			this->rot -= rotSpeed;
		}
		else{
			this->rot = targetRot;
		}
=======

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
>>>>>>> origin/master
	}

	/*
	This function will find the shortest rotation path (CW/CCW) to reach the target Rotation
	Note: This function deals with rotation in degrees only
	Note: This function favours Clockwise when both options are equal
	*/
	float rotateTo(float targetRot){
		bool adjCurRot = false;
		float finalRotation = 0;
		float curRot = this->rot;
		///printf("currently rotated at: %f\trot To: %f\trot rem: %f degrees\n",this->rot, targetRot, abs(targetRot - this->rot));

		if (targetRot < 0){
			//Adjust to make sure angle is positive
			targetRot += 360;
			//Need to track this since ship can deal with negatives
			//Need to add 360 back if it was subtracted
		}
		if (this->rot < 0){
			//Adjust to make sure angle is positive for logic
			adjCurRot = true;
			curRot += 360;
			//Need to track this since ship deals with negative degrees
		}

		//Compare the distances for CW vs CCW
		if ((targetRot - curRot) >= 0 || targetRot + 180 < curRot){
			//Clockwise is shorter rotation increase rotation
			if (targetRot + 180 < curRot){ //Shorter to turn more than 360 (350->20 case)
				if (targetRot + 360 > (curRot + this->rotSpeed)){
					finalRotation = curRot + this->rotSpeed;
				}
				else{
					finalRotation = targetRot;
				}
			}
			else if (targetRot > (curRot + this->rotSpeed)){
				//Target rotation is out of range, move by max rotation speed
				finalRotation = curRot + this->rotSpeed;
			}
			else{
				//Target rotation is in range, move precisely to that angle
				finalRotation = targetRot;
			}
		}
		else{ //Counter clockwise is shorter rotation
			if (targetRot + 180 > curRot){ //Shorter to turn negative degrees (20->350 case)
				//Shorter to rotate Coutner clockwise
				if (targetRot - 360 < (curRot - this->rotSpeed)){
					//Target rotation is out of range, move by max rotation speed
					finalRotation = curRot - this->rotSpeed;
				}
				else{
					//Target rotation is in range, move precisely to that angle
					finalRotation = targetRot;
				}
			}
			else if ((curRot - this->rotSpeed) > targetRot){
				//Rotation is out of range, move by max rotation speed
				finalRotation = curRot - this->rotSpeed;
			}
			else{
				//Rotation is in range, move precisely to that angle
				finalRotation = targetRot;
			}
		}

		if (adjCurRot){
			//Revert back to origonal negative value if adjusted earlier
			finalRotation -= 360;
		}

		return finalRotation;
	}


	void rotateClockwise(float targetRot){
		if (abs(this->rot - targetRot) > this->rotSpeed){
			this->setRot(this->rot + rotSpeed);
		}
		else{
			this->setRot(this->rot = targetRot);
		}
	}


	void rotateCounterClockwise(float targetRot){
		if (abs(this->rot - targetRot) > this->rotSpeed){
			this->rot -= rotSpeed;
		}
		else{
			this->rot = targetRot;
		}
	}


	void incSpeed(){
<<<<<<< HEAD
		this->speed += (this->accel);
=======
		this->speed += this->speed*(1 + this->accel);
>>>>>>> origin/master
		if (this->speed > this->maxSpeed){
			this->speed = this->maxSpeed;
		}
	}


	void decSpeed(){
<<<<<<< HEAD
		this->speed -= (this->deccel);
=======
		this->speed -= this->speed*(1 + this->deccel);
>>>>>>> origin/master
		if (this->speed < 0){
			this->speed = 0;
		}
	}

	void setRotFromXY(float x, float y){
		//TODO: Fix bug where ship won't intercept point due to speed/rotSpeed differences
		// |-> Create calculations to help or reduce speed during rotation (or have both options available)

		float deltaY = y - this->getLocy();
		float deltaX = x - this->getLocx();
		///checkPointInTurn(this->locx, this->locy, this->rot, this->rot, x, y);
		float angleInDegrees = (float)((atan2(deltaY, deltaX) * 180 / PI)); //-90 is from image origin pointing up
		/*if (angleInDegrees < 0){
		angleInDegrees += 360;
		}*/
<<<<<<< HEAD



		//TODO: Create precheck to determine if 'special tactics' to reach target are necessary
		//  |-> calculate arc from a->b using radius rotSpeed
		// To find out if the ship can reach the new coord, Calculate if the point is in the area of a circle (where ship is on the circumfrence)
		// Given radius rotSpeed and finding centerpoint by (-90 degrees from current rotation)
		float temp = this->setRot(angleInDegrees);
		if ( temp != this->getRot()){

		}
		//TODO: implement proper check for calculating point
		if (checkPointInTurn(this->locx, this->locy, this->rot, this->rotSpeed, x, y)){
			//Slow down
			this->decSpeed();
		}
		else{
			this->incSpeed();
		}

=======
>>>>>>> origin/master
		///printf("Need %f degrees of rotation.\n",angleInDegrees);

		this->setRot(angleInDegrees);
	}

	int getRotFromXY(float x, float y){

		float deltaY = y - this->locy;
		float deltaX = x - this->locx;

		float angleInDegrees = (float)((atan2(deltaY, deltaX) * 180 / PI)); //-270 is from image origin pointing up

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

	float getRotSpeed(){
		return this->rotSpeed;
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
		float rotation;
		//rot = ((int)rotation%360); //Makes degrees positive (loses up to 1 degree of accuracy)
		//rot = (rot * 180 / PI); //Convert to degrees
		/*if (rot < 0){ //Change to positive angles only
		rot += 360; //FIXME: This might be causing problems with changing from 0->360 instantly
		}*/

		rotation = this->rotateTo(rot); //Get final ship rotation after adjustments from rotation speed
		///printf("Rotation set to: %f degrees\n\n", rotation);
		//rotation = (rotation * PI / 180); //Convert back to radians
		//TODO: FIX radians and degrees use; it is causing issues/bugs
<<<<<<< HEAD
		if (rotation > 360){
			rotation -= 360;
		}
=======

>>>>>>> origin/master
		this->sprite.setRotation(rotation + 90); //Adjust sprite to rotation
		this->rot = rotation; //Adjust ship to rotation
	}

	void setRotSpeed(float rotSpeed){
		if (rotSpeed > 0){
			this->rotSpeed = rotSpeed;
		}
		else{
			this->rotSpeed = minRotSpeed;
		}
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

<<<<<<< HEAD
=======
/*
* IMPORTANT: This function might have a problem declaring the ship. The memory used for
* declaring the ship might not be accessable after the function call causing major issues.
*/
int addShipToList(std::vector<Ship> shipArray, char * image){

	Ship * ship = new Ship(image);

	printf("array size: %d\n", shipArray.capacity());
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
>>>>>>> origin/master
