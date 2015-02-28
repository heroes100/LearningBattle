#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <time.h>
#include <Windows.h>

#include "ship.h"

/*
TODO List:
[Include '!' at the beggining of any below for more immeditate matters that should be addressed before continuing (These may also be posted at the top of the list)]
[(+) > Someting still needed to be added or created]
[(*) > Something still needed to be adjusted/reformed]
[(-) > Something needed to be removed or dispersed]
[(~) > Suggested or possible improvements and others]



!~ If files or project is to be shared, create a proper git/repo management system to maintain stability and coherence


+ Create a quad tree for collision detection (tree maps players position to quadrants via tree)
+ Create bullet obeject such that Ships can fire bullets
+ Create a system which can manage ship objects (Creation/deletion etc)
+ Create seperate functions to handle tasks used in main loop (i.e Draw, Update, Increment 'cycle', etc)


* Adjust main such that it has a proper structure for handeling main loop of program and such
* Adjust hard coded data used from example into variables which might be useful

-


~ Add proper file headers including information such as purpose, creation date, version etc. for all files


Comeplete: Properly establish basic ship object
*/


int main()
{
	sf::RenderWindow window(sf::VideoMode(500, 400), "Learning Battle");

	std::vector<Ship> shipArray(1, Ship("ship.png")); //Creates 100 ship objects in vector


	//addShipToList(shipArray, "ship.png");
	shipArray[0].setLocx(250);
	//shipArray[1].setLocx(150);


	sf::CircleShape circle(10.f);
	circle.setPosition(200, 200);
	circle.setFillColor(sf::Color::Green);

	int temp = 0;
	while (window.isOpen()){
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::White);

		//window.draw(ship.getSprite());
		//drawShips(shipArray, window);
		for (int i = 0; i < shipArray.size(); i++){

			//shipArray[i].setRot(shipArray[i].getRotFromXY(200,400));
			shipArray[i].setRotFromXY(200, 200);
			if (temp % 20 == 0){
				//shipArray[i].setRot(shipArray[i].getRot() + 90); //Rotates clockwise
				///printf("rotation: %f\n",shipArray[0].getRot());
				//shipArray[i].setRot(shipArray[i].getRot() + 10);
			}

			//printf("rot: %f\n", shipArray[0].getRot());
			shipArray[i].incPositionFromRot();

			window.draw(shipArray[i].getSprite());
		} //Won't properly draw ships to window if sent through to a function for some reason


		temp++;

		window.draw(circle);

		window.display();

		Sleep(20);
	}
	printf("Press esc ket to quit.");
	scanf_s(".");

	return 0;
}

