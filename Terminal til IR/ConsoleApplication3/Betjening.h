#pragma once
#include<iostream>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <string>

using namespace std;

class Betjening
{
public:
	Betjening(string hi = "");
	~Betjening();
	void OnOff();
	void SRC();
	void VolUp(int nr);
	void VolDown(int nr);
private:
	string hej;
	void set();
};

