#include"order.h"

order::order(string security, string buyorsell, string morl, int quantity, double pricetag, string party){
	security_name = security;
	side = buyorsell;
	type = morl;
	volume = quantity;
	price = pricetag;
	counterparty = party;
}
//other functions are too sample, so I defined them in the header file