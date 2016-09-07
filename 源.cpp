#include<iostream>
#include<map>
#include<vector>
#include<string>
#include<fstream>
#include"order.h"
#include"message.h"
#include"structure.h"
using namespace std;

int main(){

	structure bigcarl;
	message hhhh;
	ifstream infile;
	infile.open("orz.txt");
	vector<string> input_data;

	int mark = 1;
	string temp;
	int sep = 0;
	while (mark)
	{
		infile >> temp;
		if (infile)
		{
			input_data.push_back(temp);
			if ((input_data.size() > 0) && (input_data.size() % 6 == 0))
			{
				string security_name = input_data[0];
		        string	side = input_data[1];
				string type = input_data[2];
				int volume = atoi((input_data[3]).c_str());
				double price = atof((input_data[4]).c_str());
				string counterparty = input_data[5];
				order carl ( security_name, side, type, volume, price, counterparty);
				//system("cls");
				bigcarl.input_order(hhhh, carl);
				
				input_data.clear();
			}
		}
		else
		{
			mark = 0;
			if (infile.eof())
			{
				cout << endl;
				cout << '\t' << '\t' << '\t' << "---***End of The File***---" << endl<<endl;

			}
			else
			{
				cout << "Wrong file!" << endl;
				exit(0);// method to directly quit th eprogram
			}
		}
	}
	infile.close();
	bigcarl.display_sell();
	bigcarl.display_buy();

	return 1;
}