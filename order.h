#ifndef ORDER_H
#define ORDER_H
#include<string>
using namespace std;
class order{
public:
	order(){};
	order(string security, string buyorsell, string morl, int quantity, double pricetag, string party);
	void change_volume(int x){ volume = volume - x; }
	string get_name(){ return security_name; }
	string get_side(){ return side; }
	double get_price(){ return price; }
	int get_volume(){ return volume; }
	string get_type(){ return type; }
	string get_counterparty(){ return counterparty; }
	void set_security_name(string a){ security_name = a; }
	void set_side(string a){ side = a; }
	void set_type(string a){ type = a; }
	void set_volume(int a){ volume = a; }
	void set_price(double a){ price = a; }
	void set_counterparty(string a){ counterparty = a; }
private:
	string security_name;
	string side;
	string type;
	int volume;
	double price;
	string counterparty;

};





#endif