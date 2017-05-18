#include "Konfiguration.h"
#include <conio.h>
#include <ctime>

void main() {

	//Opsætning

	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);

	string sys;
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
	
	//Opret en konfiguration udfra det indtastede navn
	Konfiguration konf(sys);
	konf.Opdater();
	system("pause");


	//Hovedmenu hvorpå valg foretages. Opstillet som Switch-statement
	while (c != 'q')
	{
		system("CLS");
		cout << sys << "\n\n" << endl;
		cout << "O for at oprette ny enhed:\nS for at slette en enhed:\nG for at gemme enhederne:\nA for at afvikle en enhed manuelt:\nT list alle enheder der er tændte:\nP for at printe:\n" << endl;
		while (!kbhit()) {
			time_t t = time(0);
			struct tm * now = localtime(&t);
			if (now->tm_sec == 0) {
				if (konf.AutomatiskAfviking() == 'a') {
					cout << "En enhed bliver afviklet" << endl;
				}
				
			}
		}
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
			int port;
			int baud;
			char jn;
			int nnr;

			//Enheds ID
			cout << "Skriv adressen på enheden du vil afvikle : " << endl;
			cin >> nummer;

			//Opret forbindelse til Arduino og sender ID som char...
			cout << "Default port (3) og baud-rate? (9600) (j/n): " << endl;
			cin >> jn;
			if (jn == 'n') {
				cout << "Skriv porten der kommunikerer med Master : " << endl;
				cin >> port;
				cout << "Skriv baud-raten : " << endl;
				cin >> baud;
			}
			else if (jn == 'j') {
				port = 3;
				baud = 9600;
			}
			nnr = nummer - '0';
			
			//...hvis enheden findes
			if (konf.Findes(nnr) == true) {
				konf.Afvikl(nummer, port, baud);
				
				break;
			}
			else if (konf.Findes(nnr) == false) {
				cout << "Enheden findes ikke!" << endl;
				system("pause");
				break;
			}	


		case 't':
		case 'T':
			cout << konf.AntalTandte(3, 9600);
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
			system("pause");
			break;

		default:
			cout << "Ikke en mulighed" << endl;
			system("pause");
			break;
		}
	}
	
	
}