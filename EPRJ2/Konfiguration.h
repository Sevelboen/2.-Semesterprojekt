#pragma once
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <sstream>
#include "Enhed.h"

using namespace std;

class Konfiguration
{
public:
	Konfiguration(string, int, int);
	~Konfiguration();
	void PrintAlle() const;
	void Opdater();
	void AendrAdresse(int, int);
	void AendrTid(int, int, int);
	void Gem() const;
	void Afvikl(char);
	void AutomatiskAfviking();
	bool Findes(int);
	char AntalTandte();
	const Konfiguration & operator+=(const Enhed &nyEnhed);
	const Konfiguration & operator-=(const string sletEnhed);
private:
	string sysNavn_;
	list<Enhed> enhedsListe_;
	int comPort_;
	int baudRate_;

};