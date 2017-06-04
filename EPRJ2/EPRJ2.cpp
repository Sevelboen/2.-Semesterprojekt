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
void CheckInt(int *);

//Vores menu for programmet
void Menu(Konfiguration konfig) {

	//Ops�tning
	slut = false;
	setlocale(LC_ALL, "danish");


	time_t t = time(0);
	struct tm * now = localtime(&t);
	
	char c = 'j';

	int enha;
	string enhn;
	char enht;
	int enhhr;
	int enhm;

	string slettes;

	system("pause");


	//Hovedmenu hvorp� valg foretages. Opstillet som Switch-statement. Q/q lukker programmet
	while (c != 'q')
	{
		system("CLS");
		cout << konfig.FaaNavn() << "\n\n" << endl;
		cout << R"(
O for at oprette ny enhed:
S for at slette en enhed:
I for at �ndre en enheds automatiske tidsinstillinger:
D for at �ndre en enheds adresse:
G for at gemme enhederne:
A for at afvikle en enhed manuelt:
T list alle enheder der er t�ndte:
P for at printe:)" << endl;



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
			konfig += Enhed(enha, enhn, enht, enhhr, enhm);
			cout << "Enheden er gemt!" << endl;
			system("pause");
			break;

			//Slet en enhed
		case's':
		case'S':
			cout << "Enhedens navn: " << endl;
			cin >> slettes;
			konfig -= (slettes);
			system("pause");
			break;

			//�ndr tid
		case 'i':
		case 'I':
			cout << "Hvilken enhed skal �ndres?" << endl;
			cin >> enha;
			CheckInt(&enha);
			cout << "Enhedens nye automatiske tidsindstilling: \nTimer:" << endl;
			cin >> enhhr;
			CheckInt(&enhhr);
			cout << "Minutter:" << endl;
			cin >> enhm;
			CheckInt(&enhm);
			konfig.AendrTid(enha, enhhr, enhm);
			system("pause");
			break;

			//�ndr adresse
		case 'd':
		case 'D':
			int nyadr;
			cout << "Hvilken enhed skal �ndres?" << endl;
			cin >> enha;
			CheckInt(&enha);
			cout << "Enhedens nye adresse:" << endl;
			cin >> nyadr;
			CheckInt(&nyadr);
			konfig.AendrAdresse(enha, nyadr);
			system("pause");
			break;


			//Gem alle oprettede enheder
		case 'g':
		case 'G':
			konfig.Gem();
			cout << "Alle enheder blev gemt";
			system("pause");
			break;

			//Afvikl en enhed manuelt
		case 'a':
		case 'A':
			char nummer;
			int nnr;

			//Enheds ID
			cout << "Skriv adressen p� enheden du vil afvikle : " << endl;
			cin >> nummer;

			//Opret forbindelse til Arduino og sender ID som char hvis enheden findes
			nnr = nummer - '0';
			

			if (konfig.Findes(nnr) == true) {
				konfig.Afvikl(nummer);
				
				break;
			}
			else if (konfig.Findes(nnr) == false) {
				cout << "Enheden findes ikke!" << endl;
				system("pause");
				break;
			}	

			//Skriver antal t�ndte enheder
		case 't':
		case 'T':
			cout << "Antal enheder som er t�ndte: " << konfig.AntalTandte() << endl;
			system("pause");
			break;
			
			//Printer alle enheder ud
		case 'p':
		case 'P':
			konfig.PrintAlle();
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
	konfig.~Konfiguration();
}

//Afvikler en enhed hvis de automatiske instillinger matcher det nuv�rende tidspunkt
void Auto(Konfiguration konfig) {
	//Ops�tning
	slut = false;
	bool sendt = false;
	
	//S� l�nge den globale variabel er false... 
	while (slut == false) {
		//...ses der efter om tiden skrifter minutter. Hvis dette er tilf�ldet kaldes AutomatiskAfvikling(), og flaget sendt bliver stillet
		time_t t = time(0);
		struct tm * now = localtime(&t);
		if (now->tm_sec == 0 && sendt == false) {
			konfig.AutomatiskAfviking();
			sendt = true;
		}
		//N�r sekundtallet p� den nuv�rende tid rammer 10, nulstilles sendt-flaget
		if (now->tm_sec == 10) {
			sendt = false;
		}
	}
}

//Validerer om cin modtager et integer
void CheckInt(int *i) {

	//Hvis ikke cin modtager et integer udskrives en fejlmeddelelse
	while (!cin) {
		cout << "Denne v�rdi skal v�re et tal.\nIndtast igen: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> *i;
	}
}

void main() {

	string sys;
	int Baud;
	int CPort;

	//Start. Her skrives navne p� systemet
	cout << R"(
     # # # # # # # # # # # # # # # # # # # # # 
     #                          ________     #
     #                         | ______o|    #
     #         _______________ ||__---_||    #
     #        |  ___________  || ______ |    #
     #        | |           | |||______||    #
     #        | | #         | ||--------|    #
     #        | |           | ||      O |    #
     #        | |           | ||      | |    #
     #        | '-----------' ||      | |    #
     #        |_____________-_||      | |    #
     #          __/_______\__  |::::::::|    #
     #         ________________'-.__         #
     #        /:::::::::':::'::\ .\\\---.    #
     #       /::======::: .:.:::\ \\_)   \   #
     #       `""""""""""""""""""`  '-----'   #
     # # # # # # # # # # # # # # # # # # # # #
        )";
	cout << "Velkommen, indtast navn pa system" << endl;
	getline(cin, sys);
	cout << "Indtast COM-port p� master" << endl;
	cin >> CPort;
	CheckInt(&CPort);
	cout << "Indtast Baud-rate p� master" << endl;
	cin >> Baud;
	CheckInt(&Baud);

	//Opretter en konfiguration og opdaterer den udfra systemfilen
	Konfiguration konfig(sys, CPort, Baud);
	konfig.Opdater();

	//Her oprettes multithreading, der k�rer menuen parallelt med at enhederne bliver automatisk afviklet
	thread menu(Menu, konfig);
	thread autoAfvikling(Auto, konfig);
	menu.join();
	autoAfvikling.join();
}