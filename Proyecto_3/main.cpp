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
	int day, month, year;
	cout << "Enter date you want to search: \n";
	cout << "Day: \n";
	cin >> day;
	cout << "Month: \n";
	cin >> month;
	cout << "Year: \n";
	cin >> year;
	Date d(day, month, year);
	if (!(d.validDate()))
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
					}
				}
			}
		}
	}
}

bool dateOverlap(Reservation R[], int count, int days, Date contractDate, char &over, int pos)
{
	bool overlap = false;
	if (contractDate+days >= R[pos].getContractDate())
	{
		overlap = true;
		over = 'L';
	}
	else if (contractDate <= R[pos].calculateEndDate())
	{
		overlap = true;
		over = 'P';
	}
	return overlap;
}

void makeRSVP(Reservation R[], Service *S[], int &count)
{
	string key;
	int dd, mm, yyyy;
	int clientID, days;
	int pos = 0;
	char over; // 'L' = rent less days or push date backwards/ 'P' = push date forward
	cout << "Enter service key: ";
	cin >> key;
	cout << "Enter client ID: ";
	cin >> clientID;
	cout << "Enter contract day: ";
	cin >> dd;
	cout << "Enter contract month: ";
	cin >> mm;
	cout << "Enter contract year: ";
	cin >> yyyy;
	cout << "Enter how many days of reservation: ";
	cin >> days;
	
	//checking if key in service list
	bool foundKey = false;
	for (int i=0; i<6; i++)
	{
		if (key == S[i]->getKey())
		{
			foundKey = true;
			pos = i;
		}
	}
	
	//checking if date is valid
	Date contractDate(dd,mm,yyyy);
	bool validDate;
	validDate = contractDate.validDate();
	
	//checking if date is available
	bool dateAvailable = false;
	dateAvailable = !dateOverlap(R, count, days, contractDate, over, pos);
	
	if (!foundKey)
	{
		cout << "That service key does not exists. Please try again." << endl;
	}
	else if (!validDate)
	{
		cout << "That date isn't valid. Please try again." << endl;
	}
	else if (!dateAvailable)
	{
		char opt, opt2;
		cout << "Date is taken!" << endl;
		cout << "Do you want to modify your date?(1/0) ";
		cin >> opt;
		// modifying date
		if (opt != '0')
		{
			if (over == 'L')
			{
				cout << "Change days or date?(1/2) ";
				cin >> opt2;
				switch (opt2) {
					case '1':
						cout << "New amount of days(less than " << days <<"): ";
						cin >> days;
						break;
					case '2':
						cout << "New date (before ";
						contractDate.show();
						cout <<")" << endl;
						cout << "Day: ";
						cin >> dd;
						cout << "Month: ";
						cin >> mm;
						cout << "Year: ";
						cin >> yyyy;
						contractDate.setDay(dd);
						contractDate.setMonth(mm);
						contractDate.setYear(yyyy);
						break;
				}
			}
			else if (over == 'P')
			{
				cout << "New date (after ";
				R[pos].calculateEndDate().show();
				cout <<")" << endl;
				cout << "Day: ";
				cin >> dd;
				cout << "Month: ";
				cin >> mm;
				cout << "Year: ";
				cin >> yyyy;
				contractDate.setDay(dd);
				contractDate.setMonth(mm);
				contractDate.setYear(yyyy);
			}
			R[count].setKey(key);
			R[count].setClientID(clientID);
			R[count].setContractDate(contractDate);
			R[count].setDays(days);
			count++;
			cout << "Reservation succesful!" << endl;
		}
		else
		{
			cout << "That date is taken. Please try again." << endl;
		}
	}
	else
	{
		R[count].setKey(key);
		R[count].setClientID(clientID);
		R[count].setContractDate(contractDate);
		R[count].setDays(days);
		count++;
		cout << "Reservation succesful!" << endl;
		for(int i=0; i<6; i++)
		{
			if (S[i]->getKey() == key)
			{
				cout << "Total: $" << S[i]->calculateCost(days)<< endl;
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
	
	
	
	
	
	
	/*  HOW TO DISPLAY RESERVATIONS IN ORDER!!!!!!!!!
	cout << R[1].getKey() << " " << R[1].getClientID() << " ";
	cout << R[1].getContractDate();
	cout << " " <<R[1].getDays() << endl;
	 */
	
	
	
	return 0;
}
