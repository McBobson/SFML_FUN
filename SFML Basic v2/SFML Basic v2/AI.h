#ifndef AI_H
#define AI_H

#include "Arena_SFML.h"

using namespace std;


class AI
{
	int pom[2], bicia;
	int TabRuch[3], TabBicie[3];
	int punkty = 0;
	int PozycjaTymczasowa[2];
	bool Atak = false;
	int WzorzecWag[ROZ][ROZ];
	//int tablicaWagRuchow[ROZ][ROZ]; 

public:
	int TabKoniec[4];
	int tablicaWagRuchow[ROZ][ROZ];
	int waga = 0;
	//vector<int> dane1;
	//vector<int> dane2;

	AI()
	{
		int wag = 1;
		for (int i = 0; i < ROZ; i++)
		{
			for (int j = 0; j < (ROZ / 2); j++)
			{
				tablicaWagRuchow[i][j] = i + wag;
				wag++;
			}
			wag--;
			for (int j = ROZ / 2; j < ROZ; j++)
			{

				tablicaWagRuchow[i][j] = i + wag;
				wag--;
			}
		}

		for (int i = 0; i < ROZ; i++)
		{
			for (int j = 0; j < ROZ; j++)
			{
				tablicaWagRuchow[i][j] += i;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			TabRuch[i] = 0;
			TabBicie[i] = 0;
			TabKoniec[i] = 0;
		}
		TabKoniec[3] = 0;

		for (int i = 0; i < ROZ; i++)
		{
			for (int j = 0; j < ROZ; j++)
			{
				WzorzecWag[i][j] = tablicaWagRuchow[i][j];
			}
		}
	}

	int Zwroc_Punkty()
	{
		return punkty;
	}

	int Ilosc_Bic(int, int, Arena&);

	int Mozliwy_Ruch_AI(int, int, Arena&);

	int Mozliwe_Bicie_AI(int, int, Arena&);

	int Czy_Mozliwe_Bicie_AI(int, int, int, int, Arena&);

	void Czy_Pod_Atakiem(int, int, Arena&);

	void Nie_Podkladaj_Sie(int, int, Arena&);

	void Koncowy_Ruch(Arena&);

};

int AI::Ilosc_Bic(int xp, int yp, Arena &A)
{
	bicia = 0;
	int xk, yk;
	//cout << yp << " " << xp << endl;

	int lastx = -5, lasty = -5;

	while (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) != -1)
	{
		//cout<<"LASAGNA"<<endl;
		//cout << A.Czy_Mozliwe_Bicie_AI(yp, xp);
		//cout << lasty<< " " << lastx << endl;
		//cout << A.Czy_Mozliwe_Bicie_AI(yp, xp, lasty, lastx) << endl;

		if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 0)
		{
			cout << "lg";
			xk = xp - 1;
			yk = yp - 1;

		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 1)
		{
			cout << "pg";
			xk = xp + 1;
			yk = yp - 1;
		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 2)
		{
			cout << "ld";
			xk = xp - 1;
			yk = yp + 1;
		}
		else if (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A) == 3)
		{
			cout << "pd";
			xk = xp + 1;
			yk = yp + 1;
		}



		switch (Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty,A))
		{
		case 0:
		{
			//cout << "Bicie lewoooo" << endl;
			pom[1] = yk - yp - 1;
			pom[0] = xk - xp - 1;
			//cout<<pom[0]<<" "<<pom[1]<<endl;
		}
		break;

		case 1:
		{
			//cout << "Bicie pewoooo" << endl;
			pom[1] = yk - yp + 1;
			pom[0] = xk - xp - 1;
			//cout<<pom[0]<<" "<<pom[1]<<endl;
		}
		break;

		case 2:
		{
			//cout << "Bicie praewoooo" << endl;
			pom[1] = yk - yp - 1;
			pom[0] = xk - xp + 1;
			//cout<<pom[0]<<" "<<pom[1]<<endl;
		}
		break;

		case 3:
		{
			//cout << "Bicie lelelwoooo" << endl;
			pom[1] = yk - yp + 1;
			pom[0] = xk - xp + 1;
			//cout<<pom[0]<<" "<<pom[1]<<endl;
		}
		break;
		}

		if (xk == lastx && yk == lasty)
		{
			cout << "Zatrzymany przez breake" << endl;
			break;
		}

		lastx = xk;
		lasty = yk;

		xp = xp + pom[0];
		yp = yp + pom[1];
		bicia++;

		//cout << endl << yk << " XXX " << xk << endl;

		//cout << endl<<yp << " " << xp << endl;
		//system("pause");

	}
	cout << "Koniec while" << endl;

	return bicia;
}

int AI::Mozliwy_Ruch_AI(int xp, int yp, Arena &A)
{
	int pom2[2];
	int wagakoncowa = 0;
	//vector<int> dane(3);

	//cout << "WAGA JIBCIWA " << endl;
	//cout << TabRuch[2] << endl;

	if (A.Czy_Jest_W_Arenie(xp + 1, yp + 1) && !A.Czy_Jest_Pionek(xp + 1, yp + 1))
	{
		//cout << "Ruch prawo dol" << endl;
		pom2[0] = 1;
		pom2[1] = 1;
		if (A.Czy_Prawidlowy_Ruch(pom2, A.tablica[xp][yp]))
		{
			wagakoncowa = tablicaWagRuchow[xp + 1][yp + 1];
			TabRuch[0] = xp + 1;
			TabRuch[1] = yp + 1;
			TabRuch[2] = wagakoncowa;
			//cout << "Prawo dol" << " ";
			//cout << wagakoncowa << endl << endl;
		}
		//else cout << "NO chyba nie" << endl;
	}
	//else cout << "Poza arena" << endl;

	pom2[0] = 1;
	pom2[1] = -1;
	if (A.Czy_Jest_W_Arenie(xp + 1, yp - 1) && !A.Czy_Jest_Pionek(xp + 1, yp - 1))
	{
		//cout << "Ruch lewo dol" << endl;
		if (A.Czy_Prawidlowy_Ruch(pom2, A.tablica[xp][yp]))
		{
			if (wagakoncowa < tablicaWagRuchow[xp + 1][yp - 1])
			{
				wagakoncowa = tablicaWagRuchow[xp + 1][yp - 1];
				TabRuch[0] = xp + 1;
				TabRuch[1] = yp - 1;
				TabRuch[2] = wagakoncowa;
				//cout << "Lewo dol" << " ";
				//cout << wagakoncowa << endl << endl;
			}
		}
		//else cout << "No nie" << endl;
	}
	//else cout << "Nie w arenia" << endl;

	//system("pause");

	//cout << wagakoncowa << endl;

	return wagakoncowa;
}

int AI::Mozliwe_Bicie_AI(int xp, int yp, Arena &A)
{
	int wagakoncowa = 0;

	switch (Czy_Mozliwe_Bicie_AI(xp, yp, xp, yp,A))
	{
	case 0:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 100;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 1:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 100;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp + 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 2:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 100;
		TabBicie[0] = xp + 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 3:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 100;
		TabBicie[0] = xp + 1;
		TabBicie[1] = yp + 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case -1:
	{
		wagakoncowa = -1;
		TabBicie[0] = xp;
		TabBicie[1] = yp;
		TabBicie[2] = wagakoncowa;
	}
	break;
	}

	return wagakoncowa;


}

void AI::Koncowy_Ruch(Arena &A)
{
	waga = 0;
	for (int i = ROZ-1; i >= 0; i--)
	{
		for (int j = ROZ-1; j >= 0; j--)
		{
			if (A.tablica[i][j] == 'x')
			{
				Nie_Podkladaj_Sie(i, j, A);
				Czy_Pod_Atakiem(i, j, A);
				

				//int radom = rand() % 10 + 1;
				if (waga < Mozliwy_Ruch_AI(i, j, A)) // || (waga==Mozliwy_Ruch_AI(i,j,A) && radom<5)
				{
					waga = TabRuch[2];
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabRuch[0];
					TabKoniec[3] = TabRuch[1];
				}

				if (waga < Mozliwe_Bicie_AI(i, j, A))
				{
					//cout << "W IF" << endl;
					//system("pause");

					waga = TabBicie[2];
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabBicie[0];
					TabKoniec[3] = TabBicie[1];

					punkty++; // Na razie bicie ma najwieksza wage wiec zawsze jak tu wejdziemy bedzie cos sie bilo

				}

			}

			TabRuch[0] = 0;
			TabRuch[1] = 0;
			TabRuch[2] = 0;

			TabBicie[0] = 0;
			TabBicie[1] = 0;
			TabBicie[2] = 0;

		}
	}

	
	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			//cout << tablicaWagRuchow[i][j] << " ";
			tablicaWagRuchow[i][j] = WzorzecWag[i][j];
			//cout << tablicaWagRuchow[i][j] << " ";
		}
		//cout << endl;
	}
	//system("pause");

}

int AI::Czy_Mozliwe_Bicie_AI(int x, int y, int xzabr, int yzabr,Arena &A)
{
	int LUp[2] = { -1,-1 };
	int RUp[2] = { -1,1 };
	int RDown[2] = { 1,1 };
	int LDown[2] = { 1,-1 };


	if (A.Czy_Jest_W_Arenie(x - 1, y - 1) && x - 1 != 7 && x - 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x - 1 != xzabr || y - 1 != yzabr))
	{
		//cout << "Bicie lewo gora" << endl;
		//cout << x << " " << y << endl;
		if (A.Bicie(x - 1, y - 1, LUp))
		{
			//cout << "Tak1" << endl;
			//system("pause");
			return 0;
		}
	}

	if (A.Czy_Jest_W_Arenie(x - 1, y + 1) && x - 1 != 7 && x - 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x - 1 != xzabr || y + 1 != yzabr))
	{
		//cout << "Bicie prawo gora" << endl;
		if (A.Bicie(x - 1, y + 1, RUp))
		{
			//cout << "Tak2" << endl;
			//system("pause");
			return 1;
		}
	}

	if (A.Czy_Jest_W_Arenie(x + 1, y + 1) && x + 1 != 7 && x + 1 != 0 && y + 1 != 7 && y + 1 != 0 && (x + 1 != xzabr || y + 1 != yzabr))
	{
		//cout << "Bicie prawo dol" << endl;
		if (A.Bicie(x + 1, y + 1, RDown))
		{
			//cout << "Tak3" << endl;
			//system("pause");
			return 3;
		}
	}

	if (A.Czy_Jest_W_Arenie(x + 1, y - 1) && x + 1 != 7 && x + 1 != 0 && y - 1 != 7 && y - 1 != 0 && (x + 1 != xzabr || y - 1 != yzabr))
	{
		//cout << "Bicie lewo dol" << endl;
		if (A.Bicie(x + 1, y - 1, LDown))
		{
			//cout << "Tak4" << endl;
			//system("pause");
			return 2;
		}
	}

	return -1;
}

void AI::Czy_Pod_Atakiem(int xp, int yp, Arena &A)
{
	Atak = false;

	if (A.Czy_Jest_W_Arenie(xp + 1, yp + 1) && xp != 7 && xp != 0 && yp != 7 && yp != 0)
	{
		if ((A.tablica[xp + 1][yp + 1] == 'o' || A.tablica[xp + 1][yp + 1] == 'O') && !A.Czy_Jest_Pionek(xp - 1, yp - 1))
		{
			//cout << "ATAKUJO" << endl;
			//system("pause");
			tablicaWagRuchow[xp - 1][yp - 1] += 50;
			Atak = true;
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1, yp - 1) && xp != 7 && xp != 0 && yp != 7 && yp != 0)
	{
		if ((A.tablica[xp + 1][yp - 1] == 'o' || A.tablica[xp + 1][yp - 1] == 'O') && !A.Czy_Jest_Pionek(xp - 1, yp + 1))
		{
			//cout << "ATAKUJO2" << endl;
			//system("pause");
			tablicaWagRuchow[xp - 1][yp + 1] += 50;
			Atak = true;
		}
	}
}

void AI::Nie_Podkladaj_Sie(int xp, int yp, Arena &A)
{
	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp + 1 + 1))
	{
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp + 1 + 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp],A.tablica[xp+1+1][yp+1+1]))
		{
			tablicaWagRuchow[xp + 1][yp + 1] = 1;
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp + 1 - 1))
	{
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp + 1 - 1) && !A.Czy_Jest_W_Arenie(xp + 1 - 1, yp + 1 + 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp + 1 - 1]))
		{
			if (!A.Czy_Jest_Pionek(xp + 1 - 1, yp + 1 + 1))
			{
				tablicaWagRuchow[xp + 1][yp + 1] = 1;
			}
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp - 1 - 1))
	{
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp - 1 - 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp - 1 - 1]))
		{
			tablicaWagRuchow[xp + 1][yp - 1] = 1;
		}
	}

	if (A.Czy_Jest_W_Arenie(xp + 1 + 1, yp - 1 + 1))
	{
		if (A.Czy_Jest_Pionek(xp + 1 + 1, yp - 1 + 1) && !A.Czy_Jest_W_Arenie(xp + 1 - 1, yp - 1 - 1) && !A.Czy_Przyjaciel(A.tablica[xp][yp], A.tablica[xp + 1 + 1][yp - 1 + 1]))
		{
			if (!A.Czy_Jest_Pionek(xp + 1 - 1, yp - 1 - 1))
			{
				tablicaWagRuchow[xp + 1][yp - 1] = 1;
			}
		}
	}


}













#endif AI_H

