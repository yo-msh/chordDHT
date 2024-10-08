#include "Node.h"
#include <iostream>
#include <cmath>

using namespace std;

// Constructor to initialize the Node with a given ID and the size of the hash space (m)
Node::Node(int id, int m) : id(id), m(m), successor(nullptr), predecessor(nullptr)
{
    fingerTable.resize(m, nullptr); // Resize the finger table based on the hash space size (m)
}

// Getter for the Node ID
int Node::getId() const
{
    return id;
}

// Getter for the successor node
Node *Node::getSuccessor() const
{
    return successor;
}

// Setter for the successor node
void Node::setSuccessor(Node *newSuccessor)
{
    successor = newSuccessor;
}

// Getter for the predecessor node
Node *Node::getPredecessor() const
{
    return predecessor;
}

// Setter for the predecessor node
void Node::setPredecessor(Node *newPredecessor)
{
    predecessor = newPredecessor;
}

// Method to initialize the finger table for routing
void Node::initializeFingerTable()
{
    for (int i = 0; i < m; ++i)
    {
        // Calculate the target ID for each finger table entry using (n + 2^i) % 2^m
        // This determines the position in the ring to find the appropriate successor node
        int targetId = (id + static_cast<int>(pow(2, i))) % static_cast<int>(pow(2, m));
        fingerTable[i] = findSuccessor(targetId); // Find and set the successor for this entry
    }
    cout << "Finger table initialized for Node " << id << "\n";
}

// Placeholder for finding the actual successor node in a fully functional Chord ring
Node *Node::findSuccessor(int key)
{
    // Check if the key is within the range between this node and its successor
    if (successor && ((id < successor->getId() && key > id && key <= successor->getId()) ||
                      (id > successor->getId() && (key > id || key <= successor->getId()))))
    {
        return successor; // If so, the successor is the responsible node
    }
    else
    {
        // Otherwise, find the closest preceding node and recursively find the successor from there
        Node *node = closestPrecedingNode(key);
        return node->findSuccessor(key);
    }
}

// Method to find the closest preceding node in the finger table for a given key
Node *Node::closestPrecedingNode(int key)
{
    // Iterate through the finger table from the farthest entry to the closest
    for (int i = m - 1; i >= 0; --i)
    {
        // Check if the finger table entry is within the desired range for routing
        if (fingerTable[i] && ((id < fingerTable[i]->getId() && fingerTable[i]->getId() < key) ||
                               (id > key && (fingerTable[i]->getId() > id || fingerTable[i]->getId() < key))))
        {
            return fingerTable[i]; // Return the closest preceding node
        }
    }
    return this; // Return this node if no closer preceding node is found
}

// Method to display the contents of the finger table for debugging purposes
void Node::displayFingerTable() const
{
    cout << "Finger Table for Node " << id << ":\n";
    for (int i = 0; i < m; ++i)
    {
        // Display each entry in the finger table, indicating if an entry is set or not
        if (fingerTable[i])
        {
            cout << "  Entry " << i << ": Node " << fingerTable[i]->getId() << "\n";
        }
        else
        {
            cout << "  Entry " << i << ": None\n";
        }
    }
}
