//important libraries in C++
#include"stdafx.h" //" " is for file included with Visual Studio
#include<SFML/Graphics.hpp> //include SFML graphics from the folder
#include<iostream>
#include<sstream> //power string
#include<SFML/Audio.hpp>
#include <string>
#include <fstream>
#define TOPSCORE 5
#define FILENAME "score.txt"

// when create class จะถูกเก็บในนี้ //using namespace for make code easier
using namespace sf;
using namespace std;

void saveScoreFile(string name, int score);
void readScoreFile();
void updateBranches(int seed);

void updateBranches(int seed);
const int amountBranches = 6;
Sprite branches[amountBranches];
//Player / Branch = LEFT / RIGHT??
enum class side { LEFT, RIGHT, NONE };
side branchPositions[amountBranches];

struct ScoreData
{
	string name;
	int score;
};
ScoreData scoreData[TOPSCORE + 1];

int main()
{
	// create video mode
	VideoMode size(1920, 1080);
	// create & show a window for the game
	RenderWindow window(size, "DwarfCutTheTree!!!", Style::Fullscreen);

	readScoreFile();

	//++++++++++++ initialize Game++++++++++++
	//////Background Game Start//////
	//Texture

	bool stopGame = true;
	bool acceptInput = false;  // Control the player input

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
	bool pizzaActive = false;
	float pizzaSpeed = 0.0f;

	//////......................Jam.................//////
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
	bool jamActive1 = false; //jam on screnn now?
	bool jamActive2 = false;
	bool jamActive3 = false;
	float jamSpeed1 = 0.0f; //How fast is each jam?
	float jamSpeed2 = 0.0f;
	float jamSpeed3 = 0.0f;

	//for control time
	Clock timer; // Clock=class , timer=object

	//...............Time bar...................
	RectangleShape timeBar;
	float timeBarStartWidth = 500;
	float timeBarHeight = 80;
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	Time gameTimeTotal;
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	//..........Draw Text on Display............
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
	FloatRect textBound; 

	// 6 Branches
	Texture branchTexture;
	branchTexture.loadFromFile("graphics/branch1.png");
	for (int i = 0; i < amountBranches; i++)
	{
		branches[i].setTexture(branchTexture);
		// Set the Sprite's origin to dead center
		// Wecan then spin it round without changing its position
		branches[i].setOrigin(220,20);
	}

	//..............Player.............
	Texture playerTexture;
	playerTexture.loadFromFile("graphics/dwarf.png");
	Sprite playerSprite;
	playerSprite.setTexture(playerTexture);
	playerSprite.setPosition(580,720);

	//................. player start on the left ..................
	side playerSide = side::LEFT;

	//.................. axe.............
	Texture axeTexture;
	axeTexture.loadFromFile("graphics/axe.png");
	Sprite axeSprite;
	axeSprite.setTexture(axeTexture);
	
	//............... Line the axe up with the tree ..................
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	//................ Log that be cut ....................
	Texture logTexture;
	logTexture.loadFromFile("graphics/log.png");
	Sprite logSprite;
	logSprite.setTexture(logTexture);
	//log variable
	bool logActive = false;
	float logSpeedX = 1000;
	float logSpeedY = -1500;

	

	// Sound
	SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	Sound chop;
	chop.setBuffer(chopBuffer);

	SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	Sound death;
	death.setBuffer(deathBuffer);

	SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	Sound outOfTime;
	outOfTime.setBuffer(ootBuffer);

	
	string playerName;
	Text nameText;
	nameText.setFont(font);
	const Vector2f nameTextPos(977, 850);
	nameText.setOrigin(Vector2f(nameText.getGlobalBounds().width, nameText.getGlobalBounds().height) / 2.f);
	nameText.setFillColor(Color::Black);
	nameText.setPosition(nameTextPos);
	nameText.setCharacterSize(60);


//++++++++++++ initialize menu_score ++++++++++++
	//.....BG.....
	Texture background3Texture;
	if (!background3Texture.loadFromFile("graphics/Background4.jpg"))
	{
		std::cout << "Load Failed";
	}
	// Sprite
	Sprite background3Sprite;
	background3Sprite.setTexture(background3Texture);
	background3Sprite.setPosition(0, 0);

	//....... score .....
	Text scoreBoardText[TOPSCORE];
	const Vector2f startPos(645, 300);
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreBoardText[i].setFont(font);
		scoreBoardText[i].setCharacterSize(38);
		scoreBoardText[i].setFillColor(Color::Black);
		scoreBoardText[i].setPosition(startPos + (Vector2f(0, 110) * (float)i));
	}


Game:
	
	sandwichSprite.setPosition(-90, 800);

	hamburgerSprite.setPosition(-68, 900);

	hotdogSprite.setPosition(-88, 1000);

	pizzaSprite.setPosition(-85, 1000);

	jamSprite1.setPosition(-250, 20); //position
	jamSprite2.setPosition(-250, 220);
	jamSprite3.setPosition(-250, 420);

	for (int i = 0; i < amountBranches; i++)
	{
		branches[i].setPosition(-2000, -2000);
	}

	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	textBound = messageText.getLocalBounds();
	messageText.setOrigin(textBound.left + textBound.width / 2.0f,
						  textBound.top + textBound.height / 2.0f);
	messageText.setPosition(1920/2.0f,1000/2.0f);
	scoreText.setPosition(20,20);

	logSprite.setPosition(810, 720);

	axeSprite.setPosition(700, 830);


	// ....... playname ........
	playerName = "";
	nameText.setString("_");
	

	while (window.isOpen())
	{
		/*
		*********************************************
				  Handle the players input
		*********************************************
		*/

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyReleased && !stopGame)
			{
				//Listen for key presses again
				acceptInput = true;
				//hide the axe
				axeSprite.setPosition(2000, axeSprite.getPosition().y);
			}
			if (stopGame)
			{
				if (event.type == Event::TextEntered)
				{
					switch (event.key.code)
					{
					case 8: // DELETE_KEY
						if (playerName.length() > 0)
							playerName.pop_back();
						break;
					default:
						playerName += (char)event.key.code;
						break;
					}
				}
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Start the game
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			playerName = "";
			nameText.setString("___");
			stopGame = false;

			//Reset Time & Score
			score = 0;
			timeRemaining = 5;

			//Make all the branches disappear
			for (int i = 1; i < amountBranches; i++)
			{
				branchPositions[i] = side::NONE;
			}


			//Move the player into position
			playerSprite.setPosition(580, 720);
			acceptInput = true;

		}

		//Wrap the player controls to
		//Make sure we are accepting input
		if (acceptInput)
		{
			// More code here next...
			// First handle pressing the right cursor key
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				// Make sure the player is on the right
				playerSide = side::RIGHT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				axeSprite.setPosition(AXE_POSITION_RIGHT,
					axeSprite.getPosition().y);



				playerSprite.setPosition(1200, 720);

				// update the branches
				updateBranches(score);

				// set the log that be cut
				logSprite.setPosition(810, 720);
				logSpeedX = -5000;
				logActive = true;


				acceptInput = false;

				// sound chop
				chop.play();

			}

			// Handle the left cursor key
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				// Make sure the player is on the left
				playerSide = side::LEFT;

				score++;

				// Add to the amount of time remaining
				timeRemaining += (2 / score) + .15;

				axeSprite.setPosition(AXE_POSITION_LEFT,
					axeSprite.getPosition().y);


				playerSprite.setPosition(580, 720);

				// update the branches
				updateBranches(score);

				// set the log that be cut
				logSprite.setPosition(810, 720);
				logSpeedX = 5000;
				logActive = true;


				acceptInput = false;

				// sound chop
				chop.play();

			}
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
			timeBar.setSize(Vector2f(timeBarWidthPerSecond* timeRemaining , 
										timeBarHeight));

			if (timeRemaining <= 0.0f)
			{
				//stop the game
				stopGame = true;

				//Change message to show player
				messageText.setString("TIME'S UP ! ! !");

				//Reposition the text based on its new size same the first before start game
				FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, 
										textRect.top + textRect.height / 2.0f);
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

				//sound the out of time
				outOfTime.play();
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

			//Update branch Sprites
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

			//Handle log that be cut
			if (logActive)
			{
				logSprite.setPosition(logSprite.getPosition().x + (logSpeedX * dt.asSeconds()),
					                  logSprite.getPosition().y + (logSpeedY * dt.asSeconds()));

				//Has the log reached the right hand edge?
				if (logSprite.getPosition().x < -100 ||
					logSprite.getPosition().x>2000)
				{
					//Set it up ready to be a whole new log next frame
					logActive = false;
					logSprite.setPosition(810, 720);
				}
			}

			//Has the player been squished by a branch?
			if (branchPositions[5] == playerSide)
			{
				//deadth
				stopGame = true;
				acceptInput = false;

				//hide the player 
				playerSprite.setPosition(3000, 1000);

				//change the text of the message
				messageText.setString("       OH NO ! !\n YOUR ATTACK ");

				//Center it on sth screen
				FloatRect textRect = messageText.getLocalBounds();

				messageText.setOrigin(textRect.left + textRect.width / 2.0f,
					textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1000 / 2.0f);

				//sound deadth
				death.play();
			}

		} //END of Function[if(!stopGame)]
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::F9))
			{
				saveScoreFile(playerName, score);
				goto menu_score;
			}
			else if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				window.close();
			}
			nameText.setString(playerName + "_");
			nameText.setOrigin(Vector2f(nameText.getGlobalBounds().width, nameText.getGlobalBounds().height) / 2.f);
			nameText.setPosition(nameTextPos);
	
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
		//Draw Branches
		for (int i = 0; i < amountBranches; i++)
		{
			window.draw(branches[i]);
		}
		//Draw Tree
		window.draw(treeSprite);
		//Draw the player
		window.draw(playerSprite);
		//Draw the axe
		window.draw(axeSprite);
		//Draw the log that be cut
		window.draw(logSprite);
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
			window.draw(nameText);
			////Draw the RIPStone
			//window.draw(RIPSprite);
		}


		// Show everything I just draw
		window.display();

	}

menu_score:

	readScoreFile();
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreBoardText[i].setString(to_string(i + 1) + ". " +scoreData[i].name +"					"+ to_string(scoreData[i].score) + " p ");
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == Keyboard::G)
				{
					goto Game;
				}
			}
		}

		window.clear();

		window.draw(background3Sprite);
		for (int i = 0; i < TOPSCORE; i++)
		{
			window.draw(scoreBoardText[i]);
		}
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

void sortScore()
{
	for (int i = 0; i < TOPSCORE; i++)
	{
		for (int j = i + 1; j < TOPSCORE + 1; j++)
		{
			if (scoreData[j].score > scoreData[i].score)
			{
				ScoreData temp = scoreData[i];
				scoreData[i] = scoreData[j];
				scoreData[j] = temp;
			}
		}
	}
}

void readScoreFile()
{
	fstream scoreFile;
	scoreFile.open(FILENAME, ios::app | ios::in);
	for (int i = 0; i < TOPSCORE; i++)
	{
		string tempname;
		string tempscore;
		if (!getline(scoreFile, tempname))
			return;
		if (!getline(scoreFile, tempscore))
			return;
		scoreData[i].name = tempname;
		scoreData[i].score = stoi(tempscore);
	}
	scoreFile.close();
	sortScore();
}

void saveScoreFile(string name, int score)
{
	scoreData[TOPSCORE].name = name;
	scoreData[TOPSCORE].score = score;
	sortScore();
	fstream scoreFile;
	scoreFile.open(FILENAME, ios::out | ios::in);
	for (int i = 0; i < TOPSCORE; i++)
	{
		scoreFile << scoreData[i].name << endl << scoreData[i].score << endl;
	}
	scoreFile.close();
}
