#ifndef NODE_H
#define NODE_H

#include <vector>

class Node
{
public:
    // Constructor, id is the unique identifier of the node, m is the number of bits in the identifier
    Node(int id, int m);

    // Getters and setters

    // Get the unique identifier of the node
    int getId() const;

    // Get the successor of the node
    Node *getSuccessor() const;

    // Set the successor of the node
    void setSuccessor(Node *successor);

    // Get the predecessor of the node
    Node *getPredecessor() const;

    // Set the predecessor of the node
    void setPredecessor(Node *predecessor);

    // Initialize the finger table
    void initializeFingerTable();

    // Update the finger table of the node
    void updateFingerTable(int index, Node *node);

    // Find the successor of a given id
    Node *findSuccessor(int id);

    // Find the closest preceding node of a given id
    Node *closestPrecedingNode(int id);

    // Display the finger table (for debugging/testing purposes)
    void displayFingerTable() const;

private:
    int id;                          // Unique identifier of the node
    int m;                           // Number of bits in the identifier
    Node *successor;                 // Successor of the node
    Node *predecessor;               // Predecessor of the node
    std::vector<Node *> fingerTable; // Finger table of the node
};

#endif
