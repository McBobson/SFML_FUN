#ifndef ARENA_SFML_H
#define ARENA_SFML_H
#include <iostream>
#include <math.h>
#include "Wyswietlanie.h"

#define ROZ 8

using namespace std;

class Arena{

public:

	char **tablica;
	int **wagi;
	string **znaki;
	int **Tab_Rozx;
	int **Tab_Rozy;
	int pom[2];
	int licznik=0;
	string poms[24] = { "P1","P2","P3","P4","P9","P10","P11","P12","P5","P6","P7","P8","Pc12","Pc11","Pc10","Pc9","Pc4","Pc3","Pc2","Pc1","Pc8","Pc7","Pc6","Pc5" };


	Arena();
	Arena(int);
	~Arena();

	void Animacja(int, int, int, int,Ekran&);
	void Wyczysc_Pole(int, int, Ekran&);
	void Zamien_SFML(int, int, Ekran&);
	int Przesun_Pionek(int, int, int, int, int,Ekran&);
	bool Czy_Jest_Pionek(int, int);
	bool Czy_Jest_W_Arenie(int, int);
	int Kierunek_Bicia(int[]);
	bool Bicie(int, int, int[]);
	bool Bicie_Damka(int, int, int[]);
	void Zamien(char, int, int);
	bool Czy_Prawidlowy_Ruch(int[], char);
	bool Czy_Przyjaciel(char, char);
	bool Czy_Mozliwe_Bicie(int, int);
	int Czy_Mozliwe_Bicie_Damka(int, int);
	bool Czy_Przyjaciel_Damki(int, int, int, int);
	bool Czy_Ruch_W_Tyl(int[], char);
	bool Czy_Droga_Wolna(int, int, int, int);

	void Ekran_Koncowy(int, int, int);


};

Arena::Arena()
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

	int xpocz=93, ypocz = 93;

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

Arena::Arena(int l) {
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



}

Arena::~Arena()
{
	for (int i = 0; i < ROZ; i++)
	{
		delete[] tablica[i];
		delete[] wagi[i];
	}

	delete[] tablica;
	delete[] wagi;
}

bool Arena::Czy_Jest_Pionek(int x, int y)
{
	if (tablica[x][y] != ' ')
	{
		return true;
	}

	else return false;
}

bool Arena::Czy_Jest_W_Arenie(int x, int y)
{
	if (x <= 7 && y <= 7 && x >= 0 && y >= 0)
	{
		return true;
	}

	else return false;
}

bool Arena::Czy_Przyjaciel(char x, char y)
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

int Arena::Kierunek_Bicia(int tab[])
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

bool Arena::Czy_Przyjaciel_Damki(int x, int y, int x1, int y1)
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

bool Arena::Bicie(int x, int y, int tab[])
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

bool Arena::Bicie_Damka(int x, int y, int tab[])
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

void Arena::Zamien(char znak, int x, int y)
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

bool Arena::Czy_Droga_Wolna(int xp, int yp, int xk, int yk)
{
	int pom[2];
	if (xk - xp < 0)
	{
		pom[0] = -1;
	}
	else pom[0] = 1;

	if (yk - yp < 0)
	{
		pom[1] = -1;
	}
	else pom[1] = 1;

	while (xp != xk && yp != yk)
	{
		xp += pom[0];
		yp += pom[1];


		if (Czy_Jest_Pionek(xp, yp))
		{
			return false;
		}
	}

	return true;
}

bool Arena::Czy_Prawidlowy_Ruch(int pom[], char znak)
{
	if ((abs(pom[0]) == 1 && abs(pom[1]) == 1 && (znak == 'x' || znak == 'o')) || ((abs(pom[0]) == abs(pom[1]) && (znak == 'X' || znak == 'O'))))
	{
		return true;
	}
	else return false;
}

bool Arena::Czy_Ruch_W_Tyl(int pom[], char znak)
{
	if ((znak == 'x' && pom[0] > 0 || znak == 'o' && pom[0] < 0))
	{
		return true;
	}
	else if (znak == 'X' && pom[0] < 0 || znak == 'X' && pom[0] > 0 || znak == 'O' && pom[0] > 0 || znak == 'O' && pom[0] < 0)
	{
		return true;
	}
	return false;
}

bool Arena::Czy_Mozliwe_Bicie(int x, int y)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };

	if (Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		if (Bicie(x - 1, y - 1, LUp))
		{
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		if (Bicie(x - 1, y + 1, RUp))
		{
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0)
	{
		if (Bicie(x + 1, y + 1, RDown))
		{
			return true;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0)
	{
		if (Bicie(x + 1, y - 1, LDown))
		{
			return true;
		}
	}

	return false;
}

int Arena::Czy_Mozliwe_Bicie_Damka(int x1, int y1)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };

	int x = x1, y = y1;

	licznik = 0;
	while (x + LUp[0] < 7 && x + LUp[0] > 0 && y + LUp[1] < 7 && y + LUp[1] > 0 && !Czy_Jest_Pionek(x + LUp[0], y + LUp[1])) {
		x += LUp[0];
		y += LUp[1];
		licznik++;
	}

	if (x + LUp[0] < 7 && x + LUp[0] > 0 && y + LUp[1] < 7 && y + LUp[1] > 0 &&	Czy_Jest_W_Arenie(x + LUp[0], y + LUp[1]) && !Czy_Jest_Pionek(x + LUp[0] - 1, y + LUp[1] - 1))
		if (!Czy_Przyjaciel_Damki(x1, y1, x + LUp[0], y + LUp[1]) && Czy_Jest_Pionek(x + LUp[0], y + LUp[1])) return 1;
	x = x1, y = y1;
	licznik = 0;

	while (x + RUp[0] < 7 && x + RUp[0] > 0 && y + RUp[1] < 7 && y + RUp[1] > 0 && !Czy_Jest_Pionek(x + RUp[0], y + RUp[1])) {
		x += RUp[0];
		y += RUp[1];
		licznik++;
	}
	if (x + RUp[0] < 7 && x + RUp[0] > 0 && y + RUp[1] < 7 && y + RUp[1] > 0 &&	Czy_Jest_W_Arenie(x + RUp[0], y + RUp[1]) && !Czy_Jest_Pionek(x + RUp[0] - 1, y + RUp[1] + 1))
		if (!Czy_Przyjaciel_Damki(x1, y1, x + RUp[0], y + RUp[1]) && Czy_Jest_Pionek(x + RUp[0], y + RUp[1])) return 2;
	x = x1, y = y1;
	licznik = 0;

	while (x + RDown[0] < 7 && x + RDown[0] > 0 && y + RDown[1] < 7 && y + RDown[1] > 0 && !Czy_Jest_Pionek(x + RDown[0], y + RDown[1])) {
		x += RDown[0];
		y += RDown[1];
		licznik++;
	}

	if (x + RDown[0] < 7 && x + RDown[0] > 0 && y + RDown[1] < 7 && y + RDown[1] > 0 &&	Czy_Jest_W_Arenie(x + RDown[0], y + RDown[1]) && !Czy_Jest_Pionek(x + RDown[0] + 1, y + RDown[1] + 1))
		if (!Czy_Przyjaciel_Damki(x1, y1, x + RDown[0], y + RDown[1]) && Czy_Jest_Pionek(x + RDown[0], y + RDown[1])) return 3;
	x = x1, y = y1;
	licznik = 0;

	while (x + LDown[0] < 7 && x + LDown[0] > 0 && y + LDown[1] < 7 && y + LDown[1] > 0 && !Czy_Jest_Pionek(x + LDown[0], y + LDown[1])) {
		x += LDown[0];
		y += LDown[1];
		licznik++;
	}
	if (x + LDown[0] < 7 && x + LDown[0] > 0 && y + LDown[1] < 7 && y + LDown[1] > 0 && Czy_Jest_W_Arenie(x + LDown[0], y + LDown[1]) && !Czy_Jest_Pionek(x + LDown[0] + 1, y + LDown[1] - 1))
		if (!Czy_Przyjaciel_Damki(x1, y1, x + LDown[0], y + LDown[1]) && Czy_Jest_Pionek(x + LDown[0], y + LDown[1])) return 4;

	return -1;
}

int Arena::Przesun_Pionek(int x1, int y1, int x2, int y2, int gracz, Ekran &E)
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
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 - 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 - 1, y2 - 1, E);

							znaki[x2 - 1][y2 - 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 - 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

						}
						break;

						case 1:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 - 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 - 1, y2 + 1, E);

							znaki[x2 - 1][y2 + 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 - 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2,E);
						}
						break;

						case 2:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 + 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 + 1, y2 - 1, E);

							znaki[x2 + 1][y2 - 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 + 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2,E);
						}
						break;

						case 3:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 + 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 + 1, y2 + 1, E);

							znaki[x2 + 1][y2 + 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 + 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Animacja(x1, y1, x2, y2,E);
						}
						break;
						}
						return 1;

					}
					else
					{
						cout << "Bicie nie jest mozliwe" << endl;
						return -1;
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
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 - 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 - 1, y2 - 1, E);

							znaki[x2 - 1][y2 - 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 - 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien_SFML(x2 - 1, y2 - 1, E);
							Zamien(tablica[x2 - 1][y2 - 1], x2 - 1, y2 - 1);
							
						}
						break;

						case 1:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 - 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 - 1, y2 + 1, E);

							znaki[x2 - 1][y2 + 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 - 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien_SFML(x2 - 1, y2 + 1, E);
							Zamien(tablica[x2 - 1][y2 + 1], x2 - 1, y2 + 1);
							
						}
						break;

						case 2:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 + 1][y2 - 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2+1, y2-1, E);

							znaki[x2 + 1][y2 - 1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 + 1][y2 - 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien_SFML(x2 + 1, y2 - 1, E);
							Zamien(tablica[x2 + 1][y2 - 1], x2 + 1, y2 - 1);
						}
						break;

						case 3:
						{
							Wyczysc_Pole(x2, y2, E);
							tablica[x2 + 1][y2 + 1] = tablica[x1][y1];
							tablica[x1][y1] = ' ';
							tablica[x2][y2] = ' ';

							Animacja(x1, y1, x2 + 1, y2 + 1, E);

							znaki[x2+1][y2+1] = znaki[x1][y1];
							znaki[x1][y1] = " ";
							znaki[x2][y2] = " ";

							wagi[x2 + 1][y2 + 1] = wagi[x1][y1];
							wagi[x1][y1] = 0;
							wagi[x2][y2] = 0;

							Zamien_SFML(x2 + 1, y2 + 1, E);
							Zamien(tablica[x2 + 1][y2 + 1], x2 + 1, y2 + 1);
		
						}
						break;
						}
						return 1;

					}
					else
					{
						cout << "Bicie nie jest mozliwe" << endl;
						return -1;
					}
				}

			}
			else if (Czy_Ruch_W_Tyl(pom, tablica[x1][y1]))
			{	
			if((tablica[x1][y1]=='X' || tablica[x1][y1]=='O') && !Czy_Droga_Wolna(x1, y1, x2, y2))
			{
					return -1;
			}
			else
			{
				tablica[x2][y2] = tablica[x1][y1];
				tablica[x1][y1] = ' ';

				Animacja(x1, y1, x2, y2, E);

				znaki[x2][y2] = znaki[x1][y1];
				znaki[x1][y1] = " ";

				wagi[x2][y2] = wagi[x1][y1];
				wagi[x1][y1] = 0;

				Zamien_SFML(x2, y2, E);
				Zamien(tablica[x2][y2], x2, y2);
				return 0;
			}
			}
			else {
				cout << "Nie uciekamy z frontu!!!" << endl;
				return -1;
			}

		}
		else
		{
			cout << "Kody b³edu: " << endl;
			cout << "Czy jest pionek: " << Czy_Jest_Pionek(x1, y1) << endl;
			cout << "Czy jest w arenie: " << Czy_Jest_W_Arenie(x2, y2) << endl;
			cout << "Czy prawidlowy ruch: " << Czy_Prawidlowy_Ruch(pom, tablica[x1][y1]) << endl;
			return -1;
		}
	}
	else
	{
		cout << "Trzymaj sie swoich pionow rycerzu!!!!" << endl;
		return -1;
	}


}

void Arena::Ekran_Koncowy(int punkty1, int punkty2, int gracz)
{
	system("cls");

	cout << endl;
	cout << "-------------------------------------------------------------------------------------------" << endl;
	cout << "                            " << "Gratulacje dla gracza: " << gracz << endl;
	cout << "---------------------------------------------------------------------------------------------" << endl;
}

ostream& operator << (ostream& wyjscie, Arena& A) {


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

void Arena::Animacja(int xp, int yp,int xk,int yk, Ekran &E1)
{
	string znakpom;
	int pomx, pomy;
	
	znakpom = znaki[xp][yp];
	
	if (znakpom == "P1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P1.setPosition(pomx, pomy);
	}
	else if (znakpom == "P2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P2.setPosition(pomx, pomy);
	}
	else if (znakpom == "P3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P3.setPosition(pomx, pomy);
	}
	else if (znakpom == "P4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P4.setPosition(pomx, pomy);
	}
	else if (znakpom == "P5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P5.setPosition(pomx, pomy);
	}
	else if (znakpom == "P6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P6.setPosition(pomx, pomy);
	}
	else if (znakpom == "P7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P7.setPosition(pomx, pomy);
	}
	else if (znakpom == "P8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P8.setPosition(pomx, pomy);
	}
	else if (znakpom == "P9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P9.setPosition(pomx, pomy);
	}
	else if (znakpom == "P10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P10.setPosition(pomx, pomy);
	}
	else if (znakpom == "P11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P11.setPosition(pomx, pomy);
	}
	else if (znakpom == "P12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P12.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc1.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];

		E1.Pc2.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc3.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc4.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc5.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc6.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc7.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc8.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc9.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc10.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc11.setPosition(pomx, pomy);
	}
	else if (znakpom == "Pc12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc12.setPosition(pomx, pomy);
	}
}

void Arena::Wyczysc_Pole(int xk, int yk, Ekran &E1)
{
	string znakpom;
	int pomx, pomy;

	znakpom = znaki[xk][yk];

	if (znakpom == "P1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P1.setTexture(E1.Pole);
	}
	else if (znakpom == "P2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P2.setTexture(E1.Pole);
	}
	else if (znakpom == "P3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P3.setTexture(E1.Pole);
	}
	else if (znakpom == "P4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P4.setTexture(E1.Pole);
	}
	else if (znakpom == "P5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P5.setTexture(E1.Pole);
	}
	else if (znakpom == "P6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P6.setTexture(E1.Pole);
	}
	else if (znakpom == "P7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P7.setTexture(E1.Pole);
	}
	else if (znakpom == "P8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P8.setTexture(E1.Pole);
	}
	else if (znakpom == "P9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P9.setTexture(E1.Pole);
	}
	else if (znakpom == "P10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P10.setTexture(E1.Pole);
	}
	else if (znakpom == "P11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P11.setTexture(E1.Pole);
	}
	else if (znakpom == "P12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P12.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc1")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc1.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc2")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc2.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc3")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc3.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc4")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc4.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc5")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc5.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc6")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc6.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc7")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc7.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc8")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc8.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc9")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc9.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc10")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc10.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc11")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc11.setTexture(E1.Pole);
	}
	else if (znakpom == "Pc12")
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc12.setTexture(E1.Pole);
	}
}

void Arena::Zamien_SFML(int xk, int yk, Ekran& E1)
{
	string znakpom;
	int pomx, pomy;

	znakpom = znaki[xk][yk];

	if (wagi[xk][yk] == 1 && znakpom == "P1" && xk==7)
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P1.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P2" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P2.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P3" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P3.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P4" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P4.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P5" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P5.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P6" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P6.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P7" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P7.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P8" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P8.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P9" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P9.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P10" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P10.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P11" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P11.setTexture(E1.DamkaB);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "P12" && xk == 7))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.P12.setTexture(E1.DamkaB);
	}
	
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc1" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc1.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc2" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc2.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc3" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc3.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc4" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc4.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc5" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc5.setTexture(E1.DamkaC);
	}
	else if (wagi[xk][yk] == 1 && znakpom == "Pc6" && xk == 0)
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc6.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc7" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc7.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc8" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc8.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc9" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc9.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc10" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc10.setTexture(E1.DamkaC);
	}
	else if (wagi[xk][yk] == 1 && znakpom == "Pc11" && xk == 0)
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc11.setTexture(E1.DamkaC);
	}
	else if ((wagi[xk][yk] == 1 && znakpom == "Pc12" && xk == 0))
	{
		pomx = Tab_Rozx[xk][yk];
		pomy = Tab_Rozy[xk][yk];
		E1.Pc12.setTexture(E1.DamkaC);
	}
}



#endif // !PLANSZA_H

#pragma once
