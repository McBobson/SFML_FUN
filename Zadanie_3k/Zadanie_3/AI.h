#ifndef AI_H
#define AI_H

#include "pch.h"
#include "Arena.h"
#include <vector>

using namespace std;


class AI
{
	int pom[2],bicia;
	//int tablicaWagRuchow[ROZ][ROZ]; 
	
public:
	int TabRuch[3],TabBicie[3],TabKoniec[4];
	int tablicaWagRuchow[ROZ][ROZ];
	int waga = 0;
	//vector<int> dane1;
	//vector<int> dane2;

	AI()
	{
		int wag = 1;
		for (int i = 0; i < ROZ; i++)
		{
			for (int j = 0; j < (ROZ/2); j++)
			{
				tablicaWagRuchow[i][j] = i+wag;
				wag++;
			}
			wag--;
			for (int j = ROZ/2; j < ROZ; j++)
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
	}

	int Ilosc_Bic(int,int,Arena&);

	int Mozliwy_Ruch_AI(int, int, Arena&);

	int Mozliwe_Bicie_AI(int, int, Arena&);

	void Koncowy_Ruch(Arena&);

};

int AI::Ilosc_Bic(int xp,int yp,Arena &A)
{
	bicia = 0;
	int xk, yk;
	//cout << yp << " " << xp << endl;

	int lastx=-5, lasty=-5;

	while (A.Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty) != -1)
	{	
		//cout<<"LASAGNA"<<endl;
		//cout << A.Czy_Mozliwe_Bicie_AI(yp, xp);
		//cout << lasty<< " " << lastx << endl;
		//cout << A.Czy_Mozliwe_Bicie_AI(yp, xp, lasty, lastx) << endl;

		if (A.Czy_Mozliwe_Bicie_AI(xp, yp,lastx, lasty) == 0)
		{
			cout << "lg";
			xk = xp - 1;
			yk = yp - 1;
			
		}
		else if (A.Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty) == 1)
		{
			cout << "pg";
			xk = xp + 1;
			yk = yp - 1;
		}
		else if (A.Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty) == 2)
		{
			cout << "ld";
			xk = xp - 1;
			yk = yp + 1;
		}
		else if (A.Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty) == 3)
		{
			cout << "pd";
			xk = xp + 1;
			yk = yp + 1;
		}



		switch (A.Czy_Mozliwe_Bicie_AI(xp, yp, lastx, lasty))
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
	int wagakoncowa=0;
	//vector<int> dane(3);

	cout << "WAGA JIBCIWA " << endl;
	cout << TabRuch[2] << endl;

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

	cout << wagakoncowa << endl;

	return wagakoncowa;
}

int AI::Mozliwe_Bicie_AI(int xp, int yp, Arena &A)
{
	int wagakoncowa = 0;

	switch (A.Czy_Mozliwe_Bicie_AI(xp, yp, xp, yp))
	{
	case 0:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 50;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 1:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 50;
		TabBicie[0] = xp - 1;
		TabBicie[1] = yp + 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 2:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 50;
		TabBicie[0] = xp + 1;
		TabBicie[1] = yp - 1;
		TabBicie[2] = wagakoncowa;
	}
	break;

	case 3:
	{
		//cout << "Tak3" << endl;
		//system("pause");
		wagakoncowa = 50;
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
	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			if (A.tablica[i][j] == 'x')
			{
				//int radom = rand() % 10 + 1;
				if (waga < Mozliwy_Ruch_AI(i, j, A)) // || (waga==Mozliwy_Ruch_AI(i,j,A) && radom<5)
				{
					//cout << "KORONA KIELCE GOWNO WIDELCE" << endl;
					waga = TabRuch[2];
					//Wynik.push_back(i);
					//Wynik.push_back(j);
					//Wynik.push_back(Mozliwy_Ruch_AI(i, j, A)[0]);
					//Wynik.push_back(Mozliwy_Ruch_AI(i, j, A)[1]);
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabRuch[0];
					TabKoniec[3] = TabRuch[1];

					//TabRuch[0] = 0;
					//TabRuch[1] = 0;
					//TabRuch[2] = 0;
				}

				// Czy jest bicie i jego waga

				//cout << "SPRAWDZANIE WAG PRZED IFEM" << endl;
				//cout << Mozliwe_Bicie_AI(i,j,A) << endl;
				//system("pause");
			
				//cout << "WAGA AKTUALNA" << endl;
				//cout << waga << endl;
				//system("pause");


				if (waga < Mozliwe_Bicie_AI(i, j, A))
				{
					//cout << "W IF" << endl;
					//system("pause");

					waga = TabBicie[2];
					TabKoniec[0] = i;
					TabKoniec[1] = j;
					TabKoniec[2] = TabBicie[0];
					TabKoniec[3] = TabBicie[1];

					//TabBicie[0] = 0;
					//TabBicie[1] = 0;
					//TabBicie[2] = 0;

					//cout << TabKoniec[0] << " " << TabKoniec[1] << endl;
					//cout << TabKoniec[2] << " " << TabKoniec[3] << endl;
					//system("pause");
				}


				cout << waga << endl;
				system("pause");
			}

			TabRuch[0] = 0;
			TabRuch[1] = 0;
			TabRuch[2] = 0;

			TabBicie[0] = 0;
			TabBicie[1] = 0;
			TabBicie[2] = 0;
		}
	}

}













#endif AI_H

