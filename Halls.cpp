#include "Halls.h"
#include <fstream>


void TicketSystem::help()
{
	cout << "The following commands are supported :\n";
	cout << "open <file> \t\t\t\t opens <file>\n";
	cout << "close \t\t\t\t\t closes currently opened file\n";
	cout << "save \t\t\t\t\t saves the currently open file\n";
	cout << "saveas <file> \t\t\t\t saves the currently open file in <file>\n";
	cout << "help \t\t\t\t\t prints this information\n";
	cout << "exit \t\t\t\t\t exists the program\n";

	cout << "addevent <date> <hall> <name> \t\t adds new event <name> on date <date> in hall <hall>\n";
	cout << "freeseats <date> <name> \t\t checks the free seats for event <name> on date <date>\n";
	cout << "book <row> <seat> <date> <name> <note> \t books tickets on <row> seats <seat> for <name> on <date> with <note>\n";
	cout << "unbook <row> <seat> <date> <name> \t cancel reservation for <name> on <date> for seats <seat> on <row> \n";
	cout << "buy <row> <seat> <date> <name> \t\t buys tikets for <name> on <date>on <row> seats <seat>\n";
	cout << "bookings [<date>] [<name>] \t\t prints the booked tickets for [<name>] on [<date>]\n";
	cout << "check <code> \t\t\t\t check if ticket is valid\n";
	cout << "report <from> <to> [<hall>] \t\t report for bought <from> date <to> date in [<hall>]\n";
}

void TicketSystem::open(string fileName)
{
	this->fileName = fileName;
	ifstream file(fileName);
	string buffer;
	if (!file.fail())
	{
		//int hall;
		Hall *temp = nullptr;
		getline(file, buffer);
		while (!buffer.empty())
		{
			if (buffer.find(" ") != string::npos)
			{
				if (!buffer.substr(0, buffer.find(" ")).compare("Hall"))
				{
					int hall, rows, seats;
					buffer = buffer.substr(buffer.find(" ") + 1);
					if (buffer.find(" ") != string::npos)
						hall = stoi(buffer.substr(0, buffer.find(" ")));
					buffer = buffer.substr(buffer.find(" ") + 1);
					if (buffer.find(" ") != string::npos)
						rows = stoi(buffer.substr(0, buffer.find(" ")));
					buffer = buffer.substr(buffer.find(" ") + 1);
					seats = stoi(buffer);
					if (seats)
					{
						temp = new Hall(hall, rows, seats);
						halls.push_back(temp);
					}					
				}
				else 
				{
					string tempName;
					int tempDate;
					buffer = buffer.substr(buffer.find(" ") + 1);
					if (buffer.find(" ") != string::npos)
						tempName = buffer.substr(0, buffer.find(" "));
					buffer = buffer.substr(buffer.find(" ") + 1);
					tempDate = stoi(buffer);

					if(tempDate && temp != nullptr)
						temp->AddEventInternal(tempName, tempDate);
				}
			}
			buffer.clear();
			getline(file, buffer);
		}
	}
	else
	{
		ofstream createFile(fileName, std::ios::trunc);
		createFile.close();
	}
	file.close();
}

void TicketSystem::save()
{
	saveAs(fileName);
}

void TicketSystem::close()
{
	save();
	halls.clear();
	fileName = "";
}

void TicketSystem::saveAs(string name)
{
	ofstream file(name, std::ios::trunc);

	if (!file.fail())
	{
		int hallsSize = halls.size();
		for (int i = 0; i < hallsSize; i++)
		{
			file << "Hall ";
			file << halls[i]->number;
			file << " ";
			file << halls[i]->rows;
			file << " "; 
			file << halls[i]->seats;
			file << "\n";

			int eventsSize = halls[i]->events.size();
			for (int k = 0; k < eventsSize; k++)
			{
				file << "Event ";
				file << halls[i]->events[k].Name.c_str();
				file << " ";
				file << halls[i]->events[k].date;
				file << "\n";
			}
		}
	}
	file.close();
}

TicketSystem::Event::Event() {}
TicketSystem::Event::Event(string name, int date, int rows, int seats) : Name(name), date(date) 
{
	vector<TicketsFlag> tempFlags;
	tempFlags.assign(seats, FREE);
	vector<string> tempNotes;
	tempNotes.assign(seats, "");
	booked = 0;
	bought = 0;
	free = seats * rows;


	this->seats.assign(rows, tempFlags);
	this->notes.assign(rows, tempNotes);
}

void TicketSystem::Event::copy(Event const& copyFrom)
{
	Name = copyFrom.Name;
	date = copyFrom.date;
	bought = copyFrom.bought;
	booked = copyFrom.booked;
	free = copyFrom.free;
	seats = copyFrom.seats;
	notes = copyFrom.notes;
}

TicketSystem::Event::Event(Event const& copyFrom)
{
	copy(copyFrom);
}
TicketSystem::Event& TicketSystem::Event::operator=(Event const& copyFrom)
{
	copy(copyFrom);
	return *this;
}
TicketSystem::Event::~Event() {}

TicketSystem::Hall::Hall() {}

TicketSystem::Hall::Hall(int number, int rows, int seats) :number(number), rows(rows), seats(seats){}

void TicketSystem::Hall::copy(Hall const& copyFrom)
{
	this->number = copyFrom.number;
	this->rows = copyFrom.rows;
	this->seats = copyFrom.seats;
	this->events = copyFrom.events;
}

TicketSystem::Hall::Hall(Hall const& copyFrom)
{
	copy(copyFrom);
}

TicketSystem::Hall& TicketSystem::Hall::operator=(Hall const& copyFrom)
{
	copy(copyFrom);
	return *this;
}

TicketSystem::Hall::~Hall() {}

int TicketSystem::Hall::findEvent(string name, string date)
{
	int size = events.size();
	for (int i = 0; i < size; i++)
		if (!name.compare(events[i].Name) && stoi(date) == events[i].date)
			return i;
	return -1;
}

void TicketSystem::Hall::AddEventInternal(string name, int date)
{
	Event temp(name, date, rows, seats);
	events.push_back(temp);
}

TicketSystem::Hall* TicketSystem::findHall(int num)
{
	int size = halls.size();
	for (int i = 0; i < size; i++)
		if (halls[i]->number == num)
			return halls[i];
	return nullptr;
}

void TicketSystem::addevent(string date, int hall, string name)
{
	Hall* temp = findHall(hall);
	temp->AddEventInternal(name, stoi(date));
}

void TicketSystem::freeseats(string date, string name)
{
	int size = halls.size();
	for (int i = 0; i < size; i++)
	{
		int temp = halls[i]->findEvent(name, date);
		if (temp != -1)
		{
			printf("For %s on date %s there are %d seats free\n", name.c_str(), date.c_str(), halls[i]->events[temp].free);
			return; 
		}
		else
			printf("There is no event %s\n", name.c_str());
	}
}

void TicketSystem::book(int row, int seat, string date,string name, string note)
{
	int size = halls.size();
	for (int i = 0; i < size; i++)
	{
		int temp = halls[i]->findEvent(name, date);
		if (temp != -1)
		{
			if (row < halls[i]->events[temp].seats.size() && seat < halls[i]->events[temp].seats[0].size())
			{
				if (halls[i]->events[temp].seats[row - 1][seat - 1] == FREE)
				{
					halls[i]->events[temp].seats[row - 1][seat - 1] = BOOKED;
					halls[i]->events[temp].notes[row - 1][seat - 1] = note;
					halls[i]->events[temp].booked++;

					return;
				}
				else
					printf("This seat is already taken\n");
			}
		}
		else
			printf("There is no event %s\n", name.c_str());
	}
}

void TicketSystem::unbook(int row, int seat, string date, string name)
{
	int size = halls.size();
	for (int i = 0; i < size; i++)
	{
		int temp = halls[i]->findEvent(name, date);
		if (temp != -1)
		{
			if (row < halls[i]->events[temp].seats.size() && seat < halls[i]->events[temp].seats[0].size())
			{
				if (halls[i]->events[temp].seats[row - 1][seat - 1] == BOOKED)
				{
					halls[i]->events[temp].seats[row - 1][seat - 1] = FREE;
					halls[i]->events[temp].notes[row - 1][seat - 1] = "";
					halls[i]->events[temp].booked--;

					return;
				}
				else
					printf("You could not unbook this seat\n");
			}
		}
		else
			printf("There is no event %s\n", name.c_str());
	}
}

void TicketSystem::buy(int row, int seat, string date, string name)
{
	int size = halls.size();
	for (int i = 0; i < size; i++)
	{
		int temp = halls[i]->findEvent(name, date);
		if (temp != -1)
		{
			if (row < halls[i]->events[temp].seats.size() && seat < halls[i]->events[temp].seats[0].size())
			{
				if (halls[i]->events[temp].seats[row - 1][seat - 1] != BOUGHT)
				{
					if (halls[i]->events[temp].seats[row - 1][seat - 1] == BOOKED)
						halls[i]->events[temp].booked--;
					else
						halls[i]->events[temp].free--;
					halls[i]->events[temp].seats[row - 1][seat - 1] = BOUGHT;
					halls[i]->events[temp].notes[row - 1][seat - 1] = "";
					halls[i]->events[temp].bought++;
					printf("Your ticket code is %d_%s_%s_%d_%d\n", halls[i]->number, name.c_str(), date.c_str(), row, seat); //code will be HallNum + eventName + date + row + seat

					return;
				}
				else
					printf("This seat is already taken\n");
			}
		}
		else
			printf("There is no event %s\n", name.c_str());
	}
}

void TicketSystem::check(string code)
{
	int hallNum = -1;
	string eventName = "";
	string date = "";
	int row = -1;
	int seat = -1;

	string temp = "";
	int tempSize = 0;


	temp = code.substr(0, code.find("_"));
	if (code.find("_") != string::npos)
	{
		hallNum = stoi(temp);
		code = code.substr(code.find("_") + 1);
	}
	if (code.find("_") != string::npos)
	{
		eventName = code.substr(0, code.find("_"));
		code = code.substr(code.find("_") + 1);
	}
	if (code.find("_") != string::npos)
	{
		date = code.substr(0, code.find("_"));
		code = code.substr(code.find("_") + 1);
	}
	if (code.find("_") != string::npos)
	{
		row = stoi(code.substr(0, code.find("_")));
		code = code.substr(code.find("_") + 1);
	}
	seat = stoi(code.substr(0, code.find("_")));

	if (hallNum && eventName.compare("") && date.compare("") && row && seat)
	{
		Hall* temp = findHall(hallNum);
		int eventNum = temp->findEvent(eventName, date);
		if (row <= temp->rows && seat <= temp->seats && eventNum)
		{
			if (temp->events[eventNum].seats[row - 1][seat - 1] == BOUGHT)
			{
				printf("The code is valid\n");
				return;
			}
		}
	}

	printf("There is no ticket with this code\n");
}

void TicketSystem::reportInternal(int from, int to, Hall* hall)
{
	int eventSize = hall->events.size();
	for (int k = 0; k < eventSize; k++)
	{
		if (hall->events[k].date > from && hall->events[k].date < to)
			printf("In hall %d event %s have %d sold tickets\n", hall->number, hall->events[k].Name.c_str(), hall->events[k].bought);
	}
}

void TicketSystem::report(int from, int to, string hall) 
{
	if (hall.empty())
	{
		int size = halls.size();
		for (int i = 0; i < size; i++)
		{
			reportInternal(from, to, halls[i]);
		}
	}
	else
	{
		string buffer = hall.substr(2);
		Hall* tempHall;
		while (!buffer.empty())
		{
			if (buffer.find(" ") != string::npos)
			{
				tempHall = findHall(stoi(buffer.substr(0, buffer.find(" "))));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			else
			{
				tempHall = findHall(stoi(buffer));
				buffer.clear();
			}
			reportInternal(from, to, tempHall);
		}
	}
}

void TicketSystem::bookingsInternal(Hall* hall)
{
	int eventSize = hall->events.size();
	for (int k = 0; k < eventSize; k++)
		printf("In hall %d event %s have %d booked tickets\n", hall->number, hall->events[k].Name.c_str(), hall->events[k].booked);
}

void TicketSystem::bookings(string date, string name)
{
	if (date.empty() && name.empty())
	{
		int size = halls.size();
		for (int i = 0; i < size; i++)
		{
			int eventSize = halls[i]->events.size();
			for (int k = 0; k < eventSize; k++)
				printf("In hall %d event %s have %d booked tickets\n", halls[i]->number, halls[i]->events[k].Name.c_str(), halls[i]->events[k].booked);
		}
	}
	else
	{
		string bufferDate = date;
		string bufferName = name;
		while (!bufferDate.empty() && !bufferName.empty())
		{
			if (bufferDate.find(" ") != string::npos && bufferName.find(" ") != string::npos)
			{
				int size = halls.size();
				for (int i = 0; i < size; i++)
				{
					int eventSize = halls[i]->events.size();
					for (int k = 0; k < eventSize; k++)
						if (!bufferName.substr(0, bufferName.find(" ")).compare(halls[i]->events[k].Name) && stoi(bufferDate.substr(0, bufferDate.find(" "))) == halls[i]->events[k].date)
							printf("In hall %d event %s have %d booked tickets\n", halls[i]->number, halls[i]->events[k].Name.c_str(), halls[i]->events[k].booked);

				}
				bufferDate = bufferDate.substr(bufferDate.find(" ") + 1);
				bufferName = bufferName.substr(bufferName.find(" ") + 1);
			}
			else
			{
				int size = halls.size();
				for (int i = 0; i < size; i++)
				{
					int eventSize = halls[i]->events.size();
					for (int k = 0; k < eventSize; k++)
						if (!name.compare(halls[i]->events[k].Name) && stoi(date) == halls[i]->events[k].date)
							printf("In hall %d event %s have %d booked tickets\n", halls[i]->number, halls[i]->events[k].Name.c_str(), halls[i]->events[k].booked);
				}
				bufferName.clear();
				bufferDate.clear();
			}
		}
	}
}