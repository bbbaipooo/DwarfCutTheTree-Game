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

	////// Texture
	Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("graphics/Background2.jpg"))
	{
		std::cout << "Load Failed";
	}
	
	////// Sprite
	Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);//set to cover the screen

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
		// Clear everything from the last frame
		window.clear();

		// Draw game scene here
		window.draw(backgroundSprite);

		// Show everything I just draw
		window.display();

	}


	return 0;
}
