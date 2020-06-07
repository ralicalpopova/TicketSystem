#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum TicketsFlag {FREE, BOOKED, BOUGHT};

class TicketSystem
{
	struct Event
	{
		string Name;
		int date;
		int bought;
		int booked;
		int free;
		vector<vector<TicketsFlag>> seats;
		vector<vector<string>> notes;

		Event();
		Event(string name, int date, int rows = 0, int seats = 0);
		void copy(Event const& copyFrom);
		Event(Event const& copyFrom);
		Event& operator=(Event const& copyFrom);
		~Event();
	};

	struct Hall
	{
		int number;
		int rows;
		int seats; 
		vector <Event> events;

		Hall();
		Hall(int number, int rows, int seats);
		void copy(Hall const& copyFrom);
		Hall(Hall const& copyFrom);
		Hall& operator = (Hall const& copyFrom);
		void AddEventInternal(string name, int date);
		int findEvent(string name, string date);
		~Hall();
	};

	string fileName;
	vector <Hall *> halls;
	void reportInternal(int from, int to, Hall* hall);
	void bookingsInternal(Hall* hall);
	Hall* findHall(int num);

public:
	void open(string fileName);
	void close();
	void save();
	void saveAs(string fileName);
	void help();

	void addevent(string date, int hall, string name);
	void freeseats(string date, string name);
	void book(int row, int seat, string date,string name, string note);
	void unbook(int row, int seat, string date, string name);
	void buy(int row, int seat, string date, string name);
	void bookings(string date = "", string name = "");
	void check(string code); // code will be HallNum + eventName + date + row + seat 
	void report(int from, int to, string hall = "");
};
