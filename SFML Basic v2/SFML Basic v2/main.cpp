#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Wyswietlanie.h"
#include "Arena_SFML.h"
#include "Nag³ówek.h"

using namespace std;

char ZwrocX(int);

int ZwrocY(int);

int main()
{
	//Arena2 E;
	Ekran E;
	Arena A;
	int x, y, gracz=2,xk,yk,xp,yp;
	int pom[2];
	//cout << A << endl;
	bool Czy_Lewy = false, Czy_Prawy = false;
	int bicie = 0;

	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	/*
	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			cout << A.znaki[i][j] << " ";
		}
		cout << endl;
	}*/

	while (oknoAplikacji.isOpen())
	{
		//cout << "TURA GRACZA " << gracz << endl;
		//system("cls");
		sf::Event zdarzenie;

		while (oknoAplikacji.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == sf::Event::Closed)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Middle)
				oknoAplikacji.close();

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)
			{
				//cout << zdarzenie.mouseButton.x << endl;
				//cout << zdarzenie.mouseButton.y << endl;
				cout << ZwrocX(zdarzenie.mouseButton.x) << " "<<ZwrocY(zdarzenie.mouseButton.y)<<endl;
				x = ZwrocX(zdarzenie.mouseButton.x);
				y = ZwrocY(zdarzenie.mouseButton.y);
				Czy_Lewy = true;

			}

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				//cout << zdarzenie.mouseButton.x << endl;
				//cout << zdarzenie.mouseButton.y << endl;
				cout << ZwrocX(zdarzenie.mouseButton.x) << " " << ZwrocY(zdarzenie.mouseButton.y) << endl;
				xk = ZwrocX(zdarzenie.mouseButton.x);
				yk = ZwrocY(zdarzenie.mouseButton.y);

				Czy_Prawy = true;

				//A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E);
				//system("pause");
				//system("cls");
				//cout << A << endl;
				//cout << endl;

				/*
				for (int i = 0; i < ROZ; i++)
				{
					for (int j = 0; j < ROZ; j++)
					{
						cout << A.znaki[i][j] << " ";
					}
					cout << endl;
				}*/


			}

			if (Czy_Lewy == true && Czy_Prawy == true)
			{
				bicie = 0;
				xp = (int)xk - 65;
				yp = yk;
				//A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E);
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[0] = ((int)xk - 65) - ((int)x - 65);
				pom[1] = yk - y;

				if (A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E) == 1)
				{
					bicie++;
					switch (A.Kierunek_Bicia(pom))
					{
					case 0:
					{
						pom[0] = ((int)xk - 65) - ((int)x - 65) - 1;
						pom[1] = yk - y - 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 1:
					{
						pom[0] = ((int)xk - 65) - ((int)x - 65) + 1;
						pom[1] = yk - y - 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 2:
					{
						pom[0] = ((int)xk - 65) - ((int)x - 65) - 1;
						pom[1] = yk - y + 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 3:
					{
						pom[0] = ((int)xk - 65) - ((int)x - 65) + 1;
						pom[1] = yk - y + 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;
					}

					xp = ((int)x - 65) + pom[0];
					yp = y + pom[1];
					cout << xp << " " << yp << endl;
					//punkty1++;
				}

				//cout << "kek";

				//cout << xp << " " << yp << endl;
				
			if (bicie==0)
			{
				cout << "TET";
				if (gracz == 1) gracz++;
				else gracz--;
			}
			else if (!A.Czy_Mozliwe_Bicie(yp, xp))
			{
				cout << "LASAGNA" << endl;
				if (gracz == 1) gracz++;
				else gracz--;
			}
		}
	}
		
			//oknoAplikacji.clear(sf::Color(255, 155, 50));
			oknoAplikacji.draw(E.Sprite);
			oknoAplikacji.draw(E.P1);
			oknoAplikacji.draw(E.P2);
			oknoAplikacji.draw(E.P3);
			oknoAplikacji.draw(E.P4);
			oknoAplikacji.draw(E.P5);
			oknoAplikacji.draw(E.P6);
			oknoAplikacji.draw(E.P7);
			oknoAplikacji.draw(E.P8);
			oknoAplikacji.draw(E.P9);
			oknoAplikacji.draw(E.P10);
			oknoAplikacji.draw(E.P11);
			oknoAplikacji.draw(E.P12);

			oknoAplikacji.draw(E.Pc1);
			oknoAplikacji.draw(E.Pc2);
			oknoAplikacji.draw(E.Pc3);
			oknoAplikacji.draw(E.Pc4);
			oknoAplikacji.draw(E.Pc5);
			oknoAplikacji.draw(E.Pc6);
			oknoAplikacji.draw(E.Pc7);
			oknoAplikacji.draw(E.Pc8);
			oknoAplikacji.draw(E.Pc9);
			oknoAplikacji.draw(E.Pc10);
			oknoAplikacji.draw(E.Pc11);
			oknoAplikacji.draw(E.Pc12);
		
		// TUTAJ BEDZIE IMBA


		oknoAplikacji.display();

		
	}

	

	return 0;
	
}

char ZwrocX(int x)
{
	if (x > 90 && x < 168)	return 'A';

	else if (x > 168 && x < 245) return 'B';

	else if (x > 245 && x < 325) return 'C';

	else if (x > 325 && x < 400) return 'D';

	else if (x > 400 && x < 477) return 'E';
	 
	else if (x > 477 && x < 555) return 'F';

	else if (x > 555 && x < 633) return 'G';

	else if (x > 633 && x < 710) return 'H';
	
}

int ZwrocY(int y)
{
	if (y > 90 && y < 168)	return 0;

	else if (y > 168 && y < 245) return 1;

	else if (y > 245 && y < 325) return 2;

	else if (y > 325 && y < 400) return 3;

	else if (y > 400 && y < 477) return 4;

	else if (y > 477 && y < 555) return 5;

	else if (y > 555 && y < 633) return 6;

	else if (y > 633 && y < 710) return 7;
}