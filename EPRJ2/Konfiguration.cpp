#include "Konfiguration.h"
#include "Serial.h"
#include <Windows.h>



Konfiguration::Konfiguration(string sys)
{
	sysNavn_ = sys; 
}


Konfiguration::~Konfiguration()
{

}

void Konfiguration::PrintAlle() const
{
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
	string str;
	ifstream myfile;
	string ej;
	int lnjr = 0;
	string *linie;


	//

	myfile.open("example.txt");
	while (getline(myfile, ej)) {
		lnjr++;
	}
	myfile.close();

	//

	myfile.open("example.txt");
	linie = new string[lnjr];

	for (int i = 0; i < lnjr; i++)
	{
		getline(myfile, linie[i]);
		str += linie[i];
	}


	myfile.close();



	//

	for (int i = 0; i<str.length(); i++)
	{
		if (str[i] == ';')
			str[i] = ' ';
	}


	vector<string> aray;
	stringstream ss(str);
	string temp;
	while (ss >> temp)
		aray.push_back(temp);


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

void Konfiguration::Gem() const
{
	ofstream myfile;
	list<Enhed>::const_iterator iter;

	int madresse;
	string mnavn;
	char mtype;
	int mtimer;
	int mminutter;

	myfile.open("example.txt");
	myfile << "ID:NAVN:TYPE:TID\n";

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

void Konfiguration::Afvikl( char enhnr, int port, int baud)
{
	char data[1];
	CSerial* s = new CSerial();


	if (!s->Open(port, baud))
	{
		cout << "Could not open COM" << port << endl;
		system("pause");
		return;
	}
	data[0] = enhnr;
	
	Sleep(2000);
	s->SendData(data, 1);
	s->Close();

	delete s;

}

bool Konfiguration::Findes(int nr)
{
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

 const Konfiguration & Konfiguration::operator+=( const Enhed & nyEnhed)
{
	bool isInserted = false;
	list<Enhed>::iterator iter;

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
	 list<Enhed>::iterator iter;

	 for (iter = enhedsListe_.begin(); iter != enhedsListe_.end(); ++iter)
	 {
		 if (iter->FaaNavn() == sletEnhed)
		 {
			 iter = enhedsListe_.erase(iter);
			 break;
		 }
	 }

	 return *this;
 }