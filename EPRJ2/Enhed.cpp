#include "Enhed.h"
#include <iomanip>




Enhed::Enhed(int adr, string nvn, char typ, int hr, int min)
{
	adresse_ = adr;
	navn_ = nvn;
	type_ = typ;
	tidspunkt_[0] = hr;
	tidspunkt_[1] = min;
}

Enhed::~Enhed()
{

}

void Enhed::Print() const
{
	string type;
	if (type_ == 's' || type_ == 'S') {
		type = "Simpel";
	}
	else {
		type = "Kompleks";
	}
	cout << "Enhedens ID: " << adresse_ << endl;
	cout << "Enhedens navn: " << navn_ << endl; 
	cout << "Enhedens type: " << type << endl;
	cout << "Enhedens automatiske konfiguration er sat til klokken: ";
	cout << setw(2) << setfill('0') << tidspunkt_[0];
	cout << ":";
	cout << setw(2) << setfill('0') << tidspunkt_[1] << endl;
}

void Enhed::AendrAdresse(int adr)
{
	adresse_ = adr;
}

void Enhed::AendrTid(int hr, int min)
{
	tidspunkt_[0] = hr;
	tidspunkt_[1] = min;
}

int Enhed::FaaAdresse() const
{
	return adresse_;
}

int Enhed::FaaTimer() const
{
	return tidspunkt_[0];
}

int Enhed::FaaMinutter() const
{
	return tidspunkt_[1];
}


string Enhed::FaaNavn() const
{
	return navn_;
}

char Enhed::FaaType() const
{
	return type_;
}
