/* 
 * BinaryHeap.cpp
 *

 * 
 * Blank space 2: Refer to our lecture notes for the data structure used as CDT.
 * Description: ______minimum____ Binary Heap data collection ADT class. 
 *              _____minimum_____ implementation.
 *
 * Class Invariant:  Always a ____minimum______ Binary Heap
 * 
 * Author: Hayato Koyama
 *
 * Last Modification: March 25 2022
 *
 */  
#define Capacity 50 //under the assumption that default capacity is 50. please change this macro if needed.
#include "BinaryHeap.h"  // Header file

  
// Default Constructor
template<class ElementType>
BinaryHeap<ElementType>::BinaryHeap() {
   elementCount = 0;
   elements = new Event[Capacity];
  
   
} // end of default constructor

//Destructor to prevent memory leak (already checked with using Valgrind)
template<class ElementType>
BinaryHeap<ElementType>::~BinaryHeap(){
	delete[] elements;
}

	
// Description: Returns the number of elements in the Binary Heap.
// Postcondition:  The Binary Heap is unchanged by this operation.
// Time Efficiency: O(1)
template<class ElementType>
unsigned int BinaryHeap<ElementType>::getElementCount() const {
   return elementCount;
}  // end getElementCount


// Description: Inserts newElement into the Binary Heap.
//              It returns "true" if successful, otherwise "false".        
// Postcondition: Remains a __________ Binary Heap after the insertion.
// Time Efficiency: O(log2 n)
template<class ElementType>
bool BinaryHeap<ElementType>::insert(Event& newElement) {

    bool ableToInsert = false;
  
	
	unsigned int indexOfBottom = elementCount;		//first, just insert the newElement into the last index.
	elements[indexOfBottom] = newElement;
	elementCount++;
	ableToInsert = true;
	reHeapUp(indexOfBottom);						//and call reHeapUp to reorder the heap.
	
    return ableToInsert;

} // end insert


// Utility method - Recursively put the array back into a Minimum Binary Heap.
template<class ElementType>
void BinaryHeap<ElementType>::reHeapUp(unsigned int indexOfBottom) {

   
   unsigned int indexOfRoot = 0;
   // Base case: Element is not the root.
   if(indexOfBottom > indexOfRoot){//if more than one element;
	unsigned int indexOfParent = (indexOfBottom-1)/2;
	if(elements[indexOfBottom]<=elements[indexOfParent]){		//if parent is bigger, swap them
		//swap
	   Event temp = elements[indexOfParent];
	   elements[indexOfParent] = elements[indexOfBottom];
	   elements[indexOfBottom] = temp;
	   reHeapUp(indexOfParent);									//call reHeapUp recursively.
	}
   }


	return;
	
} // end reHeapUp


// Description: Removes (but does not return) the element located at the root.
// Precondition: This Binary Heap is not empty.
// Postcondition: Remains a __________ Binary Heap after the removal.	
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(log2 n)
template<class ElementType>
void BinaryHeap<ElementType>::remove() {
    if(elementCount==0){					//if empty, throw an exception
		throw(EmptyDataCollectionException("dequeue() called with an empty priority Queue.")); 
	}
	else{
	//copy the last element into the root
	elements[0] = elements[elementCount-1];
	elementCount--;
	if(elementCount>1)		//if the root has at least one child, call reHeapDown to correct the positions.
		reHeapDown(0); 
	}
   
	return;
	
}  // end remove


// Utility method - Recursively put the array back into a __________ Binary Heap.
template<class ElementType>
void BinaryHeap<ElementType>::reHeapDown(unsigned int indexOfRoot) {

	unsigned int indexOfMinChild = indexOfRoot;
	
	// Find indices of children.
	unsigned int indexOfLeftChild = 2*indexOfRoot+1;
	unsigned int indexOfRightChild = 2*indexOfRoot+2;

    // Base case: elements[indexOfRoot] is a leaf as it has no children
	if (indexOfLeftChild > elementCount-1) return;

	// If we need to swap, select the smallest child
    // if (elements[indexOfRoot] > elements[indexOfLeftChild])
	if ( ! (elements[indexOfRoot] <= elements[indexOfLeftChild]) )
    	indexOfMinChild = indexOfLeftChild;

    // Check if there is a right child, is it the smallest?
    if (indexOfRightChild < elementCount) {
		// if (elements[indexOfMinChild] > elements[indexOfRightChild])
		if ( ! (elements[indexOfMinChild] <= elements[indexOfRightChild]) )
		    indexOfMinChild = indexOfRightChild;
	}

	// Swap parent with smallest of children.
	if (indexOfMinChild != indexOfRoot) {
		
	   Event temp = elements[indexOfRoot];
	   elements[indexOfRoot] = elements[indexOfMinChild];
	   elements[indexOfMinChild] = temp;
	   
	   // Recursively put the array back into a heap
	   reHeapDown(indexOfMinChild);
    }

	return;
	
} // end reHeapDown


// Description: Retrieves (but does not remove) the element located at the root.
// Precondition: This Binary Heap is not empty.
// Postcondition: This Binary Heap is unchanged.
// Exceptions: Throws EmptyDataCollectionException if this Binary Heap is empty.
// Time Efficiency: O(1) 
template<class ElementType>
Event BinaryHeap<ElementType>::retrieve() const {
   
   // Enforce precondition
   if ( elementCount > 0 )				//if not empty, just return the root
      return elements[0];
   else									//if empty, throw EmptyDataCollectionException.
      throw(EmptyDataCollectionException("peek() called with an empty BinaryHeap.")); 

}  // end retrieve






/*
Below, I left <<operator as well as a normal print function, so if you want to use them , go ahead.
*/

/*
template<class ElementType>
void BinaryHeap<ElementType>::printHeap(){
	for(int i = 0;i<elementCount;i++){
		cout<< elements[i].getTime()<<endl;
	}
}
*/

// For Testing Purposes
// Description: Prints the content of "rhs".
/*
ostream& operator<<(ostream & os, const BinaryHeap<ElementType>& rhs) {
	
	for ( unsigned int index = 0; index < rhs.elementCount; index++ )
		os << rhs.elements[index]; // Print data

	return os;
} // end of operator <<
*/





//  End of implementation file.