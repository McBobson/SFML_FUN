#ifndef ARENA2_SFML_H
#define ARENA2_SFML_H
#include <iostream>
#include <math.h>
#include "Wyswietlanie.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <string>


#define ROZ 8

using namespace std;

class Arena2 {

public:

	Ekran E1;
	char **tablica;
	int **wagi;
	string **znaki;
	int **Tab_Rozx;
	int **Tab_Rozy;
	int pom[2];
	string poms[24] = { "P1","P2","P3","P4","P9","P10","P11","P12","P5","P6","P7","P8","Pc12","Pc11","Pc10","Pc9","Pc4","Pc3","Pc2","Pc1","Pc8","Pc7","Pc6","Pc5" };

	sf::Texture Pionek;
	sf::Texture PionekC;
	sf::Texture texture;
	sf::Sprite Sprite;
	sf::Sprite P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12;
	sf::Sprite Pc1, Pc2, Pc3, Pc4, Pc5, Pc6, Pc7, Pc8, Pc9, Pc10, Pc11, Pc12;


	Arena2();
	Arena2(int);
	~Arena2();

	void Animacja(int, int, int, int);
	int Przesun_Pionek(int, int, int, int, int);
	bool Czy_Jest_Pionek(int, int);
	bool Czy_Jest_W_Arenie(int, int);
	int Kierunek_Bicia(int[]);
	bool Bicie(int, int, int[]);
	bool Bicie_Damka(int, int, int[]);
	void Zamien(char, int, int);
	bool Czy_Prawidlowy_Ruch(int[], char);
	bool Czy_Przyjaciel(char, char);
	bool Czy_Mozliwe_Bicie(int, int);
	bool Czy_Mozliwe_Bicie_Damka(int, int);
	bool Czy_Przyjaciel_Damki(int, int, int, int);
	bool Czy_Ruch_W_Tyl(int[], char);

	void Ekran_Koncowy(int, int, int);

	int Czy_Mozliwe_Bicie_AI(int, int);


	//////////////////////////////////////////////////////

	void Tworz_Plansze();
	void Ulozenie_Pionkow();


};

Arena2::Arena2()
{
	tablica = new char *[ROZ];
	wagi = new int *[ROZ];
	znaki = new string *[ROZ];
	Tab_Rozx = new int *[ROZ];
	Tab_Rozy = new int *[ROZ];

	int k = 0;

	for (int i = 0; i < ROZ; i++)
	{
		tablica[i] = new char[ROZ];
		wagi[i] = new int[ROZ];
		znaki[i] = new string[ROZ];
		Tab_Rozx[i] = new int[ROZ];
		Tab_Rozy[i] = new int[ROZ];
	}

	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			tablica[i][j] = ' ';
			wagi[i][j] = 0;
			znaki[i][j] = " ";
		}
	}

	for (int i = 0; i < 3; i += 2)
	{
		for (int j = 0; j < 8; j += 2)
		{
			tablica[i][j] = 'x';
			wagi[i][j] = 1;
			znaki[i][j] = poms[k++];
		}
	}

	for (int i = 1; i < 8; i += 2)
	{
		tablica[1][i] = 'x';
		wagi[1][i] = 1;
		znaki[1][i] = poms[k++];

	}


	for (int i = 5; i < 8; i += 2)
	{
		for (int j = 1; j < 8; j += 2)
		{
			tablica[i][j] = 'o';
			wagi[i][j] = 1;
			znaki[i][j] = poms[k++];
		}
	}

	for (int i = 0; i < 8; i += 2)
	{
		tablica[6][i] = 'o';
		wagi[6][i] = 1;
		znaki[6][i] = poms[k++];
	}

	int xpocz = 93, ypocz = 93;

	for (int i = 0; i < ROZ; i++)
	{
		xpocz = 93;

		for (int j = 0; j < ROZ; j++)
		{
			Tab_Rozx[i][j] = xpocz;
			Tab_Rozy[i][j] = ypocz;
			xpocz += 78;
		}
		ypocz += 78;
	}


}

Arena2::Arena2(int l) {
	tablica = new char *[ROZ];
	wagi = new int *[ROZ];

	for (int i = 0; i < ROZ; i++)
	{
		tablica[i] = new char[ROZ];
		wagi[i] = new int[ROZ];
	}

	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			tablica[i][j] = ' ';
			wagi[i][j] = 0;
		}
	}
	tablica[7][1] = 'O';
	tablica[4][4] = 'x';
	tablica[5][1] = 'o';
	tablica[0][0] = 'x';
	tablica[2][2] = 'x';
	tablica[4][6] = 'x';
	tablica[5][5] = 'o';
	tablica[7][3] = 'o';
	tablica[7][5] = 'o';


	//tablica[4][4] = 'x';
	//tablica[4][4] = 'O';

}

Arena2::~Arena2()
{
	for (int i = 0; i < ROZ; i++)
	{
		delete[] tablica[i];
		delete[] wagi[i];
	}

	delete[] tablica;
	delete[] wagi;
}

bool Arena2::Czy_Jest_Pionek(int x, int y)
{
	if (tablica[x][y] != ' ')
	{
		return true;
	}

	else return false;
}

bool Arena2::Czy_Jest_W_Arenie(int x, int y)
{
	if (x <= 7 && y <= 7 && x >= 0 && y >= 0)
	{
		return true;
	}

	else return false;
}

bool Arena2::Czy_Przyjaciel(char x, char y)
{
	if (x == y)
	{
		return true;
	}
	else if (x == 'O' && y == 'o')
	{
		return true;
	}
	else if (x == 'X' && y == 'x')
	{
		return true;
	}
	else if (x == 'o' && y == 'O')
	{
		return true;
	}
	else if (x == 'x' && y == 'X')
	{
		return true;
	}
	else return false;
}

int Arena2::Kierunek_Bicia(int tab[])
{
	if (tab[0] < 0 && tab[1] < 0)
	{
		return 0;
	}
	else if (tab[0] < 0 && tab[1] > 0)
	{
		return 1;
	}
	else if (tab[0] > 0 && tab[1] < 0)
	{
		return 2;
	}
	else if (tab[0] > 0 && tab[1] > 0)
	{
		return 3;
	}
	else return -1;
}

bool Arena2::Czy_Przyjaciel_Damki(int x, int y, int x1, int y1)
{
	if (tablica[x][y] == tablica[x1][y1])
	{
		return true;
	}
	else if (tablica[x][y] == 'O' && tablica[x1][y1] == 'o')
	{
		return true;
	}
	else if (tablica[x][y] == 'X' && tablica[x1][y1] == 'x')
	{
		return true;
	}
	else return false;
}

bool Arena2::Bicie(int x, int y, int tab[])
{
	switch (Kierunek_Bicia(tab))
	{
	case 0:
	{
		if (!Czy_Jest_Pionek(x - 1, y - 1) && Czy_Jest_W_Arenie(x - 1, y - 1) && !Czy_Przyjaciel(tablica[x][y], tablica[x + 1][y + 1]) && Czy_Jest_Pionek(x, y)) // Czy przyjaciel damki konieczny do sprawdzania wielokrotnego bicia
		{
			return true;
		}
		else return false;
	}
	break;

	case 1:
	{
		if (!Czy_Jest_Pionek(x - 1, y + 1) && Czy_Jest_W_Arenie(x - 1, y + 1) && !Czy_Przyjaciel(tablica[x][y], tablica[x + 1][y - 1]) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	case 2:
	{
		if (!Czy_Jest_Pionek(x + 1, y - 1) && Czy_Jest_W_Arenie(x + 1, y - 1) && !Czy_Przyjaciel(tablica[x][y], tablica[x - 1][y + 1]) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	case 3:
	{
		if (!Czy_Jest_Pionek(x + 1, y + 1) && Czy_Jest_W_Arenie(x + 1, y + 1) && !Czy_Przyjaciel(tablica[x][y], tablica[x - 1][y - 1]) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	default: return false;
	}

}

bool Arena2::Bicie_Damka(int x, int y, int tab[])
{
	switch (Kierunek_Bicia(tab))
	{
	case 0:
	{
		if (!Czy_Jest_Pionek(x - 1, y - 1) && Czy_Jest_W_Arenie(x - 1, y - 1) && !Czy_Przyjaciel_Damki(x - tab[0], y - tab[1], x, y) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	case 1:
	{
		if (!Czy_Jest_Pionek(x - 1, y + 1) && Czy_Jest_W_Arenie(x - 1, y + 1) && !Czy_Przyjaciel_Damki(x - tab[0], y - tab[1], x, y) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	case 2:
	{
		if (!Czy_Jest_Pionek(x + 1, y - 1) && Czy_Jest_W_Arenie(x + 1, y - 1) && !Czy_Przyjaciel_Damki(x - tab[0], y - tab[1], x, y) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	case 3:
	{
		if (!Czy_Jest_Pionek(x + 1, y + 1) && Czy_Jest_W_Arenie(x + 1, y + 1) && !Czy_Przyjaciel_Damki(x - tab[0], y - tab[1], x, y) && Czy_Jest_Pionek(x, y))
		{
			return true;
		}
		else return false;
	}
	break;

	default: return false;
	}
}

void Arena2::Zamien(char znak, int x, int y)
{
	if (znak == 'x' && x == 7)
	{
		tablica[x][y] = 'X';
		wagi[x][y] = 2;
	}

	if (znak == 'o' && x == 0)
	{
		tablica[x][y] = 'O';
		wagi[x][y] = 2;
	}
}

bool Arena2::Czy_Prawidlowy_Ruch(int pom[], char znak)
{
	if ((abs(pom[0]) == 1 && abs(pom[1]) == 1 && (znak == 'x' || znak == 'o')) || ((abs(pom[0]) == abs(pom[1]) && (znak == 'X' || znak == 'O'))))
	{
		return true;
	}
	else return false;
}

bool Arena2::Czy_Ruch_W_Tyl(int pom[], char znak)
{
	if ((znak == 'x' && pom[0] > 0 || znak == 'o' && pom[0] < 0))
	{
		return true;
	}
	else if ((znak == 'X' && pom[0] < 0 || znak == 'O' && pom[0] > 0))
	{
		return true;
	}
	return false;
}

bool Arena2::Czy_Mozliwe_Bicie(int x, int y)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };

	/*
	if (Bicie(x-1,y-1,LUp)==1 && Czy_Jest_W_Arenie(x-1,y-1))
	{
		cout << "Tak1" << endl;
		return true;
	}
	else if (Bicie(x-1, y+1, RUp)==1 && Czy_Jest_W_Arenie(x - 1, y + 1))
	{
		cout << "Tak2" << endl;
		return true;
	}
	else if (Bicie(x+1, y+1, RDown)==1 && Czy_Jest_W_Arenie(x + 1, y + 1))
	{
		cout << "Tak3" << endl;
		return true;
	}
	else if (Bicie(x+1, y-1, LDown)==1 && Czy_Jest_W_Arenie(x + 1, y - 1))
	{
		cout << "Tak4" << endl;
		return true;
	}

	else return false;*/

	if (Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		//cout << "Bicie lewo gora" << endl;
		//cout << x << " " << y << endl;
		if (Bicie(x - 1, y - 1, LUp))
		{
			cout << "Tak1" << endl;
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		//cout << "Bicie prawo gora" << endl;
		if (Bicie(x - 1, y + 1, RUp))
		{
			cout << "Tak2" << endl;
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		//cout << "Bicie prawo dol" << endl;
		if (Bicie(x + 1, y + 1, RDown))
		{
			cout << "Tak3" << endl;
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		//cout << "Bicie lewo dol" << endl;
		if (Bicie(x + 1, y - 1, LDown))
		{
			cout << "Tak4" << endl;
			return true;
		}
	}

	return false;
}

bool Arena2::Czy_Mozliwe_Bicie_Damka(int x1, int y1)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };

	int x = x1, y = y1;

	while (x != 7 && x != 0 && y != 7 && y != 0 && !Czy_Jest_Pionek(x + LUp[0], y + LUp[1]))
	{
		x += LUp[0];
		y += LUp[1];
	}
	if (x + LUp[0] != 7 && x + LUp[0] != 0 && y + LUp[1] != 7 && y + LUp[1] != 0 && Czy_Jest_W_Arenie(x + LUp[0], y + LUp[1]) && !Czy_Jest_Pionek(x + LUp[0] - 1, y + LUp[1] - 1))
	{
		if (!Czy_Przyjaciel_Damki(x, y, x + LUp[0], y + LUp[1]) && Czy_Jest_Pionek(x + LUp[0], y + LUp[1]))
		{
			//cout << "Bicie lewo gora" << endl;
			return true;
		}
	}
	x = x1, y = y1;

	while (x != 7 && x != 0 && y != 7 && y != 0 && !Czy_Jest_Pionek(x + RUp[0], y + RUp[1]))
	{
		x += RUp[0];
		y += RUp[1];
	}
	if (x + RUp[0] != 7 && x + RUp[0] != 0 && y + RUp[1] != 7 && y + RUp[1] != 0 && Czy_Jest_W_Arenie(x + RUp[0], y + RUp[1]) && !Czy_Jest_Pionek(x + RUp[0] - 1, y + RUp[1] + 1))
	{
		if (!Czy_Przyjaciel_Damki(x, y, x + RUp[0], y + RUp[1]) && Czy_Jest_Pionek(x + RUp[0], y + RUp[1]))
		{
			//cout << "Bicie prawo gora" << endl;
			return true;
		}
	}

	x = x1, y = y1;

	while (x != 7 && x != 0 && y != 7 && y != 0 && !Czy_Jest_Pionek(x + RDown[0], y + RDown[1]))
	{
		x += RDown[0];
		y += RDown[1];
	}

	if (x + RDown[0] != 7 && x + RDown[0] != 0 && y + RDown[1] != 7 && y + RDown[1] != 0 && Czy_Jest_W_Arenie(x + RDown[0], y + RDown[1]) && !Czy_Jest_Pionek(x + RDown[0] + 1, y + RDown[1] + 1))
	{
		if (!Czy_Przyjaciel_Damki(x, y, x + RDown[0], y + RDown[1]) && Czy_Jest_Pionek(x + RDown[0], y + RDown[1]))
		{
			//cout << "Bicie prawo dol" << endl;
			return true;
		}
	}
	x = x1, y = y1;

	while (x != 7 && x != 0 && y != 7 && y != 0 && !Czy_Jest_Pionek(x + LDown[0], y + LDown[1]))
	{
		x += LDown[0];
		y += LDown[1];
	}
	if (x + LDown[0] != 7 && x + LDown[0] != 0 && y + LDown[1] != 7 && y + LDown[1] != 0 && Czy_Jest_W_Arenie(x + LDown[0], y + LDown[1]) && !Czy_Jest_Pionek(x + LDown[0] + 1, y + LDown[1] - 1))
	{
		if (!Czy_Przyjaciel_Damki(x, y, x + LDown[0], y + LDown[1]) && Czy_Jest_Pionek(x + LDown[0], y + LDown[1]))
		{
			//cout << "Bicie lewo dol" << endl;
			return true;
		}
	}

	return false;
}

int Arena2::Przesun_Pionek(int y1, int x1, int y2, int x2, int gracz)
{
	pom[0] = x2 - x1;
	pom[1] = y2 - y1;

	if ((tablica[x1][y1] == 'o' && gracz == 1) || (tablica[x1][y1] == 'x' && gracz == 2) || (tablica[x1][y1] == 'O' && gracz == 1) || (tablica[x1][y1] == 'X' && gracz == 2)) // Czy prawid³owy warcab dla gracza
	{
		if (Czy_Jest_Pionek(x1, y1) && Czy_Jest_W_Arenie(x2, y2) && Czy_Prawidlowy_Ruch(pom, tablica[x1][y1]))
		{
			if (Czy_Jest_Pionek(x2, y2)) // Instrukcje gdy bijemy pionki
			{
				if (tablica[x1][y1] == 'O' || tablica[x1][y1] == 'X') // Polecenia dla damki
				{
					if (Bicie_Damka(x2, y2, pom))
					{
						switch (Kierunek_Bicia(pom))
						{
						case 0:
						{
							tablica[x2 - 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 - 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

				

							Animacja(x1, y1, x2, y2);
						}
						break;

						case 1:
						{
							tablica[x2 - 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 - 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2);
						}
						break;

						case 2:
						{
							tablica[x2 + 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 + 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2);
						}
						break;

						case 3:
						{
							tablica[x2 + 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 + 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2);
						}
						break;
						}
						return 1;

					}
					else
					{
						cout << "Bicie nie jest mozliwe" << endl;
						return 0;
					}

				}
				else
				{
					if (Bicie(x2, y2, pom))
					{
						//cout << "Bicie zwykle" << endl;
						switch (Kierunek_Bicia(pom))
						{
						case 0:
						{
							tablica[x2 - 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 - 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien(tablica[x2 - 1][y2 - 1], x2 - 1, y2 - 1);
							Animacja(x1, y1, x2, y2);
						}
						break;

						case 1:
						{
							tablica[x2 - 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 - 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien(tablica[x2 - 1][y2 + 1], x2 - 1, y2 + 1);
							Animacja(x1, y1, x2, y2);
						}
						break;

						case 2:
						{
							tablica[x2 + 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 + 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien(tablica[x2 + 1][y2 - 1], x2 + 1, y2 - 1);
							Animacja(x1, y1, x2, y2);
						}
						break;

						case 3:
						{
							tablica[x2 + 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							wagi[x2 + 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien(tablica[x2 + 1][y2 + 1], x2 + 1, y2 + 1);
							Animacja(x1, y1, x2, y2);
						}
						break;
						}
						return 1;

					}
					else
					{
						cout << "Bicie nie jest mozliwe" << endl;
						return 0;
					}
				}

			}
			else if (Czy_Ruch_W_Tyl(pom, tablica[x1][y1]))
			{
				tablica[x2][y2] = tablica[x1][y1];
				tablica[x1][y1] = ' ';

				Animacja(x1, y1, x2, y2);

				znaki[x2][y2] = znaki[x1][y1];
				znaki[x1][y1] = " ";

				wagi[x2][y2] = wagi[x1][y1];
				wagi[x1][y1] = 0;

				Zamien(tablica[x2][y2], x2, y2);
				return 0;
			}
			else cout << "Nie uciekamy z frontu!!!" << endl;

		}
		else
		{
			cout << "Kody b³edu: " << endl;
			cout << "Czy jest pionek: " << Czy_Jest_Pionek(x1, y1) << endl;
			cout << "Czy jest w arenie: " << Czy_Jest_W_Arenie(x2, y2) << endl;
			cout << "Czy prawidlowy ruch: " << Czy_Prawidlowy_Ruch(pom, tablica[x1][y1]) << endl;
			return 0;
		}
	}
	else
	{
		cout << "Trzymaj sie swoich pionow rycerzu!!!!" << endl;
		return 0;
	}


}

void Arena2::Ekran_Koncowy(int punkty1, int punkty2, int gracz)
{
	system("cls");

	cout << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "                                        " << "Gratulacje dla gracza: " << gracz << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
}

ostream& operator << (ostream& wyjscie, Arena2& A) {


	{
		wyjscie << endl << "       ";


		for (int i = 65; i < 65 + 8; i++)
		{
			wyjscie << (char)i << "     ";
		}

		wyjscie << endl;

	}

	{

		wyjscie << "     ";

		for (int i = 0; i < 24; i++)
		{
			wyjscie << "_ ";
		}

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 0" << "  ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[0][i] << "  ";
		}

		wyjscie << "|  " << "0";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     ";

	}

	{
		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 1" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[1][i] << "  ";
		}

		wyjscie << "|  " << "1";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 2" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[2][i] << "  ";
		}

		wyjscie << "|  " << "2";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 3" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[3][i] << "  ";
		}

		wyjscie << "|  " << "3";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 4" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[4][i] << "  ";
		}

		wyjscie << "|  " << "4";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 5" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[5][i] << "  ";
		}

		wyjscie << "|  " << "5";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 6" << "  ";


		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[6][i] << "  ";
		}

		wyjscie << "|  " << "6";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << "    ";

		for (int i = 0; i < ROZ + 1; i++)
		{
			wyjscie << "|     ";
		}

		wyjscie << endl << " 7" << "  ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|  " << A.tablica[7][i] << "  ";
		}

		wyjscie << "|  " << "7";

		wyjscie << endl << "    ";

		for (int i = 0; i < ROZ; i++)
		{
			wyjscie << "|_ _ _";
		}

		wyjscie << "|     " << endl;

	}

	{
		wyjscie << endl << "       ";


		for (int i = 65; i < 65 + 8; i++)
		{
			wyjscie << (char)i << "     ";
		}

	}


	return wyjscie;
}

void Arena2::Animacja(int xp, int yp, int xk, int yk)
{
	string znakpom;
	int pomx, pomy;

	znakpom = znaki[xp][yp];

	cout << znakpom << endl;

	if (znakpom == "P1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P1.setPosition(pomx, pomy);
	}
	else if (znakpom == "P2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P2.setPosition(pomx, pomy);
	}
	else if (znakpom == "P3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P3.setPosition(pomx, pomy);
	}
	else if (znakpom == "P4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P4.setPosition(pomx, pomy);
	}
	else if (znakpom == "P5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P5.setPosition(pomx, pomy);
	}
	else if (znakpom == "P6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P6.setPosition(pomx, pomy);
	}
	else if (znakpom == "P7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P7.setPosition(pomx, pomy);
	}
	else if (znakpom == "P8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P8.setPosition(pomx, pomy);
	}
	else if (znakpom == "P9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P9.setPosition(pomx, pomy);
	}
	else if (znakpom == "P10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P10.setPosition(pomx, pomy);
	}
	else if (znakpom == "P11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P11.setPosition(pomx, pomy);
	}
	else if (znakpom == "P12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		P12.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc1.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];

		cout << pomx << " " << pomy << endl;
		Pc2.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc3.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc4.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc5.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc6.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc7.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc8.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc9.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc10.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc11.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		Pc12.setPosition(pomx, pomy);
	}
}





int Arena2::Czy_Mozliwe_Bicie_AI(int x, int y)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };


	if (Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		//cout << "Bicie lewo gora" << endl;
		//cout << x << " " << y << endl;
		if (Bicie(x - 1, y - 1, LUp))
		{
			//cout << "Tak1" << endl;
			return 0;
		}
	}

	if (Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		//cout << "Bicie prawo gora" << endl;
		if (Bicie(x - 1, y + 1, RUp))
		{
			//cout << "Tak2" << endl;
			return 1;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		//cout << "Bicie prawo dol" << endl;
		if (Bicie(x + 1, y + 1, RDown))
		{
			//cout << "Tak3" << endl;
			return 3;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		//cout << "Bicie lewo dol" << endl;
		if (Bicie(x + 1, y - 1, LDown))
		{
			//cout << "Tak4" << endl;
			return 2;
		}
	}

	return -1;
}


//////////////////////////////////////////////


void Arena2::Tworz_Plansze()
{
	texture.loadFromFile("plansza.jpg");
	texture.setSmooth(true);

	Sprite.setTexture(texture);
}

void Arena2::Ulozenie_Pionkow()
{
	Pionek.loadFromFile("bia³y.png");
	Pionek.setSmooth(true);

	P1.setTexture(Pionek);
	P2.setTexture(Pionek);
	P3.setTexture(Pionek);
	P4.setTexture(Pionek);
	P5.setTexture(Pionek);
	P6.setTexture(Pionek);
	P7.setTexture(Pionek);
	P8.setTexture(Pionek);
	P9.setTexture(Pionek);
	P10.setTexture(Pionek);
	P11.setTexture(Pionek);
	P12.setTexture(Pionek);

	P1.setScale(1.2, 1.2);
	P1.setPosition(93, 93);

	P2.setScale(1.2, 1.2);
	P2.setPosition(249, 93);

	P3.setScale(1.2, 1.2);
	P3.setPosition(403, 93);

	P4.setScale(1.2, 1.2);
	P4.setPosition(557, 93);

	////////////////////////////////

	P5.setScale(1.2, 1.2);
	P5.setPosition(171, 170);

	P6.setScale(1.2, 1.2);
	P6.setPosition(325, 170);

	P7.setScale(1.2, 1.2);
	P7.setPosition(479, 170);

	P8.setScale(1.2, 1.2);
	P8.setPosition(634, 170);

	///////////////////////////////////

	P9.setScale(1.2, 1.2);
	P9.setPosition(93, 247);

	P10.setScale(1.2, 1.2);
	P10.setPosition(249, 247);

	P11.setScale(1.2, 1.2);
	P11.setPosition(403, 247);

	P12.setScale(1.2, 1.2);
	P12.setPosition(557, 247);

	//////////////////////////////////////////////////////////////////////////////////

	PionekC.loadFromFile("czarne.png");
	PionekC.setSmooth(true);

	Pc1.setTexture(PionekC);
	Pc2.setTexture(PionekC);
	Pc3.setTexture(PionekC);
	Pc4.setTexture(PionekC);
	Pc5.setTexture(PionekC);
	Pc6.setTexture(PionekC);
	Pc7.setTexture(PionekC);
	Pc8.setTexture(PionekC);
	Pc9.setTexture(PionekC);
	Pc10.setTexture(PionekC);
	Pc11.setTexture(PionekC);
	Pc12.setTexture(PionekC);

	Pc1.setScale(1.2, 1.2);
	Pc1.setPosition(634, 634);

	Pc2.setScale(1.2, 1.2);
	Pc2.setPosition(479, 634);

	Pc3.setScale(1.2, 1.2);
	Pc3.setPosition(325, 634);

	Pc4.setScale(1.2, 1.2);
	Pc4.setPosition(171, 634);

	////////////////////////////////

	Pc5.setScale(1.2, 1.2);
	Pc5.setPosition(557, 557);

	Pc6.setScale(1.2, 1.2);
	Pc6.setPosition(403, 557);

	Pc7.setScale(1.2, 1.2);
	Pc7.setPosition(249, 557);

	Pc8.setScale(1.2, 1.2);
	Pc8.setPosition(93, 557);

	///////////////////////////////////

	Pc9.setScale(1.2, 1.2);
	Pc9.setPosition(634, 480);

	Pc10.setScale(1.2, 1.2);
	Pc10.setPosition(479, 480);

	Pc11.setScale(1.2, 1.2);
	Pc11.setPosition(325, 480);

	Pc12.setScale(1.2, 1.2);
	Pc12.setPosition(171, 480);
}


#endif // !PLANSZA_H

#pragma once
