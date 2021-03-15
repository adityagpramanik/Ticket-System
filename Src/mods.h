#ifndef MODS_H
#define MODS_H

#include "fstream"
#include "invent.cpp"
#include "seq.h"
#include "stdio.h"
#include "database.h"

#define Print cout<<
#define In cin>>
#define Clear system ("clear") //system ("cls") for windows


using namespace std;

    bool checkday (string s) {
		if ( s.find("Sat") != string::npos || s.find("Sun") != string::npos) {
			return true;
		}
		else
			return false;
	}

	void FeedTicket () {
		fstream writef("tickets.dat", ios::app | ios::binary);
		string mname;
		vector <pair<string, bool>> shows;
		int num;
		char bb;
		bool _bb;

		Print "Enter name of the movie: ";
		getline(cin, mname, '\n');

		Print "Is it a blockbuster movie (y/n): ";
		In bb;

		_bb = bb == 'y' ? true : false;

		Print "Enter number of shows: ";
		In num;

		for (int i(0); i < num; i++) {
			string showtime;
			bool flag(false);

			getline (cin, showtime, '\n');
			size_t loc = showtime.find(" ");

			if (loc != string::npos) {
				if (showtime[loc+1] == '2' || (showtime[loc+1] == '1' && showtime[loc+2] >= '7'))
					flag = true;
			}
			shows.push_back(make_pair(showtime, flag));
		}

		Inventory ticket(mname, _bb, shows);

		writef.write( (char *) &ticket, sizeof(ticket));
		writef.close();
	}

	void Booking () {
		// end screen variables
		string p_type, daynight, movie_type, vip_type, day;
		double price(14), dis, mat(0);
		fstream tickets("tickets.dat", ios::in | ios::binary);
		fstream bill("text.txt", ios::app);

		int age;
		vector <Inventory> invent;

		Print "-------------- Booking Ticket -------------------\n\n";
		Print "Enter your age: "; cin>>age;


		// select from movies interface
		int mo;
		int i(0);
		Print "Please select from the following movies: \n";

		while (tickets) {
			Inventory tick;

			tickets.read ( (char *) &tick, sizeof(Inventory));
			invent.push_back(tick);
			i++;
		}

		do {
			for (int i(0); i < invent.size(); i++)
				cout<<(i+1)<<"- "<<invent[i].getName()<<endl;
			cin>>mo;
		} while (mo-1 < 0 || mo-1 > invent.size());
		mo--;
		// select show time interface
		int user_st;
		vector <pair<string, bool>> shows = invent[mo].getShowTime();
		int size = shows.size();

		cout<<"Select one of the following showing times: \n";
		do {

			for (int i(0); i < size; i++) {
				cout<<(i+1)<<"- "<<shows[i].first<<endl;
			}
			cin>>user_st;
		} while (user_st-1 < 0 || user_st-1 > size);
		user_st--;
		// if it's evening show then option for VIP seating
		string vip;
		bool vip_flag(false);

		daynight = shows[user_st].second ? "evening" : "matinee";
		mat = shows[user_st].second ? 3: 0;

		day = checkday (shows[user_st].first)? "Weekend " + daynight: daynight;

		// additional 20% for weekend
		price += checkday (shows[user_st].first)? 0.2*price : 0;

		// additional 10% for blockbuster movie
		movie_type = invent[mo].getBlockBuster() ? "blockbuster" : "non-blockbuster";
		price += invent[mo].getBlockBuster() ? (0.1*price) : 0;

		if (age <= 16) {
			p_type = "Child";
			dis = 0.15*price;
		}
		else if (age >= 65) {
			p_type = "Senior";
			dis = 0.1*price;
		}
		else
			p_type = "Adult";

		if (shows[user_st].second) {

			cout<<"Would you like to purchase VIP seating for "<<invent[mo].getName()<<" "<<shows[user_st].first<<"?";
			cin>>vip;


			while(vip != "Y" && vip != "N") {
				cout<<"Invalid selection must be: Y or N\n";
				cin>>vip;
			}

			vip_flag = vip == "Y"? true : false;
		}


		char pass;
		bool pass_flag(0);

		cout<<"Would you like to purchase our snack pass? "; cin>>pass;

		pass_flag = pass == 'y'? true:false;
		price += mat == 3? mat : 0;


		bill<<"************ Seneca Theatre ***************\n";
		bill<<right<<setw(30)<<invent[mo].getName()<<" "<<shows[user_st].first<<" "<<setprecision(2)<<price<<endl;

		if (p_type != "Adult") {
			bill<<right<<setw(30)<<"Age discount "<<setprecision(2)<<dis<<endl;
			price -= dis;
		}
		if (pass_flag) {
			bill<<right<<setw(30)<<"Snack Pass "<<setprecision(2)<<(15.00)<<endl;
			price += 15;
		}
		if (vip_flag) {
			bill<<right<<setw(30)<<"VIP seating "<<setprecision(2)<<(5.00)<<endl;
			price += 5;
		}

		double tax = 0.13*price;
		price += tax;

		bill<<right<<setw(30)<<"Tax "<<setprecision(2)<<tax<<endl;
		bill<<right<<setw(30)<<"Total "<<setprecision(2)<<price<<endl;

		bill.close();
		tickets.close();
	}

	void Option () {
		int input;

		Print"-------------- Ticket System -------------------\n\n";
		Print"1. Enter show details\n2. Book ticket\n3. Exit";
		In input;

		while (input > 3 || input < 1) {
			Print"Selection is invalid! Please try again.";
			In input;
		}

		switch (input) {
			case 1: FeedTicket();
			break;

			case 2: Booking();
			break;

			default: exit(0);
		}
	}
 
	void Login() {
		string name, pass;
		fstream readf("index.dat", ios::in | ios::binary);
		Database d;

		Print "-------------- Login -------------------\n\n";
		Print "Enter username: ";
		In name;

		state: {
			Print "Enter password: ";
			In pass;


			while (readf) {
				readf.read( (char *) &d, sizeof(d));

				string dname, dpass;
				Encrypt eu(d.getUname()), ep(d.getPass());

				eu.decryption();
				ep.decryption();

				dname = eu.getMssg();
				dpass = ep.getMssg();

				if (name == dname && pass == dpass) {
					Print "Login successful!";
					Option();
				}
			}
			string s;

			Print "Wrong password! press 'y' to continue or press 'q' to exit";
			In s;

			if (s == "q") {
				Clear;
				Print "Exit.";
				exit(0); 

			}
			else
				goto state;
		}
		readf.close();
	}

	void Register() {
		Clear;

		fstream data("index.dat", ios::app | ios::binary);
		string name, uname, pass, mob, email;

		Print "-------------- Register yourself -------------------\n\n";

		Print "Enter your name: ";
		In name;

		Print "Enter your email address: ";
		In email;

		Print "Enter your mobile number: ";
		In mob;

		Print "Create username: ";
		In uname;

		Print "Create password: ";
		In pass;

		Encrypt e[5] {uname, pass, name, mob, email};

		for (int i(0); i < 5; i++)
			e[i].encryption();

		uname = e[0].getMssg();
		pass = e[1].getMssg();
		name = e[2].getMssg();
		mob = e[3].getMssg();
		email = e[4].getMssg();

		Print uname <<" "<< pass <<" "<< name << " " << mob << " " << email <<endl;

		Database d(uname, pass, name, mob, email);
		data.write((char *) &d, sizeof(d));

		int k;
		In k;
		Clear;
		data.close();

		Login();
	}

	void TicketSystem () {
		int input;

		Print"-------------- Ticket System -------------------\n\n";
		Print"1. Register\n2. Login\n3. Exit";
		In input;

		while (input > 3 || input < 1) {
			Print"Selection is invalid! Please try again.";
			In input;
		}

		switch (input) {
			case 1: Register();
			break;

			case 2: Login();
			break;

			default: exit(0);
		}
	}

#endif