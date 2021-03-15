#ifndef INVENT_H
#define INVENT_H

#include "iostream"
#include "iomanip"
#include "vector"

using namespace std;

class Inventory {
	string movieName;
	bool bb;
	vector <pair<string, bool>> st;

	public:
	Inventory () {}
	Inventory (string _ttl, bool _bb, vector <pair<string, bool>> _st): movieName(_ttl), bb(_bb), st(_st) {}
	
	string getName();
	vector <pair<string, bool>> getShowTime();
	bool getBlockBuster ();

	~Inventory () {}
};

#endif