#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include "Enhed.h"
#include "Serial.h"

using namespace std;

class Konfiguration
{
public:
	Konfiguration(string, int, int); //Konfiguration constructor-funktion
	~Konfiguration(); //Konfiguration deconstructor-funktion
	string FaaNavn();
	void PrintAlle() const; //Printer alle enheder fra enhedsListe_
	void Opdater(); //Opdaterer alle gemte enheder
	void AendrAdresse(int, int); //�ndrer adresse p� en bestemt enhed
	void AendrTid(int, int, int); //�ndrer automatiske tidsindstillinger for en enhed
	void Gem() const; //Gemmer alle enheder der er �ndret eller tilf�jet
	void Afvikl(char); //Afvikler en enhed manuelt
	void AutomatiskAfviking(); //Hvis det nuv�rende klokkesl�t svarer til en enheds automatiske tidsindstilling kaldes Afvikl()
	bool Findes(int); //Checker om en enhed findes udfra dens adresse
	char AntalTandte(); //Skriver hvor mange enheder som er t�ndte
	const Konfiguration & operator+=(const Enhed &nyEnhed); //+operator til enhedsListe_, der ligger en ny enhed ind
	const Konfiguration & operator-=(const string sletEnhed); //+operator til enhedsListe_, der sletter en eksisterende enhed udfra dens navn
private:
	string sysNavn_; //Navnet p� konfigurationen/systemet
	list<Enhed> enhedsListe_; //Liste af alle enheder i systemet
	int comPort_; //Porten som master-enheden k�rer over
	int baudRate_; //Baud-raten p� master-enheden
	CSerial* s = new CSerial();

};