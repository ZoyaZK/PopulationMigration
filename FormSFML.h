#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace form {
	Font None;				// ����� ��������� �������������

	class Label {
	public:
		string text;	//�����
	protected:
		double x;		//���������� x
		double y;		//���������� y

		Text TXT;		//������������ �����

	public:
		Label(double _x = 0, double _y = 0, string _text = "text")
		{
			None.loadFromFile("None.ttf");			//�������� ������ ������ ���� ������

			x = _x;
			y = _y;
			text = _text;								// ��������� �����
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
			TXT.setFillColor(Color::White);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������
		}
		Text displayText()
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			return TXT;
		}
	};

	class Button : public Label {
	protected:
		double width;		// ������ ������
		double height;		// ������ ������
		RectangleShape BOX;	// ������� ������������� � �������� width, height
	public:
		Button(double _x = 0, double _y = 0, string _text = "button", double _width = 150, double _height = 30)
		{
			None.loadFromFile("None.ttf");			//�������� ������ ������ ���� ������

			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								// ��������� �����
			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
			TXT.setFillColor(Color::White);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������

			BOX.setSize(Vector2f(width, height));		// ������ ������
			BOX.setPosition(x, y);						// ���������� ������
			BOX.setFillColor(sf::Color(133, 133, 133));	// ���� ������
			BOX.setOutlineThickness(2);					// ������ X ��������
			BOX.setOutlineColor(Color(66, 66, 66));		// ���� �������
		}
		//�������� ������� �� ������
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) {
				return  true;
			}
			else {
				return false;
			}
		}
		//����� ������
		Text displayText()
		{
			TXT.setString(text);  // ��������� � ��������� ����� ����������� �����
			return TXT;
		}
		//����� ������
		RectangleShape displayButton()
		{
			return BOX;
		}


	};

	class Input : public Button {
	protected:
		bool focus;
	public:
		Input(double _x = 0, double _y = 0, double _width = 150, double _height = 30, string _text = "")
		{
			x = _x;
			y = _y;
			width = _width;
			height = _height;
			text = _text;								// ��������� �����
			focus = false;								// ����� ���� �����

			TXT.setFont(None);							// ��������� �����
			TXT.setCharacterSize(20); 					// � ��������, � �� ������!
			TXT.setFillColor(Color::Black);					// ������������� ���� ���������� ������
			TXT.setPosition(x, y);						// ������� ������

			BOX.setSize(Vector2f(width, height));		// ������ ���� �����
			BOX.setPosition(x, y);						// ���������� ���� �����
			BOX.setFillColor(Color::White);	// ���� ������
		}
		//����� .reText( char ) �������� ����� ������ ������ ���� ������ Input
		void reText(char _tmp)
		{
			text.erase(text.size() - 1);

			if (_tmp != 8) {
				text += _tmp;
			}
			else {
				if (text.size() > 0) {
					text.erase(text.size() - 1);
				}

			}
			text += "|";
			TXT.setString(text);
		}

		// �������� ������ Input
		bool select()
		{
			return focus;
		}

		// ��������� ������ Input
		bool select(Vector2i _mouse)
		{
			if ((_mouse.x > x && _mouse.x < x + width) && (_mouse.y > y && _mouse.y < y + height)) { 	//���� ����� ������ ��� �������� Input...
				focus = true;																	   	// ����� true
				text += "|";																		// � ����� ������ �������� | (��� �� �������� ��� input � ������)
			}
			else {																				//...����� ���� ������� ��������� �� ��� ��������, ��...
				if (text.size() > 0) {																// �������� ���������� �������(����� ��������)
					if (text[text.size() - 1] == 124) {													// ���� ������ | ...
						text.erase(text.size() - 1);														// ... �� ������� ���
					}
				}
				focus = false;																		// ������������� ����� false
			}
			return focus;
		}

		//����� ������
		Text displayText()
		{
			TXT.setString(text);						// ��������� � ��������� ����� ����������� �����
			return TXT;
		}

		//����� ���� Input
		RectangleShape displayBOX()
		{
			return BOX;
		}

		//��� ����, ��� �� ������� ����� � ���� Ipnut ���������� ���������  readText() ������� ���������� string
		string readText()
		{
			if (text[text.size() - 1] == 124) { 	// ������� (���� ����) ������ |
				text.erase(text.size() - 1);
			}
			return text;
		}
	};

	//����� ������
	class Graph {
		//���������� ������ ���������
	protected:
		int x0;
		int y0;

	public:
		Graph(int x0_, int y0_)
		{
			x0 = x0_;
			y0 = y0_;
		}
		template <typename Type_>
		double* normData(Type_* y_mass) {
			double* norm_y_mass = new double[_msize(y_mass) / sizeof(y_mass[0])];
			Type_ min = y_mass[0];
			Type_ max = y_mass[0];
			for (int i = 0; i < _msize(y_mass) / sizeof(y_mass[0]); i++)
			{
				if (y_mass[i] < min) min = y_mass[i];
				if (y_mass[i] > max) max = y_mass[i];
			}
			for (int i = 0; i < _msize(y_mass) / sizeof(y_mass[0]); i++)
			{
				double g1 = (double)(y_mass[i] - min) / (max - min);
				double g2 = g1 * (y0 - 40);
				double g3 = 40 + g2;
				norm_y_mass[i] = g3;
			}
			return norm_y_mass;
		}
		template <typename Type2>
		double* coorData(Type2* y_mass) {
			double* norm_y_mass = new double[_msize(y_mass) / sizeof(y_mass[0])];
			Type2 min = y_mass[0];
			Type2 max = y_mass[0];
			for (int i = 0; i < _msize(y_mass) / sizeof(y_mass[0]); i++)
			{
				if (y_mass[i] < min) min = y_mass[i];
				if (y_mass[i] > max) max = y_mass[i];
			}
			double len = _msize(y_mass) / sizeof(y_mass[0]);
			double h = (max - min) / len;
			for (int i = 0; i < _msize(y_mass) / sizeof(y_mass[0]); i++)
			{
				norm_y_mass[i] = min + h * i;
			}
			return norm_y_mass;
		}
		//������ ������
		void displayPlot(double* y_mass) {
			int x_mass[] = { 2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020,2021,2022,2023 };
			None.loadFromFile("None.ttf");
			//������� ��� ����
			char psz[32];
			RenderWindow window2(VideoMode(x0, y0), "Graph");
			Text coordinate_x;
			coordinate_x.setFont(None);
			coordinate_x.setCharacterSize(12);
			coordinate_x.setFillColor(Color::Black);

			Text coordinate_y = coordinate_x;

			VertexArray vertex_x(Lines, 2);//oc� �
			vertex_x[0].position = Vector2f(0, y0 - 20);
			vertex_x[1].position = Vector2f(x0, y0 - 20);

			vertex_x[0].color = Color::Black;
			vertex_x[1].color = Color::Black;

			VertexArray vertex_y(Lines, 2);//oc� y
			vertex_y[0].position = Vector2f(30, y0);
			vertex_y[1].position = Vector2f(30, 0);

			vertex_y[0].color = Color::Black;
			vertex_y[1].color = Color::Black;

			VertexArray data(LineStrip, 16);


			double* norm_y_mass = normData(y_mass);
			double* coor_y_mass_population = coorData(y_mass);
			//������ ������ �� ������
			CircleShape point(5.f);
			int sc = x0 / 17;// _msize(y_mass) / sizeof(y_mass[0]);
			point.setFillColor(Color::Blue);
			double h = (y0 - 20) / 16;
			while (window2.isOpen())
			{
				Event event;
				while (window2.pollEvent(event))
					if (event.type == Event::Closed)
						window2.close();

				window2.clear(Color::White);
				for (int i = 0; i < 16; i++) {
					point.setPosition((i + 1) * sc, y0 - norm_y_mass[i]);
					data[i].position = Vector2f((i + 1) * sc + 5, y0 - norm_y_mass[i] + 5);
					data[i].color = Color::Blue;

					coordinate_x.setString(to_string(x_mass[i]));
					coordinate_x.setPosition((i + 1) * sc - 5, y0 - 20);


					sprintf_s(psz, "%.1f", coor_y_mass_population[i]);
					coordinate_y.setString(psz);
					coordinate_y.setPosition(3, y0 - h * i - 40);


					window2.draw(point);
					window2.draw(coordinate_x);
					window2.draw(coordinate_y);
				}
				window2.draw(vertex_x);
				window2.draw(vertex_y);
				window2.draw(data);
				window2.display();
			}

		}

		void displayPlot(int** y_mass) {
			int x_mass[] = { 2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020,2021,2022,2023 };
			None.loadFromFile("None.ttf");
			//������� ��� ����
			char psz[32];
			RenderWindow window2(VideoMode(x0, y0), "Graph");
			Text coordinate_x;
			coordinate_x.setFont(None);
			coordinate_x.setCharacterSize(12);
			coordinate_x.setFillColor(Color::Black);

			Text coordinate_y = coordinate_x;

			Text legend_im;
			legend_im.setFont(None);
			legend_im.setCharacterSize(16);
			legend_im.setFillColor(Color::Blue);
			legend_im.setString("immigration");

			Text legend_em;
			legend_em.setFont(None);
			legend_em.setCharacterSize(16);
			legend_em.setFillColor(Color::Green);
			legend_em.setString("emmigration");

			legend_im.setPosition(x0 - 90, y0 - 60);
			legend_em.setPosition(x0 - 90, y0 - 44);

			VertexArray vertex_x(Lines, 2);//oc� �
			vertex_x[0].position = Vector2f(0, y0 - 20);
			vertex_x[1].position = Vector2f(x0, y0 - 20);

			vertex_x[0].color = Color::Black;
			vertex_x[1].color = Color::Black;

			VertexArray vertex_y(Lines, 2);//oc� �
			vertex_y[0].position = Vector2f(30, y0);
			vertex_y[1].position = Vector2f(30, 0);

			vertex_y[0].color = Color::Black;
			vertex_y[1].color = Color::Black;

			VertexArray dataim(LineStrip, 16);
			VertexArray dataem(LineStrip, 16);

			double* norm_y_mass_immigration = normData(y_mass[0]);
			double* norm_y_mass_emmigration = normData(y_mass[1]);

			double* coor_y_mass_emmigration = coorData(y_mass[1]);
			//������ ����������� ������ �� ������
			CircleShape point_im(5.f);
			point_im.setFillColor(Color::Blue);

			//������ ����������� ������ �� ������
			CircleShape point_em(5.f);
			point_em.setFillColor(Color::Green);
			int sc = x0 / 17;// _msize(y_mass) / sizeof(y_mass[0]);
			//int len = _msize(y_mass) / sizeof(y_mass[0][0]);
			double h = (y0 - 20) / 16;
			while (window2.isOpen())
			{
				Event event;
				while (window2.pollEvent(event))
					if (event.type == Event::Closed)
						window2.close();

				window2.clear(Color::White);
				for (int i = 0; i < 16; i++) {
					point_im.setPosition((i + 1) * sc + 5, y0 - norm_y_mass_immigration[i]);
					dataim[i].position = Vector2f((i + 1) * sc + 5, y0 - norm_y_mass_immigration[i] + 5);
					dataim[i].color = Color::Blue;

					point_em.setPosition((i + 1) * sc + 5, y0 - norm_y_mass_emmigration[i]);
					dataem[i].position = Vector2f((i + 1) * sc + 5, y0 - norm_y_mass_emmigration[i] + 5);
					dataem[i].color = Color::Green;


					window2.draw(point_im);
					window2.draw(point_em);

					coordinate_x.setString(to_string(x_mass[i]));
					coordinate_x.setPosition((i + 1) * sc, y0 - 20);
					window2.draw(coordinate_x);

					sprintf_s(psz, "%1.2f", coor_y_mass_emmigration[i] / 1000000.0);
					coordinate_y.setString(psz);
					coordinate_y.setPosition(3, y0 - h * i - 40);
					window2.draw(coordinate_y);
				}
				window2.draw(legend_im);
				window2.draw(legend_em);
				window2.draw(vertex_x);
				window2.draw(vertex_y);

				window2.draw(dataim);
				window2.draw(dataem);

				window2.display();
			}

		}
		//RectangleShape displayPlot() {
		//	return BOX;
		//}

	};

} /* namespace form */