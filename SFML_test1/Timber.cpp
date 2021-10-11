//important libraries in C++
#include"stdafx.h"//" " is for file included with Visual Studio
#include<SFML/Graphics.hpp>//include SFML graphics from the folder
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
	backgroundSprite.setPosition(0, 0);//set to cover the screen

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
		

		// Show everything I just draw
		window.display();

	}


	return 0;
}
