//
//  main.cpp
//  Proyecto_3
//
//  Created by Juan Pablo Ramos on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "Date.h"


using namespace std;
#include "Cars.h"
#include "Planes.h"
#include "Reservation.h"

void readReservationFiles()
{
	ifstream fRes;
	string line, subStr, key;
	long pos;
	int clientID, days;
	int dd, mm, yyyy;
	fRes.open("Reserva.txt");
	while (getline(fRes,line))
	{
		pos = line.find(" ");
		
	}
	fRes.close();
}

void readServiceFiles(Reservation R[])
{
	ifstream fServ;
	string line;
	fServ.open("Servicios.txt");
	while (getline(fServ,line))
	{
		
	}
	fServ.close();
}

int main()
{
	Service *S[6];
	Reservation R[20];
	
	
	
	
	
	
	return 0;
}
