#include<bits/stdc++.h>
#include "bridge.h" 
using namespace std;

class Simu
{

	public:
		Simu();

		void Transfer_FTConstruction(int num_of_data_transfers,vector<Bridge> &network_graph, vector<char> &host_to_lan, vector< pair<int, int> > &data_transfers);
		
		void Proto_LANread(vector<Bridge> &network_graph, map< char, vector<int> > &lan_to_bridges,int num_of_lans, vector<char> &host_to_lan);
		

		void ReadNetworkGraph(int num_of_bridges, bool trace, vector<Bridge> &network_graph, map< char, vector<int> > &lan_to_bridges);

		~Simu();
};