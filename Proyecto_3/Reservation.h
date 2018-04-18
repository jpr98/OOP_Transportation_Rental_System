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
}
Reservation::Reservation(string key, int clientID, int days, Date contract)
{
	this->key = key;
	this->clientID = clientID;
	this->days = days;
	contractDate = contract;
}
// Getters
string Reservation::getKey()
{
	return key;
}
int Reservation::getClientID()
{
	return clientID;
}
int Reservation::getDays()
{
	return days;
}
Date Reservation::getContractDate()
{
	return contractDate;
}
// Setters
void Reservation::setKey(string key)
{
	this->key = key;
}
void Reservation::setClientID(int clientID)
{
	this->clientID = clientID;
}
void Reservation::setDays(int days)
{
	this->days = days;
}
void Reservation::setContract(Date contract)
{
	contractDate = contract;
}
// Operations
Date Reservation::calculateEndDate()
{
	Date returnDate;
	returnDate = contractDate + days;
	return returnDate;
}

#endif /* Reservation_h */
