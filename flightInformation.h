#pragma once
#include <iostream>
#include <string>
using namespace std;

class Date {
	int day;
	int month;
	int year;
public:
	Date() {
		day = 0;
		month = 0;
		year = 0;
	}
	Date(int d, int m, int y) {
		day = d;
		month = m;
		year = y;
	}
	Date(string d) {
		int count = 0, res;
		for (int i = 0; i < d.length(); i++) {
			char a = d[i];
			string temp;
			while (a != '/' && a != '\0') {
				temp += a;
				i++;
				a = d[i];
			}
			res = stoi(temp);
			if (count == 0) {
				day = res;
				count++;
			}
			else if (count == 1) {
				month = res;
				count++;
			}
			else if (count == 2) {
				year = res;
				count++;
			}
		}
	}
	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }
	bool Check() {
		if (day <= 0 || month <= 0 || year < 0)
			return false;
		else
			return true;
	}
	void setDay(int d) { day = d; }
	void setMonth(int m) { month = m; }
	void setYear(int y) { year = y; }
	void printDate() {
		cout << day << "/" << month << "/" << year;
	}
	bool operator==(Date d) {
		bool flag = false;
		if (day == d.getDay()) {
			if (month == d.getMonth()) {
				if (year == d.getYear()) {
					flag = true;
				}
			}
		}
		return flag;
	}
	void operator=(Date d) {
		day = d.getDay();
		month = d.getMonth();
		year = d.getYear();
	}
	bool operator >= (Date d) {
		bool flag = 0;
		if (day >= d.getDay()) {
			if (month >= d.getMonth()) {
				if (year >= d.getYear()) {
					flag = 1;
				}
			}
		}
		return flag;
	}
};
class Time {
	int hours;
	int minutes;
public:
	Time() {
		hours = 0;
		minutes = 0;
	}
	Time(int h, int m) {
		hours = h;
		minutes = m;
	}
	int getHours() { return hours; }
	int getMinutes() { return minutes; }
	bool Check() {
		if (hours <= 0 || minutes <= 0)
			return false;
		else
			return true;
	}
	void setHours(int h) { hours = h; }
	void setMinutes(int m) { minutes = m; }
	void printTime() {
		cout << hours << ":";
		if (minutes == 0) {
			cout << "00";
		}
		else {
			cout << minutes;
		}
	}
	bool operator==(Time t) {
		bool flag = false;
		if (hours == t.getHours()) {
			if (minutes == t.getMinutes()) {
				flag = true;
			}
		}
		return flag;
	}
	bool operator>(Time t) {
		bool flag = 0;
		if (hours > t.getHours()) {
			flag = 1;
		}
		else if (hours == t.getHours()) {
			if (minutes > t.getMinutes()) {
				flag = 1;
			}
		}
		return flag;
	}
	Time operator+(Time t) {
		hours += t.getHours();
		minutes += t.getMinutes();
		Time res(hours, minutes);
		return res;
	}
	bool operator<(Time t) {
		bool flag = 0;
		if (hours < t.getHours()) {
			flag = 1;
		}
		else if (hours == t.getHours()) {
			if (minutes < t.getMinutes()) {
				flag = 1;
			}
		}
		return flag;
	}
	void operator=(Time t) {
		hours = t.getHours();
		minutes = t.getMinutes();
	}
};
class flightInfo {
	string departure;
	string arrival;
	Date date;
	Time departureTime;
	Time arrivalTime;
	int price;
	string airline;
public:
	flightInfo() :date(), departureTime(), arrivalTime() {
		departure = "";
		arrival = "";
		price = 0;
		airline = "";
	}
	void setDeparture(string dep) { departure = dep; }
	void setArrival(string arr) { arrival = arr; }
	void setPrice(string p) {
		int res = stoi(p);
		price = res;
	}
	void setAirrline(string air) { airline = air; }
	void setDate(string d) {
		int count = 0, res;
		for (int i = 0; i < d.length(); i++) {
			char a = d[i];
			string temp;
			while (a != '/' && a != '\0') {
				temp += a;
				i++;
				a = d[i];
			}
			res = stoi(temp);
			if (count == 0) {
				date.setDay(res);
				count++;
			}
			else if (count == 1) {
				date.setMonth(res);
				count++;
			}
			else if (count == 2) {
				date.setYear(res);
				count++;
			}
		}
	}
	void setDepartureTime(string t) {
		int count = 0, res;
		for (int i = 0; i < t.length(); i++) {
			char a = t[i];
			string temp;
			while (a != ':' && a != '\0') {
				temp += a;
				i++;
				a = t[i];
			}
			res = stoi(temp);
			if (count == 0) {
				departureTime.setHours(res);
				count++;
			}
			else if (count == 1) {
				departureTime.setMinutes(res);
				count++;
			}
		}
	}
	void setArrivalTime(string t) {
		int count = 0, res;
		for (int i = 0; i < t.length(); i++) {
			char a = t[i];
			string temp;
			while (a != ':' && a != '\0') {
				temp += a;
				i++;
				a = t[i];
			}
			res = stoi(temp);
			if (count == 0) {
				arrivalTime.setHours(res);
				count++;
			}
			else if (count == 1) {
				arrivalTime.setMinutes(res);
				count++;
			}
		}
	}
	string getDeparture() { return departure; }
	string getArrival() { return arrival; }
	Date getDate() { return date; }
	Time getDepartureTime() { return departureTime; }
	Time getArrivalTime() { return arrivalTime; }
	int getPrice() { return price; }
	string getAirline() { return airline; }
	bool operator==(flightInfo f) {
		bool flag = false;
		if (departure == f.getDeparture()) {
			if (arrival == f.getArrival()) {
				if (date == f.getDate()) {
					if (departureTime == f.getDepartureTime()) {
						if (arrivalTime == f.getArrivalTime()) {
							if (price == f.getPrice()) {
								if (airline == f.getAirline()) {
									flag == true;
								}
							}
						}
					}
				}
			}
		}
		return flag;
	}
	Time calculateTime(Time dep_time, Time arr_time) {
		Time time;
		if (arr_time.getHours() < dep_time.getHours()) {
			time.setHours((24 - dep_time.getHours()) + arr_time.getHours());
		}
		else if (arr_time.getHours() > dep_time.getHours()) {
			time.setHours(arr_time.getHours() - dep_time.getHours());
		}
		if (arr_time.getMinutes() < dep_time.getMinutes()) {
			time.setMinutes((60 - dep_time.getMinutes()) + arr_time.getMinutes());
			time.setHours(time.getHours() - 1);
		}
		else if (arr_time.getMinutes() > dep_time.getMinutes()) {
			time.setMinutes(arr_time.getMinutes() - dep_time.getMinutes());
			time.setHours(time.getHours() - 1);
		}
		return time;
	}
	bool operator>(flightInfo f) {
		bool flag = 0;
		if (price > f.getPrice()) {
			if (calculateTime(departureTime, arrivalTime) > calculateTime(f.getDepartureTime(), f.getArrivalTime())) {
				flag = 1;
			}
		}
		return flag;
	}
	void operator=(flightInfo f) {
		departure = f.getDeparture();
		arrival = f.getArrival();
		date = f.getDate();
		departureTime = f.getDepartureTime();
		arrivalTime = f.getArrivalTime();
		price = f.getPrice();
		airline = f.getAirline();
	}
};

ostream& operator << (ostream& out, flightInfo& f)
{
	out << "Departure City : " << f.getDeparture() << endl;
	out << "Arrival City : " << f.getArrival() << endl;
	out << "Date : ";
	f.getDate().printDate();
	out << endl;
	out << "Departure Time : ";
	f.getDepartureTime().printTime();
	out << endl;
	out << "Arrival Time : ";
	f.getArrivalTime().printTime();
	out << endl;
	out << "Ticket Price : " << f.getPrice() << endl;
	out << "Airline : " << f.getAirline() << endl;
	return out;
}
