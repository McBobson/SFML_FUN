#ifndef ARENA_H
#define ARENA_H
#include "pch.h"

using namespace std;

class Arena{

public:

	char **tablica;
	int **wagi;
	int pom[2];
	

	Arena();
	Arena(int);
	~Arena();

	int Przesun_Pionek(int,int,int,int,int);
	bool Czy_Jest_Pionek(int,int);
	bool Czy_Jest_W_Arenie(int,int);
	int Kierunek_Bicia(int[]);
	bool Bicie(int, int,int[]);
	bool Bicie_Damka(int, int, int[]);
	void Zamien(char, int, int);
	bool Czy_Prawidlowy_Ruch(int[],char);
	bool Czy_Przyjaciel(char, char);
	bool Czy_Mozliwe_Bicie(int, int);
	bool Czy_Mozliwe_Bicie_Damka(int, int);
	bool Czy_Przyjaciel_Damki(int, int, int, int);
	bool Czy_Ruch_W_Tyl(int[], char);

	void Ekran_Koncowy(int,int,int);

	int Czy_Mozliwe_Bicie_AI(int, int, int, int);


};

Arena::Arena()
{
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

	for (int i = 0; i < 3; i+=2)
	{
		for (int j = 0; j < 8; j+=2)
		{
			tablica[i][j] = 'x';
			wagi[i][j] = 1;
		}
	}

	for (int i = 1; i < 8; i+=2)
	{
		tablica[1][i] = 'x';
		wagi[1][i] = 1;
	}

	
	for (int i = 5; i < 8; i += 2)
	{
		for (int j = 1; j < 8; j += 2)
		{
			tablica[i][j] = 'o';
			wagi[i][j] = 1;
		}
	}

	for (int i = 0; i < 8; i += 2)
	{
		tablica[6][i] = 'o';
		wagi[6][i] = 1;
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
	tablica[6][6] = 'x';
	tablica[7][3] = 'o';
	tablica[7][7] = 'o';
	tablica[2][6] = 'x';

	
	//tablica[4][4] = 'x';
	//tablica[4][4] = 'O';

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
	if (tablica[x][y]!=' ')
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

bool Arena::Czy_Prawidlowy_Ruch(int pom[],char znak)
{
	if ((abs(pom[0])==1 && abs(pom[1])==1 && (znak=='x' || znak=='o')) || ((abs(pom[0]) == abs(pom[1]) && (znak=='X' || znak=='O'))))
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
	int LUp[2] = {-1,-1}; 
	int RUp[2] = {-1,1};
	int RDown[2] = {1,1};
	int LDown[2] = {1,-1};
	
	if (Czy_Jest_W_Arenie(x - 1, y - 1) && x-1!=7 && x-1 != 0 && y-1!=7 && y-1!=0)
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

bool Arena::Czy_Mozliwe_Bicie_Damka(int x1, int y1)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };

	int x=x1, y=y1;

	while (x != 7 && x!= 0 && y != 7 &&  y!= 0 && !Czy_Jest_Pionek(x + LUp[0], y + LUp[1]))
	{
		x += LUp[0];
		y += LUp[1];
	}
	if (x + LUp[0] != 7 && x + LUp[0] != 0 && y + LUp[1] != 7 && y + LUp[1] != 0 && Czy_Jest_W_Arenie(x+LUp[0],y+LUp[1]) && !Czy_Jest_Pionek(x+LUp[0]-1,y+LUp[1]-1))
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

int Arena::Przesun_Pionek(int x1,int y1,int x2,int y2, int gracz)
{
	pom[0] = x2 - x1;
	pom[1] = y2 - y1;

	if ((tablica[x1][y1] == 'o' && gracz == 1) || (tablica[x1][y1] == 'x' && gracz == 2) || (tablica[x1][y1] == 'O' && gracz == 1) || (tablica[x1][y1] == 'X' && gracz == 2)) // Czy prawid�owy warcab dla gracza
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
			else if(Czy_Ruch_W_Tyl(pom, tablica[x1][y1]))
			{
				tablica[x2][y2] = tablica[x1][y1];
				tablica[x1][y1] = ' ';

				wagi[x2][y2] = wagi[x1][y1];
				wagi[x1][y1] = 0;

				Zamien(tablica[x2][y2], x2, y2);
				return 0;
			}
			else cout << "Nie uciekamy z frontu!!!" << endl;

		}
		else
		{
			cout << "Kody b�edu: " << endl;
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

void Arena::Ekran_Koncowy(int punkty1, int punkty2,int gracz)
{
	system("cls");

	cout << endl;
	cout << "-------------------------------------------------------------------------------------------"<<endl;
	cout << "                                        " << "Gratulacje dla gracza: " << gracz << endl;
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
			wyjscie << "|  "<< A.tablica[0][i] <<"  ";
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

	wyjscie << "|  "<<"1";

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
		wyjscie <<"    ";

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
		wyjscie <<"    ";

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
		wyjscie <<"    ";

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
		wyjscie <<"    ";

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


		for (int i = 65; i < 65+8; i++)
		{
			wyjscie << (char)i << "     ";
		}
		
	}

	
	return wyjscie;
}





int Arena::Czy_Mozliwe_Bicie_AI(int x, int y, int xzabr, int yzabr)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };


	if (Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x-1!=xzabr || y-1 != yzabr))
	{
		//cout << "Bicie lewo gora" << endl;
		//cout << x << " " << y << endl;
		if (Bicie(x - 1, y - 1, LUp))
		{
			//cout << "Tak1" << endl;
			//system("pause");
			return 0;
		}
	}

	if (Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x - 1 != xzabr || y + 1 != yzabr))
	{
		//cout << "Bicie prawo gora" << endl;
		if (Bicie(x - 1, y + 1, RUp))
		{
			//cout << "Tak2" << endl;
			//system("pause");
			return 1;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x + 1 != xzabr || y + 1 != yzabr))
	{
		//cout << "Bicie prawo dol" << endl;
		if (Bicie(x + 1, y + 1, RDown))
		{
			//cout << "Tak3" << endl;
			//system("pause");
			return 3;
		}
	}

	if (Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x + 1 != xzabr || y - 1 != yzabr))
	{
		//cout << "Bicie lewo dol" << endl;
		if (Bicie(x + 1, y - 1, LDown))
		{
			//cout << "Tak4" << endl;
			//system("pause");
			return 2;
		}
	}

	return -1;
}


#endif // !PLANSZA_H

