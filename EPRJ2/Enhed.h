#pragma once
#include <string>
#include <iostream>
using namespace std;

class Enhed
{
public:
	Enhed(int, string, char, int, int); //Enheds-constructor
	~Enhed(); //Enheds-deconstructor
	void Print() const; //Print-function til Enhed
	void AendrAdresse(int); //Ændrer private adresse_
	void AendrTid(int, int); //Ændrer private tidspunkt_
	int FaaAdresse() const; //Get-metode til private adresse_
	int FaaTimer() const; //Get-metode til private tidspunkt_[0]
	int FaaMinutter() const; //Get-metode til private tidspunkt_[1]
	string FaaNavn() const; //Get-metode til private navn_
	char FaaType() const; //Get-metode til private type_
private:
	int adresse_; //Enhedens Adresse
	string navn_; //Enhedens Navn
	char type_; //Enhedens Type
	int tidspunkt_[2]; //Enhedens Automatiske Tidsindstilling
};