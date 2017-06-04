#include "Betjening.h"
#include<iostream>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <string>

using namespace std;


Betjening::Betjening(string hi)
{
	hej = hi;
}


Betjening::~Betjening()
{
}

void Betjening::set()
{
	system("powershell.exe Set-ExecutionPolicy RemoteSigned \n");
}

void Betjening::OnOff()
{
	set();
	system("powershell.exe C:\\IR\\OnOff.ps1");
}

void Betjening::SRC()
{
	set();
	system("powershell.exe C:\\IR\\SRC.ps1");
}

void Betjening::VolUp(int nr)
{
	set();
	system("powershell.exe C:\\IR\\VolUp.ps1");
	_sleep(nr * 1000);
	system("powershell.exe C:\\IR\\Stop.ps1");
}

void Betjening::VolDown(int nr)
{
	set();
	system("powershell.exe C:\\IR\\VolDown.ps1");
	_sleep(nr * 1000);
	system("powershell.exe C:\\IR\\Stop.ps1");
}
