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

void readReservationFiles(Reservation R[], int &count)
{
	ifstream fRes;
	string key;
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
	bool driver = false;
	bool bulletProof = false;
	char type;
	double cost;
	int count = 0;
	fServ.open("Servicios.txt");
	while (fServ>>key>>type>>cost && getline(fServ, description))
	{
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
		n = description.size()-1;
		if (description[n-1] == ' ')
		{
			opt1 = description[n];
			description.erase(n-1);
		}
		else
		{
			opt1 = description.substr(n-1);
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

void consultServiceList(Service *S[])
{
	for (int i=0; i<6; i++)
	{
		cout << "---------------" << endl;
		S[i]->show();
	}
}

void consultRSVPList(Reservation R[], Service *S[], int count)
{
	for (int i=0; i<count; i++)
	{
		for (int j=0; j<6; j++)
		{
			if (S[j]->getKey() == R[i].getKey())
			{
				cout << "---------------" << endl;
				cout << "Reservation #" << i+1 << endl;
				S[j]->show();
				cout << "Client ID: "<< R[i].getClientID() << endl;
				cout << "Start Date: "<< R[i].getContractDate() << endl;;
				cout << "End Date: " << R[i].calculateEndDate() << endl;
				cout << "Total: $" << S[j]->calculateCost(R[i].getDays()) << endl;
			}
		}
	}
}
int main()
{
	Service *S[6];
	Reservation R[20];
	
	int rCount = 0;
	readServiceFiles(S);
	readReservationFiles(R,rCount);
	
	//S[2]->show();
	char opt;
	do
	{
		cout << "**  Menu  **" << endl;
		cout << "1) Services List" << endl;
		cout << "2) Reservations List" << endl;
		cout << "3) Search Reservations by Service Key" << endl;
		cout << "4) Search Reservations by Date" << endl;
		cout << "5) Make Reservation" << endl;
		cout << "6) End" << endl;
		cin >> opt;
		
		switch (opt) {
			// Service List
			case '1':
				consultServiceList(S);
				break;
			// Reservations List
			case '2':
				consultRSVPList(R, S, rCount);
				break;
			// Search Reservations by Service Key
			case '3':
				
				break;
			// Search Reservations by Date
			case '4':
				
				break;
			// Make Reservation
			case '5':
				
				break;
		}
	} while(opt != '6');
	
	
	
	
	
	
	/*  HOW TO DISPLAY RESERVATIONS IN ORDER!!!!!!!!!
	cout << R[1].getKey() << " " << R[1].getClientID() << " ";
	cout << R[1].getContractDate();
	cout << " " <<R[1].getDays() << endl;
	 */
	
	
	
	return 0;
}
