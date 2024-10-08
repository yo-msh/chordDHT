#include "Node.h"
#include <iostream>

int main()
{
    int m = 3; // Number of bits for the identifier space, can represent 2^m unique IDs
    Node node1(1, m);
    Node node2(2, m);
    Node node4(4, m);

    // Manually set up the successors to mimic a ring structure (for testing purposes)
    node1.setSuccessor(&node2);
    node2.setSuccessor(&node4);
    node4.setSuccessor(&node1);

    // Set up predecessors (optional, for completeness)
    node1.setPredecessor(&node4);
    node2.setPredecessor(&node1);
    node4.setPredecessor(&node2);

    // Initialize the finger tables for each node
    node1.initializeFingerTable();
    node2.initializeFingerTable();
    node4.initializeFingerTable();

    // Display finger tables to verify setup
    std::cout << "Node 1:" << std::endl;
    node1.displayFingerTable();

    std::cout << "\nNode 2:" << std::endl;
    node2.displayFingerTable();

    std::cout << "\nNode 4:" << std::endl;
    node4.displayFingerTable();

    return 0;
}
