//
//  Reservation.h
//  Proyecto_3
//
//  Created by Juan Pablo Ramos on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//

#ifndef Reservation_h
#define Reservation_h

using namespace std;
#include "Date.h"

class Reservation
{
	public:
		// Constructors
		Reservation();
		Reservation(string key, int clientID, int days, Date contract);
		// Getters
		string getKey();
		int getClientID();
		int getDays();
		Date getContractDate();
		// Setters
		void setKey(string key);
		void setClientID(int clientID);
		void setDays(int days);
		void setContract(Date contract);
		// Operations
		Date calculateEndDate();
	private:
		string key;
		int clientID, days;
		Date contractDate;
};
//------------------------------------------Method Definition-----------------------------------
// Constructors
Reservation::Reservation()
{
	key = "N/A";
	clientID = 0;
	days = 0;
	contractDate;
}
Reservation::Reservation(string key, int clientID, int days, Date contract);
// Getters
string getKey();
int getClientID();
int getDays();
Date getContractDate();
// Setters
void setKey(string key);
void setClientID(int clientID);
void setDays(int days);
void setContract(Date contract);
// Operations
Date calculateEndDate();

#endif /* Reservation_h */
