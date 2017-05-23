#define NOMINMAX

#include "Konfiguration.h"
#include <conio.h>
#include <ctime>
#include <thread>
#include <Windows.h>
#include <limits>


//Global variabel slut
bool slut = false;

//Funktion der skal checke om et input er et integer
void CheckInt(int * );

void Menu() {

	//Opsætning

	setlocale(LC_ALL, "danish");

	slut = false;

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

	string slettes;

	//Start. Her skrives navne på systemet
	cout << "Velkommen, indtast navn pa system" << endl;
	getline(cin, sys);
	cout << "Indtast COM-port på master" << endl;
	cin >> CPort;	
	CheckInt(&CPort);
	cout << "Indtast Baud-rate på master" << endl;
	cin >> Baud;
	CheckInt(&Baud);

	//Opret en konfiguration udfra det indtastede navn
	Konfiguration konf(sys, CPort, Baud);
	konf.Opdater();
	system("pause");


	//Hovedmenu hvorpå valg foretages. Opstillet som Switch-statement. Q/q lukker programmet
	while (c != 'q')
	{
		system("CLS");
		cout << sys << "\n\n" << endl;
		cout << "O for at oprette ny enhed:\nS for at slette en enhed:\nI for at ændre en enheds automatiske tidsinstillinger:\nD for at ændre en enheds adresse:\nG for at gemme enhederne:\nA for at afvikle en enhed manuelt:\nT list alle enheder der er tændte:\nP for at printe:\n" << endl;



		cin >> c;
		switch (c)
		{

			//Opret ny Enhed
		case 'o':
		case 'O':
			cout << "Enhedens adresse: " << endl;
			cin >> enha;
			CheckInt(&enha);
			cout << "Enhedens navn: " << endl;
			cin >> enhn;
			cout << "Enhedens type: " << endl;
			cin >> enht;
			cout << "Enhedens automatiske tidsindstilling: \nTimer:" << endl;
			cin >> enhhr;
			CheckInt(&enhhr);
			cout << "Minutter:" << endl;
			cin >> enhm;
			CheckInt(&enhm);
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
			system("pause");
			break;

			//Ændr tid
		case 'i':
		case 'I':
			cout << "Hvilken enhed skal ændres?" << endl;
			cin >> enha;
			CheckInt(&enha);
			cout << "Enhedens nye automatiske tidsindstilling: \nTimer:" << endl;
			cin >> enhhr;
			CheckInt(&enhhr);
			cout << "Minutter:" << endl;
			cin >> enhm;
			CheckInt(&enhm);
			konf.AendrTid(enha, enhhr, enhm);
			system("pause");
			break;

			//Ændr adresse
		case 'd':
		case 'D':
			int nyadr;
			cout << "Hvilken enhed skal ændres?" << endl;
			cin >> enha;
			CheckInt(&enha);
			cout << "Enhedens nye adresse:" << endl;
			cin >> nyadr;
			CheckInt(&nyadr);
			konf.AendrAdresse(enha, nyadr);
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
			cout << "Antal enheder som er tændte: " << konf.AntalTandte() << endl;
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
	//Opsætning
	slut = false;

	bool sendt = false;

	Konfiguration konfa("s", 3, 9600);
	konfa.Opdater();


	//Så længe den globale variabel er false... 
	while (slut == false) {
		//...Ses der efter om tiden skrifter minutter. Hvis dette er tilfældet kaldes AutomatiskAfvikling(), og flaget sendt bliver stillet
		time_t t = time(0);
		struct tm * now = localtime(&t);
		if (now->tm_sec == 0 && sendt == false) {
			konfa.AutomatiskAfviking();
			sendt = true;
		}
		//Når sekundtallet på den nuværende tid rammer 10, nulstilles sendt-flaget
		if (now->tm_sec == 10) {
			sendt = false;
		}
	}
	
}


void CheckInt(int *i) {
	//Validerer om cin modtager et integer
	while (!cin) {
		//Hvis ikke cin modtager et integer udskrives en fejlmeddelelse
		cout << "Denne værdi skal være et tal.\nIndtast igen: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> *i;
	}
}

//Her oprettes multithreading, der kører menuen parallelt med at enhederne bliver automatisk afviklet

void main() {

	thread menu(Menu);
	thread autoAfvikling(Auto);
	menu.join();
	autoAfvikling.join();
}