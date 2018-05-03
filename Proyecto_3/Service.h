//
//  Service.h
//  Proyecto_3
//
//	ABSTRACT CLASS
//	Service is the base class for Cars and Planes. Operation method are pure virtual.
//
//  Created by Juan Pablo Ramos on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//

#ifndef Service_h
#define Service_h

using namespace std;

class Service
{
	public:
		// Constructors
		Service();
		Service(string key, string description, char type, double cost);
		// Getters
		string getKey();
		string getDescription();
		char getType();
		double getCostPerDay();
		// Setters
		void setKey(string key);
		void setDescription(string description);
		void setType(char type);
		void setCostPerDay(double cost);
		// Operations
		virtual double calculateCost(int) = 0;
		virtual void show() = 0;
	protected:
		string key, description;
		char type;
		double costPerDay;
};
//----------------------------------------Method definition------------------------------------
// ***********Default constructor***********
Service::Service()
{
	key = "N/A";
	description = "N/A";
	type = '0';
    costPerDay = 0;
}
//***********Constructor with parameters***********
Service::Service(string key, string description, char type, double cost)
{
	this->key = key;
	this->description = description;
	//if (type == 'A'||type == 'H'||type == 'J'||type == 'M'||type == 'S'||type == 'T')
	//{
		this->type = type;
	//}
	costPerDay = cost;
}
// ***********Getters***********
string Service::getKey()
{
	return key;
}
string Service::getDescription()
{
	return description;
}
char Service::getType()
{
	return type;
}
double Service::getCostPerDay()
{
	return costPerDay;
}
// ***********Setters***********
void Service::setKey(string key)
{
	this->key = key;
}
void Service::setDescription(string description)
{
	this->description = description;
}
void Service::setType(char type)
{
	this-> type = type;
}
void Service::setCostPerDay(double cost)
{
	costPerDay = cost;
}

#endif /* Service_h */
