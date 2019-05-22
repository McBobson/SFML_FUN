#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Wyswietlanie.h"
#include "Arena_SFML.h"
#include "Nag³ówek.h"
#include "AI.h"

using namespace std;

int ZwrocX(int);

char ZwrocY(int);

int main()
{
	//Arena2 E;
	Ekran E;
	Arena A;
	AI AI;
	int x, y, gracz=1,xk,yk,xp,yp;
	int pom[2];
	//cout << A << endl;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
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
		if (wysw == false)
		{
			system("cls");
			cout << "TURA GRACZA " << gracz << endl;
			wysw = true;
		}
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
				//cout << ZwrocX(zdarzenie.mouseButton.x) << " "<<ZwrocY(zdarzenie.mouseButton.y)<<endl;
				x = ZwrocX(zdarzenie.mouseButton.y);
				y = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Lewy = true;

			}

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				//cout << zdarzenie.mouseButton.x << endl;
				//cout << zdarzenie.mouseButton.y << endl;
				//cout << ZwrocX(zdarzenie.mouseButton.x) << " " << ZwrocY(zdarzenie.mouseButton.y) << endl;
				xk = ZwrocX(zdarzenie.mouseButton.y);
				yk = ZwrocY(zdarzenie.mouseButton.x);

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
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk-65;
				//A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E);
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				int wynik = A.Przesun_Pionek(x, (int)y-65, xk, (int)yk-65, gracz, E);

				if (wynik == 1)
				{
					bicie++;
					switch (A.Kierunek_Bicia(pom))
					{
					case 0:
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x - 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 1:
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x - 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 2:
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) - 1;
						pom[0] = xk - x + 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;

					case 3:
					{
						pom[1] = ((int)yk - 65) - ((int)y - 65) + 1;
						pom[0] = xk - x + 1;
						//cout<<pom[0]<<" "<<pom[1]<<endl;
					}
					break;
					}

					yp = ((int)y - 65) + pom[1];
					xp = x + pom[0];
					//cout << xp << " " << yp << endl;
					//punkty1++;
				}

				gracz++;
				AI.Koncowy_Ruch(A);
				A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz,E);
				//cout << AI.TabKoniec[0] << " " << AI.TabKoniec[1] << " " << AI.TabKoniec[2] << " " << AI.TabKoniec[3]<<endl;
				//system("pause");
				gracz--;
			/*
			if (bicie==0 && wynik != -1) // Ruch zwyk³y bez bicia
			{
				cout << "TET";
				if (gracz == 1) gracz++;
				else gracz--;
			}
			else if ((!A.Czy_Mozliwe_Bicie(yp, xp) || !A.Czy_Mozliwe_Bicie_Damka(yp, xp)) && wynik!=-1) // Czy mozliwe jest dalsze bicie
			{
				cout << "LASAGNA" << endl;
				if (gracz == 1) gracz++;
				else gracz--;
			}*/ //potrzebne do wielokrotnego bicia

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

char ZwrocY(int y)
{
	if (y > 90 && y < 168)	return 'A';

	else if (y > 168 && y < 245) return 'B';

	else if (y > 245 && y < 325) return 'C';

	else if (y > 325 && y < 400) return 'D';

	else if (y > 400 && y < 477) return 'E';
	 
	else if (y > 477 && y < 555) return 'F';

	else if (y > 555 && y < 633) return 'G';

	else if (y > 633 && y < 710) return 'H';
	
}

int ZwrocX(int x)
{
	if (x > 90 && x < 168)	return 0;

	else if (x > 168 && x < 245) return 1;

	else if (x > 245 && x < 325) return 2;

	else if (x > 325 && x < 400) return 3;

	else if (x > 400 && x < 477) return 4;

	else if (x > 477 && x < 555) return 5;

	else if (x > 555 && x < 633) return 6;

	else if (x > 633 && x < 710) return 7;
}