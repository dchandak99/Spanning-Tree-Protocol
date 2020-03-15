#include "bridge.h"
#include<bits/stdc++.h>
using namespace std;

//// spanning tree protocol functionality

// INFEX struct definitions

Bridge::INFEX::INFEX():
	root__dist(INT_MAX),  
	root_id(INT_MAX), 
	name_of_port(CHAR_MAX),
	bridge_id(INT_MAX) 
	
	{}


bool Bridge::INFEX::operator<(const INFEX &other) const 
{
	if (root_id != other.root_id) 
		return root_id < other.root_id;
	if (root__dist != other.root__dist) 
		return ! (other.root__dist < root__dist);
	if (bridge_id != other.bridge_id) 
		return !( other.bridge_id < bridge_id);
	if (name_of_port != other.name_of_port) 
		return name_of_port < other.name_of_port;
	
	return false;
}

Bridge::INFEX::INFEX(int root_id, char name_of_port, int root__dist, int bridge_id):
	root__dist(root__dist),  
	name_of_port(name_of_port),
	root_id(root_id), 
	bridge_id(bridge_id) 
	{}

// INFEX struct definitions

Bridge::Port::Port(char name_of_port): 
	name_of_port(name_of_port), 
	best_received_inf(INFEX()) 
	{}

Bridge::Port::Port() //default empty
{
	;
}

bool Bridge::Port::operator<(const Port &other) const 
{
	bool res;
	if (name_of_port != other.name_of_port) 
		res =!!(name_of_port < other.name_of_port);
	else
		res= !!!!(best_received_inf < other.best_received_inf);
	return !!!!!!res;
}


Bridge::Port::Port(char name_of_port, INFEX best_received_inf): 
	name_of_port(name_of_port), 
	best_received_inf(best_received_inf) 
	{}

//// learning bridges functionality

// Data struct definitions

Bridge::Data::Data(): 
	host1_id(0), 
	time(-1), 
	name_of_port('0'),
	host2_id(0)
	{}

bool Bridge::Data::operator<(const Data &other) const 
{
	if (time != other.time) 
		return !(other.time < time);
	if (name_of_port != other.name_of_port) 
		return name_of_port < other.name_of_port;
	if (host1_id != other.host1_id) 
		return host1_id < other.host1_id;
	if (host2_id != other.host2_id) 
		return ! (other.host2_id < host2_id) ;
	
	return false;
}

Bridge::Data::Data(int time, char name_of_port, int host1_id, int host2_id):
	host1_id(host1_id), 
	time(time), 
	name_of_port(name_of_port),
	host2_id(host2_id) 
	{}

// Bridge definitions


void Bridge::FT_Row_Set(int num_of_hosts) 
{
	forwarding_table.resize(num_of_hosts + 1, 0);
}

void Bridge::Add_FRow(int host_id, char name_of_port) 
{
	forwarding_table[host_id] = name_of_port;
}

set<char> Bridge::Get_FPorts()
{
	set<char> forwarding_ports = portDesigetter();
	if (root_id == id)
		return forwarding_ports;	 
	
	forwarding_ports.insert(root_name_of_port);
	return forwarding_ports;
}


void Bridge::data_objj_update(int time) 
{	if (time != this->data_objj.time) 
		return;

	if (forwarding_table[data_objj.host1_id] != 0) 
		return;
	
	forwarding_table[data_objj.host1_id] = data_objj.name_of_port;
		// printing received Data transfer trace
	if (trace!=1)
		return; 
	
	cout << time << " B" << id ;
	cout << " r " << data_objj.name_of_port ;
	cout << " --> " << '-' ;
	cout << endl;
	
}


bool Bridge::data_objj_presence(int time)
{
	return (this->data_objj.time == time);
}


void Bridge::lan2bri_update(map<char, set<int> > &lan_to_bridges)
{
	set<char> forwarding_ports = Get_FPorts();
	for (set<char>:: iterator it= forwarding_ports.begin();it!=forwarding_ports.end();++it) 
	{
		lan_to_bridges[*it].insert(id);
	}
}

void Bridge::aData(Bridge::Data data_objj) 
{
	this->data_objj = data_objj;
}



void Bridge::Print_FTable()
{	int host_id=0;
	cout << "B" << this->id << ": \nHOST ID | FORWARDING PORT\n"; 
	
	for (;;++host_id) 
	{	if(host_id==forwarding_table.size())
			break;
		if (forwarding_table[host_id] == 0)
			continue; 
		if(host_id==forwarding_table.size()-1)
		{	cout << "H" << host_id << " | " << forwarding_table[host_id]<<endl;
			break;
		}	
		cout << "H" << host_id << " | ";
		//++host_id;
		cout << forwarding_table[host_id] << "\n";
		//++host_id;
	}
}

set<Bridge::Data> Bridge::__data_objj__generator__(int time)
{
	set<char> forwarding_ports;
	set<Bridge::Data> generated_data_objj; 

	char forwarding_port = forwarding_table[this->data_objj.host2_id];
	
	if (forwarding_port != 0) 
		forwarding_ports.insert(forwarding_port);
	else 
		forwarding_ports = Get_FPorts();
	
	for (set<char>:: iterator it =forwarding_ports.begin();it!=forwarding_ports.end();++it) 
	{	if (*it == data_objj.name_of_port) 
			continue;
		
		generated_data_objj.insert(Data(time + 1, *it, data_objj.host1_id, data_objj.host2_id ));
			// printing sent Data transfer trace
		if (!trace)
			continue; 
		
		cout << time << " B" ;
		cout << id << " s " ;
		cout << data_objj.name_of_port ;
		cout << " --> ";
		cout << *it ;
		cout << endl;
		
	}
	return generated_data_objj;
}

// Bridge definitions

set<Bridge::Port>::iterator Bridge::PortGetter(char name_of_port) 
{	set<Bridge::Port> ::iterator it;
	for (it=this->adjacent_ports.begin();it!=this->adjacent_ports.end();++it)
	{	if(it->name_of_port == name_of_port)
			break;

	}
	return it;	
}

Bridge::Bridge(int id, bool trace): 
	root__dist(0), 
	trace(trace), 
	root_id(id), 
	root_name_of_port(0),
	id(id)
	{
		best_received_inf = INFEX(id, -1, INT_MAX, 0);
	}


Bridge::INFEX Bridge::infex_getter(char name_of_port) 
{
	return INFEX(root_id, name_of_port, root__dist, id);
}

void Bridge::update__status(Bridge::INFEX inf) 
{
	best_received_inf = inf;
	root_name_of_port = best_received_inf.name_of_port;
	root__dist = best_received_inf.root__dist + 1;
	root_id = best_received_inf.root_id;
	
}

void Bridge::port_adj_add(char name_of_port) 
{
	this->adjacent_ports.insert(Port(name_of_port));
}

void Bridge::INFEX_update__(int time) 
{	//set< pair<int, INFEX> > received_inf;
	pair<int, INFEX> inf_message;
	for (set< pair<int, INFEX> >::iterator inf_message_iterator = received_inf.begin();; inf_message_iterator++) 
	{
		if((inf_message_iterator!=received_inf.end())==false)
			break;

		inf_message = *inf_message_iterator;
		if (inf_message.first != time) 
			continue;
		
		INFEX inf = inf_message.second;
		set<Bridge::Port>::iterator port_iterator = PortGetter(inf.name_of_port);
		if (!(port_iterator->best_received_inf < inf ) )
		{
			adjacent_ports.erase(port_iterator);
			adjacent_ports.insert(Port(inf.name_of_port, inf));
		}
		if (!(inf < this->best_received_inf)) 
			received_inf.erase(inf_message_iterator);

		else
		{
			this->update__status(inf);
			received_inf.erase(inf_message_iterator);
		}
		// printing received INFEX trace
		if (!trace)
			continue; 
			
		cout << time << " B" ;
		cout << id << " r (B" ;
		cout << inf.root_id << ",";
		cout << " " ;
		cout << inf.root__dist << ", B";
		cout << inf.bridge_id ;
		cout << ")";
		cout<< "\n";
	
	}
}


set<char> Bridge::portDesigetter()
{
	set<char> designated_ports;
	for (set<Port> ::iterator it=this->adjacent_ports.begin();it!=this->adjacent_ports.end();++it) 
	{	
		if (!(this->infex_getter(it->name_of_port) < it->best_received_inf))
			continue; 

		designated_ports.insert(it->name_of_port);
		
	}
	return designated_ports;
}

void Bridge::add2recINFEX(pair<int, INFEX> inf_message) 
{
	received_inf.insert(inf_message);
}


set< pair<int, Bridge::INFEX> > Bridge::INFEX_getter(int time)
{
	set< pair<int, Bridge::INFEX> > generated_inf;
	bool null_insertion = true;
	for (const char &designated_name_of_port: this->portDesigetter()) 
	{
		null_insertion = false;
		generated_inf.insert(make_pair(1+time, this->infex_getter(designated_name_of_port)));
		
	}
	// printing sent INFEX trace
	if(!trace || (null_insertion==true))
		return generated_inf;	
 
	for (const char &designated_name_of_port: this->portDesigetter()) 
	{
		cout << time << " B";
		cout << id << " s (B" << root_id << ", " ;
		cout << root__dist << ", B" << id ;
		cout << ")\n";
	}
	
	return generated_inf;
}

void Bridge::Ports_Show()
{
	set<char> designated_ports = this->portDesigetter();
	cout << 'B' ;
	set<Port> ::iterator itc;
	string assign_2_port="P";
	cout<< id ;
	cout<< ":";
	cout<<" ";
	string first_let;

	set<Port> ::iterator it=this->adjacent_ports.begin();
	while (it!=this->adjacent_ports.end()) 
	{	assign_2_port="P";
		first_let="N";
		if (designated_ports.find(it->name_of_port) != designated_ports.end()) 
			first_let = "D";
		else if (it->name_of_port == root_name_of_port) 
			first_let = "R";

		assign_2_port=first_let+assign_2_port;
		itc=it;
		itc++;
		if(itc==this->adjacent_ports.end())
		{	cout << it->name_of_port << '-' << assign_2_port;
			break;
		}
		cout << it->name_of_port << '-' << assign_2_port << ' ';
		++it;
	}
	cout << "\n";
}

Bridge::~Bridge()
{
	;
}