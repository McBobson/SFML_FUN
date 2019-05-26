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

void VsAI(sf::SoundBuffer,Ekran&);

int main()
{

	bool menu = false;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	Ekran E;
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	int wybor = 0;

	////////////////////////// KOMENTARZE NA PROPSIE OBIEKTOWOSC FFF CHUJ ////////////////////////////////////

	/*
	//Arena2 E;
	Ekran E;
	Arena A;
	AI AI;
	int x, y, gracz=1,xk,yk,xp,yp;
	int pom[2];
	//cout << A << endl;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	bool menu = false;

	//sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
	//sf::RenderWindow MenuGlowne(sf::VideoMode(800, 800, 32), "Menu_Warcby");
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();*/

	//////////////// LADOWANIE SOUNDTRACKU ////////////////////////////////////

	sf::SoundBuffer BuforM,BuforB,BuforB2;
	if (!BuforM.loadFromFile("Menu.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}

	if (!BuforB.loadFromFile("Battle.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}

	if (!BuforB2.loadFromFile("Battle2.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}
	 // Menu GLowne // 
	if (menu == false)
	{
		int xpom, ypom;

		sf::Sound soundm;
		soundm.setBuffer(BuforM);
		soundm.setVolume(3);
		soundm.play();

		sf::RenderWindow MenuGlowne(sf::VideoMode(800, 800, 32), "Menu_Warcby");
		while (MenuGlowne.isOpen())
		{
			sf::Event zdarzenieM;
			while (MenuGlowne.pollEvent(zdarzenieM))
			{
				if (zdarzenieM.type == sf::Event::Closed)
					MenuGlowne.close();

				if (zdarzenieM.type == sf::Event::KeyPressed && zdarzenieM.key.code == sf::Keyboard::Escape)
					MenuGlowne.close();

				if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
					MenuGlowne.close();

				if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Left)
				{

					xpom = zdarzenieM.mouseButton.x;
					ypom = zdarzenieM.mouseButton.y;

					cout << zdarzenieM.mouseButton.x << endl;
					cout << zdarzenieM.mouseButton.y<<endl;
					Czy_Lewy = true;

				}

				if (Czy_Lewy == true)
				{
					if (xpom < 716 && xpom>468 && ypom < 146 && ypom>40)
					{
						wybor = 1;
						cout << "Bitka na chuje" << endl;
						menu = true;
						soundm.stop();
						MenuGlowne.close();
					}
					if (xpom < 727 && xpom>458 && ypom < 357 && ypom>225)
					{
						wybor = 2;
						cout << "Bitka" << endl;
						menu = true;
						soundm.stop();
						MenuGlowne.close();
					}
					if (xpom < 728 && xpom>432 && ypom < 721 && ypom>582)
					{
						soundm.stop();
						MenuGlowne.close();
					}
					//menu = true;
					//soundm.stop();
					//MenuGlowne.close();
				}
			}

			MenuGlowne.draw(E.Menu);
			MenuGlowne.display();
		}
	}

	// Bitka // 
	if (menu == true)
	{
		/*
		sf::Sound sound;
		sound.setBuffer(BuforB);
		sound.setVolume(3);
		sound.play();
		sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
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
					}


				}

				if (Czy_Lewy == true && Czy_Prawy == true)
				{
					wysw = false;
					bicie = 0;
					xp = xk;
					yp = (int)yk - 65;
					//A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E);
					Czy_Lewy = false;
					Czy_Prawy = false;

					pom[1] = ((int)yk - 65) - ((int)y - 65);
					pom[0] = xk - x;

					int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);

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
					A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz, E);
					//cout << AI.TabKoniec[0] << " " << AI.TabKoniec[1] << " " << AI.TabKoniec[2] << " " << AI.TabKoniec[3]<<endl;
					//system("pause");
					gracz--;
					
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
					} //potrzebne do wielokrotnego bicia

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


			oknoAplikacji.display();


		}*/

		if (wybor == 1)
		{
			sf::Sound soundB2;
			soundB2.setBuffer(BuforB2);
			soundB2.setVolume(3);
			soundB2.play();
			soundB2.setLoop(true);

			sf::RenderWindow Menu(sf::VideoMode(800, 800, 32), "Menu");

			while (Menu.isOpen())
			{
				sf::Event zdarzenieM;
				while (Menu.pollEvent(zdarzenieM))
				{
					if (zdarzenieM.type == sf::Event::Closed)
						Menu.close();

					if (zdarzenieM.type == sf::Event::KeyPressed && zdarzenieM.key.code == sf::Keyboard::Escape)
						Menu.close();

					if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
						Menu.close();

				}
			}
		}

		else if (wybor == 2)
		{
			VsAI(BuforB, E);
		}
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

void VsAI(sf::SoundBuffer BuforB,Ekran& E)
{
	//Arena2 E;
	//Ekran E;
	Arena A;
	AI AI;
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	//cout << A << endl;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	bool menu = false;


	//E.Tworz_Plansze();
	//E.Ulozenie_Pionkow();

	sf::Sound sound;
	sound.setBuffer(BuforB);
	sound.setVolume(3);
	sound.play();
	sound.setLoop(true);
	sf::RenderWindow oknoAplikacji(sf::VideoMode(800, 800, 32), "Warcaby");
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
				yp = (int)yk - 65;
				//A.Przesun_Pionek((int)x - 65, y, (int)xk - 65, yk, gracz, E);
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);

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
				A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz, E);
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


		oknoAplikacji.display();



	}

}