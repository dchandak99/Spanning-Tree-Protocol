#include<bits/stdc++.h>
using namespace std;

class Bridge 
{		
	public:
		
		// spanning tree protocol - INFEX is the messages exchanged - the tuple
		struct INFEX 
		{	
			int root_id;
			char name_of_port;
			int root__dist;
			int bridge_id; 
			
			INFEX();
			INFEX(int root_id, char name_of_port, int root__dist, int bridge_id);
			bool operator<(const INFEX &other) const;
		};


		// learning bridges functionality
		struct Data 
		{	int host2_id; 
			char name_of_port;
			int time;
			int host1_id; 
			
			Data();
			Data(int time, char name_of_port, int host1_id, int host2_id);
			bool operator<(const Data &other) const;
		};	

		// for describing a port
		struct Port 
		{
			char name_of_port; 
			INFEX best_received_inf;
			Port(char name_of_port);
			Port();
			Port(char name_of_port, INFEX best_received_inf);
			bool operator<(const Port &other) const;
		};

		


	protected:

		bool trace;


		// learning bridges functionality
	
		set<char> Get_FPorts() ;

		vector<char> forwarding_table;
	
		void Add_FRow(int host_id, char name_of_port);

		Data data_objj;
	

		// spanning tree protocol functionality
		int root_id, root__dist, id; 

		INFEX best_received_inf;
	
		void update__status(INFEX inf);

		set< pair<int, INFEX> > received_inf;
		
		set<char> portDesigetter() ;

		INFEX infex_getter(char name_of_port) ;
	
		set<Port>::iterator PortGetter(char name_of_port) ;
	
		set<Port> adjacent_ports;
	
		char root_name_of_port;



	public:
		Bridge(int id, bool trace);

		void port_adj_add(char name_of_port);

		// learning bridges functionality
		void FT_Row_Set(int num_of_hosts);

		void Print_FTable() ;

		void lan2bri_update(map<char, set<int> > &lan_to_bridges) ;

		set<Data> __data_objj__generator__(int time) ;

		void aData(Data data_objj);

		bool data_objj_presence(int time);

		void data_objj_update(int time);


		// spanning tree protocol functionality
		void add2recINFEX(pair<int, INFEX> inf_message);

		void INFEX_update__(int time);

		void Ports_Show();

		set< pair<int, INFEX> > INFEX_getter(int time);

		~Bridge();


};