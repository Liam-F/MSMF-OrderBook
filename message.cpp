#include"message.h"
using namespace std;

void message::received(order hhh){
	string side;
	string price;
	if (hhh.get_side() == "S")
		side = "sell";
	else
		side = "buy";
	if (hhh.get_type() == "market")
		cout << "[Market Message-Received]: " << hhh.get_counterparty() << " , your order to " << side << " with price/value: " << "N/A" << " / " << hhh.get_volume() << " has been received" << endl;
	else
		cout << "[Market Message-Received]: " << hhh.get_counterparty() << " , your order to " << side << " with price/value: " << hhh.get_price() << " / " << hhh.get_volume() << " has been received" << endl;
}
void message::returned(order hhh){
	string side;
	if (hhh.get_side() == "S")
		side = "sell";
	else
		side = "buy";
	cout << "[Market Message-No counterparty]: " << hhh.get_counterparty() << " , we can not find counterparty for your order, the order is being returned" << endl;
}
void message::transaction(order larger, order smaller){
	if ((smaller.get_volume())*(larger.get_volume()) != 0)
	{
		cout << "[Market Message-Transaction]: " << smaller.get_counterparty() << ", Your order is fully completed with the counterparty " << larger.get_counterparty() << endl;
		cout << "[Market Message-Transaction]: " << larger.get_counterparty() << ", Your order is partially completed with the counterparty " << smaller.get_counterparty() << " with volume of " << smaller.get_volume() << endl;
	}
}
void message::fullinlist(order hhh){

	cout << "[Market Message-No counterparty]: " << hhh.get_counterparty() << " , No available counterparty founded, your order has been added in the order list " << endl;
}
void message::partinlist(order hhh){

	cout << "[Market Message-Status]: " << hhh.get_counterparty() << " , your order has been partially fuifiled, the rest of your order ( " << hhh.get_volume() << " ) is now in the list" << endl;
}
void message::partreturn(order hhh){

	cout << "[Market Message-Status]: " << hhh.get_counterparty() << " , your order has been partially fuifiled, the rest of your order (" << hhh.get_volume() << " )has been returned " << endl;
}