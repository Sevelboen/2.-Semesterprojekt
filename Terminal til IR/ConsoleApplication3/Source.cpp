#include "Betjening.h"
#include<iostream>
#include <io.h>   // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#include <string>

using namespace std;


void main() {
	Betjening b1;

	string valg;
	int vlg;
	int ant;

	do 
	{
		system("CLS");
		cout << "Vælg nu hvad der skal foretages:" << endl;
		cout << "On for at tænde" << endl;
		cout << "Off for at slukke" << endl;
		cout << "VolU for at skrue op" << endl;
		cout << "VolD for at skrue ned" << endl;
		cout << "Source for at bestemme source" << endl;
		cout << "Quit for at slutte" << endl;
		cin >> valg;

		if (valg == "On" || valg == "Off") 
		{
			vlg = 1;
		}
		else if (valg == "VolU")
		{
			vlg = 2;
		}
		else if (valg == "VolD")
		{
			vlg = 3;
		}
		else if (valg == "Source")
		{
			vlg = 4;
		}
		else if (valg == "Quit")
		{
			vlg = 5;
		}

	
		switch (vlg)
		{
		case 1:
			b1.OnOff();
			break;
		case 2:
			cout << "Med hvor meget?" << endl;
			cin >> ant;
			b1.VolUp(ant);
			break;
		case 3:
			cout << "Med hvor meget?" << endl;
			cin >> ant;
			b1.VolDown(ant);
			break;
		case 4:
			b1.SRC();
			break;
		default:
			break;
		}
	} while (vlg != 5);
	

	
}