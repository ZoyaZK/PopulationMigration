#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "FormSFML.h"
using namespace std;
using namespace form;
using namespace sf;
int main()
{
    RenderWindow window(VideoMode(600, 600), "Statistica!");
	
	Button button(240, 30, "Load file");
	Label label(30, 80, "Data:");
	Input input(30, 30, 200, 30);
	Label label2(250, 80, "Answer:");
	Graph graph(600, 500);
	Graph graph2(300, 200);
	Graph graph3(200, 300);

	
		window.clear(sf::Color(0, 0, 0));

		window.draw(label.displayText());
		window.draw(label2.displayText());
		
		window.draw(button.displayButton());
		window.draw(button.displayText());

		window.draw(input.displayButton());
		window.draw(input.displayText());

		window.display();
		//sleep(milliseconds(1000 / 60));//Задержка
    }

 