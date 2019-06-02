#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <Windows.h>
#include "Wyswietlanie.h"
#include "Arena_SFML.h"
#include "Nag³ówek.h"
#include "AI.h"

using namespace std;

int ZwrocX(int);

char ZwrocY(int);

void VsAI(sf::SoundBuffer,Ekran&,bool&,bool&);

void PVP(sf::SoundBuffer, Ekran&,bool&,bool&);

void Wygrana(Ekran&,bool&,bool&);

void PrzegranaSI(Ekran&,bool&,bool&);

void Przegrana(Ekran&, bool&, bool&);


int main()
{

	bool menu = false;
	bool wygrana = false, przegrana = false;
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;
	bool Gra = true;
	Ekran E;
	E.Tworz_Plansze();
	E.Ulozenie_Pionkow();

	int wybor = 0;
	
	cout << "WSZYSTKIE GRAFIKI ORAZ UTWORY MUZYCZNE ZOSTAlY UZYTE NIE W CELACH KOMERCYJNYCH TYLKO DO UZYTKU PRYWATNEGO" << endl;
	cout << "SA ONE ASPEKTEM HUMORYSTYCZNYM ORAZ UROZMAICAJA SZATE AUDIOWIZUALNA PROGRAMU" << endl;
	Sleep(5000);

	system("cls");
	cout << "LOADING:__________";

	//////////////// LADOWANIE SOUNDTRACKU ////////////////////////////////////

	sf::SoundBuffer BuforM,BuforB,BuforB2;

	/*
	if (!BuforM.loadFromFile("Menu.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}

	system("cls");
	cout << "LOADING:[][]_______";

	if (!BuforB.loadFromFile("Battle.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}
	system("cls");
	cout << "LOADING:[][][][][]____";

	if (!BuforB2.loadFromFile("Battle2.wav"))
	{
		cout << "Nie mozna odtworzyc sciezki dzwiekowej" << endl;
	}

	system("cls");
	cout << "LOADING:[][][][][][][][]";
	Sleep(1000);
	system("cls");
	cout << "Milej gry :)" << endl;
	*/

	while (Gra)
	{
		// Menu GLowne // 
		if (menu == false)
		{
			int xpom=0, ypom=0;

			sf::Sound soundm;
			soundm.setBuffer(BuforM);
			soundm.setVolume(15);
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
					{
						MenuGlowne.close();
						Gra = false;
					}

					if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
					{
						MenuGlowne.close();
						Gra = false;
					}

					if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Left)
					{

						xpom = zdarzenieM.mouseButton.x;
						ypom = zdarzenieM.mouseButton.y;

						//cout << zdarzenieM.mouseButton.x << endl;
						//cout << zdarzenieM.mouseButton.y << endl;
						Czy_Lewy = true;

					}

					if (Czy_Lewy == true)
					{
						Czy_Lewy = false;
						if (xpom < 716 && xpom>468 && ypom < 146 && ypom>40)
						{
							wybor = 1;
							menu = true;
							soundm.stop();
							MenuGlowne.close();
						}
						if (xpom < 727 && xpom>458 && ypom < 357 && ypom>225)
						{
							wybor = 2;
							menu = true;
							soundm.stop();
							MenuGlowne.close();
						}
						if (xpom < 728 && xpom>432 && ypom < 721 && ypom>582)
						{
							soundm.stop();
							MenuGlowne.close();
							Gra=false;
						}
						
					}
				}

				MenuGlowne.draw(E.Menu);
				MenuGlowne.display();
			}
		}

		// Bitka // 
		if (menu == true)
		{

			if (wybor == 1)
			{
				E.Tworz_Plansze();
				E.Ulozenie_Pionkow();
				PVP(BuforB2, E,wygrana,przegrana);

				if (wygrana)
				{
					Wygrana(E, menu, Gra);
					wygrana = false;
				}
				else if (przegrana)
				{
					Przegrana(E, menu, Gra);
					przegrana = false;
				}
			}

			else if (wybor == 2)
			{
				E.Tworz_Plansze();
				E.Ulozenie_Pionkow();
				VsAI(BuforB, E, wygrana, przegrana);

				if (wygrana)
				{
					Wygrana(E, menu, Gra);
					wygrana = false;
				}
				else if (przegrana)
				{
					PrzegranaSI(E, menu, Gra);
					przegrana = false;
				}
			}

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

void VsAI(sf::SoundBuffer BuforB,Ekran& E,bool& wygrana,bool& przegrana)
{
	Arena A;
	AI AI;
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	bool menu = false;
	int punkty=0;


	sf::Sound sound;
	sound.setBuffer(BuforB);
	sound.setVolume(5);
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
				x = ZwrocX(zdarzenie.mouseButton.y);
				y = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Lewy = true;

			}

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				xk = ZwrocX(zdarzenie.mouseButton.y);
				yk = ZwrocY(zdarzenie.mouseButton.x);

				Czy_Prawy = true;


			}

			if (Czy_Lewy == true && Czy_Prawy == true)
			{
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				
				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);
				
				if (wynik == 1)
				{
					bicie++;
					punkty++;
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
				}

				if (bicie == 0 || (bicie > 0 && !A.Czy_Mozliwe_Bicie(xp, yp)))
				{
					if (wynik == -1) break;

					if (punkty == 12)
					{
						sound.stop();
						wygrana = true;
						oknoAplikacji.close();
						break;
					}

					gracz++;

					int zbity = 0;
					int Wektor_Przesuneicia[2]; // Wielokrotne bicie
					int ratunek[2] = { 0,0 };
					do
					{
						int punktypoprz = AI.Zwroc_Punkty();

						AI.Koncowy_Ruch(A);
						A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz, E);

						if (AI.Zwroc_Punkty() - punktypoprz == 1)
							zbity++;
						else break;

						Wektor_Przesuneicia[0] = AI.TabKoniec[2] - AI.TabKoniec[0];
						Wektor_Przesuneicia[1] = AI.TabKoniec[3] - AI.TabKoniec[1];

						if (Wektor_Przesuneicia[0] < 0 && Wektor_Przesuneicia[1] < 0)
						{
							ratunek[0] = -1;
							ratunek[1] = -1;
						}
						else if (Wektor_Przesuneicia[0] < 0 && Wektor_Przesuneicia[1] > 0)
						{
							ratunek[0] = -1;
							ratunek[1] = 1;
						}
						else if (Wektor_Przesuneicia[0] > 0 && Wektor_Przesuneicia[1] > 0)
						{
							ratunek[0] = 1;
							ratunek[1] = 1;
						}
						else if (Wektor_Przesuneicia[0] > 0 && Wektor_Przesuneicia[1] < 0)
						{
							ratunek[0] = 1;
							ratunek[1] = -1;
						}

					} while (zbity > 0 && A.Czy_Mozliwe_Bicie(AI.TabKoniec[0] + Wektor_Przesuneicia[0]+ratunek[0], AI.TabKoniec[1] + Wektor_Przesuneicia[1]+ratunek[1]));


					gracz--;

					if (AI.Zwroc_Punkty() == 12)
					{
						sound.stop();
						przegrana = true;
						oknoAplikacji.close();
						break;
					}
				}

			}
		}

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

void PVP(sf::SoundBuffer BuforB2, Ekran& E,bool& wygrana, bool& przegrana)
{
	Arena A;
	AI AI;
	int x, y, gracz = 1, xk, yk, xp, yp;
	int pom[2];
	bool Czy_Lewy = false, Czy_Prawy = false, wysw = false;;
	int bicie = 0;
	bool menu = false;
	int punkty1=0, punkty2=0;


	sf::Sound sound;
	sound.setBuffer(BuforB2);
	sound.setVolume(5);
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
	
		sf::Event zdarzenie;
		int pomgracz = gracz;

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
				x = ZwrocX(zdarzenie.mouseButton.y);
				y = ZwrocY(zdarzenie.mouseButton.x);
				Czy_Lewy = true;

			}

			if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Right)
			{
				xk = ZwrocX(zdarzenie.mouseButton.y);
				yk = ZwrocY(zdarzenie.mouseButton.x);

				Czy_Prawy = true;
			}

			if (Czy_Lewy == true && Czy_Prawy == true)
			{
				wysw = false;
				bicie = 0;
				xp = xk;
				yp = (int)yk - 65;
				Czy_Lewy = false;
				Czy_Prawy = false;

				pom[1] = ((int)yk - 65) - ((int)y - 65);
				pom[0] = xk - x;

				int wynik = A.Przesun_Pionek(x, (int)y - 65, xk, (int)yk - 65, gracz, E);
				pomgracz = gracz;

				if (wynik == 1)
				{
					bicie++;

					if (gracz == 1) punkty1++;
					else punkty2++;
				
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
				}

				pomgracz = gracz;
				if (punkty1 == 12)
				{
					wygrana = true;
					oknoAplikacji.close();
					break;
				}

				if (punkty2 == 12)
				{
					przegrana = true;
					oknoAplikacji.close();
					break;
				}

				//Zmiana gracza

				if (bicie == 0 && wynik != -1) // Ruch zwyk³y bez bicia
				{
					if (gracz == 1) gracz++;
					else gracz--;
				}
				else if ((!A.Czy_Mozliwe_Bicie(xp, yp) && wynik != -1)) // Czy mozliwe jest dalsze bicie
				{
					if (gracz == 1) gracz++;
					else gracz--;
				}
			}
		}

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

void Wygrana(Ekran& E,bool& menu,bool& Gra)
{
	int xpom1=0, ypom1=0;
	bool lewy1=false;

	sf::RenderWindow Ekran_Wygranej(sf::VideoMode(800, 800, 32), "Wygrana");
	while (Ekran_Wygranej.isOpen())
	{
		sf::Event zdarzenieM;
		while (Ekran_Wygranej.pollEvent(zdarzenieM))
		{
			if (zdarzenieM.type == sf::Event::Closed)
				Ekran_Wygranej.close();

			if (zdarzenieM.type == sf::Event::KeyPressed && zdarzenieM.key.code == sf::Keyboard::Escape)
				Ekran_Wygranej.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
				Ekran_Wygranej.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Left)
			{

				xpom1 = zdarzenieM.mouseButton.x;
				ypom1 = zdarzenieM.mouseButton.y;

				lewy1 = true;

			}

			if (lewy1 == true)
			{
				lewy1 = false;
				if (xpom1 < 782 && xpom1>540 && ypom1 < 686 && ypom1>600) // wyjscie
				{
					Ekran_Wygranej.close();
					Gra = false;
				}
				if (xpom1 < 195 && xpom1>10 && ypom1 < 680 && ypom1>605) // menu glowne
				{
					menu = false;
					Ekran_Wygranej.close();
				}
			}
		}

		Ekran_Wygranej.draw(E.Wygrana);
		Ekran_Wygranej.display();
	}
}

void PrzegranaSI(Ekran& E,bool& menu, bool& Gra)
{
	int xpom2 = 0, ypom2 = 0;
	bool lewy2 = false;

	sf::RenderWindow Ekran_PrzegranejSI(sf::VideoMode(800, 800, 32), "Przegrana");
	while (Ekran_PrzegranejSI.isOpen())
	{
		sf::Event zdarzenieM;
		while (Ekran_PrzegranejSI.pollEvent(zdarzenieM))
		{
			if (zdarzenieM.type == sf::Event::Closed)
				Ekran_PrzegranejSI.close();

			if (zdarzenieM.type == sf::Event::KeyPressed && zdarzenieM.key.code == sf::Keyboard::Escape)
				Ekran_PrzegranejSI.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
				Ekran_PrzegranejSI.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Left)
			{

				xpom2 = zdarzenieM.mouseButton.x;
				ypom2 = zdarzenieM.mouseButton.y;

				lewy2 = true;

			}

			if (lewy2 == true)
			{
				lewy2 = false;
				if (xpom2 < 781 && xpom2>515 && ypom2 < 782 && ypom2 > 693) // wyjscie
				{
					Ekran_PrzegranejSI.close();
					Gra = false;
				}
				if (xpom2 < 738 && xpom2>532 && ypom2 < 605 && ypom2>507) // menu glowne
				{
					menu = false;
					Ekran_PrzegranejSI.close();
				}
			}
		}

		Ekran_PrzegranejSI.draw(E.PrzegranaSI);
		Ekran_PrzegranejSI.display();
	}
}

void Przegrana(Ekran& E, bool& menu, bool& Gra)
{
	int xpom3 = 0, ypom3 = 0;
	bool lewy3 = false;

	sf::RenderWindow Ekran_Przegranej(sf::VideoMode(800, 800, 32), "Przegrana");
	while (Ekran_Przegranej.isOpen())
	{
		sf::Event zdarzenieM;
		while (Ekran_Przegranej.pollEvent(zdarzenieM))
		{
			if (zdarzenieM.type == sf::Event::Closed)
				Ekran_Przegranej.close();

			if (zdarzenieM.type == sf::Event::KeyPressed && zdarzenieM.key.code == sf::Keyboard::Escape)
				Ekran_Przegranej.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Middle)
				Ekran_Przegranej.close();

			if (zdarzenieM.type == sf::Event::MouseButtonPressed && zdarzenieM.mouseButton.button == sf::Mouse::Left)
			{

				xpom3 = zdarzenieM.mouseButton.x;
				ypom3 = zdarzenieM.mouseButton.y;

				lewy3 = true;

			}

			if (lewy3 == true)
			{
				lewy3 = false;
				if (xpom3 < 781 && xpom3>515 && ypom3 < 782 && ypom3 > 693) // wyjscie
				{
					Ekran_Przegranej.close();
					Gra = false;
				}
				if (xpom3 < 738 && xpom3>532 && ypom3 < 605 && ypom3>507) // menu glowne
				{
					menu = false;
					Ekran_Przegranej.close();
				}
			}
		}

		Ekran_Przegranej.draw(E.WygranaPVP);
		Ekran_Przegranej.display();
	}
}
