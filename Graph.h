#pragma once
#include <iostream>
#include "Vector.h"
#include "flightInformation.h"
#include <string>
#include <cstdlib>
#include "Stack.h"
#include "Queue.h"
using namespace std;
struct flightwithtransit {
	flightInfo dep_trans;
	flightInfo trans_arr;
	Time totalTime;
	int totalCost;
	flightwithtransit() :dep_trans(), trans_arr(), totalTime() { totalCost = 0; }
	void operator=(flightwithtransit f) {
		dep_trans = f.dep_trans;
		trans_arr = f.trans_arr;
		totalTime = f.totalTime;
		totalCost = f.totalCost;
	}
};
ostream& operator << (ostream& output, flightwithtransit& f)
{
	output << f.dep_trans << endl;
	output << f.trans_arr << endl;
	output << "TOTAL TRAVEL TIME : ";
	f.totalTime.printTime();
	cout << endl;
	output << "TOTAL COST : " << f.totalCost << endl;
	return output;
}
template<class T>
//This Class is for QueueNode .
struct AdjListNode {
	T city;//This will contain the name of the city in a node
	Vector<flightInfo> flights;//this class is the vector implimentaion on vector class
	AdjListNode* next;//this pointer will point to next node in graph
};
template<class T>
//this class make adjlist for graph
struct AdjList {
	T City_Name;//when we will make the array of adjlist we will alocate the name of each city to each node
	AdjListNode<T>* head;//it will point to the nodes which will point to the nodes of the city which he flights in those cities
};
template<typename T>
//this class make graph using Adjlist
class Graph {
private:
	int list_Size;//Size of adjlist
	string** Price;//this will contain number of cities and the prices if user wants to stay there
	AdjList<T>* array;//this pointer make adjlist
public:
	Graph(string FlightInfo, string Hotel) {
		flightInfo f;
		Vector<flightInfo> allFlightDetail;
		Vector<string> cities;
		ifstream Flight(FlightInfo);
		string line;
		if (Flight.is_open()) {
			while (getline(Flight, line)) {
				int flag = 1;
				stringstream Extra(line);
				while (getline(Extra, line, ' ')) {
					if (flag == 1) {
						f.setDeparture(line);
						flag = 2;
						if (cities.find(line) == -1) {
							cities.push(line);
						}
					}
					else if (flag == 2) {
						f.setArrival(line);
						flag = 3;
						if (cities.find(line) == -1) {
							cities.push(line);
						}
					}
					else if (flag == 3) {
						f.setDate(line);
						flag = 4;
					}
					else if (flag == 4) {
						f.setDepartureTime(line);
						flag = 5;
					}
					else if (flag == 5) {
						f.setArrivalTime(line);
						flag = 6;
					}
					else if (flag == 6) {
						if (flag == 6 && line[0] >= '0' && line[0] <= '9') {
							f.setPrice(line);
						}
						flag = 7;
					}
					else if (flag == 7) {
						f.setAirrline(line);
					}
				}
				allFlightDetail.push(f);
			}
		}
		Flight.close();
		Price = new string * [2];
		for (int i = 0; i < 2; i++)
			Price[i] = new string[cities.Size()];
		ifstream Stay(Hotel);
		if (Stay.is_open()) {
			int flag = 0, count1 = 0;
			while (getline(Stay, line)) {
				stringstream Extra(line);
				while (getline(Extra, line, ' ')) {
					if (flag == 0) {
						Price[0][count1] = line;
						flag = 1;
					}
					else if (flag == 1) {
						Price[1][count1] = line;
						flag = 0;
						count1++;
					}
				}
			}
		}
		this->list_Size = cities.Size();
		array = new  AdjList<T>[list_Size];
		for (int i = 0; i < list_Size; ++i) {
			array[i].head = NULL;
			array[i].City_Name = cities.get(i);
		}

		for (int i = 0; i < cities.Size(); i++) {
			for (int j = 0; j < allFlightDetail.Size(); j++) {
				if (cities[i] == allFlightDetail[j].getDeparture()) {
					if (!searchParticular(i, allFlightDetail[j].getArrival())) {
						addEdge(i, allFlightDetail[j].getArrival(), allFlightDetail[j]);
					}
					else {
						AdjListNode<T>* temp = NULL;
						AdjListNode<T>* current = array[i].head;
						bool flag = 0;
						while (current != NULL) {
							temp = current;
							if (temp->city == allFlightDetail[j].getArrival()) {
								temp->flights.push(allFlightDetail[j]);
								break;
							}
							current = current->next;
						}
					}
				}
			}
		}
	}
	AdjListNode<T>* AddVertices(T dest) {
		AdjListNode<T>* newNode = new AdjListNode<T>;
		newNode->city = dest;
		newNode->next = NULL;
		return newNode;
	}
	void addEdge(int num, T s, flightInfo f) {
		AdjListNode<T>* temp = NULL;
		AdjListNode<T>* current = array[num].head;
		AdjListNode<T>* newNode = new AdjListNode<T>;
		newNode->city = s;
		newNode->next = NULL;
		newNode->flights.push(f);
		if (current == NULL) {
			array[num].head = newNode;
		}
		else {
			while (current != NULL) {
				temp = current;
				current = current->next;
			}
			temp->next = newNode;
		}
	}
	bool searchParticular(int num, T s) {
		AdjListNode<T>* temp = NULL;
		AdjListNode<T>* current = array[num].head;
		while (current != NULL) {
			temp = current;
			if (temp->city == s) {
				return true;
			}
			current = current->next;
		}
		return false;
	}
	void Print(T City) {
		AdjListNode<T>* pri = new AdjListNode<T>;
		for (int i = 0; i < list_Size; i++) {
			if (array[i].City_Name == City) {
				pri = array[i].head;
				while (pri) {
					pri->flights.print();
					cout << endl;
					pri = pri->next;
				}
			}
			break;
		}
	}
	Date  Date_Input() {//Taking input date form the user
		int day = 0, month = 0, year = 0;
		//Inputting day and Checking its Correct
		cout << "Input Day : " << endl;
		cin >> day;
		while (day <= 0 || day > 31) {
			cout << "\nDay is Invalid Enter Day : " << endl;
			cin >> day;
		}
		//Inputting Month and Checking its Correct
		cout << "\nInput Month : " << endl;
		cin >> month;
		while (month <= 0 || month > 12) {
			cout << "\nMonth is Invalid Enter Month : " << endl;
			cin >> month;
		}
		//Inputting Year and Checking Its Correct
		cout << "\nYear Should Be 4 digit number " << endl;
		cout << "\nInput Year : " << endl;
		cin >> year;
		while (year < 1000 || year>9999) {
			cout << "\nYear is Invalid Enter Month : " << endl;
			cin >> year;
		}
		//Making object of the date and returning that object
		Date d(day, month, year);
		return d;
	}
	Time Time_Input() {//Taking inpur time from the user and Checking it 
		int hour = 0, min = 0;
		//Inputting Hours and Checking it 
		cout << "Input Hour : " << endl;
		cin >> hour;
		while (hour <= 0 || hour > 24) {
			cout << "Invalid Hour Input Again : " << endl;
			cin >> hour;
		}
		//Inputting Minutes and Checking it
		cout << "Input Minute : " << endl;
		cin >> min;
		while (min <= 0 || min > 60) {
			cout << "Invalid Min Input Again : " << endl;
			cin >> min;
		}
		//Making an object of Time and returning it.
		Time ti(hour, min);
		return ti;
	}
void Flight_Checker() {//This Function Take input from the user and calling the function Accordingly.
		bool flag[7] = 0;
		string Origin, Arrival, Name_Of_Airline, Transit_Location;
		int Ticket_Price = 0;
		Date Date_of_Travel;
		Time Departure_Time, Arrival_Time;

		cout << "Input Departure Place of The Flight : " << endl;
		cin >> Origin;
		while (Origin == "") {
			cout << "Departure place is Compulsory Please Enter a Place : " << endl;
			cin >> Origin;
		}

		cout << "\nInput Arival Place of the flight : " << endl;
		cin >> Arrival;
		while (Arrival == "") {
			cout << "Arrival place is Compulsory Please Enter a Place : " << endl;
			cin >> Arrival;
		}

		cout << "Input Date Of Travel : " << endl;
		Date_of_Travel = Date_Input();

		cout << "Input Name of Airline : " << endl;
		cin >> Name_Of_Airline;

		cout << "Input Transit Location : " << endl;
		cin >> Transit_Location;
		Time t;
		cout << "Input Transit Time : " << endl;
		t = Time_Input();
		flag[0] = flag[1] = flag[2] = 1;
		if (Transit_Location != "")
			flag[3] = 1;
		if (Name_Of_Airline != "")
			flag[4] = 1;
		if (Date_of_Travel.Check())
			flag[5] = 1;
		if (t.Check()) {
			flag[6] = 1;
		}
		if (flag[4] == 1) {
			Senario1(Origin, Arrival, Date_of_Travel, Name_Of_Airline);
		}
		else if (flag[3] == 1 && flag[6] == 0) {
			scenario3(Origin, Transit_Location, Arrival, Date_of_Travel);
		}
		else if (flag[6] == 1) {
			scenario4(Origin, Arrival, Date_of_Travel, Transit_Location, t);
		}
		if (flag[3] == 0 && flag[4] == 0 && flag[5] == 0 && flag[6] == 0) {
			cout << "if you want to see flights according to travel time then press 1 otherwise press 2." << endl;
			int res;
			cin >> res;
			if (res == 1) {
				Senario2(Origin, Arrival, Date_of_Travel);
			}
			else if (res == 2) {
				Senario5(Origin, Arrival, Date_of_Travel);
			}
		}
	}

	void Senario5(string dep, string arr, string date) {
		Date d(date);
		flightInfo temp;
		for (int i = 0; i < list_Size; i++) {
			AdjListNode<string>* node = array[i].head;
			while (node) {
				for (int j = 0; j < node->flights.Size(); j++) {
					if (node->flights[j].getDeparture() == dep) {
						if (node->flights[j].getArrival() == arr) {
							if (node->flights[j].getDate() == d) {
								temp = node->flights[j];
								cout << temp;
							}
						}
					}
				}
				node = node->next;
			}
		}
	}
	void scenario3(string dep, string connect, string arr, Date d) {
		stack<flightInfo> st1;
		stack<flightInfo> st2;
		for (int i = 0; i < list_Size; i++) {
			AdjListNode<string>* temp = array[i].head;
			while (temp) {
				for (int j = 0; j < temp->flights.Size(); j++) {
					if (temp->flights[j].getDeparture() == dep) {
						if (temp->flights[j].getArrival() == connect) {
							if (temp->flights[j].getDate() == d)
								st1.push(temp->flights[j]);
						}
					}
					else if (temp->flights[j].getArrival() == arr && temp->flights[j].getDeparture() == connect) {
						if (temp->flights[j].getDate() >= d && temp->flights[j].getDate().getDay() <= d.getDay() + 1)
							st2.push(temp->flights[j]);
					}
				}
				temp = temp->next;
			}
		}
		flightInfo f;
		flightInfo f1;
		while (!st1.isEmpty() && !st2.isEmpty()) {
			if (!st1.isEmpty()) {
				f = st1.pop();
				cout << f << endl;
				cout << "TRAVEL TIME:";
				travelTime(f.getDepartureTime(), f.getArrivalTime()).printTime();
				cout << endl;
			}
			if(!st2.isEmpty()) {
				f1 = st2.pop();
				cout << "TRANSIT TIME : ";
				travelTime(f.getArrivalTime(), f1.getDepartureTime()).printTime();
				cout << endl;
				cout << f1 << endl << "TRAVEL TIME : ";
				travelTime(f1.getDepartureTime(), f1.getArrivalTime()).printTime();
				cout << endl;
			}
		}
		if (st1.isEmpty() && st2.isEmpty()) {
			cout << "There is no flight available between " << dep << " & " << arr << " through " << connect << " on "; d.printDate(); cout << endl;
		}
	}
	Time travelTime(Time dep_time, Time arr_time) {
		Time time;
		if (arr_time.getHours() < dep_time.getHours()) {
			time.setHours((24 - dep_time.getHours()) + arr_time.getHours());
		}
		else if (arr_time.getHours() > dep_time.getHours()){
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
	void Senario1(string dep, string arr, Date date, string Airline, int price) {
		Queue<flightInfo> S_Direct;
		Queue<flightInfo> S_Not_Direct;
		Vector<string> Vec_Str;
		for (int i = 0; i < list_Size; i++) {
			if (array[i].City_Name == dep) {
				AdjListNode<string>* temp = array[i].head;
				while (temp) {
					for (int j = 0; j < temp->flights.Size(); j++) {
						if (temp->flights[j].getArrival() == arr) {
							if (temp->flights[j].getDate() == date) {
								S_Direct.enqueue(temp->flights[j]);
							}
						}
						else {
							if (temp->flights[j].getDate() == date) {
								S_Not_Direct.enqueue(temp->flights[j]);
								Vec_Str.push(temp->flights[j].getArrival());
							}
						}
					}
					temp = temp->next;
				}
				break;
			}
		}
		flightwithtransit fwt;
		if (S_Direct.isEmpty()) {
			cout << "There is no Direct Flight from " << dep << " to " << arr << " ." << endl;
		}
		else {
			cout << "The Direct Flights are : " << endl;
			Vector<flightInfo> Vec;
			while (!S_Direct.isEmpty()) {
				Vec.push(S_Direct.dequeue());
			}
			for (int pass = 1; pass < Vec.Size(); pass++)
			{
				for (int i = 0; i < Vec.Size() - pass; i++)
				{
					if (Vec[i] > Vec[i + 1])
					{
						flightInfo tmp = Vec[i];
						Vec[i] = Vec[i + 1];
						Vec[i + 1] = tmp;
					}
				}
			}
			for (int i = Vec.Size() - 1; i >= 0; i--) {
				flightInfo f = Vec.get(i);
				cout << f << endl;

			}
			for (int i = 0; i < Vec.Size(); i++)
			{
				if (Vec.get(i).getDate() == date && Vec.get(i).getAirline() == Airline)
				{
					cout << "The Total Cost of Direct Flight from " << dep << " to " << arr << " of date " << date.getDay() << "/" << date.getMonth() << "/" << date.getYear() << " is: ";
					cout << Vec.get(i).getPrice();
					cout << " of your selected Airline " << Airline;
				}
			}
		}
		if (S_Not_Direct.isEmpty()) {
			cout << "There is not Indirect Flight : " << endl;
		}
		else {
			Vector<flightInfo> Vec;
			while (!S_Not_Direct.isEmpty()) {
				Vec.push(S_Not_Direct.dequeue());
			}
			Queue<flightInfo> Q1_InDirect;
			Queue<flightInfo> Q2_InDirect;
			for (int i = 0; i < list_Size; i++) {
				for (int k = 0; k < Vec_Str.Size(); k++) {
					if (array[i].City_Name == Vec_Str[k]) {
						AdjListNode<string>* temp = array[i].head;
						while (temp) {
							for (int j = 0; j < temp->flights.Size(); j++) {
								if (temp->flights[j].getDeparture() == Vec_Str[k]) {
									if (temp->flights[j].getArrival() == arr) {
										if (temp->flights[j].getDate() == date) {
											Q1_InDirect.enqueue(temp->flights[j]);
											Q2_InDirect.enqueue(temp->flights[j]);
										}
									}
								}
							}
							temp = temp->next;
						}
					}
				}
			}
			Vector<flightInfo> fl;
			Vector<flightInfo> Vec1;
			while (!Q1_InDirect.isEmpty()) {
				Vec1.push(Q1_InDirect.dequeue());
			}
			for (int i = 0; i < Vec.Size(); i++)
			{
				for (int j = 0; j < Vec1.Size(); j++)
				{
					if (Vec.get(i).getDate() == Vec1.get(j).getDate() && (Vec.get(i).getAirline() == Airline || Vec.get(j).getAirline() == Airline))
					{
						cout << endl;
						int hours = Vec.get(i).getArrivalTime().getHours() - Vec.get(i).getDepartureTime().getHours();
						int mins = Vec.get(i).getArrivalTime().getMinutes() - Vec.get(i).getDepartureTime().getMinutes();
						if (hours < 0)
							hours *= -1;
						if (mins < 0)
							mins *= -1;
						cout << "First Flight from " << Vec.get(i).getDeparture() << " to " << Vec1.get(j).getDeparture() << " PRICE: " << Vec.get(i).getPrice() << " THROUGH FLIGHT " << Vec.get(i).getAirline() << " in " << hours << " and " << mins << ".";
						hours = Vec1.get(j).getArrivalTime().getHours() - Vec1.get(j).getDepartureTime().getHours();
						mins = Vec1.get(j).getArrivalTime().getMinutes() - Vec1.get(j).getDepartureTime().getMinutes();
						if (hours < 0)
							hours *= -1;
						if (mins < 0)
							mins *= -1;
						cout << "\nSecond Flight from " << Vec1.get(j).getDeparture() << " to " << Vec1.get(j).getArrival() << " PRICE: " << Vec1.get(j).getPrice() << " THROUGH FLIGHT " << Vec1.get(j).getAirline() << " in " << hours << " and " << mins << "." << endl;
						cout << "TOTAL COST:";
						int price = Vec.get(i).getPrice() + Vec1.get(j).getPrice();
						cout << price;
						fl.push(Vec.get(i));
						fl.push(Vec1.get(j));
					}
				}
			}
		}
	}
	void Senario2(string dep, string arr, Date date) {
		Queue<flightInfo> S_Direct;
		Queue<flightInfo> S_Not_Direct;
		Vector<string> Vec_Str;
		for (int i = 0; i < list_Size; i++) {
			if (array[i].City_Name == dep) {
				AdjListNode<string>* temp = array[i].head;
				while (temp) {
					for (int j = 0; j < temp->flights.Size(); j++) {
						if (temp->flights[j].getArrival() == arr) {
							if (temp->flights[j].getDate() == date) {
								S_Direct.enqueue(temp->flights[j]);
							}
						}
						else {
							if (temp->flights[j].getDate() == date) {
								S_Not_Direct.enqueue(temp->flights[j]);
								Vec_Str.push(temp->flights[j].getArrival());
							}
						}
					}
					temp = temp->next;
				}
			}
		}

		if (S_Direct.isEmpty()) {
			cout << "There is no Direct Flight from " << dep << " to " << arr << " ." << endl;
		}
		else {
			cout << "The Direct Flights are : " << endl;
			Vector<flightInfo> V;
			while (!S_Direct.isEmpty()) {
				V.push(S_Direct.dequeue());
			}
			flightInfo* conn = V.getarr();
			for (int i = 1; i <= V.Size(); i++) {
				for (int j = 0; j < V.Size() - i; j++) {
					if (conn[j] > conn[j + 1]) {
						flightInfo f = conn[j];
						conn[j] = conn[j + 1];
						conn[j + 1] = f;
					}
				}
			}
			for (int i = 0; i < V.Size(); i++) {
				cout << conn[i] << endl;
			}
		}

		Queue<flightInfo> Q1_InDirect;
		Queue<flightInfo> Q2_InDirect;
			for (int i = 0; i < list_Size; i++) {
				for (int k = 0; k < Vec_Str.Size(); k++) {
					if (array[i].City_Name == Vec_Str[k]) {
						AdjListNode<string>* temp = array[i].head;
						while (temp) {
							for (int j = 0; j < temp->flights.Size(); j++) {
								if (temp->flights[j].getDeparture() == Vec_Str[k]) {
									if (temp->flights[j].getArrival() == arr) {
										if (temp->flights[j].getDate() == date) {
											Q1_InDirect.enqueue(temp->flights[j]);
											Q2_InDirect.enqueue(temp->flights[j]);
										}
									}
								}
							}
							temp = temp->next;
						}
					}
				}
			}
			Vector<flightwithtransit> Vec;
			while (!S_Not_Direct.isEmpty()) {
				flightInfo Not_Direct = S_Not_Direct.dequeue();
				while (!Q1_InDirect.isEmpty()) {
					flightInfo Q1 = Q1_InDirect.dequeue();
					if (Not_Direct.getArrival() == Q1.getDeparture()) {
						flightwithtransit fli;
						fli.dep_trans = Not_Direct;
						fli.trans_arr = Q1;
						Vec.push(fli);
					}
				}
				Q1_InDirect = Q2_InDirect;
			}
			if (Vec.IsEmpty())
				cout << "No Indirect Flights " << endl;
			else {
				flightwithtransit* connected = Vec.getarr();
				for (int i = 0; i < Vec.Size(); i++)
				{
					connected[i].totalTime = Timer(connected[i].dep_trans, connected[i].trans_arr);
					connected[i].totalCost=Vec.get(i).dep_trans.getPrice()+Vec.get(i).trans_arr.getPrice();
				}
				for (int i = 1; i <= Vec.Size(); i++) {
					for (int j = 0; j < Vec.Size() - i; j++) {
						if (connected[j].totalTime > connected[j + 1].totalTime) {
							flightwithtransit f = connected[j];
							connected[j] = connected[j + 1];
							connected[j + 1] = f;
						}
					}
				}
				cout << "The Indirect Flights are : " << endl;
				for (int i = 0; i < Vec.Size(); i++) {
					cout << connected[i] << endl;
				}
			}
		
	}
	Time Timer(flightInfo f1, flightInfo f2) {
		Time t1, t2;
		t1 = travelTime(f1.getDepartureTime(), f1.getArrivalTime());
		t2 = travelTime(f2.getDepartureTime(), f2.getArrivalTime());
		Time t3 = travelTime(f1.getArrivalTime(), f2.getDepartureTime());
		t3 = t3 + t2 + t1;
		return t3;
	}
		void printGraph() {
		for (int i = 0; i < list_Size; i++)
		{
			AdjListNode<string>* adjp = array[i].head;
			cout << "\n Adjacency list of vertex " << i << endl;
			while (adjp)
			{
				adjp->flights.print();
				cout << endl;
				adjp = adjp->next;
			}
			cout << endl << endl;
		}
	}
	void scenario4(string origin, string destination, Date d, string transit, Time transitTime) {
		stack<flightInfo> st1;
		stack<flightInfo> st2;
		for (int i = 0; i < list_Size; i++) {
			AdjListNode<string>* node = array[i].head;
			while (node) {
				for (int j = 0; j < node->flights.Size(); j++) {
					if (node->flights[j].getDeparture() == origin) {
						if (node->flights[j].getArrival() == transit) {
							if (node->flights[j].getDate() == d) {
								st1.push(node->flights[j]);
							}
						}
					}
					else if (node->flights[j].getArrival() == destination && node->flights[j].getDeparture() == transit) {
						if (node->flights[j].getDate() >= d && node->flights[j].getDate().getDay() <= d.getDay() + 1)
							st2.push(node->flights[j]);
					}
				}
				node = node->next;
			}
		}
		Vector<flightwithtransit> v;
		flightwithtransit fwt;
		while (!st1.isEmpty() && !st2.isEmpty()) {
			if (!st1.isEmpty()) {
				fwt.dep_trans = st1.pop();
				fwt.totalCost = fwt.dep_trans.getPrice();
				fwt.totalTime = travelTime(fwt.dep_trans.getDepartureTime(), fwt.dep_trans.getArrivalTime());
			}
			if (!st2.isEmpty()) {
				fwt.trans_arr = st2.pop();
				fwt.totalTime = fwt.totalTime + travelTime(fwt.dep_trans.getArrivalTime(), fwt.trans_arr.getDepartureTime());
				Time t = travelTime(fwt.trans_arr.getDepartureTime(), fwt.trans_arr.getArrivalTime());
				fwt.totalTime.setHours(fwt.totalTime.getHours() + t.getHours());
				fwt.totalCost = fwt.totalCost + fwt.trans_arr.getPrice();
			}
			v.push(fwt);
		}
		flightwithtransit* arr = v.getarr();
		for (int i = 1; i <= v.Size(); i++) {
				for (int j = 0; j < v.Size() - i; j++) {
					if (arr[j].totalTime > arr[j  + 1].totalTime) {
						flightwithtransit f = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = f;
					}
				}
		}
		for (int i = 0; i < v.Size(); i++) {
			cout << arr[i] << endl;
		}
	}
};
