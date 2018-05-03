//
//  Planes.h
//  Proyecto_3
//
//  Created by Juan Pablo Ramos on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//

#ifndef Planes_h
#define Planes_h

using namespace std;
#include "Service.h"

class Planes : public Service
{
	public:
	// Constructors
	Planes();
	Planes(string key, string description, char type, double cost, int passengers, int additional);
	// Getters
	int getPassengers();
	int getAdditional();
	// Setters
	void setPassengers(int passengers);
	void setAdditional(int additional);
	// Operations
	double calculateCost(int);
	void show();
	private:
		int passengers, additional;
};
//------------------------------------Method Definitions-------------------------------------
// Constructors
Planes::Planes() : Service()
{
	passengers = 0;
	additional = 0;
}
Planes::Planes(string key, string description, char type, double cost, int passengers, int additional) : Service(key,description,type,cost)
{
	this->passengers = passengers;
	this->additional = additional;
}
// Getters
int Planes::getPassengers()
{
	return passengers;
}
int Planes::getAdditional()
{
	return additional;
}
// Setters
void Planes::setPassengers(int passengers)
{
	this->passengers = passengers;
}
void Planes::setAdditional(int additional)
{
	this->additional = additional;
}
// Operations
/* calculateCost
 This method calculates cost
 PArameters:
    days
 Returns:
    TOtal cost: Double
 */
double Planes::calculateCost(int days)
{
	double cost = 0;
	switch (type) {
		case 'H':
			cost = 50000*days;
			if (additional>0)
			{
				cost += ((50000*0.04)*additional)*days;
			}
			break;
		case 'J':
			cost = 120000*days;
			if (additional>0)
			{
				cost += ((120000*0.04)*additional)*days;
			}
			break;
		case 'A':
			cost = 80000*days;
			if (additional>0)
			{
				cost += ((80000*0.04)*additional)*days;
			}
			break;
	}
	return cost;
}
//This method displays
void Planes::show()
{
	cout<<"Plane Service"<<endl;
	cout<<"Service Key: "<<key<<endl;
	cout<<"Description: "<<description<<endl;
	if (type == 'H')
	{
		cout<<"Type: Helicopter"<<endl;
	}
	else if (type == 'J')
	{
		cout<<"Type: Jet"<<endl;
	}
	else if (type == 'A')
	{
		cout<<"Type: Airplane"<<endl;
	}
	cout<<"Cost Per Day: $"<<costPerDay<<endl;
	cout<<"Passengers: "<<passengers<<endl;
	cout<<"Additional: "<<additional<<endl;
}

#endif /* Planes_h */
