#include "Konfiguration.h"
#include "Serial.h"
#include <ctime>
#include <Windows.h>



Konfiguration::Konfiguration(string sys, int Port, int Baud)
{
	//Enhedens constructor-funktion der sætter alle private parametre
	sysNavn_ = sys; 
	comPort_ = Port;
	baudRate_ = Baud;

}


Konfiguration::~Konfiguration()
{
	s->Close();
	delete s;
}

string Konfiguration::FaaNavn()
{
	return sysNavn_;
}

void Konfiguration::PrintAlle() const
{
	//Går enhedsListe_ igennem, og kalder alle enhedernes Print() funktion
	list<Enhed>::const_iterator iter;

	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		iter->Print();
		cout << endl;
	}

	cout << endl;
}

void Konfiguration::Opdater()
{
	//Opsætning af anvendte variabler
	string str;
	ifstream myfile;
	string ej;
	int lnjr = 0;
	string *linie;


	//Finder antal linjer i filen hvori alle enheder gemmes

	myfile.open("example.txt");
	while (getline(myfile, ej)) {
		lnjr++;
	}
	myfile.close();

	//Opretter et nyt string-array, med en længde på antal linjer i vores enheds-fil, således at alle enheder opdateres

	myfile.open("example.txt");
	linie = new string[lnjr];

	for (int i = 0; i < lnjr; i++)
	{
		getline(myfile, linie[i]);
		str += linie[i];
	}


	myfile.close();



	//Erstatter alle ";" med et mellemrum, således at vi kan splitte enhedens private variabler fra hinanden

	for (int i = 0; i<str.length(); i++)
	{
		if (str[i] == ';')
			str[i] = ' ';
	}

	//Opretter en string vector som indeholder al information fra filen

	vector<string> aray;
	stringstream ss(str);
	string temp;
	while (ss >> temp)
		aray.push_back(temp);

	//Oversætter alt fra filen til enheder. Første linje springes over da denne bare er en indikator: "ID:NAVN:TYPE:TID"
	for (int s = 1; s < aray.size(); s ++)
	{

		int madresse;
		string mnavn;
		char mtype;
		int mtimer;
		int mminutter;

		madresse = stoi(aray[s]);
		s++;
		mnavn = aray[s];
		s++;
		mtype = aray[s][0];
		s++;
		mtimer = stoi(aray[s]);
		s++;
		mminutter = stoi(aray[s]);
		this->operator+=(Enhed(madresse, mnavn, mtype, mtimer, mminutter));
	}

}

void Konfiguration::AendrAdresse(int adr, int nyAdr)
{
	//Ændrer adressen på en bestemt enhed fra adr til nyAdr
	list<Enhed>::iterator iter;

	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		if (iter->FaaAdresse() == adr) {
			iter->AendrAdresse(nyAdr);

		}
	}

}

void Konfiguration::AendrTid(int adr, int tim, int min)
{
	//Ændrer den automatiske tidsindstilling på en enhed udfra dens adr. Tidsindstillingerne ændres således at tidspunkt_[0] = tim og tidspunkt_[1] = min
	list<Enhed>::iterator iter;

	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		if (iter->FaaAdresse() == adr) {
			iter->AendrTid(tim, min);

		}
	}

}

void Konfiguration::Gem() const
{
	//Opsætning af anvendte variabler
	ofstream myfile;
	list<Enhed>::const_iterator iter;

	int madresse;
	string mnavn;
	char mtype;
	int mtimer;
	int mminutter;

	//Første linie af filen er indikatoren:  "ID:NAVN:TYPE:TID"
	myfile.open("example.txt");
	myfile << "ID:NAVN:TYPE:TID\n";

	//Dernæst kommer en ny enheds adresse, nav, type, og tid i timer og minutter. Dette gentages for alle enheder i enhedsListe_
	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		madresse = iter->FaaAdresse();
		mnavn = iter->FaaNavn();
		mtype = iter->FaaType();
		mtimer = iter->FaaTimer();
		mminutter = iter->FaaMinutter();

		myfile << ";" << madresse << ";" << mnavn << ";" << mtype << ";" << mtimer << ";" << mminutter << "\n";
		cout << endl;
	}

	myfile.close();

}

void Konfiguration::Afvikl( char enhnr)
{
	//Opsætning af anvendte variabler
	char data[1];

	//Åbner kommunikation til master udfra comPort_ og baudRate_
	if (!s->Open(comPort_, baudRate_))
	{
		cout << "Could not open COM" << comPort_ << endl;
		system("pause");
		return;
	}
	data[0] = enhnr;
	
	//Sender enhnr til master og lukker forbindelsen
	Sleep(2000);
	s->SendData(data, 1);

}

void Konfiguration::AutomatiskAfviking()
{
	
	//Løber enhedsListe_ igennem indtil den finder en hvis automatiske tidsindstilling er tilsvarende til det nuværende klokkeslæt*
	list<Enhed>::const_iterator iter;
	
	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		time_t t = time(0);
		struct tm * now = localtime(&t);

		int timer = now->tm_hour;
		int minutter = now->tm_min;

		//*Hvis dette er tilfældet kalder den Afvikl()-funktionen med enhedens adresse som char som parameter
		if (iter->FaaTimer() == timer && iter->FaaMinutter() == minutter ) {
			char adresse = '0' + iter->FaaAdresse();
			Afvikl(adresse);
			Sleep(2000);
			cout << "Enhed " << iter->FaaAdresse() << " : " << iter->FaaNavn() << " blev afviklet..." << endl;
			
		}
	}

}

bool Konfiguration::Findes(int nr)
{
	//Løber enhedsListe_ igennem. Hvis den finder en enhed med en adresse_ som er lig nr returnes true, ellers returnes false
	list<Enhed>::const_iterator iter;
	int findes = 0;

	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		if (iter->FaaAdresse() == nr) {
			findes += 1;
		}
		else if (iter->FaaAdresse() != nr) {
			findes += 0;
		}
	}
	
	if (findes > 0) {
		return true;
	}
	else if (findes <= 0) {
		return false;
	}

}

char Konfiguration::AntalTandte()
{
	//Opsætning af anvendte variabler
	char input[1];
	char data[1];

	//Åbner en forbindelse til master udfra comPort_ og baudRate_
	if (!s->Open(comPort_, baudRate_))
	{
		cout << "Could not open COM" << comPort_ << endl;
		system("pause");
	}

	//Sender "L" og lytter derefter på seriel-porten og returner hvad der ligger der.
	data[0] = 'L';

	Sleep(2000);
	s->SendData(data, 1);
	Sleep(2000);
	if (s->ReadDataWaiting() > 0) {
		s->ReadData(input, 1);
	}
	return input[0];
}

 const Konfiguration & Konfiguration::operator+=( const Enhed & nyEnhed)
{
	//Opsætning af anvendte variabler
	bool isInserted = false;
	list<Enhed>::iterator iter;

	//Indsætter en enhed ind, efter nummerorden efter adresse
	for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	{
		if (iter->FaaAdresse() > nyEnhed.FaaAdresse())
		{
			enhedsListe_.insert(iter, nyEnhed);
			isInserted = true;
			break;
		}
	}

	if (isInserted == false)
		enhedsListe_.push_back(nyEnhed);

	return *this;
}

 const Konfiguration & Konfiguration::operator-=(const string sletEnhed)
 {
	 //Opsætning af anvendt iterator
	 list<Enhed>::iterator iter;

	 //Hvis en enhed har navnet sletEnhed slettes denne enhed
	 for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	 {
		 if (iter->FaaNavn() == sletEnhed)
		 {
			 iter = enhedsListe_.erase(iter);
			 cout << "Enhed slettet" << endl;
			 break;
		 }
	 }

	 return *this;
 }