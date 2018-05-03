/*
  main.cpp
  Proyecto_3

  Created by Juan Pablo Ramos & Ricardo Ramirez on 4/18/18.
 
 This program simulates a rent system, where you can rent either a car or airplane and check availability.
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;
#include "Date.h"
#include "Cars.h"
#include "Planes.h"
#include "Reservation.h"

/*
 readReservationFiles
 This funcition is to read reservation file and save in the reservation array all data
 Parameters:
    Reservation array and counter.
 Return:
    NONE
 */
void readReservationFiles(Reservation R[], int &count)
{
	ifstream fRes;
	string key;
	int clientID, days;
	int dd, mm, yyyy;
	fRes.open("Reserva.txt");
	while (fRes>>key>>clientID>>dd>>mm>>yyyy>>days) //saving data to variables
	{
		R[count].setKey(key);
		R[count].setClientID(clientID);
		R[count].setDays(days);
		Date d(dd,mm,yyyy);
		R[count].setContractDate(d); //filling up objet array
		count++;
	}
	fRes.close();
}

/*
 readServiceFiles
 This function is to read service file and save it in a pointer array.
 Parameters:
    Service pointer array.
 Return:
    NONE
 */
void readServiceFiles(Service *S[])
{
	ifstream fServ;
	string key, description, opt1, opt2;
	bool driver = false;
	bool bulletProof = false;
	char type;
	double cost;
	int count = 0;
	fServ.open("Servicios.txt"); //opening file
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
		else //All this conditionals is to substring and separate the string
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
			S[count] = new Planes(key,description,type,cost,passengers,additional); //creating object plane
		}
		count++;
	}
	fServ.close(); //closing file
}
/*
 writeRSVPFile
 This funcition is to write and save in the reservation array all data
 Parameters:
    Reservation array and counter.
 Return:
    NONE
 */
void writeRSVPFile(Reservation R[], int count)
{
	ofstream ofRes;
	ofRes.open("Reserva.txt");
	for (int i=0; i<count; i++) //Iterating on the array of reservation to write on the file
	{
		ofRes<<R[i].getKey()<<" "<<R[i].getClientID()<<" "<<R[i].getContractDate().getDay()<<" "<<R[i].getContractDate().getMonth()<<" "<<R[i].getContractDate().getYear()<<" "<<R[i].getDays()<<endl;
	}
	ofRes.close();
}
/*
 consultServiceList
 This funcition displays to the user all service list
 Parameters:
    Service pointer array.
 Return:
    NONE
 */
void consultServiceList(Service *S[])
{
	for (int i=0; i<6; i++) //Iterating over the service array
	{
		cout << "---------------" << endl;
		S[i]->show();
	}
}

/*
 consultRSVPList
 This funcition displays to the user all reservations that have been made
 Parameters:
    Reservation array, service pointer array, counter
 Return:
    NONE
 */
void consultRSVPList(Reservation R[], Service *S[], int count)
{
	for (int i=0; i<count; i++)//iterating over reservation array to display
	{
		for (int j=0; j<6; j++) //iterating over service pointer
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

/*
 consultServiceRSVP
 This funcition displays to the user all services on reservation
 Parameters:
    Reservation array, service pointer array, counter
 Return:
    NONE
 */
void consultServiceRSVP(Reservation R[], Service *S[], int count)
{
	string userKey;
	cout << "Enter service key: ";
	cin >> userKey;
	bool foundRes = false;
	bool foundServ = false;
	for (int i=0; i<6; i++) //iterating over services
	{
		if (S[i]->getKey() == userKey) //If we find the key then ..
		{
			S[i]->show();
			for(int j=0; j<count; j++)
			{
				if(userKey == R[j].getKey()) //Finding the unique user key
				{
					cout << "---------------" << endl;
					cout << "Reservation #" << j+1 << endl;
					cout << "Client ID: "<< R[j].getClientID() << endl;
					cout << "Start Date: "<< R[j].getContractDate() << endl;;
					cout << "End Date: " << R[j].calculateEndDate() << endl;
					foundRes = true;
				}
			}
			if (!foundRes) //not found at all
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

/*
 searchReservationByDate
 This funcition displays reservations on specific date entered by the user
 Parameters:
    Reservation array, service pointer array, counter
 Return:
    NONE
 */
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
	Date d(day, month, year); //creating date given by user
	if (!d.validDate()) //VALIDATING DATE
	{
		cout << "Invalid Date try again \n";
	}
	else
	{
		for (int i = 0; i < count; i++) //Iterating over reservation array
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
						found = true; //Reservation found ... Displayed
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

/*
 validDAta
 This funcition is to validate all data when making a reservation.
 Parameters:
    Reservation array, service pointer array, counter, date given by the user, serviceKey, days to rent, two bools looking to be validated
 Return:
    TRUE if ALL DATA IS VALID
    Else FALSE
 */
bool validData(Reservation R[], Service *S[], int count, Date date1, string serviceKey, int days, bool &serviceValid, bool &validDate)
{
	serviceValid = false;
	validDate = true;
	for (int i = 0; i < 6; i++) //iterating over service
	{
		if (serviceKey == S[i]->getKey()) //looking for a valid key
		{
			serviceValid = true;
			for(int j = 0; j < count; j++) //iterating over reservation
			{
				if (R[j].getKey() == serviceKey)
				{                                   //valid key found
					if (R[j].getContractDate() <= date1 && R[j].calculateEndDate() >= date1)
					{
						validDate = false; //INVALID DATE ****OVERLAPING***
					}
					if (R[j].getContractDate() <= date1+days && R[j].calculateEndDate() >= date1+days)
					{
						validDate = false; //INVALID DATE ****OVERLAPING***
					}
				}
			}
		}
	}
	if (serviceValid && validDate) //If both conditions satisfies, ALL DATA VALID
	{
		return true;
	}
	else
	{
		return false; //DATA NOT VALID
	}
}

/*
 validDAta
 This funcition is to make a reservation and save it.
 Parameters:
    Reservation array, service pointer array, counter
 Return:
    NONE
 */
void makeRSVP(Reservation R[], Service *S[], int &count)
{
	int clientID, d, m, y, days;
	bool serviceValid;
	bool validDate;
	string serviceKey;
	string op;
	bool valid = false;
	do{ //Reapeat untill user exits or data invalid
		cout << "Client ID: \n";
		cin >> clientID;
        if (clientID == -1)
        {
            break; //user wants to exit
        }
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
		if (da.validDate()) //validating DATE
		{
			valid = validData(R,S,count,da,serviceKey,days,serviceValid,validDate); //validating DATA on function above.
			if (!serviceValid)
			{
				cout << "Service key not valid \n";
			} else if (!validDate)
			{
				cout << "Try other date \n";
			}
		}
		else
		{
			cout << "Invalid date!" << endl;
		}
	}while (!valid);
	R[count].setClientID(clientID); //creating reservation
	R[count].setKey(serviceKey);
	R[count].setDays(days);
	Date date1(d, m, y);
	R[count].setContractDate(date1);
	if (valid) { //RESERVATION MADE
		cout << "Reservation created succefully \n"; //SUCCES
        for (int i = 0; i < 6; i++) {
            if (R[count].getKey() == S[i]->getKey()) // DISPLAYING TOTAL COST
            {
                cout << "Total: $" << S[i]->calculateCost(R[count].getDays())<< endl;
            }
        }
        
		count++;
	}
}

/*
 MAIN APPLICATION
 We made it as modular as possible.
 Parameters:
    NONE
 RETURN:
    0
 */
int main()
{
	Service *S[6];
	Reservation R[20];
	
	int rCount = 0;
	readServiceFiles(S);
	readReservationFiles(R,rCount);
	
	//S[2]->show();
	char opt;
	do //MAIN MENU DISPLAY
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
			case '1':
				consultServiceList(S); // Service List
				break;
			case '2':
				consultRSVPList(R, S, rCount); // Reservations List
				break;
			case '3':
				consultServiceRSVP(R, S, rCount);   // Search Reservations by Service Key
				break;
			case '4':
				searchReservationByDate(R, S, rCount); // Search Reservations by Date
				break;
			case '5':
				makeRSVP(R, S, rCount); // Make Reservation
				break;
		}
	} while(opt != '6');
	writeRSVPFile(R, rCount); //Writing down file.
	cout << "Data saved!" << endl;
	cout << "Exiting..." << endl;

	return 0;
}
