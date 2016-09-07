#include"structure.h"

void structure::input_order(message hhhh, order neworder){
	int starmark = 0;
	if (neworder.get_side() == "B")
	{
		hhhh.received(neworder);
		//buy side

		if ((sell_list.empty()))//若卖表空，且为limit类型则直接填入买表
		{
			if (neworder.get_type() == "limit")
			{
				buy_list[neworder.get_price()].push_back(neworder);
				starmark = 1; //starmark用来标识是否已经进入列表 在后面用作判断
			}

			else
				hhhh.returned(neworder);//订单返回
		}
		else{
			//~~~~~~~~~~~~~
			if (neworder.get_type() == "market")
			{
				while (1)//遍历sell表 每一个价格
				{
					map<double, vector<order>>::iterator sell_iter = sell_list.begin();
					if (sell_iter == sell_list.end())
						break;//订单返回
					else
					{
						//****************************
						for (int i = 0; i <= (sell_iter->second).size() - 1; i++)// 遍历每一个价格的vector
						{
							if (((sell_iter->second)[i]).get_volume() >= neworder.get_volume())
							{

								hhhh.transaction(((sell_iter->second)[i]), neworder);
								//此处输出信息***
								((sell_iter->second)[i]).change_volume(neworder.get_volume());
								neworder.change_volume(neworder.get_volume());


							}
							else  //((sell_iter->second)[i]).get_volume() <neworder.get_volume();
							{
								hhhh.transaction(neworder, ((sell_iter->second)[i]));//	此处输出信息***
								neworder.change_volume(((sell_iter->second)[i]).get_volume());
								((sell_iter->second)[i]).change_volume(((sell_iter->second)[i]).get_volume());
							}
						}
						//以下这一小块程序实现的功能是将一个price水平里 订单数量为0的订单删除（遇到还有数量的订单就停止）
						//*******************************
						while (1)
						{
							vector<order>::iterator temp = (sell_iter->second).begin();
							if (temp == (sell_iter->second).end())
								break;
							else if ((*temp).get_volume() == 0)
								(sell_iter->second).erase(temp);
							else
								break;
						}

						if ((sell_iter->second).size() == 0)
							sell_list.erase(sell_iter);
						else
							break;
						//*******************************
					}
				}
			}
			//~~~~~~~~~~
			if (neworder.get_type() == "limit")
			{
				while (1)//遍历sell表 可以交易的价格, 与上一块唯一不同的地方是：这里不是遍历所有的价格，而是只有小于等于的
				{
					map<double, vector<order>>::iterator sell_iter = sell_list.begin();
					if ((sell_list.size() == 0))
						break;
					else if ((sell_iter->first) > neworder.get_price())
					{
						hhhh.fullinlist(neworder);
						break;
					}
					else
					{
						//****************************
						for (int i = 0; i <= (sell_iter->second).size() - 1; i++)// 遍历每一个价格的vector
						{
							if (((sell_iter->second)[i]).get_volume() >= neworder.get_volume())
							{
								hhhh.transaction(((sell_iter->second)[i]), neworder);//此处输出信息***
								((sell_iter->second)[i]).change_volume(neworder.get_volume());
								neworder.change_volume(neworder.get_volume());

							}
							else  //((sell_iter->second)[i]).get_volume() <neworder.get_volume();
							{
								hhhh.transaction(neworder, ((sell_iter->second)[i]));//	此处输出信息***
								neworder.change_volume(((sell_iter->second)[i]).get_volume());
								((sell_iter->second)[i]).change_volume(((sell_iter->second)[i]).get_volume());
							}
						}
						//以下这一小块程序实现的功能是将一个price水平里 订单数量为0的订单删除（遇到还有数量的订单就停止）
						//*******************************
						while (1)
						{
							vector<order>::iterator temp = (sell_iter->second).begin();
							if (temp == (sell_iter->second).end())
								break;
							else if ((*temp).get_volume() == 0)
								(sell_iter->second).erase(temp);
							else
								break;
						}

						if ((sell_iter->second).size() == 0)
							sell_list.erase(sell_iter);
						else
							break; //如果有一个价钱还有余量说明没有必要再向下看别的价钱了hhh
						//*******************************
					}
				}
				//~~~~~~~~~~~~~~~
			}
		}

	}
	else
	{
		//sell side// order="S";
		if ((buy_list.empty()))//若买表空，买单直接填入卖表
		{
			if (neworder.get_type() == "limit")
			{
				sell_list[neworder.get_price()].push_back(neworder);
				hhhh.fullinlist(neworder);
				//输出一条信息
				starmark = 1;
			}
			else
				hhhh.returned(neworder);//仅仅输出一条信息
		}
		else{
			//~~~~~~~~~~~~~
			if (neworder.get_type() == "market")
			{
				while (1)//遍历buy表 注意要从尾开始向头遍历 因为seller 当然喜欢高价了
				{
					map<double, vector<order>>::iterator buy_iter = buy_list.end();
					if (buy_list.empty())
						break;
					else
					{
						//****************************
						buy_iter--;
						int xx = 0;
						for (int i = 0; i <= (buy_iter->second).size() - 1; i++, xx++)// 遍历每一个价格的vector
						{
							if (((buy_iter->second)[i]).get_volume() >= neworder.get_volume())
							{
								hhhh.transaction(((buy_iter->second)[i]), neworder);	//此处输出信息***
								((buy_iter->second)[i]).change_volume(neworder.get_volume());
								neworder.change_volume(neworder.get_volume());
							}
							else  //((buy_iter->second)[i]).get_volume() <neworder.get_volume();
							{
								hhhh.transaction(neworder, ((buy_iter->second)[i]));//	此处输出信息***
								neworder.change_volume(((buy_iter->second)[i]).get_volume());
								((buy_iter->second)[i]).change_volume(((buy_iter->second)[i]).get_volume());
							}
						}
						//以下这一小块程序实现的功能是将一个price水平里 订单数量为0的订单删除（遇到还有数量的订单就停止）
						while (1)
						{

							vector<order>::iterator temp = (buy_iter->second).begin();
							if (temp == (buy_iter->second).end())
								break;
							else if ((*temp).get_volume() == 0)
								(buy_iter->second).erase(temp);// act like a stack 
							else
								break;
						}
						//*******************************
						if ((buy_iter->second).size() == 0) //若空，删除整个价格
							buy_list.erase(buy_iter);
						else
							break;
					}
				}
			}
			//~~~~~~~~~~
			if (neworder.get_type() == "limit")
			{
				while (1)//遍历buy表上可以交易的价格, 不同的地方是：这里不是遍历所有的价格，而是只遍历足够大的买价
				{
					map<double, vector<order>>::iterator buy_iter = buy_list.end();
					if ((buy_list.size() == 0))
						break;
					else
					{
						buy_iter--;
						if ((buy_iter->first) < neworder.get_price())
						{
							hhhh.fullinlist(neworder);
							break;
						}
						else
						{
							//****************************
							for (int i = 0; i <= (buy_iter->second).size() - 1; i++)// 遍历每一个价格的vector
							{
								if (((buy_iter->second)[i]).get_volume() >= neworder.get_volume())
								{
									hhhh.transaction(((buy_iter->second)[i]), neworder);//此处输出信息***
									((buy_iter->second)[i]).change_volume(neworder.get_volume());
									neworder.change_volume(neworder.get_volume());

								}
								else  //((buy_iter->second)[i]).get_volume() <neworder.get_volume();
								{
									hhhh.transaction(neworder, ((buy_iter->second)[i]));//	此处输出信息***
									neworder.change_volume(((buy_iter->second)[i]).get_volume());
									((buy_iter->second)[i]).change_volume(((buy_iter->second)[i]).get_volume());
								}
							}
							//以下这一小块程序实现的功能是将一个price水平里 订单数量为0的订单删除（遇到还有数量的订单就停止）
							while (1)
							{
								vector<order>::iterator temp = (buy_iter->second).begin();
								if (temp == (buy_iter->second).end())
									break;
								else if ((*temp).get_volume() == 0)
									(buy_iter->second).erase(temp);
								else
									break;
							}
							//*******************************
							if ((buy_iter->second).size() == 0)
								buy_list.erase(buy_iter);
							else
								break;
						}
					}
				}
				//~~~~~~~~~~~~~~~
			}
		}
	}
	if (neworder.get_volume() != 0)
	{
		if (neworder.get_type() == "limit")

		{
			if ((neworder.get_side() == "B") && starmark == 0)
				buy_list[neworder.get_price()].push_back(neworder);
			else if ((neworder.get_side() == "S") && starmark == 0)
				sell_list[neworder.get_price()].push_back(neworder);
			hhhh.partinlist(neworder);
		}
	}
	else{

		//asdsadsadsad
	}

}
void structure::display_sell(){
	map<double, vector<order>>::iterator iter = sell_list.begin();
	cout << '\t' << "       " << "Offer List" << endl;
	cout << "      " << "Offer Price ($) " << '\t' << "Volume " << endl;
	for (; iter != sell_list.end(); iter++)
	{

		cout << '\t' << "   " << iter->first << "   ";
		int sum_volume = 0;
		for (vector<order>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
		{
			sum_volume += (*iter2).get_volume();
		}
		cout << "         " << sum_volume << endl;
	}
	cout << "****************************************" << endl;
	cout << "****************************************" << endl;

}
void structure::display_buy(){
	cout << '\t' << '\t' << "Bid List" << endl;
	cout << '\t' << "Bid Price ($) " << '\t' << "Volume " << endl;
	if (buy_list.size() != 0)
	{
		map<double, vector<order>>::iterator iter = buy_list.end();
		--iter;
		int x = buy_list.size();
		for (; x > 0; x--, iter--)
		{
			cout << '\t' << "   " << iter->first << "   ";
			int sum_volume = 0;
			for (vector<order>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
			{
				sum_volume += (*iter2).get_volume();
			}
			cout << '\t' << "  " << sum_volume << endl;
		}

	}
	cout << endl << endl;
}