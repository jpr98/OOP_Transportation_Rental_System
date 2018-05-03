//
//  Cars.h
//  Proyecto_3
//
//  Created by Juan Pablo Ramos on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//

#ifndef Cars_h
#define Cars_h

using namespace std;
#include "Service.h"

class Cars : public Service //Inherence
{
	public:
	// Constructors
	Cars();
	Cars(string key, string description, char type, double cost, bool bulletProof, bool driver);
	// Getters
	bool getBulletProof();
	bool getDriver();
	// Setters
	void setBulletProof(bool bulletProof);
	void setDriver(bool driver);
	// Operations
	double calculateCost(int);
	void show();
	private:
		bool bulletProof, driver;
};
//-------------------------------------Method definitions-------------------------------------
// ***********Default Constructors***********
Cars::Cars() : Service()
{
	bulletProof = false;
	driver = false;
}
//***********Constructors with parameters***********
Cars::Cars(string key, string description, char type, double cost, bool bulletProof, bool driver) : Service(key,description,type,cost)
{
	this->bulletProof = bulletProof;
	this->driver = driver;
}
// ***********Getters***********
bool Cars::getBulletProof()
{
	return bulletProof;
}
bool Cars::getDriver()
{
	return driver;
}
// ***********Setters***********
void Cars::setBulletProof(bool bulletProof)
{
	this->bulletProof = bulletProof;
}
void Cars::setDriver(bool driver)
{
	this->driver = driver;
}
// ***********Operations***********
/*  calculateCost
    This method calculates costs
 Parameters:
    days to rent
 Returns:
    total to pay
 */
double Cars::calculateCost(int days)
{
	double cost = 0;
	switch (type) {
		case 'S':
			cost = 800*days;
			if (driver)
			{
				cost += 400*days;
			}
			if (bulletProof)
			{
				cost += (800*0.4)*days;
			}
			break;
		case 'M':
			cost = 600*days;
			if (driver)
			{
				cost += 400*days;
			}
			if (bulletProof)
			{
				cost += (600*0.4)*days;
			}
			break;
		case 'T':
			cost = 400*days;
			if (driver)
			{
				cost += 400*days;
			}
			if (bulletProof)
			{
				cost += (400*0.4)*days;
			}
			break;
	}
	return cost;
}

/*  show
 This method shows
 Parameters:
    NONE
 Returns:
    NONE
 */
void Cars::show()
{
	cout<<"Car Service"<<endl;
	cout<<"Service Key: "<<key<<endl;
	cout<<"Description: "<<description<<endl;
	if (type == 'S')
	{
		cout<<"Type: Suburban"<<endl;
	}
	else if (type == 'M')
	{
		cout<<"Type: Mercedes"<<endl;
	}
	else if (type == 'T')
	{
		cout<<"Type: Altima"<<endl;
	}
	cout<<"Cost Per Day: $"<<costPerDay<<endl;
	if (driver)
	{
		cout<<"Driver: Yes"<<endl;
	}
	else
	{
		cout<<"Driver: No"<<endl;
	}
	if (bulletProof)
	{
		cout<<"Bulletproof: Yes"<<endl;
	}
	else
	{
		cout<<"Bulletproof: No"<<endl;
	}
}

#endif /* Cars_h */
