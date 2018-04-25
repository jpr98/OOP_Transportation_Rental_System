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

using namespace std;
#include "Date.h"
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
		driver = false;
		bulletProof = false;
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

			S[count] = new Cars(key,description,type,cost,bulletProof,driver);
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

void writeRSVPFile(Reservation R[], int count)
{
	ofstream ofRes;
	ofRes.open("Reserva.txt");
	for (int i=0; i<count; i++)
	{
		ofRes<<R[i].getKey()<<" "<<R[i].getClientID()<<" "<<R[i].getContractDate().getDay()<<" "<<R[i].getContractDate().getMonth()<<" "<<R[i].getContractDate().getYear()<<" "<<R[i].getDays()<<endl;
	}
	ofRes.close();
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
				cout << "Start Date: "<< R[i].getContractDate() << endl;
				cout << "End Date: " << R[i].calculateEndDate() << endl;
				cout << "Total: $" << S[j]->calculateCost(R[i].getDays()) << endl;
			}
		}
	}
}

void consultServiceRSVP(Reservation R[], Service *S[], int count)
{
	string userKey;
	cout << "Enter service key: ";
	cin >> userKey;
	bool foundRes = false;
	bool foundServ = false;
	for (int i=0; i<6; i++)
	{
		if (S[i]->getKey() == userKey)
		{
			S[i]->show();
			for(int j=0; j<count; j++)
			{
				if(userKey == R[j].getKey())
				{
					cout << "---------------" << endl;
					cout << "Reservation #" << j+1 << endl;
					cout << "Client ID: "<< R[j].getClientID() << endl;
					cout << "Start Date: "<< R[j].getContractDate() << endl;;
					cout << "End Date: " << R[j].calculateEndDate() << endl;
					foundRes = true;
				}
			}
			if (!foundRes)
			{
				cout << "No reservations for that service." << endl;
			}
			foundServ = true;
		}
	}
	if(!foundServ)
	{
		cout << "No service with that key." << endl;
	}
}

void searchReservationByDate(Reservation R[], Service *S[], int count)
{
	bool found = false;
	int day, month, year;
	cout << "Enter date you want to search: \n";
	cout << "Day: ";
	cin >> day;
	cout << "Month: ";
	cin >> month;
	cout << "Year: ";
	cin >> year;
	Date d(day, month, year);
	if (!d.validDate())
	{
		cout << "Invalid Date try again \n";
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			if (d == R[i].getContractDate())
			{
				for (int j = 0; j < 6; j++) {
					if (R[i].getKey() == S[j]->getKey())
					{
						cout << "---------------" << endl;
						cout << "Reservation #" << i+1 << endl;
						S[j]->show();
						cout << "Client ID: "<< R[i].getClientID() << endl;
						cout << "Start Date: "<< R[i].getContractDate() << endl;;
						cout << "End Date: " << R[i].calculateEndDate() << endl;
						cout << "Total: $" << S[j]->calculateCost(R[i].getDays()) << endl;
						found = true;
					}
				}
			}
		}
		if (!found)
		{
			cout << "No reservations on that date!" << endl;
		}
	}
}

bool validData(Reservation R[], Service *S[], int count, Date date1, string serviceKey, int days, bool &serviceValid, bool &validDate)
{
	serviceValid = false;
	validDate = true;
	for (int i = 0; i < 6; i++)
	{
		if (serviceKey == S[i]->getKey())
		{
			serviceValid = true;
			for(int j = 0; j < count; j++)
			{
				if (R[j].getKey() == serviceKey)
				{
					if (R[j].getContractDate() <= date1 && R[j].calculateEndDate() >= date1)
					{
						validDate = false;
					}
					if (R[j].getContractDate() <= date1+days && R[j].calculateEndDate() >= date1+days)
					{
						validDate = false;
					}
				}
			}
		}
	}
	if (serviceValid && validDate)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void makeRSVP(Reservation R[], Service *S[], int &count)
{
	int clientID, d, m, y, days;
	bool serviceValid;
	bool validDate;
	string serviceKey;
	string op;
	bool valid = false;
	do{
		cout << "Client ID: \n";
		cin >> clientID;
		cout << "Service key: \n";
		cin >> serviceKey;
		cout << "Day: \n";
		cin >> d;
		cout << "Month: \n";
		cin >> m;
		cout << "Year: \n";
		cin >> y;
		cout << "Days to rent: \n";
		cin >> days;
		Date da(d,m,y);
		if (da.validDate())
		{
			valid = validData(R,S,count,da,serviceKey,days,serviceValid,validDate);
			if (!serviceValid)
			{
				cout << "Service key not valid \n";
			} else if (!validDate)
			{
				cout << "Try other date \n";
			}
			if (clientID == -1)
			{
				break;
			}
		}
		else
		{
			cout << "Invalid date!" << endl;
		}
	}while (!valid);
	R[count].setClientID(clientID);
	R[count].setKey(serviceKey);
	R[count].setDays(days);
	Date date1(d, m, y);
	R[count].setContractDate(date1);
	if (valid) {
		cout << "Reservation created succefully \n";
		count++;
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
				consultServiceRSVP(R, S, rCount);
				break;
			// Search Reservations by Date
			case '4':
				searchReservationByDate(R, S, rCount);
				break;
			// Make Reservation
			case '5':
				makeRSVP(R, S, rCount);
				break;
		}
	} while(opt != '6');
	writeRSVPFile(R, rCount);
	cout << "Data saved!" << endl;
	cout << "Exiting..." << endl;

	return 0;
}
