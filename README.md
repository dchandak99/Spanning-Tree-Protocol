# Spanning-Tree-Protocol

### Highlights:
- Simulated the network bridge topology as a *distributed system* of nodes, communicating via messages, in **C++**
- Configured nodes to run the protocol and agree upon a *loop-less* logical topology to prevent a *broadcast storm*

### Details:

[Problem Statement](Spanning_Tree_Protocol.pdf)

- Implementation of the Spanning Tree Protocol in C++, with forwarding table and learning bridges implementation. Trace can be printed with first input set as 0 or 1  
- Created own bridge class in bridge.h with behaviour in bridge.cpp  
- Simulation in bridgesim.h and bridgesim.cpp  
- Main in main.cpp  

Sample inputs and outputs are given as the files.
