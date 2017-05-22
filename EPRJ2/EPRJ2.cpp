#include "Konfiguration.h"
#include <conio.h>
#include <ctime>
#include <thread>


bool slut = false;

void Menu() {

	//Opsætning

	time_t t = time(0);
	struct tm * now = localtime(&t);

	string sys;
	int Baud;
	int CPort;
	char c = 'j';

	int enha;
	string enhn;
	char enht;
	int enhhr;
	int enhm;
	int tjek;

	string slettes;

	//Start. Her skrives navne på systemet
	cout << "Velkommen, indtast navn pa system" << endl;
	cin >> sys;
	cout << "Indtast COM-port på master" << endl;
	cin >> CPort;
	cout << "Indtast Baud-rate på master" << endl;
	cin >> Baud;
	
	//Opret en konfiguration udfra det indtastede navn
	Konfiguration konf(sys, CPort, Baud);
	konf.Opdater();
	system("pause");


	//Hovedmenu hvorpå valg foretages. Opstillet som Switch-statement. Q/q lukker programmet
	while (c != 'q')
	{
		system("CLS");
		cout << sys << "\n\n" << endl;
		cout << "O for at oprette ny enhed:\nS for at slette en enhed:\nG for at gemme enhederne:\nA for at afvikle en enhed manuelt:\nT list alle enheder der er tændte:\nP for at printe:\n" << endl;



		cin >> c;
		switch (c)
		{

			//Opret ny Enhed
		case 'o':
		case 'O':
			cout << "Enhedens adresse: " << endl;
			cin >> enha;
			cout << "Enhedens navn: " << endl;
			cin >> enhn;
			cout << "Enhedens type: " << endl;
			cin >> enht;
			cout << "Enhedens automatiske tidsindstilling: \nTimer:" << endl;
			cin >> enhhr;
			cout << "Minutter:" << endl;
			cin >> enhm;
			konf += Enhed(enha, enhn, enht, enhhr, enhm);
			cout << "Enheden er gemt!" << endl;
			system("pause");
			break;

			//Slet en enhed
		case's':
		case'S':
			cout << "Enhedens navn: " << endl;
			cin >> slettes;
			konf -= (slettes);
			cout << "Enheden er slettet!" << endl;
			system("pause");
			break;

			//Gem alle oprettede enheder
		case 'g':
		case 'G':
			konf.Gem();
			cout << "Alle enheder blev gemt";
			system("pause");
			break;

			//Afvikl en enhed manuelt
		case 'a':
		case 'A':
			char nummer;
			int nnr;

			//Enheds ID
			cout << "Skriv adressen på enheden du vil afvikle : " << endl;
			cin >> nummer;

			//Opret forbindelse til Arduino og sender ID som char hvis enheden findes
			nnr = nummer - '0';
			

			if (konf.Findes(nnr) == true) {
				konf.Afvikl(nummer);
				
				break;
			}
			else if (konf.Findes(nnr) == false) {
				cout << "Enheden findes ikke!" << endl;
				system("pause");
				break;
			}	

			//Skriver antal tændte enheder
		case 't':
		case 'T':
			cout << konf.AntalTandte();
			system("pause");
			break;
			
			//Printer alle enheder ud
		case 'p':
		case 'P':
			konf.PrintAlle();
			system("pause");
			break;

			//Luk programmet
		case 'q':
		case 'Q':
			cout << "Lukker ned..." << endl;
			slut = true;
			system("pause");
			break;

			//Hvis ikke valget findes
		default:
			cout << "Ikke en mulighed" << endl;
			system("pause");
			break;
		}
	}
	
	
}


void Auto() {
	Konfiguration konf("s", 3, 9600);
	konf.Opdater();

	time_t t = time(0);
	struct tm * now = localtime(&t);
	while (slut == false) {
		if (now->tm_sec == 0) {
			if (konf.AutomatiskAfviking() == 'a') {
				cout << "En enhed bliver afviklet" << endl;
			}
		}
	}
	
}


//Her oprettes multithreading, der kører menuen parallelt med at enhederne bliver automatisk afviklet

void main() {

	thread menu(Menu);
	thread autoAfvikling(Auto);
	menu.join();
	autoAfvikling.join();
}
