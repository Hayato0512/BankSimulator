/* 
 * BinaryHeap.h
 *
 * 
 
 *
 * Description: Minimum Binary Heap data collection ADT class. 
 *              Minimum implementation.
 *
 * Class Invariant:  Always a Minimum Binary Heap
 * 
 * Author: Hayato Koyama
 *
 * Last Modification: March 25, 2022
 *
 */   
 
#pragma once

#include <iostream>
#include "Event.h"
#include "EmptyDataCollectionException.h"   // To do: Feel free to recycle an exception class from Assignment 3.

using namespace std;

template<class ElementType>
class BinaryHeap {

private:
	unsigned int elementCount;
	Event* elements;
	// Utility method - Recursively put the array back into a minimum Binary Heap.
	void reHeapUp(unsigned int indexOfBottom);

	// Utility method - Recursively put the array back into a minimum Binary Heap.
	void reHeapDown(unsigned int indexOfRoot);  
   
public:
	// Default Constructor
	BinaryHeap(); 
	//destructor to prevent memory leak
	~BinaryHeap();

	//void printHeap();
	
    // Description: Returns the number of elements in the Binary Heap.
    // Postcondition:  The Binary Heap is unchanged by this operation.
	// Time Efficiency: O(1)
    unsigned int getElementCount() const;

	// Description: Inserts newElement into the Binary Heap.
	//              It returns "true" if successful, otherwise "false".        
	// Postcondition: Remains a Minumum Binary Heap after the insertion.
	// Time Efficiency: O(log2 n)
	bool insert(Event& newElement);
	   
	// Description: Removes (but does not return) the element located at the root.
	// Precondition: This Binary Heap is not empty.
	// Postcondition: Remains a minimum Binary Heap after the removal.	
	// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
	// Time Efficiency: O(log2 n)
	void remove();

	// Description: Retrieves (but does not remove) the element located at the root.
	// Precondition: This Binary Heap is not empty.
	// Postcondition: This Binary Heap is unchanged.
	// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
	// Time Efficiency: O(1) 
	Event retrieve() const;

	// For Testing Purposes
	// Description: Prints the content of "this". 
	//friend ostream & operator<<(ostream & os, const BinaryHeap& rhs);
   
}; // end BinaryHeap
#include "BinaryHeap.cpp"