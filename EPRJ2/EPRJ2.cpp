#include "Konfiguration.h"

void main() {
	string sys;
	char c = 'j';

	int enha;
	string enhn;
	char enht;
	int enhhr;
	int enhm;

	string slettes;


	cout << "Velkommen, indtast navn pa system" << endl;
	cin >> sys;
	

	Konfiguration konf(sys);
	konf.Opdater();
	system("pause");

	while (c != 'q')
	{
		system("CLS");
		cout << sys << "\n\n" << endl;
		cout << "O for at oprette ny enhed:\nS for at slette en enhed:\nG for at gemme enhederne:\nA for at afvikle en enhed manuelt:\nP for at printe:\n" << endl;
		cin >> c;
		switch (c)
		{
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

		case's':
		case'S':
			cout << "Enhedens navn: " << endl;
			cin >> slettes;
			konf -= (slettes);
			cout << "Enheden er slettet!" << endl;
			system("pause");
			break;

		case 'g':
		case 'G':
			konf.Gem();
			cout << "Alle enheder blev gemt";
			system("pause");
			break;

		case 'a':
		case 'A':
			char nummer;
			int port;
			int baud;
			char jn;
			int nnr;

			cout << "Skriv adressen på enheden du vil afvikle : " << endl;
			cin >> nummer;
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
			

			if (konf.Findes(nnr) == true) {
				konf.Afvikl(nummer, port, baud);
				
				break;
			}
			else if (konf.Findes(nnr) == false) {
				cout << "Enheden findes ikke!" << endl;
				system("pause");
				break;
			}
			

		case 'p':
		case 'P':
			konf.PrintAlle();
			system("pause");
			break;

		case 'q':
		case 'Q':
			cout << "Lukker ned..." << endl;
			break;

		default:
			cout << "Ikke en mulighed" << endl;
			break;
		}
	}
	
	
}