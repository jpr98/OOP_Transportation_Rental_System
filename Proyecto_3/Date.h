//
//  Date.h
//  Proyecto_3
//
//  Created by Ricardo Ramirez on 4/18/18.
//  Copyright © 2018 Juan Pablo Ramos. All rights reserved.
//
#ifndef Date_h
#define Date_h

#include <iostream>
#include <string>
using namespace std;

class Date{
	public:
		// Constructors
		Date();
		Date(int,int,int);
		// Getters
		int getDay();
		int getMonth();
		int getYear();
		// Setters
		void setDay(int day);
		void setMonth(int month);
		void setYear(int year);
		// Operations
		string nameMonth();
		bool leapYear();
		void show();
		bool validDate();
		// Operators overload
		// >=, <=, == for comparing dates
		friend bool operator>=(Date f1, Date f2);
		friend bool operator<=(Date f1, Date f2);
		friend bool operator==(Date f1, Date f2);
		// + adding days to Date object
		friend Date operator+(Date f1, int dias);
		// >> and << to use Date objects with cin and cout
		friend istream & operator>>(istream &is,Date &f1);
		friend ostream & operator<<(ostream &os,Date f1);
	private:
		int day;
		int month;
		int year;
};
//-----------------------Definition of Methods----------------------------
//constructor
Date::Date(){
    day=0;
    month=0;
    year=0;
}
//constructor with parameters
Date::Date(int day,int month,int year){
    this->day=day;
    this->month=month;
    this->year=year;
    
}
//getters
int Date::getDay(){
    return day;
}
int Date::getMonth(){
    return month;
}
int Date::getYear(){
    return year;
}

//setters
void Date::setDay(int day){
    this->day= day;}
void Date::setMonth(int month){
    this->month=month;}
void Date::setYear(int year){
    this->year=year;}

//operations
string Date::nameMonth(){
    switch (month){
        case 1:return "January";
            break;
        case 2:return "February";
            break;
        case 3:return "March";
            break;
        case 4:return "April";
            break;
        case 5:return "May";
            break;
        case 6:return "June";
            break;
        case 7:return "July";
            break;
        case 8:return "August";
            break;
        case 9:return "September";
            break;
        case 10:return "October";
            break;
        case 11:return "November";
            break;
        case 12:return "December";
            break;
    }
    return 0;
}
//leap year validator
bool Date::leapYear(){
    if (year %4==0 && (year % 100 != 0 || year %400 ==0))
        return true;
    else
        return false;
}
//show method
void Date::show(){
    cout<<day<<"/"<<nameMonth()<<"/"<<year<<" ";
}

//validating a date method
bool Date::validDate()
{
    int monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};
    if (!year || !month || !day || month>12){
        return false;
        cout << "Not a valid date\n";}
    if (leapYear() && month==2){
        monthlen[1]++;}
    if (day>monthlen[month-1]){
        return false;}
    return true;
}

// >=, <=, == for comparing dates
bool operator>=(Date f1, Date f2)
{
    bool valid = false;
    
    if (f1.year == f2.year)
    {
        if(f1.month == f2.month)
        {
            if(f1.day >= f2.day)
                valid = true;
        }
        else if(f1.month > f2.month)
            valid = true;
    }
    else if(f1.year > f2.year )
        valid = true;
    
    return valid;
}

bool operator<=(Date f1, Date f2)
{
    bool valid = false;
    
    if (f1.year == f2.year)
    {
        if(f1.month == f2.month)
        {
            if(f1.day <= f2.day)
                valid = true;
        }
        else if(f1.month < f2.month)
            valid = true;
    }
    else if(f1.year < f2.year)
        valid = true;
    
    return valid;
}

bool operator == (Date f1, Date f2)
{
    bool valid = false;
    
    if (f1.year == f2.year)
    {
        if(f1.month == f2.month)
        {
            if(f1.day == f2.day)
                valid = true;
        }
    }
    return valid;
}
// + adding days to Date object
Date operator+(Date f1, int dias)
{
    Date f2 = f1;
    bool valid = false;
    f2.day += dias;
    
    while(!valid)
    {
        switch(f2.month)
        {
            case 1: case 3: case 5: case 7: case 8: case 10:
                if(f2.day > 31)
                {
                    f2.month++;
                    f2.day -= 31;
                }
                else
                    valid = true;
                
                break;
                
            case 12:
                if(f2.day > 31)
                {
                    f2.day -= 31;
                    f2.year++;
                    f2.month = 1;
                }
                else
                    valid = true;
                
                break;
                
            case 4: case 6: case 9: case 11:
                if(f2.day > 30)
                {
                    f2.month++;
                    f2.day -= 30;
                }
                else
                    valid = true;
                
                break;
                
            case 2:
                if(f2.leapYear())
                {
                    if(f2.day > 29)
                    {
                        f2.month++;
                        f2.day -= 29;
                    }
                    else
                        valid = true;
                    
                }
                else
                {
                    if(f2.day  > 28)
                    {
                        f2.month++;
                        f2.day -= 28;
                    }
                    else
                        valid = true;
                }
                break;
        }
    }
    return f2;
}

// >> and << to use Date objects with cin and cout
istream& operator>>(istream &is, Date &f1)
{
    is >> f1.day;
    is >> f1.month;
    is >> f1.year;
    return is;
}

ostream& operator<<(ostream &os, Date f1)
{
    os <<f1.day<<"/"<<f1.nameMonth()<<"/"<<f1.year;
    return os;
}

#endif /* Date_h */

