// Ticket.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Halls.h"


int main()
{
	string buffer;
	getline(cin, buffer);
	TicketSystem NDK;
	bool isClose = 0;

	while (1)
	{
		if (!buffer.compare(0, 4, "open"))
		{
			NDK.open(buffer.substr(5));
			if (isClose == 1)
				isClose = 0;
		}
		else if (isClose)
		{
			printf("Please enter command open.\n");
		}
		else if (!buffer.compare(0, 5, "close"))
		{
			NDK.close();
			isClose = 1;
		}
		else if (!buffer.compare(0, 6, "saveas"))
		{
			NDK.saveAs(buffer.substr(7));
		}
		else if (!buffer.compare(0, 4, "save"))
		{
			NDK.save();
		}
		else if (!buffer.compare(0, 4, "help"))
		{
			NDK.help();
		}
		else if (!buffer.compare(0, 4, "exit"))
		{
			cout << "Exiting the program...\n";
			break;
		}
		else if (!buffer.compare(0, 8, "addevent"))
		{
			string date, name;
			int hall = -1;
			buffer = buffer.substr(9);
			if (buffer.find(" ") != string::npos)
			{
				date = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				hall = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			name = buffer;
			
			if(hall != -1)
				NDK.addevent(date, hall, name);
		}
		else if (!buffer.compare(0, 9, "freeseats"))
		{
			string date, name;
			buffer = buffer.substr(10);
			if (buffer.find(" ") != string::npos)
			{
				date = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			name = buffer;

			NDK.freeseats(date, name);
		}
		else if (!buffer.compare(0, 8, "bookings"))
		{
			string date = "", name = "";
			if (buffer.size() > 8)
			{
				buffer = buffer.substr(10);
				if (buffer.find("]") != string::npos)
				{
					date = buffer.substr(0, buffer.find("]"));
					buffer = buffer.substr(buffer.find("]") + 3);
				}
				if (buffer.find("]") != string::npos)
					name = buffer.substr(0, buffer.find("]"));
			}
			NDK.bookings(date, name);
		}
		else if (!buffer.compare(0, 5, "book "))
		{
			string date, name, note;
			int row = -1, seat = -1;
			buffer = buffer.substr(5);
			if (buffer.find(" ") != string::npos)
			{
				row = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				seat = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				date = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				name = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			else
			{
				name = buffer;
				buffer = "";
			}
			note = buffer;

			if (row != -1 && seat != -1)
				NDK.book(row, seat, date, name, note);
		}
		else if (!buffer.compare(0, 6, "unbook"))
		{
			string date, name, note;
			int row = -1, seat = -1;
			buffer = buffer.substr(7);
			if (buffer.find(" ") != string::npos)
			{
				row = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				seat = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				date = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			name = buffer;

			if (row != -1 && seat != -1)
				NDK.unbook(row, seat, date, name);
		}
		else if (!buffer.compare(0, 3, "buy"))
		{
			string date, name, note;
			int row = -1, seat = -1;
			buffer = buffer.substr(4);
			if (buffer.find(" ") != string::npos)
			{
				row = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				seat = stoi(buffer.substr(0, buffer.find(" ")));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			if (buffer.find(" ") != string::npos)
			{
				date = buffer.substr(0, buffer.find(" "));
				buffer = buffer.substr(buffer.find(" ") + 1);
			}
			name = buffer;

			if (row != -1 && seat != -1)
				NDK.buy(row, seat, date, name);
		}
		else if (!buffer.compare(0, 5, "check"))
		{
			NDK.check(buffer.substr(6));
		}
		else if (!buffer.compare(0, 6, "report"))
		{
			string hall = "";
			int date1 = -1, date2 = -1;

			buffer = buffer.substr(7);
			if (buffer.size() > 16) // size of two dates
			{
				date1 = stoi(buffer.substr(0, 8));
				date2 = stoi(buffer.substr(9, 16));
			}
			hall = buffer.substr(17);
			
			if(date1 != -1 && date2 != -1)
				NDK.report(date1, date2, hall);
		}
		else
			cerr << "Please enter a vaid command. You can use the \"help\" command to check the valid ones\n";


		buffer.clear();
		getline(cin, buffer);
	}



	return 0;
}

