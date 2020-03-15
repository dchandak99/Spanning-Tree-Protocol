#include <bits/stdc++.h>
#include "bridgesim.h"

using namespace std;

Simu::Simu() //No variables in this Simu class
{}


//eXXEPTION SAFE
//REF::https://codereview.stackexchange.com/questions/206754/an-exception-safe-wrapper-for-stdstoi
int stoii(const string& str, int* p_value, size_t* pos = 0, int base = 10) {
    // wrapping stoi because it may throw an exception

    try {
        *p_value = stoi(str, pos, base);
        return 0;
    }

    catch (const invalid_argument& ia) {
        //cerr << "Invalid argument: " << ia.what() << endl;
        return -1;
    }

    catch (const out_of_range& oor) {
        //cerr << "Out of Range error: " << oor.what() << endl;
        return -2;
    }

    catch (const exception& e)
    {
        //cerr << "Undefined error: " << e.what() << endl;
        return -3;
    }
}

Simu::~Simu()
{;;}

// _FTable_construct by Learning Bridges 

void Simu::Transfer_FTConstruction(int num_of_data_objj_transfers, vector<Bridge> &network_graph, vector<char> &host_to_lan, vector< pair<int, int> > &data_objj_transfers) 
{	
	string host1, host2; 
	int j;
	int host1_value,host2_value;
	int bridge_num=1;
	int num_of_hosts = host_to_lan.size()-1;
	vector<Bridge>:: iterator it_bri;
	j=host1_value=host2_value=0;

	while( j++ < num_of_data_objj_transfers ) 
	{	cin >> host1; 
		cin >> host2;
		//++i;
		//try{
		host2_value = stoi(host2.substr(1, host2.length()-1));
		host1_value = stoi(host1.substr(1, host1.length()-1));
		data_objj_transfers.push_back(make_pair(host1_value, host2_value));
		//}
		//catch(exception &e)
		//{}
	}

	int global_time = 0;
	int num_of_bridges = network_graph.size() - 1;
	map<char, set<int> > lan_to_bridges;
	vector<pair<int,int> > ::iterator i;
	set<Bridge::Data> generated_data_objj;
	

	it_bri=network_graph.begin();
	++it_bri;

	for (; it_bri!=network_graph.end(); ++it_bri) 
	{	
		it_bri->FT_Row_Set(num_of_hosts);

		it_bri->lan2bri_update(lan_to_bridges);
	}
	int time;

	//ITERATORS

	
	set<int>:: iterator b;
	set<int>:: iterator rec_bri;
	set<Bridge::Data>:: iterator it;

	for (i= data_objj_transfers.begin();i!=data_objj_transfers.end();++i) 
	{
		global_time += 100;
		int host1_id = i->first, host2_id = i->second;
		time = global_time;

		char host1_lan, host2_lan;
		host1_lan = host_to_lan[host1_id];
		host2_lan = host_to_lan[host2_id];
		

		for(b=lan_to_bridges[host1_lan].begin();b!=lan_to_bridges[host1_lan].end();++b)
		{	network_graph[*b].aData(Bridge::Data(time + 1, host1_lan, host1_id, host2_id));
		}
		++time;

		while (global_time-time > -100) 
		{	it_bri=network_graph.begin();
			++it_bri;

			for (; it_bri!=network_graph.end(); ++it_bri) 
			{
				it_bri->data_objj_update(time);
			}
			it_bri=network_graph.begin();
			++it_bri;

			for (; it_bri!=network_graph.end(); ++it_bri) 
			{
				if (!it_bri->data_objj_presence(time))
				{	continue;
				}

				generated_data_objj = it_bri->__data_objj__generator__(time);
				for (it=generated_data_objj.begin();it!=generated_data_objj.end();++it) 
				{	for (rec_bri=lan_to_bridges[it->name_of_port].begin();rec_bri!=lan_to_bridges[it->name_of_port].end();++rec_bri) 
					{
						if (*rec_bri == bridge_num) 
						{
							continue;
						}
						network_graph[*rec_bri].aData(*it);
					}
			
				}
				bridge_num++;
			}
			++time;
		}

		it_bri=network_graph.begin();
		++it_bri;

		for (; it_bri!=network_graph.end(); ++it_bri) 
		{
			it_bri->Print_FTable();
		}
		cout << "\n";
	}
}


// Spanning Tree Protocol implementation and reading second part of input

void Simu::Proto_LANread(vector<Bridge> &network_graph, map< char, vector<int> > &lan_to_bridges,int num_of_lans, vector<char> &host_to_lan) 
{
	int num_of_bridges;
	int time = 0;
	int bridge_num=0;

	set< pair<int, Bridge::INFEX> > generated_messages;
	set< pair<int, Bridge::INFEX> >:: iterator m;
	num_of_bridges = network_graph.size() - 1;
	vector<int> ::iterator rec_bri;
	Bridge::INFEX inf ;
	int host_id;
	char lan;
	vector<Bridge>:: iterator i;

	do 
	{	i=network_graph.begin();
		++i;

		for (; i!=network_graph.end(); ++i) 
		{
			i->INFEX_update__(time);
		}

		i=network_graph.begin();
		++i;
		bridge_num=1;

		for (; i!=network_graph.end(); ++i) 
		{
			generated_messages =  i->INFEX_getter(time);
			for (m =generated_messages.begin();m!=generated_messages.end();++m) 
			{
				inf = m->second;
				for (rec_bri =lan_to_bridges[inf.name_of_port].begin();rec_bri!=lan_to_bridges[inf.name_of_port].end();++rec_bri) 
				{
					if (*rec_bri == bridge_num)
						continue; 
					
					network_graph[*rec_bri].add2recINFEX(*m);
					
				}
			}
			bridge_num++;
		}
		time++;
	}while(time>=100==false);

	int j =0;
	
	i=network_graph.begin();
	++i;

	for (; i!=network_graph.end(); ++i) 
	{
		i->Ports_Show();
	}

	//Reading LAn and the HOSTsss
	
	bool first=false;

	while (j < num_of_lans ) 
	{
		string line, input_word; 
		
		//fgets(line);
		//REF::https://stackoverflow.com/questions/18318980/taking-input-of-a-string-word-by-word
		getline(cin, line); 
		istringstream iss(line);
		first = true; 
		if(line!="")
			++j;
		//read_lan_count++;
		
		while (iss >> input_word) 
		{
			if (!first) 
			{	//try{
				host_id = stoi(input_word.substr(1, input_word.length()-1));
				if(host_to_lan.size()>host_id)
				{	
					host_to_lan[host_id] = lan;
					continue;
				}
				
				host_to_lan.resize(host_id+1);
				host_to_lan[host_id] = lan;
				continue;
				//}
				//catch(exception &e)
				//{	//cout<<input_word<<endl;
					//cout<<line<<endl;
				//	continue;
				//}

			}
		 
			first = false;
			lan = input_word[0];
			}
		}
}


void Simu::ReadNetworkGraph(int num_of_bridges, bool trace, vector<Bridge> &network_graph, map< char, vector<int> > &lan_to_bridges) 
{	
	//REF::http://www.cplusplus.com/reference/vector/vector/reserve/
	
	network_graph.push_back(Bridge(0, trace));
	int read_bridge_count =0;
	int bridge_num;
	read_bridge_count=bridge_num=0;

	string line, input_word; 
	bool first;
	bridge_num = 1;

	while(bridge_num < num_of_bridges+1) 
	{
		network_graph.push_back(Bridge(bridge_num, trace));
		++bridge_num ;
	}
	//REF:https://stackoverflow.com/questions/25475384/when-and-why-do-i-need-to-use-cin-ignore-in-c 
	//ignre used for getline later
	cin.ignore();
	//char x;
	//cin>>x;
	//cout<<num_of_bridges<<endl;
	while (read_bridge_count < num_of_bridges ) 
	{
		
		//REF::https://stackoverflow.com/questions/18318980/taking-input-of-a-string-word-by-word
		getline(cin, line); 
		istringstream iss(line);
		//cout<<line<<endl;
		first = true; 

		if(line!="")
		++read_bridge_count;

		while (iss >> input_word) 
		{
			if (!first) 
			{
				lan_to_bridges[input_word[0]].push_back(bridge_num);
				network_graph[bridge_num].port_adj_add(input_word[0]);
				continue;
			} 
			 
			first = false;
			//try{
			bridge_num = stoi(input_word.substr(1, input_word.length()-2));	
			//}
			//catch(exception &e){}
			
		}
	}
	map<char,vector<int> >:: iterator it;

	for(it=lan_to_bridges.begin();it!=lan_to_bridges.end();++it)
	{
		sort((it->second).begin(),((*it).second).end());
	}
}
