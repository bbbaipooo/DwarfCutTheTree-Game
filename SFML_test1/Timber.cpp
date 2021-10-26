//important libraries in C++
#include"stdafx.h" //" " is for file included with Visual Studio
#include<SFML/Graphics.hpp> //include SFML graphics from the folder
#include<iostream>
#include<sstream> //power string

// when create class จะถูกเก็บในนี้ //using namespace for make code easier
using namespace sf;

void updateBranches(int seed);
const int amountBranches = 6;
Sprite branches[amountBranches];
//Player / Branch = LEFT / RIGHT??
enum class side { LEFT, RIGHT, NONE };
side branchPositions[amountBranches];

int main()
{
	// create video mode
	VideoMode size(1920, 1080);

	// create & show a window for the game
	RenderWindow window(size, "DwarfCutTheTree!!!", Style::Fullscreen);

	//////Background Game Start//////
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

	//Texture
	Texture background2Texture;
	if (!background2Texture.loadFromFile("graphics/Forest1.jpg")) 
	{
		std::cout << "Load Failed";
	}
	// Sprite
	Sprite background2Sprite;
	background2Sprite.setTexture(background2Texture);
	background2Sprite.setPosition(0, 0); //set to cover the screen

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
	sandwichSprite.setPosition(-90, 800);
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
	hamburgerSprite.setPosition(-68, 900);
	bool hamburgerActive = false;
	float hamburgerSpeed = 0.0f;

	//////hotdog//////
	Texture hotdogTexture;
	if (!hotdogTexture.loadFromFile("graphics/hotdog.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite hotdogSprite;
	hotdogSprite.setTexture(hotdogTexture);
	hotdogSprite.setPosition(-88, 1000);
	bool hotdogActive = false;
	float hotdogSpeed = 0.0f;

	//////pizza//////
	Texture pizzaTexture;
	if (!pizzaTexture.loadFromFile("graphics/pizza.png"))
	{
		std::cout << "Load Failed";
	}
	Sprite pizzaSprite;
	pizzaSprite.setTexture(pizzaTexture);
	pizzaSprite.setPosition(-85, 1000);
	bool pizzaActive = false;
	float pizzaSpeed = 0.0f;

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
	jamSprite1.setPosition(-250, 20); //position
	jamSprite2.setPosition(-250, 220);
	jamSprite3.setPosition(-250, 420);
	bool jamActive1 = false; //jam on screnn now?
	bool jamActive2 = false;
	bool jamActive3 = false;
	float jamSpeed1 = 0.0f; //How fast is each jam?
	float jamSpeed2 = 0.0f;
	float jamSpeed3 = 0.0f;

	//for control time
	Clock timer; // Clock=class , timer=object

	//Time bar
	RectangleShape timeBar;
	float timeBarStartWidth = 500;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool stopGame = true;

	//Draw Text on Display
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;

	Font font; //choose font
	font.loadFromFile("font/ka1.ttf");

	messageText.setFont(font);
	scoreText.setFont(font);

	messageText.setString("   PRESS ENTER TO \nSTART THE GAME ! ! !"); //assign
	scoreText.setString("SCORE   0");

	messageText.setCharacterSize(90);
	scoreText.setCharacterSize(85);

	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::Black);

	//Position the text
	FloatRect textBound = messageText.getLocalBounds();
	messageText.setOrigin(textBound.left + textBound.width / 2.0f,
						  textBound.top + textBound.height / 2.0f);
	messageText.setPosition(1920/2.0f,1080/2.0f);
	scoreText.setPosition(20,20);

	// 6 Branches
	Texture branchTexture;
	branchTexture.loadFromFile("graphics/branch1.png");
	for (int i = 0; i < amountBranches; i++)
	{
		branches[i].setTexture(branchTexture);
		branches[i].setPosition(-2000,-2000);
		// Set the Sprite's origin to dead center
		// Wecan then spin it round without changing its position
		branches[i].setOrigin(220,20);
	}

	updateBranches(1);
	updateBranches(2);
	updateBranches(3);
	updateBranches(4);
	updateBranches(5);

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

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			stopGame = false;

			//Reset Time & Score
			score = 0;
			timeRemaining = 5;
		}
		/*
		*********************************************
					  Update the scene
		*********************************************
		*/
		if (!stopGame)
		{
			//score++;
			// Measure time
			Time dt = timer.restart(); /*-restart timer every frame
				 dt mean delta time		 -know time how long every frame take
										 -return last time at update the scene to dt
										[.restart() = function of Clock]
										*/

			// minus from the amount of time remaining
			timeRemaining -= dt.asSeconds();
			// update size the time bar
			timeBar.setSize(Vector2f(timeBarWidthPerSecond* timeRemaining, 
										timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//stop the game
				stopGame = true;

				//Change message to show player
				messageText.setString("GAME OVER ! ! !");

				//Reposition the text based on its new size same the first before start game
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, 
										textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
			}

			// Manage Sandwich
			if (!sandwichActive)
			{
				//sandwich speed
				srand((int)time(0) * 200);
				sandwichSpeed = (rand() % 200) + 200; // random between 199-399

				//sandwich high
				srand((int)time(0) * 10);
				float height = (rand() % 420) + 420; // random between 419-839
				sandwichSprite.setPosition(1950, height);
				sandwichActive = true;
			}
			else
			{
				//Move sandwich
				sandwichSprite.setPosition(
					sandwichSprite.getPosition().x -
					(sandwichSpeed * dt.asSeconds()), //appoxe 1 second run 5000 frames so dt=0.0002,sandwichSpeed max=399
					sandwichSprite.getPosition().y);

				//Sandwich out of screen?
				if (sandwichSprite.getPosition().x < -90) //sandwich wide pixel = 90
				{
					sandwichActive = false;
				}
			}

			// Manage Hamburger
			if (!hamburgerActive)
			{
				srand((int)time(0) * 250);
				hamburgerSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 20);
				float height = (rand() % 490) + 490;
				hamburgerSprite.setPosition(2200, height);
				hamburgerActive = true;
			}
			else
			{
				//Move Hamburger
				hamburgerSprite.setPosition(
					hamburgerSprite.getPosition().x -
					(hamburgerSpeed * dt.asSeconds()),
					hamburgerSprite.getPosition().y);

				//Hamburger out of screen?
				if (hamburgerSprite.getPosition().x < -68) //hamburger wide pixel = 68
				{
					hamburgerActive = false;
				}
			}

			// Manage Hotdog
			if (!hotdogActive)
			{
				srand((int)time(0) * 300);
				hotdogSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 30);
				float height = (rand() % 520) + 520;
				hotdogSprite.setPosition(2400, height);
				hotdogActive = true;
			}
			else
			{
				//Move Hotdog
				hotdogSprite.setPosition(
					hotdogSprite.getPosition().x -
					(hotdogSpeed * dt.asSeconds()),
					hotdogSprite.getPosition().y);

				//Hotdog out of screen?
				if (hotdogSprite.getPosition().x < -88) //hotdog wide pixel = 88
				{
					hotdogActive = false;
				}
			}

			// Manage Pizza
			if (!pizzaActive)
			{
				srand((int)time(0) * 350);
				pizzaSpeed = (rand() % 200) + 200;

				srand((int)time(0) * 40);
				float height = (rand() % 470) + 470;
				pizzaSprite.setPosition(2600, height);
				pizzaActive = true;
			}
			else
			{
				//Move Pizza
				pizzaSprite.setPosition(
					pizzaSprite.getPosition().x -
					(pizzaSpeed * dt.asSeconds()),
					pizzaSprite.getPosition().y);

				//Pizza out of screen?
				if (pizzaSprite.getPosition().x < -85) //pizza wide pixel = 85
				{
					pizzaActive = false;
				}
			}

			// Manage Jam1;
			if (!jamActive1)
			{
				srand((int)time(0) * 10);
				jamSpeed1 = (rand() % 200);

				srand((int)time(0) * 10);
				float height = (rand() % 150);
				jamSprite1.setPosition(-250, height + 100); //jam wide pixel = 250
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
				float height = (rand() % 300) - 150;
				jamSprite2.setPosition(-250, height + 125); //jam wide pixel = 250
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
				float height = (rand() % 450) - 150;
				jamSprite3.setPosition(-250, height + 150); //jam wide pixel = 250
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

			//Update score text to show on display
			std::stringstream ss;
			ss << "SCORE   " << score;
			scoreText.setString(ss.str());

			//Update brancgh Sprites
			for (int i = 0; i < amountBranches; i++)
			{
				float height = i * 150;
				if (branchPositions[i] == side::LEFT)
				{
					//move to left side
					branches[i].setPosition(610, height);
					//flip sprite from original photo
					branches[i].setRotation(180);
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0);
				}
				else
				{
					//hide branch
					branches[i].setPosition(3000, height);
				}
			}

		} //END of Function[if(!stopGame)]
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
		//Draw Branches
		for (int i = 0; i < amountBranches; i++)
		{
			window.draw(branches[i]);
		}
		//Draw Tree
		window.draw(treeSprite);
		//Draw Sandwich (draw after tree = drifting either infront or behind tree)
		window.draw(sandwichSprite);//หรือจะวางไว้ข้างหน้าtreeก้ได้เพราะมันจะทำให้เวลาเรามองกิ่งไม้แล้วไขว้เขว
		//Draw Hamburger
		window.draw(hamburgerSprite);
		//Draw Hotdog
		window.draw(hotdogSprite);
		//Draw Pizza
		window.draw(pizzaSprite);
		//Draw TimeBar
		window.draw(timeBar);
		//Draw the score
		window.draw(scoreText);
		//draw the massege
		if (stopGame)
		{
			window.draw(background2Sprite);
			window.draw(messageText);
		}


		// Show everything I just draw
		window.display();

	}

	return 0;

}

void updateBranches(int seed)
{
	//move all branches down one place
	for (int j = amountBranches - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}
	//born a new branch at position 0
	//LEFT / RIGHT / NONE
	srand((int)time(0) + seed);
	int r = (rand() % 5);
	switch (r)
	{
	case 0:
		branchPositions[0] = side::LEFT;
		break;

	case 1:
		branchPositions[0] = side::RIGHT;
		break;

	default:
		branchPositions[0] = side::NONE;
		break;
	}
}