#include "bridgesim.h"
#include <bits/stdc++.h>
using namespace std;

int main() 
{
	bool trace; 
	int num__bridges; 
	cin >> trace;

	vector< pair<int, int> > data_transfers; 
	cin >> num__bridges;
	int num__data_transfers;

	vector<Bridge> network_graph;
	int num__hosts; 
	map< char, vector<int> > lan_2_bridges;
	Simu *sim=new Simu();

	sim->ReadNetworkGraph(num__bridges, trace, network_graph, lan_2_bridges); // indexed from 1 to num__bridges
	vector<char> host_2_lan; 
	
	sim->Proto_LANread(network_graph, lan_2_bridges, lan_2_bridges.size(), host_2_lan);

	cin >> num__data_transfers;
	
	sim->Transfer_FTConstruction(num__data_transfers, network_graph, host_2_lan, data_transfers);

}
