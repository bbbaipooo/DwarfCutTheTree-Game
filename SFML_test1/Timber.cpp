//important libraries in C++
#include"stdafx.h"//" " is for file included with Visual Studio
#include<SFML/Graphics.hpp>//include SFML graphics from the folder

//using namespace for make code easier
using namespace sf;

int main()
{
	// create video mode
	VideoMode size(1920, 1080);

	// create & show a window for the game
	RenderWindow window(size, "DwarfCutTheTree!!!", Style::Fullscreen);

	return 0;
}
