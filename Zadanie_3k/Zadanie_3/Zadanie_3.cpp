#include "pch.h"
#include "Arena.h"
#include "AI.h"

using namespace std;


// WPROWADZANIE POLOZENIA W FORMACIE (X)(Y) GDZIE DO FUNKCJI OPERUJACYCH NA TABLICACH WYSYLAMY -> (Y)(X) - ZAMIANA OSI

int main()
{
	srand(time(NULL));
	Arena A;
	AI AI;

	cout << A;

	cout << endl;
	for (int i = 0; i < ROZ; i++)
	{
		for (int j = 0; j < ROZ; j++)
		{
			cout << AI.tablicaWagRuchow[i][j] << ' ';
		}
		cout << endl;
	}

	char warcab[2] = { 'O','X' };

	int pom[2];
	int gracz=1;
	int g;
	int q = 0;
	//cout << endl << "Gracz 1 -> O" << endl << "Gracz 2 -> X" << endl;
	//cout << "Wybierz swojego championa: ";
	//cin >> gracz;
	g = gracz;
	int punkty1 = 0, punkty2 = 0;

	char y1, y2;
	//char a, b;
	int x1, x2;

	/*
	while(true)
	{
		gracz = g;
		//system("cls");

		//cout << A << endl;

		//cout << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;

		//cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
		
		char y1, y2;
		char a, b;
		int a1, b1;
		int x1, x2;

		
		//cin >> a >> y1 >> b >> y2;
		//pom[0] = ((int)b - 65) - ((int)a - 65);
		//pom[1] = y2 - y1;
		//A.Przesun_Pionek((int)a - 65, y1, (int)b - 65, y2, gracz);
		
		
		int bicie = 0;
		do
		{
			system("cls");

			cout << A << endl;

			cout << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;

			if (bicie < 1)
			{
				cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
				cin >> y1 >> x1 >> y2 >> x2;
				pom[1] = ((int)y2 - 65) - ((int)y1 - 65);
				pom[0] = x2 - x1;
				a1 = (int)y1 - 65;

			}
			else
			{
				cout << a1 << " " << x1 << endl;
				cout << gracz<<endl;
				cout << "Podaj pionka do zbicia" << endl;
				cin >> y2 >> x2;
				pom[1] = ((int)y2 - 65) - a1;
				pom[0] = x2 - x1;
			}
			//cout << "przed switch" << endl;

			if (A.Przesun_Pionek(x1, a1, x2, (int)y2 - 65, gracz)==1)
			{
				//cout << "switch" << endl;
				//cout << A.Kierunek_Bicia(pom)<<endl;
				switch (A.Kierunek_Bicia(pom))
				{
				case 0:
				{
					pom[1] = ((int)y2 - 65) - (a1) - 1;
					pom[0] = x2 - x1 - 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 1:
				{
					pom[1] = ((int)y2 - 65) - (a1)+1;
					pom[0] = x2 - x1 - 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 2:
				{
					pom[1] = ((int)y2 - 65) - (a1)-1;
					pom[0] = x2 - x1 + 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 3:
				{
					pom[1] = ((int)y2 - 65) - (a1)+1;
					pom[0] = x2 - x1 + 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;
				}

				bicie++;
				punkty1++;
				a1 = a1 + pom[1];
				x1 = x1 + pom[0];

				//cout << y1 << " " << a1 << endl;

				//cout << "Bicie" << endl;
			}
			else
			{
				//cout << "NieBicie" << endl;
				pom[0] = 0;
				pom[1] = 0;
				break;
			}

			//cout << (int)a - 65 + pom[1] << " " << y1 + pom[0];
			//A.Czy_Mozliwe_Bicie(y1 + pom[0], (int)a - 65 + pom[1]);
			//system("pause");

			
			//cout << y1 << " " << a1 << endl;
			//cout << (int)a - 65 + pom[1] << " " << a1 << endl;
			//cout << y1 + pom[0] << " "<<y1<<endl;
			//cout << y1<< " " << a1<<endl;
			//A.Czy_Mozliwe_Bicie(y1, a1);
			//system("pause");

			//A.Czy_Mozliwe_Bicie(y1, a1);
			//A.Czy_Mozliwe_Bicie_Damka(y1, a1);
			//system("pause");

		} while (bicie>0 && (A.Czy_Mozliwe_Bicie(x1, a1) || A.Czy_Mozliwe_Bicie_Damka(x1,a1)));

		if (punkty1 == 12) break;
		
		//system("Pause");
		//system("cls");
		//cout << A;
		
		if (gracz == 2) gracz--;
		else gracz++;

		cout << endl;

		//cout << "TURA GRACZA " << gracz <<" -> " << warcab[gracz-1] << endl;

		//cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;

		//cin >> a >> y1 >> b >> y2;

		//A.Przesun_Pionek((int)a - 65, y1, (int)b - 65, y2, gracz);

		bicie = 0;
		do
		{
			system("cls");

			cout << A << endl;

			cout << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;

			if (bicie < 1)
			{
				cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
				cin >> y1 >> x1 >> y2 >> x2;
				pom[1] = ((int)y2 - 65) - ((int)y1 - 65);
				pom[0] = x2 - x1;
				a1 = (int)y1 - 65;

			}
			else
			{
				cout << a1 << " " << x1 << endl;
				cout << gracz << endl;
				cout << "Podaj pionka do zbicia" << endl;
				cin >> y2 >> x2;
				pom[1] = ((int)y2 - 65) - a1;
				pom[0] = x2 - x1;
			}
			//cout << "przed switch" << endl;

			if (A.Przesun_Pionek(x1, a1, x2, (int)y2 - 65, gracz) == 1)
			{
				//cout << "switch" << endl;
				//cout << A.Kierunek_Bicia(pom)<<endl;
				switch (A.Kierunek_Bicia(pom))
				{
				case 0:
				{
					pom[1] = ((int)y2 - 65) - (a1)-1;
					pom[0] = x2 - x1 - 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 1:
				{
					pom[1] = ((int)y2 - 65) - (a1)+1;
					pom[0] = x2 - x1 - 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 2:
				{
					pom[1] = ((int)y2 - 65) - (a1)-1;
					pom[0] = x2 - x1 + 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;

				case 3:
				{
					pom[1] = ((int)y2 - 65) - (a1)+1;
					pom[0] = x2 - x1 + 1;
					//cout<<pom[0]<<" "<<pom[1]<<endl;
				}
				break;
				}

				bicie++;
				punkty1++;
				a1 = a1 + pom[1];
				x1 = x1 + pom[0];

				//cout << y1 << " " << a1 << endl;

				//cout << "Bicie" << endl;
			}
			else
			{
				//cout << "NieBicie" << endl;
				pom[0] = 0;
				pom[1] = 0;
				break;
			}

			//cout << (int)a - 65 + pom[1] << " " << y1 + pom[0];
			//A.Czy_Mozliwe_Bicie(y1 + pom[0], (int)a - 65 + pom[1]);
			//system("pause");


			//cout << y1 << " " << a1 << endl;
			//cout << (int)a - 65 + pom[1] << " " << a1 << endl;
			//cout << y1 + pom[0] << " "<<y1<<endl;
			//cout << y1<< " " << a1<<endl;
			//A.Czy_Mozliwe_Bicie(y1, a1);
			//system("pause");

			//A.Czy_Mozliwe_Bicie(y1, a1);
			//A.Czy_Mozliwe_Bicie_Damka(y1, a1);
			//system("pause");

		} while (bicie > 0 && (A.Czy_Mozliwe_Bicie(x1, a1) || A.Czy_Mozliwe_Bicie_Damka(x1, a1)));

		if (punkty2 == 12) break;

		system("Pause");
		system("cls");
		cout << A;
	}
	
	A.Ekran_Koncowy(punkty1, punkty2, gracz);
	*/
	
//A.Czy_Mozliwe_Bicie_Damka(4, 4);

//cout << A.Czy_Mozliwe_Bicie_AI(5, 5);
//cout<<endl<<AI.Ilosc_Bic(7,7,A);
//A.Czy_Mozliwe_Bicie(5, 5);

vector<int> Kek(4);
//system("pause");
//Kek=AI.Koncowy_Ruch(A);

system("cls");

//A.Przesun_Pionek(Kek[1], Kek[0], Kek[3], Kek[2], 2);
//cout << A;

/*
for (int i = 0; i < ROZ; i++)
{
	for (int j = 0; j < ROZ; j++)
	{
		cout<<AI.tablicaWagRuchow[i][j] <<' ';
	}
	cout << endl;
}*/

while (1)
{
	gracz = 1;

	system("cls");

	cout << A << endl;

	cout << "TURA GRACZA " << gracz << " -> " << warcab[gracz - 1] << endl;

	cout << "PODAJ POLOZENIE PIONKA DO PRZESUNIECIA I TO GDZIE CHCESZ GO PRZESUNAC" << endl;
	cin >> y1 >> x1 >> y2 >> x2;
	pom[1] = ((int)y2 - 65) - ((int)y1 - 65);
	pom[0] = x2 - x1;
	cout << pom[1] << " " << pom[0] << endl;
	A.Przesun_Pionek(x1, (int)y1 - 65, x2, (int)y2-65, gracz);

	system("cls");
	cout << A;
	system("pause");

	gracz++;

	AI.Koncowy_Ruch(A);
	A.Przesun_Pionek(AI.TabKoniec[0], AI.TabKoniec[1], AI.TabKoniec[2], AI.TabKoniec[3], gracz);

	system("cls");
	cout << A;
	system("pause");
	gracz--;

}


//cout << endl << endl;

//cout << AI.Ilosc_Bic(1, 1, A);


}
