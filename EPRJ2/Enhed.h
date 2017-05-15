#pragma once
#include <string>
#include <iostream>
using namespace std;

class Enhed
{
public:
	Enhed(int, string, char, int, int);
	~Enhed();
	void Print() const;
	void AendrAdresse(int);
	void AendrTid(int, int);
	int FaaAdresse() const;
	int FaaTimer() const;
	int FaaMinutter() const;
	string FaaNavn() const;
	char FaaType() const;
private:
	int adresse_;
	string navn_;
	char type_;
	int tidspunkt_[2];
};