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
	Konfiguration(string);
	~Konfiguration();
	void PrintAlle() const;
	void Opdater();
	void Gem() const;
	void Afvikl(char, int, int);
	char AutomatiskAfviking();
	bool Findes(int);
	char AntalTandte(int, int);
	const Konfiguration & operator+=(const Enhed &nyEnhed);
	const Konfiguration & operator-=(const string sletEnhed);
private:
	string sysNavn_;
	list<Enhed> enhedsListe_;

};