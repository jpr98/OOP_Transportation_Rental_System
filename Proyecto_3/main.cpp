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

void readReservationFiles(Reservation R[])
{
	ifstream fRes;
	string key;
	int count = 0;
	int clientID, days;
	int dd, mm, yyyy;
	fRes.open("Reserva.txt");
	while (fRes>>key>>clientID>>dd>>mm>>yyyy>>days)
	{
		R[count].setKey(key);
		R[count].setClientID(clientID);
		R[count].setDays(days);
		Date d(dd,mm,yyyy);
		R[count].setContractDate(d);
		count++;
	}
	fRes.close();
}

void readServiceFiles(Service *S[])
{
	ifstream fServ;
	string key, description, opt1, opt2;
	bool found = false;
	bool driver = false;
	bool bulletProof = false;
	char type;
	double cost;
	int count = 0;
	fServ.open("Servicios.txt");
	while (fServ>>key>>type>>cost && getline(fServ, description))
	{
		string opt2;
		description.substr(description.size());
		long n = description.size();
		if (description[n-1] == ' ')
		{
			opt2 = description[n];
			description.erase(n-1);
		}
		else
		{
			opt2 = description[n-1] + description[n];
			description.erase(n-2);
		}
		n = description.size();
		string opt1;
		if (description[n-1] == ' ')
		{
			opt1 = description[n];
			description.erase(n-1);
		}
		else
		{
			opt1 = description[n-1] + description[n];
			description.erase(n-2);
		}
		
		// Checking for service type
		if (type == 'S'||type == 'M'||type == 'T')
		{
			// Checking for driver and bulletProof
			if (opt1 == "1")
			{
				driver = true;
			}
			if (opt2 == "1")
			{
				bulletProof = true;
			}

			S[count] = new Cars(key,description,type,cost,driver,bulletProof);
		}
		else if (type == 'H'||type == 'J'||type == 'A')
		{
			// opt1 is passengers and opt2 is additonal
			int passengers = stoi(opt1);
			int additional = stoi(opt2);
			S[count] = new Planes(key,description,type,cost,passengers,additional);
		}
		count++;
	}
	fServ.close();
}

int main()
{
	Service *S[6];
	Reservation R[20];
	
	readServiceFiles(S);
	readReservationFiles(R);
	
	S[2]->show();
	
	/*  HOW TO DISPLAY RESERVATIONS IN ORDER!!!!!!!!!
	cout << R[1].getKey() << " " << R[1].getClientID() << " ";
	cout << R[1].getContractDate();
	cout << " " <<R[1].getDays() << endl;
	 */
	
	
	
	return 0;
}
