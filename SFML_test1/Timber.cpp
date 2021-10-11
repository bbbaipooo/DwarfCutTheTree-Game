//important libraries in C++
#include"stdafx.h" //" " is for file included with Visual Studio
#include<SFML/Graphics.hpp> //include SFML graphics from the folder
#include<iostream>

// when create class จะถูกเก็บในนี้ //using namespace for make code easier
using namespace sf;

int main()
{
	// create video mode
	VideoMode size(1920, 1080);

	// create & show a window for the game
	RenderWindow window(size, "DwarfCutTheTree!!!", Style::Fullscreen);

	//////Background//////
	//Texture
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("graphics/Background2.jpg"))
	{
		std::cout << "Load Failed";
	}
	// Sprite
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0); //set to cover the screen

	//////Tree//////
	Texture treeTexture;
	if (!treeTexture.loadFromFile("graphics/tree.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite treeSprite;
	treeSprite.setTexture(treeTexture);
	treeSprite.setPosition(810, 0);

	//////Sandwich//////
	Texture sandwichTexture;
	if (!sandwichTexture.loadFromFile("graphics/sandwich.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite sandwichSprite;
	sandwichSprite.setTexture(sandwichTexture);
	sandwichSprite.setPosition(0, 800);
	bool sandwichActive = false; //sandwich on sceen now?
	float sandwichSpeed = 0.0f; //How fast is sandwich?

	//////Hamburger//////
	Texture hamburgerTexture;
	if (!hamburgerTexture.loadFromFile("graphics/hamburger.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite hamburgerSprite;
	hamburgerSprite.setTexture(hamburgerTexture);
	//hamburgerTexture.setPosition(0, 800);


	//////hotdog//////
	// 
	//////Jam//////
	Texture jamTexture;
	if (!jamTexture.loadFromFile("graphics/jam.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite jamSprite1; //3 jam sprites from 1 texture
	Sprite jamSprite2;
	Sprite jamSprite3;
	jamSprite1.setTexture(jamTexture);
	jamSprite2.setTexture(jamTexture);
	jamSprite3.setTexture(jamTexture);
	jamSprite1.setPosition(0, 20); //position
	jamSprite2.setPosition(0, 220);
	jamSprite3.setPosition(0, 420);
	bool jamActive1 = false; //jam on screnn now?
	bool jamActive2 = false;
	bool jamActive3 = false;
	float jamSpeed1 = 0.0f; //How fast is each jam?
	float jamSpeed2 = 0.0f;
	float jamSpeed3 = 0.0f;

	//for control time
	Clock timer; // Clock=class , timer=object

	while (window.isOpen()) 
	{
		/*
		*********************************************
		          Handle the players input
		*********************************************
		*/
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		********************************************* 
		              Update the scene
		*********************************************
		*/

		// Measure time
		Time dt = timer.restart(); /*-restart timer every frame
			 dt mean delta time		 -know time how long every frame take
									 -return last time at update the scene to dt
									[.restart() = function of Clock]
									*/

		// Manage Sandwich
		if (!sandwichActive)
		{
			//sandwich speed
			srand((int)time(0) * 200);
			sandwichSpeed = (rand() % 200) + 200; // random between 199-399

			//sandwich high
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500; // random between 499-999
			sandwichSprite.setPosition(2000, height);
			sandwichActive = true;
		}
		else
		{
			//Move sandwich
			sandwichSprite.setPosition(
				sandwichSprite.getPosition().x-
				(sandwichSpeed*dt.asSeconds()), //appoxe 1 second run 5000 frames so dt=0.0002,sandwichSpeed max=399
				sandwichSprite.getPosition().y);

			//Sandwich out of screen?
			if (sandwichSprite.getPosition().x < -90) //sandwich wide pixel = 90
			{
				sandwichActive = false;
			}
		}

		// Manage Jam1;
		if (!jamActive1)
		{
			srand((int)time(0) * 10);
			jamSpeed1 = (rand() % 200);

			srand((int)time(0) * 10);
			float height = (rand() % 150);
			jamSprite1.setPosition(-250, height+100); //jam wide pixel = 250
			jamActive1 = true;
		}
		else
		{
			//Move Jam1
			jamSprite1.setPosition(
				jamSprite1.getPosition().x + 
				(jamSpeed1 * dt.asSeconds()), 
				jamSprite1.getPosition().y);

			//Jam1 out of screen?
			if (jamSprite1.getPosition().x > 1920) //background wide pixel = 1920
			{
				jamActive1 = false;
			}
		}

		// Manage Jam2;
		if (!jamActive2)
		{
			srand((int)time(0) * 20);
			jamSpeed2 = (rand() % 200);

			srand((int)time(0) * 20);
			float height = (rand() % 300)-150;
			jamSprite2.setPosition(-250, height+125); //jam wide pixel = 250
			jamActive2 = true;
		}
		else
		{
			//Move Jam2
			jamSprite2.setPosition(
				jamSprite2.getPosition().x +
				(jamSpeed2 * dt.asSeconds()),
				jamSprite2.getPosition().y);

			//Jam2 out of screen?
			if (jamSprite2.getPosition().x > 1920) //background wide pixel = 1920
			{
				jamActive2 = false;
			}
		}

		// Manage Jam3;
		if (!jamActive3)
		{
			srand((int)time(0) * 30);
			jamSpeed3 = (rand() % 200);

			srand((int)time(0) * 30);
			float height = (rand() % 450)-150;
			jamSprite3.setPosition(-250, height+150); //jam wide pixel = 250
			jamActive3 = true;
		}
		else
		{
			//Move Jam3
			jamSprite3.setPosition(
				jamSprite3.getPosition().x +
				(jamSpeed3 * dt.asSeconds()),
				jamSprite3.getPosition().y);

			//Jam3 out of screen?
			if (jamSprite3.getPosition().x > 1920) //background wide pixel = 1920
			{
				jamActive3 = false;
			}
		}
		/*
		*********************************************
		               Draw the scene
		*********************************************
		*/
		//// Clear everything from the last frame
		window.clear();

		//// Draw everything in game 
		//Draw Scene 
		window.draw(backgroundSprite);
		//Draw Jam (draw before tree = drifting in front of tree)
		window.draw(jamSprite1);
		window.draw(jamSprite2);
		window.draw(jamSprite3);
		//Draw Tree
		window.draw(treeSprite);
		//Draw Sandwich (draw after tree = drifting either infront or behind tree)
		window.draw(sandwichSprite);//หรือจะวางไว้ข้างหน้าtreeก้ได้เพราะมันจะทำให้เวลาเรามองกิ่งไม้แล้วไขว้เขว
		//Draw Hamburger
		window.draw(hamburgerSprite);
		

		// Show everything I just draw
		window.display();

	}


	return 0;
}