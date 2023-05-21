#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "FormSFML.h"
#include "Population.h"
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
	Population population(16);
	Graph graph(600, 500);
	Graph graph2(300, 200);
	Graph graph3(200, 300);

	
    while (window.isOpen())
    {
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					Vector2i mouse = Mouse::getPosition(window); // Считываем координаты мыши(если че обратиться можно будет mouse.x mouse.y)

					if (button.select(mouse)) { 
							if (input.text == "population|") {//создаем популяцию
								population.readData("population.txt");
								graph.displayPlot(population.getValue());
								label.text = label.text + '\n' + population.sgetValue();
								label2.text = label2.text +'\n'+to_string(population.calculateGrowth());//нужно чтобы все данные выводил
							}
							else if (input.text == "migration|") {//создаем миграцию	
								label2.text = "In progress";//
							}
							else 
								label2.text = "Wrong file";
					}//если кнопка нажата нужно выбрать файл
					input.select(mouse);			//поле ввода
				}
			}
			if (event.type == sf::Event::TextEntered) {
				if (input.select()) {
					input.reText(event.text.unicode);
				}

			}
			
		}
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

    return 0;
}