#include "iostream"
#include "iomanip"
#include "vector"

using namespace std;

class Invent {
	string ttl;
	bool bb;
	vector <pair<string, bool>> st;

	public:
	Invent (string _ttl, bool _bb, vector <pair<string, bool>> _st): ttl(_ttl), bb(_bb), st(_st) {}
	string getName() {return this->ttl;}
	vector <pair<string, bool>> getShowTime() {return this->st;}
	bool getBlockBuster () {return this->bb;}
	~Invent () {}
};

bool checkday (string s) {
	if ( s.find("Sat") != string::npos || s.find("Sun") != string::npos) {
		return true;
	}
	else
		return false;
}

int main () {
	vector <Invent> table;
	vector <string> names {"The Gentleman", "The Invisible Man", "Sonic Hedgehog", "Bad Boys for Life"};
	vector <bool> bb_types {false, false, true, false};
	vector <vector<pair<string, bool>>> times {{make_pair("Wed 15:30", false), make_pair("Thu 19:00", true), make_pair("Sat 13:00", false)},
									{make_pair("Tue 13:30", false), make_pair("Wed 19:00", true), make_pair("Sun 13:00", false)},
									{make_pair("Mon 16:30", false), make_pair("Fir 14:00", false)},
									{make_pair("Mon 17:30", true), make_pair("Wed 10:00", false), make_pair("Sat 13:00", false), make_pair("Sun 15:00", false)}
								};

	// for storing data
	for (int i(0); i < 4; i++) {
		Invent data(names[i], bb_types[i], times[i]);
		table.push_back(data);
	}

	// end screen variables
	string p_type, daynight, movie_type, vip_type, day;
	double price(14), dis, mat(0);

	// for age data
	int age;
	cout<<"Enter your age: "; cin>>age;


	// select from movies interface
	int mo;
	cout<<"Please select from the following movies: \n";
	do {
		for (int i(0); i < 4; i++)
			cout<<(i+1)<<"- "<<table[i].getName()<<endl;
		cin>>mo;
	} while (mo-1 < 0 || mo-1 > 4);
	mo--;
	// select show time interface
	int user_st;
	vector <pair<string, bool>> shows = table[mo].getShowTime();
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
	movie_type = table[mo].getBlockBuster() ? "blockbuster" : "non-blockbuster";
	price += table[mo].getBlockBuster() ? (0.1*price) : 0;

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

		cout<<"Would you like to purchase VIP seating for "<<table[mo].getName()<<" "<<shows[user_st].first<<"?";
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

	cout<<"************ Seneca Theatre ***************\n";
	cout<<right<<setw(30)<<table[mo].getName()<<" "<<shows[user_st].first<<" "<<setprecision(2)<<price<<endl;

	if (p_type != "Adult") {
		cout<<right<<setw(30)<<"Age discount "<<setprecision(2)<<dis<<endl;
		price -= dis;
	}
	if (pass_flag) {
		cout<<right<<setw(30)<<"Snack Pass "<<setprecision(2)<<(15.00)<<endl;
		price += 15;
	}
	if (vip_flag) {
		cout<<right<<setw(30)<<"VIP seating "<<setprecision(2)<<(5.00)<<endl;
		price += 5;
	}

	double tax = 0.13*price;
	price += tax;

	cout<<right<<setw(30)<<"Tax "<<setprecision(2)<<tax<<endl;
	cout<<right<<setw(30)<<"Total "<<setprecision(2)<<price<<endl;

	return 0;
}
